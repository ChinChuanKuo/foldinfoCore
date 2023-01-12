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

let sizes = size =>
  switch (size) {
  | None => "300px"
  | Some(size) => size ++ "px"
  };

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
  | None => "rgba(0,0,0,1)"
  | Some(stroke) => stroke
  };

let strokeWidths = strokeWidth =>
  switch (strokeWidth) {
  | None => "2"
  | Some(strokeWidth) => strokeWidth
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~width: option(string)=?,
      ~height: option(string)=?,
      ~color: option(string)=?,
      ~enterOpacity: option(string)=?,
      ~downOpacity: option(string)=?,
      ~stroke: option(string)=?,
      ~strokeWidth: option(string)=?,
      ~x: string,
      ~y: string,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    "g",
    ~props=ReactDOMRe.domProps(),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "rect",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.combine(
                ReactDOMRe.Style.make(
                  ~width={
                    width |> sizes;
                  },
                  ~height={
                    height |> sizes;
                  },
                  ~cursor="pointer",
                  (),
                ),
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
              strokeWidth |> strokeWidths;
            },
            ~x,
            ~y,
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