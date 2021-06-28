open React;
open Setting;
[%bs.raw {|require('../../scss/Switch/switch.scss')|}];

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

let marginRights = right =>
  switch (right) {
  | None => "16px"
  | Some(right) => right ++ "px"
  };

let marginLefts = left =>
  switch (left) {
  | None => "-14px"
  | Some(left) => left ++ "px"
  };

let paddings = padding =>
  switch (padding) {
  | None => "0px"
  | Some(padding) => padding ++ "px"
  };

let transforms = checked => checked ? "translateX(14px)" : "translateX(0px)";

let circleColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,0,0,0.8)"
  | Some(backgroundColor) => backgroundColor
  };

let downBoxShadows = downBoxShadow =>
  switch (downBoxShadow) {
  | None => "0px 0px 0px 12px rgba(0,0,0,0.16)"
  | Some(downBoxShadow) => downBoxShadow
  };

let boxShadows = boxShadow =>
  switch (boxShadow) {
  | None => "0px 0px 0px 8px rgba(0,0,0,0.16)"
  | Some(boxShadow) => boxShadow
  };

let linearColors = linearColor =>
  switch (linearColor) {
  | None => "rgba(0,0,0,0.38)"
  | Some(linearColor) => linearColor
  };

let disabledFontColors = disabledFontColor =>
  switch (disabledFontColor) {
  | None => "rgba(0,0,0,0.26)"
  | Some(disabledFontColor) => disabledFontColor
  };

let fontColors = fontColor =>
  switch (fontColor) {
  | None => "rgba(0,0,0,1)"
  | Some(fontColor) => fontColor
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~right: option(string)=?,
      ~left: option(string)=?,
      ~checked: option(bool)=?,
      ~padding: option(string)=?,
      ~circleColor: option(string)=?,
      ~checkBoxShadow: option(string)=?,
      ~enterBoxShadow: option(string)=?,
      ~downBoxShadow: option(string)=?,
      ~linearColor: option(string)=?,
      ~disabledFontColor: option(string)=?,
      ~fontColor: option(string)=?,
      ~disabled: option(bool)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    "label",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.make(
            ~marginRight={
              right |> marginRights;
            },
            ~marginLeft={
              left |> marginLefts;
            },
            (),
          );
        },
        ~className="j14cdvo3",
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=ReactDOMRe.domProps(~className="j1p4uln4", ()),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "span",
            ~props=
              ReactDOMRe.domProps(
                ~style={
                  ReactDOMRe.Style.make(
                    ~padding={
                      padding |> paddings;
                    },
                    ~transform={
                      checked |> disabledObjects |> transforms;
                    },
                    (),
                  );
                },
                ~className="jr0u89w j1g2vga5 j15rg1tn jtb5zs6 j1nv0zgm",
                (),
              ),
            [|
              ReactDOMRe.createDOMElementVariadic(
                "span",
                ~props=ReactDOMRe.domProps(~className="jsbmc5e", ()),
                [|
                  ReactDOMRe.createDOMElementVariadic(
                    "span",
                    ~props=
                      ReactDOMRe.domProps(
                        ~style={
                          ReactDOMRe.Style.combine(
                            ReactDOMRe.Style.make(
                              ~backgroundColor={
                                circleColor |> circleColors;
                              },
                              ~boxShadow={
                                switch (
                                  disabled |> disabledObjects,
                                  checked |> disabledObjects,
                                  state.enter,
                                  state.down,
                                ) {
                                | (false, true, true, false) =>
                                  checkBoxShadow |> boxShadows
                                | (false, false, true, false) =>
                                  enterBoxShadow |> boxShadows
                                | (false, _, true, true) =>
                                  downBoxShadow |> downBoxShadows
                                | (_, _, _, _) => ""
                                };
                              },
                              (),
                            ),
                            style |> styleObjects,
                          );
                        },
                        ~className="jxselqx",
                        (),
                      ),
                    [||],
                  ),
                  ReactDOMRe.createDOMElementVariadic(
                    "input",
                    ~props=
                      ReactDOMRe.domProps(
                        ~type_="checkbox",
                        ~className="j9ixv80",
                        ~checked={
                          checked |> disabledObjects;
                        },
                        ~disabled={
                          disabled |> disabledObjects;
                        },
                        ~onMouseDown=_ => MouseUpDown(true) |> dispatch,
                        ~onMouseUp=_ => MouseUpDown(false) |> dispatch,
                        ~onMouseEnter=_ => MouseEnterLeave(true) |> dispatch,
                        ~onMouseLeave=_ => MouseEnterLeave(false) |> dispatch,
                        ~onClick?,
                        (),
                      ),
                    [||],
                  ),
                |],
              ),
              ReactDOMRe.createDOMElementVariadic(
                "span",
                ~props=ReactDOMRe.domProps(~className="jb3bkca", ()),
                [||],
              ),
            |],
          ),
          ReactDOMRe.createDOMElementVariadic(
            "span",
            ~props=
              ReactDOMRe.domProps(
                ~style={
                  ReactDOMRe.Style.make(
                    ~backgroundColor={
                      linearColor |> linearColors;
                    },
                    (),
                  );
                },
                ~className="ju2cry8",
                (),
              ),
            [||],
          ),
        |],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~color={
                  disabled |> disabledObjects
                    ? disabledFontColor |> disabledFontColors
                    : fontColor |> fontColors;
                },
                (),
              );
            },
            ~className="j59oks2 j1n0vc23",
            (),
          ),
        [|children|],
      ),
    |],
  );
};