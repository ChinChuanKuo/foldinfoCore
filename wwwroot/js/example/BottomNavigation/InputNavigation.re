open Setting;

[@react.component]
let make =
    (
      ~textRef: option(React.Ref.t(Js.Nullable.t(Dom.element)))=?,
      ~disabled: option(bool)=?,
      ~onInput: option(ReactEvent.Form.t => unit)=?,
      ~onKeyDown: option(ReactEvent.Keyboard.t => unit)=?,
      ~children,
    ) =>
  <GridContainer direction="column" justify="center" alignItem="stretch">
    <GridItem top="0" bottom="6" xs="auto">
      <ToolBar disabled={disabled |> disabledObjects} />
    </GridItem>
    <GridItem top="0" bottom="0" xs="auto">
      <TextFieldArticle
        maxHeight="121"
        height="80"
        textRef={textRef |> refObjects}
        disabled={disabled |> disabledObjects}
        ?onInput
        ?onKeyDown
      />
    </GridItem>
    <GridItem top="6" bottom="0" xs="auto"> children </GridItem>
  </GridContainer>;
