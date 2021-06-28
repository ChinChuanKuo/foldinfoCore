open React;
open Setting;

let paddingOthers = other =>
  switch (other) {
  | None => "0px"
  | Some(other) => other ++ "px"
  };

let paddingBottoms = paddingBottom =>
  switch (paddingBottom) {
  | None => "12px"
  | Some(paddingBottom) => paddingBottom ++ "px"
  };

[@react.component]
let make =
    (
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~tile: option(string)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.make(
            ~width="100%",
            //~height="100%",
            ~cursor="pointer",
            (),
          );
        },
        ~onClick?,
        (),
      ),
    [|
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
                ~width="100%",
                ~height="100%",
                (),
              );
            },
            (),
          ),
        [|
          createElementVariadic(
            Typography.make,
            Typography.makeProps(
              ~variant="subheading",
              ~noWrap=true,
              ~children={
                tile |> stringObjects |> string;
              },
              (),
            ),
            [||],
          ),
        |],
      ),
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
                ~width="100%",
                ~height="100%",
                (),
              );
            },
            (),
          ),
        [|children|],
      ),
    |],
  );