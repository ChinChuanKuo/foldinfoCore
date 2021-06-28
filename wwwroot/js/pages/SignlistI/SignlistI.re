open React;
open Together;
open ReactIntl;
open Path;
open Data;
open Axiosapi;
open Status;
open Storage;
open SwitchColor;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type mbitem = {
  mbId: int,
  mbValue: string,
};

type item = {
  postdate: string,
  postinfo: string,
  subject: string,
  obj: string,
  homepageMomo: string,
  mbitems: array(mbitem),
  pageitems: array(mbitem),
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
  showPdfFile: bool,
  showPdfImage: bool,
  showPdfVideo: bool,
  showPdfAudio: bool,
  pdfSrc: string,
  pdfPath: string,
  pdfOriginal: string,
  pdfEncryption: string,
  pdfExtension: string,
  pdfDate: string,
  body: string,
  releaseDate: string,
  limit: bool,
  endDate: string,
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
  items: array(item),
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

  let searchAJax = formId =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(formId)
      |> Axiosapi.SignlistI.search
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

  let signinAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Axiosapi.SignlistI.send
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
      |> Axiosapi.SignlistI.back
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
            <GridContainer
              direction="rowReverse" justify="around" alignItem="center">
              <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                <Button disabled={state.showProgress} onClick=signoutForm>
                  <FormattedMessage
                    id="Signlist.signout"
                    defaultMessage="Signout"
                  />
                </Button>
              </GridItem>
              <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                <Button disabled={state.showProgress} onClick=signinForm>
                  <FormattedMessage
                    id="Signlist.signin"
                    defaultMessage="Signin"
                  />
                </Button>
              </GridItem>
              <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                null
              </GridItem>
            </GridContainer>
          </GridItem>
          {state.items
           |> Array.map(item =>
                <>
                  <GridItem
                    style={ReactDOMRe.Style.make(~height="50px", ())}
                    top="0"
                    right="6"
                    bottom="0"
                    left="6"
                    xs="auto">
                    <GridContainer
                      direction="row" justify="center" alignItem="center">
                      <GridItem
                        top="25" right="0" bottom="0" left="0" xs="auto">
                        <Typography variant="subheading" fontWeight="bolder">
                          {item.postdate |> string}
                        </Typography>
                      </GridItem>
                      <GridItem
                        top="25" right="0" bottom="0" left="0" xs="auto">
                        <Typography variant="subheading" fontWeight="bolder">
                          {item.postinfo |> string}
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
                      {{js|文件名稱|js} |> string}
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
                          value={item.obj}
                          disabled=true>
                          {{js|製程別|js} |> string}
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
                    </GridContainer>
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
                  <GridItem top="0" right="6" bottom="6" left="6" xs="auto">
                    <GridContainer
                      direction="row" justify="start" alignItem="center">
                      {item.pageitems
                       |> Array.map(pageitem =>
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
                                       {pageitem.mbValue |> string}
                                     </Typography>,
                                   )
                              </Chip>
                            </GridItem>
                          )
                       |> array}
                    </GridContainer>
                  </GridItem>
                  <GridItem right="0" left="0" xs="auto">
                    <GridContainer
                      direction="row" justify="center" alignItem="center">
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        null
                      </GridItem>
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        null
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
                      value={item.body}
                      disabled=true>
                      {{js|說明|js} |> string}
                    </TextFieldMultiline>
                  </GridItem>
                  <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                    <GridContainer
                      direction="rowReverse"
                      justify="center"
                      alignItem="center">
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        <Switch
                          right="0"
                          checked={item.limit}
                          circleColor={item.limit |> circle}
                          linearColor={item.limit |> linear}
                          fontColor={item.limit |> font}
                          disabled=true>
                          {{js|限期|js} |> string}
                        </Switch>
                      </GridItem>
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        <Switch
                          right="0"
                          checked={!item.limit}
                          circleColor={!item.limit |> circle}
                          linearColor={!item.limit |> linear}
                          fontColor={!item.limit |> font}
                          disabled=true>
                          {{js|無限期|js} |> string}
                        </Switch>
                      </GridItem>
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        null
                      </GridItem>
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        null
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
                          value={item.releaseDate}
                          disabled=true>
                          {{js|發行日期|js} |> string}
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
                          {{js|到期日|js} |> string}
                        </TextFieldStandard>
                      </GridItem>
                    </GridContainer>
                  </GridItem>
                </>
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
