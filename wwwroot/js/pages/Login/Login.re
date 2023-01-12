open React;
open Data;
open Basic;
open Storage;
open ObjectFormat;

type state = {
  formLoad: bool,
  error: bool,
  loading: bool,
  showYoutube: bool,
  youtubeText: string,
  disabled: bool,
  userid: string,
  password: string,
};

type action =
  | SettingUserId(string)
  | ChangeUserId(string)
  | ChangePassword(string)
  | ActionOtherLoad(bool)
  | ActionErrorLoad(bool)
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingUserId(value) => {
      ...state,
      userid: value,
      formLoad: !state.formLoad,
    }
  | ChangeUserId(value) => {...state, userid: value}
  | ChangePassword(value) => {...state, password: value}
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
  userid: "",
  password: "",
};

let autoLoginPath = value =>
  switch (value) {
  | "" => "/"
  | _ => value
  };

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);

  useEffect(() =>
    if (state.formLoad) {
      Some(() => "action" |> Js.log);
    } else {
      let testId =
        SettingUserId("userid" |> Sessions.select |> checkObjects) |> dispatch;
      let pstId =
        Navigator.Position.make(
          Location.success,
          Location.error,
          Location.items,
        )
        |> ignore;
      //let bwsId = JsModules.Browsers.make |> ignore;
      Some(
        () => {
          testId;
          pstId;
        },
        //bwsId;
      );
    }
  );

  let changeUserid =
    useCallback(value => {
      ChangeUserId(value) |> dispatch;
      Sessions.create("userid", value);
    });

  let changePassword =
    useCallback(value => ChangePassword(value) |> dispatch);

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

  let checkUserAJax = () =>
    Js.Promise.(
      state.userid
      |> userData
      |> Axiosapi.Login.checkUser
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               response##data##newid |> Sessions.create("newid");
               Path.forgetPath |> ReasonReactRouter.push;
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

  let forgetForm =
    useCallback(_ => {
      ActionOtherLoad(true) |> dispatch;
      checkUserAJax();
    });

  let loginUserAJax = () =>
    Js.Promise.(
      "latitude"
      |> Locals.select
      |> loginData(
           state.userid,
           state.password,
           "longitude" |> Locals.select,
         )
      |> Axiosapi.Login.loginUser
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               response##data##newid |> Locals.create("newid");
               response##data##name |> Locals.create("name");
               response##data##allname |> Locals.create("allname");
               "autoPath"
               |> Sessions.select
               |> checkObjects
               |> autoLoginPath
               |> ReasonReactRouter.push;
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

  let keydownUserid =
    useCallback(keyCode =>
      if (keyCode == 13) {
        ActionOtherLoad(true) |> dispatch;
        loginData(
          state.userid,
          state.password,
          "longitude" |> Locals.select,
          "latitude" |> Locals.select,
        )
        |> Js.log;
        loginUserAJax();
      }
    );

  let keydownPassword =
    useCallback(keyCode =>
      if (keyCode == 13) {
        ActionOtherLoad(true) |> dispatch;
        loginUserAJax();
      }
    );

  let sendForm =
    useCallback(_ => {
      ActionOtherLoad(true) |> dispatch;
      loginUserAJax();
    });

  <YoutubeLogin
    error={state.error}
    loading={state.loading}
    showYoutube={state.showYoutube}
    youtubeText={state.youtubeText}
    disabled={state.disabled}
    userid={state.userid}
    changeUserid={event =>
      ReactEvent.Form.target(event)##value |> changeUserid
    }
    keydownUserid={event =>
      ReactEvent.Keyboard.keyCode(event) |> keydownUserid
    }
    password={state.password}
    changePassword={event =>
      ReactEvent.Form.target(event)##value |> changePassword
    }
    keydownPassword={event =>
      ReactEvent.Keyboard.keyCode(event) |> keydownPassword
    }
    forgetForm
    sendForm>
    null
  </YoutubeLogin>;
};
