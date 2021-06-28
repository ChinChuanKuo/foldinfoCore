open React;
type state = {
  showDialog: bool,
  showAnimationBottom: bool,
  showAnimationRight: bool,
  showFull: bool,
};

type action =
  | ShowDialog
  | ShowAnimationBottom
  | ShowAnimationRight
  | ShowFull;

let reducer = (state, action) =>
  switch (action) {
  | ShowDialog => {...state, showDialog: !state.showDialog}
  | ShowAnimationBottom => {
      ...state,
      showAnimationBottom: !state.showAnimationBottom,
    }
  | ShowAnimationRight => {
      ...state,
      showAnimationRight: !state.showAnimationRight,
    }
  | ShowFull => {...state, showFull: !state.showFull}
  };

let initialState = {
  showDialog: false,
  showAnimationBottom: false,
  showAnimationRight: false,
  showFull: false,
};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);
  let clickDialogShow = useCallback(_ => ShowDialog |> dispatch);
  let clickAnimationBottomShow =
    useCallback(_ => ShowAnimationBottom |> dispatch);
  <div>
    <div onClick=clickDialogShow>
      {string(state.showDialog ? "dialog" : "123")}
    </div>
    <div onClick=clickAnimationBottomShow>
      {string(state.showAnimationBottom ? "animationBottom" : "123")}
    </div>
    <div onClick={_ => dispatch(ShowAnimationRight)}>
      {string(state.showAnimationRight ? "animationRight" : "123")}
    </div>
    <div onClick={_ => dispatch(ShowFull)}>
      {string(state.showFull ? "full" : "123")}
    </div>
    <Dialog showDialog={state.showDialog}>
      <DialogTitle> {"Use Google's location service?" |> string} </DialogTitle>
      <DialogContent>
        <DialogContentText>
          {"Let Google help apps determine location. This means sending anonymous location data to
        Google, even when no apps are running."
           |> string}
        </DialogContentText>
      </DialogContent>
      <DialogActions> {"123" |> string} </DialogActions>
    </Dialog>
    <DialogAnimationBottom showAnimation={state.showAnimationBottom}>
      <DialogTitle> {"Use Google's location service?" |> string} </DialogTitle>
      <DialogContent>
        <DialogContentText>
          {"Let Google help apps determine location. This means sending anonymous location data to
        Google, even when no apps are running."
           |> string}
        </DialogContentText>
      </DialogContent>
      <DialogActions> {"123" |> string} </DialogActions>
    </DialogAnimationBottom>
    <DialogAnimationRight showAnimation={state.showAnimationRight}>
      <DialogTitle> {"Use Google's location service?" |> string} </DialogTitle>
      <DialogContent>
        <DialogContentText>
          {"Let Google help apps determine location. This means sending anonymous location data to
        Google, even when no apps are running."
           |> string}
        </DialogContentText>
      </DialogContent>
      <DialogActions> {"123" |> string} </DialogActions>
    </DialogAnimationRight>
    <DialogFull showAnimation={state.showFull}>
      <DialogTitle> {"Use Google's location service?" |> string} </DialogTitle>
      <DialogContent>
        <DialogContentText>
          {"Let Google help apps determine location. This means sending anonymous location data to
        Google, even when no apps are running."
           |> string}
        </DialogContentText>
      </DialogContent>
      <DialogActions> {"123" |> string} </DialogActions>
    </DialogFull>
  </div>;
};