open Setting;
[%bs.raw {|require('../../scss/PasteBoard/pasteBoard.scss')|}];

let widths = width =>
  switch (width) {
  | None => "calc(100% - 8px)"
  | Some(width) => width
  };

let heights = height =>
  switch (height) {
  | None => "250px"
  | Some(height) => height ++ "px"
  };

let insideWidths = borderWidth =>
  switch (borderWidth) {
  | None => "calc(100% - 8px)"
  | Some(borderWidth) =>
    "calc(100% - " ++ string_of_int(int_of_string(borderWidth) * 2) ++ "px)"
  };

let insideHeights = (height, borderWidth) =>
  switch (height, borderWidth) {
  | (None, None) => "242px"
  | (None, Some(borderWidth)) =>
    "calc(250px - " ++ string_of_int(int_of_string(borderWidth) * 2) ++ "px)"
  | (Some(height), None) => "calc(" ++ height ++ " - 8px)"
  | (Some(height), Some(borderWidth)) =>
    "calc("
    ++ height
    ++ " - "
    ++ string_of_int(int_of_string(borderWidth) * 2)
    ++ "px)"
  };

let borderRadiuses = borderRadius =>
  switch (borderRadius) {
  | None => "10px"
  | Some(borderRadius) => borderRadius ++ "px"
  };

let borderWidths = borderWidth =>
  switch (borderWidth) {
  | None => "4px"
  | Some(borderWidth) => borderWidth ++ "px"
  };

let borderStyles = borderStyle =>
  switch (borderStyle) {
  | None => "dashed"
  | Some(borderStyle) => borderStyle
  };

let borderColors = borderColor =>
  switch (borderColor) {
  | None => "rgba(255,0,0,0.8)"
  | Some(borderColor) => borderColor
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~width: option(string)=?,
      ~height: option(string)=?,
      ~borderRadius: option(string)=?,
      ~borderWidth: option(string)=?,
      ~borderStyle: option(string)=?,
      ~borderColor: option(string)=?,
      ~onDragOver: option(ReactEvent.Mouse.t => unit)=?,
      ~onDragLeave: option(ReactEvent.Mouse.t => unit)=?,
      ~onDrop: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.make(
            ~width={
              width |> widths;
            },
            ~height={
              height |> heights;
            },
            (),
          );
        },
        ~onDragOver?,
        ~onDragLeave?,
        ~onDrop?,
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~width="100%",
                ~height={
                  height |> heights;
                },
                ~borderRadius={
                  borderRadius |> borderRadiuses;
                },
                (),
              );
            },
            ~className="bgScalePaste",
            (),
          ),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "div",
            ~props=
              ReactDOMRe.domProps(
                ~style={
                  ReactDOMRe.Style.combine(
                    ReactDOMRe.Style.make(
                      ~width={
                        borderWidth |> insideWidths;
                      },
                      ~height={
                        insideHeights(height, borderWidth);
                      },
                      ~borderRadius={
                        borderRadius |> borderRadiuses;
                      },
                      ~borderWidth={
                        borderWidth |> borderWidths;
                      },
                      ~borderStyle={
                        borderStyle |> borderStyles;
                      },
                      ~borderColor={
                        borderColor |> borderColors;
                      },
                      (),
                    ),
                    style |> styleObjects,
                  );
                },
                ~className="innerPaste",
                (),
              ),
            [|children|],
          ),
        |],
      ),
    |],
  );