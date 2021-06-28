open ReasonReact;
type item = {
  tile: string,
  subhead: string,
  fstother: string,
  sndother: string,
  trdother: string,
};

[@react.component]
let make = (~items: array(item), ~onClick: ReactEvent.Mouse.t => unit) => {
  items
  |> Array.map(item =>
       <TableRow onClick>
         <TableCell> {item.tile |> string} </TableCell>
         <TableCell> {item.subhead |> string} </TableCell>
         <TableCell> {item.fstother |> string} </TableCell>
         <TableCell> {item.sndother |> string} </TableCell>
         <TableCell> {item.trdother |> string} </TableCell>
       </TableRow>
     )
  |> array;
};