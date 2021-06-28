open React;
open Setting;

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

let fills = fill =>
  switch (fill) {
  | None => "transparent"
  | Some(fill) => fill
  };

let colors = color =>
  switch (color) {
  | None => "rgba(255,0,0,0.8)"
  | Some(color) => color
  };

let strokeWidths = size =>
  switch (size) {
  | None => "20"
  | Some(size) => size
  };

let calcModes = calcMode =>
  switch (calcMode) {
  | None => "linear"
  | Some(calcMode) => calcMode
  };

let durs = dur =>
  switch (dur) {
  | None => "1s"
  | Some(dur) => dur ++ "s"
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~fill: option(string)=?,
      ~enterColor: option(string)=?,
      ~downColor: option(string)=?,
      ~color: option(string)=?,
      ~size: option(string)=?,
      ~from: string,
      ~to_: string,
      ~calcMode: option(string)=?,
      ~dur: option(string)=?,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    "circle",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~fill={
                fill |> fills;
              },
              ~stroke={
                switch (state.enter, state.down) {
                | (true, false) => enterColor |> colors
                | (true, true) => downColor |> colors
                | (_, _) => color |> colors
                };
              },
              ~strokeWidth={
                size |> strokeWidths;
              },
              ~strokeDasharray="0 100",
              ~strokeDashoffset={
                "-" ++ from;
              },
              ~cursor="pointer",
              (),
            ),
            style |> styleObjects,
          );
        },
        ~r="15.92",
        ~cx="16",
        ~cy="16",
        ~onMouseDown=_ => MouseUpDown(true) |> dispatch,
        ~onMouseUp=_ => MouseUpDown(false) |> dispatch,
        ~onMouseEnter=_ => MouseEnterLeave(true) |> dispatch,
        ~onMouseLeave=_ => MouseEnterLeave(false) |> dispatch,
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "animate",
        ~props=
          ReactDOMRe.domProps(
            ~attributeName="stroke-dasharray",
            ~calcMode={
              calcMode |> calcModes;
            },
            ~fill="freeze",
            ~from="0",
            ~dur={
              dur |> durs;
            },
            ~to_,
            (),
          ),
        [||],
      ),
    |],
  );
};