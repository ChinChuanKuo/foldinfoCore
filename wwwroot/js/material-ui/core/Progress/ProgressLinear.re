open Setting;
[%bs.raw {|require('../../scss/Progress/progressLinear.scss')|}];

let boardColors = boardColor =>
  switch (boardColor) {
  | None => "rgba(240,132,171,1)"
  | Some(boardColor) => boardColor
  };

let lineColors = lineColor =>
  switch (lineColor) {
  | None => "rgba(225,0,80,1)"
  | Some(lineColor) => lineColor
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~boardColor: option(string)=?,
      ~lineColor: option(string)=?,
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
                ~width="auto",
                ~animation=
                  "mui-indeterminate1 2.1s cubic-bezier(0.65, 0.815, 0.735, 0.395) infinite",
                ~animationName="j1gddc18",
                ~transition="transform 0.2s linear",
                ~backgroundColor={
                  lineColor |> lineColors;
                },
                (),
              );
            },
            ~className="j128yqez",
            (),
          ),
        [||],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~width="auto",
                ~animation=
                  "mui-indeterminate2 2.1s cubic-bezier(0.165, 0.84, 0.44, 1) infinite",
                ~animationName="j1yrkkuf",
                ~animationDelay="1.15s",
                ~transition="transform 0.2s linear",
                ~backgroundColor={
                  lineColor |> lineColors;
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