open Setting;
[%bs.raw {|require('../../scss/Tabs/tabs.scss')|}];

let maxWidths = maxWidth =>
  switch (maxWidth) {
  | None => "100%"
  | Some(maxWidth) => maxWidth ++ "px"
  };

let displays = display =>
  switch (display) {
  | None => "inline-block"
  | Some(display) => display
  };

let justifys = justify =>
  switch (justify) {
  | Some("center") => " MuiTabs-centered"
  | _ => ""
  };

let indexLefts: (string, int, int) => string = [%bs.raw
  (id, index, short) => {| return document.getElementById(id+index) == null ? 0 : index * document.getElementById(id+index).offsetWidth + short / 2; |}
];

let indexMaxWidths: (string, int, int) => string = [%bs.raw
  (id, index, short) => {| return document.getElementById(id+index) == null ? 0 : document.getElementById(id+index).offsetWidth - short; |}
];

let heights = height =>
  switch (height) {
  | None => "2px"
  | Some(height) => height ++ "px"
  };

let backgroundColors = linearColor =>
  switch (linearColor) {
  | None => "rgba(220,0,78,1)"
  | Some(linearColor) => linearColor
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~maxWidth: option(string)=?,
      ~display: option(string)=?,
      ~justify: option(string)=?,
      ~id: string,
      ~index: option(int)=?,
      ~short: option(int)=?,
      ~height: option(string)=?,
      ~color: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.make(
            ~maxWidth={
              maxWidth |> maxWidths;
            },
            ~margin="0 auto",
            (),
          );
        },
        ~className="MuiTabs-root",
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~display={
                  display |> displays;
                },
                (),
              );
            },
            ~className="MuiTabs-scroller MuiTabs-fixed",
            (),
          ),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "div",
            ~props=
              ReactDOMRe.domProps(
                ~role="tablist",
                ~className="MuiTabs-flexContainer" ++ (justify |> justifys),
                (),
              ),
            [|children|],
          ),
          ReactDOMRe.createDOMElementVariadic(
            "span",
            ~props=
              ReactDOMRe.domProps(
                ~style={
                  ReactDOMRe.Style.combine(
                    ReactDOMRe.Style.make(
                      ~left={
                        indexLefts(
                          id,
                          index |> intObjects,
                          short |> intObjects,
                        );
                      },
                      ~maxWidth={
                        indexMaxWidths(
                          id,
                          index |> intObjects,
                          short |> intObjects,
                        );
                      },
                      ~height={
                        height |> heights;
                      },
                      ~backgroundColor={
                        color |> backgroundColors;
                      },
                      (),
                    ),
                    style |> styleObjects,
                  );
                },
                ~className="jss296",
                (),
              ),
            [||],
          ),
        |],
      ),
    |],
  );
