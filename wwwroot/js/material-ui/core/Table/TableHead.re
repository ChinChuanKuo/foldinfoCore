open Setting;
[%bs.raw {|require('../../scss/Table/tableHead.scss')|}];

[@react.component]
let make = (~style: option(ReactDOMRe.style)=?, ~children) =>
  ReactDOMRe.createDOMElementVariadic(
    "thead",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          style |> styleObjects;
        },
        ~className="j1focyla",
        (),
      ),
    [|children|],
  );