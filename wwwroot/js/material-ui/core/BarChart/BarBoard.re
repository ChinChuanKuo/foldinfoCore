open Setting;

let widths = width =>
  switch (width) {
  | None => "650"
  | Some(width) => width
  };

let heights = size =>
  switch (size) {
  | None => "500"
  | Some(size) => size
  };

let transforms = transform =>
  switch (transform) {
  | None => "rotate(0deg)"
  | Some(transform) => "rotate(" ++ transform ++ "deg)"
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "transparent"
  | Some(backgroundColor) => backgroundColor
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~width: option(string)=?,
      ~height: option(string)=?,
      ~transform: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "svg",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~width={
                width |> widths;
              },
              ~height={
                height |> heights;
              },
              ~transform={
                transform |> transforms;
              },
              ~backgroundColor={
                backgroundColor |> backgroundColors;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        (),
      ),
    [|children|],
  );