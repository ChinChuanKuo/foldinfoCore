open React;
open Setting;
[%bs.raw {|require('../../scss/TextField/textFieldStandard.scss')|}];

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

let labelTops = labelTop =>
  switch (labelTop) {
  | None => "6px"
  | Some(labelTop) => labelTop ++ "px"
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
  | None => "10px"
  | Some(topBottom) => topBottom ++ "px"
  };

let paddingRightLefts = rightLeft =>
  switch (rightLeft) {
  | None => "14px"
  | Some(rightLeft) => rightLeft ++ "px"
  };

let borderBottomWidths = borderBottomWidth =>
  switch (borderBottomWidth) {
  | None => "2px"
  | Some(borderBottomWidth) => borderBottomWidth ++ "px"
  };

let borderBottomStyles = borderBottomStyle =>
  switch (borderBottomStyle) {
  | None => "solid"
  | Some(borderBottomStyle) => borderBottomStyle
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
      ~labelTop: option(string)=?,
      ~disabledLabelColor: option(string)=?,
      ~labelColor: option(string)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~borderTop: option(string)=?,
      ~borderRight: option(string)=?,
      ~borderBottom: option(string)=?,
      ~borderLeft: option(string)=?,
      ~borderWidth: option(string)=?,
      ~borderStyle: option(string)=?,
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
                ~marginTop={
                  labelTop |> labelTops;
                },
                ~color={
                  disabled |> disabledObjects
                    ? disabledLabelColor |> disabledColors
                    : labelColor |> colors;
                },
                (),
              );
            },
            ~className="j1g19fqe j189b1ed j12la19 j1sj1d1qs j1sj1d1q j1azw8op",
            (),
          ),
        [|children|],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=ReactDOMRe.domProps(~className="jbr6nlo j77gjdk j5t5fws", ()),
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
                      ~borderBottomWidth={
                        borderWidth |> borderBottomWidths;
                      },
                      ~borderBottomStyle={
                        borderStyle |> borderBottomStyles;
                      },
                      ~borderBottomColor={
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
                ~className="j4ap7vg j4ap7vgd",
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
