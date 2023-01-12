open Setting;
[%bs.raw {|require('../../scss/Table/tableBody.scss')|}];

[@react.component]
let make = (~style: option(ReactDOMRe.style)=?, ~children) =>
  ReactDOMRe.createDOMElementVariadic(
    "tbody",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          style |> styleObjects;
        },
        ~className="j1lm4ike",
        (),
      ),
    [|children|],
  );