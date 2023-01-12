open React;
open Setting;
open OutSide;
open Together;
open ReactIntl;
open Icons;

type item = {
  link: string,
  icon: string,
  value: string,
};

[@react.component]
let make =
    (
      ~maxHeight: string,
      ~value: option(string)=?,
      ~beforeLoad: option(bool)=?,
      ~showItem: option(bool)=?,
      ~items: option(array(item))=?,
      ~onChange: option(ReactEvent.Form.t => unit)=?,
      ~onKeyDown: option(ReactEvent.Keyboard.t => unit)=?,
      ~onBlur: option(ReactEvent.Focus.t => unit)=?,
      ~clickShow: option(ReactEvent.Mouse.t => unit)=?,
    ) =>
  <>
    <div
      style={ReactDOMRe.Style.combine(
        menuOutSide,
        ReactDOMRe.Style.make(
          ~top="0px",
          ~left="0px",
          ~width="320px",
          ~maxWidth="320px",
          ~minWidth="320px",
          ~maxHeight,
          ~borderRadius="10px",
          (),
        ),
      )}>
      <Menu
        topLeft="12"
        topRight="12"
        bottomRight="12"
        bottomLeft="12"
        top="5"
        right="0"
        left="0">
        <GridContainer direction="column" justify="center" alignItem="stretch">
          <GridItem
            top="0"
            bottom="0"
            left="8"
            enterBackgroundColor="transparent"
            backgroundColor="transparent"
            xs="auto">
            <GridContainer direction="row" justify="start" alignItem="center">
              <GridItem
                top="0"
                right="4"
                bottom="0"
                enterBackgroundColor="transparent"
                backgroundColor="transparent"
                xs="no">
                <IconButton padding="6" onClick=?clickShow>
                  <IconAction animation="circle" src=arrowBackIosBlack />
                </IconButton>
              </GridItem>
              <GridItem
                top="0"
                right="0"
                bottom="0"
                left="0"
                enterBackgroundColor="transparent"
                backgroundColor="transparent"
                xs="auto">
                <TextFieldOutline
                  top="0"
                  right="0"
                  bottom="0"
                  left="0"
                  borderTop="12"
                  borderBottom="12"
                  borderRadius="20"
                  value={value |> stringObjects}
                  ?onChange
                  ?onKeyDown
                  ?onBlur>
                  null
                </TextFieldOutline>
              </GridItem>
            </GridContainer>
          </GridItem>
          <GridItem
            right="0"
            bottom="0"
            left="16"
            enterBackgroundColor="transparent"
            backgroundColor="transparent"
            xs="auto">
            <GridContainer
              direction="row" justify="between" alignItem="center">
              <GridItem
                top="0"
                right="0"
                bottom="0"
                left="0"
                enterBackgroundColor="transparent"
                backgroundColor="transparent"
                xs="no">
                <Typography variant="subheading" fontSize="1.2rem">
                  <FormattedMessage
                    id="Face.history"
                    defaultMessage="History"
                  />
                </Typography>
              </GridItem>
              <GridItem
                top="0"
                right="0"
                bottom="0"
                left="0"
                enterBackgroundColor="transparent"
                backgroundColor="transparent"
                xs="no">
                <Button
                  enterBackgroundColor="rgba(0,0,0,0.06)"
                  downBackgroundColor="rgba(0,0,0,0.08)"
                  backgroundColor="rgba(255,255,255,1)"
                  color="rgba(255,0,0,0.8)">
                  <FormattedMessage id="Action.edit" defaultMessage="Edit" />
                </Button>
              </GridItem>
            </GridContainer>
          </GridItem>
          {switch (beforeLoad |> disabledObjects, showItem |> disabledObjects) {
           | (true, _) =>
             <GridItem xs="auto">
               <GridContainer
                 direction="row" justify="center" alignItem="center">
                 <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                   <ProgressCircular size="80" color="rgba(0,0,0,0.08)" />
                 </GridItem>
               </GridContainer>
             </GridItem>
           | (false, true) =>
             <GridItem
               style={ReactDOMRe.Style.combine(
                 divScrollbar,
                 ReactDOMRe.Style.make(
                   ~maxHeight="calc(" ++ maxHeight ++ " - 120px)",
                   (),
                 ),
               )}
               top="0"
               right="0"
               bottom="0"
               left="0"
               xs="no">
               <GridContainer
                 direction="column" justify="center" alignItem="stretch">
                 {items
                  |> arrayObjects
                  |> Array.map(item =>
                       <GridItem
                         top="0"
                         right="0"
                         bottom="0"
                         left="0"
                         enterBackgroundColor="transparent"
                         backgroundColor="transparent"
                         xs="auto">
                         <MenuItem
                           top="8"
                           right="15"
                           bottom="8"
                           left="6"
                           enterBackgroundColor="rgba(0,0,0,0.06)"
                           downBackgroundColor="rgba(0,0,0,0.08)"
                           topLeft="12"
                           topRight="12"
                           bottomRight="12"
                           bottomLeft="12"
                           onClick={_ => item.link |> ReasonReactRouter.push}>
                           <GridContainer
                             backgroundColor="transparent"
                             direction="row"
                             justify="between"
                             alignItem="center">
                             <GridItem
                               top="0"
                               right="0"
                               bottom="0"
                               left="0"
                               enterBackgroundColor="transparent"
                               backgroundColor="transparent"
                               xs="no">
                               <IconButton padding="6">
                                 <IconAction
                                   width="32"
                                   height="32"
                                   animation="circle"
                                   src={item.icon}
                                 />
                               </IconButton>
                             </GridItem>
                             <GridItem
                               top="0"
                               right="6"
                               bottom="0"
                               left="6"
                               enterBackgroundColor="transparent"
                               backgroundColor="transparent"
                               xs="auto">
                               <Typography variant="subheading">
                                 {item.value |> string}
                               </Typography>
                             </GridItem>
                             <GridItem
                               top="0"
                               right="0"
                               bottom="0"
                               left="0"
                               enterBackgroundColor="transparent"
                               backgroundColor="transparent"
                               xs="no">
                               <IconButton padding="4">
                                 <IconAction
                                   animation="leftRight"
                                   src=clearBlack
                                 />
                               </IconButton>
                             </GridItem>
                           </GridContainer>
                         </MenuItem>
                       </GridItem>
                     )
                  |> array}
               </GridContainer>
             </GridItem>
           | (false, false) =>
             <GridItem top="18" right="18" bottom="18" left="32" xs="auto">
               <Typography variant="tile" noWrap=true>
                 {"undefined this database" |> string}
               </Typography>
             </GridItem>
           }}
        </GridContainer>
      </Menu>
    </div>
    <BackgroundBoard
      showBackground=true
      backgroundColor="transparent"
      onClick=?clickShow
    />
  </>;
