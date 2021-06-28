open ReasonReact;

type tupleChildren = (reactElement, reactElement);

let widths = width =>
  switch (width) {
  | None => "100%"
  | Some(width) => width
  };

let heights = height =>
  switch (height) {
  | None => "100%"
  | Some(height) => height
  };

let leftRightWidths = leftRightWidth =>
  switch (leftRightWidth) {
  | None => "50%"
  | Some(leftRightWidth) => leftRightWidth ++ "%"
  };

[@react.component]
let make =
    (
      ~outWidth: option(string)=?,
      ~height: option(string)=?,
      ~leftWidth: option(string)=?,
      ~rightWidth: option(string)=?,
      ~width: option(string)=?,
      ~maxWidth: option(string)=?,
      ~flexBasis: option(string)=?,
      ~children: tupleChildren,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.make(
            ~width={
              outWidth |> widths;
            },
            ~height={
              height |> heights;
            },
            (),
          );
        },
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~width={
                  leftWidth |> leftRightWidths;
                },
                ~height="100%",
                ~display="inline-block",
                (),
              );
            },
            (),
          ),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "div",
            ~props=
              ReactDOMRe.domProps(
                ~style={
                  ReactDOMRe.Style.make(~overflow="auto", ~height="100%", ());
                },
                (),
              ),
            [|
              ReactDOMRe.createDOMElementVariadic(
                "div",
                ~props=
                  ReactDOMRe.domProps(
                    ~style={
                      ReactDOMRe.Style.make(
                        ~width={
                          width |> widths;
                        },
                        ~maxWidth={
                          maxWidth |> widths;
                        },
                        ~flexBasis={
                          flexBasis |> widths;
                        },
                        ~margin="0 auto",
                        (),
                      );
                    },
                    (),
                  ),
                [|fst(children)|],
              ),
            |],
          ),
        |],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~width={
                  rightWidth |> leftRightWidths;
                },
                ~height="100%",
                ~display="inline-block",
                (),
              );
            },
            (),
          ),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "div",
            ~props=
              ReactDOMRe.domProps(
                ~style={
                  ReactDOMRe.Style.make(~overflow="auto", ~height="100%", ());
                },
                (),
              ),
            [|
              ReactDOMRe.createDOMElementVariadic(
                "div",
                ~props=
                  ReactDOMRe.domProps(
                    ~style={
                      ReactDOMRe.Style.make(
                        ~width={
                          width |> widths;
                        },
                        ~maxWidth={
                          maxWidth |> widths;
                        },
                        ~flexBasis={
                          flexBasis |> widths;
                        },
                        ~margin="0 auto",
                        (),
                      );
                    },
                    (),
                  ),
                [|snd(children)|],
              ),
            |],
          ),
        |],
      ),
    |],
  );