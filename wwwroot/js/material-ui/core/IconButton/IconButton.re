open React;
open Setting;
[%bs.raw {|require('../../scss/IconButton/iconButton.scss')|}];

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

let components = variant =>
  switch (variant) {
  | "span" => "span"
  | _ => "div"
  };

let disabledBackgroundColors = disabledBackgroundColor =>
  switch (disabledBackgroundColor) {
  | None => "rgba(102,102,102,0.8)"
  | Some(disabledBackgroundColor) => disabledBackgroundColor
  };

let otherBackgroundColors = otherBackgroundColor =>
  switch (otherBackgroundColor) {
  | None => "rgba(0,0,0,0.08)"
  | Some(otherBackgroundColor) => otherBackgroundColor
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "transparent"
  | Some(backgroundColor) => backgroundColor
  };

let paddings = padding =>
  switch (padding) {
  | None => "10px"
  | Some(padding) => padding ++ "px"
  };

let borderRadiuses = borderRadius =>
  switch (borderRadius) {
  | None => "50%"
  | Some(borderRadius) => borderRadius ++ "%"
  };

let colors = color =>
  switch (color) {
  | None => "inherit"
  | Some(color) => color
  };

let ariaLabels = ariaLabel =>
  switch (ariaLabel) {
  | None => "This is Button"
  | Some(ariaLabel) => ariaLabel
  };

let classes = className => {
  let basic = "jss152 jss146";
  switch (className) {
  | None => basic
  | Some(className) => basic ++ " " ++ className
  };
};

let cursors = disabled => disabled ? "no-drop" : "pointer";

let pointerEvents = disabled => disabled ? "none" : "initial";

[@react.component]
let make =
    (
      ~variant: option(string)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~disabledBackgroundColor: option(string)=?,
      ~enterBackgroundColor: option(string)=?,
      ~downBackgroundColor: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~padding: option(string)=?,
      ~borderRadius: option(string)=?,
      ~color: option(string)=?,
      ~ariaLabel: option(string)=?,
      ~className: option(string)=?,
      ~disabled: option(bool)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    variant |> stringObjects |> components,
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~backgroundColor={
                switch (disabled |> disabledObjects, state.enter, state.down) {
                | (true, _, _) =>
                  disabledBackgroundColor |> disabledBackgroundColors
                | (false, true, false) =>
                  enterBackgroundColor |> otherBackgroundColors
                | (false, true, true) =>
                  downBackgroundColor |> otherBackgroundColors
                | (_, _, _) => backgroundColor |> backgroundColors
                };
              },
              ~padding={
                padding |> paddings;
              },
              ~borderRadius={
                borderRadius |> borderRadiuses;
              },
              ~color={
                color |> colors;
              },
              ~cursor={
                disabled |> disabledObjects |> cursors;
              },
              ~pointerEvents={
                disabled |> disabledObjects |> pointerEvents;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~role="button",
        ~ariaLabel={
          ariaLabel |> ariaLabels;
        },
        ~className={
          className |> classes;
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
    [|
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=ReactDOMRe.domProps(~className="jss151", ()),
        [|children|],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=ReactDOMRe.domProps(~className="jss270", ()),
        [||],
      ),
    |],
  );
};