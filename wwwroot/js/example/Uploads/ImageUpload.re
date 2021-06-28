open React;
open Setting;
open ReactIntl;

[@react.component]
let make =
    (
      ~webLoad: option(bool)=?,
      ~showDrop: option(bool)=?,
      ~showFile: option(bool)=?,
      ~src: option(string)=?,
      ~fileRef: option(Ref.t(Js.Nullable.t(Dom.element)))=?,
      ~onDragOver: option(ReactEvent.Mouse.t => unit)=?,
      ~onDragLeave: option(ReactEvent.Mouse.t => unit)=?,
      ~onDrop: option(ReactEvent.Mouse.t => unit)=?,
      ~disabled: option(bool)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~onChange: option(ReactEvent.Form.t => unit)=?,
    ) =>
  webLoad |> disabledObjects
    ? <PasteBoard>
        <PasteInformation tile="Reviewing File..." />
        <ProgressCircular size="80" color="rgba(255,0,0,0.8)" />
      </PasteBoard>
    : <PasteBoard ?onDragOver ?onDragLeave ?onDrop>
        {switch (showFile |> disabledObjects, showDrop |> disabledObjects) {
         | (true, _) =>
           <Image
             width="auto"
             height="200px"
             borderRadius="6"
             src={src |> stringObjects}
           />
         | (false, true) => <PasteInformation tile="Please Let Go" />
         | (false, false) =>
           <PasteInformation
             tile="Please Drop Photo In Here"
             instruction="or you can ..."
           />
         }}
        <Button
          variant="button"
          color="rgba(255,255,255,1)"
          border="contained"
          size="medium"
          disabled={disabled |> disabledObjects}
          ?onClick>
          <FormattedMessage id="choose" defaultMessage="Choose" />
        </Button>
        <input
          type_="file"
          style={ReactDOMRe.Style.make(~display="none", ())}
          ref={fileRef |> refObjects |> ReactDOMRe.Ref.domRef}
          ?onChange
        />
      </PasteBoard>;
