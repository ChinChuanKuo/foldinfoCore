open React;
open ReasonReact;
open Setting;
[%bs.raw {|require('../../scss/Chip/chip.scss')|}];

type tupleChildren = (reactElement, reactElement);

type state = {
  enter: bool,
  down: bool,
  enterButn: bool,
  downButn: bool,
};

type action =
  | MouseEnterLeave(bool)
  | MouseUpDown(bool)
  | MouseEnterLeaveButn(bool)
  | MouseUpDownButn(bool);

let reducer = (state, action) =>
  switch (action) {
  | MouseEnterLeave(enter) => {
      ...state,
      enter,
      down: enter ? state.down : false,
    }
  | MouseUpDown(down) => {...state, down}
  | MouseEnterLeaveButn(enterButn) => {
      ...state,
      enterButn,
      downButn: enterButn ? state.downButn : false,
    }
  | MouseUpDownButn(downButn) => {...state, downButn}
  };

let initialState = {
  enter: false,
  down: false,
  enterButn: false,
  downButn: false,
};

let paddings = margin =>
  switch (margin) {
  | None => "8px"
  | Some(margin) => margin ++ "px"
  };

let borderWidths = borderWidth =>
  switch (borderWidth) {
  | None => "1px"
  | Some(borderWidth) => borderWidth ++ "px"
  };

let borderStyles = borderStyle =>
  switch (borderStyle) {
  | None => "solid"
  | Some(borderStyle) => borderStyle
  };

let borderColors = borderColor =>
  switch (borderColor) {
  | None => "rgba(0,0,0,0.23)"
  | Some(borderColor) => borderColor
  };

let borderRadiuses = borderRadius =>
  switch (borderRadius) {
  | None => "16px"
  | Some(borderRadius) => borderRadius ++ "px"
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
  | None => "transparent"
  | Some(backgroundColor) => backgroundColor
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~enterBorderWidth: option(string)=?,
      ~downBorderWidth: option(string)=?,
      ~borderWidth: option(string)=?,
      ~enterBorderStyle: option(string)=?,
      ~downBorderStyle: option(string)=?,
      ~borderStyle: option(string)=?,
      ~enterBorderColor: option(string)=?,
      ~downBorderColor: option(string)=?,
      ~borderColor: option(string)=?,
      ~enterBorderRadius: option(string)=?,
      ~downBorderRadius: option(string)=?,
      ~borderRadius: option(string)=?,
      ~enterBackgroundColor: option(string)=?,
      ~downBackgroundColor: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~showButn: option(bool)=?,
      ~disabledButnBackgroundColor: option(string)=?,
      ~enterButnBackgroundColor: option(string)=?,
      ~downButnBackgroundColor: option(string)=?,
      ~butnBackgroundColor: option(string)=?,
      ~disabled: option(bool)=?,
      ~src: option(string)=?,
      ~onButton: option(ReactEvent.Mouse.t => unit)=?,
      ~children: tupleChildren,
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
                top |> paddings;
              },
              ~paddingRight={
                right |> paddings;
              },
              ~paddingBottom={
                bottom |> paddings;
              },
              ~paddingLeft={
                left |> paddings;
              },
              ~borderWidth={
                switch (state.enter, state.down) {
                | (true, false) => enterBorderWidth |> borderWidths
                | (true, true) => downBorderWidth |> borderWidths
                | (_, _) => borderWidth |> borderWidths
                };
              },
              ~borderStyle={
                switch (state.enter, state.down) {
                | (true, false) => enterBorderStyle |> borderStyles
                | (true, true) => downBorderStyle |> borderStyles
                | (_, _) => borderStyle |> borderStyles
                };
              },
              ~borderColor={
                switch (state.enter, state.down) {
                | (true, false) => enterBorderColor |> borderColors
                | (true, true) => downBorderColor |> borderColors
                | (_, _) => borderColor |> borderColors
                };
              },
              ~borderRadius={
                switch (state.enter, state.down) {
                | (true, false) => enterBorderRadius |> borderRadiuses
                | (true, true) => downBorderRadius |> borderRadiuses
                | (_, _) => borderRadius |> borderRadiuses
                };
              },
              ~backgroundColor={
                switch (state.enter, state.down) {
                | (true, false) =>
                  enterBackgroundColor |> otherBackgroundColors
                | (true, true) => downBackgroundColor |> otherBackgroundColors
                | (_, _) => backgroundColor |> backgroundColors
                };
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~role="button",
        ~className="j8nrp8lcp juyseni",
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
        ~props=ReactDOMRe.domProps(~className="j8nrp8lcts j1s4s3te", ()),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "div",
            ~props=
              ReactDOMRe.domProps(~className="j4f2n9ip ja16k5a j8idkay", ()),
            [|fst(children)|],
          ),
          ReactDOMRe.createDOMElementVariadic(
            "span",
            ~props=ReactDOMRe.domProps(~className="j1ffzryl", ()),
            [|snd(children)|],
          ),
        |],
      ),
      showButn |> disabledObjects
        ? ReactDOMRe.createDOMElementVariadic(
            "span",
            ~props=
              ReactDOMRe.domProps(
                ~style={
                  ReactDOMRe.Style.make(
                    ~backgroundColor={
                      switch (
                        disabled |> disabledObjects,
                        state.enterButn,
                        state.downButn,
                      ) {
                      | (true, _, _) =>
                        disabledButnBackgroundColor |> disabledBackgroundColors
                      | (false, true, false) =>
                        enterButnBackgroundColor |> otherBackgroundColors
                      | (false, true, true) =>
                        downButnBackgroundColor |> otherBackgroundColors
                      | (_, _, _) => butnBackgroundColor |> backgroundColors
                      };
                    },
                    (),
                  );
                },
                ~className="j2dfb39 j2dfspan",
                ~disabled={
                  disabled |> disabledObjects;
                },
                ~onMouseDown=_ => MouseUpDownButn(true) |> dispatch,
                ~onMouseUp=_ => MouseUpDownButn(false) |> dispatch,
                ~onMouseEnter=_ => MouseEnterLeaveButn(true) |> dispatch,
                ~onMouseLeave=_ => MouseEnterLeaveButn(false) |> dispatch,
                ~onClick=?onButton,
                (),
              ),
            [|
              ReactDOMRe.createDOMElementVariadic(
                "img",
                ~props=
                  ReactDOMRe.domProps(
                    ~style={
                      ReactDOMRe.Style.make(
                        ~width="24px",
                        ~height="24px",
                        ~display="block",
                        (),
                      );
                    },
                    ~src={
                      src |> stringObjects;
                    },
                    (),
                  ),
                [||],
              ),
            |],
          )
        : null,
    |],
  );
};
