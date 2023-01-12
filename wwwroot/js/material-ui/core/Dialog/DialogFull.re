open Setting;
[%bs.raw {|require('../../scss/Dialog/dialogFull.scss')|}];

let visibilitys = showAnimation => showAnimation ? "" : "hidden";

let opacitys = showAnimation => showAnimation ? "1" : "0";

let outtransitions = showAnimation =>
  showAnimation
    ? "opacity 225ms cubic-bezier(0.4, 0, 0.2, 1) 0ms"
    : "opacity 195ms cubic-bezier(0.4, 0, 0.2, 1) 0ms";

let transforms = showAnimation =>
  showAnimation ? "translate(0px, 0px)" : "translateY(100vh) translateY(0px)";

let transitions = showAnimation =>
  showAnimation ? "transform 225ms cubic-bezier(0, 0, 0.2, 1) 0ms" : "";

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

[@react.component]
let make =
    (
      ~showAnimation: option(bool)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~backgroundColor: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.make(
            ~visibility={
              showAnimation |> disabledObjects |> visibilitys;
            },
            (),
          );
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
                ~opacity={
                  showAnimation |> disabledObjects |> opacitys;
                },
                ~transition={
                  showAnimation |> disabledObjects |> outtransitions;
                },
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
                ~transform={
                  showAnimation |> disabledObjects |> transforms;
                },
                ~transition={
                  showAnimation |> disabledObjects |> transitions;
                },
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
                ~className="j1iocy8x j116tjkxl j1bnredml jnw24a9",
                (),
              ),
            [|children|],
          ),
        |],
      ),
    |],
  );