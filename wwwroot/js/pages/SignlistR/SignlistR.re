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
open SwitchColor;
open IconAnimation;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type photoitem = {
  photoId: int,
  photoImage: bool,
  photoVideo: bool,
  photoAudio: bool,
  photoSrc: string,
  photoPath: string,
  photoOriginal: string,
  photoEncryption: string,
  photoExtension: string,
  photoDate: string,
};

type item = {
  postdate: string,
  postinfo: string,
  floor: string,
  workno: string,
  homepage1: string,
  pnumber: string,
  homepageMomo: string,
  mb: string,
  obj: string,
  pn: string,
  amount: string,
  invest: string,
  fail: string,
  subject: string,
  containment: string,
  cause: string,
  showRegroupMenu: bool,
  regroupitems: array(optionitem),
  reGroup: string,
  showReplierMenu: bool,
  replieritems: array(optionitem),
  replier: string,
  issuesort: string,
  causeclass: string,
  directPt: string,
  indirectPt: string,
  correctiveaction1: string,
  correctiveaction2: string,
  showFile: bool,
  showImage: bool,
  showVideo: bool,
  showAudio: bool,
  src: string,
  path: string,
  original: string,
  encryption: string,
  extension: string,
  date: string,
  closure: string,
  body: string,
  notice: bool,
  nonstatistical: bool,
  belong: string,
  belonger: string,
  stage: string,
  releasedate: string,
  formEdit: bool,
  formModify: bool,
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
  formId: string,
  tile: string,
  tabitems: list(tabitem),
  index: int,
  items: array(item),
  photoitems: array(photoitem),
  showYoutube: bool,
  youtubeText: string,
};

type action =
  | SettingError
  | SettingFormLoad(string)
  | SettingFormWidth(int, int)
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormItems(string, string, array(item))
  | SettingPhotoItems(array(photoitem))
  | ClickItemTab(int)
  | ShowRegroupMenu(int)
  | ClickRegroupMenu(string, int)
  | ShowReplierMenu(int)
  | SettingItemReplier(array(optionitem), int)
  | ClickReplierMenu(string, int)
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingError => {...state, error: !state.error}
  | SettingFormLoad(value) => {
      ...state,
      formId: value,
      formLoad: !state.formLoad,
    }
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
  | SettingFormItems(formId, tile, items) => {...state, formId, tile, items}
  | SettingPhotoItems(items) => {...state, photoitems: items}
  | ClickItemTab(index) => {
      ...state,
      tabitems:
        List.mapi(
          (i, tabitem) => {...tabitem, showTab: index == i},
          state.tabitems,
        ),
      index,
    }
  | ShowRegroupMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showRegroupMenu: !item.showRegroupMenu} : item,
          state.items,
        ),
    }
  | ClickRegroupMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                reGroup: value,
                showRegroupMenu: !item.showRegroupMenu,
                formModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ShowReplierMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showReplierMenu: !item.showReplierMenu} : item,
          state.items,
        ),
    }
  | SettingItemReplier(items, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, replieritems: items} : item,
          state.items,
        ),
    }
  | ClickReplierMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                replier: value,
                showReplierMenu: !item.showReplierMenu,
                formModify: true,
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
  formId: "",
  tile: "",
  tabitems: [
    {showTab: true, tabImage: bookBlack},
    {showTab: false, tabImage: collectionsBlack},
  ],
  index: 0,
  items: [||],
  photoitems: [||],
  showYoutube: false,
  youtubeText: "",
};

let defaultFloat = value =>
  switch (value) {
  | "" => "0.0"
  | _ => value
  };

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);
  let barShowRestoreAction = youtubeText => {
    ActionSnackBar(youtubeText, true) |> dispatch;
    Js.Global.setTimeout(() => ActionSnackBar("", false) |> dispatch, 5000)
    |> ignore;
  };

  let searchAJax = formId =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(formId)
      |> Axiosapi.SignlistR.search
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               SettingFormItems(
                 response##data##formId,
                 response##data##tile,
                 response##data##items,
               )
               |> dispatch;
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
             ReasonReactRouter.dangerouslyGetInitialUrl().hash |> searchAJax;
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  useEffect(() =>
    if (state.formLoad) {
      Some(() => "action" |> Js.log);
    } else {
      let testtime =
        SettingFormLoad(ReasonReactRouter.dangerouslyGetInitialUrl().hash)
        |> dispatch;
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
    let watchId =
      ReasonReactRouter.watchUrl(_ => {
        SettingFormLoad(ReasonReactRouter.dangerouslyGetInitialUrl().hash)
        |> dispatch;
        ActionShowProgress |> dispatch;
      });
    let sizeId = Window.Listeners.add("resize", handleResize, true) |> ignore;
    /*let scrollId =
      Window.Listeners.add("scroll", handleScrollBar, true) |> ignore;*/
    Some(
      () => {
        watchId |> ReasonReactRouter.unwatchUrl;
        sizeId;
      },
    );
  });

  let sFileAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Axiosapi.SignlistR.sFile
      |> then_(response =>
           SettingPhotoItems(response##data##items) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickItemTab =
    useCallback(i => {
      ClickItemTab(i) |> dispatch;
      if (i == 1) {
        sFileAJax();
      };
    });

  let showRegroupMenu = useCallback(i => ShowRegroupMenu(i) |> dispatch);

  let sRegroupAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> CreateR.sGroup
      |> then_(response => {
           SettingItemReplier(response##data##items, i) |> dispatch |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickRegroupMenu =
    useCallback((value, i) => {
      ClickRegroupMenu(value, i) |> dispatch;
      i |> sRegroupAJax(value);
    });

  let showReplierMenu = useCallback(i => ShowReplierMenu(i) |> dispatch);

  let clickReplierMenu =
    useCallback((value, i) => ClickReplierMenu(value, i) |> dispatch);

  let signinAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iFormData(
           state.formId,
           "",
           Js_array.filter(
             (item: item) => item.formModify === true,
             state.items,
           ),
         )
      |> Axiosapi.SignlistR.send
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               "signInSuccess" |> Sessions.create("form");
               signlistPath |> ReasonReactRouter.push;
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

  let signinForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      signinAJax();
    });

  let signoutAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Axiosapi.SignlistR.back
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               "signOutSuccess" |> Sessions.create("form");
               signlistPath |> ReasonReactRouter.push;
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

  let signoutForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      signoutAJax();
    });

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
            left="0"
            xs="auto">
            <GridContainer direction="row" justify="around" alignItem="center">
              <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                <Tabs id="report-" index={state.index} height="3">
                  {state.tabitems
                   |> List.mapi((i, tabitem) =>
                        <Tab
                          showTab={tabitem.showTab}
                          maxWidth="111.6"
                          borderRadius="15"
                          id={"report-" ++ string_of_int(i)}
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
              <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                <Button disabled={state.showProgress} onClick=signinForm>
                  <FormattedMessage
                    id="Signlist.signin"
                    defaultMessage="Signin"
                  />
                </Button>
              </GridItem>
              <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                <Button disabled={state.showProgress} onClick=signoutForm>
                  <FormattedMessage
                    id="Signlist.signout"
                    defaultMessage="Signout"
                  />
                </Button>
              </GridItem>
            </GridContainer>
          </GridItem>
          {switch (state.index) {
           | 0 =>
             state.items
             |> Array.mapi((i, item) =>
                  <>
                    <GridItem top="18" bottom="0" left="0" xs="auto">
                      <Typography
                        variant="subheading"
                        color="rgba(0,0,0,0.6)"
                        fontWeight="bolder">
                        {{js|【Characterize】問題描述|js} |> string}
                      </Typography>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="20" right="0" bottom="6" left="6" xs="auto">
                          <Typography variant="subheading" fontWeight="bolder">
                            {item.postdate |> string}
                          </Typography>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.postinfo}
                            disabled=true>
                            {{js|提出資訊|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.floor}
                            disabled=true>
                            {{js|生產樓層|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.workno}
                            disabled=true>
                            {{js|工單|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.homepage1}
                            disabled=true>
                            {{js|客戶|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.pnumber}
                            disabled=true>
                            {{js|產品規格單|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.homepageMomo}
                            disabled=true>
                            {{js|機種|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.mb}
                            disabled=true>
                            {"M/B" |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.obj}
                            disabled=true>
                            {{js|品異來源|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <TextFieldStandard
                        top="12"
                        right="0"
                        left="0"
                        labelColor="rgba(255,0,0,0.8)"
                        enterBorderColor="rgba(255,0,0,0.8)"
                        downBorderColor="rgba(255,0,0,0.6)"
                        borderColor="rgba(0,0,0,0.2)"
                        value={item.pn}
                        disabled=true>
                        {{js|不良料號|js} |> string}
                      </TextFieldStandard>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.amount}
                            disabled=true>
                            {{js|工單總數|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.invest}
                            disabled=true>
                            {{js|投入數|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.fail}
                            disabled=true>
                            {{js|不良數量|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="20" right="0" bottom="0" left="0" xs="auto">
                          <Typography variant="subheading" fontWeight="bolder">
                            {{js|不良率:|js}
                             ++ string_of_float(
                                  float_of_int(
                                    Math.round(
                                      float_of_string(
                                        item.fail |> defaultFloat,
                                      )
                                      /. float_of_string(
                                           item.invest |> defaultFloat,
                                         )
                                      *. 10000.0,
                                    ),
                                  )
                                  /. 100.0,
                                )
                             ++ "%"
                             |> string}
                          </Typography>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <TextFieldStandard
                        top="12"
                        right="0"
                        left="0"
                        labelColor="rgba(255,0,0,0.8)"
                        enterBorderColor="rgba(255,0,0,0.8)"
                        downBorderColor="rgba(255,0,0,0.6)"
                        borderColor="rgba(0,0,0,0.2)"
                        value={item.subject}
                        disabled=true>
                        {{js|異常內容|js} |> string}
                      </TextFieldStandard>
                    </GridItem>
                    <GridItem top="18" bottom="0" left="0" xs="auto">
                      <Typography
                        variant="subheading"
                        color="rgba(0,0,0,0.6)"
                        fontWeight="bolder">
                        {{js|【Containment】緊急處置|js} |> string}
                      </Typography>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <TextFieldMultiline
                        top="12"
                        right="0"
                        left="0"
                        labelColor="rgba(255,0,0,0.8)"
                        enterBorderColor="rgba(255,0,0,0.8)"
                        downBorderColor="rgba(255,0,0,0.6)"
                        borderColor="rgba(0,0,0,0.2)"
                        rows=3
                        value={item.containment}
                        disabled=true>
                        null
                      </TextFieldMultiline>
                    </GridItem>
                    <GridItem top="18" bottom="0" left="0" xs="auto">
                      <Typography
                        variant="subheading"
                        color="rgba(0,0,0,0.6)"
                        fontWeight="bolder">
                        {{js|【Cause】真因調查|js} |> string}
                      </Typography>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <TextFieldMultiline
                        top="12"
                        right="0"
                        left="0"
                        labelColor="rgba(255,0,0,0.8)"
                        enterBorderColor="rgba(255,0,0,0.8)"
                        downBorderColor="rgba(255,0,0,0.6)"
                        borderColor="rgba(0,0,0,0.2)"
                        rows=3
                        value={item.cause}
                        disabled=true>
                        null
                      </TextFieldMultiline>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <SelectStandard
                            top="12"
                            right="0"
                            left="0"
                            tile={js|處理部門|js}
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.reGroup}
                            disabled={state.showProgress || item.formEdit || !state.update}
                            onClick={_ => i |> showRegroupMenu}>
                            ...(
                                 item.showRegroupMenu
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
                                       {item.regroupitems
                                        |> Array.map(regroupitem =>
                                             <MenuItem
                                               top="0"
                                               right="8"
                                               bottom="0"
                                               left="8"
                                               disablePadding={
                                                                regroupitem.
                                                                  optionPadding
                                                              }
                                               topLeft="12"
                                               topRight="12"
                                               bottomRight="12"
                                               bottomLeft="12"
                                               onClick={_ =>
                                                 i
                                                 |> clickRegroupMenu(
                                                      regroupitem.value,
                                                    )
                                               }>
                                               {regroupitem.value |> string}
                                             </MenuItem>
                                           )
                                        |> array}
                                     </SelectMenu>
                                   : null,
                                 <IconGeneral
                                   animation={
                                     item.showRegroupMenu |> topDownRorate
                                   }
                                   src=arrowDownBlack
                                 />,
                               )
                          </SelectStandard>
                          <BackgroundBoard
                            showBackground={item.showRegroupMenu}
                            backgroundColor="transparent"
                            onClick={_ => i |> showRegroupMenu}
                          />
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <SelectStandard
                            top="12"
                            right="0"
                            left="0"
                            tile={js|處理者|js}
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.replier}
                            disabled={state.showProgress || item.formEdit || !state.update}
                            onClick={_ => i |> showReplierMenu}>
                            ...(
                                 item.showReplierMenu
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
                                       {item.replieritems
                                        |> Array.map(replieritem =>
                                             <MenuItem
                                               top="0"
                                               right="8"
                                               bottom="0"
                                               left="8"
                                               disablePadding={
                                                                replieritem.
                                                                  optionPadding
                                                              }
                                               topLeft="12"
                                               topRight="12"
                                               bottomRight="12"
                                               bottomLeft="12"
                                               onClick={_ =>
                                                 i
                                                 |> clickReplierMenu(
                                                      replieritem.value,
                                                    )
                                               }>
                                               {replieritem.value |> string}
                                             </MenuItem>
                                           )
                                        |> array}
                                     </SelectMenu>
                                   : null,
                                 <IconGeneral
                                   animation={
                                     item.showReplierMenu |> topDownRorate
                                   }
                                   src=arrowDownBlack
                                 />,
                               )
                          </SelectStandard>
                          <BackgroundBoard
                            showBackground={item.showReplierMenu}
                            backgroundColor="transparent"
                            onClick={_ => i |> showReplierMenu}
                          />
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.issuesort}
                            disabled=true>
                            {{js|原因分類|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.causeclass}
                            disabled=true>
                            {{js|原因分類|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.directPt}
                            disabled=true>
                            {{js|直接損耗工時|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.indirectPt}
                            disabled=true>
                            {{js|間接損耗工時|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="18" bottom="6" left="0" xs="auto">
                      <Typography
                        variant="subheading"
                        color="rgba(0,0,0,0.6)"
                        fontWeight="bolder">
                        {{js|【Corrective Action】改善對策|js} |> string}
                      </Typography>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldMultiline
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            rows=3
                            value={item.correctiveaction1}
                            disabled=true>
                            {"Short Term" |> string}
                          </TextFieldMultiline>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldMultiline
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            rows=3
                            value={item.correctiveaction2}
                            disabled=true>
                            {"Long Term" |> string}
                          </TextFieldMultiline>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      null
                    </GridItem>
                    <GridItem top="18" bottom="0" left="0" xs="auto">
                      <Typography
                        variant="subheading"
                        color="rgba(0,0,0,0.6)"
                        fontWeight="bolder">
                        {{js|【Closure】成效驗證|js} |> string}
                      </Typography>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <Switch
                            right="0"
                            checked={item.notice}
                            circleColor={item.notice |> circle}
                            linearColor={item.notice |> linear}
                            fontColor={item.notice |> font}
                            disabled=true>
                            {{js|列入注意事項|js} |> string}
                          </Switch>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <Switch
                            right="0"
                            checked={item.nonstatistical}
                            circleColor={item.nonstatistical |> circle}
                            linearColor={item.nonstatistical |> linear}
                            fontColor={item.nonstatistical |> font}
                            disabled=true>
                            {{js|不列入統計資料|js} |> string}
                          </Switch>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldMultiline
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            rows=3
                            value={item.closure}
                            disabled=true>
                            null
                          </TextFieldMultiline>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldMultiline
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            rows=3
                            value={item.body}
                            disabled=true>
                            null
                          </TextFieldMultiline>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.belong}
                            disabled=true>
                            {{js|責任單位|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.belonger}
                            disabled=true>
                            {{js|責任人員|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.stage}
                            disabled=true>
                            {{js|處理狀態|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="20" right="0" bottom="0" left="0" xs="auto">
                          <Typography variant="subheading" fontWeight="bolder">
                            {{js|結案日期:|js}
                             ++ item.releasedate
                             |> string}
                          </Typography>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                  </>
                )
             |> array
           | _ =>
             <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
               <GridContainer
                 direction="columnReverse"
                 justify="center"
                 alignItem="stretch">
                 {state.photoitems
                  |> Array.map(photoitem =>
                       <>
                         <GridItem
                           enterBorderRadius="15"
                           borderRadius="15"
                           enterBackgroundColor="rgba(255,255,255,1)"
                           backgroundColor="rgba(255,255,255,1)"
                           xs="auto">
                           <GridContainer
                             backgroundColor="transparent"
                             direction="columnReverse"
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
                               {switch (
                                  photoitem.photoImage,
                                  photoitem.photoVideo,
                                  photoitem.photoAudio,
                                ) {
                                | (true, _, _) =>
                                  <Image
                                    width="auto"
                                    height="300px"
                                    borderRadius="6"
                                    src={
                                      photoitem.photoPath ++ photoitem.photoSrc
                                    }
                                  />
                                | (_, true, _) =>
                                  <Media
                                    width="auto"
                                    borderRadius="6"
                                    controls=true
                                    src={
                                      photoitem.photoPath ++ photoitem.photoSrc
                                    }
                                  />
                                | (_, _, true) =>
                                  <Media
                                    variant="audio"
                                    width="auto"
                                    borderRadius="6"
                                    controls=true
                                    src={
                                      photoitem.photoPath ++ photoitem.photoSrc
                                    }
                                  />
                                | (_, _, _) => null
                                }}
                             </GridItem>
                             <GridItem
                               top="0"
                               right="0"
                               bottom="6"
                               left="0"
                               enterBackgroundColor="transparent"
                               backgroundColor="transparent"
                               xs="auto">
                               <Typography
                                 variant="subheading"
                                 color="rgba(0,0,0,1)"
                                 noWrap=true>
                                 {photoitem.photoOriginal
                                  ++ photoitem.photoExtension
                                  |> string}
                               </Typography>
                             </GridItem>
                           </GridContainer>
                         </GridItem>
                         <GridItem right="24" left="24" xs="auto">
                           <Divider />
                         </GridItem>
                       </>
                     )
                  |> array}
               </GridContainer>
             </GridItem>
           }}
        </GridContainer>
      </GridItem>
    </NewFacetube>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
