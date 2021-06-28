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
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type grotoitem = {
  grotoId: int,
  grotoImage: bool,
  grotoVideo: bool,
  grotoAudio: bool,
  grotoSrc: string,
  grotoPath: string,
  grotoOriginal: string,
  grotoEncryption: string,
  grotoExtension: string,
  grotoName: string,
  grotoDate: string,
};

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

type mbitem = {
  mbId: int,
  mbValue: string,
};

type item = {
  postdate: string,
  postinfo: string,
  case: string,
  homepage1: string,
  pnumber: string,
  endDate: string,
  obj: string,
  homepageMomo: string,
  mb: string,
  amount: string,
  subject: string,
  ecr: string,
  ecn: string,
  type_: string,
  body: string,
  mailitems: array(mbitem),
  action1: string,
  workitems: array(mbitem),
  action2: string,
  mbitems: array(mbitem),
  oldno: string,
  newno: string,
  sopno: string,
  action3: string,
  sipno: string,
  action4: string,
  action5: string,
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
  grotoitems: array(grotoitem),
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
  | SettingGrotoItems(array(grotoitem))
  | ClickItemTab(int)
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
  | SettingGrotoItems(items) => {...state, grotoitems: items}
  | ClickItemTab(index) => {
      ...state,
      tabitems:
        List.mapi(
          (i, tabitem) => {...tabitem, showTab: index == i},
          state.tabitems,
        ),
      index,
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
    {showTab: false, tabImage: groupBlack},
  ],
  index: 0,
  items: [||],
  photoitems: [||],
  grotoitems: [||],
  showYoutube: false,
  youtubeText: "",
};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);

  let textRef = useRef(Js.Nullable.null);

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
      |> Axiosapi.SignlistF.search
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
      |> Axiosapi.SignlistF.sFile
      |> then_(response =>
           SettingPhotoItems(response##data##items) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let sGrotoAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Axiosapi.SignlistF.sGroto
      |> then_(response =>
           SettingGrotoItems(response##data##items) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickItemTab =
    useCallback(i => {
      ClickItemTab(i) |> dispatch;
      if (i == 1) {
        sFileAJax();
      } else if (i == 2) {
        sGrotoAJax();
      };
    });

  let signinAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Axiosapi.SignlistF.send
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
      |> Axiosapi.SignlistF.back
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
             |> Array.map(item =>
                  <>
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
                            {{js|發文資訊|js} |> string}
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
                            value={item.case}
                            disabled=true>
                            {{js|變更內容|js} |> string}
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
                            {{js|訂單號碼|js} |> string}
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
                            value={item.endDate}
                            disabled=true>
                            {{js|文件有效期限|js} |> string}
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
                            value={item.obj}
                            disabled=true>
                            {{js|影響站別|js} |> string}
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
                            value={item.amount}
                            disabled=true>
                            {{js|生產數量|js} |> string}
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
                        value={item.subject}
                        disabled=true>
                        {{js|主旨|js} |> string}
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
                            value={item.ecr}
                            disabled=true>
                            {"ECR" |> string}
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
                            value={item.ecn}
                            disabled=true>
                            {"ECN" |> string}
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
                            value={item.type_}
                            disabled=true>
                            {{js|類型|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem left="0" xs="auto">
                      <TextFieldArticle textRef disabled=true />
                    </GridItem>
                    <GridItem top="0" right="6" bottom="6" left="6" xs="auto">
                      <GridContainer
                        direction="row" justify="start" alignItem="center">
                        {item.mailitems
                         |> Array.map(mailitem =>
                              <GridItem top="0" bottom="0" left="0" xs="no">
                                <Chip
                                  enterBorderWidth="0"
                                  downBorderWidth="0"
                                  borderWidth="0">
                                  ...(
                                       <Typography variant="subtitle2">
                                         {"S" |> string}
                                       </Typography>,
                                       <Typography variant="subtitle2">
                                         {mailitem.mbValue |> string}
                                       </Typography>,
                                     )
                                </Chip>
                              </GridItem>
                            )
                         |> array}
                      </GridContainer>
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
                        value={item.action1}
                        disabled=true>
                        {{js|資材處|js} |> string}
                      </TextFieldMultiline>
                    </GridItem>
                    <GridItem top="0" right="6" bottom="6" left="6" xs="auto">
                      <GridContainer
                        direction="row" justify="start" alignItem="center">
                        {item.workitems
                         |> Array.map(workitem =>
                              <GridItem top="0" bottom="0" left="0" xs="no">
                                <Chip
                                  enterBorderWidth="0"
                                  downBorderWidth="0"
                                  borderWidth="0">
                                  ...(
                                       <Typography variant="subtitle2">
                                         {"S" |> string}
                                       </Typography>,
                                       <Typography variant="subtitle2">
                                         {workitem.mbValue |> string}
                                       </Typography>,
                                     )
                                </Chip>
                              </GridItem>
                            )
                         |> array}
                      </GridContainer>
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
                        value={item.action2}
                        disabled=true>
                        {{js|工程處|js} |> string}
                      </TextFieldMultiline>
                    </GridItem>
                    <GridItem top="0" right="6" bottom="6" left="6" xs="auto">
                      <GridContainer
                        direction="row" justify="start" alignItem="center">
                        {item.mbitems
                         |> Array.map(mbitem =>
                              <GridItem top="0" bottom="0" left="0" xs="no">
                                <Chip
                                  enterBorderWidth="0"
                                  downBorderWidth="0"
                                  borderWidth="0">
                                  ...(
                                       <Typography variant="subtitle2">
                                         {"S" |> string}
                                       </Typography>,
                                       <Typography variant="subtitle2">
                                         {mbitem.mbValue |> string}
                                       </Typography>,
                                     )
                                </Chip>
                              </GridItem>
                            )
                         |> array}
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
                            value={item.oldno}
                            disabled=true>
                            {{js|舊料號|js} |> string}
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
                            value={item.newno}
                            disabled=true>
                            {{js|新料號|js} |> string}
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
                            value={item.sopno}
                            disabled=true>
                            {{js|SOP文件編號|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                      </GridContainer>
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
                        value={item.action3}
                        disabled=true>
                        {{js|品保處|js} |> string}
                      </TextFieldMultiline>
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
                        value={item.sipno}
                        disabled=true>
                        {{js|SIP文件編號|js} |> string}
                      </TextFieldMultiline>
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
                        value={item.action4}
                        disabled=true>
                        {{js|生產處|js} |> string}
                      </TextFieldMultiline>
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
                        value={item.action5}
                        disabled=true>
                        {{js|不知道|js} |> string}
                      </TextFieldMultiline>
                    </GridItem>
                  </>
                )
             |> array
           | 1 =>
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
           | _ =>
             <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
               <GridContainer
                 direction="columnReverse"
                 justify="center"
                 alignItem="stretch">
                 {state.grotoitems
                  |> Array.mapi((i, grotoitem) =>
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
                                  grotoitem.grotoImage,
                                  grotoitem.grotoVideo,
                                  grotoitem.grotoAudio,
                                ) {
                                | (true, _, _) =>
                                  <Image
                                    width="auto"
                                    height="300px"
                                    borderRadius="6"
                                    src={
                                      grotoitem.grotoPath ++ grotoitem.grotoSrc
                                    }
                                  />
                                | (_, true, _) =>
                                  <Media
                                    width="auto"
                                    borderRadius="6"
                                    controls=true
                                    src={
                                      grotoitem.grotoPath ++ grotoitem.grotoSrc
                                    }
                                  />
                                | (_, _, true) =>
                                  <Media
                                    variant="audio"
                                    width="auto"
                                    borderRadius="6"
                                    controls=true
                                    src={
                                      grotoitem.grotoPath ++ grotoitem.grotoSrc
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
                                 {grotoitem.grotoOriginal
                                  ++ grotoitem.grotoExtension
                                  ++ "("
                                  ++ grotoitem.grotoName
                                  ++ ")"
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
