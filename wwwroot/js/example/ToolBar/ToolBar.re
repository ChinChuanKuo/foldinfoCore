open React;
open ReactIntl;
open Setting;
open Data;
open Icons;
open Items;
open Storage;
open Axiosapi;
open Document;
open ObjectFormat;
open IconAnimation;

type sizeitem = {
  disablePadding: bool,
  size: string,
  value: string,
};

type state = {
  showName: bool,
  name: string,
  nameitems: array(optionitem),
  showSize: bool,
  sizeitems: array(sizeitem),
  showAlign: bool,
  showMore: bool,
  showAnimation: bool,
  tabitems: list(tabitem),
  index: int,
  showDrop: bool,
  showFile: bool,
  showImage: bool,
  showVideo: bool,
  showAudio: bool,
  src: string,
  imagePath: string,
  original: string,
  encryption: string,
  extension: string,
  webValue: string,
};

type action =
  | ShowName
  | ClickNameMenu(string)
  | ShowSize
  | ShowAlign
  | ShowMore
  | ShowAnimation
  | SettingUploadFile(
      bool,
      bool,
      bool,
      string,
      string,
      string,
      string,
      string,
    )
  | ClickItemTab(int)
  | ShowDrop(bool)
  | ShowFile(bool)
  | ChangeWebsite(string)
  | CloseAnimation;

let reducer = (state, action) =>
  switch (action) {
  | ShowName => {...state, showName: !state.showName}
  | ClickNameMenu(value) => {...state, name: value, showName: false}
  | ShowSize => {...state, showSize: !state.showSize}
  | ShowAlign => {...state, showAlign: !state.showAlign}
  | ShowMore => {...state, showMore: !state.showMore}
  | ShowAnimation => {...state, showAnimation: !state.showAnimation}
  | SettingUploadFile(
      showImage,
      showVideo,
      showAudio,
      src,
      imagePath,
      original,
      encryption,
      extension,
    ) => {
      ...state,
      showImage,
      showVideo,
      showAudio,
      src,
      imagePath,
      original,
      encryption,
      extension,
    }
  | ClickItemTab(index) => {
      ...state,
      tabitems:
        List.mapi(
          (i, tabitem) => {...tabitem, showTab: index == i},
          state.tabitems,
        ),
      index,
    }
  | ShowDrop(showDrop) => {...state, showDrop}
  | ShowFile(showFile) => {...state, showFile}
  | ChangeWebsite(value) => {...state, webValue: value}
  | CloseAnimation => {...state, showAnimation: !state.showAnimation}
  };

let initialState = {
  showName: false,
  name: "Sans Serif",
  nameitems: [|
    {optionPadding: false, value: "Microsoft JhengHei"},
    {optionPadding: false, value: "PMingLiU"},
    {optionPadding: false, value: "MingLiU"},
    {optionPadding: false, value: "Sans Serif"},
    {optionPadding: false, value: "Serif"},
    {optionPadding: false, value: "Monospace font"},
    {optionPadding: false, value: "width"},
    {optionPadding: false, value: "narrow"},
    {optionPadding: false, value: "Comic Sans MS"},
    {optionPadding: false, value: "Garamond"},
    {optionPadding: false, value: "Georgia"},
    {optionPadding: false, value: "Tahoma"},
    {optionPadding: false, value: "Trebuchet MS"},
    {optionPadding: false, value: "Verdana"},
  |],
  showSize: false,
  sizeitems: [|
    {disablePadding: false, size: "1", value: "small"},
    {disablePadding: false, size: "3", value: "general"},
    {disablePadding: false, size: "4", value: "larger"},
    {disablePadding: false, size: "6", value: "largest"},
  |],
  showAlign: false,
  showMore: false,
  showAnimation: false,
  tabitems: [
    {showTab: true, tabImage: factoryWhite},
    {showTab: false, tabImage: factoryWhite},
    {showTab: false, tabImage: factoryWhite},
    {showTab: false, tabImage: factoryWhite},
    {showTab: false, tabImage: factoryWhite},
  ],
  index: 0,
  showDrop: false,
  showFile: false,
  showImage: false,
  showVideo: false,
  showAudio: false,
  src: "",
  imagePath: "",
  original: "",
  encryption: "",
  extension: "",
  webValue: "",
};

[@react.component]
let make = (~disabled: option(bool)=?, ~width: option(int)=?) => {
  let (state, dispatch) = useReducer(reducer, initialState);

  let fileRef = useRef(Js.Nullable.null);

  let clickUndo = useCallback(_ => ExecCommands.make("undo", false, ""));
  let clickRedo = useCallback(_ => ExecCommands.make("redo", false, ""));
  let showName = useCallback(_ => ShowName |> dispatch);
  let clickNameMenu =
    useCallback(value => {
      ClickNameMenu(value) |> dispatch;
      ExecCommands.make("fontName", false, value);
    });
  let showSize = useCallback(_ => ShowSize |> dispatch);
  let clickSizeMenu =
    useCallback(size => ExecCommands.make("fontSize", false, size));
  let formatBold = useCallback(_ => ExecCommands.make("bold", false, ""));
  let formatItalic = useCallback(_ => ExecCommands.make("italic", false, ""));
  let underline = useCallback(_ => ExecCommands.make("underline", false, ""));
  let showAlign = useCallback(_ => ShowAlign |> dispatch);
  let alignLeft =
    useCallback(_ => ExecCommands.make("justifyLeft", false, ""));
  let alignCenter =
    useCallback(_ => ExecCommands.make("justifyCenter", false, ""));
  let alignRight =
    useCallback(_ => ExecCommands.make("justifyRight", false, ""));
  let insertorderedlist =
    useCallback(_ => ExecCommands.make("insertorderedlist", false, ""));
  let insertUnorderedlist =
    useCallback(_ => ExecCommands.make("insertUnorderedlist", false, ""));
  let outdent = useCallback(_ => ExecCommands.make("outdent", false, ""));
  let indent = useCallback(_ => ExecCommands.make("indent", false, ""));
  let showMore = useCallback(_ => ShowMore |> dispatch);
  let showUpload = useCallback(_ => ShowAnimation |> dispatch);
  let clickItemTab = useCallback(i => ClickItemTab(i) |> dispatch);
  let dragOverFile =
    useCallback(event => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      ShowDrop(true) |> dispatch;
    });
  let dragLeaveFile =
    useCallback(event => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      ShowDrop(false) |> dispatch;
    });
  let uploadAJax = files => {
    let formData = FormData.make();
    FormData.append(formData, "file", files) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               SettingUploadFile(
                 response##data##images,
                 response##data##videos,
                 response##data##audios,
                 response##data##src,
                 response##data##imagePath,
                 response##data##original,
                 response##data##encryption,
                 response##data##extension,
               )
               |> dispatch;
               ShowFile(true) |> dispatch;
             | _ => "upload error" |> Js.log
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );
  };
  let dropFile =
    useCallback((event, value) => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      //ActionShowProgress |> dispatch;
      ShowDrop(false) |> dispatch;
      value |> uploadAJax;
    });
  let chooseFile =
    useCallback(_ =>
      switch (fileRef |> Ref.current |> Js.Nullable.toOption) {
      | None => ()
      | Some(el) => el->ReactDOMRe.domElementToObj##click() |> ignore
      }
    );
  let changeFile = useCallback(value => value |> uploadAJax);
  let changeWebSite = useCallback(value => ChangeWebsite(value) |> dispatch);
  let websiteAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> sRowsData("", state.webValue)
      |> Files.website
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               SettingUploadFile(
                 response##data##images,
                 response##data##videos,
                 response##data##audios,
                 response##data##src,
                 response##data##imagePath,
                 response##data##original,
                 response##data##encryption,
                 response##data##extension,
               )
               |> dispatch;
               ShowFile(true) |> dispatch;
             | _ => ShowFile(false) |> dispatch
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );
  let keyDownWebSite =
    useCallback(keyCode =>
      if (keyCode == 13) {
        websiteAJax();
      }
    );
  let insertFile =
    useCallback(_ => {
      switch (
        state.showFile,
        state.showImage,
        state.showVideo,
        state.showAudio,
      ) {
      | (true, true, _, _) =>
        ExecCommands.make("insertImage", false, state.imagePath ++ state.src)
      | (true, _, true, _) =>
        ExecCommands.make(
          "insertHTML",
          false,
          "<video style='width:auto;height:200px;border-radius:6px;cursor:pointer;'><source src='"
          ++ state.imagePath
          ++ state.src
          ++ "' type='video/mp4' /></video>",
        )
      | (true, _, _, true) =>
        ExecCommands.make(
          "insertHTML",
          false,
          "<audio style='width:auto;height:200px;border-radius:6px;cursor:pointer;'><source src='"
          ++ state.imagePath
          ++ state.src
          ++ "' type='audio/mpeg' /></audio>",
        )
      | (_, _, _, _) => "123" |> Js.log
      };
      CloseAnimation |> dispatch;
    });
  let closeAnimation = useCallback(_ => CloseAnimation |> dispatch);
  //let insertImage =  useCallback(_ => ExecCommands.make("insertimage", false, ""));
  let removeFormat =
    useCallback(_ => ExecCommands.make("removeFormat", false, ""));
  let strikethrough =
    useCallback(_ => ExecCommands.make("strikethrough", false, ""));

  <>
    <AppBar
      backgroundColor="rgba(255,255,255,1)"
      position="relative"
      zIndex="1"
      minHeight="40">
      <GridContainer
        direction="rowReverse" justify="center" alignItem="center">
        <GridItem top="0" right="6" bottom="0" left="0" xs="no">
          <IconButton padding="4" onClick=showMore>
            <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
              <FormattedMessage id="Toolbar.more" defaultMessage="More" />
            </Tooltip>
            <IconAction animation="leftRight" src=arrowDownBlack />
          </IconButton>
          {state.showMore
             ? <>
                 <SelectMenu
                   top="50%"
                   transform="translate(0, -50%)"
                   minWidth="auto"
                   maxHeight="280"
                   minHeight="0"
                   topLeft="12"
                   topRight="12"
                   bottomRight="12"
                   bottomLeft="12"
                   paddingRight="8"
                   paddingLeft="8">
                   <MenuItem
                     top="0"
                     right="8"
                     bottom="0"
                     left="8"
                     topLeft="12"
                     topRight="12"
                     bottomRight="12"
                     bottomLeft="12"
                     onClick=showUpload>
                     <Tooltip
                       location="top" backgroundColor="rgba(255,0,0,0.8)">
                       <FormattedMessage
                         id="Toolbar.upload"
                         defaultMessage="Upload"
                       />
                     </Tooltip>
                     <IconGeneral src=imageBlack />
                   </MenuItem>
                   <MenuItem
                     top="0"
                     right="8"
                     bottom="0"
                     left="8"
                     topLeft="12"
                     topRight="12"
                     bottomRight="12"
                     bottomLeft="12"
                     onClick=removeFormat>
                     <Tooltip
                       location="top" backgroundColor="rgba(255,0,0,0.8)">
                       <FormattedMessage
                         id="Toolbar.remove"
                         defaultMessage="Remove"
                       />
                     </Tooltip>
                     <IconGeneral src=formatClearBlack />
                   </MenuItem>
                   <MenuItem
                     top="0"
                     right="8"
                     bottom="0"
                     left="8"
                     topLeft="12"
                     topRight="12"
                     bottomRight="12"
                     bottomLeft="12"
                     onClick=strikethrough>
                     <Tooltip
                       location="top" backgroundColor="rgba(255,0,0,0.8)">
                       <FormattedMessage
                         id="Toolbar.strike"
                         defaultMessage="Strike"
                       />
                     </Tooltip>
                     <IconGeneral src=strikethroughSBlack />
                   </MenuItem>
                   {switch (intObjects(width) < 900) {
                    | true =>
                      <MenuItem
                        top="0"
                        right="8"
                        bottom="0"
                        left="8"
                        topLeft="12"
                        topRight="12"
                        bottomRight="12"
                        bottomLeft="12"
                        onClick=indent>
                        <Tooltip
                          location="top" backgroundColor="rgba(255,0,0,0.8)">
                          <FormattedMessage
                            id="Toolbar.increase"
                            defaultMessage="Increase"
                          />
                        </Tooltip>
                        <IconGeneral src=formatIndentIncreaseBlack />
                      </MenuItem>
                    | _ => null
                    }}
                   {switch (intObjects(width) < 850) {
                    | true =>
                      <MenuItem
                        top="0"
                        right="8"
                        bottom="0"
                        left="8"
                        topLeft="12"
                        topRight="12"
                        bottomRight="12"
                        bottomLeft="12"
                        onClick=outdent>
                        <Tooltip
                          location="top" backgroundColor="rgba(255,0,0,0.8)">
                          <FormattedMessage
                            id="Toolbar.decrease"
                            defaultMessage="Decrease"
                          />
                        </Tooltip>
                        <IconGeneral src=formatIndentDecreaseBlack />
                      </MenuItem>
                    | _ => null
                    }}
                   {switch (intObjects(width) < 800) {
                    | true =>
                      <MenuItem
                        top="0"
                        right="8"
                        bottom="0"
                        left="8"
                        topLeft="12"
                        topRight="12"
                        bottomRight="12"
                        bottomLeft="12"
                        onClick=insertUnorderedlist>
                        <Tooltip
                          location="top" backgroundColor="rgba(255,0,0,0.8)">
                          <FormattedMessage
                            id="Toolbar.bullist"
                            defaultMessage="Bullist"
                          />
                        </Tooltip>
                        <IconGeneral src=formatListBulletedBlack />
                      </MenuItem>
                    | _ => null
                    }}
                   {switch (intObjects(width) < 750) {
                    | true =>
                      <MenuItem
                        top="0"
                        right="8"
                        bottom="0"
                        left="8"
                        topLeft="12"
                        topRight="12"
                        bottomRight="12"
                        bottomLeft="12"
                        onClick=insertorderedlist>
                        <Tooltip
                          location="top" backgroundColor="rgba(255,0,0,0.8)">
                          <FormattedMessage
                            id="Toolbar.ordlist"
                            defaultMessage="Ordlist"
                          />
                        </Tooltip>
                        <IconAction
                          animation="leftRight"
                          src=formatListNumberedBlack
                        />
                      </MenuItem>
                    | _ => null
                    }}
                 </SelectMenu>
                 <BackgroundBoard
                   showBackground={state.showMore}
                   backgroundColor="transparent"
                   onClick=showMore
                 />
               </>
             : null}
        </GridItem>
        <GridItem
          style={ReactDOMRe.Style.make(
            ~height="25px",
            ~marginTop="6px",
            ~marginRight="3px",
            ~borderRight="1px solid rgba(0,0,0,0.08)",
            (),
          )}
          top="0"
          right="0"
          bottom="0"
          left="3"
          xs="no">
          null
        </GridItem>
        {switch (intObjects(width) >= 900) {
         | true =>
           <GridItem top="0" right="0" bottom="0" left="0" xs="no">
             <IconButton padding="4" onClick=indent>
               <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
                 <FormattedMessage
                   id="Toolbar.increase"
                   defaultMessage="Increase"
                 />
               </Tooltip>
               <IconAction
                 animation="leftRight"
                 src=formatIndentIncreaseBlack
               />
             </IconButton>
           </GridItem>
         | _ => null
         }}
        {switch (intObjects(width) >= 850) {
         | true =>
           <GridItem top="0" right="0" bottom="0" left="0" xs="no">
             <IconButton padding="4" onClick=outdent>
               <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
                 <FormattedMessage
                   id="Toolbar.decrease"
                   defaultMessage="Decrease"
                 />
               </Tooltip>
               <IconAction
                 animation="leftRight"
                 src=formatIndentDecreaseBlack
               />
             </IconButton>
           </GridItem>
         | _ => null
         }}
        {switch (intObjects(width) >= 800) {
         | true =>
           <GridItem top="0" right="0" bottom="0" left="0" xs="no">
             <IconButton padding="4" onClick=insertUnorderedlist>
               <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
                 <FormattedMessage
                   id="Toolbar.bullist"
                   defaultMessage="Bullist"
                 />
               </Tooltip>
               <IconAction animation="leftRight" src=formatListBulletedBlack />
             </IconButton>
           </GridItem>
         | _ => null
         }}
        {switch (intObjects(width) >= 750) {
         | true =>
           <GridItem top="0" right="0" bottom="0" left="0" xs="no">
             <IconButton padding="4" onClick=insertorderedlist>
               <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
                 <FormattedMessage
                   id="Toolbar.ordlist"
                   defaultMessage="Ordlist"
                 />
               </Tooltip>
               <IconAction animation="leftRight" src=formatListNumberedBlack />
             </IconButton>
           </GridItem>
         | _ => null
         }}
        <GridItem top="0" right="0" bottom="0" left="0" xs="no">
          <IconButton padding="4" onClick=showAlign>
            <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
              <FormattedMessage id="Toolbar.align" defaultMessage="Align" />
            </Tooltip>
            <IconAction animation="leftRight" src=formatAlignRightBlack />
          </IconButton>
          {state.showAlign
             ? <>
                 <SelectMenu
                   top="50%"
                   transform="translate(0, -50%)"
                   minWidth="auto"
                   maxHeight="280"
                   minHeight="0"
                   topLeft="12"
                   topRight="12"
                   bottomRight="12"
                   bottomLeft="12"
                   paddingRight="8"
                   paddingLeft="8">
                   <MenuItem
                     top="0"
                     right="8"
                     bottom="0"
                     left="8"
                     topLeft="12"
                     topRight="12"
                     bottomRight="12"
                     bottomLeft="12"
                     onClick=alignLeft>
                     <Tooltip
                       location="top" backgroundColor="rgba(255,0,0,0.8)">
                       <FormattedMessage
                         id="Toolbar.left"
                         defaultMessage="Left"
                       />
                     </Tooltip>
                     <IconGeneral src=formatAlignLeftBlack />
                   </MenuItem>
                   <MenuItem
                     top="0"
                     right="8"
                     bottom="0"
                     left="8"
                     topLeft="12"
                     topRight="12"
                     bottomRight="12"
                     bottomLeft="12"
                     onClick=alignCenter>
                     <Tooltip
                       location="top" backgroundColor="rgba(255,0,0,0.8)">
                       <FormattedMessage
                         id="Toolbar.center"
                         defaultMessage="Center"
                       />
                     </Tooltip>
                     <IconGeneral src=formatAlignCenterBlack />
                   </MenuItem>
                   <MenuItem
                     top="0"
                     right="8"
                     bottom="0"
                     left="8"
                     topLeft="12"
                     topRight="12"
                     bottomRight="12"
                     bottomLeft="12"
                     onClick=alignRight>
                     <Tooltip
                       location="top" backgroundColor="rgba(255,0,0,0.8)">
                       <FormattedMessage
                         id="Toolbar.right"
                         defaultMessage="Right"
                       />
                     </Tooltip>
                     <IconGeneral src=formatAlignRightBlack />
                   </MenuItem>
                 </SelectMenu>
                 <BackgroundBoard
                   showBackground={state.showAlign}
                   backgroundColor="transparent"
                   onClick=showAlign
                 />
               </>
             : null}
        </GridItem>
        <GridItem
          style={ReactDOMRe.Style.make(
            ~height="25px",
            ~marginTop="6px",
            ~marginRight="3px",
            ~borderRight="1px solid rgba(0,0,0,0.08)",
            (),
          )}
          top="0"
          right="0"
          bottom="0"
          left="3"
          xs="no">
          null
        </GridItem>
        <GridItem top="0" right="0" bottom="0" left="0" xs="no">
          <IconButton padding="4">
            <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
              <FormattedMessage id="Toolbar.color" defaultMessage="Color" />
            </Tooltip>
            <IconAction animation="leftRight" src=textFormatBlack />
          </IconButton>
        </GridItem>
        <GridItem top="0" right="0" bottom="0" left="0" xs="no">
          <IconButton padding="4" onClick=underline>
            <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
              <FormattedMessage
                id="Toolbar.underline"
                defaultMessage="Underline"
              />
            </Tooltip>
            <IconAction animation="leftRight" src=formatUnderlinedBlack />
          </IconButton>
        </GridItem>
        <GridItem top="0" right="0" bottom="0" left="0" xs="no">
          <IconButton padding="4" onClick=formatItalic>
            <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
              <FormattedMessage id="Toolbar.italic" defaultMessage="Italic" />
            </Tooltip>
            <IconAction animation="leftRight" src=formatItalicBlack />
          </IconButton>
        </GridItem>
        <GridItem top="0" right="0" bottom="0" left="0" xs="no">
          <IconButton padding="4" onClick=formatBold>
            <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
              <FormattedMessage id="Toolbar.bold" defaultMessage="Bold" />
            </Tooltip>
            <IconAction animation="leftRight" src=formatBoldBlack />
          </IconButton>
        </GridItem>
        <GridItem
          style={ReactDOMRe.Style.make(
            ~height="25px",
            ~marginTop="6px",
            ~marginRight="3px",
            ~borderRight="1px solid rgba(0,0,0,0.08)",
            (),
          )}
          top="0"
          right="0"
          bottom="0"
          left="3"
          xs="no">
          null
        </GridItem>
        <GridItem top="0" right="0" bottom="0" left="6" xs="no">
          <IconButton padding="4" onClick=showSize>
            <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
              <FormattedMessage id="Toolbar.size" defaultMessage="Size" />
            </Tooltip>
            <IconAction animation="leftRight" src=formatSizeBlack />
          </IconButton>
          {state.showSize
             ? <>
                 <SelectMenu
                   top="50%"
                   transform="translate(0, -50%)"
                   minWidth="auto"
                   maxHeight="280"
                   minHeight="0"
                   topLeft="12"
                   topRight="12"
                   bottomRight="12"
                   bottomLeft="12"
                   paddingRight="8"
                   paddingLeft="8">
                   {state.sizeitems
                    |> Array.map(sizeitem =>
                         <MenuItem
                           top="0"
                           right="8"
                           bottom="0"
                           left="8"
                           disablePadding={sizeitem.disablePadding}
                           topLeft="12"
                           topRight="12"
                           bottomRight="12"
                           bottomLeft="12"
                           onClick={_ => sizeitem.size |> clickSizeMenu}>
                           {sizeitem.value |> string}
                         </MenuItem>
                       )
                    |> array}
                 </SelectMenu>
                 <BackgroundBoard
                   showBackground={state.showSize}
                   backgroundColor="transparent"
                   onClick=showSize
                 />
               </>
             : null}
        </GridItem>
        <GridItem
          style={ReactDOMRe.Style.make(~minWidth="135px", ())}
          top="0"
          right="0"
          bottom="0"
          left="6"
          xs="auto">
          <SelectStandard
            top="0"
            right="0"
            bottom="0"
            left="0"
            borderTop="6"
            borderBottom="6"
            borderWidth="0"
            enterBorderColor="rgba(255,0,0,0.8)"
            downBorderColor="rgba(255,0,0,0.6)"
            borderColor="rgba(0,0,0,0.2)"
            value={state.name}
            disabled={disabled |> disabledObjects}
            onClick=showName>
            ...(
                 state.showName
                   ? <SelectMenu
                       top="50%"
                       transform="translate(0, -50%)"
                       maxHeight="280"
                       minHeight="0"
                       topLeft="12"
                       topRight="12"
                       bottomRight="12"
                       bottomLeft="12"
                       paddingRight="8"
                       paddingLeft="8">
                       {state.nameitems
                        |> Array.map(nameitem =>
                             <MenuItem
                               top="0"
                               right="8"
                               bottom="0"
                               left="8"
                               disablePadding={nameitem.optionPadding}
                               topLeft="12"
                               topRight="12"
                               bottomRight="12"
                               bottomLeft="12"
                               onClick={_ => nameitem.value |> clickNameMenu}>
                               {nameitem.value |> string}
                             </MenuItem>
                           )
                        |> array}
                     </SelectMenu>
                   : null,
                 <IconGeneral
                   animation={state.showName |> topDownRorate}
                   src=arrowDownBlack
                 />,
               )
          </SelectStandard>
          <BackgroundBoard
            showBackground={state.showName}
            backgroundColor="transparent"
            onClick=showName
          />
        </GridItem>
        <GridItem top="0" right="0" bottom="0" left="6" xs="no">
          <IconButton padding="4" onClick=clickRedo>
            <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
              <FormattedMessage id="Toolbar.redo" defaultMessage="Redo" />
            </Tooltip>
            <IconAction animation="leftRight" src=redoBlack />
          </IconButton>
        </GridItem>
        <GridItem top="0" right="0" bottom="0" left="6" xs="no">
          <IconButton padding="4" onClick=clickUndo>
            <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
              <FormattedMessage id="Toolbar.undo" defaultMessage="Undo" />
            </Tooltip>
            <IconAction animation="leftRight" src=undoBlack />
          </IconButton>
        </GridItem>
      </GridContainer>
    </AppBar>
    {state.showAnimation
       ? <DialogAnimationBottom showAnimation=true>
           <DialogTitle
             backgroundColor="rgba(255,0,0,1)" color="rgba(255,255,255,1)">
             {"UPLOAD FILE" |> string}
           </DialogTitle>
           <DialogContent right="0" bottom="0" left="0">
             <DialogContentText>
               <GridItem
                 top="0"
                 right="0"
                 bottom="6"
                 left="0"
                 enterBackgroundColor="rgba(255,0,0,1)"
                 backgroundColor="rgba(255,0,0,1)"
                 xs="12">
                 <Tabs
                   id="tool-"
                   index={state.index}
                   short=10
                   height="3"
                   color="rgba(255,255,255,1)">
                   {state.tabitems
                    |> List.mapi((i, tabtitem) =>
                         <Tab
                           showTab={tabtitem.showTab}
                           borderRadius="15"
                           id={"tool-" ++ string_of_int(i)}
                           animationName="none"
                           onClick={_ => i |> clickItemTab}>
                           <IconAction
                             width="28"
                             height="28"
                             animation="leftRight"
                             src={tabtitem.tabImage}
                           />
                         </Tab>
                       )
                    |> Array.of_list
                    |> array}
                 </Tabs>
               </GridItem>
               <GridItem top="25" right="25" left="25" xs="12">
                 {switch (state.index) {
                  | 0 =>
                    <OtherUpload
                      webLoad={disabled |> disabledObjects}
                      showDrop={state.showDrop}
                      showFile={state.showFile}
                      showImage={state.showImage}
                      showVideo={state.showVideo}
                      showAudio={state.showAudio}
                      src={state.imagePath ++ state.src}
                      fileRef
                      onDragOver={event => event |> dragOverFile}
                      onDragLeave={event => event |> dragLeaveFile}
                      onDrop={event =>
                        dropFile(
                          event,
                          ReactEventRe.Synthetic.nativeEvent(event)##dataTransfer##files[0],
                        )
                      }
                      onClick=chooseFile
                      onChange={event =>
                        ReactEvent.Form.target(event)##files[0] |> changeFile
                      }
                    />
                  | 2 =>
                    <GridContainer
                      direction="column" justify="center" alignItem="stretch">
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        <TextFieldOutline
                          top="0"
                          right="0"
                          bottom="0"
                          left="0"
                          borderTop="12"
                          borderBottom="12"
                          type_="text"
                          value={state.webValue}
                          disabled={disabled |> disabledObjects}
                          onChange={event =>
                            ReactEvent.Form.target(event)##value
                            |> changeWebSite
                          }
                          onKeyDown={event =>
                            ReactEvent.Keyboard.keyCode(event)
                            |> keyDownWebSite
                          }>
                          {"Please Paste Picture Path" |> string}
                        </TextFieldOutline>
                      </GridItem>
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        <PasteBoard borderWidth="0">
                          {switch (
                             disabled |> disabledObjects,
                             state.showFile,
                             state.showImage,
                             state.showVideo,
                             state.showAudio,
                           ) {
                           | (false, true, true, _, _) =>
                             <Image
                               width="auto"
                               height="200px"
                               borderRadius="6"
                               src={state.imagePath ++ state.src}
                             />

                           | (false, true, _, true, _) =>
                             <Media
                               width="auto"
                               height="200px"
                               borderRadius="6"
                               src={state.imagePath ++ state.src}
                             />

                           | (false, true, _, _, true) =>
                             <Media
                               variant="audio"
                               borderRadius="6"
                               src={state.imagePath ++ state.src}
                             />

                           | (false, false, _, _, _) =>
                             <PasteInformation
                               titleSize="12"
                               tile={js|如果您的網址正確，這裡將會顯示圖片預覽|js}
                               instruction={js|請注意，未經許可擅用他人在網路上的圖片，不但沒有禮貌，更是侵權的行為|js}
                             />

                           | (_, _, _, _, _) =>
                             <ProgressCircular
                               size="80"
                               color="rgba(0,0,0,0.08)"
                             />
                           }}
                        </PasteBoard>
                      </GridItem>
                    </GridContainer>
                  | _ => null
                  }}
               </GridItem>
             </DialogContentText>
           </DialogContent>
           <DialogActions>
             <GridItem right="0" left="0" xs="12">
               <GridContainer
                 direction="rowReverse" justify="start" alignItem="center">
                 {switch (state.index) {
                  | 1 =>
                    <>
                      <GridItem top="0" bottom="0" left="0" xs="no">
                        <Button
                          enterBackgroundColor="rgba(255,0,0,0.4)"
                          downBackgroundColor="rgba(255,0,0,0.2)"
                          backgroundColor="rgba(255,255,255,1)"
                          color="rgba(255,0,0,1)"
                          disabled={disabled |> disabledObjects}>
                          {"Recording" |> string}
                        </Button>
                      </GridItem>
                      <GridItem top="0" bottom="0" xs="no">
                        <Button
                          enterBackgroundColor="rgba(255,0,0,0.4)"
                          downBackgroundColor="rgba(255,0,0,0.2)"
                          backgroundColor="rgba(255,255,255,1)"
                          color="rgba(255,0,0,1)"
                          disabled={disabled |> disabledObjects}>
                          {"ScreenShot" |> string}
                        </Button>
                      </GridItem>
                    </>
                  | _ =>
                    <GridItem top="0" bottom="0" xs="no">
                      <Button
                        enterBackgroundColor="rgba(255,0,0,0.4)"
                        downBackgroundColor="rgba(255,0,0,0.2)"
                        backgroundColor="rgba(255,255,255,1)"
                        color="rgba(255,0,0,1)"
                        disabled={disabled |> disabledObjects}
                        onClick=insertFile>
                        {"Send" |> string}
                      </Button>
                    </GridItem>
                  }}
                 <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                   <Button
                     enterBackgroundColor="rgba(255,0,0,0.4)"
                     downBackgroundColor="rgba(255,0,0,0.2)"
                     backgroundColor="rgba(255,255,255,1)"
                     color="rgba(255,0,0,1)"
                     disabled={disabled |> disabledObjects}
                     onClick=closeAnimation>
                     {"Cancel" |> string}
                   </Button>
                 </GridItem>
               </GridContainer>
             </GridItem>
           </DialogActions>
         </DialogAnimationBottom>
       : null}
  </>;
};
