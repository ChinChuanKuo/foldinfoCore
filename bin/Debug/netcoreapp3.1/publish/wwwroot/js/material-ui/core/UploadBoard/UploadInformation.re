open ReasonReact;

type tupleChildren = (reactElement, reactElement);

[@react.component]
let make = (~children: tupleChildren) =>
  ReactDOMRe.createElement(
    fragment,
    [|
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=ReactDOMRe.domProps(),
        [|fst(children)|],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=ReactDOMRe.domProps(),
        [|snd(children)|],
      ),
    |],
  );