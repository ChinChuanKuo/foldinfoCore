open React;
open Setting;
open ReactIntl;

[@react.component]
let make =
    (
      ~webLoad: option(bool)=?,
      ~showDrop: option(bool)=?,
      ~showFile: option(bool)=?,
      ~showImage: option(bool)=?,
      ~showVideo: option(bool)=?,
      ~showAudio: option(bool)=?,
      ~src: option(string)=?,
      ~fileRef: option(Ref.t(Js.Nullable.t(Dom.element)))=?,
      ~onDragOver: option(ReactEvent.Mouse.t => unit)=?,
      ~onDragLeave: option(ReactEvent.Mouse.t => unit)=?,
      ~onDrop: option(ReactEvent.Mouse.t => unit)=?,
      ~disabled: option(bool)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~onDownload: option(ReactEvent.Mouse.t => unit)=?,
      ~onChange: option(ReactEvent.Form.t => unit)=?,
    ) =>
  webLoad |> disabledObjects
    ? <PasteBoard>
        <PasteInformation tile="Reviewing File..." />
        <ProgressCircular size="80" color="rgba(255,0,0,0.8)" />
      </PasteBoard>
    : <PasteBoard ?onDragOver ?onDragLeave ?onDrop>
        {switch (
           showFile |> disabledObjects,
           showImage |> disabledObjects,
           showVideo |> disabledObjects,
           showAudio |> disabledObjects,
         ) {
         | (true, true, false, false) =>
           <Image
             width="auto"
             height="200px"
             borderRadius="6"
             src={src |> stringObjects}
           />
         | (true, false, true, false) =>
           <Media
             width="auto"
             height="200px"
             borderRadius="6"
             src={src |> stringObjects}
           />
         | (true, false, false, true) =>
           <Media
             variant="audio"
             borderRadius="6"
             src={src |> stringObjects}
           />
         | (_, _, _, _) =>
           showDrop |> disabledObjects
             ? <PasteInformation tile="Please Let Go" />
             : <PasteInformation
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
        {showFile |> disabledObjects
           ? <Button
               variant="button"
               color="rgba(255,255,255,1)"
               border="contained"
               size="medium"
               onClick=?onDownload>
               <FormattedMessage id="download" defaultMessage="Download" />
             </Button>
           : null}
        <input
          type_="file"
          style={ReactDOMRe.Style.make(~display="none", ())}
          ref={fileRef |> refObjects |> ReactDOMRe.Ref.domRef}
          ?onChange
        />
      </PasteBoard>;
