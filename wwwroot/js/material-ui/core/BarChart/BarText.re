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

let fontSizes = fontSize =>
  switch (fontSize) {
  | None => "14"
  | Some(fontSize) => fontSize
  };

let textAnchors = textAnchor =>
  switch (textAnchor) {
  | None => "middle"
  | Some(textAnchor) => textAnchor
  };

let otherColors = otherColor =>
  switch (otherColor) {
  | None => "rgba(255,0,0,0.8)"
  | Some(otherColor) => otherColor
  };

let colors = color =>
  switch (color) {
  | None => "rgba(255,0,0,1)"
  | Some(color) => color
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~fontSize: option(string)=?,
      ~textAnchor: option(string)=?,
      ~color: option(string)=?,
      ~x: string,
      ~y: string,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "text",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(~cursor="pointer", ()),
            style |> styleObjects,
          );
        },
        ~fontSize={
          fontSize |> fontSizes;
        },
        ~textAnchor={
          textAnchor |> textAnchors;
        },
        ~fill={
          color |> colors;
        },
        ~x,
        ~y,
        (),
      ),
    [|children|],
  );