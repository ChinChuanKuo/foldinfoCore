open React;
open Together;
open ReactIntl;
open Path;
open Data;
open Icons;
open Items;
open Axiosapi;
open Status;
open Storage;
open IconAnimation;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type nameitem = {
  padding: bool,
  key: string,
  value: string,
};

type item = {
  iid: string,
  group: string,
  showGroupMenu: bool,
  groupitems: array(optionitem),
  id: string,
  name: string,
  showNameMenu: bool,
  nameitems: array(nameitem),
  itemInsert: bool,
  itemModify: bool,
};

type state = {
  formLoad: bool,
  formWidth: int,
  formHeight: int,
  showProgress: bool,
  error: bool,
  insert: bool,
  update: bool,
  delete: bool,
  export: bool,
  tabitems: list(tabitem),
  index: int,
  items: array(item),
  showYoutube: bool,
  youtubeText: string,
};

let newitem = (iid, groupitems) => 
[|{ iid, group: "",
  showGroupMenu: false,
  groupitems,
  id: "",
  name: "",
  showNameMenu: false,
  nameitems: [||],
  itemInsert: true,
  itemModify: false 
  }|]

type action =
  | SettingError
  | SettingFormLoad
  | SettingFormWidth(int, int)
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormItems(array(item))
  | ClickItemTab(int)
  | AddForm(array(optionitem))
  | ShowGroupMenu(int)
  | ClickGroupMenu(string, int)
  | ShowNameMenu(int)
  | SettingItemName(array(nameitem), int)
  | ClickNameMenu(string, string, int)
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingError => {...state, error: !state.error}
  | SettingFormLoad => {...state, formLoad: !state.formLoad}
  | SettingFormWidth(width, height) => {
      ...state,
      formWidth: width,
      formHeight: height,
    }
  | ActionShowProgress => {...state, showProgress: !state.showProgress}
  | ActionPermissItems(insert, update, delete, export) => {
      ...state,
      insert,
      update,
      delete,
      export,
    }
  | SettingFormItems(items) => {...state, items}
  | ClickItemTab(index) => {
      ...state,
      tabitems:
        List.mapi(
          (i, tabitem) => {...tabitem, showTab: index == i},
          state.tabitems,
        ),
      index,
    }
  | AddForm(groupitems) => {
    ...state,
    items:
        Array.append(
          state.items,
          newitem(
            int_of_string(state.items[Js_array.length(state.items) - 1].iid) + 1 |> string_of_int,
            groupitems,
          ),
        ),
  }
  | ShowGroupMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showGroupMenu: !item.showGroupMenu} : item,
          state.items,
        ),
    }
  | ClickGroupMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                group: value,
                showGroupMenu: !item.showGroupMenu,
                itemModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ShowNameMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showNameMenu: !item.showNameMenu} : item,
          state.items,
        ),
    }
  | SettingItemName(items, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, nameitems: items} : item,
          state.items,
        ),
    }
  | ClickNameMenu(key, value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                id: key,
                name: value,
                showNameMenu: !item.showNameMenu,
                itemModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ActionSnackBar(youtubeText, showYoutube) => {
      ...state,
      youtubeText,
      showYoutube,
    }
  };

let initialState = {
  formLoad: false,
  formWidth: 0,
  formHeight: 0,
  showProgress: true,
  error: false,
  insert: false,
  update: false,
  delete: false,
  export: false,
  tabitems: [{showTab: true, tabImage: transmissionBlack}, {showTab: false, tabImage: factoryBlack}],
  index: 0,
  items: [||],
  showYoutube: false,
  youtubeText: "", 
};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);

  let barShowRestoreAction = youtubeText => {
    ActionSnackBar(youtubeText, true) |> dispatch;
    Js.Global.setTimeout(() => ActionSnackBar("", false) |> dispatch, 5000)
    |> ignore;
  };

  let searchAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Axiosapi.SendistR.search
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               SettingFormItems(response##data##items) |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               SettingError |> dispatch;
               response##data##status |> statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let permissAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Form.permiss
      |> then_(response =>
           {
             ActionPermissItems(
               response##data##insert,
               response##data##update,
               response##data##delete,
               response##data##export,
             )
             |> dispatch;
             searchAJax();
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  useEffect(() =>
    switch (state.formLoad) {
    | true => Some(() => "action" |> Js.log)
    | _ =>
      let testtime = SettingFormLoad |> dispatch;
      let sizeId =
        SettingFormWidth(Window.Sizes.width, Window.Sizes.height) |> dispatch;
      let timeId = permissAJax();
      Some(
        () => {
          testtime;
          sizeId;
          timeId;
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
    let sizeId = Window.Listeners.add("resize", handleResize, true) |> ignore;
    /*let scrollId =
      Window.Listeners.add("scroll", handleScrollBar, true) |> ignore;*/
    Some(() => sizeId);
  });

  let clickItemTab = useCallback(i => {
      switch (i) {
      | 0 => sendistRPath |> ReasonReactRouter.push
      | _ => sendistFPath |> ReasonReactRouter.push
      };
  });

      let addAJax = () => 
      Js.Promise.(
        "newid"
        |> Locals.select
        |> userData
        |> Axiosapi.SendistR.add
        |> then_(response =>
            {
              AddForm(response##data##items) |> dispatch;
              ActionShowProgress |> dispatch;
            }
            |> resolve
          )
        |> catch(error => error |> Js.log |> resolve)
        |> ignore
      );

    let addForm = 
    useCallback(_ => {
        ActionShowProgress |> dispatch;
        addAJax();
    });

  let insertAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iItemsData(
           Js_array.filter(
             (item: item) => item.itemModify === true,
             state.items,
           ),
         )
      |> Axiosapi.SendistR.insert
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               "saveSuccess" |> statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let insertForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      insertAJax();
    });

  let showGroupMenu = useCallback(i => ShowGroupMenu(i) |> dispatch);

  let sGroupAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.SendistR.sGroup
      |> then_(response =>
           SettingItemName(response##data##items, i) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickGroupMenu =
    useCallback((value, i) => {
      ClickGroupMenu(value, i) |> dispatch;
      i |> sGroupAJax(value);
    });

  let showNameMenu = useCallback(i => ShowNameMenu(i) |> dispatch);

  let clickNameMenu =
    useCallback((key, value, i) => ClickNameMenu(key, value, i) |> dispatch);

  <>
    <NewFacetube showProgress={state.showProgress} error={state.error}>
      <GridItem
        style=marginAuto
        top="0"
        right="32"
        bottom="0"
        left="32"
        xs="12"
        maxWidth="770px">
        <GridContainer direction="column" justify="center" alignItem="stretch">
          <GridItem
            style={ReactDOMRe.Style.make(
              ~position="sticky",
              ~top="0px",
              ~zIndex="1000",
              (),
            )}
            top="0"
            bottom="6"
            xs="auto">
            <GridContainer
              backgroundColor="transparent"
              direction="row"
              justify="between"
              alignItem="center">
              <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                <Tabs id="send-" index={state.index} height="3">
                  {state.tabitems
                   |> List.mapi((i, tabitem) =>
                        <Tab
                          showTab={tabitem.showTab}
                          maxWidth="111.6"
                          borderRadius="15"
                          id={"send-" ++ string_of_int(i)}
                          animationName="none"
                          onClick={_ => i |> clickItemTab}>
                          <IconAction
                            width="28"
                            height="28"
                            animation="leftRight"
                            src={tabitem.tabImage}
                          />
                        </Tab>
                      )
                   |> Array.of_list
                   |> array}
                </Tabs>
              </GridItem>
              <GridItem top="0" bottom="0" left="0" xs="no">
                <Button
                  variant="button"
                  disabled={state.showProgress}
                  onClick=addForm>
                  <FormattedMessage id="add" defaultMessage="Add" />
                </Button>
              </GridItem>
              <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                <Button
                  variant="button"
                  disabled={state.showProgress}
                  onClick=insertForm>
                  <FormattedMessage id="save" defaultMessage="Save" />
                </Button>
              </GridItem>
            </GridContainer>
          </GridItem>
          {state.items
           |> Array.mapi((i, item) =>
                <GridItem
                  style=cursorPointer
                  enterBorderRadius="10"
                  enterBackgroundColor="rgba(0,0,0,0.1)"
                  xs="auto">
                  <GridContainer
                    backgroundColor="transparent"
                    direction="row"
                    justify="center"
                    alignItem="center">
                    <GridItem
                      top="0"
                      right="0"
                      bottom="0"
                      left="0"
                      enterBackgroundColor="transparent"
                      backgroundColor="transparent"
                      xs="auto">
                      <SelectStandard
                        top="12"
                        right="0"
                        left="0"
                        tile={js|部門|js}
                        labelColor="rgba(255,0,0,0.8)"
                        enterBorderColor="rgba(255,0,0,0.8)"
                        downBorderColor="rgba(255,0,0,0.6)"
                        borderColor="rgba(0,0,0,0.2)"
                        value={item.group}
                        disabled={state.showProgress}
                        onClick={_ => i |> showGroupMenu}>
                        ...(
                             item.showGroupMenu
                               ? <SelectMenu
                                   top="0"
                                   transform="translate(0, 0)"
                                   maxHeight="280"
                                   minHeight="0"
                                   topLeft="12"
                                   topRight="12"
                                   bottomRight="12"
                                   bottomLeft="12"
                                   paddingRight="8"
                                   paddingLeft="8">
                                   {item.groupitems
                                    |> Array.map(groupitem =>
                                         <MenuItem
                                           top="0"
                                           right="8"
                                           bottom="0"
                                           left="8"
                                           disablePadding={
                                                            groupitem.
                                                              optionPadding
                                                          }
                                           topLeft="12"
                                           topRight="12"
                                           bottomRight="12"
                                           bottomLeft="12"
                                           onClick={_ =>
                                             i
                                             |> clickGroupMenu(
                                                  groupitem.value,
                                                )
                                           }>
                                           {groupitem.value |> string}
                                         </MenuItem>
                                       )
                                    |> array}
                                 </SelectMenu>
                               : null,
                             <IconGeneral
                               animation={item.showGroupMenu |> topDownRorate}
                               src=arrowDownBlack
                             />,
                           )
                      </SelectStandard>
                      <BackgroundBoard
                        showBackground={item.showGroupMenu}
                        backgroundColor="transparent"
                        onClick={_ => i |> showGroupMenu}
                      />
                    </GridItem>
                    <GridItem
                      top="0"
                      right="0"
                      bottom="0"
                      left="0"
                      enterBackgroundColor="transparent"
                      backgroundColor="transparent"
                      xs="auto">
                      <SelectStandard
                        top="12"
                        right="0"
                        left="0"
                        tile={js|人員|js}
                        labelColor="rgba(255,0,0,0.8)"
                        enterBorderColor="rgba(255,0,0,0.8)"
                        downBorderColor="rgba(255,0,0,0.6)"
                        borderColor="rgba(0,0,0,0.2)"
                        value={item.name}
                        disabled={state.showProgress}
                        onClick={_ => i |> showNameMenu}>
                        ...(
                             item.showNameMenu
                               ? <SelectMenu
                                   top="0"
                                   transform="translate(0, 0)"
                                   maxHeight="280"
                                   minHeight="0"
                                   topLeft="12"
                                   topRight="12"
                                   bottomRight="12"
                                   bottomLeft="12"
                                   paddingRight="8"
                                   paddingLeft="8">
                                   {item.nameitems
                                    |> Array.map(nameitem =>
                                         <MenuItem
                                           top="0"
                                           right="8"
                                           bottom="0"
                                           left="8"
                                           disablePadding={nameitem.padding}
                                           topLeft="12"
                                           topRight="12"
                                           bottomRight="12"
                                           bottomLeft="12"
                                           onClick={_ =>
                                             i
                                             |> clickNameMenu(
                                                  nameitem.key,
                                                  nameitem.value,
                                                )
                                           }>
                                           {nameitem.value |> string}
                                         </MenuItem>
                                       )
                                    |> array}
                                 </SelectMenu>
                               : null,
                             <IconGeneral
                               animation={item.showNameMenu |> topDownRorate}
                               src=arrowDownBlack
                             />,
                           )
                      </SelectStandard>
                      <BackgroundBoard
                        showBackground={item.showNameMenu}
                        backgroundColor="transparent"
                        onClick={_ => i |> showNameMenu}
                      />
                    </GridItem>
                  </GridContainer>
                </GridItem>
              )
           |> array}
        </GridContainer>
      </GridItem>
    </NewFacetube>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
