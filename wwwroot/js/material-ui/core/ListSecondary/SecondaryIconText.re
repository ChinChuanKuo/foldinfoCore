open ReasonReact;
open Setting;
[%bs.raw {|require('../../scss/ListSecondary/listSecondary.scss')|}];

type tupleChildren = (reactElement, reactElement);

let disablePaddings = disablePadding => disablePadding ? "32px" : "16px";

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "#bdbdbd"
  | Some(backgroundColor) => backgroundColor
  };

[@react.component]
let make =
    (
      ~disablePadding: option(bool)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~backgroundColor: option(string)=?,
      ~children: tupleChildren,
    ) =>
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
            ~className="ja16k5a j4f2n9i",
            (),
          ),
        [|fst(children)|],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=ReactDOMRe.domProps(~className="j9018ah", ()),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "span",
            ~props=ReactDOMRe.domProps(~className="j1pzzryc j59oks2", ()),
            [|snd(children)|],
          ),
        |],
      ),
    |],
  );