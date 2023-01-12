open React;
open Setting;
open Icons;

type state = {enter: bool};

type action =
  | MouseEnterLeave(bool);

let reducer = (_, action) =>
  switch (action) {
  | MouseEnterLeave(enter) => {enter: enter}
  };

let initialState = {enter: false};

let enterSrcs = enterSrc =>
  switch (enterSrc) {
  | None => arrowDownWhite
  | Some(enterSrc) => enterSrc
  };

let srcs = src =>
  switch (src) {
  | None => arrowDownBlack
  | Some(src) => src
  };

[@react.component]
let make =
    (
      ~showBar: option(bool)=?,
      ~disabled: option(bool)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~enterSrc: option(string)=?,
      ~src: option(string)=?,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  showBar |> disabledObjects
    ? <GridItem
        top="0"
        right="0"
        bottom="0"
        left="0"
        enterBackgroundColor="none"
        backgroundColor="none"
        xs="12">
        <div
          onMouseEnter={_ => MouseEnterLeave(true) |> dispatch}
          onMouseLeave={_ => MouseEnterLeave(false) |> dispatch}>
          <Button
            width="100%"
            enterBackgroundColor="rgba(255,0,0,0.6)"
            backgroundColor="rgba(255,255,255,1)"
            size="large"
            disabled={disabled |> disabledObjects}
            ?onClick>
            <IconAction
              src={state.enter ? enterSrc |> enterSrcs : src |> srcs}
            />
          </Button>
        </div>
      </GridItem>
    : null;
};
