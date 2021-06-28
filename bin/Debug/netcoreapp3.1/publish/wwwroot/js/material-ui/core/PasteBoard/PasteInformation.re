open ReasonReact;
open Setting;
[%bs.raw {|require('../../scss/PasteBoard/pasteInformation.scss')|}];

let titleSizes = titleSize =>
  switch (titleSize) {
  | None => "20pt"
  | Some(titleSize) => titleSize ++ "pt"
  };

let colors = color =>
  switch (color) {
  | None => "rgba(255,0,0,0.8)"
  | Some(color) => color
  };

let instrSizes = instrSize =>
  switch (instrSize) {
  | None => "13px"
  | Some(instrSize) => instrSize ++ "px"
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~titleSize: option(string)=?,
      ~titleColor: option(string)=?,
      ~tile: option(string)=?,
      ~instrSize: option(string)=?,
      ~instrColor: option(string)=?,
      ~instruction: option(string)=?,
    ) =>
  ReactDOMRe.createElement(
    fragment,
    [|
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.combine(
                ReactDOMRe.Style.make(
                  ~fontSize={
                    titleSize |> titleSizes;
                  },
                  ~color={
                    titleColor |> colors;
                  },
                  (),
                ),
                style |> styleObjects,
              );
            },
            ~className="titlePaste",
            (),
          ),
        [|
          {
            tile |> stringObjects |> string;
          },
        |],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~fontSize={
                  instrSize |> instrSizes;
                },
                ~color={
                  instrColor |> colors;
                },
                (),
              );
            },
            ~className="instructionsPaste",
            (),
          ),
        [|
          {
            instruction |> stringObjects |> string;
          },
        |],
      ),
    |],
  );