open Setting;
[%bs.raw {|require('../../scss/Typography/typography.scss')|}];

let components = variant =>
  switch (variant) {
  | "h1" => "h2"
  | "h4" => "h4"
  | "h5" => "h5"
  | "h6"
  | "subtitle1"
  | "subtitle2" => "h6"
  | "body1"
  | "body2" => "p"
  | "button"
  | "caption"
  | "overline" => "span"
  | "h2"
  | "display4"
  | "display3"
  | "display2"
  | "display1"
  | "headline"
  | "tile" => "h2"
  | "h3"
  | "subheading" => "h3"
  | _ => "h2"
  };

let colors = color =>
  switch (color) {
  | None => "rgba(0,0,0,0.87)"
  | Some(color) => color
  };

let fontFamilys = fontFamily =>
  switch (fontFamily) {
  | None => "Roboto, Helvetica, Arial, sans-serif"
  | Some(fontFamily) => fontFamily
  };

let fontSizes = (variant, fontSize) =>
  switch (variant, fontSize) {
  | ("h1", None) => "6rem"
  | ("h3", None) => "3rem"
  | ("h6", None) => "1.25rem"
  | ("subtitle1", None)
  | ("subtitle2", None)
  | ("body2", None)
  | ("button", None) => "0.875rem"
  | ("caption", None)
  | ("overline", None) => "0.75rem"
  | ("display4", None) => "7rem"
  | ("display3", None) => "3.5rem"
  | ("display2", None) => "2.8125rem"
  | ("h4", None)
  | ("display1", None) => "2.125rem"
  | ("h5", None)
  | ("headline", None) => "1.5rem"
  | ("tile", None) => "1.3125rem"
  | ("body1", None)
  | ("subheading", None) => "1rem"
  | ("h2", None)
  | (_, None) => "3.75rem"
  | (_, Some(fontSize)) => fontSize
  };

let fontWeights = (variant, fontWeight) =>
  switch (variant, fontWeight) {
  | ("h6", None)
  | ("tile", None)
  | ("subtitle2", None) => "500"
  | ("h3", None)
  | ("h4", None)
  | ("h5", None)
  | ("subtitle1", None)
  | ("body1", None)
  | ("body2", None)
  | ("button", None)
  | ("caption", None)
  | ("overline", None)
  | ("display3", None)
  | ("display2", None)
  | ("display1", None)
  | ("headline", None)
  | ("subheading", None) => "400"
  | ("h1", None)
  | ("h2", None)
  | ("display4", None)
  | (_, None) => "300"
  | (_, Some(fontWeight)) => fontWeight
  };

let lineHeights = (variant, lineHeight) =>
  switch (variant, lineHeight) {
  | ("h3", None) => "1.04"
  | ("h4", None) => "1.17"
  | ("h5", None) => "1.33"
  | ("h6", None) => "1.6"
  | ("button", None)
  | ("subtitle1", None) => "1.75"
  | ("subtitle2", None) => "1.57"
  | ("body1", None)
  | ("body2", None) => "1.5"
  | ("caption", None) => "1.66"
  | ("overline", None) => "2.66"
  | ("display4", None) => "1.14286em"
  | ("display3", None) => "1.30357em"
  | ("display2", None) => "1.13333em"
  | ("display1", None) => "1.20588em"
  | ("headline", None) => "1.35417em"
  | ("tile", None) => "1.16667em"
  | ("subheading", None) => "1.5em"
  | ("h1", None)
  | ("h2", None)
  | (_, None) => "1"
  | (_, Some(lineHeight)) => lineHeight
  };

let letterSpacings = (variant, letterSpacing) =>
  switch (variant, letterSpacing) {
  | ("h1", None) => "-0.01562em"
  | ("h2", None) => "-0.00833em"
  | ("h3", None)
  | ("h5", None)
  | ("display1", None)
  | ("display2", None)
  | ("headline", None)
  | ("tile", None)
  | ("subheading", None) => "0em"
  | ("h4", None) => "0.00735em"
  | ("h6", None) => "0.0075em"
  | ("body1", None)
  | ("subtitle1", None) => "0.00938em"
  | ("subtitle2", None) => "0.00714em"
  | ("body2", None) => "0.01071em"
  | ("button", None) => "0.02857em"
  | ("caption", None) => "0.03333em"
  | ("overline", None) => "0.08333em"
  | ("display4", None) => "-0.04em"
  | ("display3", None) => "-0.02em"
  | (_, None) => "-0.00833em"
  | (_, Some(letterSpacing)) => letterSpacing
  };

let whiteSpaces = (whiteSpace, noWrap) =>
  switch (whiteSpace, noWrap) {
  | (None, true) => "nowrap"
  | (None, false) => "pre-wrap"
  | (Some(whiteSpace), _) => whiteSpace
  };

[@react.component]
let make =
    (
      ~variant: option(string)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~color: option(string)=?,
      ~fontFamily: option(string)=?,
      ~fontSize: option(string)=?,
      ~fontWeight: option(string)=?,
      ~lineHeight: option(string)=?,
      ~letterSpacing: option(string)=?,
      ~whiteSpace: option(string)=?,
      ~noWrap: option(bool)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    variant |> stringObjects |> components,
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~color={
                color |> colors;
              },
              ~overflow="hidden",
              ~textOverflow="ellipsis",
              ~fontFamily={
                fontFamily |> fontFamilys;
              },
              ~fontSize={
                fontSizes(variant |> stringObjects, fontSize);
              },
              ~fontWeight={
                fontWeights(variant |> stringObjects, fontWeight);
              },
              ~lineHeight={
                lineHeights(variant |> stringObjects, lineHeight);
              },
              ~letterSpacing={
                letterSpacings(variant |> stringObjects, letterSpacing);
              },
              ~whiteSpace={
                noWrap |> disabledObjects |> whiteSpaces(whiteSpace);
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="jss164",
        (),
      ),
    [|children|],
  );
