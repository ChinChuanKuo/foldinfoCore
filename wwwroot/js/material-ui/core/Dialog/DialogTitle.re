open Setting;
[%bs.raw {|require('../../scss/Dialog/dialogTitle.scss')|}];

let paddingOthers = other =>
  switch (other) {
  | None => "24px"
  | Some(other) => other ++ "px"
  };

let paddingBottoms = bottom =>
  switch (bottom) {
  | None => "20px"
  | Some(bottom) => bottom ++ "px"
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

let colors = color =>
  switch (color) {
  | None => "rgba(0,0,0,1)"
  | Some(color) => color
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~color: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.make(
            ~paddingTop={
              top |> paddingOthers;
            },
            ~paddingRight={
              right |> paddingOthers;
            },
            ~paddingBottom={
              bottom |> paddingBottoms;
            },
            ~paddingLeft={
              left |> paddingOthers;
            },
            ~backgroundColor={
              backgroundColor |> backgroundColors;
            },
            (),
          );
        },
        ~className="j16fb98s",
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "h6",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.combine(
                ReactDOMRe.Style.make(
                  ~color={
                    color |> colors;
                  },
                  (),
                ),
                style |> styleObjects,
              );
            },
            ~className="j59oks2 j1ylkzii",
            (),
          ),
        [|children|],
      ),
    |],
  );