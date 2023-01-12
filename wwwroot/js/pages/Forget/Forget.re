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
  birthday: string,
};

type action =
  | SettingFormLoad
  | ChangeBirthday(string)
  | ActionOtherLoad(bool)
  | ActionErrorLoad(bool)
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingFormLoad => {...state, formLoad: !state.formLoad}
  | ChangeBirthday(value) => {...state, birthday: value}
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
  youtubeText: "",
  showYoutube: false,
  disabled: false,
  birthday: "",
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

  let changeBirthday =
    useCallback(value => ChangeBirthday(value) |> dispatch);

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

  let forgetUserAJax = () =>
    Js.Promise.(
      state.birthday
      |> otherData("newid" |> Sessions.select)
      |> Axiosapi.Forget.forgetUser
      |> then_(response => {
           (
             switch (response##data##status) {
             | "nousers" => Path.loginPath |> ReasonReactRouter.push
             | "istrue" => Path.codePath |> ReasonReactRouter.push
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

  let keydownBirthday =
    useCallback(keyCode =>
      if (keyCode == 13) {
        ActionOtherLoad(true) |> dispatch;
        forgetUserAJax();
      }
    );

  let nextForm =
    useCallback(_ => {
      ActionOtherLoad(true) |> dispatch;
      forgetUserAJax();
    });

  <YoutubeForget
    error={state.error}
    loading={state.loading}
    showYoutube={state.showYoutube}
    youtubeText={state.youtubeText}
    disabled={state.disabled}
    birthday={state.birthday}
    changeBirthday={event =>
      ReactEvent.Form.target(event)##value |> changeBirthday
    }
    keydownBirthday={event =>
      ReactEvent.Keyboard.keyCode(event) |> keydownBirthday
    }
    backForm={_ => Path.loginPath |> ReasonReactRouter.push}
    nextForm
  />;
};
