open ReasonReact;
open Setting;
[%bs.raw {|require('../../scss/ExpansionPanel/expansionSummary.scss')|}];

type tupleChildren = (reactElement, reactElement);

let displays = display =>
  switch (display) {
  | None => "flex"
  | Some(display) => display
  };

let minHeights = showSummary => showSummary ? "64px" : "48px";

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~display: option(string)=?,
      ~showSummary: option(bool)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children: tupleChildren,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~display={
                display |> displays;
              },
              ~minHeight={
                showSummary |> disabledObjects |> minHeights;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~role="button",
        ~className="jr0u89w j25l2u0",
        ~onClick?,
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=ReactDOMRe.domProps(~className="joi1x8j", ()),
        [|fst(children)|],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(~position="absolute", ());
            },
            ~role="button",
            ~className="jr0u89w j1g2vga5l j1k29h72",
            (),
          ),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "span",
            ~props=ReactDOMRe.domProps(~className="jsbmc5e", ()),
            [|snd(children)|],
          ),
          ReactDOMRe.createDOMElementVariadic(
            "span",
            ~props=ReactDOMRe.domProps(~className="jb3bkca", ()),
            [||],
          ),
        |],
      ),
    |],
  );