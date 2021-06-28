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
      ~fstPassword: option(string)=?,
      ~changeFstPassword: option(ReactEvent.Form.t => unit)=?,
      ~keydownFstPassword: option(ReactEvent.Keyboard.t => unit)=?,
      ~sndPassword: option(string)=?,
      ~changeSndPassword: option(ReactEvent.Form.t => unit)=?,
      ~keydownSndPassword: option(ReactEvent.Keyboard.t => unit)=?,
      ~backForm: option(ReactEvent.Mouse.t => unit)=?,
      ~nextForm: option(ReactEvent.Mouse.t => unit)=?,
    ) =>
  <AccountBoard
    error={error |> disabledObjects}
    loading={loading |> disabledObjects}
    index=3
    tile="RESEND"
    showYoutube={showYoutube |> disabledObjects}
    youtubeText={youtubeText |> stringObjects}>
    <GridContainer direction="column" justify="center" alignItem="stretch">
      <GridItem right="0" left="0" xs="auto">
        <TextFieldOutline
          left="0"
          right="0"
          type_="password"
          value={fstPassword |> stringObjects}
          disabled={disabled |> disabledObjects}
          onChange=?changeFstPassword
          onKeyDown=?keydownFstPassword>
          <FormattedMessage id="Resend.first" defaultMessage="First" />
        </TextFieldOutline>
      </GridItem>
      <GridItem top="21" right="0" left="0" xs="auto">
        <TextFieldOutline
          left="0"
          right="0"
          type_="password"
          value={sndPassword |> stringObjects}
          disabled={disabled |> disabledObjects}
          onChange=?changeSndPassword
          onKeyDown=?keydownSndPassword>
          <FormattedMessage id="Resend.second" defaultMessage="Second" />
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
