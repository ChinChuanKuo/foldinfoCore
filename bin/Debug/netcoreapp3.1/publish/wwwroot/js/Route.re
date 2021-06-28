open Setting;
[@react.component]
let make = _ => {
  let url = ReasonReactRouter.useUrl();

  switch (url.path) {
  | ["login"] => <Login />
  | ["forget"] => <Forget />
  | ["code"] => <Code />
  | ["resend"] => <Resend />
  | ["signup"] => <Signup />
  | ["oauth"] => <Oauth />
  | _ =>
    <NewBookBoard
      autoPath={pathObjects(Js_list.length(url.path), url.path, url.hash)}>
      {switch (url.path) {
       | [] => <Home />
       | ["icon"] => <Icon />
       | ["bookmarks"] => <Bookmarks />
       | ["inside"] => <Inside />
       | ["isoFile"] => <IsoFile />
       | ["product"] => <Product />
       | ["createR"] => <CreateR />
       | ["createF"] => <CreateF />
       | ["createI"] => <CreateI />
       | ["createP"] => <CreateP />
       | ["signlist"] => <Signlist />
       | ["signlistR"] => <SignlistR />
       | ["signlistI"] => <SignlistI />
       | ["signlistF"] => <SignlistF />
       | ["mailistR"] => <MailistR />
       | ["mailistF"] => <MailistF />
       | ["mailistI"] => <MailistI />
       | ["sendistF"] => <SendistF />
       | ["modifyR"] => <ModifyR />
       | ["modifyF"] => <ModifyF />
       | ["modifyI"] => <ModifyI />
       | _ => <Home />
       }}
    </NewBookBoard>
  };
};
