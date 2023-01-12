open Setting;

let colors = color =>
  switch (color) {
  | None => "rgba(255,0,0,1)"
  | Some(color) => color
  };

let strokeWidths = strokeWidth =>
  switch (strokeWidth) {
  | None => "3"
  | Some(strokeWidth) => strokeWidth
  };

let xys = xy =>
  switch (xy) {
  | None => "0"
  | Some(xy) => xy
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~color: option(string)=?,
      ~strokeWidth: option(string)=?,
      ~x1: option(string)=?,
      ~x2: option(string)=?,
      ~y1: option(string)=?,
      ~y2: option(string)=?,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "line",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(~cursor="pointer", ()),
            style |> styleObjects,
          );
        },
        ~stroke={
          color |> colors;
        },
        ~strokeWidth={
          strokeWidth |> strokeWidths;
        },
        ~x1={
          x1 |> xys;
        },
        ~x2={
          x2 |> xys;
        },
        ~y1={
          y1 |> xys;
        },
        ~y2={
          y2 |> xys;
        },
        (),
      ),
    [||],
  );