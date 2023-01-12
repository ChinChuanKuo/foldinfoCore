open React;
open Setting;
open Math;

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

let mathCos = (size, value) =>
  size +. size *. cos(value *. pi /. 180.0) |> int_of_float |> string_of_int;

let mathSin = (size, value) =>
  size -. size *. sin(value *. pi /. 180.0) |> int_of_float |> string_of_int;

let overCircumference = (from, to_) => to_ -. from >= 180.0 ? "1" : "0";

let colors = color =>
  switch (color) {
  | None => "rgba(255,0,0,1)"
  | Some(color) => color
  };

let enterOpacitys = enterOpacity =>
  switch (enterOpacity) {
  | None => "0.8"
  | Some(enterOpacity) => enterOpacity
  };

let downOpacitys = downOpacity =>
  switch (downOpacity) {
  | None => "0.6"
  | Some(downOpacity) => downOpacity
  };

let strokes = stroke =>
  switch (stroke) {
  | None => "rgba(255,255,255,1)"
  | Some(stroke) => stroke
  };

let enterStrokeWidths = enterStrokeWidth =>
  switch (enterStrokeWidth) {
  | None => "10"
  | Some(enterStrokeWidth) => enterStrokeWidth
  };

let downStrokeWidths = downStrokeWidth =>
  switch (downStrokeWidth) {
  | None => "10"
  | Some(downStrokeWidth) => downStrokeWidth
  };

let strokeWidths = strokeWidth =>
  switch (strokeWidth) {
  | None => "0"
  | Some(strokeWidth) => strokeWidth
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
      ~circles: float,
      ~color: option(string)=?,
      ~enterOpacity: option(string)=?,
      ~downOpacity: option(string)=?,
      ~stroke: option(string)=?,
      ~enterStrokeWidth: option(string)=?,
      ~downStrokeWidth: option(string)=?,
      ~strokeWidth: option(string)=?,
      ~from: float,
      ~to_: float,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  let from = from *. 360.0;
  let to_ = to_ *. 360.0;
  ReactDOMRe.createDOMElementVariadic(
    "g",
    ~props=ReactDOMRe.domProps(),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "path",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.combine(
                ReactDOMRe.Style.make(~cursor="pointer", ()),
                style |> styleObjects,
              );
            },
            ~fill={
              color |> colors;
            },
            ~fillOpacity={
              switch (state.enter, state.down) {
              | (true, false) => enterOpacity |> enterOpacitys
              | (true, true) => downOpacity |> downOpacitys
              | (_, _) => "1"
              };
            },
            ~stroke={
              stroke |> strokes;
            },
            ~strokeWidth={
              switch (state.enter, state.down) {
              | (true, false) => enterStrokeWidth |> enterStrokeWidths
              | (true, true) => downStrokeWidth |> downStrokeWidths
              | (_, _) => strokeWidth |> strokeWidths
              };
            },
            ~d=
              "M "
              ++ {
                circles |> int_of_float |> string_of_int;
              }
              ++ ","
              ++ {
                circles |> int_of_float |> string_of_int;
              }
              ++ " L "
              ++ mathCos(circles, from)
              ++ ","
              ++ mathSin(circles, from)
              ++ " A "
              ++ {
                circles |> int_of_float |> string_of_int;
              }
              ++ ","
              ++ {
                circles |> int_of_float |> string_of_int;
              }
              ++ " 0 "
              ++ overCircumference(from, to_)
              ++ ",0 "
              ++ mathCos(circles, to_)
              ++ ","
              ++ mathSin(circles, to_)
              ++ " Z",
            ~onMouseDown=_ => MouseUpDown(true) |> dispatch,
            ~onMouseUp=_ => MouseUpDown(false) |> dispatch,
            ~onMouseEnter=_ => MouseEnterLeave(true) |> dispatch,
            ~onMouseLeave=_ => MouseEnterLeave(false) |> dispatch,
            ~onClick?,
            (),
          ),
        [|children|],
      ),
    |],
  );
};