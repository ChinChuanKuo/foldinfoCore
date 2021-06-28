open React;
open Setting;
[%bs.raw {|require('../../../scss/example/Medias/mediaImage.scss')|}];

let widths = width =>
  switch (width) {
  | None => "100%"
  | Some(width) => width
  };

let heights = height =>
  switch (height) {
  | None => "200px"
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
      ~showImage: option(bool)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~width: option(string)=?,
      ~height: option(string)=?,
      ~borderRadius: option(string)=?,
      ~src: option(string)=?,
    ) =>
  showImage |> disabledObjects
    ? ReactDOMRe.createDOMElementVariadic(
        "div",
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
                  ~textAlign="center",
                  ~opacity="0",
                  ~animation="fadeIn 0.8s ease-in forwards",
                  (),
                ),
                style |> styleObjects,
              );
            },
            (),
          ),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "img",
            ~props=
              ReactDOMRe.domProps(
                ~style={
                  ReactDOMRe.Style.make(
                    ~width="auto",
                    ~height="100%",
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
          ),
        |],
      )
    : null;
