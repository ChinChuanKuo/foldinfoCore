open Setting;
[%bs.raw {|require('../../scss/Menu/menu.scss')|}];

let locations = location =>
  switch (location) {
  | None => "auto"
  | Some(location) => location
  };

let otherSizes = otherSize =>
  switch (otherSize) {
  | None => "auto"
  | Some(otherSize) => otherSize ++ "px"
  };

let widths = width =>
  switch (width) {
  | None => "max-content"
  | Some(width) => width
  };

let minWidths = minWidth =>
  switch (minWidth) {
  | None => "100%"
  | Some(minWidth) => minWidth
  };

let transforms = transform =>
  switch (transform) {
  | None => "translate(0, 0)"
  | Some(transform) => transform
  };

let overflows = overflow =>
  switch (overflow) {
  | None => "auto"
  | Some(overflow) => overflow
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

let borderRadiuses = borderRadius =>
  switch (borderRadius) {
  | None => "4px"
  | Some(border) => border ++ "px"
  };

let paddingTopBottoms = topBottom =>
  switch (topBottom) {
  | None => "8px"
  | Some(topBottom) => topBottom ++ "px"
  };

let paddingOthers = other =>
  switch (other) {
  | None => "0px"
  | Some(other) => other ++ "px"
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~transform: option(string)=?,
      ~width: option(string)=?,
      ~minWidth: option(string)=?,
      ~maxHeight: option(string)=?,
      ~height: option(string)=?,
      ~minHeight: option(string)=?,
      ~overflow: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~topLeft: option(string)=?,
      ~topRight: option(string)=?,
      ~bottomRight: option(string)=?,
      ~bottomLeft: option(string)=?,
      ~paddingTop: option(string)=?,
      ~paddingRight: option(string)=?,
      ~paddingBottom: option(string)=?,
      ~paddingLeft: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~position="absolute",
              ~zIndex="1200",
              ~top={
                top |> locations;
              },
              ~right={
                right |> locations;
              },
              ~bottom={
                bottom |> locations;
              },
              ~left={
                left |> locations;
              },
              ~transform={
                transform |> transforms;
              },
              ~width={
                width |> widths;
              },
              ~minWidth={
                minWidth |> minWidths;
              },
              ~maxHeight={
                maxHeight |> otherSizes;
              },
              ~height={
                height |> otherSizes;
              },
              ~minHeight={
                minHeight |> otherSizes;
              },
              ~overflow={
                overflow |> overflows;
              },
              ~backgroundColor={
                backgroundColor |> backgroundColors;
              },
              ~borderTopLeftRadius={
                topLeft |> borderRadiuses;
              },
              ~borderTopRightRadius={
                topRight |> borderRadiuses;
              },
              ~borderBottomRightRadius={
                bottomRight |> borderRadiuses;
              },
              ~borderBottomLeftRadius={
                bottomLeft |> borderRadiuses;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="jt9nf5x",
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "ul",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~paddingTop={
                  paddingTop |> paddingTopBottoms;
                },
                ~paddingRight={
                  paddingRight |> paddingOthers;
                },
                ~paddingBottom={
                  paddingBottom |> paddingTopBottoms;
                },
                ~paddingLeft={
                  paddingLeft |> paddingOthers;
                },
                (),
              );
            },
            ~className="j1afduyh",
            (),
          ),
        [|children|],
      ),
    |],
  );
