open ReasonReact;
open Setting;
[%bs.raw {|require('../../scss/ListSecondary/listSecondary.scss')|}];

type tupleChildren = (reactElement, reactElement);

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~backgroundColor: option(string)=?,
      ~children: tupleChildren,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "li",
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
        ~className="jvpp5ov",
        (),
      ),
    [|
      fst(children),
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=ReactDOMRe.domProps(~className="jt151jr", ()),
        [|snd(children)|],
      ),
    |],
  );