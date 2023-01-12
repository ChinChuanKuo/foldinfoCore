open React;
open ReactIntl;
open Setting;

[@react.component]
let make =
    (
      ~error: option(bool)=?,
      ~loading: option(bool)=?,
      ~showYoutube: option(bool)=?,
      ~youtubeText: option(string)=?,
      ~disabled: option(bool)=?,
      ~userid: option(string)=?,
      ~changeUserid: option(ReactEvent.Form.t => unit)=?,
      ~keydownUserid: option(ReactEvent.Keyboard.t => unit)=?,
      ~password: option(string)=?,
      ~changePassword: option(ReactEvent.Form.t => unit)=?,
      ~keydownPassword: option(ReactEvent.Keyboard.t => unit)=?,
      ~forgetForm: option(ReactEvent.Mouse.t => unit)=?,
      ~sendForm: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) => {
  <AccountBoard
    error={error |> disabledObjects}
    loading={loading |> disabledObjects}
    tile="LOGIN"
    showYoutube={showYoutube |> disabledObjects}
    youtubeText={youtubeText |> stringObjects}>
    <GridContainer direction="column" justify="center" alignItem="stretch">
      <GridItem right="0" left="0" xs="auto"> children </GridItem>
      <GridItem right="0" left="0" xs="auto">
        <TextFieldOutline
          left="0"
          right="0"
          type_="email"
          value={userid |> stringObjects}
          disabled={disabled |> disabledObjects}
          onChange=?changeUserid
          onKeyDown=?keydownUserid>
          <FormattedMessage id="Login.email" defaultMessage="Email" />
        </TextFieldOutline>
      </GridItem>
      <GridItem top="21" right="0" left="0" xs="auto">
        <TextFieldOutline
          left="0"
          right="0"
          type_="password"
          value={password |> stringObjects}
          disabled={disabled |> disabledObjects}
          onChange=?changePassword
          onKeyDown=?keydownPassword>
          <FormattedMessage id="Login.password" defaultMessage="Password" />
        </TextFieldOutline>
      </GridItem>
      <GridItem top="21" right="0" left="0" xs="auto">
        <GridContainer direction="row" justify="between" alignItem="center">
          <GridItem right="0" left="0" xs="no">
            <Button
              variant="button"
              border="contained"
              size="medium"
              disabled={disabled |> disabledObjects}
              onClick=?forgetForm>
              <FormattedMessage id="Account.forget" defaultMessage="Forget" />
            </Button>
          </GridItem>
          <GridItem right="0" left="0" xs="no">
            <Button
              variant="button"
              border="contained"
              size="medium"
              disabled={disabled |> disabledObjects}
              onClick=?sendForm>
              <FormattedMessage id="Account.send" defaultMessage="Send" />
            </Button>
          </GridItem>
        </GridContainer>
      </GridItem>
    </GridContainer>
  </AccountBoard>;
};
