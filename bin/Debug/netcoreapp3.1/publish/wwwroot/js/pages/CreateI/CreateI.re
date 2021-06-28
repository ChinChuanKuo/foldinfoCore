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

type mbitem = {
  mbId: int,
  mbValue: string,
};

type item = {
  showTypeMenu: bool,
  typeitems: array(optionitem),
  type_: string,
  showGroupMenu: bool,
  groupitems: array(optionitem),
  postGroup: string,
  showNameMenu: bool,
  nameitems: array(optionitem),
  postName: string,
  subject: string,
  showObjMenu: bool,
  objitems: array(optionitem),
  obj: string,
  homepageMomo: string,
  mbitems: array(mbitem),
  showMtstMenu: bool,
  mtstitems: array(optionitem),
  mtst: string,
  showMbstMenu: bool,
  mbstitems: array(optionitem),
  mbst: string,
  pageitems: array(mbitem),
  custom: string,
  showCustom: bool,
  customitems: array(optionitem),
  showDrop: bool,
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
  showPdfDrop: bool,
  showPdfFile: bool,
  showPdfImage: bool,
  showPdfVideo: bool,
  showPdfAudio: bool,
  pdfSrc: string,
  pdfPath: string,
  pdfOriginal: string,
  pdfEncryption: string,
  pdfExtension: string,
  pdfDate: string,
  showTotal: bool,
  first: string,
  final: string,
  body: string,
  releaseDate: string,
  limit: bool,
  endDate: string,
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
  items: array(item),
  showYoutube: bool,
  youtubeText: string,
};

let newmbitem = (mbId, mbValue) => [|{mbId, mbValue}|];

type action =
  | SettingError
  | SettingFormLoad
  | SettingFormWidth(int, int)
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormItems(array(item))
  | ShowTypeMenu(int)
  | ClickTypeMenu(string, int)
  | ShowGroupMenu(int)
  | ClickGroupMenu(string, int)
  | ShowNameMenu(int)
  | SettingItemName(array(optionitem), int)
  | ClickNameMenu(string, int)
  | ChangeSubject(string, int)
  | ShowObjMenu(int)
  | ClickObjMenu(string, int)
  | ChangeMomo(string, int)
  | ClearMbItem(int, int)
  | ShowMtstMenu(int)
  | ClickMtstMenu(string, int)
  | ShowMbstMenu(int)
  | SettingItemModel(array(optionitem), int)
  | AddMbItem(string, int)
  | ClickMbstMenu(string, int)
  | ClearPageItem(int, int)
  | ShowCustom(bool, int)
  | SettingItemCustom(array(optionitem), int)
  | ChangeCustom(string, int)
  | ClickItemCustom(int)
  | AddCustomItem(string, int)
  | ShowDrop(bool, int)
  | ShowFile(
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
  | ShowPdfDrop(bool, int)
  | ShowPdfFile(
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
  | ShowTotal(string, int)
  | ChangeFirst(string, int)
  | ChangeFinal(string, int)
  | RemovePage(string, int)
  | ChangeBody(string, int)
  | ChangeReleaseDate(string, int)
  | SwitchLimit(int)
  | ChangeEndDate(string, int)
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
  | ShowTypeMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showTypeMenu: !item.showTypeMenu} : item,
          state.items,
        ),
    }
  | ClickTypeMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, type_: value, showTypeMenu: !item.showTypeMenu}
              : item,
          state.items,
        ),
    }
  | ShowGroupMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showGroupMenu: !item.showGroupMenu} : item,
          state.items,
        ),
    }
  | ClickGroupMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                postGroup: value,
                showGroupMenu: !item.showGroupMenu,
              }
              : item,
          state.items,
        ),
    }
  | ShowNameMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showNameMenu: !item.showNameMenu} : item,
          state.items,
        ),
    }
  | SettingItemName(items, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, nameitems: items} : item,
          state.items,
        ),
    }
  | ClickNameMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, postName: value, showNameMenu: !item.showNameMenu}
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
  | ChangeMomo(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, homepageMomo: value} : item,
          state.items,
        ),
    }
  | ClearMbItem(mbId, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                mbitems:
                  Js_array.filter(
                    (mbitem: mbitem) => mbitem.mbId !== mbId,
                    item.mbitems,
                  ),
              }
              : item,
          state.items,
        ),
    }
  | ShowMtstMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showMtstMenu: !item.showMtstMenu} : item,
          state.items,
        ),
    }
  | ClickMtstMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, mtst: value, showMtstMenu: !item.showMtstMenu}
              : item,
          state.items,
        ),
    }
  | ShowMbstMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showMbstMenu: !item.showMbstMenu} : item,
          state.items,
        ),
    }
  | SettingItemModel(items, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, mbstitems: items} : item,
          state.items,
        ),
    }
  | AddMbItem(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                mbitems:
                  Array.append(
                    item.mbitems,
                    newmbitem(
                      item.mbitems |> Js_array.length == 0
                        ? 0
                        : item.mbitems[Js_array.length(item.mbitems) - 1].mbId
                          + 1,
                      value,
                    ),
                  ),
              }
              : item,
          state.items,
        ),
    }
  | ClickMbstMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, mbst: value} : item,
          state.items,
        ),
    }
  | ClearPageItem(mbId, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                pageitems:
                  Js_array.filter(
                    (mbitem: mbitem) => mbitem.mbId !== mbId,
                    item.pageitems,
                  ),
              }
              : item,
          state.items,
        ),
    }
  | ShowCustom(showCustom, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showCustom} : item,
          state.items,
        ),
    }
  | SettingItemCustom(items, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, customitems: items, showCustom: true} : item,
          state.items,
        ),
    }
  | ChangeCustom(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, custom: value} : item,
          state.items,
        ),
    }
  | ClickItemCustom(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, custom: "", showCustom: !item.showCustom} : item,
          state.items,
        ),
    }
  | AddCustomItem(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                pageitems:
                  Array.append(
                    item.pageitems,
                    newmbitem(
                      item.pageitems |> Js_array.length == 0
                        ? 0
                        : item.pageitems[Js_array.length(item.pageitems) - 1].
                            mbId
                          + 1,
                      value,
                    ),
                  ),
              }
              : item,
          state.items,
        ),
    }
  | ShowDrop(showDrop, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showDrop} : item,
          state.items,
        ),
    }
  | ShowFile(
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
                showImage,
                showVideo,
                showAudio,
                src,
                path,
                original,
                encryption,
                extension,
                date,
                showFile: true,
              }
              : item,
          state.items,
        ),
    }
  | ShowPdfDrop(showDrop, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showPdfDrop: showDrop} : item,
          state.items,
        ),
    }
  | ShowPdfFile(
      showPdfImage,
      showPdfVideo,
      showPdfAudio,
      pdfSrc,
      pdfPath,
      pdfOriginal,
      pdfEncryption,
      pdfExtension,
      pdfDate,
      index,
    ) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                showPdfImage,
                showPdfVideo,
                showPdfAudio,
                pdfSrc,
                pdfPath,
                pdfOriginal,
                pdfEncryption,
                pdfExtension,
                pdfDate,
                showPdfFile: true,
              }
              : item,
          state.items,
        ),
    }
  | ShowTotal(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, final: value, showTotal: true} : item,
          state.items,
        ),
    }
  | ChangeFirst(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, first: value} : item,
          state.items,
        ),
    }
  | ChangeFinal(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, final: value} : item,
          state.items,
        ),
    }
  | RemovePage(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, first: "1", final: value} : item,
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
  | ChangeReleaseDate(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, releaseDate: value} : item,
          state.items,
        ),
    }
  | SwitchLimit(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, limit: !item.limit} : item,
          state.items,
        ),
    }
  | ChangeEndDate(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, endDate: value} : item,
          state.items,
        ),
    }
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
  items: [||],
  showYoutube: false,
  youtubeText: "",
};

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
      |> Axiosapi.CreateI.search
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

  let insertAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iItemsData(state.items)
      |> Axiosapi.CreateI.insert
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               "saveSuccess" |> Sessions.create("form");
               isoFilePath |> ReasonReactRouter.push;
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
      |> iItemsData(state.items)
      |> Axiosapi.CreateI.send
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               "sendSuccess" |> Sessions.create("form");
               isoFilePath |> ReasonReactRouter.push;
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

  let showTypeMenu = useCallback(i => ShowTypeMenu(i) |> dispatch);

  let clickTypeMenu =
    useCallback((value, i) => ClickTypeMenu(value, i) |> dispatch);

  let showGroupMenu = useCallback(i => ShowGroupMenu(i) |> dispatch);

  let sGroupAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.CreateI.sGroup
      |> then_(response =>
           SettingItemName(response##data##items, i) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickGroupMenu =
    useCallback((value, i) => {
      ClickGroupMenu(value, i) |> dispatch;
      i |> sGroupAJax(value);
    });

  let showNameMenu = useCallback(i => ShowNameMenu(i) |> dispatch);

  let clickNameMenu =
    useCallback((value, i) => ClickNameMenu(value, i) |> dispatch);

  let changeSubject =
    useCallback((value, i) => ChangeSubject(value, i) |> dispatch);

  let showObjMenu = useCallback(i => ShowObjMenu(i) |> dispatch);

  let clickObjMenu =
    useCallback((value, i) => ClickObjMenu(value, i) |> dispatch);

  let changeMomo =
    useCallback((value, i) => ChangeMomo(value, i) |> dispatch);

  let clearMbItem =
    useCallback((mbId, i) => ClearMbItem(mbId, i) |> dispatch);

  let showMtstMenu = useCallback(i => ShowMtstMenu(i) |> dispatch);

  let sModelAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.CreateI.sModel
      |> then_(response =>
           SettingItemModel(response##data##items, i) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickMtstMenu =
    useCallback((value, i) => {
      ClickMtstMenu(value, i) |> dispatch;
      i |> sModelAJax(value);
    });

  let showMbstMenu = useCallback(i => ShowMbstMenu(i) |> dispatch);

  let clickMbstMenu =
    useCallback((value, i) => {
      ClickMbstMenu(value, i) |> dispatch;
      AddMbItem(value, i) |> dispatch;
    });

  let clearPageItem =
    useCallback((mbId, i) => ClearPageItem(mbId, i) |> dispatch);

  let sCustomAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.CreateI.sCustom
      |> then_(response =>
           SettingItemCustom(response##data##items, i) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let changeCustom =
    useCallback((value, i) => {
      ChangeCustom(value, i) |> dispatch;
      i |> sCustomAJax(value);
    });

  let cCustomAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.CreateI.cCustom
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               ClickItemCustom(i) |> dispatch;
               AddCustomItem(value, i) |> dispatch;
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let keydownCustom =
    useCallback((keyCode, value, i) =>
      if (keyCode == 13) {
        i |> cCustomAJax(value);
      }
    );

  let showCustom = useCallback(i => ShowCustom(false, i) |> dispatch);

  let clickItemCustom =
    useCallback((value, i) => {
      ClickItemCustom(i) |> dispatch;
      AddCustomItem(value, i) |> dispatch;
    });

  let dragOverFile =
    useCallback((event, i) => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      ShowDrop(true, i) |> dispatch;
    });

  let dragLeaveFile =
    useCallback((event, i) => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      ShowDrop(false, i) |> dispatch;
    });

  let uploadAJax = (files, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", files) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               ShowFile(
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

  let dropFile =
    useCallback((event, value, i) => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowDrop(false, i) |> dispatch;
      i |> uploadAJax(value);
    });

  let chooseFile =
    useCallback(_ =>
      switch (fileRef |> Ref.current |> Js.Nullable.toOption) {
      | None => ()
      | Some(el) => el->ReactDOMRe.domElementToObj##click() |> ignore
      }
    );

  let changeFile =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> uploadAJax(value);
    });

  let transAJax = (path, original, encryption, extension, i) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> sFileData(path, original, encryption, extension)
      |> Files.transfer
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               ShowPdfFile(
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

  let transForm =
    useCallback((path, original, encryption, extension, i) => {
      ActionShowProgress |> dispatch;
      i |> transAJax(path, original, encryption, extension);
    });

  let dragOverPdfFile =
    useCallback((event, i) => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      ShowPdfDrop(true, i) |> dispatch;
    });

  let dragLeavePdfFile =
    useCallback((event, i) => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      ShowPdfDrop(false, i) |> dispatch;
    });

  let upPdfAJax = (files, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", files) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               ShowPdfFile(
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

  let dropPdfFile =
    useCallback((event, value, i) => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowPdfDrop(false, i) |> dispatch;
      i |> upPdfAJax(value);
    });

  let changePdfFile =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upPdfAJax(value);
    });

  let totalAJax = (path, original, encryption, extension, i) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> sFileData(path, original, encryption, extension)
      |> Files.total
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               ShowTotal(response##data##value, i) |> dispatch;
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

  let totalForm =
    useCallback((path, original, encryption, extension, i) => {
      ActionShowProgress |> dispatch;
      i |> totalAJax(path, original, encryption, extension);
    });

  let changeFirst =
    useCallback((value, i) => ChangeFirst(value, i) |> dispatch);

  let changeFinal =
    useCallback((value, i) => ChangeFinal(value, i) |> dispatch);

  let removeAJax = (path, original, encryption, extension, first, final, i) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> rFileData(path, original, encryption, extension, first, final)
      |> Files.remove
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               RemovePage(response##data##value, i) |> dispatch;
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

  let removeFile =
    useCallback((path, original, encryption, extension, first, final, i) => {
      ActionShowProgress |> dispatch;
      i |> removeAJax(path, original, encryption, extension, first, final);
    });

  let changeBody =
    useCallback((value, i) => ChangeBody(value, i) |> dispatch);

  let changeReleaseDate =
    useCallback((value, i) => ChangeReleaseDate(value, i) |> dispatch);

  let switchLimit = useCallback(i => SwitchLimit(i) |> dispatch);

  let changeEndDate =
    useCallback((value, i) => ChangeEndDate(value, i) |> dispatch);

  <>
    <NewFacetube showProgress={state.showProgress} error={state.error}>
      <GridItem
        style=marginAuto top="0" right="32" left="32" xs="12" maxWidth="770px">
        <GridContainer direction="column" justify="center" alignItem="stretch">
          {state.insert
             ? <GridItem
                 style={ReactDOMRe.Style.make(
                   ~position="sticky",
                   ~top="0px",
                   ~zIndex="1000",
                   (),
                 )}
                 top="0"
                 left="0"
                 xs="auto">
                 <GridContainer
                   direction="rowReverse" justify="between" alignItem="center">
                   <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                     <Button disabled={state.showProgress} onClick=sendForm>
                       <FormattedMessage id="send" defaultMessage="Send" />
                     </Button>
                   </GridItem>
                   <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                     <Button disabled={state.showProgress} onClick=insertForm>
                       <FormattedMessage id="save" defaultMessage="Save" />
                     </Button>
                   </GridItem>
                   <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                     null
                   </GridItem>
                 </GridContainer>
               </GridItem>
             : null}
          {state.items
           |> Array.mapi((i, item) =>
                <>
                  <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                    <GridContainer
                      direction="row" justify="center" alignItem="center">
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        <SelectStandard
                          top="12"
                          right="0"
                          left="0"
                          tile={js|三階文件類型|js}
                          labelColor="rgba(255,0,0,0.8)"
                          enterBorderColor="rgba(255,0,0,0.8)"
                          downBorderColor="rgba(255,0,0,0.6)"
                          borderColor="rgba(0,0,0,0.2)"
                          value={item.type_}
                          disabled={state.showProgress}
                          onClick={_ => i |> showTypeMenu}>
                          ...(
                               item.showTypeMenu
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
                                     {item.typeitems
                                      |> Array.map(typeitem =>
                                           <MenuItem
                                             top="0"
                                             right="8"
                                             bottom="0"
                                             left="8"
                                             disablePadding={
                                                              typeitem.
                                                                optionPadding
                                                            }
                                             topLeft="12"
                                             topRight="12"
                                             bottomRight="12"
                                             bottomLeft="12"
                                             onClick={_ =>
                                               i
                                               |> clickTypeMenu(
                                                    typeitem.value,
                                                  )
                                             }>
                                             {typeitem.value |> string}
                                           </MenuItem>
                                         )
                                      |> array}
                                   </SelectMenu>
                                 : null,
                               <IconGeneral
                                 animation={item.showTypeMenu |> topDownRorate}
                                 src=arrowDownBlack
                               />,
                             )
                        </SelectStandard>
                        <BackgroundBoard
                          showBackground={item.showTypeMenu}
                          backgroundColor="transparent"
                          onClick={_ => i |> showTypeMenu}
                        />
                      </GridItem>
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        null
                      </GridItem>
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        null
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
                          tile={js|撰寫部門|js}
                          labelColor="rgba(255,0,0,0.8)"
                          enterBorderColor="rgba(255,0,0,0.8)"
                          downBorderColor="rgba(255,0,0,0.6)"
                          borderColor="rgba(0,0,0,0.2)"
                          value={item.postGroup}
                          disabled={state.showProgress}
                          onClick={_ => i |> showGroupMenu}>
                          ...(
                               item.showGroupMenu
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
                                     {item.groupitems
                                      |> Array.map(groupitem =>
                                           <MenuItem
                                             top="0"
                                             right="8"
                                             bottom="0"
                                             left="8"
                                             disablePadding={
                                                              groupitem.
                                                                optionPadding
                                                            }
                                             topLeft="12"
                                             topRight="12"
                                             bottomRight="12"
                                             bottomLeft="12"
                                             onClick={_ =>
                                               i
                                               |> clickGroupMenu(
                                                    groupitem.value,
                                                  )
                                             }>
                                             {groupitem.value |> string}
                                           </MenuItem>
                                         )
                                      |> array}
                                   </SelectMenu>
                                 : null,
                               <IconGeneral
                                 animation={
                                   item.showGroupMenu |> topDownRorate
                                 }
                                 src=arrowDownBlack
                               />,
                             )
                        </SelectStandard>
                        <BackgroundBoard
                          showBackground={item.showGroupMenu}
                          backgroundColor="transparent"
                          onClick={_ => i |> showGroupMenu}
                        />
                      </GridItem>
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        <SelectStandard
                          top="12"
                          right="0"
                          left="0"
                          tile={js|撰寫者|js}
                          labelColor="rgba(255,0,0,0.8)"
                          enterBorderColor="rgba(255,0,0,0.8)"
                          downBorderColor="rgba(255,0,0,0.6)"
                          borderColor="rgba(0,0,0,0.2)"
                          value={item.postName}
                          disabled={state.showProgress}
                          onClick={_ => i |> showNameMenu}>
                          ...(
                               item.showNameMenu
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
                                     {item.nameitems
                                      |> Array.map(nameitem =>
                                           <MenuItem
                                             top="0"
                                             right="8"
                                             bottom="0"
                                             left="8"
                                             disablePadding={
                                                              nameitem.
                                                                optionPadding
                                                            }
                                             topLeft="12"
                                             topRight="12"
                                             bottomRight="12"
                                             bottomLeft="12"
                                             onClick={_ =>
                                               i
                                               |> clickNameMenu(
                                                    nameitem.value,
                                                  )
                                             }>
                                             {nameitem.value |> string}
                                           </MenuItem>
                                         )
                                      |> array}
                                   </SelectMenu>
                                 : null,
                               <IconGeneral
                                 animation={item.showNameMenu |> topDownRorate}
                                 src=arrowDownBlack
                               />,
                             )
                        </SelectStandard>
                        <BackgroundBoard
                          showBackground={item.showNameMenu}
                          backgroundColor="transparent"
                          onClick={_ => i |> showNameMenu}
                        />
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
                      {{js|文件名稱|js} |> string}
                    </TextFieldStandard>
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
                          tile={js|製程別|js}
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
                                               |> clickObjMenu(objitem.value)
                                             }>
                                             {objitem.value |> string}
                                           </MenuItem>
                                         )
                                      |> array}
                                   </SelectMenu>
                                 : null,
                               <IconGeneral
                                 animation={item.showObjMenu |> topDownRorate}
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
                            |> changeMomo(
                                 ReactEvent.Form.target(event)##value,
                               )
                          }>
                          {{js|機種|js} |> string}
                        </TextFieldStandard>
                      </GridItem>
                    </GridContainer>
                  </GridItem>
                  <GridItem top="0" right="6" bottom="6" left="6" xs="auto">
                    <GridContainer
                      direction="row" justify="start" alignItem="center">
                      {item.mbitems
                       |> Array.map(mbitem =>
                            <GridItem top="0" bottom="0" left="0" xs="no">
                              <Chip
                                enterBorderWidth="0"
                                downBorderWidth="0"
                                borderWidth="0"
                                showButn=true
                                src=clearBlack
                                onButton={_ => i |> clearMbItem(mbitem.mbId)}>
                                ...(
                                     <Typography variant="subtitle2">
                                       {"S" |> string}
                                     </Typography>,
                                     <Typography variant="subtitle2">
                                       {mbitem.mbValue |> string}
                                     </Typography>,
                                   )
                              </Chip>
                            </GridItem>
                          )
                       |> array}
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
                          tile={js|篩選板類|js}
                          labelColor="rgba(255,0,0,0.8)"
                          enterBorderColor="rgba(255,0,0,0.8)"
                          downBorderColor="rgba(255,0,0,0.6)"
                          borderColor="rgba(0,0,0,0.2)"
                          value={item.mtst}
                          disabled={state.showProgress}
                          onClick={_ => i |> showMtstMenu}>
                          ...(
                               item.showMtstMenu
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
                                     {item.mtstitems
                                      |> Array.map(mtstitem =>
                                           <MenuItem
                                             top="0"
                                             right="8"
                                             bottom="0"
                                             left="8"
                                             disablePadding={
                                                              mtstitem.
                                                                optionPadding
                                                            }
                                             topLeft="12"
                                             topRight="12"
                                             bottomRight="12"
                                             bottomLeft="12"
                                             onClick={_ =>
                                               i
                                               |> clickMtstMenu(
                                                    mtstitem.value,
                                                  )
                                             }>
                                             {mtstitem.value |> string}
                                           </MenuItem>
                                         )
                                      |> array}
                                   </SelectMenu>
                                 : null,
                               <IconGeneral
                                 animation={item.showMtstMenu |> topDownRorate}
                                 src=arrowDownBlack
                               />,
                             )
                        </SelectStandard>
                        <BackgroundBoard
                          showBackground={item.showMtstMenu}
                          backgroundColor="transparent"
                          onClick={_ => i |> showMtstMenu}
                        />
                      </GridItem>
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        <SelectStandard
                          top="12"
                          right="0"
                          left="0"
                          tile={js|板類|js}
                          labelColor="rgba(255,0,0,0.8)"
                          enterBorderColor="rgba(255,0,0,0.8)"
                          downBorderColor="rgba(255,0,0,0.6)"
                          borderColor="rgba(0,0,0,0.2)"
                          value={item.mbst}
                          disabled={state.showProgress}
                          onClick={_ => i |> showMbstMenu}>
                          ...(
                               item.showMbstMenu
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
                                     {item.mbstitems
                                      |> Array.map(mbstitem =>
                                           <MenuItem
                                             top="0"
                                             right="8"
                                             bottom="0"
                                             left="8"
                                             disablePadding={
                                                              mbstitem.
                                                                optionPadding
                                                            }
                                             topLeft="12"
                                             topRight="12"
                                             bottomRight="12"
                                             bottomLeft="12"
                                             onClick={_ =>
                                               i
                                               |> clickMbstMenu(
                                                    mbstitem.value,
                                                  )
                                             }>
                                             {mbstitem.value |> string}
                                           </MenuItem>
                                         )
                                      |> array}
                                   </SelectMenu>
                                 : null,
                               <IconGeneral
                                 animation={item.showMbstMenu |> topDownRorate}
                                 src=arrowDownBlack
                               />,
                             )
                        </SelectStandard>
                        <BackgroundBoard
                          showBackground={item.showMbstMenu}
                          backgroundColor="transparent"
                          onClick={_ => i |> showMbstMenu}
                        />
                      </GridItem>
                    </GridContainer>
                  </GridItem>
                  <GridItem top="0" right="6" bottom="6" left="6" xs="auto">
                    <GridContainer
                      direction="row" justify="start" alignItem="center">
                      {item.pageitems
                       |> Array.map(pageitem =>
                            <GridItem top="0" bottom="0" left="0" xs="no">
                              <Chip
                                enterBorderWidth="0"
                                downBorderWidth="0"
                                borderWidth="0"
                                showButn=true
                                src=clearBlack
                                onButton={_ =>
                                  i |> clearPageItem(pageitem.mbId)
                                }>
                                ...(
                                     <Typography variant="subtitle2">
                                       {"S" |> string}
                                     </Typography>,
                                     <Typography variant="subtitle2">
                                       {pageitem.mbValue |> string}
                                     </Typography>,
                                   )
                              </Chip>
                            </GridItem>
                          )
                       |> array}
                    </GridContainer>
                  </GridItem>
                  <GridItem
                    style={ReactDOMRe.Style.make(~position="relative", ())}
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
                      value={item.custom}
                      disabled={state.showProgress}
                      onChange={event =>
                        i
                        |> changeCustom(ReactEvent.Form.target(event)##value)
                      }
                      onKeyDown={event =>
                        i
                        |> keydownCustom(
                             ReactEvent.Keyboard.keyCode(event),
                             item.custom,
                           )
                      }>
                      {{js|客戶|js} |> string}
                    </TextFieldStandard>
                    {item.showCustom
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
                             {item.customitems
                              |> Array.map(customitems =>
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
                                       i |> clickItemCustom(customitems.value)
                                     }>
                                     <Typography variant="subheading">
                                       {customitems.value |> string}
                                     </Typography>
                                   </MenuItem>
                                 )
                              |> array}
                           </SelectMenu>
                           <BackgroundBoard
                             showBackground=true
                             backgroundColor="transparent"
                             onClick={_ => i |> showCustom}
                           />
                         </>
                       : null}
                  </GridItem>
                  <GridItem right="0" left="0" xs="auto">
                    <GridContainer
                      direction="row" justify="center" alignItem="center">
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        <OtherUpload
                          webLoad={state.showProgress}
                          showDrop={item.showDrop}
                          showFile={item.showFile}
                          showImage={item.showImage}
                          showVideo={item.showVideo}
                          showAudio={item.showAudio}
                          src={item.path ++ item.src}
                          fileRef
                          onDragOver={event => i |> dragOverFile(event)}
                          onDragLeave={event => i |> dragLeaveFile(event)}
                          onDrop={event =>
                            i
                            |> dropFile(
                                 event,
                                 ReactEvent.Synthetic.nativeEvent(event)##dataTransfer##files[0],
                               )
                          }
                          disabled={state.showProgress}
                          onClick=chooseFile
                          onChange={event =>
                            i
                            |> changeFile(
                                 ReactEvent.Form.target(event)##files[0],
                               )
                          }
                        />
                      </GridItem>
                      <GridItem top="0" right="4" bottom="0" left="0" xs="no">
                        <IconButton
                          padding="2"
                          disabled={state.showProgress || !item.showFile}
                          onClick={_ =>
                            i
                            |> transForm(
                                 item.path,
                                 item.original,
                                 item.encryption,
                                 item.extension,
                               )
                          }>
                          <IconAction animation="leftRight" src=cachedBlack />
                        </IconButton>
                      </GridItem>
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        <OtherUpload
                          webLoad={state.showProgress}
                          showDrop={item.showPdfDrop}
                          showFile={item.showPdfFile}
                          showImage={item.showPdfImage}
                          showVideo={item.showPdfVideo}
                          showAudio={item.showPdfAudio}
                          src={item.pdfPath ++ item.pdfSrc}
                          fileRef
                          onDragOver={event => i |> dragOverPdfFile(event)}
                          onDragLeave={event => i |> dragLeavePdfFile(event)}
                          onDrop={event =>
                            i
                            |> dropPdfFile(
                                 event,
                                 ReactEvent.Synthetic.nativeEvent(event)##dataTransfer##files[0],
                               )
                          }
                          disabled={state.showProgress}
                          onClick=chooseFile
                          onChange={event =>
                            i
                            |> changePdfFile(
                                 ReactEvent.Form.target(event)##files[0],
                               )
                          }
                        />
                      </GridItem>
                    </GridContainer>
                  </GridItem>
                  {switch (item.showPdfFile, item.showTotal) {
                   | (true, false) =>
                     <GridItem top="0" bottom="0" xs="auto">
                       <GridContainer
                         direction="rowReverse"
                         justify="center"
                         alignItem="center">
                         <GridItem
                           top="0" right="0" bottom="0" left="0" xs="no">
                           <Button
                             disabled={state.showProgress}
                             onClick={_ =>
                               i
                               |> totalForm(
                                    item.pdfPath,
                                    item.pdfOriginal,
                                    item.pdfEncryption,
                                    item.pdfExtension,
                                  )
                             }>
                             <FormattedMessage
                               id="save"
                               defaultMessage="Save"
                             />
                           </Button>
                         </GridItem>
                         <GridItem
                           top="0" right="0" bottom="0" left="0" xs="auto">
                           null
                         </GridItem>
                       </GridContainer>
                     </GridItem>
                   | (true, true) =>
                     <GridItem top="0" bottom="0" xs="auto">
                       <GridContainer
                         direction="rowReverse"
                         justify="center"
                         alignItem="center">
                         <GridItem
                           top="0" right="0" bottom="0" left="0" xs="auto">
                           <GridContainer
                             direction="row"
                             justify="center"
                             alignItem="center">
                             <GridItem
                               top="0" right="0" bottom="0" left="0" xs="auto">
                               <TextFieldStandard
                                 top="0"
                                 right="0"
                                 bottom="0"
                                 left="0"
                                 labelColor="rgba(255,0,0,0.8)"
                                 enterBorderColor="rgba(255,0,0,0.8)"
                                 downBorderColor="rgba(255,0,0,0.6)"
                                 borderColor="rgba(0,0,0,0.2)"
                                 type_="number"
                                 value={item.first}
                                 disabled={state.showProgress}
                                 onChange={event =>
                                   i
                                   |> changeFirst(
                                        ReactEvent.Form.target(event)##value,
                                      )
                                 }>
                                 {{js|起始頁|js} |> string}
                               </TextFieldStandard>
                             </GridItem>
                             <GridItem
                               top="0" right="0" bottom="0" left="0" xs="auto">
                               <TextFieldStandard
                                 top="0"
                                 right="0"
                                 bottom="0"
                                 left="0"
                                 labelColor="rgba(255,0,0,0.8)"
                                 enterBorderColor="rgba(255,0,0,0.8)"
                                 downBorderColor="rgba(255,0,0,0.6)"
                                 borderColor="rgba(0,0,0,0.2)"
                                 type_="number"
                                 value={item.final}
                                 disabled={state.showProgress}
                                 onChange={event =>
                                   i
                                   |> changeFinal(
                                        ReactEvent.Form.target(event)##value,
                                      )
                                 }>
                                 {{js|最終頁|js} |> string}
                               </TextFieldStandard>
                             </GridItem>
                             <GridItem
                               top="0" right="0" bottom="0" left="0" xs="no">
                               <Button
                                 disabled={state.showProgress}
                                 onClick={_ =>
                                   i
                                   |> removeFile(
                                        item.pdfPath,
                                        item.pdfOriginal,
                                        item.pdfEncryption,
                                        item.pdfExtension,
                                        item.first,
                                        item.final,
                                      )
                                 }>
                                 <FormattedMessage
                                   id="save"
                                   defaultMessage="Save"
                                 />
                               </Button>
                             </GridItem>
                           </GridContainer>
                         </GridItem>
                         <GridItem
                           top="0"
                           right="0"
                           bottom="0"
                           left="0"
                           width="34px"
                           xs="no">
                           null
                         </GridItem>
                         <GridItem
                           top="0" right="0" bottom="0" left="0" xs="auto">
                           null
                         </GridItem>
                       </GridContainer>
                     </GridItem>
                   | (false, _) => null
                   }}
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
                      value={item.body}
                      disabled={state.showProgress}
                      onChange={event =>
                        i |> changeBody(ReactEvent.Form.target(event)##value)
                      }>
                      {{js|說明|js} |> string}
                    </TextFieldMultiline>
                  </GridItem>
                  <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                    <GridContainer
                      direction="rowReverse"
                      justify="center"
                      alignItem="center">
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        <Switch
                          right="0"
                          checked={item.limit}
                          circleColor={item.limit |> circle}
                          linearColor={item.limit |> linear}
                          fontColor={item.limit |> font}
                          disabled={state.showProgress}
                          onClick={_ => i |> switchLimit}>
                          {{js|限期|js} |> string}
                        </Switch>
                      </GridItem>
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        <Switch
                          right="0"
                          checked={!item.limit}
                          circleColor={!item.limit |> circle}
                          linearColor={!item.limit |> linear}
                          fontColor={!item.limit |> font}
                          disabled={state.showProgress}
                          onClick={_ => i |> switchLimit}>
                          {{js|無限期|js} |> string}
                        </Switch>
                      </GridItem>
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        null
                      </GridItem>
                      <GridItem
                        top="0" right="0" bottom="0" left="0" xs="auto">
                        null
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
                          type_="date"
                          value={item.releaseDate}
                          disabled={state.showProgress}
                          onChange={event =>
                            i
                            |> changeReleaseDate(
                                 ReactEvent.Form.target(event)##value,
                               )
                          }>
                          {{js|發行日期|js} |> string}
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
                          type_="date"
                          value={item.endDate}
                          disabled={state.showProgress || !item.limit}
                          onChange={event =>
                            i
                            |> changeEndDate(
                                 ReactEvent.Form.target(event)##value,
                               )
                          }>
                          {{js|到期日|js} |> string}
                        </TextFieldStandard>
                      </GridItem>
                    </GridContainer>
                  </GridItem>
                </>
              )
           |> array}
        </GridContainer>
      </GridItem>
    </NewFacetube>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
