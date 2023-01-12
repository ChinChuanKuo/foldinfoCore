open Setting;
[%bs.raw {|require('../../scss/Table/tableCell.scss')|}];

let paddingOthers = other =>
  switch (other) {
  | None => "4px"
  | Some(other) => other ++ "px"
  };

let paddingRights = paddingRight =>
  switch (paddingRight) {
  | None => "56px"
  | Some(paddingRight) => paddingRight ++ "px"
  };

let paddingLefts = paddingLeft =>
  switch (paddingLeft) {
  | None => "24px"
  | Some(paddingLeft) => paddingLeft ++ "px"
  };

let colors = color =>
  switch (color) {
  | None => "rgba(0,0,0,0.54)"
  | Some(color) => color
  };

let textAligns = textAlign =>
  switch (textAlign) {
  | None => "left"
  | Some(textAlign) => textAlign
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~color: option(string)=?,
      ~textAlign: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "tr",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~paddingTop={
                top |> paddingOthers;
              },
              ~paddingRight={
                right |> paddingRights;
              },
              ~paddingBottom={
                bottom |> paddingOthers;
              },
              ~paddingLeft={
                left |> paddingLefts;
              },
              ~color={
                color |> colors;
              },
              ~textAlign={
                textAlign |> textAligns;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="jcqtdg2 jhjsvkq",
        (),
      ),
    [|children|],
  );