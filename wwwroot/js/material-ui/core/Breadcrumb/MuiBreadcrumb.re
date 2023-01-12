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

let listStyles = listStyle =>
  switch (listStyle) {
  | None => "none"
  | Some(listStyle) => listStyle
  };

let colors = color =>
  switch (color) {
  | None => "inherit"
  | Some(color) => color
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~listStyle: option(string)=?,
      ~enterColor: option(string)=?,
      ~downColor: option(string)=?,
      ~color: option(string)=?,
      ~disabled: option(bool)=?,
      ~href: option(string)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    "li",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~listStyle={
                listStyle |> listStyles;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "a",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~margin="0",
                ~display="flex",
                ~cursor="pointer",
                ~textDecoration={
                  switch (state.enter, state.down) {
                  | (true, true)
                  | (true, false) => "underline"
                  | (_, _) => "none"
                  };
                },
                ~color={
                  switch (state.enter, state.down) {
                  | (true, false) => enterColor |> colors
                  | (true, true) => downColor |> colors
                  | (_, _) => color |> colors
                  };
                },
                (),
              );
            },
            ~role="button",
            ~href={
              href |> stringObjects;
            },
            ~disabled={
              disabled |> disabledObjects;
            },
            ~onMouseDown=_ => MouseUpDown(true) |> dispatch,
            ~onMouseUp=_ => MouseUpDown(false) |> dispatch,
            ~onMouseEnter=_ => MouseEnterLeave(true) |> dispatch,
            ~onMouseLeave=_ => MouseEnterLeave(false) |> dispatch,
            (),
          ),
        [|children|],
      ),
    |],
  );
};