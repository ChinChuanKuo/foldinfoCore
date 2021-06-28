open Setting;
[%bs.raw {|require('../../scss/Dialog/dialogActions.scss')|}];

let marginTopBottoms = topBottom =>
  switch (topBottom) {
  | None => "8px"
  | Some(topBottom) => topBottom ++ "px"
  };

let marginRightLefts = rightLeft =>
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
              ~marginTop={
                top |> marginTopBottoms;
              },
              ~marginRight={
                right |> marginRightLefts;
              },
              ~marginBottom={
                bottom |> marginTopBottoms;
              },
              ~marginLeft={
                left |> marginRightLefts;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="jgaml5n",
        (),
      ),
    [|children|],
  );