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
      ~code: option(string)=?,
      ~changeCode: option(ReactEvent.Form.t => unit)=?,
      ~keydownCode: option(ReactEvent.Keyboard.t => unit)=?,
      ~backForm: option(ReactEvent.Mouse.t => unit)=?,
      ~nextForm: option(ReactEvent.Mouse.t => unit)=?,
    ) =>
  <AccountBoard
    error={error |> disabledObjects}
    loading={loading |> disabledObjects}
    index=3
    tile="CODE"
    showYoutube={showYoutube |> disabledObjects}
    youtubeText={youtubeText |> stringObjects}>
    <GridContainer direction="column" justify="center" alignItem="stretch">
      <GridItem right="0" left="0" xs="auto">
        <TextFieldOutline
          left="0"
          right="0"
          value={code |> stringObjects}
          disabled={disabled |> disabledObjects}
          onChange=?changeCode
          onKeyDown=?keydownCode>
          <FormattedMessage
            id="Code.verification"
            defaultMessage="Verification"
          />
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
