open Setting;
[%bs.raw {|require('../../scss/Dialog/dialogContentText.scss')|}];

let colors = color =>
  switch (color) {
  | None => "rgba(0,0,0,0.54)"
  | Some(color) => color
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~color: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "p",
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
        ~className="j59oks2 j1ujprzo j1dp773x",
        (),
      ),
    [|children|],
  );