open Setting;

let paddings = padding =>
  switch (padding) {
  | None => "16px"
  | Some(padding) => padding ++ "px"
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~paddingTop={
                top |> paddings;
              },
              ~paddingRight={
                right |> paddings;
              },
              ~paddingBottom={
                bottom |> paddings;
              },
              ~paddingLeft={
                left |> paddings;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        (),
      ),
    [|children|],
  );