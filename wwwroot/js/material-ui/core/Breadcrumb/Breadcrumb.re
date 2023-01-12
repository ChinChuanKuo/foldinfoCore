open Setting;

let margins = margin =>
  switch (margin) {
  | None => "0px"
  | Some(margin) => margin ++ "px"
  };

let colors = color =>
  switch (color) {
  | None => "rgba(255,255,255,0.7)"
  | Some(color) => color
  };

let fontSizes = fontSize =>
  switch (fontSize) {
  | None => "1rem"
  | Some(fontSize) => fontSize
  };

let fontFamilys = fontFamily =>
  switch (fontFamily) {
  | None => "'Roboto', 'Helvetica', 'Arial', sans-serif"
  | Some(fontFamily) => fontFamily
  };

let fontWeights = fontWeight =>
  switch (fontWeight) {
  | None => "400"
  | Some(fontWeight) => fontWeight
  };

let lineHeights = lineHeight =>
  switch (lineHeight) {
  | None => "1.5"
  | Some(lineHeight) => lineHeight
  };

let letterSpacings = letterSpacing =>
  switch (letterSpacing) {
  | None => "0.00938em"
  | Some(letterSpacing) => letterSpacing
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
      ~fontSize: option(string)=?,
      ~fontFamily: option(string)=?,
      ~fontWeight: option(string)=?,
      ~lineHeight: option(string)=?,
      ~letterSpacing: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "nav",
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
              ~color={
                color |> colors;
              },
              ~fontSize={
                fontSize |> fontSizes;
              },
              ~fontFamily={
                fontFamily |> fontFamilys;
              },
              ~fontWeight={
                fontWeight |> fontWeights;
              },
              ~lineHeight={
                lineHeight |> lineHeights;
              },
              ~letterSpacing={
                letterSpacing |> letterSpacings;
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
        "ol",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~margin="0",
                ~display="flex",
                ~padding="0",
                ~flexWrap="wrap",
                ~alignItems="center",
                (),
              );
            },
            (),
          ),
        [|children|],
      ),
    |],
  );