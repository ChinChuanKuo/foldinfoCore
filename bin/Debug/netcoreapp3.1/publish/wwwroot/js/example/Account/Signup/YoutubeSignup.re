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
      ~username: option(string)=?,
      ~changeUsername: option(ReactEvent.Form.t => unit)=?,
      ~keydownUsername: option(ReactEvent.Keyboard.t => unit)=?,
      ~birthday: option(string)=?,
      ~changeBirthday: option(ReactEvent.Form.t => unit)=?,
      ~keydownBirthday: option(ReactEvent.Keyboard.t => unit)=?,
      ~backForm: option(ReactEvent.Mouse.t => unit)=?,
      ~nextForm: option(ReactEvent.Mouse.t => unit)=?,
    ) =>
  <AccountBoard
    error={error |> disabledObjects}
    loading={loading |> disabledObjects}
    index=1
    tile="SIGNUP"
    showYoutube={showYoutube |> disabledObjects}
    youtubeText={youtubeText |> stringObjects}>
    <GridContainer direction="column" justify="center" alignItem="stretch">
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
      <GridItem right="0" left="0" xs="auto">
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
      <GridItem right="0" left="0" xs="auto">
        <TextFieldOutline
          left="0"
          right="0"
          value={username |> stringObjects}
          disabled={disabled |> disabledObjects}
          onChange=?changeUsername
          onKeyDown=?keydownUsername>
          <FormattedMessage id="Signup.name" defaultMessage="Name" />
        </TextFieldOutline>
      </GridItem>
      <GridItem right="0" left="0" xs="auto">
        <TextFieldOutline
          left="0"
          right="0"
          value={birthday |> stringObjects}
          disabled={disabled |> disabledObjects}
          onChange=?changeBirthday
          onKeyDown=?keydownBirthday>
          <FormattedMessage id="Signup.birthday" defaultMessage="Birthday" />
        </TextFieldOutline>
      </GridItem>
      <GridItem right="0" left="0" xs="auto">
        <GridContainer direction="row" justify="between" alignItem="center">
          <GridItem right="0" left="0" xs="no">
            <Button
              variant="button"
              border="contained"
              size="medium"
              disabled={disabled |> disabledObjects}
              onClick=?backForm>
              <FormattedMessage id="Account.back" defaultMessage="Back" />
            </Button>
          </GridItem>
          <GridItem right="0" left="0" xs="no">
            <Button
              variant="button"
              border="contained"
              size="medium"
              disabled={disabled |> disabledObjects}
              onClick=?nextForm>
              <FormattedMessage id="Account.send" defaultMessage="Send" />
            </Button>
          </GridItem>
        </GridContainer>
      </GridItem>
    </GridContainer>
  </AccountBoard>;
