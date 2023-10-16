open React;
open Together;
open ReactIntl;
open Path;
open Data;
open Icons;
open Items;
open Axiosapi;
open Status;
open Storage;
open SwitchColor;
open IconAnimation;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type photoitem = {
  photoId: int,
  photoImage: bool,
  photoVideo: bool,
  photoAudio: bool,
  photoSrc: string,
  photoPath: string,
  photoOriginal: string,
  photoEncryption: string,
  photoExtension: string,
  photoDate: string,
  photoInsert: bool,
  photoDelete: bool,
};

type item = {
  showFloorMenu: bool,
  flooritems: array(optionitem),
  floor: string,
  workno: string,
  showXps: bool,
  homepage1: string,
  pnumber: string,
  homepageMomo: string,
  showMbMenu: bool,
  mbitems: array(optionitem),
  mb: string,
  showObjMenu: bool,
  objitems: array(optionitem),
  obj: string,
  pn: string,
  showPn: bool,
  pnitems: array(optionitem),
  invest: string,
  amount: string,
  fail: string,
  subject: string,
  containment: string,
  cause: string,
  showRegroupMenu: bool,
  regroupitems: array(optionitem),
  reGroup: string,
  showReplierMenu: bool,
  replieritems: array(optionitem),
  replier: string,
  showIssueMenu: bool,
  issueitems: array(optionitem),
  issuesort: string,
  showCauseMenu: bool,
  causeitems: array(optionitem),
  causeclass: string,
  directPt: string,
  indirectPt: string,
  correctiveaction1: string,
  correctiveaction2: string,
  showFile: bool,
  showImage: bool,
  showVideo: bool,
  showAudio: bool,
  src: string,
  path: string,
  original: string,
  encryption: string,
  extension: string,
  date: string,
  closure: string,
  body: string,
  notice: bool,
  nonstatistical: bool,
  showBelongMenu: bool,
  belongitems: array(optionitem),
  belong: string,
  belonger: string,
  showStageMenu: bool,
  stageitems: array(optionitem),
  stage: string,
  formWork: bool,
};

type state = {
  formLoad: bool,
  formWidth: int,
  formHeight: int,
  showProgress: bool,
  error: bool,
  insert: bool,
  update: bool,
  delete: bool,
  export: bool,
  tabitems: list(tabitem),
  index: int,
  items: array(item),
  showDrop: bool,
  photoitems: array(photoitem),
  showFileFull: bool,
  fileId: string,
  fileTile: string,
  filePath: string,
  fileSrc: string,
  showYoutube: bool,
  youtubeText: string,
};

let newphotoitem =
    (
      id,
      images,
      videos,
      audios,
      src,
      imagePath,
      original,
      encryption,
      extension,
      date,
    ) => [|
  {
    photoId: id,
    photoImage: images,
    photoVideo: videos,
    photoAudio: audios,
    photoSrc: src,
    photoPath: imagePath,
    photoOriginal: original,
    photoEncryption: encryption,
    photoExtension: extension,
    photoDate: date,
    photoInsert: true,
    photoDelete: false,
  },
|];

type action =
  | SettingError
  | SettingFormLoad
  | SettingFormWidth(int, int)
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormItems(array(item))
  | ClickItemTab(int)
  | ShowFloorMenu(int)
  | ClickFloorMenu(string, int)
  | ChangeWorkno(string, int)
  | SettingItemWorkno(
      string,
      bool,
      string,
      string,
      string,
      string,
      array(optionitem),
      string,
      int,
    )
  | ChangePage1(string, int)
  | ChangePnumber(string, int)
  | ChangeMB(string, int)
  | ChangePageMomo(string, int)
  | ShowObjMenu(int)
  | ClickObjMenu(string, int)
  | ShowPn(bool, int)
  | SettingItemPn(array(optionitem), int)
  | ChangePn(string, int)
  | ClickItemPn(string, int)
  | ChangeAmount(string, int)
  | ChangeInvest(string, int)
  | ChangeFail(string, int)
  | ChangeSubject(string, int)
  | ChangeContainment(string, int)
  | ChangeCause(string, int)
  | ShowRegroupMenu(int)
  | ClickRegroupMenu(string, int)
  | ShowReplierMenu(int)
  | SettingItemReplier(array(optionitem), int)
  | ClickReplierMenu(string, int)
  | ShowIssueMenu(int)
  | ClickIssueMenu(string, int)
  | ShowCauseMenu(int)
  | SettingItemCause(array(optionitem), int)
  | ClickCauseMenu(string, int)
  | ChangeDirectPt(string, int)
  | ChangeIndirectPt(string, int)
  | ChangeCorrectiveaction1(string, int)
  | ChangeCorrectiveaction2(string, int)
  | UploadOtherFile(
      bool,
      bool,
      bool,
      string,
      string,
      string,
      string,
      string,
      string,
      int,
    )
  | ChangeClosure(string, int)
  | SwitchNotice(int)
  | SwitchNonstatistical(int)
  | ChangeBody(string, int)
  | ShowBelongMenu(int)
  | ClickBelongMenu(string, int)
  | ChangeBelonger(string, int)
  | ShowStageMenu(int)
  | ClickStageMenu(string, int)
  | ShowDrop(bool)
  | AddPhotoItem(
      bool,
      bool,
      bool,
      string,
      string,
      string,
      string,
      string,
      string,
    )
  | ActionPhotoItem(int)
  | SettingFileItem(string, string, string, string)
  | CloseFileFull
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingError => {...state, error: !state.error}
  | SettingFormLoad => {...state, formLoad: !state.formLoad}
  | SettingFormWidth(width, height) => {
      ...state,
      formWidth: width,
      formHeight: height,
    }
  | ActionShowProgress => {...state, showProgress: !state.showProgress}
  | ActionPermissItems(insert, update, delete, export) => {
      ...state,
      insert,
      update,
      delete,
      export,
    }
  | SettingFormItems(items) => {...state, items}
  | ClickItemTab(index) => {
      ...state,
      tabitems:
        List.mapi(
          (i, tabitem) => {...tabitem, showTab: index == i},
          state.tabitems,
        ),
      index,
    }
  | ShowFloorMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showFloorMenu: !item.showFloorMenu} : item,
          state.items,
        ),
    }
  | ClickFloorMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, floor: value, showFloorMenu: !item.showFloorMenu}
              : item,
          state.items,
        ),
    }
  | ChangeWorkno(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, workno: value, formWork: value == "NA"} : item,
          state.items,
        ),
    }
  | SettingItemWorkno(
      workno,
      showXps,
      homepage1,
      pnumber,
      homepageMomo,
      mb,
      mbitems,
      amount,
      index,
    ) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                workno,
                showXps,
                homepage1,
                pnumber,
                homepageMomo,
                mb,
                mbitems,
                amount,
              }
              : item,
          state.items,
        ),
    }
  | ChangePage1(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, homepage1: value} : item,
          state.items,
        ),
    }
  | ChangePnumber(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, pnumber: value} : item,
          state.items,
        ),
    }
  | ChangeMB(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, mb: value} : item,
          state.items,
        ),
    }
  | ChangePageMomo(value, index) => {
    ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, homepageMomo: value} : item,
          state.items,
        ),
  }
  | ShowObjMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showObjMenu: !item.showObjMenu} : item,
          state.items,
        ),
    }
  | ClickObjMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, obj: value, showObjMenu: !item.showObjMenu} : item,
          state.items,
        ),
    }
  | ShowPn(showPn, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showPn} : item,
          state.items,
        ),
    }
  | SettingItemPn(items, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, pnitems: items, showPn: true} : item,
          state.items,
        ),
    }
  | ChangePn(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, pn: value} : item,
          state.items,
        ),
    }
  | ClickItemPn(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, pn: value, showPn: !item.showPn} : item,
          state.items,
        ),
    }
  | ChangeAmount(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, amount: value} : item,
          state.items,
        ),
    }
  | ChangeInvest(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                invest:
                  int_of_string(value) > int_of_string(item.amount)
                    ? "0" : value,
              }
              : item,
          state.items,
        ),
    }
  | ChangeFail(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                fail:
                  int_of_string(value) > int_of_string(item.invest)
                    ? "0" : value,
              }
              : item,
          state.items,
        ),
    }
  | ChangeSubject(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, subject: value} : item,
          state.items,
        ),
    }
  | ChangeContainment(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, containment: value} : item,
          state.items,
        ),
    }
  | ChangeCause(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, cause: value} : item,
          state.items,
        ),
    }
  | ShowRegroupMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showRegroupMenu: !item.showRegroupMenu} : item,
          state.items,
        ),
    }
  | ClickRegroupMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                reGroup: value,
                showRegroupMenu: !item.showRegroupMenu,
              }
              : item,
          state.items,
        ),
    }
  | ShowReplierMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showReplierMenu: !item.showReplierMenu} : item,
          state.items,
        ),
    }
  | SettingItemReplier(items, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, replieritems: items} : item,
          state.items,
        ),
    }
  | ClickReplierMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                replier: value,
                showReplierMenu: !item.showReplierMenu,
              }
              : item,
          state.items,
        ),
    }
  | ShowIssueMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showIssueMenu: !item.showIssueMenu} : item,
          state.items,
        ),
    }
  | ClickIssueMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                issuesort: value,
                showIssueMenu: !item.showIssueMenu,
              }
              : item,
          state.items,
        ),
    }
  | ShowCauseMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showCauseMenu: !item.showCauseMenu} : item,
          state.items,
        ),
    }
  | SettingItemCause(items, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, causeitems: items} : item,
          state.items,
        ),
    }
  | ClickCauseMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                causeclass: value,
                showCauseMenu: !item.showCauseMenu,
              }
              : item,
          state.items,
        ),
    }
  | ChangeDirectPt(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, directPt: value} : item,
          state.items,
        ),
    }
  | ChangeIndirectPt(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, indirectPt: value} : item,
          state.items,
        ),
    }
  | ChangeCorrectiveaction1(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, correctiveaction1: value} : item,
          state.items,
        ),
    }
  | ChangeCorrectiveaction2(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, correctiveaction2: value} : item,
          state.items,
        ),
    }
  | UploadOtherFile(
      showImage,
      showVideo,
      showAudio,
      src,
      path,
      original,
      encryption,
      extension,
      date,
      index,
    ) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                showFile: true,
                showImage,
                showVideo,
                showAudio,
                src,
                path,
                original,
                encryption,
                extension,
                date,
              }
              : item,
          state.items,
        ),
    }
  | ChangeClosure(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, closure: value} : item,
          state.items,
        ),
    }
  | SwitchNotice(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, notice: !item.notice} : item,
          state.items,
        ),
    }
  | SwitchNonstatistical(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, nonstatistical: !item.nonstatistical} : item,
          state.items,
        ),
    }
  | ChangeBody(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, body: value} : item,
          state.items,
        ),
    }
  | ShowBelongMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showBelongMenu: !item.showBelongMenu} : item,
          state.items,
        ),
    }
  | ClickBelongMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                belong: value,
                showBelongMenu: !item.showBelongMenu,
              }
              : item,
          state.items,
        ),
    }
  | ChangeBelonger(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, belonger: value} : item,
          state.items,
        ),
    }
  | ShowStageMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showStageMenu: !item.showStageMenu} : item,
          state.items,
        ),
    }
  | ClickStageMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, stage: value, showStageMenu: !item.showStageMenu}
              : item,
          state.items,
        ),
    }
  | ShowDrop(showDrop) => {...state, showDrop}
  | AddPhotoItem(
      images,
      videos,
      audios,
      src,
      imagePath,
      original,
      encryption,
      extension,
      date,
    ) => {
      ...state,
      photoitems:
        Array.append(
          state.photoitems,
          newphotoitem(
            Js_array.length(state.photoitems) + 1,
            images,
            videos,
            audios,
            src,
            imagePath,
            original,
            encryption,
            extension,
            date,
          ),
        ),
    }
  | ActionPhotoItem(index) => {
      ...state,
      photoitems:
        Array.mapi(
          (i, photoitem) =>
            index == i
              ? {...photoitem, photoDelete: !photoitem.photoDelete}
              : photoitem,
          state.photoitems,
        ),
    }
  | SettingFileItem(id, tile, path, src) => {
      ...state,
      fileId: id,
      fileTile: tile,
      filePath: path,
      fileSrc: src,
      showFileFull: !state.showFileFull,
    }
  | CloseFileFull => {...state, showFileFull: !state.showFileFull}
  | ActionSnackBar(youtubeText, showYoutube) => {
      ...state,
      youtubeText,
      showYoutube,
    }
  };

let initialState = {
  formLoad: false,
  formWidth: 0,
  formHeight: 0,
  showProgress: true,
  error: false,
  insert: false,
  update: false,
  delete: false,
  export: false,
  tabitems: [
    {showTab: true, tabImage: bookBlack},
    {showTab: false, tabImage: collectionsBlack},
  ],
  index: 0,
  items: [||],
  showDrop: false,
  photoitems: [||],
  showFileFull: false,
  fileId: "",
  fileTile: "",
  filePath: "",
  fileSrc: "",
  showYoutube: false,
  youtubeText: "",
};

let defaultFloat = value =>
  switch (value) {
  | "" => "0.0"
  | _ => value
  };

//string_of_float( float_of_int( Math.round( float_of_int( fail ) /. float_of_int( invest ) *. 10000.0 ) ) )
let resultBadData = (fail, invest) =>
  fail == 0 || fail < 0
    ? "0"
    : invest == 0
        ? "0"
        : string_of_float(
            float_of_int(
              Math.round(
                float_of_int(fail) /. float_of_int(invest) *. 10000.0,
              ),
            )
            /. 100.0,
          );

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);

  let fileRef = useRef(Js.Nullable.null);

  let barShowRestoreAction = youtubeText => {
    ActionSnackBar(youtubeText, true) |> dispatch;
    Js.Global.setTimeout(() => ActionSnackBar("", false) |> dispatch, 5000)
    |> ignore;
  };

  let searchAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Axiosapi.CreateR.search
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               SettingFormItems(response##data##items) |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               SettingError |> dispatch;
               response##data##status |> statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let permissAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Form.permiss
      |> then_(response =>
           {
             ActionPermissItems(
               response##data##insert,
               response##data##update,
               response##data##delete,
               response##data##export,
             )
             |> dispatch;
             searchAJax();
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  useEffect(() =>
    switch (state.formLoad) {
    | true => Some(() => "action" |> Js.log)
    | _ =>
      let testtime = SettingFormLoad |> dispatch;
      let sizeId =
        SettingFormWidth(Window.Sizes.width, Window.Sizes.height) |> dispatch;
      let timeId = permissAJax();
      Some(
        () => {
          testtime;
          sizeId;
          timeId;
        },
      );
    }
  );

  let handleResize = event =>
    SettingFormWidth(
      event##currentTarget##innerWidth,
      event##currentTarget##innerHeight,
    )
    |> dispatch;

  /*let scrollFunc: 'a => unit = [%bs.raw
      func => {| func(state.items.length); |}
    ];
    let handleScrollBar = event =>
      if (event##target##scrollTop
          ++
          event##target##clientHeight ==
          event##target##scrollHeight) {
        ActionShowProgress |> dispatch;
        scrollAJax |> scrollFunc;
      };*/

  useEffect0(() => {
    let sizeId = Window.Listeners.add("resize", handleResize, true) |> ignore;
    /*let scrollId =
      Window.Listeners.add("scroll", handleScrollBar, true) |> ignore;*/
    Some(() => sizeId);
  });

  let clickItemTab = useCallback(i => ClickItemTab(i) |> dispatch);

  let insertAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iIconData(state.items, state.photoitems)
      |> Axiosapi.CreateR.insert
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               "saveSuccess" |> Sessions.create("form");
               homePath |> ReasonReactRouter.push;
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let insertForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      insertAJax();
    });

  let sendAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iIconData(state.items, state.photoitems)
      |> Axiosapi.CreateR.send
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               "sendSuccess" |> Sessions.create("form");
               homePath |> ReasonReactRouter.push;
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let sendForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      sendAJax();
    });

  let showFloorMenu = useCallback(i => ShowFloorMenu(i) |> dispatch);

  let clickFloorMenu =
    useCallback((value, i) => ClickFloorMenu(value, i) |> dispatch);

  let changeWorkno =
    useCallback((value, i) => ChangeWorkno(value, i) |> dispatch);

  let sWorknoAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.CreateR.sWorkno
      |> then_(response =>
           SettingItemWorkno(
             response##data##items[0]##workno,
             response##data##items[0]##showxps,
             response##data##items[0]##custname,
             response##data##items[0]##pnumber,
             response##data##items[0]##mbname,
             response##data##items[0]##mb,
             response##data##items[0]##mbitems,
             response##data##items[0]##amount,
             i,
           )
           |> dispatch
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let keydownWorkno =
    useCallback((keyCode, value, i) =>
      if (keyCode == 13) {
        i |> sWorknoAJax(value);
      }
    );

  let sXpsAJax = value =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.CreateR.sXps
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               SettingFileItem(
                 response##data##formId,
                 response##data##tile,
                 response##data##items[0].path,
                 response##data##items[0].src,
               )
               |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let showXpsFile =
    useCallback(value => {
      ActionShowProgress |> dispatch;
      value |> sXpsAJax;
    });

  let changePage1 =
    useCallback((value, i) => ChangePage1(value, i) |> dispatch);

  let changePnumber =
    useCallback((value, i) => ChangePnumber(value, i) |> dispatch);

  let changeMB =
    useCallback((value, i) => ChangeMB(value, i) |> dispatch);

  let changePageMomo =
    useCallback((value, i) => ChangePageMomo(value, i) |> dispatch);

  let showObjMenu = useCallback(i => ShowObjMenu(i) |> dispatch);

  let clickObjMenu =
    useCallback((value, i) => ClickObjMenu(value, i) |> dispatch);

  let sPnAJax = (workno, value, i) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> sRowsData(workno, value)
      |> Axiosapi.CreateR.sPn
      |> then_(response =>
           SettingItemPn(response##data##items, i) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let changePn =
    useCallback((value, workno, i) => {
      ChangePn(value, i) |> dispatch;
      i |> sPnAJax(workno, value);
    });

  let showPn = useCallback(i => ShowPn(false, i) |> dispatch);

  let clickItemPn =
    useCallback((value, i) => ClickItemPn(value, i) |> dispatch);

  let changeAmount =
    useCallback((value, i) => ChangeAmount(value, i) |> dispatch);

  let changeInvest =
    useCallback((value, i) => {
      let value = int_of_string(value) <= 0 ? "0" : value;
      ChangeInvest(value, i) |> dispatch;
    });

  let changeFail =
    useCallback((value, i) => {
      let value = int_of_string(value) <= 0 ? "0" : value;
      ChangeFail(value, i) |> dispatch;
    });

  let changeSubject =
    useCallback((value, i) => ChangeSubject(value, i) |> dispatch);

  let changeContainment =
    useCallback((value, i) => ChangeContainment(value, i) |> dispatch);

  let changeCause =
    useCallback((value, i) => ChangeCause(value, i) |> dispatch);

  let showRegroupMenu = useCallback(i => ShowRegroupMenu(i) |> dispatch);

  let sRegroupAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.CreateR.sGroup
      |> then_(response => {
           SettingItemReplier(response##data##items, i) |> dispatch |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickRegroupMenu =
    useCallback((value, i) => {
      ClickRegroupMenu(value, i) |> dispatch;
      i |> sRegroupAJax(value);
    });

  let showReplierMenu = useCallback(i => ShowReplierMenu(i) |> dispatch);

  let clickReplierMenu =
    useCallback((value, i) => ClickReplierMenu(value, i) |> dispatch);

  let showIssueMenu = useCallback(i => ShowIssueMenu(i) |> dispatch);

  let sIssueAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.CreateR.sIssus
      |> then_(response =>
           SettingItemCause(response##data##items, i) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickIssueMenu =
    useCallback((value, i) => {
      ClickIssueMenu(value, i) |> dispatch;
      i |> sIssueAJax(value);
    });

  let showCauseMenu = useCallback(i => ShowCauseMenu(i) |> dispatch);

  let clickCauseMenu =
    useCallback((value, i) => ClickCauseMenu(value, i) |> dispatch);

  let changeDirectPt =
    useCallback((value, i) => ChangeDirectPt(value, i) |> dispatch);

  let changeIndirectPt =
    useCallback((value, i) => ChangeIndirectPt(value, i) |> dispatch);

  let changeCorrectiveaction1 =
    useCallback((value, i) => ChangeCorrectiveaction1(value, i) |> dispatch);

  let changeCorrectiveaction2 =
    useCallback((value, i) => ChangeCorrectiveaction2(value, i) |> dispatch);

  let changeClosure =
    useCallback((value, i) => ChangeClosure(value, i) |> dispatch);

  let switchNotice = useCallback(i => SwitchNotice(i) |> dispatch);

  let switchNonstatistical =
    useCallback(i => SwitchNonstatistical(i) |> dispatch);

  let changeBody =
    useCallback((value, i) => ChangeBody(value, i) |> dispatch);

  let showBelongMenu = useCallback(i => ShowBelongMenu(i) |> dispatch);

  let clickBelongMenu =
    useCallback((value, i) => ClickBelongMenu(value, i) |> dispatch);

  let changeBelonger =
    useCallback((value, i) => ChangeBelonger(value, i) |> dispatch);

  let showStageMenu = useCallback(i => ShowStageMenu(i) |> dispatch);

  let clickStageMenu =
    useCallback((value, i) => ClickStageMenu(value, i) |> dispatch);

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
               AddPhotoItem(
                 response##data##images,
                 response##data##videos,
                 response##data##audios,
                 response##data##src,
                 response##data##imagePath,
                 response##data##original,
                 response##data##encryption,
                 response##data##extension,
                 response##data##date,
               )
               |> dispatch;
               ActionShowProgress |> dispatch;
             | _ => ActionShowProgress |> dispatch
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
      ActionShowProgress |> dispatch;
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

  let changeFile =
    useCallback(value => {
      ActionShowProgress |> dispatch;
      value |> uploadAJax;
    });

  let actionPhoto = useCallback(i => ActionPhotoItem(i) |> dispatch);

  let upOtherAJax = (files, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", files) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               UploadOtherFile(
                 response##data##images,
                 response##data##videos,
                 response##data##audios,
                 response##data##src,
                 response##data##imagePath,
                 response##data##original,
                 response##data##encryption,
                 response##data##extension,
                 response##data##date,
                 i,
               )
               |> dispatch;
               ActionShowProgress |> dispatch;
             | _ => ActionShowProgress |> dispatch
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );
  };

  let dropOtherFile =
    useCallback((event, value, i) => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowDrop(false) |> dispatch;
      i |> upOtherAJax(value);
    });

  let changeOtherFile =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upOtherAJax(value);
    });

  let closeFileFull = useCallback(_ => CloseFileFull |> dispatch);

  let downloadAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.fileId)
      |> Axiosapi.CreateR.download
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               response##data##value |> Window.Locations.assign;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let downloadAlbum =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      downloadAJax();
    });

  <>
    <NewFacetube showProgress={state.showProgress} error={state.error}>
      <GridItem
        style=marginAuto top="0" right="32" left="32" xs="12" maxWidth="770px">
        <GridContainer direction="column" justify="center" alignItem="stretch">
          <GridItem
            style={ReactDOMRe.Style.make(
              ~position="sticky",
              ~top="0px",
              ~zIndex="1000",
              (),
            )}
            top="0"
            left="0"
            xs="auto">
            <GridContainer direction="row" justify="around" alignItem="center">
              <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                <Tabs id="report-" index={state.index} height="3">
                  {state.tabitems
                   |> List.mapi((i, tabitem) =>
                        <Tab
                          showTab={tabitem.showTab}
                          maxWidth="111.6"
                          borderRadius="15"
                          id={"report-" ++ string_of_int(i)}
                          animationName="none"
                          onClick={_ => i |> clickItemTab}>
                          <IconAction
                            width="28"
                            height="28"
                            animation="leftRight"
                            src={tabitem.tabImage}
                          />
                        </Tab>
                      )
                   |> Array.of_list
                   |> array}
                </Tabs>
              </GridItem>
              {state.insert
                 ? <>
                     <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                       <Button
                         disabled={state.showProgress} onClick=insertForm>
                         <FormattedMessage id="save" defaultMessage="Save" />
                       </Button>
                     </GridItem>
                     <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                       <Button disabled={state.showProgress} onClick=sendForm>
                         <FormattedMessage id="send" defaultMessage="Send" />
                       </Button>
                     </GridItem>
                   </>
                 : null}
            </GridContainer>
          </GridItem>
          {switch (state.index) {
           | 0 =>
             state.items
             |> Array.mapi((i, item) =>
                  <>
                    <GridItem top="18" bottom="0" left="0" xs="auto">
                      <Typography
                        variant="subheading"
                        color="rgba(0,0,0,0.6)"
                        fontWeight="bolder">
                        {{js|【Characterize】問題描述|js} |> string}
                      </Typography>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <SelectStandard
                            top="12"
                            right="0"
                            left="0"
                            tile={js|生產樓層|js}
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.floor}
                            disabled={state.showProgress}
                            onClick={_ => i |> showFloorMenu}>
                            ...(
                                 item.showFloorMenu
                                   ? <SelectMenu
                                       top="0"
                                       transform="translate(0, 0)"
                                       maxHeight="280"
                                       minHeight="0"
                                       topLeft="12"
                                       topRight="12"
                                       bottomRight="12"
                                       bottomLeft="12"
                                       paddingRight="8"
                                       paddingLeft="8">
                                       {item.flooritems
                                        |> Array.map(flooritem =>
                                             <MenuItem
                                               top="0"
                                               right="8"
                                               bottom="0"
                                               left="8"
                                               disablePadding={
                                                                flooritem.
                                                                  optionPadding
                                                              }
                                               topLeft="12"
                                               topRight="12"
                                               bottomRight="12"
                                               bottomLeft="12"
                                               onClick={_ =>
                                                 i
                                                 |> clickFloorMenu(
                                                      flooritem.value,
                                                    )
                                               }>
                                               {flooritem.value |> string}
                                             </MenuItem>
                                           )
                                        |> array}
                                     </SelectMenu>
                                   : null,
                                 <IconGeneral
                                   animation={
                                     item.showFloorMenu |> topDownRorate
                                   }
                                   src=arrowDownBlack
                                 />,
                               )
                          </SelectStandard>
                          <BackgroundBoard
                            showBackground={item.showFloorMenu}
                            backgroundColor="transparent"
                            onClick={_ => i |> showFloorMenu}
                          />
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <GridContainer
                            direction="row"
                            justify="between"
                            alignItem="center">
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="auto">
                              <TextFieldStandard
                                top="12"
                                right="0"
                                left="0"
                                labelColor="rgba(255,0,0,0.8)"
                                enterBorderColor="rgba(255,0,0,0.8)"
                                downBorderColor="rgba(255,0,0,0.6)"
                                borderColor="rgba(0,0,0,0.2)"
                                value={item.workno}
                                disabled={state.showProgress}
                                onChange={event =>
                                  i
                                  |> changeWorkno(
                                       ReactEvent.Form.target(event)##value,
                                     )
                                }
                                onKeyDown={event =>
                                  i
                                  |> keydownWorkno(
                                       ReactEvent.Keyboard.keyCode(event),
                                       ReactEvent.Keyboard.target(event)##value,
                                     )
                                }>
                                {{js|工單|js} |> string}
                              </TextFieldStandard>
                            </GridItem>
                            {item.showXps
                               ? <GridItem top="0" bottom="0" left="0" xs="no">
                                   <IconButton
                                     padding="2"
                                     disabled={state.showProgress}
                                     onClick={_ => item.workno |> showXpsFile}>
                                     <IconAction
                                       animation="circle"
                                       src=visibilityBlack
                                     />
                                   </IconButton>
                                 </GridItem>
                               : null}
                          </GridContainer>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.homepage1}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changePage1(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|客戶|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.pnumber}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changePnumber(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|產品規格單|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.homepageMomo}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changePageMomo(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|機種|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.mb}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeMB(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|M/B|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <SelectStandard
                            top="12"
                            right="0"
                            left="0"
                            tile={js|品異來源|js}
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.obj}
                            disabled={state.showProgress}
                            onClick={_ => i |> showObjMenu}>
                            ...(
                                 item.showObjMenu
                                   ? <SelectMenu
                                       top="0"
                                       transform="translate(0, 0)"
                                       maxHeight="280"
                                       minHeight="0"
                                       topLeft="12"
                                       topRight="12"
                                       bottomRight="12"
                                       bottomLeft="12"
                                       paddingRight="8"
                                       paddingLeft="8">
                                       {item.objitems
                                        |> Array.map(objitem =>
                                             <MenuItem
                                               top="0"
                                               right="8"
                                               bottom="0"
                                               left="8"
                                               disablePadding={
                                                                objitem.
                                                                  optionPadding
                                                              }
                                               topLeft="12"
                                               topRight="12"
                                               bottomRight="12"
                                               bottomLeft="12"
                                               onClick={_ =>
                                                 i
                                                 |> clickObjMenu(
                                                      objitem.value,
                                                    )
                                               }>
                                               {objitem.value |> string}
                                             </MenuItem>
                                           )
                                        |> array}
                                     </SelectMenu>
                                   : null,
                                 <IconGeneral
                                   animation={
                                     item.showObjMenu |> topDownRorate
                                   }
                                   src=arrowDownBlack
                                 />,
                               )
                          </SelectStandard>
                          <BackgroundBoard
                            showBackground={item.showObjMenu}
                            backgroundColor="transparent"
                            onClick={_ => i |> showObjMenu}
                          />
                        </GridItem>
                        <GridItem
                          style={ReactDOMRe.Style.make(
                            ~position="relative",
                            (),
                          )}
                          top="0"
                          right="0"
                          bottom="0"
                          left="0"
                          xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.pn}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changePn(
                                   ReactEvent.Form.target(event)##value,
                                   item.workno,
                                 )
                            }
                            onClick={_ => i |> showPn}>
                            {{js|不良料號|js} |> string}
                          </TextFieldStandard>
                          {item.showPn
                             ? <>
                                 <SelectMenu
                                   top="100%"
                                   transform="translate(0, 0)"
                                   maxHeight="280"
                                   minHeight="0"
                                   topLeft="12"
                                   topRight="12"
                                   bottomRight="12"
                                   bottomLeft="12"
                                   paddingRight="8"
                                   paddingLeft="8">
                                   {item.pnitems
                                    |> Array.map(pnitem =>
                                         <MenuItem
                                           top="8"
                                           right="15"
                                           bottom="8"
                                           left="6"
                                           enterBackgroundColor="rgba(0,0,0,0.06)"
                                           downBackgroundColor="rgba(0,0,0,0.08)"
                                           topLeft="12"
                                           topRight="12"
                                           bottomRight="12"
                                           bottomLeft="12"
                                           onClick={_ =>
                                             i |> clickItemPn(pnitem.value)
                                           }>
                                           <Typography variant="subheading">
                                             {pnitem.value |> string}
                                           </Typography>
                                         </MenuItem>
                                       )
                                    |> array}
                                 </SelectMenu>
                                 <BackgroundBoard
                                   showBackground=true
                                   backgroundColor="transparent"
                                   onClick={_ => i |> showPn}
                                 />
                               </>
                             : null}
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            type_="number"
                            value={item.amount}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeAmount(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|工單總數|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            type_="number"
                            value={item.invest}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeInvest(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|投入數|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            type_="number"
                            value={item.fail}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeFail(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|不良數量|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="20" right="0" bottom="0" left="0" xs="auto">
                          <Typography variant="subheading" fontWeight="bolder">
                            {{js|不良率:|js}
                             ++ resultBadData(
                                  int_of_string(item.fail),
                                  int_of_string(item.invest),
                                )
                             ++ "%"
                             |> string}
                          </Typography>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <TextFieldStandard
                        top="12"
                        right="0"
                        left="0"
                        labelColor="rgba(255,0,0,0.8)"
                        enterBorderColor="rgba(255,0,0,0.8)"
                        downBorderColor="rgba(255,0,0,0.6)"
                        borderColor="rgba(0,0,0,0.2)"
                        value={item.subject}
                        disabled={state.showProgress}
                        onChange={event =>
                          i
                          |> changeSubject(
                               ReactEvent.Form.target(event)##value,
                             )
                        }>
                        {{js|異常內容|js} |> string}
                      </TextFieldStandard>
                    </GridItem>
                    <GridItem right="0" bottom="0" left="0" xs="auto">
                      <OtherUpload
                        webLoad={state.showProgress}
                        showDrop={state.showDrop}
                        showFile={item.showFile}
                        showImage={item.showImage}
                        showVideo={item.showVideo}
                        showAudio={item.showAudio}
                        src={item.path ++ item.src}
                        fileRef
                        onDragOver={event => event |> dragOverFile}
                        onDragLeave={event => event |> dragLeaveFile}
                        onDrop={event =>
                          i
                          |> dropOtherFile(
                               event,
                               ReactEvent.Synthetic.nativeEvent(event)##dataTransfer##files[0],
                             )
                        }
                        disabled={state.showProgress}
                        onClick=chooseFile
                        onChange={event =>
                          i
                          |> changeOtherFile(
                               ReactEvent.Form.target(event)##files[0],
                             )
                        }
                      />
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <SelectStandard
                            top="12"
                            right="0"
                            left="0"
                            tile={js|處理部門|js}
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.reGroup}
                            disabled={state.showProgress}
                            onClick={_ => i |> showRegroupMenu}>
                            ...(
                                 item.showRegroupMenu
                                   ? <SelectMenu
                                       top="0"
                                       transform="translate(0, 0)"
                                       maxHeight="280"
                                       minHeight="0"
                                       topLeft="12"
                                       topRight="12"
                                       bottomRight="12"
                                       bottomLeft="12"
                                       paddingRight="8"
                                       paddingLeft="8">
                                       {item.regroupitems
                                        |> Array.map(regroupitem =>
                                             <MenuItem
                                               top="0"
                                               right="8"
                                               bottom="0"
                                               left="8"
                                               disablePadding={
                                                                regroupitem.
                                                                  optionPadding
                                                              }
                                               topLeft="12"
                                               topRight="12"
                                               bottomRight="12"
                                               bottomLeft="12"
                                               onClick={_ =>
                                                 i
                                                 |> clickRegroupMenu(
                                                      regroupitem.value,
                                                    )
                                               }>
                                               {regroupitem.value |> string}
                                             </MenuItem>
                                           )
                                        |> array}
                                     </SelectMenu>
                                   : null,
                                 <IconGeneral
                                   animation={
                                     item.showRegroupMenu |> topDownRorate
                                   }
                                   src=arrowDownBlack
                                 />,
                               )
                          </SelectStandard>
                          <BackgroundBoard
                            showBackground={item.showRegroupMenu}
                            backgroundColor="transparent"
                            onClick={_ => i |> showRegroupMenu}
                          />
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <SelectStandard
                            top="12"
                            right="0"
                            left="0"
                            tile={js|處理者|js}
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.replier}
                            disabled={state.showProgress}
                            onClick={_ => i |> showReplierMenu}>
                            ...(
                                 item.showReplierMenu
                                   ? <SelectMenu
                                       top="0"
                                       transform="translate(0, 0)"
                                       maxHeight="280"
                                       minHeight="0"
                                       topLeft="12"
                                       topRight="12"
                                       bottomRight="12"
                                       bottomLeft="12"
                                       paddingRight="8"
                                       paddingLeft="8">
                                       {item.replieritems
                                        |> Array.map(replieritem =>
                                             <MenuItem
                                               top="0"
                                               right="8"
                                               bottom="0"
                                               left="8"
                                               disablePadding={
                                                                replieritem.
                                                                  optionPadding
                                                              }
                                               topLeft="12"
                                               topRight="12"
                                               bottomRight="12"
                                               bottomLeft="12"
                                               onClick={_ =>
                                                 i
                                                 |> clickReplierMenu(
                                                      replieritem.value,
                                                    )
                                               }>
                                               {replieritem.value |> string}
                                             </MenuItem>
                                           )
                                        |> array}
                                     </SelectMenu>
                                   : null,
                                 <IconGeneral
                                   animation={
                                     item.showReplierMenu |> topDownRorate
                                   }
                                   src=arrowDownBlack
                                 />,
                               )
                          </SelectStandard>
                          <BackgroundBoard
                            showBackground={item.showReplierMenu}
                            backgroundColor="transparent"
                            onClick={_ => i |> showReplierMenu}
                          />
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <SelectStandard
                            top="12"
                            right="0"
                            left="0"
                            tile={js|原因分類|js}
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.issuesort}
                            disabled=true
                            onClick={_ => i |> showIssueMenu}>
                            ...(
                                 item.showIssueMenu
                                   ? <SelectMenu
                                       top="0"
                                       transform="translate(0, 0)"
                                       maxHeight="280"
                                       minHeight="0"
                                       topLeft="12"
                                       topRight="12"
                                       bottomRight="12"
                                       bottomLeft="12"
                                       paddingRight="8"
                                       paddingLeft="8">
                                       {item.issueitems
                                        |> Array.map(issueitem =>
                                             <MenuItem
                                               top="0"
                                               right="8"
                                               bottom="0"
                                               left="8"
                                               disablePadding={
                                                                issueitem.
                                                                  optionPadding
                                                              }
                                               topLeft="12"
                                               topRight="12"
                                               bottomRight="12"
                                               bottomLeft="12"
                                               onClick={_ =>
                                                 i
                                                 |> clickIssueMenu(
                                                      issueitem.value,
                                                    )
                                               }>
                                               {issueitem.value |> string}
                                             </MenuItem>
                                           )
                                        |> array}
                                     </SelectMenu>
                                   : null,
                                 <IconGeneral
                                   animation={
                                     item.showIssueMenu |> topDownRorate
                                   }
                                   src=arrowDownBlack
                                 />,
                               )
                          </SelectStandard>
                          <BackgroundBoard
                            showBackground={item.showIssueMenu}
                            backgroundColor="transparent"
                            onClick={_ => i |> showIssueMenu}
                          />
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <SelectStandard
                            top="12"
                            right="0"
                            left="0"
                            tile={js|原因分類|js}
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.causeclass}
                            disabled=true
                            onClick={_ => i |> showCauseMenu}>
                            ...(
                                 item.showCauseMenu
                                   ? <SelectMenu
                                       top="0"
                                       transform="translate(0, 0)"
                                       maxHeight="280"
                                       minHeight="0"
                                       topLeft="12"
                                       topRight="12"
                                       bottomRight="12"
                                       bottomLeft="12"
                                       paddingRight="8"
                                       paddingLeft="8">
                                       {item.causeitems
                                        |> Array.map(causeitem =>
                                             <MenuItem
                                               top="0"
                                               right="8"
                                               bottom="0"
                                               left="8"
                                               disablePadding={
                                                                causeitem.
                                                                  optionPadding
                                                              }
                                               topLeft="12"
                                               topRight="12"
                                               bottomRight="12"
                                               bottomLeft="12"
                                               onClick={_ =>
                                                 i
                                                 |> clickCauseMenu(
                                                      causeitem.value,
                                                    )
                                               }>
                                               {causeitem.value |> string}
                                             </MenuItem>
                                           )
                                        |> array}
                                     </SelectMenu>
                                   : null,
                                 <IconGeneral
                                   animation={
                                     item.showCauseMenu |> topDownRorate
                                   }
                                   src=arrowDownBlack
                                 />,
                               )
                          </SelectStandard>
                          <BackgroundBoard
                            showBackground={item.showCauseMenu}
                            backgroundColor="transparent"
                            onClick={_ => i |> showCauseMenu}
                          />
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            type_="number"
                            value={item.directPt}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeDirectPt(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|直接損耗工時|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            type_="number"
                            value={item.indirectPt}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeIndirectPt(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|間接損耗工時|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="18" bottom="0" left="0" xs="auto">
                      <Typography
                        variant="subheading"
                        color="rgba(0,0,0,0.6)"
                        fontWeight="bolder">
                        {{js|【Containment】緊急處置|js} |> string}
                      </Typography>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <TextFieldMultiline
                        top="12"
                        right="0"
                        left="0"
                        labelColor="rgba(255,0,0,0.8)"
                        enterBorderColor="rgba(255,0,0,0.8)"
                        downBorderColor="rgba(255,0,0,0.6)"
                        borderColor="rgba(0,0,0,0.2)"
                        rows=3
                        value={item.containment}
                        disabled={state.showProgress}
                        onChange={event =>
                          i
                          |> changeContainment(
                               ReactEvent.Form.target(event)##value,
                             )
                        }>
                        null
                      </TextFieldMultiline>
                    </GridItem>
                    <GridItem top="18" bottom="0" left="0" xs="auto">
                      <Typography
                        variant="subheading"
                        color="rgba(0,0,0,0.6)"
                        fontWeight="bolder">
                        {{js|【Cause】真因調查|js} |> string}
                      </Typography>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <TextFieldMultiline
                        top="12"
                        right="0"
                        left="0"
                        labelColor="rgba(255,0,0,0.8)"
                        enterBorderColor="rgba(255,0,0,0.8)"
                        downBorderColor="rgba(255,0,0,0.6)"
                        borderColor="rgba(0,0,0,0.2)"
                        rows=3
                        value={item.cause}
                        disabled=true
                        onChange={event =>
                          i
                          |> changeCause(
                               ReactEvent.Form.target(event)##value,
                             )
                        }>
                        null
                      </TextFieldMultiline>
                    </GridItem>
                    <GridItem top="18" bottom="6" left="0" xs="auto">
                      <Typography
                        variant="subheading"
                        color="rgba(0,0,0,0.6)"
                        fontWeight="bolder">
                        {{js|【Corrective Action】改善對策|js} |> string}
                      </Typography>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <TextFieldMultiline
                        top="12"
                        right="0"
                        left="0"
                        labelColor="rgba(255,0,0,0.8)"
                        enterBorderColor="rgba(255,0,0,0.8)"
                        downBorderColor="rgba(255,0,0,0.6)"
                        borderColor="rgba(0,0,0,0.2)"
                        rows=3
                        value={item.correctiveaction1}
                        disabled=true
                        onChange={event =>
                          i
                          |> changeCorrectiveaction1(
                               ReactEvent.Form.target(event)##value,
                             )
                        }>
                        {"Short Term" |> string}
                      </TextFieldMultiline>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <TextFieldMultiline
                        top="12"
                        right="0"
                        left="0"
                        labelColor="rgba(255,0,0,0.8)"
                        enterBorderColor="rgba(255,0,0,0.8)"
                        downBorderColor="rgba(255,0,0,0.6)"
                        borderColor="rgba(0,0,0,0.2)"
                        rows=3
                        value={item.correctiveaction2}
                        disabled=true
                        onChange={event =>
                          i
                          |> changeCorrectiveaction2(
                               ReactEvent.Form.target(event)##value,
                             )
                        }>
                        {"Long Term" |> string}
                      </TextFieldMultiline>
                    </GridItem>
                    <GridItem top="18" bottom="0" left="0" xs="auto">
                      <Typography
                        variant="subheading"
                        color="rgba(0,0,0,0.6)"
                        fontWeight="bolder">
                        {{js|【Closure】成效驗證|js} |> string}
                      </Typography>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <Switch
                            right="0"
                            checked={item.notice}
                            circleColor={item.notice |> circle}
                            linearColor={item.notice |> linear}
                            fontColor={item.notice |> font}
                            disabled=true
                            onClick={_ => i |> switchNotice}>
                            {{js|列入注意事項|js} |> string}
                          </Switch>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <Switch
                            right="0"
                            checked={item.nonstatistical}
                            circleColor={item.nonstatistical |> circle}
                            linearColor={item.nonstatistical |> linear}
                            fontColor={item.nonstatistical |> font}
                            disabled=true
                            onClick={_ => i |> switchNonstatistical}>
                            {{js|不列入統計資料|js} |> string}
                          </Switch>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldMultiline
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            rows=3
                            value={item.closure}
                            disabled=true
                            onChange={event =>
                              i
                              |> changeClosure(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            null
                          </TextFieldMultiline>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldMultiline
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            rows=3
                            value={item.body}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeBody(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            null
                          </TextFieldMultiline>
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <SelectStandard
                            top="12"
                            right="0"
                            left="0"
                            tile={js|責任單位|js}
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.belong}
                            disabled=true
                            onClick={_ => i |> showBelongMenu}>
                            ...(
                                 item.showBelongMenu
                                   ? <SelectMenu
                                       top="100%"
                                       transform="translate(0, -100%)"
                                       maxHeight="280"
                                       minHeight="0"
                                       topLeft="12"
                                       topRight="12"
                                       bottomRight="12"
                                       bottomLeft="12"
                                       paddingRight="8"
                                       paddingLeft="8">
                                       {item.belongitems
                                        |> Array.map(belongitem =>
                                             <MenuItem
                                               top="0"
                                               right="8"
                                               bottom="0"
                                               left="8"
                                               disablePadding={
                                                                belongitem.
                                                                  optionPadding
                                                              }
                                               topLeft="12"
                                               topRight="12"
                                               bottomRight="12"
                                               bottomLeft="12"
                                               onClick={_ =>
                                                 i
                                                 |> clickBelongMenu(
                                                      belongitem.value,
                                                    )
                                               }>
                                               {belongitem.value |> string}
                                             </MenuItem>
                                           )
                                        |> array}
                                     </SelectMenu>
                                   : null,
                                 <IconGeneral
                                   animation={
                                     item.showBelongMenu |> topDownRorate
                                   }
                                   src=arrowDownBlack
                                 />,
                               )
                          </SelectStandard>
                          <BackgroundBoard
                            showBackground={item.showBelongMenu}
                            backgroundColor="transparent"
                            onClick={_ => i |> showBelongMenu}
                          />
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <TextFieldStandard
                            top="12"
                            right="0"
                            left="0"
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.belonger}
                            disabled=true
                            onChange={event =>
                              i
                              |> changeBelonger(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|責任人員|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <SelectStandard
                            top="12"
                            right="0"
                            left="0"
                            tile={js|處理狀態|js}
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.stage}
                            disabled=true
                            onClick={_ => i |> showStageMenu}>
                            ...(
                                 item.showStageMenu
                                   ? <SelectMenu
                                       top="100%"
                                       transform="translate(0, -100%)"
                                       maxHeight="280"
                                       minHeight="0"
                                       topLeft="12"
                                       topRight="12"
                                       bottomRight="12"
                                       bottomLeft="12"
                                       paddingRight="8"
                                       paddingLeft="8">
                                       {item.stageitems
                                        |> Array.map(stageitem =>
                                             <MenuItem
                                               top="0"
                                               right="8"
                                               bottom="0"
                                               left="8"
                                               disablePadding={
                                                                stageitem.
                                                                  optionPadding
                                                              }
                                               topLeft="12"
                                               topRight="12"
                                               bottomRight="12"
                                               bottomLeft="12"
                                               onClick={_ =>
                                                 i
                                                 |> clickStageMenu(
                                                      stageitem.value,
                                                    )
                                               }>
                                               {stageitem.value |> string}
                                             </MenuItem>
                                           )
                                        |> array}
                                     </SelectMenu>
                                   : null,
                                 <IconGeneral
                                   animation={
                                     item.showStageMenu |> topDownRorate
                                   }
                                   src=arrowDownBlack
                                 />,
                               )
                          </SelectStandard>
                          <BackgroundBoard
                            showBackground={item.showStageMenu}
                            backgroundColor="transparent"
                            onClick={_ => i |> showStageMenu}
                          />
                        </GridItem>
                      </GridContainer>
                    </GridItem>
                  </>
                )
             |> array
           | _ =>
             <>
               <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                 <GeneralUpload
                   webLoad={state.showProgress}
                   showDrop={state.showDrop}
                   fileRef
                   onDragOver={event => event |> dragOverFile}
                   onDragLeave={event => event |> dragLeaveFile}
                   onDrop={event =>
                     ReactEvent.Synthetic.nativeEvent(event)##dataTransfer##files[0]
                     |> dropFile(event)
                   }
                   disabled={state.showProgress}
                   onClick=chooseFile
                   onChange={event =>
                     ReactEvent.Form.target(event)##files[0] |> changeFile
                   }
                 />
               </GridItem>
               <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                 <GridContainer
                   direction="columnReverse"
                   justify="center"
                   alignItem="stretch">
                   {state.photoitems
                    |> Array.mapi((i, photoitem) =>
                         <>
                           <GridItem
                             enterBorderRadius="15"
                             borderRadius="15"
                             enterBackgroundColor={
                               photoitem.photoDelete
                                 ? "rgba(255,0,0,1)" : "rgba(255,255,255,1)"
                             }
                             backgroundColor={
                               photoitem.photoDelete
                                 ? "rgba(255,0,0,0.8)" : "rgba(255,255,255,1)"
                             }
                             xs="auto">
                             <GridContainer
                               backgroundColor="transparent"
                               direction="columnReverse"
                               justify="center"
                               alignItem="stretch">
                               <GridItem
                                 top="0"
                                 right="0"
                                 bottom="0"
                                 left="0"
                                 enterBackgroundColor="transparent"
                                 backgroundColor="transparent"
                                 xs="auto">
                                 {switch (
                                    photoitem.photoImage,
                                    photoitem.photoVideo,
                                    photoitem.photoAudio,
                                  ) {
                                  | (true, _, _) =>
                                    <Image
                                      width="auto"
                                      height="300px"
                                      borderRadius="6"
                                      src={
                                        photoitem.photoPath
                                        ++ photoitem.photoSrc
                                      }
                                    />
                                  | (_, true, _) =>
                                    <Media
                                      width="auto"
                                      borderRadius="6"
                                      controls=true
                                      src={
                                        photoitem.photoPath
                                        ++ photoitem.photoSrc
                                      }
                                    />
                                  | (_, _, true) =>
                                    <Media
                                      variant="audio"
                                      width="auto"
                                      borderRadius="6"
                                      controls=true
                                      src={
                                        photoitem.photoPath
                                        ++ photoitem.photoSrc
                                      }
                                    />
                                  | (_, _, _) => null
                                  }}
                               </GridItem>
                               <GridItem
                                 top="0"
                                 right="0"
                                 bottom="6"
                                 left="0"
                                 enterBackgroundColor="transparent"
                                 backgroundColor="transparent"
                                 xs="auto">
                                 <GridContainer
                                   backgroundColor="transparent"
                                   direction="row"
                                   justify="between"
                                   alignItem="center">
                                   <GridItem
                                     top="0"
                                     right="0"
                                     bottom="0"
                                     left="0"
                                     enterBackgroundColor="transparent"
                                     backgroundColor="transparent"
                                     xs="auto">
                                     <Typography
                                       variant="subheading"
                                       color={
                                         photoitem.photoDelete
                                           ? "rgba(255,255,255,1)"
                                           : "rgba(0,0,0,1)"
                                       }
                                       noWrap=true>
                                       {photoitem.photoOriginal
                                        ++ photoitem.photoExtension
                                        |> string}
                                     </Typography>
                                   </GridItem>
                                   <GridItem
                                     top="0"
                                     right="0"
                                     bottom="0"
                                     left="0"
                                     enterBackgroundColor="transparent"
                                     backgroundColor="transparent"
                                     xs="no">
                                     <IconButton
                                       padding="6"
                                       disabled={state.showProgress}
                                       onClick={_ => i |> actionPhoto}>
                                       <IconAction
                                         animation="leftRight"
                                         src={
                                           photoitem.photoDelete
                                             ? refreshWhite : deleteBlack
                                         }
                                       />
                                     </IconButton>
                                   </GridItem>
                                 </GridContainer>
                               </GridItem>
                             </GridContainer>
                           </GridItem>
                           <GridItem right="24" left="24" xs="auto">
                             <Divider />
                           </GridItem>
                         </>
                       )
                    |> array}
                 </GridContainer>
               </GridItem>
             </>
           }}
        </GridContainer>
      </GridItem>
    </NewFacetube>
    <DialogFull
      showAnimation={state.showFileFull} backgroundColor="rgba(0,0,0,0.8)">
      <DialogTitle top="22" left="64" backgroundColor="transparent">
        <Typography
          variant="tile" color="rgba(255,255,255,1)" fontWeight="600">
          {state.fileTile |> string}
        </Typography>
      </DialogTitle>
      <DialogContent style={ReactDOMRe.Style.make(~overflow="hidden", ())}>
        <DialogContentText>
          <GridItem
            style=marginAuto
            top="0"
            right="0"
            bottom="0"
            left="54"
            xs="12"
            enterBackgroundColor="transparent"
            backgroundColor="transparent"
            maxWidth="770px">
            <iframe
              style={ReactDOMRe.Style.make(
                ~width="100%",
                ~height={string_of_int(state.formHeight) ++ "px"},
                ~borderWidth="0px",
                (),
              )}
              scrolling="auto"
              src={state.filePath ++ state.fileSrc}
            />
          </GridItem>
        </DialogContentText>
      </DialogContent>
      <DialogActions>
        <div
          style={ReactDOMRe.Style.make(
            ~position="fixed",
            ~top="10px",
            ~left="10px",
            (),
          )}>
          <IconButton
            padding="12"
            enterBackgroundColor="transparent"
            downBackgroundColor="transparent"
            disabled={state.showProgress}
            onClick=closeFileFull>
            <IconAction animation="circle" src=clearWhite />
          </IconButton>
        </div>
        <div
          style={ReactDOMRe.Style.make(
            ~position="fixed",
            ~top="64px",
            ~left="10px",
            (),
          )}>
          <IconButton
            padding="12"
            enterBackgroundColor="transparent"
            downBackgroundColor="transparent"
            disabled={state.showProgress}
            onClick=downloadAlbum>
            <IconAction animation="leftRight" src=cloudDownloadWhite />
          </IconButton>
        </div>
      </DialogActions>
    </DialogFull>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
