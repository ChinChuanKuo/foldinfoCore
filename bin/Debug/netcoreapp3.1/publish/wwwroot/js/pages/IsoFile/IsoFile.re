open React;
open Together;
open OutSide;
open ReactIntl;
open Data;
open Icons;
open Items;
open Axiosapi;
open Status;
open Storage;
open SwitchColor;
open IconAnimation;
open ObjectFormat;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type listitem = {
  id: string,
  content: string,
  inoper: string,
};

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
  showDelete: bool,
  photoDelete: bool,
};

type mbitem = {
  mbId: int,
  mbValue: string,
};

type formitem = {
  postdate: string,
  postinfo: string,
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
  formInsert: bool,
  formDelete: bool,
  formEdit: bool,
  formSend: bool,
  formModify: bool,
};

type item = {
  ids: string,
  numbers: string,
  subjects: string,
  postGroups: string,
  objs: string,
  issuedates: string,
  releasedates: string,
  homepageMomos: string,
  mbs: string,
  homepage1s: string,
  bodys: string,
  itemDelete: bool,
};

type filitem = {
  index: int,
  tile: string,
  filtValue: string,
  showMenu: bool,
  optionitems: array(optionitem),
};

type recorditem = {
  cordIcon: string,
  cordValue: string,
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
  record: string,
  showRecord: bool,
  recorditems: array(recorditem),
  filitems: array(filitem),
  showItem: bool,
  itemCount: int,
  items: array(item),
  showFull: bool,
  formIndex: int,
  formId: string,
  formTitle: string,
  tabitems: list(tabitem),
  index: int,
  formitems: array(formitem),
  listitems: array(listitem),
  showYoutube: bool,
  youtubeText: string,
};

let newmbitem = (mbId, mbValue) => [|{mbId, mbValue}|];

let newitem =
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
    showDelete: true,
    photoDelete: false,
  },
|];

type action =
  | SettingError
  | SettingFormLoad
  | SettingFormWidth(int, int)
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFilItems(array(filitem))
  | SettingFormItems(bool, int, array(item))
  | SettingScrollItems(bool, array(item))
  | ShowAnimationFull(int, string, string, array(formitem))
  | SettingAnimationFull(int, string, string, array(formitem))
  | ShowRecord(bool)
  | ClickRecordItems(array(recorditem))
  | ChangeRecord(string)
  | ClickItemRecord(string)
  | ClearFilterItems
  | ShowMenu(int)
  | ClickMenu(string, int)
  | ClearItem(string)
  | ClickItemTab(int)
  | SettingListItems(array(listitem))
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
  | ShowAnimationItems(string, string, array(formitem))
  | CloseAnimationFull
  | SendAnimationFull(int)
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
  | SettingFilItems(filitems) => {...state, filitems}
  | SettingFormItems(showItem, itemCount, items) => {
      ...state,
      showItem,
      itemCount,
      items,
    }
  | SettingScrollItems(showItem, items) => {
      ...state,
      showItem,
      items: Array.append(state.items, items),
    }
  | ShowAnimationFull(index, id, value, formitems) => {
      ...state,
      index: 0,
      formIndex: index,
      formId: id,
      formTitle: value,
      formitems,
      showFull: !state.showFull,
    }
  | SettingAnimationFull(index, id, value, formitems) => {
      ...state,
      index: 0,
      formIndex: index,
      formId: id,
      formTitle: value,
      formitems,
    }
  | ShowRecord(showRecord) => {...state, showRecord}
  | ClickRecordItems(items) => {...state, recorditems: items}
  | ChangeRecord(value) => {...state, record: value}
  | ClickItemRecord(value) => {
      ...state,
      record: value,
      showRecord: !state.showRecord,
    }
  | ClearFilterItems => {
      ...state,
      filitems:
        Array.map(filitem => {...filitem, filtValue: ""}, state.filitems),
    }
  | ShowMenu(index) => {
      ...state,
      filitems:
        Array.mapi(
          (i, filitem) =>
            index == i ? {...filitem, showMenu: !filitem.showMenu} : filitem,
          state.filitems,
        ),
    }
  | ClickMenu(value, index) => {
      ...state,
      filitems:
        Array.mapi(
          (i, filitem) =>
            index == i
              ? {...filitem, filtValue: value, showMenu: !filitem.showMenu}
              : filitem,
          state.filitems,
        ),
    }
  | ClearItem(id) => {
      ...state,
      itemCount: state.itemCount - 1,
      items: Js_array.filter((item: item) => item.ids !== id, state.items),
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
  | SettingListItems(items) => {...state, listitems: items}
  | ChangeSubject(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, subject: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ShowObjMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showObjMenu: !item.showObjMenu} : item,
          state.formitems,
        ),
    }
  | ClickObjMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                obj: value,
                showObjMenu: !item.showObjMenu,
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ChangeMomo(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, homepageMomo: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ClearMbItem(mbId, index) => {
      ...state,
      formitems:
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
          state.formitems,
        ),
    }
  | ShowMtstMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showMtstMenu: !item.showMtstMenu} : item,
          state.formitems,
        ),
    }
  | ClickMtstMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                mtst: value,
                showMtstMenu: !item.showMtstMenu,
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ShowMbstMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showMbstMenu: !item.showMbstMenu} : item,
          state.formitems,
        ),
    }
  | SettingItemModel(items, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, mbstitems: items} : item,
          state.formitems,
        ),
    }
  | AddMbItem(value, index) => {
      ...state,
      formitems:
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
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ClickMbstMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                mbst: value,
                showMbstMenu: !item.showMbstMenu,
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ClearPageItem(mbId, index) => {
      ...state,
      formitems:
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
          state.formitems,
        ),
    }
  | ShowCustom(showCustom, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, showCustom} : item,
          state.formitems,
        ),
    }
  | SettingItemCustom(items, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, customitems: items, showCustom: true} : item,
          state.formitems,
        ),
    }
  | ChangeCustom(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, custom: value} : item,
          state.formitems,
        ),
    }
  | ClickItemCustom(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                custom: "",
                showCustom: !item.showCustom,
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | AddCustomItem(value, index) => {
      ...state,
      formitems:
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
          state.formitems,
        ),
    }
  | ShowDrop(showDrop, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, showDrop} : item,
          state.formitems,
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
      formitems:
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
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ShowPdfDrop(showDrop, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, showPdfDrop: showDrop} : item,
          state.formitems,
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
      formitems:
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
                 formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ShowTotal(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, final: value, showTotal: true} : item,
          state.formitems,
        ),
    }
  | ChangeFirst(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, first: value} : item,
          state.formitems,
        ),
    }
  | ChangeFinal(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, final: value} : item,
          state.formitems,
        ),
    }
  | RemovePage(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, first: "1", final: value} : item,
          state.formitems,
        ),
    }
  | ChangeBody(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, body: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeReleaseDate(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, releaseDate: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | SwitchLimit(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, limit: !item.limit} : item,
          state.formitems,
        ),
    }
  | ChangeEndDate(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, endDate: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ShowAnimationItems(id, value, formitems) => {
      ...state,
      index: 0,
      formId: id,
      formTitle: value,
      formitems,
    }
  | CloseAnimationFull => {...state, showFull: !state.showFull}
  | SendAnimationFull(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, itemDelete: false} : item,
          state.items,
        ),
      showFull: !state.showFull,
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
  record: "",
  showRecord: false,
  recorditems: [||],
  filitems: [||],
  showItem: false,
  itemCount: 0,
  items: [||],
  showFull: false,
  formIndex: 0,
  formId: "",
  formTitle: "",
  tabitems: [
    {showTab: true, tabImage: descriptionBlack},
    {showTab: false, tabImage: listBlack},
  ],
  index: 0,
  formitems: [||],
  listitems: [||],
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
      state.items
      |> Js_array.length
      |> string_of_int
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.IsoFile.search
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               SettingFormItems(
                 response##data##showItem,
                 response##data##itemCount,
                 response##data##items,
               )
               |> dispatch;
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

  let filterAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Axiosapi.IsoFile.filter
      |> then_(response =>
           {
             SettingFilItems(response##data##items) |> dispatch;
             searchAJax();
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
             filterAJax();
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
      let testId =
        switch ("form" |> Sessions.select |> checkObjects) {
        | "saveSuccess"
        | "sendSuccess"
        | "deleteSuccess" =>
          "form"
          |> Sessions.select
          |> checkObjects
          |> statusModule
          |> barShowRestoreAction;
          "" |> Sessions.create("form");
        | _ => "action" |> Js.log
        };
      let timeId = permissAJax();
      Some(
        () => {
          testtime;
          sizeId;
          testId;
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

  let scrollAJax = length =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> sScroData(
           Js_array.filter(
             (filitem: filitem) => filitem.filtValue !== "",
             state.filitems,
           ),
           state.record,
           length,
         )
      |> Axiosapi.IsoFile.scroll
      |> then_(response =>
           {
             SettingScrollItems(
               response##data##showItem,
               response##data##items,
             )
             |> dispatch;
             ActionShowProgress |> dispatch;
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickScrollBar =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      state.items |> Js_array.length |> scrollAJax;
    });

  let sRecordAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Axiosapi.IsoFile.sRecord
      |> then_(response =>
           ClickRecordItems(response##data##items) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickRecord =
    useCallback(_ => {
      ShowRecord(true) |> dispatch;
      sRecordAJax();
    });

  let showRecord = useCallback(_ => ShowRecord(false) |> dispatch);

  let changeRecord = useCallback(value => ChangeRecord(value) |> dispatch);

  let sFiltCordAJax = record =>
    Js.Promise.(
      record
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.IsoFile.sFiltCord
      |> then_(response =>
           {
             ClearFilterItems |> dispatch;
             switch (response##data##status) {
             | "istrue" =>
               SettingFormItems(
                 response##data##showItem,
                 response##data##itemCount,
                 response##data##items,
               )
               |> dispatch
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let keydownRecord =
    useCallback(keyCode =>
      if (keyCode == 13) {
        ShowRecord(false) |> dispatch;
        state.record |> sFiltCordAJax;
      }
    );

  let clickItemRecord =
    useCallback(value => {
      ClickItemRecord(value) |> dispatch;
      value |> sFiltCordAJax;
    });

  let showMenu = useCallback(index => ShowMenu(index) |> dispatch);

  let sfilterAJax = (index, value) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> sFiltData(
           Js_array.filter(
             (filitem: filitem) => filitem.filtValue !== "",
             state.filitems,
           ),
           index,
           value,
           state.record,
         )
      |> Axiosapi.IsoFile.sFilter
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               SettingFormItems(
                 response##data##showItem,
                 response##data##itemCount,
                 response##data##items,
               )
               |> dispatch
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

  let clickMenu =
    useCallback((value, index) => {
      ClickMenu(value, index) |> dispatch;
      value |> sfilterAJax(index);
    });

  let sItemAJax = (index, id) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(id)
      |> Axiosapi.IsoFile.sItem
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowAnimationFull(
                 index,
                 response##data##formId,
                 response##data##tile,
                 response##data##items,
               )
               |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickFormBoard =
    useCallback((i, id) => {
      ActionShowProgress |> dispatch;
      id |> sItemAJax(i);
    });

  let clearAJax = id =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(id)
      |> Axiosapi.IsoFile.clear
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ClearItem(id) |> dispatch;
               "deleteSuccess" |> statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clearItem =
    useCallback(id => {
      ActionShowProgress |> dispatch;
      id |> clearAJax;
    });

  let sListAJax = () =>
    Js.Promise.(
      state.formId
      |> dFormData("newid" |> Locals.select)
      |> Axiosapi.IsoFile.sList
      |> then_(response =>
           {
             SettingListItems(response##data##items) |> dispatch;
             ActionShowProgress |> dispatch;
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickItemTab =
    useCallback(i => {
      ClickItemTab(i) |> dispatch;
      if (i == 1) {
        ActionShowProgress |> dispatch;
        sListAJax();
      };
    });

  let deleteAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Axiosapi.IsoFile.delete
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               ClearItem(state.formId) |> dispatch;
               CloseAnimationFull |> dispatch;
               "saveSuccess" |> statusModule |> barShowRestoreAction;
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

  let deleteForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      deleteAJax();
    });

  let orderAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iFormData(state.formId, state.formTitle, state.formitems)
      |> Axiosapi.IsoFile.order
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               CloseAnimationFull |> dispatch;
               "saveSuccess" |> statusModule |> barShowRestoreAction;
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

  let orderForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      orderAJax();
    });

  let insertAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iFormData(
           state.formId,
           state.formTitle,
           Js_array.filter(
             (formitem: formitem) => formitem.formModify === true,
             state.formitems,
           ),
         )
      |> Axiosapi.IsoFile.insert
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               CloseAnimationFull |> dispatch;
               "saveSuccess" |> statusModule |> barShowRestoreAction;
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

  let previousAJax = (index, id) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(id)
      |> Axiosapi.IsoFile.previous
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               SettingAnimationFull(
                 index,
                 response##data##formId,
                 response##data##tile,
                 response##data##items,
               )
               |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let previousForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      state.formId |> previousAJax(state.formIndex);
    });

  let nextAJax = (index, id) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(id)
      |> Axiosapi.IsoFile.next
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               SettingAnimationFull(
                 index,
                 response##data##formId,
                 response##data##tile,
                 response##data##items,
               )
               |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let nextForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      state.formId |> nextAJax(state.formIndex);
    });

  let insertForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      insertAJax();
    });

  let sendAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iFormData(
           state.formId,
           state.formTitle,
           Js_array.filter(
             (formitem: formitem) => formitem.formModify === true,
             state.formitems,
           ),
         )
      |> Axiosapi.IsoFile.send
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               SendAnimationFull(state.formIndex) |> dispatch;
               "sendSuccess" |> statusModule |> barShowRestoreAction;
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

  let sendForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      sendAJax();
    });

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
      |> CreateF.sModel
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
      |> CreateI.sCustom
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
      |> CreateI.cCustom
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

  let clickFile =
    useCallback((path, original, encryption, extension) =>
      path
      ++ original
      ++ "("
      ++ encryption
      ++ ")"
      ++ extension
      |> Window.Locations.assign
    );

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

  let closeAnimationFull = useCallback(_ => CloseAnimationFull |> dispatch);

  <>
    <NewFacetube showProgress={state.showProgress} error={state.error}>
      <GridItem
        style=marginAuto
        top="0"
        right="32"
        bottom="0"
        left="32"
        xs="12"
        maxWidth="770px">
        <GridContainer direction="column" justify="center" alignItem="stretch">
          <GridItem
            style={ReactDOMRe.Style.make(
              ~position="sticky",
              ~top="0px",
              ~zIndex="2",
              (),
            )}
            top="6"
            bottom="6"
            left="6"
            xs="auto">
            <GridContainer direction="row" justify="center" alignItem="center">
              <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                <TextFieldOutline
                  top="0"
                  right="0"
                  left="0"
                  bottom="0"
                  borderTop="12"
                  borderBottom="12"
                  borderRadius="20"
                  value={state.record}
                  disabled={state.showProgress}
                  onChange={event =>
                    ReactEvent.Form.target(event)##value |> changeRecord
                  }
                  onKeyDown={event =>
                    ReactEvent.Keyboard.keyCode(event) |> keydownRecord
                  }
                  onClick=clickRecord>
                  null
                </TextFieldOutline>
                {state.showRecord
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
                         {state.recorditems
                          |> Array.map(recorditem =>
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
                                   recorditem.cordValue |> clickItemRecord
                                 }>
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
                                     xs="no">
                                     <IconButton
                                       enterBackgroundColor="transparent"
                                       downBackgroundColor="transparent"
                                       padding="4">
                                       <IconAction
                                         animation="circle"
                                         src={recorditem.cordIcon}
                                       />
                                     </IconButton>
                                   </GridItem>
                                   <GridItem
                                     top="0"
                                     right="6"
                                     bottom="0"
                                     left="6"
                                     enterBackgroundColor="transparent"
                                     backgroundColor="transparent"
                                     xs="auto">
                                     <Typography variant="subheading">
                                       {recorditem.cordValue |> string}
                                     </Typography>
                                   </GridItem>
                                 </GridContainer>
                               </MenuItem>
                             )
                          |> array}
                       </SelectMenu>
                       <BackgroundBoard
                         showBackground=true
                         backgroundColor="transparent"
                         onClick=showRecord
                       />
                     </>
                   : null}
              </GridItem>
              <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                <Typography variant="subheading" fontWeight="600">
                  {{js|總筆數：|js}
                   ++ string_of_int(state.itemCount)
                   |> string}
                </Typography>
              </GridItem>
            </GridContainer>
          </GridItem>
          <GridItem
            style={ReactDOMRe.Style.make(
              ~position="sticky",
              ~top="61px",
              ~zIndex="1",
              (),
            )}
            top="0"
            right="0"
            bottom="0"
            left="0"
            xs="auto">
            <GridContainer direction="row" justify="center" alignItem="center">
              {state.filitems
               |> Array.mapi((i, filitem) =>
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <SelectOutline
                        labelColor="rgba(255,0,0,0.8)"
                        tile={filitem.tile}
                        enterBorderColor="rgba(255,0,0,0.8)"
                        downBorderColor="rgba(255,0,0,0.6)"
                        borderColor="rgba(0,0,0,0.2)"
                        value={filitem.filtValue}
                        disabled={state.showProgress}
                        onClick={_ => i |> showMenu}>
                        ...(
                             filitem.showMenu
                               ? <SelectMenu
                                   top="0%"
                                   transform="translate(0, 0%)"
                                   maxHeight="280"
                                   minHeight="0"
                                   topLeft="12"
                                   topRight="12"
                                   bottomRight="12"
                                   bottomLeft="12"
                                   paddingRight="8"
                                   paddingLeft="8">
                                   {filitem.optionitems
                                    |> Array.map(optionitem =>
                                         <MenuItem
                                           top="0"
                                           right="8"
                                           bottom="0"
                                           left="8"
                                           disablePadding={
                                                            optionitem.
                                                              optionPadding
                                                          }
                                           topLeft="12"
                                           topRight="12"
                                           bottomRight="12"
                                           bottomLeft="12"
                                           onClick={_ =>
                                             i |> clickMenu(optionitem.value)
                                           }>
                                           {optionitem.value |> string}
                                         </MenuItem>
                                       )
                                    |> array}
                                 </SelectMenu>
                               : null,
                             <IconGeneral
                               animation={filitem.showMenu |> topDownRorate}
                               src=arrowDownBlack
                             />,
                           )
                      </SelectOutline>
                      <BackgroundBoard
                        showBackground={filitem.showMenu}
                        backgroundColor="transparent"
                        onClick={_ => i |> showMenu}
                      />
                    </GridItem>
                  )
               |> array}
            </GridContainer>
          </GridItem>
          {state.items
           |> Array.mapi((i, item) =>
                <>
                  <GridItem
                    top="0"
                    right="0"
                    bottom="0"
                    left="0"
                    cursor="pointer"
                    enterBorderRadius="10"
                    borderRadius="10"
                    enterBackgroundColor="rgba(0,0,0,0.1)"
                    xs="auto"
                    onClick={_ => item.ids |> clickFormBoard(i)}>
                    <GridContainer
                      backgroundColor="none"
                      direction="column"
                      justify="center"
                      alignItem="stretch">
                      <GridItem
                        top="6"
                        bottom="0"
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <GridContainer
                          backgroundColor="none"
                          direction="row"
                          justify="between"
                          alignItem="center">
                          <GridItem
                            top="0"
                            right="0"
                            bottom="0"
                            left="0"
                            enterBackgroundColor="none"
                            backgroundColor="none"
                            xs="auto">
                            <Typography variant="subheading" fontWeight="600">
                              {item.numbers |> string}
                            </Typography>
                          </GridItem>
                          {item.itemDelete
                             ? <GridItem
                                 top="0"
                                 right="0"
                                 bottom="0"
                                 left="0"
                                 enterBackgroundColor="none"
                                 backgroundColor="none"
                                 xs="no">
                                 <IconButton
                                   padding="8"
                                   disabled={state.showProgress}
                                   onClick={_ => item.ids |> clearItem}>
                                   <Tooltip
                                     location="bottom"
                                     backgroundColor="rgba(255,0,0,0.8)">
                                     <FormattedMessage
                                       id="deleted"
                                       defaultMessage="Deleted"
                                     />
                                   </Tooltip>
                                   <IconAction
                                     animation="circle"
                                     src=deleteBlack
                                   />
                                 </IconButton>
                               </GridItem>
                             : null}
                        </GridContainer>
                      </GridItem>
                      <GridItem
                        top="0"
                        left="14"
                        bottom="0"
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <Typography variant="body2">
                          {item.subjects |> string}
                        </Typography>
                      </GridItem>
                      <GridItem
                        top="0"
                        bottom="0"
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <GridContainer
                          backgroundColor="none"
                          direction="row"
                          justify="center"
                          alignItem="center">
                          <GridItem
                            top="0"
                            bottom="0"
                            left="0"
                            enterBackgroundColor="none"
                            backgroundColor="none"
                            xs="no">
                            <Typography variant="body2" color="#606060">
                              {item.issuedates |> string}
                            </Typography>
                          </GridItem>
                          <GridItem
                            top="0"
                            bottom="0"
                            left="0"
                            enterBackgroundColor="none"
                            backgroundColor="none"
                            xs="auto">
                            <Typography variant="body2" color="#606060">
                              {item.postGroups |> string}
                            </Typography>
                          </GridItem>
                        </GridContainer>
                      </GridItem>
                      <GridItem
                        top="0"
                        bottom="0"
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <GridContainer
                          backgroundColor="none"
                          direction="row"
                          justify="center"
                          alignItem="center">
                          <GridItem
                            top="0"
                            bottom="0"
                            left="0"
                            enterBackgroundColor="none"
                            backgroundColor="none"
                            xs="no">
                            <Typography variant="body2" color="#606060">
                              {item.releasedates |> string}
                            </Typography>
                          </GridItem>
                          <GridItem
                            top="0"
                            bottom="0"
                            left="0"
                            enterBackgroundColor="none"
                            backgroundColor="none"
                            xs="auto">
                            <Typography variant="body2" color="#606060">
                              {item.objs |> string}
                            </Typography>
                          </GridItem>
                        </GridContainer>
                      </GridItem>
                      <GridItem
                        top="0"
                        bottom="0"
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <Typography
                          variant="subheading"
                          color="#606060"
                          whiteSpace="inherit">
                          {item.homepageMomos |> string}
                        </Typography>
                      </GridItem>
                      <GridItem
                        top="0"
                        bottom="0"
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <Typography
                          variant="subheading"
                          color="#606060"
                          whiteSpace="inherit">
                          {item.mbs |> string}
                        </Typography>
                      </GridItem>
                      <GridItem
                        top="0"
                        bottom="0"
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <Typography
                          variant="subheading"
                          color="#606060"
                          whiteSpace="inherit">
                          {item.homepage1s |> string}
                        </Typography>
                      </GridItem>
                      <GridItem
                        top="0"
                        bottom="0"
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <Typography
                          variant="subheading"
                          color="#606060"
                          whiteSpace="inherit">
                          {item.bodys |> string}
                        </Typography>
                      </GridItem>
                    </GridContainer>
                  </GridItem>
                  <GridItem top="6" right="0" bottom="6" left="0" xs="auto">
                    <Divider />
                  </GridItem>
                </>
              )
           |> array}
        </GridContainer>
        <BottomScroll
          showBar={state.showItem}
          disabled={state.showProgress}
          onClick=clickScrollBar
        />
      </GridItem>
    </NewFacetube>
    <DialogFull showAnimation={state.showFull}>
      <DialogTitle top="22" left="64">
        <Typography variant="tile" fontWeight="600">
          {state.formTitle |> string}
        </Typography>
      </DialogTitle>
      <DialogContent>
        <DialogContentText>
          <GridItem
            style=marginAuto
            top="0"
            right="0"
            bottom="0"
            left="54"
            xs="12"
            maxWidth="770px">
            <GridContainer
              direction="column" justify="center" alignItem="stretch">
              <GridItem
                style={ReactDOMRe.Style.make(
                  ~position="sticky",
                  ~top="0px",
                  ~zIndex="1000",
                  (),
                )}
                top="0"
                bottom="6"
                left="0"
                xs="auto">
                <GridContainer
                  direction="row" justify="around" alignItem="center">
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
                  <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                    <Button disabled={state.showProgress} onClick=previousForm>
                      <FormattedMessage
                        id="Action.previous"
                        defaultMessage="Previous"
                      />
                    </Button>
                  </GridItem>
                  {state.formitems
                   |> Array.map(item =>
                        item.formInsert && state.insert
                          ? <GridItem
                              top="0" right="0" bottom="0" left="0" xs="no">
                              <Button
                                disabled={state.showProgress}
                                onClick=orderForm>
                                <FormattedMessage
                                  id="IsoFile.order"
                                  defaultMessage="Order"
                                />
                              </Button>
                            </GridItem>
                          : null
                      )
                   |> array}
                  {state.formitems
                   |> Array.map(item =>
                        item.formEdit && state.update
                          ? <GridItem
                              top="0" right="0" bottom="0" left="0" xs="no">
                              <Button
                                disabled={state.showProgress}
                                onClick=insertForm>
                                <FormattedMessage
                                  id="save"
                                  defaultMessage="Save"
                                />
                              </Button>
                            </GridItem>
                          : null
                      )
                   |> array}
                  {state.formitems
                   |> Array.map(item =>
                        item.formSend
                          ? <GridItem
                              top="0" right="0" bottom="0" left="0" xs="no">
                              <Button
                                disabled={state.showProgress} onClick=sendForm>
                                <FormattedMessage
                                  id="send"
                                  defaultMessage="Send"
                                />
                              </Button>
                            </GridItem>
                          : null
                      )
                   |> array}
                  {state.formitems
                   |> Array.map(item =>
                        item.formDelete && state.delete
                          ? <GridItem
                              top="0" right="0" bottom="0" left="0" xs="no">
                              <Button
                                disabled={state.showProgress}
                                onClick=deleteForm>
                                <FormattedMessage
                                  id="deleted"
                                  defaultMessage="Deleted"
                                />
                              </Button>
                            </GridItem>
                          : null
                      )
                   |> array}
                  <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                    <Button disabled={state.showProgress} onClick=nextForm>
                      <FormattedMessage
                        id="Action.next"
                        defaultMessage="Next"
                      />
                    </Button>
                  </GridItem>
                </GridContainer>
              </GridItem>
              {switch (state.index) {
               | 0 =>
                 state.formitems
                 |> Array.mapi((i, item) =>
                      <>
                        <GridItem
                          style={ReactDOMRe.Style.make(~height="50px", ())}
                          top="0"
                          right="6"
                          bottom="0"
                          left="6"
                          xs="auto">
                          <GridContainer
                            direction="row"
                            justify="center"
                            alignItem="center">
                            <GridItem
                              top="25" right="0" bottom="0" left="0" xs="auto">
                              <Typography
                                variant="subheading" fontWeight="bolder">
                                {item.postdate |> string}
                              </Typography>
                            </GridItem>
                            <GridItem
                              top="25" right="0" bottom="0" left="0" xs="auto">
                              <Typography
                                variant="subheading" fontWeight="bolder">
                                {item.postinfo |> string}
                              </Typography>
                            </GridItem>
                          </GridContainer>
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
                            value={item.subject}
                            disabled={state.showProgress || !item.formEdit}
                            onChange={event =>
                              i
                              |> changeSubject(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|文件名稱|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <GridContainer
                            direction="row"
                            justify="center"
                            alignItem="center">
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
                                disabled={state.showProgress || !item.formEdit}
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
                                disabled={state.showProgress || !item.formEdit}
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
                        <GridItem
                          top="0" right="6" bottom="6" left="6" xs="auto">
                          <GridContainer
                            direction="row" justify="start" alignItem="center">
                            {item.mbitems
                             |> Array.map(mbitem =>
                                  <GridItem
                                    top="0" bottom="0" left="0" xs="no">
                                    <Chip
                                      enterBorderWidth="0"
                                      downBorderWidth="0"
                                      borderWidth="0"
                                      showButn=true
                                      src=clearBlack
                                      onButton={_ =>
                                        i |> clearMbItem(mbitem.mbId)
                                      }>
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
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <GridContainer
                            direction="row"
                            justify="center"
                            alignItem="center">
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
                                disabled={state.showProgress || !item.formEdit}
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
                                       animation={
                                         item.showMtstMenu |> topDownRorate
                                       }
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
                                disabled={state.showProgress || !item.formEdit}
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
                                       animation={
                                         item.showMbstMenu |> topDownRorate
                                       }
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
                        <GridItem
                          top="0" right="6" bottom="6" left="6" xs="auto">
                          <GridContainer
                            direction="row" justify="start" alignItem="center">
                            {item.pageitems
                             |> Array.map(pageitem =>
                                  <GridItem
                                    top="0" bottom="0" left="0" xs="no">
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
                            value={item.custom}
                            disabled={state.showProgress || !item.formEdit}
                            onChange={event =>
                              i
                              |> changeCustom(
                                   ReactEvent.Form.target(event)##value,
                                 )
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
                                             i
                                             |> clickItemCustom(
                                                  customitems.value,
                                                )
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
                            direction="row"
                            justify="center"
                            alignItem="center">
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
                                onDragLeave={event =>
                                  i |> dragLeaveFile(event)
                                }
                                onDrop={event =>
                                  i
                                  |> dropFile(
                                       event,
                                       ReactEvent.Synthetic.nativeEvent(event)##dataTransfer##files[0],
                                     )
                                }
                                disabled={state.showProgress || !item.formEdit}
                                onClick=chooseFile
                                onDownload={_ =>
                                  clickFile(
                                    item.path,
                                    item.original,
                                    item.encryption,
                                    item.extension,
                                  )
                                }
                                onChange={event =>
                                  i
                                  |> changeFile(
                                       ReactEvent.Form.target(event)##files[0],
                                     )
                                }
                              />
                            </GridItem>
                            <GridItem
                              top="0" right="4" bottom="0" left="0" xs="no">
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
                                <IconAction
                                  animation="leftRight"
                                  src=cachedBlack
                                />
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
                                onDragOver={event =>
                                  i |> dragOverPdfFile(event)
                                }
                                onDragLeave={event =>
                                  i |> dragLeavePdfFile(event)
                                }
                                onDrop={event =>
                                  i
                                  |> dropPdfFile(
                                       event,
                                       ReactEvent.Synthetic.nativeEvent(event)##dataTransfer##files[0],
                                     )
                                }
                                disabled={state.showProgress || !item.formEdit}
                                onClick=chooseFile
                                onDownload={_ =>
                                  clickFile(
                                    item.pdfPath,
                                    item.pdfOriginal,
                                    item.pdfEncryption,
                                    item.pdfExtension,
                                  )
                                }
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
                                   disabled={
                                     state.showProgress || !item.formEdit
                                   }
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
                                 top="0"
                                 right="0"
                                 bottom="0"
                                 left="0"
                                 xs="auto">
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
                                 top="0"
                                 right="0"
                                 bottom="0"
                                 left="0"
                                 xs="auto">
                                 <GridContainer
                                   direction="row"
                                   justify="center"
                                   alignItem="center">
                                   <GridItem
                                     top="0"
                                     right="0"
                                     bottom="0"
                                     left="0"
                                     xs="auto">
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
                                       disabled={
                                         state.showProgress || !item.formEdit
                                       }
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
                                     top="0"
                                     right="0"
                                     bottom="0"
                                     left="0"
                                     xs="auto">
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
                                       disabled={
                                         state.showProgress || !item.formEdit
                                       }
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
                                     top="0"
                                     right="0"
                                     bottom="0"
                                     left="0"
                                     xs="no">
                                     <Button
                                       disabled={
                                         state.showProgress || !item.formEdit
                                       }
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
                                 top="0"
                                 right="0"
                                 bottom="0"
                                 left="0"
                                 xs="auto">
                                 null
                               </GridItem>
                             </GridContainer>
                           </GridItem>
                         | (false, _) => null
                         }}
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
                            disabled={state.showProgress || !item.formEdit}
                            onChange={event =>
                              i
                              |> changeBody(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|說明|js} |> string}
                          </TextFieldMultiline>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
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
                                disabled={state.showProgress || !item.formEdit}
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
                                disabled={state.showProgress || !item.formEdit}
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
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <GridContainer
                            direction="row"
                            justify="center"
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
                                type_="date"
                                value={item.releaseDate}
                                disabled={state.showProgress || !item.formEdit}
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
                                disabled={
                                  state.showProgress
                                  || !item.formEdit
                                  || !item.limit
                                }
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
                 |> array
               | _ =>
                 switch (state.listitems |> Js_array.length) {
                 | 0 =>
                   <GridItem
                     style=errorForm
                     top="18"
                     right="18"
                     bottom="18"
                     left="32"
                     xs="auto">
                     <Typography
                       variant="tile"
                       color="rgba(255,0,0,0.8)"
                       fontSize="x-large">
                       {"UNDEFINED THIS DATABASE" |> string}
                     </Typography>
                   </GridItem>
                 | _ =>
                   state.listitems
                   |> Array.map(item =>
                        <>
                          <GridContainer
                            direction="column"
                            justify="end"
                            alignItem="stretch">
                            <GridItem cursor="pointer" xs="auto">
                              <Typography variant="body2">
                                {item.inoper |> string}
                              </Typography>
                            </GridItem>
                            <GridItem
                              top="18"
                              bottom="18"
                              cursor="pointer"
                              enterBorderRadius="10"
                              borderRadius="10"
                              enterBackgroundColor="rgba(0,0,0,0.1)"
                              xs="auto">
                              <Typography variant="body2">
                                <div
                                  dangerouslySetInnerHTML={
                                    "__html": item.content,
                                  }
                                />
                              </Typography>
                            </GridItem>
                          </GridContainer>
                          <GridItem
                            top="6" right="0" bottom="6" left="0" xs="auto">
                            <Divider />
                          </GridItem>
                        </>
                      )
                   |> array
                 }
               }}
            </GridContainer>
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
            disabled={state.showProgress}
            onClick=closeAnimationFull>
            <Tooltip location="bottom" backgroundColor="rgba(255,0,0,0.8)">
              <FormattedMessage id="closed" defaultMessage="Closed" />
            </Tooltip>
            <IconAction animation="circle" src=clearBlack />
          </IconButton>
        </div>
      </DialogActions>
    </DialogFull>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
