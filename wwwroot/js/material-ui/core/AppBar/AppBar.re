open Setting;
[%bs.raw {|require('../../scss/AppBar/appBar.scss')|}];

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "#3f51b5"
  | Some(backgroundColor) => backgroundColor
  };

let positions = position =>
  switch (position) {
  | None => "fixed"
  | Some(position) => position
  };

let zIndexs = zIndex =>
  switch (zIndex) {
  | None => "1200"
  | Some(zIndex) => zIndex
  };

let minHeights = minHeight =>
  switch (minHeight) {
  | None => "64px"
  | Some(minHeight) => minHeight ++ "px"
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~backgroundColor: option(string)=?,
      ~position: option(string)=?,
      ~zIndex: option(string)=?,
      ~minHeight: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "header",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~backgroundColor={
                backgroundColor |> backgroundColors;
              },
              ~position={
                position |> positions;
              },
              ~zIndex={
                zIndex |> zIndexs;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="jss99 jss98 jss113",
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~minHeight={
                  minHeight |> minHeights;
                },
                (),
              );
            },
            ~className="jss134 jss136",
            (),
          ),
        [|children|],
      ),
    |],
  );