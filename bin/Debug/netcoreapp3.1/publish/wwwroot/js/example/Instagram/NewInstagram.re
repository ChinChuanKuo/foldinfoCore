open React;
open Setting;
open OutSide;
open Together;

type state = {
  formLoad: bool,
  formWidth: int,
  formHeight: int,
};

type action =
  | SettingFormLoad
  | SettingFormWidth(int, int);

let reducer = (state, action) =>
  switch (action) {
  | SettingFormLoad => {...state, formLoad: !state.formLoad}
  | SettingFormWidth(width, height) => {
      ...state,
      formWidth: width,
      formHeight: height,
    }
  };

let initialState = {formLoad: false, formWidth: 0, formHeight: 0};

let widths = width =>
  switch (width) {
  | None => "95%"
  | Some(width) => width ++ "%"
  };

let bottoms = bottom =>
  switch (bottom) {
  | None => "0px"
  | Some(bottom) => bottom ++ "px"
  };

[@react.component]
let make =
    (
      ~showProgress: option(bool)=?,
      ~error: option(bool)=?,
      ~width: option(string)=?,
      ~bottom: option(string)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  useEffect(() =>
    if (state.formLoad) {
      Some(() => "action" |> Js.log);
    } else {
      let testId = SettingFormLoad |> dispatch;
      let formId =
        SettingFormWidth(Window.Sizes.width, Window.Sizes.height) |> dispatch;
      Some(
        () => {
          testId;
          formId;
        },
      );
    }
  );
  let handleResize = event =>
    SettingFormWidth(
      event##currentTarget##innerWidth,
      event##currentTarget##innerHeight,
    )
    |> dispatch;
  useEffect0(() => {
    let testId = Window.Listeners.add("resize", handleResize, true) |> ignore;
    Some(() => testId);
  });
  <>
    {showProgress |> disabledObjects
       ? <ProgressLinear style=progressFixed /> : null}
    <main
      style={ReactDOMRe.Style.combine(
        mainTube,
        ReactDOMRe.Style.make(
          ~right="5px",
          ~bottom={
            bottom |> bottoms;
          },
          ~left="5px",
          (),
        ),
      )}>
      <div style=divScrollbar>
        <div
          style={ReactDOMRe.Style.combine(
            marginAuto,
            ReactDOMRe.Style.make(
              ~width={
                width |> widths;
              },
              ~maxWidth={
                width |> widths;
              },
              ~flexBasis={
                width |> widths;
              },
              (),
            ),
          )}>
          {error |> disabledObjects
             ? <div style=errorForm>
                 <Typography
                   variant="tile" color="rgba(255,0,0,0.8)" fontSize="x-large">
                   {"UNDEFINED THIS PAGE" |> string}
                 </Typography>
               </div>
             : children}
        </div>
      </div>
    </main>
  </>;
};
