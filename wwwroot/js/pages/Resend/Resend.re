open React;
open Axiosapi;
open Data;
open Storage;

type state = {
  formLoad: bool,
  error: bool,
  loading: bool,
  showYoutube: bool,
  youtubeText: string,
  disabled: bool,
  fstPassword: string,
  sndPassword: string,
};

type action =
  | SettingFormLoad
  | ChangeFstPassword(string)
  | ChangeSndPassword(string)
  | ActionOtherLoad(bool)
  | ActionErrorLoad(bool)
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingFormLoad => {...state, formLoad: !state.formLoad}
  | ChangeFstPassword(value) => {...state, fstPassword: value}
  | ChangeSndPassword(value) => {...state, sndPassword: value}
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
  fstPassword: "",
  sndPassword: "",
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

  let changeFstPassword =
    useCallback(value => ChangeFstPassword(value) |> dispatch);

  let changeSndPassword =
    useCallback(value => ChangeSndPassword(value) |> dispatch);

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

  let resendUserAJax = () =>
    Js.Promise.(
      state.sndPassword
      |> otherData("newid" |> Sessions.select)
      |> Axiosapi.Resend.resendUser
      |> then_(response => {
           (
             switch (response##data##status) {
             | "nousers"
             | "istrue" => Path.loginPath |> ReasonReactRouter.push
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

  let checkResendData = () =>
    if (state.fstPassword != state.sndPassword) {
      restoreAction();
      "errorDifPassword" |> Status.accountModule |> barShowRestoreAction;
    } else {
      ActionOtherLoad(true) |> dispatch;
      resendUserAJax();
    };

  let keydownFstPassword =
    useCallback(keyCode =>
      if (keyCode == 13) {
        checkResendData();
      }
    );

  let keydownSndPassword =
    useCallback(keyCode =>
      if (keyCode == 13) {
        checkResendData();
      }
    );

  let nextForm = useCallback(_ => checkResendData());

  <YoutubeResend
    error={state.error}
    loading={state.loading}
    showYoutube={state.showYoutube}
    youtubeText={state.youtubeText}
    disabled={state.disabled}
    fstPassword={state.fstPassword}
    changeFstPassword={event =>
      ReactEvent.Form.target(event)##value |> changeFstPassword
    }
    keydownFstPassword={event =>
      ReactEvent.Keyboard.keyCode(event) |> keydownFstPassword
    }
    sndPassword={state.sndPassword}
    changeSndPassword={event =>
      ReactEvent.Form.target(event)##value |> changeSndPassword
    }
    keydownSndPassword={event =>
      ReactEvent.Keyboard.keyCode(event) |> keydownSndPassword
    }
    backForm={_ => Path.loginPath |> ReasonReactRouter.push}
    nextForm
  />;
};
