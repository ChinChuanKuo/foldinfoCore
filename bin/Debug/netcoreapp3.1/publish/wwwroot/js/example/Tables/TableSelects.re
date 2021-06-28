open ReasonReact;
type tupleChildren = (reactElement, reactElement);

[@react.component]
let make =
    (
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children: tupleChildren,
    ) =>
  <>
    <TableHead> <TableRow ?onClick> {fst(children)} </TableRow> </TableHead>
    <TableBody> {snd(children)} </TableBody>
  </>;