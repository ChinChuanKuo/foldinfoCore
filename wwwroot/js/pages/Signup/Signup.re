open React;
open Data;
open Storage;

type state = {
  error: bool,
  loading: bool,
  showYoutube: bool,
  youtubeText: string,
  disabled: bool,
  userid: string,
  password: string,
  username: string,
  birthday: string,
};

type action =
  | ChangeUserid(string)
  | ChangePassword(string)
  | ChangeUsername(string)
  | ChangeBirthday(string)
  | ActionOtherLoad(bool)
  | ActionErrorLoad(bool)
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | ChangeUserid(value) => {...state, userid: value}
  | ChangePassword(value) => {...state, password: value}
  | ChangeUsername(value) => {...state, username: value}
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
  error: false,
  loading: false,
  showYoutube: false,
  youtubeText: "",
  disabled: false,
  userid: "",
  password: "",
  username: "",
  birthday: "",
};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);

  let changeUserid =
    useCallback(value => {
      Sessions.create("userid", value);
      ChangeUserid(value) |> dispatch;
    });

  let changePassword =
    useCallback(value => ChangePassword(value) |> dispatch);

  let changeUsername =
    useCallback(value => ChangeUsername(value) |> dispatch);

  let changeBirthday =
    useCallback(value => ChangeBirthday(value) |> dispatch);

  let restoreAction = () => ActionErrorLoad(true) |> dispatch;
  Js.Global.setTimeout(
    () => {
      ActionErrorLoad(false) |> dispatch;
      ActionOtherLoad(false) |> dispatch;
    },
    500,
  )
  |> ignore;

  let barShowRestoreAction = youtubeText => {
    ActionSnackBar(youtubeText, true) |> dispatch;
    Js.Global.setTimeout(() => ActionSnackBar("", false) |> dispatch, 5000)
    |> ignore;
  };

  let signupUserAJax = () =>
    Js.Promise.(
      signupData(state.userid, state.password, state.username, state.birthday)
      |> Axiosapi.Signup.signupUser
      |> then_(response =>
           resolve(
             switch (response##data##status) {
             | "istrue" => Path.loginPath |> ReasonReactRouter.push
             | _ =>
               restoreAction();
               response##data##status
               |> Status.accountModule
               |> barShowRestoreAction;
             },
           )
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let keydownUserid =
    useCallback(keyCode =>
      if (keyCode == 13) {
        ActionOtherLoad(true) |> dispatch;
        signupUserAJax();
      }
    );

  let keydownPassword =
    useCallback(keyCode =>
      if (keyCode == 13) {
        ActionOtherLoad(true) |> dispatch;
        signupUserAJax();
      }
    );

  let keydownUsername =
    useCallback(keyCode =>
      if (keyCode == 13) {
        ActionOtherLoad(true) |> dispatch;
        signupUserAJax();
      }
    );

  let keydownBirthday =
    useCallback(keyCode =>
      if (keyCode == 13) {
        ActionOtherLoad(true) |> dispatch;
        signupUserAJax();
      }
    );

  let nextForm =
    useCallback(_ => {
      ActionOtherLoad(true) |> dispatch;
      signupUserAJax();
    });

  <YoutubeSignup
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
    username={state.username}
    changeUsername={event =>
      ReactEvent.Form.target(event)##value |> changeUsername
    }
    keydownUsername={event =>
      ReactEvent.Keyboard.keyCode(event) |> keydownUsername
    }
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
