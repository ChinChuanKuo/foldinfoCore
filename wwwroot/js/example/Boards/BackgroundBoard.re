open ReasonReact;
open Setting;
[%bs.raw {|require('../../../scss/example/Boards/backGroundBoard.scss')|}];

let opacitys = showBackground => showBackground ? "1" : "0";

let visibilitys = showBackground => showBackground ? "visible" : "hidden";

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(0,0,0,0.8)"
  | Some(backgroundColor) => backgroundColor
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~showBackground: option(bool)=?,
      ~backgroundColor: option(string)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
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
              ~opacity={
                showBackground |> disabledObjects |> opacitys;
              },
              ~visibility={
                showBackground |> disabledObjects |> visibilitys;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="uploadArea-3QgLtWd",
        ~onClick?,
        (),
      ),
    [|null|],
  );