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
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type formitem = {
  newid: string,
  username: string,
  notice: bool,
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
  tabitems: list(tabitem),
  index: int,
  items: array(string),
  showFull: bool,
  formId: string,
  formTitle: string,
  formitems: array(formitem),
  showYoutube: bool,
  youtubeText: string,
};

type action =
  | SettingError
  | SettingFormLoad
  | SettingFormWidth(int, int)
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormItems(array(string))
  | ClickItemTab(int)
  | ShowAnimationFull(string, string, array(formitem))
  | SwitchNotice(int)
  | CloseAnimationFull
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
  | ShowAnimationFull(id, value, formitems) => {
      ...state,
      formId: id,
      formTitle: value,
      formitems,
      showFull: !state.showFull,
    }
  | SwitchNotice(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, notice: !item.notice, formModify: true} : item,
          state.formitems,
        ),
    }
  | CloseAnimationFull => {...state, showFull: !state.showFull}
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
  tabitems: [
    {showTab: true, tabImage: transmissionBlack},
    {showTab: false, tabImage: factoryBlack},
    {showTab: false, tabImage: fileCopyBlack},
  ],
  index: 0,
  items: [||],
  showFull: false,
  formId: "",
  formTitle: "",
  formitems: [||],
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
      state.items
      |> Js_array.length
      |> string_of_int
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.MailistR.search
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

  let clickItemTab =
    useCallback(i =>
      if (i == 1) {
        mailistFPath |> ReasonReactRouter.push;
      } else if (i == 2) {
        mailistIPath |> ReasonReactRouter.push;
      }
    );

  let sItemAJax = value =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.MailistR.sItem
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowAnimationFull(
                 value,
                 response##data##tile,
                 response##data##items,
               )
               |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickFormBoard =
    useCallback(value => {
      ActionShowProgress |> dispatch;
      value |> sItemAJax;
    });

  let insertAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iFormData(
           state.formId,
           state.formTitle,
           Js_array.filter(
             (formitem: formitem) => formitem.formModify === true,
             state.formitems,
           ),
         )
      |> Axiosapi.MailistR.insert
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               CloseAnimationFull |> dispatch;
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

  let switchNotice = useCallback(i => SwitchNotice(i) |> dispatch);

  let closeAnimationFull = useCallback(_ => CloseAnimationFull |> dispatch);

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
            left="0"
            xs="auto">
            <Tabs id="mail-" index={state.index} height="3">
              {state.tabitems
               |> List.mapi((i, tabitem) =>
                    <Tab
                      showTab={tabitem.showTab}
                      maxWidth="111.6"
                      borderRadius="15"
                      id={"mail-" ++ string_of_int(i)}
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
          {state.items
           |> Array.map(item =>
                <div onClick={_ => item |> clickFormBoard}>
                  <GridItem
                    style={ReactDOMRe.Style.make(~cursor="pointer", ())}
                    enterBorderRadius="10"
                    enterBackgroundColor="rgba(0,0,0,0.1)"
                    xs="auto">
                    <Typography variant="subheading">
                      {item |> string}
                    </Typography>
                  </GridItem>
                </div>
              )
           |> array}
        </GridContainer>
      </GridItem>
    </NewFacetube>
    <DialogFull showAnimation={state.showFull}>
      <DialogTitle top="22" left="64">
        <Typography variant="tile" fontWeight="600">
          {state.formTitle |> string}
        </Typography>
      </DialogTitle>
      <DialogContent>
        <DialogContentText>
          <GridItem
            style=marginAuto
            top="0"
            right="0"
            bottom="0"
            left="54"
            xs="12"
            maxWidth="770px">
            <GridContainer
              direction="column" justify="center" alignItem="stretch">
              <GridItem
                style={ReactDOMRe.Style.make(
                  ~position="sticky",
                  ~top="0px",
                  ~zIndex="1000",
                  (),
                )}
                top="0"
                bottom="6"
                left="0"
                xs="auto">
                <GridContainer
                  direction="rowReverse" justify="center" alignItem="center">
                  <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                    <Button disabled={state.showProgress} onClick=insertForm>
                      <FormattedMessage id="save" defaultMessage="Save" />
                    </Button>
                  </GridItem>
                  <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                    null
                  </GridItem>
                </GridContainer>
              </GridItem>
              {state.formitems
               |> Array.mapi((i, item) =>
                    <GridItem
                      style={ReactDOMRe.Style.make(~cursor="pointer", ())}
                      enterBorderRadius="10"
                      enterBackgroundColor="rgba(0,0,0,0.1)"
                      xs="auto">
                      <GridContainer
                        backgroundColor="transparent"
                        direction="row"
                        justify="around"
                        alignItem="center">
                        <GridItem
                          top="0"
                          right="0"
                          bottom="0"
                          left="0"
                          backgroundColor="transparent"
                          enterBackgroundColor="transparent"
                          xs="auto">
                          <Typography variant="subheading">
                            {item.username |> string}
                          </Typography>
                        </GridItem>
                        <GridItem
                          top="0"
                          right="0"
                          bottom="0"
                          left="0"
                          backgroundColor="transparent"
                          enterBackgroundColor="transparent"
                          xs="no">
                          <Switch
                            right="0"
                            checked={item.notice}
                            circleColor={item.notice |> circle}
                            linearColor={item.notice |> linear}
                            fontColor={item.notice |> font}
                            disabled={state.showProgress}
                            onClick={_ => i |> switchNotice}>
                            {{js|需通知人員|js} |> string}
                          </Switch>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                  )
               |> array}
            </GridContainer>
          </GridItem>
        </DialogContentText>
      </DialogContent>
      <DialogActions>
        <div
          style={ReactDOMRe.Style.make(
            ~position="fixed",
            ~top="10px",
            ~left="10px",
            (),
          )}>
          <IconButton
            padding="12"
            disabled={state.showProgress}
            onClick=closeAnimationFull>
            <Tooltip location="bottom" backgroundColor="rgba(255,0,0,0.8)">
              <FormattedMessage id="closed" defaultMessage="Closed" />
            </Tooltip>
            <IconAction animation="circle" src=clearBlack />
          </IconButton>
        </div>
      </DialogActions>
    </DialogFull>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
