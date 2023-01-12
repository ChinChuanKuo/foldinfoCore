open ReasonReact;

[@react.component]
let make =
    (
      ~heads: array(string),
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) =>
  <>
    <TableHead>
      <TableRow ?onClick>
        {heads
         |> Array.map(head => <TableCell> {head |> string} </TableCell>)
         |> array}
      </TableRow>
    </TableHead>
    <TableBody> children </TableBody>
  </>;