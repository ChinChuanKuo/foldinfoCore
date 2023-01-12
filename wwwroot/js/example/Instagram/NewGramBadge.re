open React;
open OutSide;
open ReactIntl;
open Setting;
open Icons;

type state = {showBadge: bool};

type action =
  | ShowBadge;

let reducer = (state, action) =>
  switch (action) {
  | ShowBadge => {showBadge: !state.showBadge}
  };

let initialState = {showBadge: false};

let transforms = showAnimation =>
  showAnimation ? "translate(0px, 0px)" : "translateX(200vh) translateX(0px)";

let boardstyles = showAnimation =>
  ReactDOMRe.Style.make(
    ~position="absolute",
    ~transform={
      showAnimation |> transforms;
    },
    ~transition="transform 225ms cubic-bezier(0, 0, 0.2, 1) 0ms",
    (),
  );

[@react.component]
let make =
    (
      ~maxHeight: string,
      ~badge: option(string)=?,
      ~clickShow: option(ReactEvent.Mouse.t => unit)=?,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  let showBadge = useCallback(_ => ShowBadge |> dispatch);
  <>
    <div
      style={ReactDOMRe.Style.combine(
        menuOutSide,
        ReactDOMRe.Style.make(
          ~top="54px",
          ~width="500px",
          ~maxWidth="500px",
          ~minWidth="500px",
          ~maxHeight,
          ~marginLeft="-423px",
          ~borderRadius="10px",
          (),
        ),
      )}>
      <GridItem
        style={!state.showBadge |> boardstyles}
        top="0"
        right="0"
        bottom="0"
        left="0"
        width="100%"
        enterBorderWidth="0"
        borderWidth="0"
        enterBorderRadius="6"
        borderRadius="6"
        xs="12">
        <Menu top="12" bottom="13" left="16" right="16">
          <GridContainer
            backgroundColor="transparent"
            direction="column"
            justify="start"
            alignItem="stretch">
            <GridItem
              top="0"
              right="0"
              bottom="0"
              left="0"
              cursor="pointer"
              enterBackgroundColor="transparent"
              backgroundColor="transparent"
              xs="auto">
              <div onClick=showBadge>
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
                    <Avatar
                      style={ReactDOMRe.Style.make(
                        ~width="32px",
                        ~height="32px",
                        (),
                      )}
                      top="0"
                      right="0"
                      bottom="0"
                      left="0"
                      enterBorderColor="transparent"
                      downBorderColor="transparent">
                      {badge |> stringObjects |> string}
                    </Avatar>
                  </GridItem>
                  <GridItem
                    top="0"
                    bottom="0"
                    enterBackgroundColor="transparent"
                    backgroundColor="transparent"
                    xs="auto">
                    <GridContainer
                      direction="column" justify="start" alignItem="stretch">
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        <Typography
                          variant="subtitle2" fontWeight="700" lineHeight="1">
                          <FormattedMessage
                            id="Gram.track"
                            defaultMessage="Track"
                          />
                        </Typography>
                      </GridItem>
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        <Typography
                          variant="subtitle2"
                          color="rgba(142,142,142,1)"
                          lineHeight="1">
                          <FormattedMessage
                            id="Gram.require"
                            defaultMessage="Require"
                          />
                        </Typography>
                      </GridItem>
                    </GridContainer>
                  </GridItem>
                  <GridItem
                    top="0"
                    right="0"
                    bottom="0"
                    left="0"
                    enterBackgroundColor="transparent"
                    backgroundColor="transparent"
                    xs="no">
                    <IconButton
                      enterBackgroundColor="transparent"
                      downBackgroundColor="transparent"
                      padding="6">
                      <IconAction
                        width="15"
                        height="15"
                        animation="leftRight"
                        src=arrowForwardIosBlack
                      />
                    </IconButton>
                  </GridItem>
                </GridContainer>
              </div>
            </GridItem>
            <GridItem
              right="0"
              left="0"
              enterBackgroundColor="transparent"
              backgroundColor="transparent"
              xs="auto">
              null
            </GridItem>
          </GridContainer>
        </Menu>
      </GridItem>
      <GridItem
        style={state.showBadge |> boardstyles}
        top="0"
        right="0"
        bottom="0"
        left="0"
        width="100%"
        enterBorderWidth="0"
        borderWidth="0"
        enterBorderRadius="6"
        borderRadius="6"
        xs="12">
        <Menu top="12" bottom="13" left="16" right="16"> null </Menu>
      </GridItem>
    </div>
    <BackgroundBoard
      showBackground=true
      backgroundColor="transparent"
      onClick=?clickShow
    />
  </>;
};
