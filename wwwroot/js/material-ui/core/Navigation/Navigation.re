open Setting;
[%bs.raw {|require('../../scss/Navigation/navigation.scss')|}];

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

let heights = height =>
  switch (height) {
  | None => "56px"
  | Some(height) => height ++ "px"
  };

let classes = className => {
  let basic = "j17c6ssp";
  switch (className) {
  | None => basic
  | Some(className) => basic ++ " " ++ className
  };
};

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~backgroundColor: option(string)=?,
      ~height: option(string)=?,
      ~className: option(string)=?,
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
              ~height={
                height |> heights;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className={
          className |> classes;
        },
        (),
      ),
    [|children|],
  );