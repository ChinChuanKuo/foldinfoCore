open React;

type state = {
  value: string,
  disabled: bool,
};

type action =
  | ChangeField(string);

let reducer = (state, action) =>
  switch (action) {
  | ChangeField(value) => {...state, value}
  };

let initialState = {value: "", disabled: false};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);
  let changeField = useCallback(value => ChangeField(value) |> dispatch);
  let keydownField = useCallback(value => value |> Js.log);
  <div>
    <TextFieldOutline
      value={state.value}
      disabled={state.disabled}
      onChange={event => ReactEvent.Form.target(event)##value |> changeField}
      onKeyDown={event =>
        ReactEvent.Keyboard.target(event)##value |> keydownField
      }>
      {"error" |> string}
    </TextFieldOutline>
    <TextFieldStandard
      value={state.value}
      disabled={state.disabled}
      onChange={event => ReactEvent.Form.target(event)##value |> changeField}
      onKeyDown={event =>
        ReactEvent.Keyboard.target(event)##value |> keydownField
      }>
      {"error" |> string}
    </TextFieldStandard>
    <TextFieldMultiline
      rows=4
      value={state.value}
      disabled={state.disabled}
      onChange={event => ReactEvent.Form.target(event)##value |> changeField}
      onKeyDown={event =>
        ReactEvent.Keyboard.target(event)##value |> keydownField
      }>
      {"error" |> string}
    </TextFieldMultiline>
  </div>;
};
