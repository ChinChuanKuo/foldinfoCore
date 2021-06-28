open Setting;

let widths = width =>
  switch (width) {
  | None => "100%"
  | Some(width) => width
  };

let heights = height =>
  switch (height) {
  | None => "auto"
  | Some(height) => height
  };

let borderRadiuses = borderRadius =>
  switch (borderRadius) {
  | None => "0px"
  | Some("circle") => "50%"
  | Some(borderRadius) => borderRadius ++ "px"
  };

[@react.component]
let make =
    (
      ~width: option(string)=?,
      ~height: option(string)=?,
      ~borderRadius: option(string)=?,
      ~src: option(string)=?,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "img",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.make(
            ~width={
              width |> widths;
            },
            ~height={
              height |> heights;
            },
            ~borderRadius={
              borderRadius |> borderRadiuses;
            },
            ~cursor="pointer",
            (),
          );
        },
        ~src={
          src |> stringObjects;
        },
        (),
      ),
    [||],
  );
