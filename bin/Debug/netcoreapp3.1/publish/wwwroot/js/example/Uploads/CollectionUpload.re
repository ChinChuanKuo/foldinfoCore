open React;
open Setting;
open ReactIntl;
open Icons;

[@react.component]
let make =
    (
      ~webLoad: option(bool)=?,
      ~showDrop: option(bool)=?,
      ~showFile: option(bool)=?,
      ~fileRef: option(Ref.t(Js.Nullable.t(Dom.element)))=?,
      ~onDragOver: option(ReactEvent.Mouse.t => unit)=?,
      ~onDragLeave: option(ReactEvent.Mouse.t => unit)=?,
      ~onDrop: option(ReactEvent.Mouse.t => unit)=?,
      ~disabled: option(bool)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~onChange: option(ReactEvent.Form.t => unit)=?,
      ~showPrevious: option(ReactEvent.Mouse.t => unit)=?,
      ~showNext: option(ReactEvent.Mouse.t => unit)=?,
      ~showDelete: option(bool)=?,
      ~onDelete: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) =>
  <div style={ReactDOMRe.Style.make(~position="relative", ())}>
    <div
      style={ReactDOMRe.Style.make(
        ~position="absolute",
        ~top="50%",
        ~left="20px",
        ~transform="translate(0px, -50%)",
        ~zIndex="1",
        (),
      )}>
      <IconButton
        padding="6"
        disabled={webLoad |> disabledObjects}
        onClick=?showPrevious>
        <IconAction animation="leftRight" src=arrowBackIosBlack />
      </IconButton>
    </div>
    <GridItem right="0" left="0" xs="12">
      {webLoad |> disabledObjects
         ? <PasteBoard>
             <PasteInformation tile="Reviewing File..." />
             <ProgressCircular size="80" color="rgba(255,0,0,0.8)" />
           </PasteBoard>
         : <PasteBoard ?onDragOver ?onDragLeave ?onDrop>
             {switch (
                showFile |> disabledObjects,
                showDrop |> disabledObjects,
              ) {
              | (true, _) => children
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
           </PasteBoard>}
    </GridItem>
    <div
      style={ReactDOMRe.Style.make(
        ~position="absolute",
        ~top="50%",
        ~right="20px",
        ~transform="translate(0px, -50%)",
        ~zIndex="1",
        (),
      )}>
      <IconButton
        padding="6" disabled={webLoad |> disabledObjects} onClick=?showNext>
        <IconAction animation="leftRight" src=arrowForwardIosBlack />
      </IconButton>
    </div>
    {showDelete |> disabledObjects
       ? <div
           style={ReactDOMRe.Style.make(
             ~position="absolute",
             ~top="20px",
             ~right="20px",
             ~transform="translate(0px, 0%)",
             ~zIndex="1",
             (),
           )}>
           <IconButton
             padding="6"
             disabled={webLoad |> disabledObjects}
             onClick=?onDelete>
             <IconAction animation="leftRight" src=deleteBlack />
           </IconButton>
         </div>
       : null}
  </div>;
