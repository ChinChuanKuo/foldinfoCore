open React;
open Data;
open Axiosapi;
open Storage;

type state = {
  formLoad: bool,
  error: bool,
  loading: bool,
  showYoutube: bool,
  youtubeText: string,
  disabled: bool,
  code: string,
};

type action =
  | SettingFormLoad
  | ChangeCode(string)
  | ActionOtherLoad(bool)
  | ActionErrorLoad(bool)
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingFormLoad => {...state, formLoad: !state.formLoad}
  | ChangeCode(value) => {...state, code: value}
  | ActionOtherLoad(other) => {...state, disabled: other, loading: other}
  | ActionErrorLoad(error) => {...state, error}
  | ActionSnackBar(youtubeText, showYoutube) => {
      ...state,
      youtubeText,
      showYoutube,
    }
  };

let initialState = {
  formLoad: false,
  error: false,
  loading: false,
  showYoutube: false,
  youtubeText: "",
  disabled: false,
  code: "",
};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);

  let checkNewAJax = () =>
    Js.Promise.(
      "newid"
      |> Sessions.select
      |> userData
      |> Form.checkNew
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" => "check" |> Js.log
             | _ => Path.loginPath |> ReasonReactRouter.push
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
      let testId = SettingFormLoad |> dispatch;
      let timeId = checkNewAJax();
      Some(
        () => {
          testId;
          timeId;
        },
      );
    }
  );

  let changeCode = useCallback(value => ChangeCode(value) |> dispatch);

  let restoreAction = () => {
    ActionErrorLoad(true) |> dispatch;
    Js.Global.setTimeout(
      () => {
        ActionErrorLoad(false) |> dispatch;
        ActionOtherLoad(false) |> dispatch;
      },
      500,
    )
    |> ignore;
  };

  let barShowRestoreAction = youtubeText => {
    ActionSnackBar(youtubeText, true) |> dispatch;
    Js.Global.setTimeout(() => ActionSnackBar("", false) |> dispatch, 5000)
    |> ignore;
  };

  let codeUserAJax = () =>
    Js.Promise.(
      state.code
      |> otherData("newid" |> Sessions.select)
      |> Axiosapi.Code.codeUser
      |> then_(response => {
           (
             switch (response##data##status) {
             | "nousers" => Path.loginPath |> ReasonReactRouter.push
             | "istrue" => Path.resendPath |> ReasonReactRouter.push
             | _ =>
               restoreAction();
               response##data##status
               |> Status.accountModule
               |> barShowRestoreAction;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let keydownCode =
    useCallback(keyCode =>
      if (keyCode == 13) {
        ActionOtherLoad(true) |> dispatch;
        codeUserAJax();
      }
    );

  let nextForm =
    useCallback(_ => {
      ActionOtherLoad(true) |> dispatch;
      codeUserAJax();
    });

  <YoutubeCode
    error={state.error}
    loading={state.loading}
    showYoutube={state.showYoutube}
    youtubeText={state.youtubeText}
    disabled={state.disabled}
    code={state.code}
    changeCode={event => ReactEvent.Form.target(event)##value |> changeCode}
    keydownCode={event => ReactEvent.Keyboard.keyCode(event) |> keydownCode}
    backForm={_ => Path.loginPath |> ReasonReactRouter.push}
    nextForm
  />;
};
