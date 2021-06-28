open Setting;
[%bs.raw {|require('../../scss/Divider/divider.scss')|}];

let margins = margin =>
  switch (margin) {
  | None => "0px"
  | Some(margin) => margin ++ "px"
  };

let heights = height =>
  switch (height) {
  | None => "1px"
  | Some(height) => height ++ "px"
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(0,0,0,0.12)"
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
      ~height: option(string)=?,
      ~backgroundColor: option(string)=?,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "hr",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~marginTop={
                top |> margins;
              },
              ~marginRight={
                right |> margins;
              },
              ~marginBottom={
                bottom |> margins;
              },
              ~marginLeft={
                left |> margins;
              },
              ~height={
                height |> heights;
              },
              ~backgroundColor={
                backgroundColor |> backgroundColors;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="j1c9j684",
        (),
      ),
    [||],
  );