open Setting;
[%bs.raw {|require('../../scss/Card/card.scss')|}];

let sizes = size =>
  switch (size) {
  | None => "100%"
  | Some(size) => size
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

let borderRadiuses = borderRadius =>
  switch (borderRadius) {
  | None => "4px"
  | Some(borderRadius) => borderRadius ++ "px"
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~width: option(string)=?,
      ~height: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~topLeft: option(string)=?,
      ~topRight: option(string)=?,
      ~bottomRight: option(string)=?,
      ~bottomLeft: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~width={
                width |> sizes;
              },
              ~minWidth={
                width |> sizes;
              },
              ~maxWidth={
                width |> sizes;
              },
              ~height={
                height |> sizes;
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
        ~className="j1nljlifc j6afj2p jlixhhq",
        (),
      ),
    [|children|],
  );