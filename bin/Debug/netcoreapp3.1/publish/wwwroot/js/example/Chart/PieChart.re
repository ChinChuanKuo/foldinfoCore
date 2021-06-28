open React;
open Setting;
open Items;
open PieBoard;

[@react.component]
let make =
    (
      ~size: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~datas: array(chartitem),
      ~enterOpacity: option(string)=?,
      ~downOpacity: option(string)=?,
      ~stroke: option(string)=?,
      ~enterStrokeWidth: option(string)=?,
      ~downStrokeWidth: option(string)=?,
      ~strokeWidth: option(string)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
    ) => {
  let circles = float_of_string(size |> sizes) /. 2.0;
  let total: array(chartitem) => float = [%bs.raw
    datas => {| let total = 0; for (var i = 0; i < datas.length; i++) {total += datas[i][1];} return total; |}
  ];
  let from: (array(chartitem), int) => float = [%bs.raw
    (datas, index) => {| if (index == 0) {return 0.0;} let before = 0; for (var i = 0; i < index; i++) {before += datas[i][1];} return before; |}
  ];
  let to_: (array(chartitem), int, float) => float = [%bs.raw
    (datas, index, to_) => {| if (index == 0) {return to_;} let before = 0; for (var i = 0; i <= index; i++) {before += datas[i][1];} return before; |}
  ];
  <PieBoard
    size={size |> sizes} backgroundColor={backgroundColor |> stringObjects}>
    {datas
     |> Array.mapi((i, data) =>
          <PiePath
            circles
            color={data.color}
            enterOpacity={enterOpacity |> stringObjects}
            downOpacity={downOpacity |> stringObjects}
            stroke={stroke |> stringObjects}
            enterStrokeWidth={enterStrokeWidth |> stringObjects}
            downStrokeWidth={downStrokeWidth |> stringObjects}
            strokeWidth={strokeWidth |> stringObjects}
            from={from(datas, i) /. total(datas)}
            to_={to_(datas, i, data.to_) /. total(datas)}
            ?onClick>
            <Animate attributeName="opacity" to_="1" />
          </PiePath>
        )
     |> array}
  </PieBoard>;
};