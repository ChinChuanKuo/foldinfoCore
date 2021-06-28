open React;
open Setting;
[%bs.raw {|require('../../scss/Button/button.scss')|}];

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
  | None => "rgba(255,255,255,1)"
  | Some(color) => color
  };

let widths = width =>
  switch (width) {
  | None => "auto"
  | Some(width) => width
  };

let cursors = disabled => disabled ? "no-drop" : "pointer";

let borders = border =>
  switch (border) {
  | "contained" => "jpyw0mp"
  | "text" => "j1hrif9t"
  | "outlined" => "j5jkmku"
  | _ => "j1hrif9t"
  };

let sizes = size =>
  switch (size) {
  | "small" => "jkjbjgt"
  | "medium" => "jkjbjgm"
  | "large" => "j1h1ts3f"
  | _ => "jkjbjgm"
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
      ~width: option(string)=?,
      ~href: option(string)=?,
      ~border: option(string)=?,
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
              ~width={
                width |> widths;
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
          "j9la4jl jr0u89w j16xd9wg "
          ++ (border |> stringObjects |> borders)
          ++ " "
          ++ (size |> stringObjects |> sizes);
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
