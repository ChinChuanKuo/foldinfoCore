open React;

type state = {
  showGmail: bool,
  showYoutube: bool,
};

type action =
  | ShowGmail
  | ShowYoutube;

let reducer = (state, action) =>
  switch (action) {
  | ShowGmail => {...state, showGmail: !state.showGmail}
  | ShowYoutube => {...state, showYoutube: !state.showYoutube}
  };

let initialState = {showGmail: false, showYoutube: false};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);
  let showGmail = useCallback(_ => ShowGmail |> dispatch);
  let showYoutube = useCallback(_ => ShowYoutube |> dispatch);
  <div>
    <div onClick=showGmail>
      {string(state.showGmail ? "gmail" : "123")}
    </div>
    <div onClick=showYoutube>
      {string(state.showYoutube ? "youtube" : "456")}
    </div>
    <SnackbarGmail showGmail={state.showGmail} position="topRight">
      ...(<span> {"123" |> string} </span>, null)
    </SnackbarGmail>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {"123" |> string} </span>, null)
    </SnackbarYoutube>
  </div>;
};