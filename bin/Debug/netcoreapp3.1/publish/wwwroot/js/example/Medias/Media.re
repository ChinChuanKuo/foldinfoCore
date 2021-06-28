open Setting;

let components = variant =>
  switch (variant) {
  | "audio" => "audio"
  | _ => "video"
  };

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

let types = variant =>
  switch (variant) {
  | "audio" => "audio/mpeg"
  | _ => "video/mp4"
  };

[@react.component]
let make =
    (
      ~variant: option(string)=?,
      ~width: option(string)=?,
      ~height: option(string)=?,
      ~borderRadius: option(string)=?,
      ~controls: option(bool)=?,
      ~src: option(string)=?,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    variant |> stringObjects |> components,
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
        ~controls={
          controls |> disabledObjects;
        },
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "source",
        ~props=
          ReactDOMRe.domProps(
            ~src={
              src |> stringObjects;
            },
            ~type_={
              variant |> stringObjects |> types;
            },
            (),
          ),
        [||],
      ),
    |],
  );
