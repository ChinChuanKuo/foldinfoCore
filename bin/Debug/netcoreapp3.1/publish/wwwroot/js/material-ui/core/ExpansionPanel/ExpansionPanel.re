open ReasonReact;
open Setting;
[%bs.raw {|require('../../scss/ExpansionPanel/expansionPanel.scss')|}];

type tupleChildren = (reactElement, reactElement);

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

let borderRadiuses = borderRadius =>
  switch (borderRadius) {
  | None => "0px"
  | Some(borderRadius) => borderRadius ++ "px"
  };

let margins = showPanel => showPanel ? "16px 0px" : "auto";

let overflows = showPanel => showPanel ? "visible" : "hidden";

let heights = showPanel => showPanel ? "auto" : "0px";

let transitionDurations = showPanel => showPanel ? "168ms" : "208ms";

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~backgroundColor: option(string)=?,
      ~topLeft: option(string)=?,
      ~topRight: option(string)=?,
      ~bottomRight: option(string)=?,
      ~bottomLeft: option(string)=?,
      ~showPanel: option(bool)=?,
      ~children: tupleChildren,
    ) =>
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
              ~borderTopLeftRadius={
                topLeft |> borderRadiuses;
              },
              ~borderTopRightRadius={
                topRight |> borderRadiuses;
              },
              ~borderBottomRightRadius={
                bottomRight |> borderRadiuses;
              },
              ~borderBottomLeftRadius={
                bottomLeft |> borderRadiuses;
              },
              ~margin={
                showPanel |> disabledObjects |> margins;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="j1nljlif ja472eb j1j3r21x",
        (),
      ),
    [|
      fst(children),
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~minHeight="0px",
                ~overflow={
                  showPanel |> disabledObjects |> overflows;
                },
                ~height={
                  showPanel |> disabledObjects |> heights;
                },
                ~transitionDuration={
                  showPanel |> disabledObjects |> transitionDurations;
                },
                (),
              );
            },
            ~className="j1pb73ym",
            (),
          ),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "div",
            ~props=ReactDOMRe.domProps(~className="jzlkjnt", ()),
            [|
              ReactDOMRe.createDOMElementVariadic(
                "div",
                ~props=ReactDOMRe.domProps(~className="j12m3ddi", ()),
                [|
                  ReactDOMRe.createDOMElementVariadic(
                    "div",
                    ~props=ReactDOMRe.domProps(~className="jkmh82r", ()),
                    [|snd(children)|],
                  ),
                |],
              ),
            |],
          ),
        |],
      ),
    |],
  );