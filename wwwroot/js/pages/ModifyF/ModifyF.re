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
open IconAnimation;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type grotoitem = {
  grotoId: int,
  grotoImage: bool,
  grotoVideo: bool,
  grotoAudio: bool,
  grotoSrc: string,
  grotoPath: string,
  grotoOriginal: string,
  grotoEncryption: string,
  grotoExtension: string,
  grotoName: string,
  grotoDate: string,
  grotoInsert: bool,
  showDelete: bool,
  grotoDelete: bool,
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

type item = {
  postdate: string,
  showGroupMenu: bool,
  groupitems: array(optionitem),
  postGroup: string,
  showNameMenu: bool,
  nameitems: array(optionitem),
  postName: string,
  showCaseMenu: bool,
  caseitems: array(optionitem),
  case: string,
  homepage1: string,
  pnumber: string,
  endDate: string,
  showObjMenu: bool,
  objitems: array(optionitem),
  obj: string,
  homepageMomo: string,
  mb: string,
  amount: string,
  subject: string,
  ecr: string,
  ecn: string,
  showTypeMenu: bool,
  typeitems: array(optionitem),
  type_: string,
  body: string,
  mailitems: array(mbitem),
  showMagroupMenu: bool,
  magroupitems: array(optionitem),
  maGroup: string,
  showManameMenu: bool,
  manameitems: array(optionitem),
  maName: string,
  action1: string,
  workitems: array(mbitem),
  work: string,
  showWork: bool,
  worknoitems: array(optionitem),
  action2: string,
  mbitems: array(mbitem),
  showMtstMenu: bool,
  mtstitems: array(optionitem),
  mtst: string,
  showMbstMenu: bool,
  mbstitems: array(optionitem),
  mbst: string,
  oldno: string,
  newno: string,
  sopno: string,
  action3: string,
  sipno: string,
  action4: string,
  action5: string,
  formModify: bool,
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
  formId: string,
  formTitle: string,
  tabitems: list(tabitem),
  index: int,
  items: array(item),
  showDrop: bool,
  photoitems: array(photoitem),
  grotoitems: array(grotoitem),
  showYoutube: bool,
  youtubeText: string,
};

let newmbitem = (mbId, mbValue) => [|{mbId, mbValue}|];

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
    showDelete: true,
    photoDelete: false,
  },
|];

let newgrotoitem =
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
      name,
    ) => [|
  {
    grotoId: id,
    grotoImage: images,
    grotoVideo: videos,
    grotoAudio: audios,
    grotoSrc: src,
    grotoPath: imagePath,
    grotoOriginal: original,
    grotoEncryption: encryption,
    grotoExtension: extension,
    grotoDate: date,
    grotoName: name,
    grotoInsert: true,
    showDelete: true,
    grotoDelete: false,
  },
|];

type action =
  | SettingError
  | SettingFormLoad(string)
  | SettingFormWidth(int, int)
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormItems(string, string, array(item))
  | ClickItemTab(int)
  | SettingPhotoItems(array(photoitem))
  | SettingGrotoItems(array(grotoitem))
  | ShowGroupMenu(int)
  | ClickGroupMenu(string, int)
  | ShowNameMenu(int)
  | SettingItemName(array(optionitem), int)
  | ClickNameMenu(string, int)
  | ShowCaseMenu(int)
  | ClickCaseMenu(string, int)
  | ChangePage1(string, int)
  | ChangePnumber(string, int)
  | ChangeEndDate(string, int)
  | ShowObjMenu(int)
  | ClickObjMenu(string, int)
  | ChangeMomo(string, int)
  | ChangeMb(string, int)
  | ChangeAmount(string, int)
  | ChangeSubject(string, int)
  | ChangeEcr(string, int)
  | ChangeEcn(string, int)
  | ShowTypeMenu(int)
  | ClickTypeMenu(string, int)
  | InputBody(string, int)
  | ClearMailItem(int, int)
  | ShowMagroupMenu(int)
  | ClickMagroupMenu(string, int)
  | ShowManameMenu(int)
  | SettingItemManame(array(optionitem), int)
  | AddMailItem(string, int)
  | ClickManameMenu(string, int)
  | ChangeAction1(string, int)
  | ClearWorkItem(int, int)
  | ShowWork(bool, int)
  | SettingItemWork(array(optionitem), int)
  | ChangeWork(string, int)
  | ClickItemWork(int)
  | AddWorkItem(string, int)
  | ChangeAction2(string, int)
  | ClearMbItem(int, int)
  | ShowMtstMenu(int)
  | ClickMtstMenu(string, int)
  | ShowMbstMenu(int)
  | SettingItemModel(array(optionitem), int)
  | AddMbItem(string, int)
  | ClickMbstMenu(string, int)
  | ChangeOldno(string, int)
  | ChangeNewno(string, int)
  | ChangeSopno(string, int)
  | ChangeAction3(string, int)
  | ChangeSipno(string, int)
  | ChangeAction4(string, int)
  | ChangeAction5(string, int)
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
  | AddGrotoItem(
      bool,
      bool,
      bool,
      string,
      string,
      string,
      string,
      string,
      string,
      string,
    )
  | ActionGrotoItem(int)
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingError => {...state, error: !state.error}
  | SettingFormLoad(value) => {
      ...state,
      formId: value,
      formLoad: !state.formLoad,
    }
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
  | SettingFormItems(id, value, items) => {
      ...state,
      formId: id,
      formTitle: value,
      items,
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
  | SettingPhotoItems(items) => {...state, photoitems: items}
  | SettingGrotoItems(items) => {...state, grotoitems: items}
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
                formModify: true,
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
              ? {
                ...item,
                postName: value,
                showNameMenu: !item.showNameMenu,
                formModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ShowCaseMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showCaseMenu: !item.showCaseMenu} : item,
          state.items,
        ),
    }
  | ClickCaseMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                case: value,
                showCaseMenu: !item.showCaseMenu,
                formModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ChangePage1(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, homepage1: value, formModify: true} : item,
          state.items,
        ),
    }
  | ChangePnumber(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, pnumber: value, formModify: true} : item,
          state.items,
        ),
    }
  | ChangeEndDate(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, endDate: value, formModify: true} : item,
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
              ? {
                ...item,
                obj: value,
                showObjMenu: !item.showObjMenu,
                formModify: true,
              }
              : item,
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
  | ChangeMb(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, mb: value, formModify: true} : item,
          state.items,
        ),
    }
  | ChangeAmount(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, amount: value, formModify: true} : item,
          state.items,
        ),
    }
  | ChangeSubject(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, subject: value, formModify: true} : item,
          state.items,
        ),
    }
  | ChangeEcr(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, ecr: value, formModify: true} : item,
          state.items,
        ),
    }
  | ChangeEcn(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, ecn: value, formModify: true} : item,
          state.items,
        ),
    }
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
  | InputBody(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, body: value, formModify: true} : item,
          state.items,
        ),
    }
  | ClearMailItem(mbId, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                mailitems:
                  Js_array.filter(
                    (mbitem: mbitem) => mbitem.mbId !== mbId,
                    item.mailitems,
                  ),
              }
              : item,
          state.items,
        ),
    }
  | ShowMagroupMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showMagroupMenu: !item.showMagroupMenu} : item,
          state.items,
        ),
    }
  | ClickMagroupMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                maGroup: value,
                showMagroupMenu: !item.showMagroupMenu,
              }
              : item,
          state.items,
        ),
    }
  | ShowManameMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showManameMenu: !item.showManameMenu} : item,
          state.items,
        ),
    }
  | SettingItemManame(items, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, manameitems: items} : item,
          state.items,
        ),
    }
  | AddMailItem(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                mailitems:
                  Array.append(
                    item.mailitems,
                    newmbitem(
                      item.mailitems |> Js_array.length == 0
                        ? 0
                        : item.mailitems[Js_array.length(item.mailitems) - 1].
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
  | ClickManameMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                maName: value,
                showManameMenu: !item.showManameMenu,
                formModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ChangeAction1(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, action1: value, formModify: true} : item,
          state.items,
        ),
    }
  | ClearWorkItem(mbId, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                workitems:
                  Js_array.filter(
                    (mbitem: mbitem) => mbitem.mbId !== mbId,
                    item.workitems,
                  ),
              }
              : item,
          state.items,
        ),
    }
  | ShowWork(showWork, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showWork} : item,
          state.items,
        ),
    }
  | SettingItemWork(items, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, worknoitems: items, showWork: true} : item,
          state.items,
        ),
    }
  | ChangeWork(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, work: value} : item,
          state.items,
        ),
    }
  | ClickItemWork(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, work: "", showWork: !item.showWork} : item,
          state.items,
        ),
    }
  | AddWorkItem(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                workitems:
                  Array.append(
                    item.workitems,
                    newmbitem(
                      item.workitems |> Js_array.length == 0
                        ? 0
                        : item.workitems[Js_array.length(item.workitems) - 1].
                            mbId
                          + 1,
                      value,
                    ),
                  ),
                formModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ChangeAction2(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, action2: value, formModify: true} : item,
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
              ? {
                ...item,
                mtst: value,
                showMtstMenu: !item.showMtstMenu,
                formModify: true,
              }
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
          (i, item) =>
            index == i ? {...item, mbst: value, formModify: true} : item,
          state.items,
        ),
    }
  | ChangeOldno(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, oldno: value, formModify: true} : item,
          state.items,
        ),
    }
  | ChangeNewno(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, newno: value, formModify: true} : item,
          state.items,
        ),
    }
  | ChangeSopno(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, sopno: value, formModify: true} : item,
          state.items,
        ),
    }
  | ChangeAction3(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, action3: value, formModify: true} : item,
          state.items,
        ),
    }
  | ChangeSipno(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, sipno: value, formModify: true} : item,
          state.items,
        ),
    }
  | ChangeAction4(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, action4: value, formModify: true} : item,
          state.items,
        ),
    }
  | ChangeAction5(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, action5: value, formModify: true} : item,
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
  | AddGrotoItem(
      images,
      videos,
      audios,
      src,
      imagePath,
      original,
      encryption,
      extension,
      date,
      name,
    ) => {
      ...state,
      grotoitems:
        Array.append(
          state.grotoitems,
          newgrotoitem(
            Js_array.length(state.grotoitems) + 1,
            images,
            videos,
            audios,
            src,
            imagePath,
            original,
            encryption,
            extension,
            date,
            name,
          ),
        ),
    }
  | ActionGrotoItem(index) => {
      ...state,
      grotoitems:
        Array.mapi(
          (i, grotoitem) =>
            index == i
              ? {...grotoitem, grotoDelete: !grotoitem.grotoDelete}
              : grotoitem,
          state.grotoitems,
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
  formId: "",
  formTitle: "",
  tabitems: [
    {showTab: true, tabImage: bookBlack},
    {showTab: false, tabImage: collectionsBlack},
    {showTab: false, tabImage: groupBlack},
  ],
  index: 0,
  items: [||],
  showDrop: false,
  photoitems: [||],
  grotoitems: [||],
  showYoutube: false,
  youtubeText: "",
};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);

  let fileRef = useRef(Js.Nullable.null);

  let textRef = useRef(Js.Nullable.null);

  let barShowRestoreAction = youtubeText => {
    ActionSnackBar(youtubeText, true) |> dispatch;
    Js.Global.setTimeout(() => ActionSnackBar("", false) |> dispatch, 5000)
    |> ignore;
  };

  let setTextRef: (React.Ref.t(Js.Nullable.t('b)), string) => unit = [%bs.raw
    (element, value) => {| element.current.innerHTML = value; |}
  ];

  let searchAJax = id =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(id)
      |> Inside.sItem
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               SettingFormItems(
                 id,
                 response##data##tile,
                 response##data##items,
               )
               |> dispatch;
               response##data##items[0].body |> setTextRef(textRef);
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
             ReasonReactRouter.dangerouslyGetInitialUrl().hash |> searchAJax;
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
      let testtime =
        SettingFormLoad(ReasonReactRouter.dangerouslyGetInitialUrl().hash)
        |> dispatch;
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

  let sFileAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Inside.sFile
      |> then_(response =>
           SettingPhotoItems(response##data##items) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let sGrotoAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Inside.sGroto
      |> then_(response =>
           SettingGrotoItems(response##data##items) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickItemTab =
    useCallback(i => {
      ClickItemTab(i) |> dispatch;
      if (i == 1) {
        sFileAJax();
      } else if (i == 2) {
        sGrotoAJax();
      };
    });

  let insertAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iSirmsData(
           state.formId,
           state.formTitle,
           Js_array.filter(
             (item: item) => item.formModify === true,
             state.items,
           ),
           Js_array.filter(
             (photoitem: photoitem) =>
               photoitem.photoInsert === true || photoitem.photoDelete === true,
             state.photoitems,
           ),
           Js_array.filter(
             (grotoitem: grotoitem) =>
               grotoitem.grotoInsert === true || grotoitem.grotoDelete === true,
             state.grotoitems,
           ),
         )
      |> Inside.insert
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               "saveSuccess" |> Sessions.create("form");
               insidePath |> ReasonReactRouter.push;
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

  let showGroupMenu = useCallback(i => ShowGroupMenu(i) |> dispatch);

  let sGroupAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> CreateF.sGroup
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

  let showCaseMenu = useCallback(i => ShowCaseMenu(i) |> dispatch);

  let clickCaseMenu =
    useCallback((value, i) => ClickCaseMenu(value, i) |> dispatch);

  let changePage1 =
    useCallback((value, i) => ChangePage1(value, i) |> dispatch);

  let changePnumber =
    useCallback((value, i) => ChangePnumber(value, i) |> dispatch);

  let changeEndDate =
    useCallback((value, i) => ChangeEndDate(value, i) |> dispatch);

  let showObjMenu = useCallback(i => ShowObjMenu(i) |> dispatch);

  let clickObjMenu =
    useCallback((value, i) => ClickObjMenu(value, i) |> dispatch);

  let changeMomo =
    useCallback((value, i) => ChangeMomo(value, i) |> dispatch);

  let changeMb = useCallback((value, i) => ChangeMb(value, i) |> dispatch);

  let changeAmount =
    useCallback((value, i) => ChangeAmount(value, i) |> dispatch);

  let changeSubject =
    useCallback((value, i) => ChangeSubject(value, i) |> dispatch);

  let changeEcr = useCallback((value, i) => ChangeEcr(value, i) |> dispatch);

  let changeEcn = useCallback((value, i) => ChangeEcn(value, i) |> dispatch);

  let showTypeMenu = useCallback(i => ShowTypeMenu(i) |> dispatch);

  let sTypeAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> CreateF.sType
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               InputBody(response##data##value, i) |> dispatch;
               response##data##value |> setTextRef(textRef);
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickTypeMenu =
    useCallback((value, i) => {
      ClickTypeMenu(value, i) |> dispatch;
      i |> sTypeAJax(value);
    });

  let inputBody = useCallback((value, i) => InputBody(value, i) |> dispatch);

  let clearMailItem =
    useCallback((mbId, i) => ClearMailItem(mbId, i) |> dispatch);

  let showMagroupMenu = useCallback(i => ShowMagroupMenu(i) |> dispatch);

  let sMagroupAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> CreateF.sGroup
      |> then_(response =>
           SettingItemManame(response##data##items, i) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickMagroupMenu =
    useCallback((value, i) => {
      ClickMagroupMenu(value, i) |> dispatch;
      i |> sMagroupAJax(value);
    });

  let showManameMenu = useCallback(i => ShowManameMenu(i) |> dispatch);

  let clickManameMenu =
    useCallback((value, i) => {
      ClickManameMenu(value, i) |> dispatch;
      AddMailItem(value, i) |> dispatch;
    });

  let changeAction1 =
    useCallback((value, i) => ChangeAction1(value, i) |> dispatch);

  let clearWorkItem =
    useCallback((mbId, i) => ClearWorkItem(mbId, i) |> dispatch);

  let sWorknoAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> CreateF.sWorkno
      |> then_(response =>
           SettingItemWork(response##data##items, i) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let changeWork =
    useCallback((value, i) => {
      ChangeWork(value, i) |> dispatch;
      i |> sWorknoAJax(value);
    });

  let cWorknoAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> CreateF.cWorkno
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               ClickItemWork(i) |> dispatch;
               AddWorkItem(value, i) |> dispatch;
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let keydownWork =
    useCallback((keyCode, value, i) =>
      if (keyCode == 13) {
        i |> cWorknoAJax(value);
      }
    );

  let showWork = useCallback(i => ShowWork(false, i) |> dispatch);

  let clickItemWork =
    useCallback((value, i) => {
      ClickItemWork(i) |> dispatch;
      AddWorkItem(value, i) |> dispatch;
    });

  let changeAction2 =
    useCallback((value, i) => ChangeAction2(value, i) |> dispatch);

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

  let changeOldno =
    useCallback((value, i) => ChangeOldno(value, i) |> dispatch);

  let changeNewno =
    useCallback((value, i) => ChangeNewno(value, i) |> dispatch);

  let changeSopno =
    useCallback((value, i) => ChangeSopno(value, i) |> dispatch);

  let changeAction3 =
    useCallback((value, i) => ChangeAction3(value, i) |> dispatch);

  let changeSipno =
    useCallback((value, i) => ChangeSipno(value, i) |> dispatch);

  let changeAction4 =
    useCallback((value, i) => ChangeAction4(value, i) |> dispatch);

  let changeAction5 =
    useCallback((value, i) => ChangeAction5(value, i) |> dispatch);

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

  let cGrotoAJax =
      (
        images,
        videos,
        audios,
        src,
        imagePath,
        original,
        encryption,
        extension,
        date,
      ) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> CreateF.cGroto
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               AddGrotoItem(
                 images,
                 videos,
                 audios,
                 src,
                 imagePath,
                 original,
                 encryption,
                 extension,
                 date,
                 response##data##newid,
               )
               |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status |> statusModule |> barShowRestoreAction
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let upGrotoAJax = files => {
    let formData = FormData.make();
    FormData.append(formData, "file", files) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               response##data##date
               |> cGrotoAJax(
                    response##data##images,
                    response##data##videos,
                    response##data##audios,
                    response##data##src,
                    response##data##imagePath,
                    response##data##original,
                    response##data##encryption,
                    response##data##extension,
                  )
             | _ => ActionShowProgress |> dispatch
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );
  };

  let dropGrotoFile =
    useCallback((event, value) => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowDrop(false) |> dispatch;
      value |> upGrotoAJax;
    });

  let changeGrotoFile =
    useCallback(value => {
      ActionShowProgress |> dispatch;
      value |> upGrotoAJax;
    });

  let actionGroto = useCallback(i => ActionGrotoItem(i) |> dispatch);

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
              ~zIndex="1000",
              (),
            )}
            left="0"
            xs="auto">
            <Typography variant="tile" fontWeight="600">
              {state.formTitle |> string}
            </Typography>
          </GridItem>
          <GridItem
            style={ReactDOMRe.Style.make(
              ~position="sticky",
              ~top="50px",
              ~zIndex="1000",
              (),
            )}
            top="0"
            bottom="6"
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
              {state.update
                 ? <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                     <Button disabled={state.showProgress} onClick=insertForm>
                       <FormattedMessage id="save" defaultMessage="Save" />
                     </Button>
                   </GridItem>
                 : null}
            </GridContainer>
          </GridItem>
          {switch (state.index) {
           | 0 =>
             state.items
             |> Array.mapi((i, item) =>
                  <>
                    <GridItem top="10" right="0" bottom="6" left="6" xs="auto">
                      <Typography variant="subheading" fontWeight="bolder">
                        {item.postdate |> string}
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
                            tile={js|發文部門|js}
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
                            tile={js|發文者|js}
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
                                   animation={
                                     item.showNameMenu |> topDownRorate
                                   }
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
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <SelectStandard
                            top="12"
                            right="0"
                            left="0"
                            tile={js|變更內容|js}
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.case}
                            disabled={state.showProgress}
                            onClick={_ => i |> showCaseMenu}>
                            ...(
                                 item.showCaseMenu
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
                                       {item.caseitems
                                        |> Array.map(caseitem =>
                                             <MenuItem
                                               top="0"
                                               right="8"
                                               bottom="0"
                                               left="8"
                                               disablePadding={
                                                                caseitem.
                                                                  optionPadding
                                                              }
                                               topLeft="12"
                                               topRight="12"
                                               bottomRight="12"
                                               bottomLeft="12"
                                               onClick={_ =>
                                                 i
                                                 |> clickCaseMenu(
                                                      caseitem.value,
                                                    )
                                               }>
                                               {caseitem.value |> string}
                                             </MenuItem>
                                           )
                                        |> array}
                                     </SelectMenu>
                                   : null,
                                 <IconGeneral
                                   animation={
                                     item.showCaseMenu |> topDownRorate
                                   }
                                   src=arrowDownBlack
                                 />,
                               )
                          </SelectStandard>
                          <BackgroundBoard
                            showBackground={item.showCaseMenu}
                            backgroundColor="transparent"
                            onClick={_ => i |> showCaseMenu}
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
                            {{js|訂單號碼|js} |> string}
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
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeEndDate(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|文件有效期限|js} |> string}
                          </TextFieldStandard>
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
                            tile={js|影響站別|js}
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
                              |> changeMb(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {"M/B" |> string}
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
                            value={item.amount}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeAmount(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|生產數量|js} |> string}
                          </TextFieldStandard>
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
                        {{js|主旨|js} |> string}
                      </TextFieldStandard>
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
                            value={item.ecr}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeEcr(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {"ECR" |> string}
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
                            value={item.ecn}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeEcn(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {"ECN" |> string}
                          </TextFieldStandard>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <SelectStandard
                            top="12"
                            right="0"
                            left="0"
                            tile={js|類型|js}
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
                                   animation={
                                     item.showTypeMenu |> topDownRorate
                                   }
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
                      </GridContainer>
                    </GridItem>
                    <GridItem bottom="0" left="0" xs="auto">
                      <ToolBar
                        disabled={state.showProgress}
                        width={state.formWidth}
                      />
                    </GridItem>
                    <GridItem left="0" xs="auto">
                      <TextFieldArticle
                        textRef
                        disabled={state.showProgress}
                        onInput={event =>
                          i
                          |> inputBody(
                               ReactEvent.Form.target(event)##innerHTML,
                             )
                        }
                      />
                    </GridItem>
                    /*<TextFieldMultiline
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
                          |> inputBody(ReactEvent.Form.target(event)##value)
                        }>
                        {{js|說明|js} |> string}
                      </TextFieldMultiline>*/
                    <GridItem top="0" right="6" bottom="6" left="6" xs="auto">
                      <GridContainer
                        direction="row" justify="start" alignItem="center">
                        {item.mailitems
                         |> Array.map(mailitem =>
                              <GridItem top="0" bottom="0" left="0" xs="no">
                                <Chip
                                  enterBorderWidth="0"
                                  downBorderWidth="0"
                                  borderWidth="0"
                                  showButn=true
                                  src=clearBlack
                                  onButton={_ =>
                                    i |> clearMailItem(mailitem.mbId)
                                  }>
                                  ...(
                                       <Typography variant="subtitle2">
                                         {"S" |> string}
                                       </Typography>,
                                       <Typography variant="subtitle2">
                                         {mailitem.mbValue |> string}
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
                            tile={js|相關部門|js}
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.maGroup}
                            disabled={state.showProgress}
                            onClick={_ => i |> showMagroupMenu}>
                            ...(
                                 item.showMagroupMenu
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
                                       {item.magroupitems
                                        |> Array.map(magroupitem =>
                                             <MenuItem
                                               top="0"
                                               right="8"
                                               bottom="0"
                                               left="8"
                                               disablePadding={
                                                                magroupitem.
                                                                  optionPadding
                                                              }
                                               topLeft="12"
                                               topRight="12"
                                               bottomRight="12"
                                               bottomLeft="12"
                                               onClick={_ =>
                                                 i
                                                 |> clickMagroupMenu(
                                                      magroupitem.value,
                                                    )
                                               }>
                                               {magroupitem.value |> string}
                                             </MenuItem>
                                           )
                                        |> array}
                                     </SelectMenu>
                                   : null,
                                 <IconGeneral
                                   animation={
                                     item.showMagroupMenu |> topDownRorate
                                   }
                                   src=arrowDownBlack
                                 />,
                               )
                          </SelectStandard>
                          <BackgroundBoard
                            showBackground={item.showMagroupMenu}
                            backgroundColor="transparent"
                            onClick={_ => i |> showMagroupMenu}
                          />
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <SelectStandard
                            top="12"
                            right="0"
                            left="0"
                            tile={js|相關人員|js}
                            labelColor="rgba(255,0,0,0.8)"
                            enterBorderColor="rgba(255,0,0,0.8)"
                            downBorderColor="rgba(255,0,0,0.6)"
                            borderColor="rgba(0,0,0,0.2)"
                            value={item.maName}
                            disabled={state.showProgress}
                            onClick={_ => i |> showManameMenu}>
                            ...(
                                 item.showManameMenu
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
                                       {item.manameitems
                                        |> Array.map(manameitem =>
                                             <MenuItem
                                               top="0"
                                               right="8"
                                               bottom="0"
                                               left="8"
                                               disablePadding={
                                                                manameitem.
                                                                  optionPadding
                                                              }
                                               topLeft="12"
                                               topRight="12"
                                               bottomRight="12"
                                               bottomLeft="12"
                                               onClick={_ =>
                                                 i
                                                 |> clickManameMenu(
                                                      manameitem.value,
                                                    )
                                               }>
                                               {manameitem.value |> string}
                                             </MenuItem>
                                           )
                                        |> array}
                                     </SelectMenu>
                                   : null,
                                 <IconGeneral
                                   animation={
                                     item.showManameMenu |> topDownRorate
                                   }
                                   src=arrowDownBlack
                                 />,
                               )
                          </SelectStandard>
                          <BackgroundBoard
                            showBackground={item.showManameMenu}
                            backgroundColor="transparent"
                            onClick={_ => i |> showManameMenu}
                          />
                        </GridItem>
                      </GridContainer>
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
                        value={item.action1}
                        disabled={state.showProgress}
                        onChange={event =>
                          i
                          |> changeAction1(
                               ReactEvent.Form.target(event)##value,
                             )
                        }>
                        {{js|資材處|js} |> string}
                      </TextFieldMultiline>
                    </GridItem>
                    <GridItem top="0" right="6" bottom="6" left="6" xs="auto">
                      <GridContainer
                        direction="row" justify="start" alignItem="center">
                        {item.workitems
                         |> Array.map(workitem =>
                              <GridItem top="0" bottom="0" left="0" xs="no">
                                <Chip
                                  enterBorderWidth="0"
                                  downBorderWidth="0"
                                  borderWidth="0"
                                  showButn=true
                                  src=clearBlack
                                  onButton={_ =>
                                    i |> clearWorkItem(workitem.mbId)
                                  }>
                                  ...(
                                       <Typography variant="subtitle2">
                                         {"S" |> string}
                                       </Typography>,
                                       <Typography variant="subtitle2">
                                         {workitem.mbValue |> string}
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
                        value={item.work}
                        disabled={state.showProgress}
                        onChange={event =>
                          i
                          |> changeWork(ReactEvent.Form.target(event)##value)
                        }
                        onKeyDown={event =>
                          i
                          |> keydownWork(
                               ReactEvent.Keyboard.keyCode(event),
                               ReactEvent.Keyboard.target(event)##value,
                             )
                        }>
                        {{js|生產工單|js} |> string}
                      </TextFieldStandard>
                      {item.showWork
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
                               {item.worknoitems
                                |> Array.map(worknoitem =>
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
                                         i |> clickItemWork(worknoitem.value)
                                       }>
                                       <Typography variant="subheading">
                                         {worknoitem.value |> string}
                                       </Typography>
                                     </MenuItem>
                                   )
                                |> array}
                             </SelectMenu>
                             <BackgroundBoard
                               showBackground=true
                               backgroundColor="transparent"
                               onClick={_ => i |> showWork}
                             />
                           </>
                         : null}
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
                        value={item.action2}
                        disabled={state.showProgress}
                        onChange={event =>
                          i
                          |> changeAction2(
                               ReactEvent.Form.target(event)##value,
                             )
                        }>
                        {{js|工程處|js} |> string}
                      </TextFieldMultiline>
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
                    <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="center" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <SelectStandard
                            top="12"
                            right="0"
                            left="0"
                            tile={js|篩選M/B|js}
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
                            tile="M/B"
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
                            value={item.oldno}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeOldno(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|舊料號|js} |> string}
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
                            value={item.newno}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeNewno(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|新料號|js} |> string}
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
                            value={item.sopno}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeSopno(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {{js|SOP文件編號|js} |> string}
                          </TextFieldStandard>
                        </GridItem>
                      </GridContainer>
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
                        value={item.action3}
                        disabled={state.showProgress}
                        onChange={event =>
                          i
                          |> changeAction3(
                               ReactEvent.Form.target(event)##value,
                             )
                        }>
                        {{js|品保處|js} |> string}
                      </TextFieldMultiline>
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
                        value={item.sipno}
                        disabled={state.showProgress}
                        onChange={event =>
                          i
                          |> changeSipno(
                               ReactEvent.Form.target(event)##value,
                             )
                        }>
                        {{js|SIP文件編號|js} |> string}
                      </TextFieldStandard>
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
                        value={item.action4}
                        disabled={state.showProgress}
                        onChange={event =>
                          i
                          |> changeAction4(
                               ReactEvent.Form.target(event)##value,
                             )
                        }>
                        {{js|生產處|js} |> string}
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
                        value={item.action5}
                        disabled={state.showProgress}
                        onChange={event =>
                          i
                          |> changeAction5(
                               ReactEvent.Form.target(event)##value,
                             )
                        }>
                        {{js|不知道|js} |> string}
                      </TextFieldMultiline>
                    </GridItem>
                  </>
                )
             |> array
           | 1 =>
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
                                   {photoitem.showDelete
                                      ? <GridItem
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
                                      : null}
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
                     |> dropGrotoFile(event)
                   }
                   disabled={state.showProgress}
                   onClick=chooseFile
                   onChange={event =>
                     ReactEvent.Form.target(event)##files[0]
                     |> changeGrotoFile
                   }
                 />
               </GridItem>
               <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                 <GridContainer
                   direction="columnReverse"
                   justify="center"
                   alignItem="stretch">
                   {state.grotoitems
                    |> Array.mapi((i, grotoitem) =>
                         <>
                           <GridItem
                             enterBorderRadius="15"
                             borderRadius="15"
                             enterBackgroundColor={
                               grotoitem.grotoDelete
                                 ? "rgba(255,0,0,1)" : "rgba(255,255,255,1)"
                             }
                             backgroundColor={
                               grotoitem.grotoDelete
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
                                    grotoitem.grotoImage,
                                    grotoitem.grotoVideo,
                                    grotoitem.grotoAudio,
                                  ) {
                                  | (true, _, _) =>
                                    <Image
                                      width="auto"
                                      height="300px"
                                      borderRadius="6"
                                      src={
                                        grotoitem.grotoPath
                                        ++ grotoitem.grotoSrc
                                      }
                                    />
                                  | (_, true, _) =>
                                    <Media
                                      width="auto"
                                      borderRadius="6"
                                      controls=true
                                      src={
                                        grotoitem.grotoPath
                                        ++ grotoitem.grotoSrc
                                      }
                                    />
                                  | (_, _, true) =>
                                    <Media
                                      variant="audio"
                                      width="auto"
                                      borderRadius="6"
                                      controls=true
                                      src={
                                        grotoitem.grotoPath
                                        ++ grotoitem.grotoSrc
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
                                         grotoitem.grotoDelete
                                           ? "rgba(255,255,255,1)"
                                           : "rgba(0,0,0,1)"
                                       }
                                       noWrap=true>
                                       {grotoitem.grotoOriginal
                                        ++ grotoitem.grotoExtension
                                        ++ "("
                                        ++ grotoitem.grotoName
                                        ++ ")"
                                        |> string}
                                     </Typography>
                                   </GridItem>
                                   {grotoitem.showDelete
                                      ? <GridItem
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
                                            onClick={_ => i |> actionGroto}>
                                            <IconAction
                                              animation="leftRight"
                                              src={
                                                grotoitem.grotoDelete
                                                  ? refreshWhite : deleteBlack
                                              }
                                            />
                                          </IconButton>
                                        </GridItem>
                                      : null}
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
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
