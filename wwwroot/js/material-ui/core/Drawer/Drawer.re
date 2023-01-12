open Setting;
[%bs.raw {|require('../../scss/Drawer/drawer.scss')|}];

let tops = top =>
  switch (top) {
  | None => "64px"
  | Some(top) => top ++ "px"
  };

let rights = right =>
  switch (right) {
  | None => "auto"
  | Some(right) => right ++ "px"
  };

let lefts = left =>
  switch (left) {
  | None => "auto"
  | Some(left) => left ++ "px"
  };

let widths = width =>
  switch (width) {
  | None => "0px"
  | Some(width) => width
  };

let heights = height =>
  switch (height) {
  | None => "100%"
  | Some(height) => "calc(100% - " ++ height ++ "px)"
  };

let zIndexs = zIndex =>
  switch (zIndex) {
  | None => "1200"
  | Some(zIndex) => zIndex
  };

let locations = location =>
  switch (location) {
  | None => "left"
  | Some(location) => location
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

let outClasses = className => {
  let basic = "jss231 jss233 jss232 jss100vh";
  switch (className) {
  | None => basic
  | Some(className) => basic ++ " " ++ className
  };
};

let borderRights = location =>
  switch (location) {
  | "left" => "1px solid rgba(0, 0, 0, 0.12)"
  | _ => ""
  };

let borderLefts = location =>
  switch (location) {
  | "left" => ""
  | _ => "1px solid rgba(0, 0, 0, 0.12)"
  };

let inClasses = className => {
  let basic = "jss237 jss233 jss232 jss109 jss107";
  switch (className) {
  | None => basic
  | Some(className) => basic ++ " " ++ className
  };
};

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~left: option(string)=?,
      ~width: option(string)=?,
      ~height: option(string)=?,
      ~zIndex: option(string)=?,
      ~location: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~className: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~top={
                top |> tops;
              },
              ~right={
                right |> rights;
              },
              ~left={
                left |> lefts;
              },
              ~width={
                width |> widths;
              },
              ~height={
                height |> heights;
              },
              ~zIndex={
                zIndex |> zIndexs;
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
          className |> outClasses;
        },
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.combine(
                ReactDOMRe.Style.make(
                  ~top={
                    top |> tops;
                  },
                  ~right={
                    right |> rights;
                  },
                  ~left={
                    left |> lefts;
                  },
                  ~width={
                    width |> widths;
                  },
                  ~height={
                    height |> heights;
                  },
                  ~borderRight={
                    location |> locations |> borderRights;
                  },
                  ~borderLeft={
                    location |> locations |> borderLefts;
                  },
                  (),
                ),
                style |> styleObjects,
              );
            },
            ~className={
              className |> inClasses;
            },
            (),
          ),
        [|children|],
      ),
    |],
  );