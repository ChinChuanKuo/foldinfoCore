open React;
open ReasonReact;
open Setting;
[%bs.raw {|require('../../scss/Select/selectOutline.scss')|}];

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

let widths = width =>
  switch (width) {
  | None => "calc(100% - 12px)"
  | Some(width) => "calc(" ++ width ++ "% - 12px)"
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

let marginTops = marginTop =>
  switch (marginTop) {
  | None => "24px"
  | Some(marginTop) => marginTop ++ "px"
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
      ~tile: option(string)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~borderWidth: option(string)=?,
      ~borderStyle: option(string)=?,
      ~disabledBorderColor: option(string)=?,
      ~enterBorderColor: option(string)=?,
      ~downBorderColor: option(string)=?,
      ~borderColor: option(string)=?,
      ~fontColor: option(string)=?,
      ~value: option(string)=?,
      ~disabled: option(bool)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children: tupleChildren,
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
            ~marginTop="0px",
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
                ~zIndex="1",
                ~marginTop={
                  top |> marginTops;
                },
                ~color={
                  disabled |> disabledObjects
                    ? disabledLabelColor |> disabledColors
                    : labelColor |> colors;
                },
                (),
              );
            },
            ~className=
              "j1g19fqe j189b1ed j12la19 j1sj1d1qso j1sj1d1q j1g6ef6m",
            (),
          ),
        [|tile |> stringObjects |> string|],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~marginTop={
                  top |> marginTops;
                },
                (),
              );
            },
            ~className="jbr6nlo j1hdgrm8",
            (),
          ),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "div",
            ~props=ReactDOMRe.domProps(~className="je77vcb", ()),
            [|
              ReactDOMRe.createDOMElementVariadic(
                "div",
                ~props=
                  ReactDOMRe.domProps(
                    ~style={
                      ReactDOMRe.Style.combine(
                        ReactDOMRe.Style.make(
                          ~width="auto",
                          ~borderWidth={
                            borderWidth |> borderWidths;
                          },
                          ~borderStyle={
                            borderStyle |> borderStyles;
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
                    ~role="button",
                    ~className=
                      "j1blqbob j1j3s8fr j4ap7vg j16ez2rp selectCursor",
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
                  {
                    value |> stringObjects |> string;
                  },
                |],
              ),
              ReactDOMRe.createDOMElementVariadic(
                "input",
                ~props=ReactDOMRe.domProps(~type_="hidden", ()),
                [||],
              ),
              ReactDOMRe.createDOMElementVariadic(
                "span",
                ~props=
                  ReactDOMRe.domProps(
                    ~style={
                      ReactDOMRe.Style.make(~right="5px", ());
                    },
                    ~className="j2dfb39 j1efw385",
                    (),
                  ),
                [|snd(children)|],
              ),
            |],
          ),
        |],
      ),
      disabled |> disabledObjects ? null : fst(children),
    |],
  );
};