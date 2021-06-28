let attributeNames = attributeName =>
  switch (attributeName) {
  | None => ""
  | Some(attributeName) => attributeName
  };

let calcModes = calcMode =>
  switch (calcMode) {
  | None => "linear"
  | Some(calcMode) => calcMode
  };

let fills = fill =>
  switch (fill) {
  | None => "freeze"
  | Some(fill) => fill
  };

let durs = dur =>
  switch (dur) {
  | None => "1s"
  | Some(dur) => dur ++ "s"
  };

let others = other =>
  switch (other) {
  | None => "0"
  | Some(other) => other
  };

[@react.component]
let make =
    (
      ~attributeName: option(string)=?,
      ~calcMode: option(string)=?,
      ~fill: option(string)=?,
      ~dur: option(string)=?,
      ~from: option(string)=?,
      ~to_: option(string)=?,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "animate",
    ~props=
      ReactDOMRe.domProps(
        ~attributeName={
          attributeName |> attributeNames;
        },
        ~calcMode={
          calcMode |> calcModes;
        },
        ~fill={
          fill |> fills;
        },
        ~dur={
          dur |> durs;
        },
        ~from={
          from |> others;
        },
        ~to_={
          to_ |> others;
        },
        (),
      ),
    [||],
  );