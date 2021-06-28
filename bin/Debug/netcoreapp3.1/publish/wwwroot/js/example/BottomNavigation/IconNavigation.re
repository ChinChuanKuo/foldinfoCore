open ReasonReact;
open Setting;

[@react.component]
let make =
    (
      ~disabled: option(bool)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~icon: string,
      ~tile: option(string)=?,
    ) => {
  <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
    <IconButton disabled={disabled |> disabledObjects} ?onClick>
      <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
        {tile |> stringObjects |> string}
      </Tooltip>
      <IconAction animation="leftRight" src=icon />
    </IconButton>
  </GridItem>;
};