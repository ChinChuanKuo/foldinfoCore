open React;
open Setting;

type state = {enter: bool};

type action =
  | MouseEnterLeave(bool);

let reducer = (_, action) =>
  switch (action) {
  | MouseEnterLeave(enter) => {enter: enter}
  };

let initialState = {enter: false};

let paddings = padding =>
  switch (padding) {
  | None => "12px"
  | Some(padding) => padding ++ "px"
  };

let widths = width =>
  switch (width) {
  | None => "auto"
  | Some(width) => width
  };

let cursors = cursor =>
  switch (cursor) {
  | None => "inherit"
  | Some(cursor) => cursor
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

let borderRadiuses = borderRadius =>
  switch (borderRadius) {
  | None => "0px"
  | Some(borderRadius) => borderRadius ++ "px"
  };

let enterBackgroundColors = enterBackgroundColor =>
  switch (enterBackgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(enterBackgroundColor) => enterBackgroundColor
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

let flexGrows = (xs, flexGrow) =>
  switch (xs, flexGrow) {
  | ("no", None) => ""
  | ("auto", None) => "1"
  | (_, None) => "0"
  | (_, Some(flexGrow)) => flexGrow
  };

let maxWidths = (xs, maxWidth) =>
  switch (xs, maxWidth) {
  | ("no", None) => ""
  | ("1", None) => "8.34%"
  | ("2", None) => "16.67%"
  | ("3", None) => "25%"
  | ("4", None) => "33.34%"
  | ("5", None) => "41.67%"
  | ("6", None) => "50%"
  | ("7", None) => "58.34%"
  | ("8", None) => "66.67%"
  | ("9", None) => "75%"
  | ("10", None) => "83.34%"
  | ("11", None) => "91.67%"
  | (_, None) => "100%"
  | (_, Some(maxWidth)) => maxWidth
  };

let flexBasises = (xs, flexBasis) =>
  switch (xs, flexBasis) {
  | ("no", None) => ""
  | ("1", None) => "8.34%"
  | ("2", None) => "16.67%"
  | ("3", None) => "25%"
  | ("4", None) => "33.34%"
  | ("5", None) => "41.67%"
  | ("6", None) => "50%"
  | ("7", None) => "58.34%"
  | ("8", None) => "66.67%"
  | ("9", None) => "75%"
  | ("10", None) => "83.34%"
  | ("11", None) => "91.67%"
  | ("12", None) => "100%"
  | (_, None) => "0"
  | (_, Some(flexBasis)) => flexBasis
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~width: option(string)=?,
      ~cursor: option(string)=?,
      ~enterBorderWidth: option(string)=?,
      ~borderWidth: option(string)=?,
      ~enterBorderStyle: option(string)=?,
      ~borderStyle: option(string)=?,
      ~enterBorderColor: option(string)=?,
      ~borderColor: option(string)=?,
      ~enterBorderRadius: option(string)=?,
      ~borderRadius: option(string)=?,
      ~enterBackgroundColor: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~xs: option(string)=?,
      ~flexGrow: option(string)=?,
      ~maxWidth: option(string)=?,
      ~flexBasis: option(string)=?,
      ~className: option(string)=?,
      ~onClick=?,
      /*~onMouseEnter=?,
        ~onMouseLeave=?,*/
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  /*let onMouseEnter = onMouseEnter |> actionObjects;
    let mouseEnter =
      useCallback(event => {
        onMouseEnter(event);
        MouseEnterLeave(true) |> dispatch;
      });
    let onMouseLeave = onMouseLeave |> actionObjects;
    let mouseLeave =
      useCallback(event => {
        onMouseLeave(event);
        MouseEnterLeave(false) |> dispatch;
      });*/
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~paddingTop={
                top |> paddings;
              },
              ~paddingRight={
                right |> paddings;
              },
              ~paddingBottom={
                bottom |> paddings;
              },
              ~paddingLeft={
                left |> paddings;
              },
              ~width={
                width |> widths;
              },
              ~cursor={
                cursor |> cursors;
              },
              ~borderWidth={
                state.enter
                  ? enterBorderWidth |> borderWidths
                  : borderWidth |> borderWidths;
              },
              ~borderStyle={
                state.enter
                  ? enterBorderStyle |> borderStyles
                  : borderStyle |> borderStyles;
              },
              ~borderColor={
                state.enter
                  ? enterBorderColor |> borderColors
                  : borderColor |> borderColors;
              },
              ~borderRadius={
                state.enter
                  ? enterBorderRadius |> borderRadiuses
                  : borderRadius |> borderRadiuses;
              },
              ~backgroundColor={
                state.enter
                  ? enterBackgroundColor |> enterBackgroundColors
                  : backgroundColor |> backgroundColors;
              },
              ~flexGrow={
                flexGrows(xs |> stringObjects, flexGrow);
              },
              ~maxWidth={
                maxWidths(xs |> stringObjects, maxWidth);
              },
              ~flexBasis={
                flexBasises(xs |> stringObjects, flexBasis);
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className={
          className |> stringObjects;
        },
        ~onClick?,
        ~onMouseEnter=_ => MouseEnterLeave(true) |> dispatch,
        ~onMouseLeave=_ => MouseEnterLeave(false) |> dispatch,
        (),
      ),
    [|children|],
  );
};
