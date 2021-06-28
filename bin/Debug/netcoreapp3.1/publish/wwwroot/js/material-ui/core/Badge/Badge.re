open Setting;
[%bs.raw {|require('../../scss/Badge/badge.scss')|}];

let transforms = (vertical, horizontal) =>
  switch (vertical) {
  | None =>
    switch (horizontal) {
    | None => "translate(15px, -15px)"
    | _ => "translate(-15px, -15px)"
    }
  | _ =>
    switch (horizontal) {
    | None => "translate(15px, 15px)"
    | _ => "translate(-15px, 15px)"
    }
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "#3f51b5"
  | Some(backgroundColor) => backgroundColor
  };

let colors = color =>
  switch (color) {
  | None => "rgba(255,255,255,1)"
  | Some(color) => color
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~vertical: option(string)=?,
      ~horizontal: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~color: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "span",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~top="auto",
              ~right="auto",
              ~bottom="auto",
              ~left="auto",
              ~transform={
                transforms(vertical, horizontal);
              },
              ~backgroundColor={
                backgroundColor |> backgroundColors;
              },
              ~color={
                color |> colors;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="j1nwm6bj j177wmhi",
        (),
      ),
    [|children|],
  );