open React;
open Basic;
open Together;
open Data;
open Path;
open Icons;
open Axiosapi;
open Storage;
open ObjectFormat;
[%bs.raw {|require('../../../scss/example/Instagram/instagram.scss')|}];

type state = {
  formLoad: bool,
  formWidth: int,
  formHeight: int,
  value: string,
  showRecord: bool,
  showItemRecord: bool,
  recorditems: array(NewBookRecord.item),
  index: int,
  badge: string,
  showBadge: bool,
  showUser: bool,
  beforeLoad: bool,
  showItemBadge: bool,
};

type action =
  | SettingFormLoad(string, int)
  | SettingFormWidth(int, int)
  | SettingBadge(string)
  | ChangeField(string)
  | ShowRecord
  | ClickRecordItems(bool, array(NewBookRecord.item))
  | ShowBadge
  | ShowUser
  | ClickBadgeItems(bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingFormLoad(value, index) => {
      ...state,
      value,
      index,
      formLoad: !state.formLoad,
    }
  | SettingFormWidth(width, height) => {
      ...state,
      formWidth: width,
      formHeight: height,
    }
  | SettingBadge(badge) => {...state, badge}
  | ChangeField(value) => {...state, value}
  | ShowRecord => {...state, showRecord: !state.showRecord}
  | ClickRecordItems(showItemRecord, recorditems) => {
      ...state,
      showItemRecord,
      recorditems,
      beforeLoad: !state.beforeLoad,
    }
  | ShowBadge => {...state, showBadge: !state.showBadge}
  | ShowUser => {...state, showUser: !state.showUser}
  | ClickBadgeItems(showItemBadge) => {
      ...state,
      showItemBadge,
      beforeLoad: !state.beforeLoad,
    }
  };

let initialState = {
  formLoad: false,
  formWidth: 0,
  formHeight: 0,
  value: "",
  showRecord: false,
  showItemRecord: false,
  recorditems: [||],
  index: 0,
  badge: "",
  showBadge: false,
  showUser: false,
  beforeLoad: true,
  showItemBadge: false,
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
  let notification = () =>
    Notifications.message(
      "New message from dcode !",
      {"body": "test", "icon": ""},
    );
  let notificationAJax = () =>
    if (Notifications.make === "granted") {
      notification();
    } else if (Notifications.make !== "denied") {
      Js.Promise.(
        Notifications.request()
        |> then_(response => {
             (
               if (response === "granted") {
                 notification();
               }
             )
             |> resolve
           })
        |> catch(error => error |> Js.log |> resolve)
        |> ignore
      );
    };
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
               notificationAJax();
               badgeFormAJax();
             //JsModules.Browsers.make |> ignore;
             | _ =>
               "" |> Locals.create("newid");
               autoPath |> Sessions.create("autoPath");
               loginPath |> ReasonReactRouter.push;
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
        SettingFormLoad(
          "search" |> Sessions.select |> checkObjects,
          [|"/"|] |> Js_array.indexOf(autoPath),
        )
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
  let recordAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Form.record
      |> then_(response =>
           ClickRecordItems(response##data##showItem, response##data##items)
           |> dispatch
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );
  let searchRecord =
    useCallback(_ => {
      ShowRecord |> dispatch;
      recordAJax();
    });
  let keydownField =
    useCallback(keyCode =>
      if (keyCode == 13 && state.value != "") {
        searchPath ++ "#" ++ state.value |> ReasonReactRouter.push;
      }
    );
  let showBadge = useCallback(_ => ShowBadge |> dispatch);
  let showUser = useCallback(_ => ShowUser |> dispatch);
  let clickOut =
    useCallback(_ => {
      "" |> Locals.create("newid");
      autoPath |> Sessions.create("autoPath");
      loginPath |> ReasonReactRouter.push;
    });
  <>
    <AppBar backgroundColor="rgba(255,255,255,1)" minHeight="54">
      <GridItem
        style=marginAuto
        top="0"
        right="20"
        bottom="0"
        left="20"
        xs="12"
        maxWidth="933px">
        <GridContainer direction="row" justify="center" alignItem="center">
          <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
            <IconButton padding="10" backgroundColor="rgba(0,0,0,0.08)">
              <IconAction animation="circleTop" src=menuBlack />
            </IconButton>
          </GridItem>
          {state.formWidth < 683
             ? null
             : <GridItem
                 style={ReactDOMRe.Style.make(~minWidth="125px", ())}
                 top="0"
                 right="0"
                 bottom="0"
                 left="0"
                 width="215px"
                 xs="no">
                 <TextFieldOutline
                   top="0"
                   right="0"
                   bottom="0"
                   left="0"
                   borderTop="6"
                   borderBottom="6"
                   borderRadius="6"
                   enterBorderColor="rgba(219,219,219,1)"
                   downBorderColor="rgba(219,219,219,1)"
                   borderColor="rgba(219,219,219,1)"
                   fontColor="rgba(38,38,38,1)"
                   value={state.value}
                   onClick=searchRecord
                   onChange={event =>
                     ReactEvent.Form.target(event)##value |> changeField
                   }
                   onKeyDown={event =>
                     ReactEvent.Keyboard.keyCode(event) |> keydownField
                   }>
                   null
                 </TextFieldOutline>
               </GridItem>}
          <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
            <GridContainer direction="row" justify="end" alignItem="center">
              <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                <IconButton
                  enterBackgroundColor="transparent"
                  downBackgroundColor="transparent"
                  padding="6">
                  <IconAction
                    style=zIndexGrow
                    width="28"
                    height="28"
                    animation="leftRight"
                    src=homeBlack
                  />
                </IconButton>
              </GridItem>
              <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                <IconButton
                  enterBackgroundColor="transparent"
                  downBackgroundColor="transparent"
                  padding="6">
                  <IconAction
                    style=zIndexGrow
                    width="28"
                    height="28"
                    animation="leftRight"
                    src=sendBlack
                  />
                </IconButton>
              </GridItem>
              <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                <IconButton
                  enterBackgroundColor="transparent"
                  downBackgroundColor="transparent"
                  padding="6">
                  <IconAction
                    style=zIndexGrow
                    width="28"
                    height="28"
                    animation="leftRight"
                    src=exploreBlack
                  />
                </IconButton>
              </GridItem>
              <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                <IconButton
                  enterBackgroundColor="transparent"
                  downBackgroundColor="transparent"
                  padding="6"
                  onClick=showBadge>
                  <IconAction
                    style=zIndexGrow
                    width="28"
                    height="28"
                    animation="leftRight"
                    src=favoriteBorderBlack
                  />
                </IconButton>
                {state.showBadge
                   ? <NewGramBadge
                       maxHeight
                       badge={state.badge}
                       clickShow=showBadge
                     />
                   : null}
              </GridItem>
              <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                <IconButton
                  enterBackgroundColor="transparent"
                  downBackgroundColor="transparent"
                  padding="6"
                  onClick=showUser>
                  <IconAction
                    style=zIndexGrow
                    width="28"
                    height="28"
                    animation="leftRight"
                    src=personBlack
                  />
                </IconButton>
                {state.showUser
                   ? <NewGramUser clickOut clickShow=showUser /> : null}
              </GridItem>
            </GridContainer>
          </GridItem>
        </GridContainer>
      </GridItem>
    </AppBar>
    children
  </>;
};
