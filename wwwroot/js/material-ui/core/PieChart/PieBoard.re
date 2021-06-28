open Setting;

let sizes = size =>
  switch (size) {
  | None => "300"
  | Some(size) => size
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "transparent"
  | Some(backgroundColor) => backgroundColor
  };

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~size: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~children,
    ) => {
  ReactDOMRe.createDOMElementVariadic(
    "svg",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~width={
                size |> sizes;
              },
              ~height={
                size |> sizes;
              },
              ~backgroundColor={
                backgroundColor |> backgroundColors;
              },
              ~transform="rotate(-90deg)",
              ~borderRadius="50%",
              (),
            ),
            style |> styleObjects,
          );
        },
        (),
      ),
    [|children|],
  );
};