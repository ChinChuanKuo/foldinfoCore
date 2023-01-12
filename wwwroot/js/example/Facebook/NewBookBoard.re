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
[%bs.raw {|require('../../../scss/example/Facebook/newBookBoard.scss')|}];

type tabtitem = {
  showTab: bool,
  tabImage: string,
  tabTip: string,
  tabPath: string,
};

type state = {
  formLoad: bool,
  formWidth: int,
  formHeight: int,
  value: string,
  showRecord: bool,
  showItemRecord: bool,
  recorditems: array(NewBookRecord.item),
  menuPath: string,
  tabitems: list(tabtitem),
  index: int,
  showCreate: bool,
  badge: string,
  showBadge: bool,
  beforeLoad: bool,
  showItemBadge: bool,
  badgeitems: array(NewBookBadge.item),
  showItemUser: bool,
  checked: bool,
};

type action =
  | SettingFormLoad(string, int)
  | SettingFormWidth(int, int)
  | SettingBadge(string)
  | ChangeField(string)
  | ShowRecord
  | ClickRecordItems(bool, array(NewBookRecord.item))
  | SettingPath(string)
  | ClickItemTab(int)
  | ShowCreate
  | ClickBadgeItems(bool, array(NewBookBadge.item))
  | ShowBadge
  | ShowItemUser
  | SwitchChecked;

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
  | SettingPath(value) => {...state, menuPath: value}
  | ClickItemTab(index) => {
      ...state,
      tabitems:
        List.mapi(
          (i, tabtitem) => {...tabtitem, showTab: index == i},
          state.tabitems,
        ),
      index,
    }
  | ShowCreate => {...state, showCreate: !state.showCreate}
  | ClickBadgeItems(showItemBadge, badgeitems) => {
      ...state,
      showItemBadge,
      badgeitems,
      beforeLoad: !state.beforeLoad,
    }
  | ShowBadge => {...state, showBadge: !state.showBadge, beforeLoad: true}
  | ShowItemUser => {...state, showItemUser: !state.showItemUser}
  | SwitchChecked => {...state, checked: !state.checked}
  };

let initialState = {
  formLoad: false,
  formWidth: 0,
  formHeight: 0,
  value: "",
  showRecord: false,
  showItemRecord: false,
  recorditems: [||],
  menuPath: "/",
  tabitems: [
    {
      showTab: true,
      tabImage: transmissionBlack,
      tabTip: {js|品異單|js},
      tabPath: homePath,
    },
    {
      showTab: false,
      tabImage: factoryBlack,
      tabTip: {js|工廠內部通告|js},
      tabPath: insidePath,
    },
    {
      showTab: false,
      tabImage: fileCopyBlack,
      tabTip: {js|ISO三階文件|js},
      tabPath: isoFilePath,
    },
    {
      showTab: false,
      tabImage: homeBlack,
      tabTip: {js|生產注意事項|js},
      tabPath: productPath,
    },
    {
      showTab: false,
      tabImage: homeBlack,
      tabTip: {js|簽核總列表|js},
      tabPath: signlistPath,
    },
  ],
  index: 0,
  showCreate: false,
  badge: "",
  showBadge: false,
  beforeLoad: true,
  showItemBadge: false,
  badgeitems: [||],
  showItemUser: false,
  checked: false,
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
  let menuShow = autoPath === "bookmarks";
  let maxHeight = string_of_int(state.formHeight) ++ "px";
  let badgeFormFunc: string => unit = [%bs.raw
    badge => {| badgeFormAJax(badge); |}
  ];
  let badgeFormEror: string => unit = [%bs.raw
    badge => {| setTimeout(() => badgeFormAJax(badge), 15000); |}
  ];
  let badgeFormAJax = badge =>
    Js.Promise.(
      badge
      |> otherData("newid" |> Locals.select)
      |> Form.badgeForm
      |> then_(response =>
           {
             SettingBadge(response##data##status) |> dispatch;
             response##data##status |> badgeFormFunc;
           }
           |> resolve
         )
      |> catch(_ => badge |> badgeFormEror |> resolve)
      |> ignore
    );
  let notification = () =>
    Notifications.message(
      "New message from dcode!",
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
               //JsModules.Browsers.make |> ignore;
               state.badge |> badgeFormAJax;
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
          [|"/", "inside", "isoFile", "product", "/signlist"|]
          |> Js_array.indexOf(autoPath),
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
  let addCordAJax = () =>
    Js.Promise.(
      state.value
      |> otherData("newid" |> Locals.select)
      |> Form.addCord
      |> then_(_ =>
           searchPath
           ++ "#"
           ++ state.value
           |> ReasonReactRouter.push
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );
  let keydownField =
    useCallback(keyCode =>
      if (keyCode == 13 && state.value != "") {
        ShowRecord |> dispatch;
        addCordAJax();
      }
    );
  let showMenu =
    useCallback(_ =>
      if (state.formWidth < 1100) {
        if (!menuShow) {
          SettingPath(autoPath) |> dispatch;
        };
        let menuPath = menuShow ? state.menuPath : bookmarksPath;
        menuPath |> ReasonReactRouter.push;
      }
    );
  let clickItemTab =
    useCallback((i, tabPath) => {
      ClickItemTab(i) |> dispatch;
      tabPath |> ReasonReactRouter.push;
    });
  let showCreate = useCallback(_ => ShowCreate |> dispatch);
  let createForm =
    useCallback(_ => {
      ClickItemTab(-1) |> dispatch;
      ShowCreate |> dispatch;
      createRPath |> ReasonReactRouter.push;
    });
  let contactsForm =
    useCallback(_ => {
      ClickItemTab(-1) |> dispatch;
      ShowCreate |> dispatch;
      createFPath |> ReasonReactRouter.push;
    });
  let assistantForm =
    useCallback(_ => {
      ClickItemTab(-1) |> dispatch;
      ShowCreate |> dispatch;
      createIPath |> ReasonReactRouter.push;
    });
  let flagForm =
    useCallback(_ => {
      ClickItemTab(-1) |> dispatch;
      ShowCreate |> dispatch;
      createPPath |> ReasonReactRouter.push;
    });
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
  let showItemUser = useCallback(_ => ShowItemUser |> dispatch);
  let switchChecked = useCallback(_ => SwitchChecked |> dispatch);
  let clickOut =
    useCallback(_ => {
      "" |> Locals.create("newid");
      autoPath |> Sessions.create("autoPath");
      loginPath |> ReasonReactRouter.push;
    });
  <>
    <AppBar backgroundColor="rgba(255,255,255,1)" minHeight="60">
      <GridContainer direction="row" justify="between" alignItem="center">
        <GridItem top="0" right="0" bottom="0" left="0" xs="no">
          <GridContainer direction="row" justify="center" alignItem="center">
            {state.showRecord
               ? <GridItem top="0" right="0" bottom="0" width="46px" xs="no">
                   null
                 </GridItem>
               : <GridItem top="0" right="0" bottom="0" xs="no">
                   <IconButton padding="10" backgroundColor="rgba(0,0,0,0.08)">
                     <IconAction animation="circleTop" src=flytech />
                   </IconButton>
                 </GridItem>}
            {switch (state.formWidth < 1259, state.showRecord) {
             | (true, false) =>
               <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                 <IconButton padding="8" onClick=searchRecord>
                   <Tooltip
                     location="bottom" backgroundColor="rgba(255,0,0,0.8)">
                     <FormattedMessage
                       id="Action.search"
                       defaultMessage="Search"
                     />
                   </Tooltip>
                   <IconAction
                     style=zIndexGrow
                     animation="circle"
                     src=searchBlack
                   />
                 </IconButton>
               </GridItem>
             | (false, false) =>
               <GridItem
                 top="0" right="0" bottom="0" left="0" width="242px" xs="auto">
                 <TextFieldOutline
                   top="0"
                   right="0"
                   bottom="0"
                   left="0"
                   borderTop="12"
                   borderBottom="12"
                   borderRadius="20"
                   value={state.value}
                   onClick=searchRecord>
                   null
                 </TextFieldOutline>
               </GridItem>
             | (true, _) =>
               <GridItem
                 top="0" right="0" bottom="0" left="0" width="38px" xs="auto">
                 null
               </GridItem>
             | (false, _) =>
               <GridItem
                 top="0" right="0" bottom="0" left="0" width="240px" xs="auto">
                 null
               </GridItem>
             }}
            {state.formWidth < 1100
               ? <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                   <IconButton padding="12" borderRadius="20" onClick=showMenu>
                     <IconAction
                       animation="circleTop"
                       src={menuShow ? menuWarn : menuBlack}
                     />
                   </IconButton>
                 </GridItem>
               : null}
            {state.showRecord
               ? <NewBookRecord
                   maxHeight
                   value={state.value}
                   beforeLoad={state.beforeLoad}
                   showItem={state.showItemRecord}
                   items={state.recorditems}
                   onChange={event =>
                     ReactEvent.Form.target(event)##value |> changeField
                   }
                   onKeyDown={event =>
                     ReactEvent.Keyboard.keyCode(event) |> keydownField
                   }
                   clickShow=searchRecord
                 />
               : null}
          </GridContainer>
        </GridItem>
        <GridItem
          top="0" right="0" bottom="0" left="0" maxWidth="55%" xs="auto">
          {state.formWidth < 701
             ? null
             : <Tabs
                 maxWidth="558"
                 display="block"
                 id="tab-"
                 index={state.index}
                 short=10
                 height="3">
                 {state.tabitems
                  |> List.mapi((i, tabtitem) =>
                       <Tab
                         showTab={tabtitem.showTab}
                         maxWidth="111.6"
                         borderRadius="15"
                         id={"tab-" ++ string_of_int(i)}
                         animationName="none"
                         onClick={_ => tabtitem.tabPath |> clickItemTab(i)}>
                         <Tooltip
                           location="bottom"
                           backgroundColor="rgba(255,0,0,0.8)">
                           {tabtitem.tabTip |> string}
                         </Tooltip>
                         <IconAction
                           width="28"
                           height="28"
                           animation="leftRight"
                           src={tabtitem.tabImage}
                         />
                       </Tab>
                     )
                  |> Array.of_list
                  |> array}
               </Tabs>}
        </GridItem>
        <GridItem top="0" right="0" bottom="0" left="0" xs="no">
          <GridContainer direction="row" justify="end" alignItem="center">
            {state.formWidth < 1259
               ? null
               : <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                   <Chip
                     right="0"
                     enterBorderWidth="0"
                     downBorderWidth="0"
                     borderWidth="0">
                     ...(
                          <Typography variant="subtitle2">
                            {"name" |> Locals.select |> checkObjects |> string}
                          </Typography>,
                          <Typography variant="subtitle2">
                            {"allname"
                             |> Locals.select
                             |> checkObjects
                             |> string}
                          </Typography>,
                        )
                   </Chip>
                 </GridItem>}
            <GridItem top="0" right="0" bottom="0" left="0" xs="no">
              <IconButton
                style=butnRight
                padding="8"
                className="butnToolAction"
                onClick=showCreate>
                <Tooltip location="bottom" backgroundColor="rgba(255,0,0,0.8)">
                  <FormattedMessage id="create" defaultMessage="Create" />
                </Tooltip>
                <IconAction
                  style=zIndexGrow
                  animation="leftRight"
                  src=addBlack
                />
              </IconButton>
              {state.showCreate
                 ? <NewBookCreate
                     maxHeight
                     createForm
                     contactsForm
                     assistantForm
                     flagForm
                     clickShow=showCreate
                   />
                 : null}
            </GridItem>
            <GridItem top="0" right="0" bottom="0" left="0" xs="no">
              <IconButton
                style=butnRight
                padding="8"
                className="butnToolAction"
                onClick=searchBadge>
                <Badge backgroundColor="rgba(255,0,0,0.8)">
                  {state.badge |> string}
                </Badge>
                <Tooltip location="bottom" backgroundColor="rgba(255,0,0,0.8)">
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
                 ? <NewBookBadge
                     maxHeight
                     beforeLoad={state.beforeLoad}
                     showItem={state.showItemBadge}
                     items={state.badgeitems}
                     clickShow=showBadge
                   />
                 : null}
            </GridItem>
            <GridItem top="0" right="0" bottom="0" left="0" xs="no">
              <IconButton
                style=butnRight
                padding="8"
                className="butnToolAction"
                onClick=showItemUser>
                <Tooltip location="bottom" backgroundColor="rgba(255,0,0,0.8)">
                  <FormattedMessage
                    id="Action.account"
                    defaultMessage="Account"
                  />
                </Tooltip>
                <IconAction
                  style=zIndexGrow
                  animation="leftRight"
                  src=arrowDownBlack
                />
              </IconButton>
              {state.showItemUser
                 ? <NewBookUser
                     checked={state.checked}
                     switchChecked
                     clickOut
                     clickShow=showItemUser
                   />
                 : null}
            </GridItem>
          </GridContainer>
        </GridItem>
      </GridContainer>
    </AppBar>
    children
  </>;
};
