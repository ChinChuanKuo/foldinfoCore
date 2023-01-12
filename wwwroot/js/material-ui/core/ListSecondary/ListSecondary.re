open ReasonReact;
open Setting;
[%bs.raw {|require('../../scss/ListSecondary/listSecondary.scss')|}];

type tupleChildren = (reactElement, reactElement);

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(255,255,255,1)"
  | Some(backgroundColor) => backgroundColor
  };

let disablePaddings = disablePadding => disablePadding ? "32px" : "16px";

let colors = color =>
  switch (color) {
  | None => "rgba(0,0,0,1)"
  | Some(color) => color
  };

[@react.component]
let make =
    (
      ~disablePadding: option(bool)=?,
      ~backgroundColor: option(string)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~color: option(string)=?,
      ~children: tupleChildren,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "li",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.make(
            ~backgroundColor={
              backgroundColor |> backgroundColors;
            },
            (),
          );
        },
        ~className="jvpp5ov",
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~paddingLeft={
                  disablePadding |> disabledObjects |> disablePaddings;
                },
                (),
              );
            },
            ~className="j1a697ls j10qoe32 jn23b2ny",
            (),
          ),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "div",
            ~props=ReactDOMRe.domProps(~className="j9018ah", ()),
            [|
              ReactDOMRe.createDOMElementVariadic(
                "span",
                ~props=
                  ReactDOMRe.domProps(
                    ~style={
                      ReactDOMRe.Style.combine(
                        ReactDOMRe.Style.make(
                          ~color={
                            color |> colors;
                          },
                          (),
                        ),
                        style |> styleObjects,
                      );
                    },
                    ~className="j1pzzryc j59oks2",
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
        ~props=ReactDOMRe.domProps(~className="jt151jr", ()),
        [|snd(children)|],
      ),
    |],
  );