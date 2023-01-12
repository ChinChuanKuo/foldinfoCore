open React;
open Setting;
[%bs.raw {|require('../../scss/Tabs/tab.scss')|}];

type state = {down: bool};

type action =
  | MouseEnterLeave
  | MouseUpDown(bool);

let reducer = (_, action) =>
  switch (action) {
  | MouseEnterLeave => {down: false}
  | MouseUpDown(down) => {down: down}
  };

let initialState = {down: false};

let tabOpacitys = showTab => showTab ? "1" : "0.8";

let maxWidths = maxWidth =>
  switch (maxWidth) {
  | None => "264px"
  | Some(maxWidth) => maxWidth ++ "px"
  };

let heights = height =>
  switch (height) {
  | None => "55px"
  | Some(height) => height ++ "px"
  };

let colors = color =>
  switch (color) {
  | None => "rgba(255,255,255,1)"
  | Some(color) => color
  };

let paddingTopBottoms = topBottom =>
  switch (topBottom) {
  | None => "6px"
  | Some(topBottom) => topBottom ++ "px"
  };

let paddingRightLefts = rightLeft =>
  switch (rightLeft) {
  | None => "12px"
  | Some(rightLeft) => rightLeft ++ "px"
  };

let borderRadiuses = borderRadius =>
  switch (borderRadius) {
  | None => "0px"
  | Some(borderRadius) => borderRadius ++ "px"
  };

let animationNames = animationName =>
  switch (animationName) {
  | None => "pinkWaveAnimation"
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
      ~showTab: option(bool)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~maxWidth: option(string)=?,
      ~height: option(string)=?,
      ~color: option(string)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~borderRadius: option(string)=?,
      ~id: string,
      ~animationName: option(string)=?,
      ~animationDuration: option(string)=?,
      ~animationTimingFunction: option(string)=?,
      ~animationFillMode: option(string)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    "button",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~opacity={
                showTab |> disabledObjects |> tabOpacitys;
              },
              ~maxWidth={
                maxWidth |> maxWidths;
              },
              ~height={
                height |> heights;
              },
              ~color={
                color |> colors;
              },
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
              ~borderRadius={
                borderRadius |> borderRadiuses;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~id,
        ~role="tab",
        ~className=
          "ji48r2t MuiButtonBase-root MuiTab-root MuiTab-textColorInherit",
        ~onMouseDown=_ => MouseUpDown(true) |> dispatch,
        ~onMouseUp=_ => MouseUpDown(false) |> dispatch,
        ~onMouseLeave=_ => MouseEnterLeave |> dispatch,
        ~onClick?,
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=ReactDOMRe.domProps(~className="MuiTab-wrapper", ()),
        [|children|],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~animationName={
                  switch (showTab |> disabledObjects, state.down) {
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
            ~className="MuiTouchRipple-root",
            (),
          ),
        [||],
      ),
    |],
  );
};