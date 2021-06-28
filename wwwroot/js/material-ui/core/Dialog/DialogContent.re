open Setting;
[%bs.raw {|require('../../scss/Dialog/dialogContent.scss')|}];

let paddingTops = top =>
  switch (top) {
  | None => "0px"
  | Some(top) => top ++ "px"
  };

let paddingOthers = other =>
  switch (other) {
  | None => "24px"
  | Some(other) => other ++ "px"
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
                top |> paddingTops;
              },
              ~paddingRight={
                right |> paddingOthers;
              },
              ~paddingBottom={
                bottom |> paddingOthers;
              },
              ~paddingLeft={
                left |> paddingOthers;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="j1anzh93",
        (),
      ),
    [|children|],
  );