open React;
open Setting;
open Items;
open BarBoard;

[@react.component]
let make =
    (
      ~width: option(string)=?,
      ~height: option(string)=?,
      ~transform: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~latitude: option(bool)=?,
      ~longitude: option(bool)=?,
      ~datas: array(chartitem),
      ~spacing: float,
      ~stroke: option(string)=?,
      ~strokeWidth: option(string)=?,
    ) => {
  let counts =
    float_of_string(width |> widths) /. float_of_int(Js_array.length(datas));
  let proportion: (array(chartitem), int) => float = [%bs.raw
    (datas, height) => {| let max = 0; for (var i = 0; i < datas.length; i++) { if (datas[i][1] > max) {max = datas[i][1];} } return height / max; |}
  ];
  let barWidth = counts -. spacing |> int_of_float |> string_of_int;
  let barHeight = value => {
    value
    *. proportion(datas, int_of_string(height |> heights))
    -. spacing
    |> int_of_float
    |> string_of_int;
  };
  let x = i => {
    int_of_float(counts *. float_of_int(i)) |> string_of_int;
  };
  let y = value => {
    int_of_float(
      float_of_string(height |> heights)
      -. (
        value
        *. proportion(datas, int_of_string(height |> heights))
        -. spacing
      ),
    )
    |> string_of_int;
  };
  <BarBoard
    width={width |> widths}
    height={height |> heights}
    transform={transform |> stringObjects}
    backgroundColor={backgroundColor |> stringObjects}>
    {latitude |> disabledObjects ? <BarLine y2={height |> heights} /> : null}
    {longitude |> disabledObjects
       ? <BarLine
           x2={width |> widths}
           y1={height |> heights}
           y2={height |> heights}
         />
       : null}
    {datas
     |> Array.mapi((i, data) =>
          <>
            <BarPillar
              width=barWidth
              height={data.to_ |> barHeight}
              color={data.color}
              stroke={stroke |> stringObjects}
              strokeWidth={strokeWidth |> stringObjects}
              x={i |> x}
              y={data.to_ |> y}>
              <Animate attributeName="height" to_={data.to_ |> barHeight} />
            </BarPillar>
            <BarText
              x={
                int_of_float(
                  counts *. float_of_int(i) +. (counts -. spacing) /. 2.0,
                )
                |> string_of_int
              }
              y={
                int_of_float(
                  float_of_string(height |> heights)
                  -. data.to_
                  *. proportion(datas, int_of_string(height |> heights))
                  +. spacing
                  /. 2.0,
                )
                |> string_of_int
              }>
              {data.to_ |> int_of_float |> string_of_int |> string}
            </BarText>
          </>
        )
     |> array}
  </BarBoard>;
};