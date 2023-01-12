open React;
open Setting;
[%bs.raw {|require('../../scss/Button/circleButton.scss')|}];

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
  | "Link"
  | "a" => "a"
  | _ => "button"
  };

let disabledBackgroundColors = disabledBackgroundColor =>
  switch (disabledBackgroundColor) {
  | None => "rgba(102,102,102,0.8)"
  | Some(disabledBackgroundColor) => disabledBackgroundColor
  };

let otherBackgroundColors = otherBackgroundColor =>
  switch (otherBackgroundColor) {
  | None => "rgba(255,0,0,0.8)"
  | Some(otherBackgroundColor) => otherBackgroundColor
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,0,0,1)"
  | Some(backgroundColor) => backgroundColor
  };

let colors = color =>
  switch (color) {
  | None => "rgba(0,0,0,0.87)"
  | Some(color) => color
  };

let cursors = disabled => disabled ? "no-drop" : "pointer";

let sizes = size =>
  switch (size) {
  | "small" => "jkjbjgts"
  | "medium" => "jkjbjgmm"
  | "large" => "j1h1ts3fe"
  | _ => "jkjbjgmm"
  };

[@react.component]
let make =
    (
      ~variant: option(string)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~disabledBackgroundColor: option(string)=?,
      ~enterBackgroundColor: option(string)=?,
      ~downBackgroundColor: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~color: option(string)=?,
      ~href: option(string)=?,
      ~size: option(string)=?,
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
              ~color={
                color |> colors;
              },
              ~cursor={
                disabled |> disabledObjects |> cursors;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~role="button",
        ~href={
          href |> stringObjects;
        },
        ~className={
          (size |> stringObjects |> sizes) ++ " j1xx5fqz j1mg51c jr0u89w";
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
        ~props=ReactDOMRe.domProps(~className="jlyilep", ()),
        [|children|],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=ReactDOMRe.domProps(~className="jb3bkca", ()),
        [||],
      ),
    |],
  );
};
