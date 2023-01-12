open React;
open Setting;
[%bs.raw {|require('../../scss/Slider/slider.scss')|}];

type state = {
  enter: bool,
  down: bool,
};

type action =
  | MouseEnterLeave(bool)
  | MouseUpDown(bool);

let reducer = (state, action) =>
  switch (action) {
  | MouseEnterLeave(enter) => {enter, down: enter ? state.down : false}
  | MouseUpDown(down) => {...state, down}
  };

let initialState = {enter: false, down: false};

let colors = color =>
  switch (color) {
  | None => "rgba(255,0,0,0.8)"
  | Some(color) => color
  };

let lefts = left =>
  switch (left) {
  | None => "0%"
  | Some(left) => left ++ "%"
  };

let values = value =>
  switch (value) {
  | None => "0"
  | Some(value) => value
  };

let classes = overShow => {
  let basic = "MuiSlider-mark";
  overShow ? basic ++ " MuiSlider-markActive" : basic;
};

let fontColors = fontColor =>
  switch (fontColor) {
  | None => "rgba(255,255,255,1)"
  | Some(fontColor) => fontColor
  };

[@react.component]
let make =
    (
      ~min: option(int)=?,
      ~max: option(int)=?,
      ~step: option(int)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~color: option(string)=?,
      ~value: option(string)=?,
      ~fontColor: option(string)=?,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);

  let steps: int = value |> values |> int_of_string;

  let items: array(int) =
    Array.make(intObjects(max) / intObjects(step), 0);

  for (x in
       intObjects(min) / intObjects(step) - 1 to
       intObjects(max) / intObjects(step) - 1) {
    items[x] = x * intObjects(step);
  };

  ReactDOMRe.createDOMElementVariadic(
    "span",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.make(
            ~color={
              color |> colors;
            },
            (),
          );
        },
        ~className="MuiSlider-root",
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              style |> styleObjects;
            },
            ~className="MuiSlider-rail",
            (),
          ),
        [||],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~left="0%",
                ~width={
                  value |> lefts;
                },
                () //when change value, this need change too. default zero number
              );
            },
            ~className="MuiSlider-track",
            (),
          ),
        [||],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "input",
        ~props=
          ReactDOMRe.domProps(
            ~type_="hidden",
            ~value={
              value |> values;
            },
            (),
          ), //when change value, this need change too. default min number
        [||],
      ),
      {
        items
        |> Array.map(item =>
             ReactDOMRe.createDOMElementVariadic(
               "span",
               ~props=
                 ReactDOMRe.domProps(
                   ~style={
                     ReactDOMRe.Style.make(
                       ~left={
                         string_of_int(item) ++ "%";
                       },
                       (),
                     );
                   },
                   //~className="MuiSlider-mark MuiSlider-markActive",
                   ~className={
                     item < steps |> classes;
                   },
                   (),
                 ),
               [||],
             )
           )
        |> array;
      },
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~left={
                  value |> lefts;
                },
                (),
              );
            },
            //~className="MuiSlider-markLabel MuiSlider-markLabelActive",
            ~className="MuiSlider-markLabel",
            (),
          ),
        [||],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~left={
                  value |> lefts;
                },
                ~boxShadow={
                  switch (state.enter, state.down) {
                  | (true, false) => "0px 0px 0px 10px rgba(144, 202, 249, 0.16)"
                  | (true, true) => "0px 0px 0px 14px rgba(144, 202, 249, 0.16)"
                  | (_, _) => ""
                  };
                },
                ~cursor="pointer",
                () //when change value, this need change too. default zero number too.
              );
            },
            ~role="slider",
            ~className="MuiSlider-thumb",
            ~onMouseDown=_ => MouseUpDown(true) |> dispatch,
            ~onMouseUp=_ => MouseUpDown(false) |> dispatch,
            ~onMouseEnter=_ => MouseEnterLeave(true) |> dispatch,
            ~onMouseLeave=_ => MouseEnterLeave(false) |> dispatch,
            (),
          ),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "span",
            ~props=
              ReactDOMRe.domProps(
                ~style={
                  ReactDOMRe.Style.make(
                    ~transform={
                      state.enter ? "scale(1) translateY(-10px)" : "";
                    },
                    (),
                  );
                },
                ~className="jss867",
                (),
              ),
            [|
              ReactDOMRe.createDOMElementVariadic(
                "span",
                ~props=ReactDOMRe.domProps(~className="jss868", ()),
                [|
                  ReactDOMRe.createDOMElementVariadic(
                    "span",
                    ~props=
                      ReactDOMRe.domProps(
                        ~style={
                          ReactDOMRe.Style.make(
                            ~color={
                              fontColor |> fontColors;
                            },
                            (),
                          );
                        },
                        ~className="jss869",
                        (),
                      ),
                    [|value |> values |> string|],
                  ),
                |],
              ),
            |],
          ),
        |],
      ),
    |],
  );
};
