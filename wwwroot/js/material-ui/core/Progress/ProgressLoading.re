open Setting;
[%bs.raw {|require('../../scss/Progress/progressLoading.scss')|}];

let boardColors = boardColor =>
  switch (boardColor) {
  | None => "rgba(240,132,171,1)"
  | Some(boardColor) => boardColor
  };

let classes = className => {
  let basic = "jsrd2tl";
  switch (className) {
  | None => basic
  | Some(className) => basic ++ " " ++ className
  };
};

let lineColors = lineColor =>
  switch (lineColor) {
  | None => "rgba(225,0,80,1)"
  | Some(lineColor) => lineColor
  };

let transforms = transform =>
  switch (transform) {
  | None => "scaleX(0)"
  | Some(transform) => "scaleX(" ++ transform ++ ")"
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~boardColor: option(string)=?,
      ~lineColor: option(string)=?,
      ~transform: option(string)=?,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~backgroundColor={
                boardColor |> boardColors;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~role="progressbar",
        ~className="jsrd2tl",
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~width="100%",
                ~transition="transform 0.4s linear",
                ~backgroundColor={
                  lineColor |> lineColors;
                },
                ~transform={
                  transform |> transforms;
                },
                (),
              );
            },
            ~className="j128yqez",
            (),
          ),
        [||],
      ),
    |],
  );