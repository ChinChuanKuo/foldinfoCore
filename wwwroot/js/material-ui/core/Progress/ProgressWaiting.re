open Setting;
[%bs.raw {|require('../../scss/Progress/progressWaiting.scss')|}];

let pointColors = pointColor =>
  switch (pointColor) {
  | None => "radial-gradient(rgba(240,132,171,1) 0%, rgba(240,132,171,1) 16%, transparent 42%)"
  | Some(pointColor) =>
    "radial-gradient("
    ++ pointColor
    ++ " 0%,"
    ++ pointColor
    ++ " 16%,transparent 42%)"
  };

let lineColors = lineColor =>
  switch (lineColor) {
  | None => "rgba(225,0,80,1)"
  | Some(lineColor) => lineColor
  };

let lineTransforms = lineTransform =>
  switch (lineTransform) {
  | None => "scaleX(0)"
  | Some(lineTransform) => "scaleX(" ++ lineTransform ++ ")"
  };

let runColors = runColor =>
  switch (runColor) {
  | None => "rgba(240,132,171,1)"
  | Some(runColor) => runColor
  };

let runTransforms = runTransform =>
  switch (runTransform) {
  | None => "scaleX(0.06)"
  | Some(runTransform) => "scaleX(" ++ runTransform ++ ")"
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~pointColor: option(string)=?,
      ~lineColor: option(string)=?,
      ~lineTransform: option(string)=?,
      ~runColor: option(string)=?,
      ~runTransform: option(string)=?,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(~backgroundColor="transparent", ()),
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
                ~height="100%",
                ~position="absolute",
                ~animation="buffer 3s infinite linear",
                ~backgroundSize="10px 10px",
                ~backgroundPosition="0px -23px",
                ~backgroundImage={
                  pointColor |> pointColors;
                },
                (),
              );
            },
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
                ~width="100%",
                ~zIndex="1",
                ~transition="transform 0.4s linear",
                ~backgroundColor={
                  lineColor |> lineColors;
                },
                ~transform={
                  lineTransform |> lineTransforms;
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
                ~width="100%",
                ~transition="transform 0.4s linear",
                ~backgroundColor={
                  runColor |> runColors;
                },
                ~transform={
                  runTransform |> runTransforms;
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