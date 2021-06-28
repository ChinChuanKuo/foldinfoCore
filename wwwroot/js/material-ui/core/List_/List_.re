open Setting;
[%bs.raw {|require('../../scss/List_/list.scss')|}];

let paddingTopBottoms = topBottom =>
  switch (topBottom) {
  | None => "8px"
  | Some(topBottom) => topBottom ++ "px"
  };

let paddingRightLefts = rightLeft =>
  switch (rightLeft) {
  | None => "0px"
  | Some(rightLeft) => rightLeft ++ "px"
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
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
      ~backgroundColor: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "nav",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~paddingTop={
                top |> paddingTopBottoms;
              },
              ~paddingRight={
                right |> paddingRightLefts;
              },
              ~paddingBottom={
                bottom |> paddingTopBottoms;
              },
              ~paddingLeft={
                left |> paddingRightLefts;
              },
              ~backgroundColor={
                backgroundColor |> backgroundColors;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="jmwifwk j1afduyh",
        (),
      ),
    [|children|],
  );