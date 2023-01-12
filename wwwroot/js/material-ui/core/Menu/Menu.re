open Setting;
[%bs.raw {|require('../../scss/Menu/menu.scss')|}];

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
      ~backgroundColor: option(string)=?,
      ~topLeft: option(string)=?,
      ~topRight: option(string)=?,
      ~bottomRight: option(string)=?,
      ~bottomLeft: option(string)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
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
                  top |> paddingTopBottoms;
                },
                ~paddingRight={
                  right |> paddingOthers;
                },
                ~paddingBottom={
                  bottom |> paddingTopBottoms;
                },
                ~paddingLeft={
                  left |> paddingOthers;
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