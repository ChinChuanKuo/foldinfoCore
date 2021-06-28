open Storage;
open ObjectFormat;
[@genType]
let barColors = barColor => {
  let checkColor = "barColor" |> Locals.select |> checkObjects;
  switch (barColor, checkColor) {
  | (None, "") => "rgba(0,0,0,1)"
  | (None, _) => checkColor
  | (Some(barColor), _) => barColor
  };
};
[@genType]
let fontColors = fontColor => {
  let checkColor = "fontColor" |> Locals.select |> checkObjects;
  switch (fontColor, checkColor) {
  | (None, "") => "rgba(255,255,255,1)"
  | (None, _) => checkColor
  | (Some(fontColor), _) => fontColor
  };
};