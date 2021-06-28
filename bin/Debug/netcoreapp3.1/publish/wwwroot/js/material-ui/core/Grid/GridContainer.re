open Setting;
[%bs.raw {|require('../../scss/Grid/gridContainer.scss')|}];

let margins = margin =>
  switch (margin) {
  | None => "0px"
  | Some(margin) => margin ++ "px"
  };

let displays = display =>
  switch (display) {
  | None => "flex"
  | Some(display) => display
  };

let widths = width =>
  switch (width) {
  | None => "100%"
  | Some(width) => "calc(100% - " ++ width ++ " px)"
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

let directions = direction =>
  switch (direction) {
  | "column" => "jmxzedj"
  | "rowReverse" => "j1qb8kah"
  | "columnReverse" => "jlecjg4"
  | _ => ""
  };

let justifys = justify =>
  switch (justify) {
  | "start" => "jrz2a3nstart"
  | "center" => "jrz2a3n"
  | "end" => "j1dgalzs"
  | "between" => "jf14myd"
  | "around" => "j1qyqqgx"
  | "evenly" => "j1jj17ug"
  | _ => "jrz2a3nstart"
  };

let alignItems = alignItem =>
  switch (alignItem) {
  | "start" => "j1if8dd6"
  | "center" => "jwwules"
  | "end" => "j239l07"
  | "baseline" => "j4d0665"
  | _ => ""
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~display: option(string)=?,
      ~width: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~direction: option(string)=?,
      ~justify: option(string)=?,
      ~alignItem: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~marginTop={
                top |> margins;
              },
              ~marginRight={
                right |> margins;
              },
              ~marginBottom={
                bottom |> margins;
              },
              ~marginLeft={
                left |> margins;
              },
              ~display={
                display |> displays;
              },
              ~width={
                width |> widths;
              },
              ~backgroundColor={
                backgroundColor |> backgroundColors;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className={
          "jasti5v j1ptnqky "
          ++ (direction |> stringObjects |> directions)
          ++ " "
          ++ (justify |> stringObjects |> justifys)
          ++ " "
          ++ (alignItem |> stringObjects |> alignItems);
        },
        (),
      ),
    [|children|],
  );