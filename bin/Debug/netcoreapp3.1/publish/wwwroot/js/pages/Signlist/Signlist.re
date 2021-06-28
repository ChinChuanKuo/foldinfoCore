open React;
open Together;
open Data;
open Axiosapi;
open Status;
open Storage;
open ObjectFormat;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type item = {
  id: string,
  tile: string,
  subject: string,
  postdate: string,
  postGroup: string,
  postName: string,
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
  items: array(item),
  showYoutube: bool,
  youtubeText: string,
};

type action =
  | SettingError
  | SettingFormLoad
  | SettingFormWidth(int, int)
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormItems(array(item))
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
      |> Axiosapi.Signlist.search
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
    if (state.formLoad) {
      Some(() => "action" |> Js.log);
    } else {
      let testtime = SettingFormLoad |> dispatch;
      let sizeId =
        SettingFormWidth(Window.Sizes.width, Window.Sizes.height) |> dispatch;
      let testId =
        switch ("form" |> Sessions.select |> checkObjects) {
        | "signInSuccess"
        | "signOutSuccess" =>
          "form"
          |> Sessions.select
          |> checkObjects
          |> signModels
          |> barShowRestoreAction;
          "" |> Sessions.create("form");
        | _ => "action" |> Js.log
        };
      let timeId = permissAJax();
      Some(
        () => {
          testtime;
          sizeId;
          testId;
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

  let clickFormBoard = useCallback(id => id |> ReasonReactRouter.push);

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
          {state.items
           |> Array.map(item =>
                <>
                  <GridItem
                    top="0"
                    right="0"
                    bottom="0"
                    left="0"
                    cursor="pointer"
                    enterBorderRadius="10"
                    borderRadius="10"
                    enterBackgroundColor="rgba(0,0,0,0.1)"
                    xs="auto"
                    onClick={_ => item.id |> clickFormBoard}>
                    <GridContainer
                      backgroundColor="none"
                      direction="column"
                      justify="center"
                      alignItem="stretch">
                      <GridItem
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <Typography variant="tile" fontWeight="600">
                          {item.tile |> string}
                        </Typography>
                      </GridItem>
                      <GridItem
                        top="0"
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <Typography variant="subheading">
                          {item.subject |> string}
                        </Typography>
                      </GridItem>
                      <GridItem
                        top="0"
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <GridContainer
                          backgroundColor="none"
                          direction="row"
                          justify="start"
                          alignItem="center">
                          <GridItem
                            top="0"
                            bottom="0"
                            left="0"
                            enterBackgroundColor="none"
                            backgroundColor="none"
                            xs="no">
                            <Typography variant="subheading" color="#606060">
                              {item.postdate |> string}
                            </Typography>
                          </GridItem>
                          <GridItem
                            top="0"
                            bottom="0"
                            left="0"
                            enterBackgroundColor="none"
                            backgroundColor="none"
                            xs="no">
                            <Typography variant="subheading" color="#606060">
                              {item.postGroup |> string}
                            </Typography>
                          </GridItem>
                          <GridItem
                            top="0"
                            bottom="0"
                            left="0"
                            enterBackgroundColor="none"
                            backgroundColor="none"
                            xs="no">
                            <Typography variant="subheading" color="#606060">
                              {item.postName |> string}
                            </Typography>
                          </GridItem>
                        </GridContainer>
                      </GridItem>
                    </GridContainer>
                  </GridItem>
                  <GridItem top="6" right="0" bottom="6" left="0" xs="auto">
                    <Divider />
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
