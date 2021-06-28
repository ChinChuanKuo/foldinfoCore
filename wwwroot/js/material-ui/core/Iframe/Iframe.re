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

let borderWidths = borderWidth =>
  switch (borderWidth) {
  | None => "0px"
  | Some(borderWidth) => borderWidth ++ "px"
  };

let sizes = size =>
  switch (size) {
  | None => "100%"
  | Some(size) => size
  };

let scrollings = scrolling =>
  switch (scrolling) {
  | None => "auto"
  | Some(scrolling) => scrolling
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~enterBorderWidth: option(string)=?,
      ~downBorderWidth: option(string)=?,
      ~borderWidth: option(string)=?,
      ~width: option(string)=?,
      ~height: option(string)=?,
      ~scrolling: option(string)=?,
      ~src: option(string)=?,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    "iframe",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~borderWidth={
                switch (state.enter, state.down) {
                | (true, false) => enterBorderWidth |> borderWidths
                | (true, true) => downBorderWidth |> borderWidths
                | (_, _) => borderWidth |> borderWidths
                };
              },
              ~width={
                width |> sizes;
              },
              ~height={
                height |> sizes;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~scrolling={
          scrolling |> scrollings;
        },
        ~src={
          src |> stringObjects;
        },
        ~onMouseDown=_ => MouseUpDown(true) |> dispatch,
        ~onMouseUp=_ => MouseUpDown(false) |> dispatch,
        ~onMouseEnter=_ => MouseEnterLeave(true) |> dispatch,
        ~onMouseLeave=_ => MouseEnterLeave(false) |> dispatch,
        (),
      ),
    [||],
  );
};
