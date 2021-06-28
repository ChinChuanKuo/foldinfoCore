open React;
open Setting;
open ReactIntl;
open Icons;
open Items;
open Storage;
open ObjectFormat;
[%bs.raw {|require('../../../scss/example/Account/accountBoard.scss')|}];

type state = {
  formLoad: bool,
  formWidth: int,
  formHeight: int,
  tabitems: list(tabitem),
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

let initialState = {
  formLoad: false,
  formWidth: 0,
  formHeight: 0,
  tabitems: [
    {showTab: false, tabImage: accountBoxBlack},
    {showTab: false, tabImage: accountTreeBlack},
    {showTab: false, tabImage: homeBlack},
  ],
};

let errorAnimation = error => error ? "justLeftRightAnimation 0.5s" : "";

[@react.component]
let make =
    (
      ~error: option(bool)=?,
      ~loading: option(bool)=?,
      ~index: option(int)=?,
      ~tile: option(string)=?,
      ~showYoutube: option(bool)=?,
      ~youtubeText: option(string)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);

  useEffect(() =>
    if (state.formLoad) {
      Some(() => Js.log("action"));
    } else {
      let testtime = SettingFormLoad |> dispatch;
      let sizeId =
        SettingFormWidth(Window.Sizes.width, Window.Sizes.height) |> dispatch;
      Some(
        () => {
          testtime;
          sizeId;
        },
      );
    }
  );

  let handleResize = event => {
    SettingFormWidth(
      event##currentTarget##innerWidth,
      event##currentTarget##innerHeight,
    )
    |> dispatch;
  };

  useEffect0(() => {
    let sizeId = Window.Listeners.add("resize", handleResize, true) |> ignore;
    Some(() => sizeId);
  });

  let clickItemTab =
    useCallback(i =>
      if (i == 0) {
        Path.loginPath |> ReasonReactRouter.push;
      } else if (i == 1) {
        Path.signupPath |> ReasonReactRouter.push;
      } else if (i == 2) {
        Path.oauthPath |> ReasonReactRouter.push;
      }
    );

  <div>
    <Paper
      style={ReactDOMRe.Style.make(
        ~position="absolute",
        ~top="50%",
        ~left="50%",
        ~transform="translate(-50%, -50%)",
        ~minHeight="500px",
        ~textAlign="center",
        ~animation={error |> disabledObjects |> errorAnimation},
        (),
      )}
      className="paperAccount">
      {loading |> disabledObjects
         ? <ProgressLinear
             style={ReactDOMRe.Style.make(
               ~position="fixed",
               ~top="0",
               ~left="0",
               ~right="0",
               ~borderRadius="4px",
               (),
             )}
           />
         : null}
      <GridContainer direction="column" justify="center" alignItem="stretch">
        <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
          <Tabs
            display="block"
            id="account-"
            index={index |> intObjects}
            height="3">
            {state.tabitems
             |> List.mapi((i, tabitem) =>
                  <Tab
                    showTab={tabitem.showTab}
                    borderRadius="15"
                    id={"account-" ++ string_of_int(i)}
                    animationName="none"
                    onClick={_ => i |> clickItemTab}>
                    <IconAction
                      width="28"
                      height="28"
                      animation="leftRight"
                      src={tabitem.tabImage}
                    />
                  </Tab>
                )
             |> Array.of_list
             |> array}
          </Tabs>
        </GridItem>
        <GridItem top="0" xs="auto">
          <Typography
            variant="tile"
            style={ReactDOMRe.Style.make(
              ~paddingTop="16px",
              ~fontSize="24px",
              ~fontWeight="400",
              ~lineHeight="1.3333",
              (),
            )}>
            {tile |> stringObjects |> string}
          </Typography>
          <Typography
            variant="tile"
            style={ReactDOMRe.Style.make(
              ~fontSize="16px",
              ~letterSpacing="1px",
              ~lineHeight="1.5",
              ~paddingTop="8px",
              (),
            )}>
            <FormattedMessage id="Account.info" defaultMessage="Info" />
          </Typography>
        </GridItem>
        <GridItem top="6" bottom="0" left="0" xs="auto">
          <IconButton onClick={_ => ReasonReactRouter.push(Path.loginPath)}>
            <IconAction animation="leftRight" src=personBlack />
          </IconButton>
          {"YOUR ACCOUNT : "
           ++ checkObjects("userid" |> Sessions.select)
           |> string}
        </GridItem>
        <GridItem top="0" xs="auto"> children </GridItem>
      </GridContainer>
    </Paper>
    <SnackbarYoutube
      showYoutube={showYoutube |> disabledObjects} position="bottomLeft">
      ...(<span> {youtubeText |> stringObjects |> string} </span>, null)
    </SnackbarYoutube>
  </div>;
};
