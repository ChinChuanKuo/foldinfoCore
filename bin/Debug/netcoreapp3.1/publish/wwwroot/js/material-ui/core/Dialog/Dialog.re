open ReasonReact;
open Setting;
[%bs.raw {|require('../../scss/Dialog/dialog.scss')|}];

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

[@react.component]
let make =
    (
      ~showDialog: option(bool)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~backgroundColor: option(string)=?,
      ~children,
    ) =>
  showDialog |> disabledObjects
    ? ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(~backgroundColor="rgba(0,0,0,0.54)", ());
            },
            ~role="dialog",
            ~className="jupvbsj",
            (),
          ),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "div",
            ~props=
              ReactDOMRe.domProps(
                ~style={
                  ReactDOMRe.Style.make(
                    ~opacity="1",
                    ~transition=
                      "opacity 225ms cubic-bezier(0.4, 0, 0.2, 1) 0ms",
                    (),
                  );
                },
                ~className="j1hwasmh",
                (),
              ),
            [||],
          ),
          ReactDOMRe.createDOMElementVariadic(
            "div",
            ~props=
              ReactDOMRe.domProps(
                ~style={
                  ReactDOMRe.Style.make(
                    ~opacity="1",
                    ~transition=
                      "opacity 225ms cubic-bezier(0.4, 0, 0.2, 1) 0ms",
                    (),
                  );
                },
                ~className="jlbc39s j1olfzzh",
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
                          ~backgroundColor={
                            backgroundColor |> backgroundColors;
                          },
                          (),
                        ),
                        style |> styleObjects,
                      );
                    },
                    ~className="j1iocy8x ji1kkbr j116tjkx j1bnredm jrkcwvt",
                    (),
                  ),
                [|children|],
              ),
            |],
          ),
        |],
      )
    : null;