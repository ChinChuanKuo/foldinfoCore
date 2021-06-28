open React;
open Basic;
open OutSide;
open Together;
open ReactIntl;
open Data;
open Path;
open Icons;
open Axiosapi;
open Storage;
open ObjectFormat;
[%bs.raw {|require('../../../scss/example/Youtube/youtubeBoard.scss')|}];

type state = {
  formLoad: bool,
  formWidth: int,
  formHeight: int,
  showLogin: bool,
  value: string,
  showRecord: bool,
  badge: string,
  showBadge: bool,
  badgeLoad: bool,
  showItem: bool,
  items: array(NewYouBadge.item),
  showMenu: bool,
};

type action =
  | SettingFormLoad(string)
  | SettingFormWidth(int, int)
  | SettingBadge(string)
  | ShowLogin
  | ChangeField(string)
  | ShowRecord
  | ClickBadgeItems(bool, array(NewYouBadge.item))
  | ShowBadge
  | ShowMenu;

let reducer = (state, action) =>
  switch (action) {
  | SettingFormLoad(value) => {...state, value, formLoad: !state.formLoad}
  | SettingFormWidth(width, height) => {
      ...state,
      formWidth: width,
      formHeight: height,
    }
  | SettingBadge(badge) => {...state, badge}
  | ShowLogin => {...state, showLogin: !state.showLogin}
  | ChangeField(value) => {...state, value}
  | ShowRecord => {...state, showRecord: !state.showRecord}
  | ClickBadgeItems(showItem, items) => {
      ...state,
      showItem,
      items,
      badgeLoad: !state.badgeLoad,
    }
  | ShowBadge => {...state, showBadge: !state.showBadge, badgeLoad: true}
  | ShowMenu => {...state, showMenu: !state.showMenu}
  };

let initialState = {
  formLoad: false,
  formWidth: 0,
  formHeight: 0,
  showLogin: true,
  value: "",
  showRecord: false,
  badge: "",
  showBadge: false,
  badgeLoad: true,
  showItem: false,
  items: [||],
  showMenu: false,
};

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
let make = (~autoPath: 'a, ~children) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  let maxHeight = string_of_int(state.formHeight) ++ "px";
  let badgeFormAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Form.badgeForm
      |> then_(response =>
           SettingBadge(response##data##status) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );
  let loginFormAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Form.loginForm
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               response##data##name |> Locals.create("name");
               response##data##allname |> Locals.create("allname");
               Navigator.Position.make(
                 Location.success,
                 Location.error,
                 Location.items,
               )
               |> ignore;
               Navigator.Browser.make |> Browser.success |> ignore;
               //JsModules.Browsers.make |> ignore;
               badgeFormAJax();
             //searchAJax();
             | _ =>
               "" |> Locals.create("newid");
               ShowLogin |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );
  useEffect(() =>
    if (state.formLoad) {
      Some(() => "action" |> Js.log);
    } else {
      let testId =
        SettingFormLoad("search" |> Sessions.select |> checkObjects)
        |> dispatch;
      let formId =
        SettingFormWidth(Window.Sizes.width, Window.Sizes.height) |> dispatch;
      let badgeId = loginFormAJax();
      Some(
        () => {
          testId;
          formId;
          badgeId;
        },
      );
    }
  );
  let handleResize = event =>
    SettingFormWidth(
      event##currentTarget##innerWidth,
      event##currentTarget##innerHeight,
    )
    |> dispatch;
  useEffect0(() => {
    let testId = Window.Listeners.add("resize", handleResize, true) |> ignore;
    Some(() => testId);
  });
  let changeField =
    useCallback(value => {
      ChangeField(value) |> dispatch;
      value |> Sessions.create("search");
    });
  let searchRecord = useCallback(_ => ShowRecord |> dispatch);
  let keydownField =
    useCallback(keyCode =>
      if (keyCode == 13 && state.value != "") {
        searchPath ++ "#" ++ state.value |> ReasonReactRouter.push;
      }
    );
  let badgeAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Form.badge
      |> then_(response =>
           ClickBadgeItems(response##data##showItem, response##data##items)
           |> dispatch
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );
  let searchBadge =
    useCallback(_ => {
      ShowBadge |> dispatch;
      badgeAJax();
    });
  let showBadge = useCallback(_ => ShowBadge |> dispatch);
  let showMenu = useCallback(_ => ShowMenu |> dispatch);
  let clickOut =
    useCallback(_ => {
      "" |> Locals.create("newid");
      autoPath |> Sessions.create("autoPath");
      loginPath |> ReasonReactRouter.push;
    });
  <>
    <AppBar>
      <GridContainer direction="row" justify="between" alignItem="center">
        <GridItem top="0" right="0" bottom="0" width="140px" xs="no">
          <GridContainer direction="row" justify="start" alignItem="center">
            <GridItem
              top="0" right="16" bottom="0" left="0" width="46px" xs="no">
              null
            </GridItem>
            <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
              <Typography
                variant="subheading" style=zIndexGrow fontSize="1.15rem">
                {"BTS" |> string}
              </Typography>
            </GridItem>
          </GridContainer>
        </GridItem>
        {switch (state.showLogin, state.formWidth < 656) {
         | (true, false) =>
           <GridItem
             top="0" right="0" bottom="0" left="0" xs="auto" maxWidth="50%">
             <TextFieldOutline
               top="0"
               right="12"
               bottom="0"
               left="0"
               borderTop="10"
               borderBottom="10"
               value={state.value}
               onChange={event =>
                 ReactEvent.Form.target(event)##value |> changeField
               }
               onKeyDown={event =>
                 ReactEvent.Keyboard.keyCode(event) |> keydownField
               }>
               null
             </TextFieldOutline>
           </GridItem>
         | (_, _) => null
         }}
        <GridItem top="0" right="0" bottom="0" left="0" xs="no">
          <GridContainer direction="row" justify="end" alignItem="center">
            {switch (state.showLogin, state.formWidth < 656) {
             | (true, true) =>
               <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                 <IconButton padding="8" onClick=searchRecord>
                   <Tooltip
                     location="bottom" backgroundColor="rgba(255,0,0,0.8)">
                     <FormattedMessage
                       id="Action.search"
                       defaultMessage="Search"
                     />
                   </Tooltip>
                   <IconAction animation="circle" src=searchBlack />
                 </IconButton>
               </GridItem>
             | (_, _) => null
             }}
            <GridItem top="0" right="0" bottom="0" left="0" xs="no">
              <IconButton
                style=butnRight padding="8" className="butnToolAction">
                <Tooltip location="bottom" backgroundColor="rgba(255,0,0,0.8)">
                  <FormattedMessage
                    id="Action.network"
                    defaultMessage="Network"
                  />
                </Tooltip>
                <IconAction
                  style=zIndexGrow
                  animation="leftRight"
                  src=wifiBlack
                />
              </IconButton>
            </GridItem>
            <GridItem top="0" right="0" bottom="0" left="0" xs="no">
              <IconButton
                style=butnRight
                padding="8"
                className="butnToolAction"
                onClick={_ => colorPath |> ReasonReactRouter.push}>
                <Tooltip location="bottom" backgroundColor="rgba(255,0,0,0.8)">
                  <FormattedMessage id="Action.color" defaultMessage="Color" />
                </Tooltip>
                <IconAction
                  style=zIndexGrow
                  animation="leftRight"
                  src=colorLensBlack
                />
              </IconButton>
            </GridItem>
            {state.showLogin
               ? <>
                   <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                     <IconButton
                       style=butnRight
                       padding="8"
                       className="butnToolAction"
                       onClick=searchBadge>
                       <Badge backgroundColor="transparent">
                         {state.badge |> string}
                       </Badge>
                       <Tooltip
                         location="bottom" backgroundColor="rgba(255,0,0,0.8)">
                         <FormattedMessage
                           id="Action.notice"
                           defaultMessage="Notice"
                         />
                       </Tooltip>
                       <IconAction
                         style=zIndexGrow
                         animation="leftRight"
                         src=notificationsBlack
                       />
                     </IconButton>
                     {state.showBadge
                        ? <NewYouBadge
                            maxHeight
                            beforeLoad={state.badgeLoad}
                            showItem={state.showItem}
                            items={state.items}
                            clickShow=showBadge
                          />
                        : null}
                   </GridItem>
                   <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                     <Avatar
                       top="5" right="16" bottom="5" left="0" onClick=showMenu>
                       {"name" |> Locals.select |> checkObjects |> string}
                     </Avatar>
                     {state.showMenu
                        ? <NewYouUser clickOut clickShow=showMenu /> : null}
                   </GridItem>
                 </>
               : <GridItem top="0" right="15" bottom="0" left="0" xs="no">
                   <Button
                     onClick={_ => {
                       autoPath |> Sessions.create("autoPath");
                       loginPath |> ReasonReactRouter.push;
                     }}>
                     <FormattedMessage
                       id="Action.login"
                       defaultMessage="Login"
                     />
                   </Button>
                 </GridItem>}
          </GridContainer>
        </GridItem>
      </GridContainer>
    </AppBar>
    children
  </>;
};
