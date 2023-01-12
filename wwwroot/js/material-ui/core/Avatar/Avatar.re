open React;
open Setting;
[%bs.raw {|require('../../scss/Avatar/avatar.scss')|}];

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

let margins = margin =>
  switch (margin) {
  | None => "10px"
  | Some(margin) => margin ++ "px"
  };

let colors = color =>
  switch (color) {
  | None => "#fafafa"
  | Some(color) => color
  };

let borderWidths = borderWidth =>
  switch (borderWidth) {
  | None => "1px"
  | Some(borderWidth) => borderWidth ++ "px"
  };

let borderStyles = borderStyle =>
  switch (borderStyle) {
  | None => "solid"
  | Some(borderStyle) => borderStyle
  };

let borderColors = borderColor =>
  switch (borderColor) {
  | None => "transparent"
  | Some(borderColor) => borderColor
  };

let enterBorderColors = enterBorderColor =>
  switch (enterBorderColor) {
  | None => "rgba(255,0,0,1)"
  | Some(enterBorderColor) => enterBorderColor
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "#bdbdbd"
  | Some(backgroundColor) => backgroundColor
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~color: option(string)=?,
      ~borderWidth: option(string)=?,
      ~borderStyle: option(string)=?,
      ~enterBorderColor: option(string)=?,
      ~downBorderColor: option(string)=?,
      ~borderColor: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    "header",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~marginTop={
                top |> margins;
              },
              ~marginRight={
                right |> margins;
              },
              ~marginBottom={
                bottom |> margins;
              },
              ~marginLeft={
                left |> margins;
              },
              ~color={
                color |> colors;
              },
              ~cursor="pointer",
              ~borderWidth={
                borderWidth |> borderWidths;
              },
              ~borderStyle={
                borderStyle |> borderStyles;
              },
              ~borderColor={
                switch (state.enter, state.down) {
                | (true, false) => enterBorderColor |> enterBorderColors
                | (true, true) => downBorderColor |> enterBorderColors
                | (_, _) => borderColor |> borderColors
                };
              },
              ~backgroundColor={
                backgroundColor |> backgroundColors;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="j4f2n9i",
        ~onMouseDown=_ => MouseUpDown(true) |> dispatch,
        ~onMouseUp=_ => MouseUpDown(false) |> dispatch,
        ~onMouseEnter=_ => MouseEnterLeave(true) |> dispatch,
        ~onMouseLeave=_ => MouseEnterLeave(false) |> dispatch,
        ~onClick?,
        (),
      ),
    [|children|],
  );
};