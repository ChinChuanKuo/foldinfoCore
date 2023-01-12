open React;
open ReasonReact;
open Setting;
[%bs.raw {|require('../../scss/Navigation/navigationAction.scss')|}];

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

let disabledBackgroundColors = disabledBackgroundColor =>
  switch (disabledBackgroundColor) {
  | None => "transparent"
  | Some(disabledBackgroundColor) => disabledBackgroundColor
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

let colors = color =>
  switch (color) {
  | None => "#2196f3"
  | Some(color) => color
  };

let stillColors = stillColor =>
  switch (stillColor) {
  | None => "rgba(0,0,0,0.54)"
  | Some(stillColor) => stillColor
  };

let paddingTops = showAction => showAction ? "6px" : "16px";

let cursors = disabled => disabled ? "no-drop" : "pointer";

let actionClass = showAction => {
  let basic = "j9jzp64";
  showAction ? basic ++ " j1kms6th" : basic ++ " j1rdad3f";
};

let animationNames = animationName =>
  switch (animationName) {
  | None => "blueWaveAnimation"
  | Some(animationName) => animationName
  };

let animationDurations = animationDuration =>
  switch (animationDuration) {
  | None => "0.3s"
  | Some(animationDuration) => animationDuration
  };

let animationTimingFunctions = animationTimingFunction =>
  switch (animationTimingFunction) {
  | None => "linear"
  | Some(animationTimingFunction) => animationTimingFunction
  };

let animationFillModes = animationFillMode =>
  switch (animationFillMode) {
  | None => "forwards"
  | Some(animationFillMode) => animationFillMode
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~showAction: option(bool)=?,
      ~disabledBackgroundColor: option(string)=?,
      ~enterBackgroundColor: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~color: option(string)=?,
      ~stillColor: option(string)=?,
      ~animationName: option(string)=?,
      ~animationDuration: option(string)=?,
      ~animationTimingFunction: option(string)=?,
      ~animationFillMode: option(string)=?,
      ~disabled: option(bool)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children: tupleChildren,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    "button",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~backgroundColor={
                switch (disabled |> disabledObjects, state.enter) {
                | (true, _) =>
                  disabledBackgroundColor |> disabledBackgroundColors
                | (false, true) => enterBackgroundColor |> backgroundColors
                | (_, _) => backgroundColor |> backgroundColors
                };
              },
              ~color={
                showAction |> disabledObjects
                  ? color |> colors : stillColor |> stillColors;
              },
              ~paddingTop={
                showAction |> disabledObjects |> paddingTops;
              },
              ~cursor={
                disabled |> disabledObjects |> cursors;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="jr0u89w ji48r2j",
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
        ~props=ReactDOMRe.domProps(~className="j4q78u6 j4q78u6zi", ()),
        [|
          fst(children),
          ReactDOMRe.createDOMElementVariadic(
            "span",
            ~props=
              ReactDOMRe.domProps(
                ~className={
                  showAction |> disabledObjects |> actionClass;
                },
                (),
              ),
            [|snd(children)|],
          ),
        |],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~animationName={
                  switch (showAction |> disabledObjects, state.down) {
                  | (true, true) => animationName |> animationNames
                  | (false, true) => "grayWaveAnimation"
                  | (_, _) => ""
                  };
                },
                ~animationDuration={
                  animationDuration |> animationDurations;
                },
                ~animationTimingFunction={
                  animationTimingFunction |> animationTimingFunctions;
                },
                ~animationFillMode={
                  animationFillMode |> animationFillModes;
                },
                (),
              );
            },
            ~className="jb3bkca",
            (),
          ),
        [||],
      ),
    |],
  );
};