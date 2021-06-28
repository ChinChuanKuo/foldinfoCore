open ReasonReact;
open Setting;

let otherBackgroundColors = otherBackgroundColor =>
  switch (otherBackgroundColor) {
  | None => "rgba(0,0,0,0.08)"
  | Some(otherBackgroundColor) => otherBackgroundColor
  };

[@react.component]
let make =
    (
      ~enterBackgroundColor: option(string)=?,
      ~downBackgroundColor: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~disablePadding: option(bool)=?,
      ~value: option(string)=?,
    ) =>
  <MenuItem
    enterBackgroundColor={enterBackgroundColor |> otherBackgroundColors}
    downBackgroundColor={downBackgroundColor |> otherBackgroundColors}
    backgroundColor={backgroundColor |> otherBackgroundColors}
    disablePadding={disablePadding |> disabledObjects}>
    {value |> stringObjects |> string}
  </MenuItem>;