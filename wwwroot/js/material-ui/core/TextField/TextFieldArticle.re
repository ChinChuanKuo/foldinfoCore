open React;
open Setting;
[%bs.raw {|require('../../scss/TextField/textFieldArticle.scss')|}];

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

let sizes = size =>
  switch (size) {
  | None => "100%"
  | Some(size) => size ++ "px"
  };

let paddingTopBottoms = topBottom =>
  switch (topBottom) {
  | None => "18.5px"
  | Some(topBottom) => topBottom ++ "px"
  };

let paddingRightLefts = rightLeft =>
  switch (rightLeft) {
  | None => "14px"
  | Some(rightLeft) => rightLeft ++ "px"
  };

let borderWidths = borderWidth =>
  switch (borderWidth) {
  | None => "2px"
  | Some(borderWidth) => borderWidth ++ "px"
  };

let borderStyles = borderStyle =>
  switch (borderStyle) {
  | None => "solid"
  | Some(borderStyle) => borderStyle
  };

let borderRadiuses = borderRadius =>
  switch (borderRadius) {
  | None => "4px"
  | Some(borderRadius) => borderRadius ++ "px"
  };

let disabledBorderColors = disabledBorderColor =>
  switch (disabledBorderColor) {
  | None => "rgba(0,0,0,0.26)"
  | Some(disabledBorderColor) => disabledBorderColor
  };

let otherBorderColors = otherBorderColor =>
  switch (otherBorderColor) {
  | None => "rgba(255,0,0,0.8)"
  | Some(otherBorderColor) => otherBorderColor
  };

let borderColors = borderColor =>
  switch (borderColor) {
  | None => "rgba(255,0,0,1)"
  | Some(borderColor) => borderColor
  };

let colors = color =>
  switch (color) {
  | None => "rgba(0,0,0,1)"
  | Some(color) => color
  };

let pointerEvents = disabled => disabled ? "none" : "initial";

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~width: option(string)=?,
      ~maxHeight: option(string)=?,
      ~height: option(string)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~borderWidth: option(string)=?,
      ~borderStyle: option(string)=?,
      ~borderRadius: option(string)=?,
      ~disabledBorderColor: option(string)=?,
      ~enterBorderColor: option(string)=?,
      ~downBorderColor: option(string)=?,
      ~borderColor: option(string)=?,
      ~color: option(string)=?,
      ~textRef: option(React.Ref.t(Js.Nullable.t(Dom.element)))=?,
      ~disabled: option(bool)=?,
      ~onInput: option(ReactEvent.Form.t => unit)=?,
      ~onKeyDown: option(ReactEvent.Keyboard.t => unit)=?,
      ~onBlur: option(ReactEvent.Focus.t => unit)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.make(
            ~width={
              width |> sizes;
            },
            ~maxHeight={
              maxHeight |> sizes;
            },
            (),
          );
        },
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.combine(
                ReactDOMRe.Style.make(
                  ~height={
                    height |> sizes;
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
                  ~borderWidth={
                    borderWidth |> borderWidths;
                  },
                  ~borderStyle={
                    borderStyle |> borderStyles;
                  },
                  ~borderRadius={
                    borderRadius |> borderRadiuses;
                  },
                  ~borderColor={
                    switch (
                      disabled |> disabledObjects,
                      state.enter,
                      state.down,
                    ) {
                    | (true, _, _) =>
                      disabledBorderColor |> disabledBorderColors
                    | (false, true, false) =>
                      enterBorderColor |> otherBorderColors
                    | (false, true, true) =>
                      downBorderColor |> otherBorderColors
                    | (_, _, _) => borderColor |> borderColors
                    };
                  },
                  ~color={
                    color |> colors;
                  },
                  ~pointerEvents={
                    disabled |> disabledObjects |> pointerEvents;
                  },
                  ~outline="none",
                  ~display="block",
                  ~overflow="auto",
                  (),
                ),
                style |> styleObjects,
              );
            },
            ~ref={
              textRef |> refObjects |> ReactDOMRe.Ref.domRef;
            },
            ~className="j1pa5zxfe j1m8k26r",
            ~contentEditable=
              !{
                disabled |> disabledObjects;
              },
            ~suppressContentEditableWarning=
              !{
                disabled |> disabledObjects;
              },
            ~onMouseDown=_ => MouseUpDown(true) |> dispatch,
            ~onMouseUp=_ => MouseUpDown(false) |> dispatch,
            ~onMouseEnter=_ => MouseEnterLeave(true) |> dispatch,
            ~onMouseLeave=_ => MouseEnterLeave(false) |> dispatch,
            ~onInput?,
            ~onKeyDown?,
            ~onBlur?,
            ~onClick?,
            (),
          ),
        [||],
      ),
    |],
  );
};
