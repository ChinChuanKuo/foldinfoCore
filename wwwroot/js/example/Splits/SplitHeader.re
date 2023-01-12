open React;
open Setting;

[@react.component]
let make = (~tile: option(string)=?, ~descShow: option(bool)=?, ~description: option(string)=?) =>
  <GridContainer direction="column" justify="center" alignItem="stretch">
    <GridItem xs="auto">
      <Typography variant="tile" noWrap=true> {tile |> stringObjects |> string} </Typography>
    </GridItem>
    {descShow |> disabledObjects
       ? <GridItem xs="auto">
           <Typography variant="tile" noWrap=true>
             {description |> stringObjects |> string}
           </Typography>
         </GridItem>
       : null}
    <GridItem xs="auto"> <Divider /> </GridItem>
  </GridContainer>;