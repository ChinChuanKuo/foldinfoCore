open ReasonReact;
open Setting;

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~disablePadding: option(bool)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~value: option(string)=?,
    ) =>
  <MenuItem
    style={style |> styleObjects}
    disablePadding={disablePadding |> disabledObjects}
    ?onClick>
    {value |> stringObjects |> string}
  </MenuItem>;