open React;
open Setting;
[%bs.raw {|require('../../scss/Paper/paper.scss')|}];

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

let paddingTopBottoms = topBottom =>
  switch (topBottom) {
  | None => "16px"
  | Some(topBottom) => topBottom ++ "px"
  };

let otherBackgroundColors = otherBackgroundColor =>
  switch (otherBackgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(otherBackgroundColor) => otherBackgroundColor
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

let boxShadows = boxShadow =>
  switch (boxShadow) {
  | None => "0px 1px 10px 0px rgba(0, 0, 0, 0.2), 0px 1px 1px 0px rgba(0, 0, 0, 0.14), 0px 2px 1px -1px rgba(0, 0, 0, 0.12)"
  | Some(boxShadow) => boxShadow
  };

let borderRadiuses = borderRadius =>
  switch (borderRadius) {
  | None => "4px"
  | Some(borderRadius) => borderRadius ++ "px"
  };

let classes = className => {
  let basic = "j1q4pwjm";
  switch (className) {
  | None => basic
  | Some(className) => basic ++ " " ++ className
  };
};

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~top: option(string)=?,
      ~bottom: option(string)=?,
      ~enterBackgroundColor: option(string)=?,
      ~downBackgroundColor: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~enterBoxShadow: option(string)=?,
      ~downBoxShadow: option(string)=?,
      ~boxShadow: option(string)=?,
      ~enterBorderRadius: option(string)=?,
      ~downBorderRadius: option(string)=?,
      ~borderRadius: option(string)=?,
      ~className: option(string)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~paddingTop={
                top |> paddingTopBottoms;
              },
              ~paddingBottom={
                bottom |> paddingTopBottoms;
              },
              ~backgroundColor={
                switch (state.enter, state.down) {
                | (true, false) =>
                  enterBackgroundColor |> otherBackgroundColors
                | (true, true) => downBackgroundColor |> otherBackgroundColors
                | (_, _) => backgroundColor |> backgroundColors
                };
              },
              ~boxShadow={
                switch (state.enter, state.down) {
                | (true, false) => enterBoxShadow |> boxShadows
                | (true, true) => downBoxShadow |> boxShadows
                | (_, _) => boxShadow |> boxShadows
                };
              },
              ~borderRadius={
                switch (state.enter, state.down) {
                | (true, false) => enterBorderRadius |> borderRadiuses
                | (true, true) => downBorderRadius |> borderRadiuses
                | (_, _) => borderRadius |> borderRadiuses
                };
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className={
          className |> classes;
        },
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