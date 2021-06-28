open React;
open Setting;
[%bs.raw {|require('../../scss/MenuItem/menuItem.scss')|}];

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

let paddingOthers = other =>
  switch (other) {
  | None => "11px"
  | Some(other) => other ++ "px"
  };

let paddingRights = right =>
  switch (right) {
  | None => "16px"
  | Some(right) => right ++ "px"
  };

let disablePaddings = (left, disablePadding) =>
  switch (left, disablePadding) {
  | (None, true) => "32px"
  | (None, false) => "16px"
  | (Some(left), _) => left ++ "px"
  };

let minHeights = minHeight =>
  switch (minHeight) {
  | None => "46px"
  | Some(minHeight) => minHeight ++ "px"
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
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

let borderRadiuses = borderRadius =>
  switch (borderRadius) {
  | None => "0px"
  | Some(border) => border ++ "px"
  };

let colors = color =>
  switch (color) {
  | None => "rgba(0,0,0,1)"
  | Some(color) => color
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~disablePadding: option(bool)=?,
      ~minHeight: option(string)=?,
      ~disabledBackgroundColor: option(string)=?,
      ~enterBackgroundColor: option(string)=?,
      ~downBackgroundColor: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~topLeft: option(string)=?,
      ~topRight: option(string)=?,
      ~bottomRight: option(string)=?,
      ~bottomLeft: option(string)=?,
      ~color: option(string)=?,
      ~disabled: option(bool)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    "li",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~paddingTop={
                top |> paddingOthers;
              },
              ~paddingRight={
                right |> paddingRights;
              },
              ~paddingBottom={
                bottom |> paddingOthers;
              },
              ~paddingLeft={
                disablePaddings(left, disablePadding |> disabledObjects);
              },
              ~minHeight={
                minHeight |> minHeights;
              },
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
              ~borderTopLeftRadius={
                topLeft |> borderRadiuses;
              },
              ~borderTopRightRadius={
                topRight |> borderRadiuses;
              },
              ~borderBottomRightRadius={
                bottomRight |> borderRadiuses;
              },
              ~borderBottomLeftRadius={
                bottomLeft |> borderRadiuses;
              },
              ~color={
                color |> colors;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~role="menuitem",
        ~className="jr0u89wlm jn23b2n j1a697ls j1nroktp jkz2jqj",
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
      children,
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=ReactDOMRe.domProps(~className="jb3bkca", ()),
        [||],
      ),
    |],
  );
};
