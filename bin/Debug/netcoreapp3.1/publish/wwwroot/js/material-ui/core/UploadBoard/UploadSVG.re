open ReasonReact;
[%bs.raw {|require('../../scss/UploadBoard/uploadSVG.scss')|}];

[@react.component]
let make = _ =>
  ReactDOMRe.createElement(
    fragment,
    [|
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=ReactDOMRe.domProps(~className="wrapOne-14G98n", ()),
        [||],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=ReactDOMRe.domProps(~className="wrapThree-1CNQ42", ()),
        [||],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=ReactDOMRe.domProps(~className="wrapTwo-mQGI3R", ()),
        [||],
      ),
    |],
  );