open React;
open Setting;
[%bs.raw {|require('../../scss/TextField/textFieldOutline.scss')|}];

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

let widths = width =>
  switch (width) {
  | None => "calc(100% - 12px)"
  | Some(width) => "calc(" ++ width ++ "% - 12px)"
  };

let marginTops = top =>
  switch (top) {
  | None => "16px"
  | Some(top) => top ++ "px"
  };

let marginOthers = other =>
  switch (other) {
  | None => "8px"
  | Some(other) => other ++ "px"
  };

let disabledColors = disabledBorderColor =>
  switch (disabledBorderColor) {
  | None => "rgba(0,0,0,0.26)"
  | Some(disabledBorderColor) => disabledBorderColor
  };

let colors = color =>
  switch (color) {
  | None => "rgba(255,0,0,0.6)"
  | Some(color) => color
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

let fontColors = fontColor =>
  switch (fontColor) {
  | None => "rgba(0,0,0,1)"
  | Some(fontColor) => fontColor
  };

let types = type_ =>
  switch (type_) {
  | None => "text"
  | Some(type_) => type_
  };

let placeholders = placeholder =>
  switch (placeholder) {
  | None => "Please enter"
  | Some(placeholder) => placeholder
  };

[@react.component]
let make =
    (
      ~width: option(string)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~disabledLabelColor: option(string)=?,
      ~labelColor: option(string)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~borderTop: option(string)=?,
      ~borderRight: option(string)=?,
      ~borderBottom: option(string)=?,
      ~borderLeft: option(string)=?,
      ~borderWidth: option(string)=?,
      ~borderStyle: option(string)=?,
      ~borderRadius: option(string)=?,
      ~disabledBorderColor: option(string)=?,
      ~enterBorderColor: option(string)=?,
      ~downBorderColor: option(string)=?,
      ~borderColor: option(string)=?,
      ~fontColor: option(string)=?,
      ~type_: option(string)=?,
      ~placeholder: option(string)=?,
      ~value: option(string)=?,
      ~disabled: option(bool)=?,
      ~onChange: option(ReactEvent.Form.t => unit)=?,
      ~onKeyDown: option(ReactEvent.Keyboard.t => unit)=?,
      ~onBlur: option(ReactEvent.Focus.t => unit)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.make(
            ~width={
              width |> widths;
            },
            ~marginTop={
              top |> marginTops;
            },
            ~marginRight={
              right |> marginOthers;
            },
            ~marginBottom={
              bottom |> marginOthers;
            },
            ~marginLeft={
              left |> marginOthers;
            },
            (),
          );
        },
        ~className="joig26a",
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "label",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~backgroundColor="rgba(255,255,255,1)",
                ~paddingRight="5px",
                ~paddingLeft="5px",
                ~color={
                  disabled |> disabledObjects
                    ? disabledLabelColor |> disabledColors
                    : labelColor |> colors;
                },
                (),
              );
            },
            ~className="j1g19fqe j189b1ed j12la19 j1sj1d1q j1azw8op",
            (),
          ),
        [|children|],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=ReactDOMRe.domProps(~className="jbr6nlo j7v6wc2", ()),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "input",
            ~props=
              ReactDOMRe.domProps(
                ~style={
                  ReactDOMRe.Style.combine(
                    ReactDOMRe.Style.make(
                      ~paddingTop={
                        borderTop |> paddingTopBottoms;
                      },
                      ~paddingRight={
                        borderRight |> paddingRightLefts;
                      },
                      ~paddingBottom={
                        borderBottom |> paddingTopBottoms;
                      },
                      ~paddingLeft={
                        borderLeft |> paddingRightLefts;
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
                          disabledBorderColor |> disabledColors
                        | (false, true, false) =>
                          enterBorderColor |> otherBorderColors
                        | (false, true, true) =>
                          downBorderColor |> otherBorderColors
                        | (_, _, _) => borderColor |> borderColors
                        };
                      },
                      ~color={
                        fontColor |> fontColors;
                      },
                      (),
                    ),
                    style |> styleObjects,
                  );
                },
                ~className="j4ap7vg j106nmqb",
                ~type_={
                  type_ |> types;
                },
                ~placeholder={
                  placeholder |> placeholders;
                },
                ~value={
                  value |> stringObjects;
                },
                ~disabled={
                  disabled |> disabledObjects;
                },
                ~onMouseDown=_ => MouseUpDown(true) |> dispatch,
                ~onMouseUp=_ => MouseUpDown(false) |> dispatch,
                ~onMouseEnter=_ => MouseEnterLeave(true) |> dispatch,
                ~onMouseLeave=_ => MouseEnterLeave(false) |> dispatch,
                ~onChange?,
                ~onKeyDown?,
                ~onBlur?,
                ~onClick?,
                (),
              ),
            [||],
          ),
        |],
      ),
    |],
  );
};
