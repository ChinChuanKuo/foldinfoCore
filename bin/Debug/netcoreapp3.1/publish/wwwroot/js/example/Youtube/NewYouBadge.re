open React;
open Setting;
open OutSide;
open ReactIntl;
open Path;
open Icons;

type item = {
  link: string,
  name: string,
  value: string,
  datetime: string,
};

[@react.component]
let make =
    (
      ~maxHeight: string,
      ~beforeLoad: option(bool)=?,
      ~showItem: option(bool)=?,
      ~items: option(array(item))=?,
      ~clickShow: option(ReactEvent.Mouse.t => unit)=?,
    ) =>
  <>
    <div
      style={ReactDOMRe.Style.combine(
        menuOutSide,
        ReactDOMRe.Style.make(
          ~right="80px",
          ~width="480px",
          ~maxWidth="480px",
          ~minWidth="480px",
          ~maxHeight,
          (),
        ),
      )}>
      <Menu topLeft="12" topRight="12" bottomRight="12" bottomLeft="12">
        <GridContainer
          backgroundColor="transparent"
          direction="column"
          justify="center"
          alignItem="stretch">
          <GridItem
            top="0"
            right="0"
            bottom="0"
            left="0"
            enterBackgroundColor="transparent"
            backgroundColor="transparent"
            xs="auto">
            <MenuItem
              top="0"
              right="6"
              bottom="0"
              left="6"
              enterBackgroundColor="rgba(255,255,255,1)"
              downBackgroundColor="rgba(255,255,255,1)"
              backgroundColor="rgba(255,255,255,1)"
              topLeft="12"
              topRight="12"
              bottomRight="12"
              bottomLeft="12"
              onClick={_ => homePath |> ReasonReactRouter.push}>
              <GridContainer
                backgroundColor="transparent"
                direction="row"
                justify="between"
                alignItem="center">
                <GridItem
                  top="0"
                  right="0"
                  bottom="0"
                  enterBackgroundColor="transparent"
                  backgroundColor="transparent"
                  xs="no">
                  <Typography variant="tile">
                    <FormattedMessage
                      id="Action.notice"
                      defaultMessage="Notice"
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
                  <IconButton padding="6">
                    <IconGeneral
                      width="28"
                      height="28"
                      src=settingsApplicationsBlack
                    />
                  </IconButton>
                </GridItem>
              </GridContainer>
            </MenuItem>
          </GridItem>
          <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
            <Divider />
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
             items
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
                        justify="start"
                        alignItem="center">
                        <GridItem
                          top="0"
                          right="0"
                          bottom="0"
                          left="0"
                          enterBackgroundColor="transparent"
                          backgroundColor="transparent"
                          xs="no">
                          <Avatar
                            style={ReactDOMRe.Style.make(
                              ~width="48px",
                              ~height="48px",
                              (),
                            )}
                            top="0"
                            right="0"
                            bottom="0"
                            left="0"
                            enterBorderColor="transparent"
                            downBorderColor="transparent"
                            onClick={_ => item.link |> ReasonReactRouter.push}>
                            <Typography variant="tile">
                              {item.name |> string}
                            </Typography>
                          </Avatar>
                        </GridItem>
                        <GridItem
                          top="0"
                          right="0"
                          bottom="0"
                          enterBackgroundColor="transparent"
                          backgroundColor="transparent"
                          xs="auto">
                          <GridContainer
                            backgroundColor="transparent"
                            direction="column"
                            justify="center"
                            alignItem="stretch">
                            <GridItem
                              top="0"
                              right="0"
                              bottom="0"
                              left="0"
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
                              xs="auto">
                              <Typography variant="subtitle2">
                                {item.datetime |> string}
                              </Typography>
                            </GridItem>
                          </GridContainer>
                        </GridItem>
                      </GridContainer>
                    </MenuItem>
                  </GridItem>
                )
             |> array
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
