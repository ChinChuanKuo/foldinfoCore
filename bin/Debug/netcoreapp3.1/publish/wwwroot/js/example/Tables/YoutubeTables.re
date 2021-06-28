open ReasonReact;
open Setting;
open Items;

[@react.component]
let make =
    (
      ~tile: option(string)=?,
      ~datas: array(youtableitem),
      ~showDesc: option(bool)=?,
      ~desc: option(string)=?,
      ~children,
    ) =>
  <GridItem
    cursor="pointer"
    enterBorderRadius="10"
    enterBackgroundColor="rgba(0,0,0,0.1)"
    xs="12">
    <GridItem
      top="0"
      right="0"
      left="0"
      enterBackgroundColor="none"
      backgroundColor="none"
      xs="12">
      <Typography variant="tile">
        {tile |> stringObjects |> string}
      </Typography>
    </GridItem>
    <GridItem
      top="0"
      right="0"
      left="0"
      enterBackgroundColor="none"
      backgroundColor="none"
      xs="12">
      <GridContainer
        backgroundColor="none"
        direction="row"
        justify="start"
        alignItem="center">
        {datas
         |> Array.map(data =>
              <>
                <GridItem
                  top="0"
                  right="0"
                  bottom="0"
                  left="0"
                  enterBackgroundColor="none"
                  backgroundColor="none"
                  xs="no">
                  <IconButton padding="6">
                    <Tooltip
                      location="top" backgroundColor="rgba(255,0,0,0.8)">
                      {data.tooltip |> string}
                    </Tooltip>
                    <IconAction animation="leftRight" src={data.icon} />
                  </IconButton>
                </GridItem>
                <GridItem
                  top="0"
                  right="6"
                  bottom="0"
                  left="0"
                  enterBackgroundColor="none"
                  backgroundColor="none"
                  xs="no">
                  <Typography variant="subtitle2">
                    {data.value |> string}
                  </Typography>
                </GridItem>
              </>
            )
         |> array}
        children
      </GridContainer>
    </GridItem>
    {showDesc |> disabledObjects
       ? <GridItem
           top="0"
           right="0"
           bottom="6"
           left="0"
           enterBackgroundColor="none"
           backgroundColor="none"
           xs="12">
           <Typography variant="subtitle2">
             {desc |> stringObjects |> string}
           </Typography>
         </GridItem>
       : null}
  </GridItem>;