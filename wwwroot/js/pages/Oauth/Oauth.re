open React;
open Basic;

type state = {
  formLoad: bool,
  error: bool,
  loading: bool,
  showYoutube: bool,
  youtubeText: string,
  disabled: bool,
};

type action =
  | SettingUserId
  | ActionOtherLoad(bool)
  | ActionErrorLoad(bool)
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingUserId => {...state, formLoad: !state.formLoad}
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
};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);

  useEffect(() =>
    if (state.formLoad) {
      Some(() => "action" |> Js.log);
    } else {
      let testId = SettingUserId |> dispatch;
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

  <YoutubeOauth
    error={state.error}
    loading={state.loading}
    showYoutube={state.showYoutube}
    youtubeText={state.youtubeText}
    disabled={state.disabled}
  />;
};
