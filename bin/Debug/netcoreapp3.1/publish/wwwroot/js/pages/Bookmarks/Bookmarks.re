open React;
open ReactIntl;
open Path;
open Icons;
open Storage;
open ObjectFormat;

[@react.component]
let make = _ => {
  <Drawer
    style={ReactDOMRe.Style.make(
      ~overflow="hidden",
      ~whiteSpace="nowrap",
      ~borderRight="0",
      ~transition="width 225ms cubic-bezier(0.4, 0, 0.6, 1) 0ms",
      (),
    )}
    top="60"
    left="0"
    width="100vw"
    height="64"
    location="left"
    zIndex="1000">
    <List_ top="16">
      <ListIcon
        style={ReactDOMRe.Style.make(~height="52px", ())}
        enterBackgroundColor="rgba(0,0,0,0.12)"
        downBackgroundColor="rgba(0,0,0,0.06)"
        topLeft="20"
        topRight="20"
        bottomRight="20"
        bottomLeft="20"
        right="0"
        left="0"
        onClick={_ => homePath |> ReasonReactRouter.push}>
        ...(
             <Avatar
               top="0"
               right="0"
               bottom="0"
               left="0"
               color="#909090"
               backgroundColor="rgba(0,0,0,0.08)">
               {"name" |> Locals.select |> checkObjects |> string}
             </Avatar>,
             <Typography variant="subheading">
               {"allname" |> Locals.select |> checkObjects |> string}
             </Typography>,
           )
      </ListIcon>
      <ListIcon
        style={ReactDOMRe.Style.make(~height="52px", ())}
        enterBackgroundColor="rgba(0,0,0,0.12)"
        downBackgroundColor="rgba(0,0,0,0.06)"
        topLeft="20"
        topRight="20"
        bottomRight="20"
        bottomLeft="20"
        right="0"
        left="0"
        onClick={_ => homePath |> ReasonReactRouter.push}>
        ...(
             <IconButton backgroundColor="rgba(0,0,0,0.08)">
               <IconGeneral src=transmissionBlack />
             </IconButton>,
             <Typography variant="subheading">
               {{js|品異單|js} |> string}
             </Typography>,
           )
      </ListIcon>
      <ListIcon
        style={ReactDOMRe.Style.make(~height="52px", ())}
        enterBackgroundColor="rgba(0,0,0,0.12)"
        downBackgroundColor="rgba(0,0,0,0.06)"
        topLeft="20"
        topRight="20"
        bottomRight="20"
        bottomLeft="20"
        right="0"
        left="0"
        onClick={_ => insidePath |> ReasonReactRouter.push}>
        ...(
             <IconButton backgroundColor="rgba(0,0,0,0.08)">
               <IconGeneral src=factoryBlack />
             </IconButton>,
             <Typography variant="subheading">
               {{js|工廠內部通告|js} |> string}
             </Typography>,
           )
      </ListIcon>
      <ListIcon
        style={ReactDOMRe.Style.make(~height="52px", ())}
        enterBackgroundColor="rgba(0,0,0,0.12)"
        downBackgroundColor="rgba(0,0,0,0.06)"
        topLeft="20"
        topRight="20"
        bottomRight="20"
        bottomLeft="20"
        right="0"
        left="0"
        onClick={_ => isoFilePath |> ReasonReactRouter.push}>
        ...(
             <IconButton backgroundColor="rgba(0,0,0,0.08)">
               <IconGeneral src=fileCopyBlack />
             </IconButton>,
             <Typography variant="subheading">
               {{js|ISO三階文件|js} |> string}
             </Typography>,
           )
      </ListIcon>
      <ListIcon
        style={ReactDOMRe.Style.make(~height="52px", ())}
        enterBackgroundColor="rgba(0,0,0,0.12)"
        downBackgroundColor="rgba(0,0,0,0.06)"
        topLeft="20"
        topRight="20"
        bottomRight="20"
        bottomLeft="20"
        right="0"
        left="0"
        onClick={_ => productPath |> ReasonReactRouter.push}>
        ...(
             <IconButton backgroundColor="rgba(0,0,0,0.08)">
               <IconGeneral src=homeBlack />
             </IconButton>,
             <Typography variant="subheading">
               {{js|生產注意事項|js} |> string}
             </Typography>,
           )
      </ListIcon>
    </List_>
    <Divider />
    <List_ top="16">
      <ListIcon
        style={ReactDOMRe.Style.make(~height="52px", ())}
        enterBackgroundColor="rgba(0,0,0,0.12)"
        downBackgroundColor="rgba(0,0,0,0.06)"
        topLeft="20"
        topRight="20"
        bottomRight="20"
        bottomLeft="20"
        right="0"
        left="0"
        onClick={_ => signlistPath |> ReasonReactRouter.push}>
        ...(
             <IconButton backgroundColor="rgba(0,0,0,0.08)">
               <IconGeneral src=homeBlack />
             </IconButton>,
             <Typography variant="subheading">
               {{js|簽核總列表|js} |> string}
             </Typography>,
           )
      </ListIcon>
      <ListIcon
        style={ReactDOMRe.Style.make(~height="52px", ())}
        enterBackgroundColor="rgba(0,0,0,0.12)"
        downBackgroundColor="rgba(0,0,0,0.06)"
        topLeft="20"
        topRight="20"
        bottomRight="20"
        bottomLeft="20"
        right="0"
        left="0"
        onClick={_ => mailistRPath |> ReasonReactRouter.push}>
        ...(
             <IconButton backgroundColor="rgba(0,0,0,0.08)">
               <IconGeneral src=mailBlack />
             </IconButton>,
             <Typography variant="subheading">
               {{js|MAIL通知列表|js} |> string}
             </Typography>,
           )
      </ListIcon>
      <ListIcon
        style={ReactDOMRe.Style.make(~height="52px", ())}
        enterBackgroundColor="rgba(0,0,0,0.12)"
        downBackgroundColor="rgba(0,0,0,0.06)"
        topLeft="20"
        topRight="20"
        bottomRight="20"
        bottomLeft="20"
        right="0"
        left="0"
        onClick={_ => sendistFPath |> ReasonReactRouter.push}>
        ...(
             <IconButton backgroundColor="rgba(0,0,0,0.08)">
               <IconGeneral src=mailBlack />
             </IconButton>,
             <Typography variant="subheading">
               {{js|SEND列表|js} |> string}
             </Typography>,
           )
      </ListIcon>
    </List_>
  </Drawer>;
};
