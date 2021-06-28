open React;
open Icons;

type state = {isShow: bool};

type action =
  | ShowPanel;

let reducer = (state, action) =>
  switch (action) {
  | ShowPanel => {isShow: !state.isShow}
  };

let initialState = {isShow: false};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);
  let showPanel = useCallback(_ => ShowPanel |> dispatch);
  <div>
    <ExpansionPanel showPanel={state.isShow}>
      ...(
           <ExpansionSummary showSummary={state.isShow} onClick=showPanel>
             ...(
                  <span> {"123" |> string} </span>,
                  <IconGeneral
                    src={state.isShow ? arrowUpBlack : arrowDownBlack}
                  />,
                )
           </ExpansionSummary>,
           "test" |> string,
         )
    </ExpansionPanel>
    <ExpansionPanel showPanel={state.isShow}>
      ...(
           <ExpansionSummary showSummary={state.isShow} onClick=showPanel>
             ...(
                  <>
                    <ExpansionBasis>
                      <span> {"123" |> string} </span>
                    </ExpansionBasis>
                    <ExpansionBasis>
                      <span> {"123" |> string} </span>
                    </ExpansionBasis>
                  </>,
                  <IconGeneral
                    src={state.isShow ? arrowDownBlack : arrowUpBlack}
                  />,
                )
           </ExpansionSummary>,
           "test" |> string,
         )
    </ExpansionPanel>
  </div>;
};
