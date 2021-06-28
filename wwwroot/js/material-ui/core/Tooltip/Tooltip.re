open React;
open Setting;
[%bs.raw {|require('../../scss/Tooltip/tooltip.scss')|}];

type state = {enter: bool};

type action =
  | MouseEnterLeave(bool);

let reducer = (_, action) =>
  switch (action) {
  | MouseEnterLeave(enter) => {enter: enter}
  };

let initialState = {enter: false};

let widths = width =>
  switch (width) {
  | None => "max-content"
  | Some(width) => width
  };

let tops = location =>
  switch (location) {
  | "top"
  | "topRight"
  | "topLeft" => "0"
  | "right"
  | "left" => "50%"
  | _ => "auto"
  };

let rights = location =>
  switch (location) {
  | "topRight"
  | "right"
  | "bottomRight" => "0"
  | _ => "auto"
  };

let bottoms = location =>
  switch (location) {
  | "bottom"
  | "bottomRight"
  | "bottomLeft" => "0"
  | _ => "auto"
  };

let lefts = location =>
  switch (location) {
  | "top" => "50%"
  | "topLeft"
  | "left"
  | "bottomLeft" => "0"
  | _ => "auto"
  };

let transforms = location =>
  switch (location) {
  | "topRight" => "translate(100%, -150%)"
  | "right" => "translate(100%, -50%)"
  | "bottomRight" => "translate(100%, 150%)"
  | "bottom" => "translate(-50%, 150%)"
  | "bottomLeft" => "translate(-100%, 150%)"
  | "left" => "translate(-100%, -50%)"
  | "topLeft" => "translate(-100%, -150%)"
  | _ => "translate(-50%, -150%)"
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(0,0,0,1)"
  | Some(backgroundColor) => backgroundColor
  };

let colors = color =>
  switch (color) {
  | None => "rgba(255,255,255,1)"
  | Some(color) => color
  };

let fontSizes = fontSize =>
  switch (fontSize) {
  | None => "12px"
  | Some(fontSize) => fontSize ++ "px"
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~width: option(string)=?,
      ~location: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~color: option(string)=?,
      ~fontSize: option(string)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~className="tooltip",
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
              ReactDOMRe.Style.combine(
                ReactDOMRe.Style.make(
                  ~width={
                    width |> widths;
                  },
                  ~top={
                    location |> stringObjects |> tops;
                  },
                  ~right={
                    location |> stringObjects |> rights;
                  },
                  ~bottom={
                    location |> stringObjects |> bottoms;
                  },
                  ~left={
                    location |> stringObjects |> lefts;
                  },
                  ~transform={
                    location |> stringObjects |> transforms;
                  },
                  ~backgroundColor={
                    backgroundColor |> backgroundColors;
                  },
                  ~color={
                    color |> colors;
                  },
                  ~fontSize={
                    fontSize |> fontSizes;
                  },
                  ~visibility={
                    state.enter ? "visible" : "hidden";
                  },
                  (),
                ),
                style |> styleObjects,
              );
            },
            ~className="tooltiptext",
            (),
          ),
        [|children|],
      ),
    |],
  );
};