open React;
open ReasonReact;
open Setting;
[%bs.raw {|require('../../scss/ListItem/listItem.scss')|}];

type tupleChildren = (reactElement, reactElement);

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
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

let disablePaddings = disablePadding => disablePadding ? "32px" : "16px";

let displays = display =>
  switch (display) {
  | None => "flex"
  | Some(display) => display
  };

let borderRadiuses = borderRadius =>
  switch (borderRadius) {
  | None => "0px"
  | Some(borderRadius) => borderRadius ++ "px"
  };

let paddingTopBottoms = topBottom =>
  switch (topBottom) {
  | None => "0px"
  | Some(topBottom) => topBottom ++ "px"
  };

let paddingRightLefts = rightLeft =>
  switch (rightLeft) {
  | None => "16px"
  | Some(rightLeft) => rightLeft ++ "px"
  };

let colors = color =>
  switch (color) {
  | None => "rgba(0,0,0,1)"
  | Some(color) => color
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
      ~disablePadding: option(bool)=?,
      ~display: option(string)=?,
      ~topLeft: option(string)=?,
      ~topRight: option(string)=?,
      ~bottomRight: option(string)=?,
      ~bottomLeft: option(string)=?,
      ~disabled: option(bool)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~color: option(string)=?,
      ~children: tupleChildren,
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
              ~paddingLeft={
                disablePadding |> disabledObjects |> disablePaddings;
              },
              ~display={
                display |> displays;
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
              (),
            ),
            style |> styleObjects,
          );
        },
        ~role="button",
        ~className="j1a697ls j1nroktp jn23b2n jr0u89wl",
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
        "div",
        ~props=ReactDOMRe.domProps(~className="j1xd9iw9", ()),
        [|fst(children)|],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~paddingTop={
                  top |> paddingTopBottoms;
                },
                ~paddingRight={
                  right |> paddingRightLefts;
                },
                ~paddingBottom={
                  bottom |> paddingTopBottoms;
                },
                ~paddingLeft={
                  left |> paddingRightLefts;
                },
                (),
              );
            },
            ~className="j9018ah",
            (),
          ),
        [|
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
                ~className="j1pzzryc j59oks2",
                (),
              ),
            [|snd(children)|],
          ),
        |],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=ReactDOMRe.domProps(~className="jb3bkca", ()),
        [||],
      ),
    |],
  );
};
