open React;

type state = {isOpen: bool};

type action =
  | ClickCircle;

let reducer = (state, action) =>
  switch (action) {
  | ClickCircle => {isOpen: !state.isOpen}
  };

let initialState = {isOpen: false};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);
  let clickCircle = useCallback(_ => ClickCircle |> dispatch);
  <List_>
    <ListSecondary disablePadding=false>
      ...(
           "test" |> string,
           <CircleButton
             style={ReactDOMRe.Style.make(~width="48px", ~height="48px", ())}
             size="small"
             onClick=clickCircle>
             <span> {string(state.isOpen ? "T" : "F")} </span>
           </CircleButton>,
         )
    </ListSecondary>
  </List_>;
};