open React;
open Setting;
open OutSide;
open Together;
open ReactIntl;
open Icons;

type state = {showOpen: bool};

type action =
  | ShowOpen;

let reducer = (state, action) =>
  switch (action) {
  | ShowOpen => {showOpen: !state.showOpen}
  };

let initialState = {showOpen: false};

let widths = width =>
  switch (width) {
  | None => "95%"
  | Some(width) => width ++ "%"
  };

let bottoms = bottom =>
  switch (bottom) {
  | None => "0px"
  | Some(bottom) => bottom ++ "px"
  };

[@react.component]
let make =
    (
      ~showProgress: option(bool)=?,
      ~error: option(bool)=?,
      ~width: option(string)=?,
      ~bottom: option(string)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  let showOpen = useCallback(_ => ShowOpen |> dispatch);
  <>
    {showProgress |> disabledObjects
       ? <ProgressLinear style=progressFixed /> : null}
    <IconButton style=menuButn padding="8" onClick=showOpen>
      <IconAction animation="circleTop" src=menuBlack />
    </IconButton>
    <Drawer
      style={ReactDOMRe.Style.combine(
        drawerTube,
        ReactDOMRe.Style.make(
          ~transition={
            state.showOpen
              ? "width 225ms cubic-bezier(0.4, 0, 0.6, 1) 0ms"
              : "width 195ms cubic-bezier(0.4, 0, 0.6, 1) 0ms";
          },
          (),
        ),
      )}
      left="0"
      width={state.showOpen ? "240px" : "72px"}
      height="64"
      location="left">
      <List_>
        <ListItem top="0" right="0" bottom="0" left="0">
          <GridContainer
            backgroundColor="transparent"
            direction="row"
            justify="center"
            alignItem="center">
            <GridItem
              style={ReactDOMRe.Style.make(~height="24px", ())}
              top="0"
              right={state.showOpen ? "18" : "0"}
              bottom="0"
              left="0"
              enterBackgroundColor="transparent"
              backgroundColor="transparent"
              xs="no">
              <IconGeneral src=homeBlack />
            </GridItem>
            {state.showOpen
               ? <GridItem
                   top="0"
                   right="0"
                   bottom="0"
                   left="0"
                   enterBackgroundColor="transparent"
                   backgroundColor="transparent"
                   xs="auto">
                   <Typography variant="subheading">
                     <FormattedMessage id="Path.home" defaultMessage="Home" />
                   </Typography>
                 </GridItem>
               : null}
          </GridContainer>
        </ListItem>
      </List_>
      <Divider />
    </Drawer>
    <main
      style={ReactDOMRe.Style.combine(
        mainTube,
        ReactDOMRe.Style.make(
          ~right="0px",
          ~left={
            state.showOpen ? "250px" : "75px";
          },
          ~transition={
            state.showOpen
              ? "left 225ms cubic-bezier(0.4, 0, 0.6, 1) 0ms"
              : "left 195ms cubic-bezier(0.4, 0, 0.6, 1) 0ms";
          },
          ~bottom={
            bottom |> bottoms;
          },
          (),
        ),
      )}>
      <div style=divScrollbar>
        <div
          style={ReactDOMRe.Style.combine(
            marginAuto,
            ReactDOMRe.Style.make(
              ~width={
                width |> widths;
              },
              ~maxWidth={
                width |> widths;
              },
              ~flexBasis={
                width |> widths;
              },
              (),
            ),
          )}>
          {error |> disabledObjects
             ? <div style=errorForm>
                 <Typography
                   variant="tile"
                   color="rgba(255,0,0,0.8)"
                   fontSize="x-large"
                   noWrap=true>
                   {"UNDEFINED THIS PAGE" |> string}
                 </Typography>
               </div>
             : children}
        </div>
      </div>
    </main>
  </>;
};
