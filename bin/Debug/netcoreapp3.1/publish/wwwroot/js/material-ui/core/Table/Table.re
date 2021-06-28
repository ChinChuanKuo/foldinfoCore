open Setting;
[%bs.raw {|require('../../scss/Table/table.scss')|}];

let minWidths = minWidth =>
  switch (minWidth) {
  | None => "961px"
  | Some(minWidth) => minWidth ++ "px"
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~minWidth: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "table",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~minWidth={
                minWidth |> minWidths;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="j8ew6kj",
        (),
      ),
    [|children|],
  );