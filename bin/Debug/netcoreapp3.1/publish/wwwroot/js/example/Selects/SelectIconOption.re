open ReasonReact;
open Setting;

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~disablePadding: option(bool)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~icon: string,
      ~value: option(string)=?,
    ) =>
  <MenuIcon
    style={style |> styleObjects}
    disablePadding={disablePadding |> disabledObjects}
    ?onClick>
    ...(<IconGeneral src=icon />, value |> stringObjects |> string)
  </MenuIcon>;