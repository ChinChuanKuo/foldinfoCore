open Setting;

let borderWidths = (bottom, height) => {
  switch (bottom, height) {
  | (None, None) => "0px 10px 20px 10px"
  | (None, Some(height)) => "0px 10px" ++ " " ++ height ++ "px 10px"
  | (Some(bottom), None) =>
    "0px" ++ " " ++ bottom ++ "px" ++ " 20px" ++ " " ++ bottom ++ "px"
  | (Some(bottom), Some(height)) =>
    "0px"
    ++ " "
    ++ bottom
    ++ "px"
    ++ " "
    ++ height
    ++ "px"
    ++ " "
    ++ bottom
    ++ "px"
  };
};

let borderColors = color =>
  switch (color) {
  | None => "transparent transparent rgba(255,0,0,0.8) transparent"
  | Some(color) =>
    "transparent transparent" ++ " " ++ color ++ " " ++ "transparent"
  };

let borderStyles = style =>
  switch (style) {
  | None => "solid"
  | Some(style) => style
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~bottom: option(string)=?,
      ~height: option(string)=?,
      ~borderColor: option(string)=?,
      ~borderStyle: option(string)=?,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~borderWidth={
                borderWidths(bottom, height);
              },
              ~borderColor={
                borderColor |> borderColors;
              },
              ~borderStyle={
                borderStyle |> borderStyles;
              },
              ~width="0px",
              ~height="0px",
              (),
            ),
            style |> styleObjects,
          );
        },
        (),
      ),
    [||],
  );