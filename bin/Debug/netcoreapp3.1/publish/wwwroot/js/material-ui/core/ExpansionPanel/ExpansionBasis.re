open Setting;
[%bs.raw {|require('../../scss/ExpansionPanel/expansionBasis.scss')|}];

[@react.component]
let make = (~style: option(ReactDOMRe.style)=?, ~children) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          style |> styleObjects;
        },
        ~className="jv3mgrj",
        (),
      ),
    [|children|],
  );