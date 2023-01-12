open Setting;
[%bs.raw {|require('../../scss/Card/cardBottom.scss')|}];

let paddingTopBottoms = topBottom =>
  switch (topBottom) {
  | None => "8px"
  | Some(topBottom) => topBottom ++ "px"
  };

let paddingRightLefts = rightLeft =>
  switch (rightLeft) {
  | None => "4px"
  | Some(rightLeft) => rightLeft ++ "px"
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
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
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="j1h57870",
        (),
      ),
    [|children|],
  );