open React;
open Setting;

[@react.component]
let make =
    (
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~showLine: option(bool)=?,
      ~children,
    ) =>
  showLine |> disabledObjects
    ? ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(~position="relative", ());
            },
            ~onClick?,
            (),
          ),
        [|
          createElementVariadic(
            Paper.make,
            Paper.makeProps(
              ~style={
                ReactDOMRe.Style.make(
                  ~borderLeft="3px solid rgba(255,0,0,1)",
                  (),
                );
              },
              ~children,
              (),
            ),
            [||],
          ),
        |],
      )
    : ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=ReactDOMRe.domProps(~onClick?, ()),
        [|
          createElementVariadic(
            Card.make,
            Card.makeProps(
              ~children={
                createElementVariadic(
                  CardHeader.make,
                  CardHeader.makeProps(~bottom="24", ~children, ()),
                  [||],
                );
              },
              (),
            ),
            [||],
          ),
        |],
      );