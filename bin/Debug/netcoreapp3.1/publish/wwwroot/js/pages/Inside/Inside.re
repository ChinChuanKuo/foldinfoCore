open React;
open Together;
open ReactIntl;
open Data;
open Icons;
open Items;
open Axiosapi;
open Status;
open Storage;
open IconAnimation;
open ObjectFormat;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type actionitem = {
  actId: string,
  actName: string,
  actContent: string,
  actDate: string,
};

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

type formitem = {
  snno: string,
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
  showXps: bool,
  ecn: string,
  en: string,
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
  code: string,
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
  formTrans: bool,
  formSend: bool,
  formModify: bool,
};

type item = {
  ids: string,
  numbers: string,
  indexs: int,
  subjects: string,
  postdates: string,
  postGroups: string,
  homepage1s: string,
  pnumbers: string,
  objs: string,
  homepageMomos: string,
  mbs: string,
  changeCases: string,
  worknumbers: string,
  endDates: string,
  postTP: string,
  postTM: string,
  postTB: string,
  postTS: string,
  colors: string,
  status: string,
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
  tabsitems: list(tabitem),
  showFull: bool,
  formIndex: int,
  formId: string,
  formTitle: string,
  tabitems: list(tabitem),
  index: int,
  formitems: array(formitem),
  showDrop: bool,
  photoitems: array(photoitem),
  grotoitems: array(grotoitem),
  actionitems: array(actionitem),
  showFileFull: bool,
  fileId: string,
  fileTile: string,
  filePath: string,
  fileSrc: string,
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
  | SettingFormLoad
  | SettingFormWidth(int, int)
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFilItems(array(filitem))
  | SettingFormItems(bool, int, array(item))
  | SettingScrollItems(bool, array(item))
  | RefreshFormItem(string, string)
  | ShowAnimationFull(int, string, string, array(formitem))
  | ShowRecord(bool)
  | ClickRecordItems(array(recorditem))
  | ChangeRecord(string)
  | ClickItemRecord(string)
  | ClearFilterItems
  | ShowMenu(int)
  | ClickMenu(string, int)
  | ClearItem(string)
  | ClickItemTabs(int, int)
  | ClickItemTab(int)
  | SettingPhotoItems(array(photoitem))
  | SettingGrotoItems(array(grotoitem))
  | SettingActionItems(array(actionitem))
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
  | ChangeEn(string, int)
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
  | SettingItemMtst(array(optionitem), int)
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
  | CloseAnimationFull
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
  | RefreshFormItem(color, status) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            state.formIndex == i ? {...item, colors: color, status} : item,
          state.items,
        ),
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
  | ClickItemTabs(tindex, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, indexs: tindex} : item,
          state.items,
        ),
      tabsitems:
        List.mapi(
          (i, tabitem) => {...tabitem, showTab: tindex == i},
          state.tabsitems,
        ),
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
  | SettingActionItems(items) => {
      ...state,
      actionitems: Array.append(state.actionitems, items),
    }
  | ShowGroupMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showGroupMenu: !item.showGroupMenu} : item,
          state.formitems,
        ),
    }
  | ClickGroupMenu(value, index) => {
      ...state,
      formitems:
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
          state.formitems,
        ),
    }
  | ShowNameMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showNameMenu: !item.showNameMenu} : item,
          state.formitems,
        ),
    }
  | SettingItemName(items, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, nameitems: items} : item,
          state.formitems,
        ),
    }
  | ClickNameMenu(value, index) => {
      ...state,
      formitems:
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
          state.formitems,
        ),
    }
  | ShowCaseMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showCaseMenu: !item.showCaseMenu} : item,
          state.formitems,
        ),
    }
  | ClickCaseMenu(value, index) => {
      ...state,
      formitems:
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
          state.formitems,
        ),
    }
  | ChangePage1(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, homepage1: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangePnumber(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, pnumber: value, formModify: true} : item,
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
          (i, item) => index == i ? {...item, homepageMomo: value} : item,
          state.formitems,
        ),
    }
  | ChangeMb(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, mb: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeAmount(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, amount: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeSubject(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, subject: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeEcr(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, ecr: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeEcn(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, ecn: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeEn(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, en: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ShowTypeMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showTypeMenu: !item.showTypeMenu} : item,
          state.formitems,
        ),
    }
  | ClickTypeMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, type_: value, showTypeMenu: !item.showTypeMenu}
              : item,
          state.formitems,
        ),
    }
  | InputBody(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, body: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ClearMailItem(mbId, index) => {
      ...state,
      formitems:
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
          state.formitems,
        ),
    }
  | ShowMagroupMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showMagroupMenu: !item.showMagroupMenu} : item,
          state.formitems,
        ),
    }
  | ClickMagroupMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                maGroup: value,
                showMagroupMenu: !item.showMagroupMenu,
              }
              : item,
          state.formitems,
        ),
    }
  | ShowManameMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showManameMenu: !item.showManameMenu} : item,
          state.formitems,
        ),
    }
  | SettingItemManame(items, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, manameitems: items} : item,
          state.formitems,
        ),
    }
  | AddMailItem(value, index) => {
      ...state,
      formitems:
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
          state.formitems,
        ),
    }
  | ClickManameMenu(value, index) => {
      ...state,
      formitems:
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
          state.formitems,
        ),
    }
  | ChangeAction1(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, action1: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ClearWorkItem(mbId, index) => {
      ...state,
      formitems:
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
          state.formitems,
        ),
    }
  | ShowWork(showWork, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, showWork} : item,
          state.formitems,
        ),
    }
  | SettingItemWork(items, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, worknoitems: items, showWork: true} : item,
          state.formitems,
        ),
    }
  | ChangeWork(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, work: value} : item,
          state.formitems,
        ),
    }
  | ClickItemWork(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, work: "", showWork: !item.showWork} : item,
          state.formitems,
        ),
    }
  | AddWorkItem(value, index) => {
      ...state,
      formitems:
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
          state.formitems,
        ),
    }
  | ChangeAction2(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, action2: value, formModify: true} : item,
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
  | SettingItemMtst(items, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, mtstitems: items} : item,
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
            index == i ? {...item, mbst: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeOldno(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, oldno: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeNewno(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, newno: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeSopno(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, sopno: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeAction3(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, action3: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeSipno(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, sipno: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeAction4(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, action4: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeAction5(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, action5: value, formModify: true} : item,
          state.formitems,
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
  | CloseAnimationFull => {...state, showFull: !state.showFull}
  | SettingFileItem(id, tile, path, src) => {
      ...state,
      fileId: id,
      fileTile: tile,
      filePath: path,
      fileSrc: src,
      showFileFull: !state.showFileFull,
      showFull: !state.showFull,
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
  record: "",
  showRecord: false,
  recorditems: [||],
  filitems: [||],
  showItem: false,
  itemCount: 0,
  items: [||],
  tabsitems: [
    {showTab: true, tabImage: descriptionBlack},
    {showTab: false, tabImage: collectionsBlack},
  ],
  showFull: false,
  formIndex: 0,
  formId: "",
  formTitle: "",
  tabitems: [
    {showTab: true, tabImage: descriptionBlack},
    {showTab: false, tabImage: collectionsBlack},
    {showTab: false, tabImage: groupBlack},
    {showTab: false, tabImage: listBlack},
  ],
  index: 0,
  formitems: [||],
  showDrop: false,
  photoitems: [||],
  grotoitems: [||],
  actionitems: [||],
  showFileFull: false,
  fileId: "",
  fileTile: "",
  filePath: "",
  fileSrc: "",
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

  let searchAJax = () =>
    Js.Promise.(
      state.items
      |> Js_array.length
      |> string_of_int
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.Inside.search
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
      |> Axiosapi.Inside.filter
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
      |> Axiosapi.Inside.scroll
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
      |> Axiosapi.Inside.sRecord
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
      |> Axiosapi.Inside.sFiltCord
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
      |> Axiosapi.Inside.sFilter
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

  let setTextRef: (React.Ref.t(Js.Nullable.t('b)), string) => unit = [%bs.raw
    (element, value) => {| element.current.innerHTML = value; |}
  ];

  let sItemAJax = (index, id) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(id)
      |> Axiosapi.Inside.sItem
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowAnimationFull(
                 index,
                 id,
                 response##data##tile,
                 response##data##items,
               )
               |> dispatch;
               response##data##items[0].body |> setTextRef(textRef);
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
      |> Axiosapi.Inside.clear
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
    useCallback((id, event) => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      id |> clearAJax;
    });

  let clickItemTabs =
    useCallback((ti, i, event) => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      ClickItemTabs(ti, i) |> dispatch;
    });

  let sFileAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Axiosapi.Inside.sFile
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
      |> Axiosapi.Inside.sGroto
      |> then_(response =>
           SettingGrotoItems(response##data##items) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let sActionAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> sRowsData(state.formId, state.actionitems |> Js_array.length)
      |> Axiosapi.Inside.sAction
      |> then_(response =>
           SettingActionItems(response##data##items) |> dispatch |> resolve
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
      } else if (i == 3) {
        sActionAJax();
      };
    });

  let refreshAJax = (color, status) =>
    RefreshFormItem(color, status) |> dispatch;

  let insertAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iSirmsData(
           state.formId,
           state.formTitle,
           Js_array.filter(
             (formitem: formitem) => formitem.formModify === true,
             state.formitems,
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
      |> Axiosapi.Inside.insert
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               {js|文件建立中|js} |> refreshAJax("rgba(255,0,0,0.8)");
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

  let insertForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      insertAJax();
    });

  let sendAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iSirmsData(
           state.formId,
           state.formTitle,
           Js_array.filter(
             (formitem: formitem) => formitem.formModify === true,
             state.formitems,
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
      |> Axiosapi.Inside.send
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               {js|等待工程處簽核|js} |> refreshAJax("#E36C0A");
               CloseAnimationFull |> dispatch;
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

  let sEcrnoAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.CreateF.sEcrno
      |> then_(response =>
           SettingItemMtst(response##data##items, i) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let keydownEcr =
    useCallback((keyCode, value, i) =>
      if (keyCode == 13) {
        i |> sEcrnoAJax(value);
      }
    );

  let sXpsAJax = value =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> CreateF.sXps
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               SettingFileItem(
                 response##data##formId,
                 response##data##tile,
                 response##data##items[0].filePath,
                 response##data##items[0].fileSrc,
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

  let changeEcn = useCallback((value, i) => ChangeEcn(value, i) |> dispatch);

  let changeEn = useCallback((value, i) => ChangeEn(value, i) |> dispatch);

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

  let sModelAJax = (ecrno, value, i) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> sRowsData(ecrno, value)
      |> Axiosapi.CreateF.sModel
      |> then_(response =>
           SettingItemModel(response##data##items, i) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickMtstMenu =
    useCallback((ecr, value, i) => {
      ClickMtstMenu(value, i) |> dispatch;
      i |> sModelAJax(ecr, value);
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

  let closeAnimationFull = useCallback(_ => CloseAnimationFull |> dispatch);

  let closeFileFull =
    useCallback(_ => {
      CloseAnimationFull |> dispatch;
      CloseFileFull |> dispatch;
    });

  let downloadAJax = () =>
    Js.Promise.(
      state.fileId
      |> otherData("newid" |> Locals.select)
      |> CreateF.download
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

  let downloadFile =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      downloadAJax();
    });

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
                        bottom="6"
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
                                   onClick={event =>
                                     event |> clearItem(item.ids)
                                   }>
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
                        bottom="0"
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <Tabs id="list-" index={item.indexs} height="3">
                          {state.tabsitems
                           |> List.mapi((ti, tabsitem) =>
                                <Tab
                                  showTab={tabsitem.showTab}
                                  maxWidth="111.6"
                                  height="32"
                                  borderRadius="15"
                                  id={"list-" ++ string_of_int(ti)}
                                  animationName="none"
                                  onClick={event =>
                                    event |> clickItemTabs(ti, i)
                                  }>
                                  <IconAction
                                    width="20"
                                    height="20"
                                    animation="leftRight"
                                    src={tabsitem.tabImage}
                                  />
                                </Tab>
                              )
                           |> Array.of_list
                           |> array}
                        </Tabs>
                      </GridItem>
                      {switch (item.indexs) {
                       | 0 =>
                         <>
                           <GridItem
                             top="0"
                             left="14"
                             bottom="0"
                             enterBackgroundColor="none"
                             backgroundColor="none"
                             xs="auto">
                             <Typography variant="subheading">
                               {item.postTS |> string}
                             </Typography>
                           </GridItem>
                           <GridItem
                             top="0"
                             left="14"
                             bottom="0"
                             enterBackgroundColor="none"
                             backgroundColor="none"
                             xs="auto">
                             <Typography variant="body2" color="#606060">
                               {item.postTP |> string}
                             </Typography>
                           </GridItem>
                           <GridItem
                             top="0"
                             bottom="0"
                             enterBackgroundColor="none"
                             backgroundColor="none"
                             xs="auto">
                             <Typography
                               variant="body2"
                               color="#606060"
                               whiteSpace="inherit">
                               {item.postTM |> string}
                             </Typography>
                           </GridItem>
                           <GridItem
                             top="0"
                             bottom="0"
                             enterBackgroundColor="none"
                             backgroundColor="none"
                             xs="auto">
                             <Typography
                               variant="body2"
                               color="#606060"
                               whiteSpace="inherit">
                               {item.postTB |> string}
                             </Typography>
                           </GridItem>
                         </>
                       | _ =>
                         <>
                           <GridItem
                             top="0"
                             left="14"
                             bottom="0"
                             enterBackgroundColor="none"
                             backgroundColor="none"
                             xs="auto">
                             <Typography variant="subheading">
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
                                   {item.postdates |> string}
                                 </Typography>
                               </GridItem>
                               <GridItem
                                 top="0"
                                 bottom="0"
                                 left="0"
                                 enterBackgroundColor="none"
                                 backgroundColor="none"
                                 xs="no">
                                 <Typography variant="body2" color="#606060">
                                   {item.postGroups |> string}
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
                                   {item.homepage1s |> string}
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
                                   {item.pnumbers |> string}
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
                                   {item.changeCases |> string}
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
                                   {item.endDates |> string}
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
                               variant="body2"
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
                               variant="body2"
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
                               variant="body2"
                               color="#606060"
                               whiteSpace="inherit">
                               {item.worknumbers |> string}
                             </Typography>
                           </GridItem>
                         </>
                       }}
                      <GridItem
                        top="0"
                        bottom="0"
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <Typography variant="body2" color={item.colors}>
                          {item.status |> string}
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
                  {state.update
                     ? <>
                         <GridItem
                           top="0" right="0" bottom="0" left="0" xs="no">
                           <Button
                             disabled={state.showProgress} onClick=insertForm>
                             <FormattedMessage
                               id="save"
                               defaultMessage="Save"
                             />
                           </Button>
                         </GridItem>
                         {state.formitems
                          |> Array.map(item =>
                               item.formSend
                                 ? <GridItem
                                     top="0"
                                     right="0"
                                     bottom="0"
                                     left="0"
                                     xs="no">
                                     <Button
                                       disabled={state.showProgress}
                                       onClick=sendForm>
                                       <FormattedMessage
                                         id="send"
                                         defaultMessage="Send"
                                       />
                                     </Button>
                                   </GridItem>
                                 : null
                             )
                          |> array}
                       </>
                     : null}
                </GridContainer>
              </GridItem>
              {switch (state.index) {
               | 0 =>
                 state.formitems
                 |> Array.mapi((i, item) =>
                      <>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <GridContainer
                            direction="row"
                            justify="center"
                            alignItem="center">
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="auto">
                              null
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
                                value={item.snno}
                                disabled=true>
                                {{js|SN編號|js} |> string}
                              </TextFieldStandard>
                            </GridItem>
                          </GridContainer>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <Typography
                            variant="subheading"
                            color="rgba(0,0,0,0.6)"
                            fontWeight="bolder">
                            {{js|【工廠內部通告】|js} |> string}
                          </Typography>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <GridContainer
                            direction="row"
                            justify="center"
                            alignItem="center">
                            <GridItem
                              top="20" right="0" bottom="6" left="6" xs="auto">
                              <Typography
                                variant="subheading" fontWeight="bolder">
                                {item.postdate |> string}
                              </Typography>
                            </GridItem>
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
                                disabled={state.showProgress || !item.formSend}
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
                                disabled={state.showProgress || !item.formSend}
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
                                value={item.ecr}
                                disabled={
                                  state.showProgress
                                  || !item.formTrans
                                  || !item.formSend
                                }
                                onChange={event =>
                                  i
                                  |> changeEcr(
                                       ReactEvent.Form.target(event)##value,
                                     )
                                }
                                onKeyDown={event =>
                                  i
                                  |> keydownEcr(
                                       ReactEvent.Keyboard.keyCode(event),
                                       item.ecr,
                                     )
                                }>
                                {"ECR" |> string}
                              </TextFieldStandard>
                            </GridItem>
                            {item.showXps
                               ? <GridItem
                                   top="0"
                                   right="0"
                                   bottom="0"
                                   left="0"
                                   xs="no">
                                   <IconButton
                                     padding="2"
                                     disabled={state.showProgress}
                                     onClick={_ => item.ecr |> showXpsFile}>
                                     <IconAction
                                       animation="circle"
                                       src=visibilityBlack
                                     />
                                   </IconButton>
                                 </GridItem>
                               : null}
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
                                disabled={
                                  state.showProgress
                                  || !item.formTrans
                                  || !item.formSend
                                }
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
                              <TextFieldStandard
                                top="12"
                                right="0"
                                left="0"
                                labelColor="rgba(255,0,0,0.8)"
                                enterBorderColor="rgba(255,0,0,0.8)"
                                downBorderColor="rgba(255,0,0,0.6)"
                                borderColor="rgba(0,0,0,0.2)"
                                value={item.en}
                                disabled={
                                  state.showProgress
                                  || !item.formTrans
                                  || !item.formSend
                                }
                                onChange={event =>
                                  i
                                  |> changeEn(
                                       ReactEvent.Form.target(event)##value,
                                     )
                                }>
                                {"EN" |> string}
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
                                disabled={state.showProgress || !item.formSend}
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
                        <GridItem
                          top="0" right="6" bottom="6" left="6" xs="auto">
                          <GridContainer
                            direction="row" justify="start" alignItem="center">
                            {item.mailitems
                             |> Array.map(mailitem =>
                                  <GridItem
                                    top="0" bottom="0" left="0" xs="no">
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
                                             {Js_string.substring(
                                                mailitem.mbValue,
                                                ~from=0,
                                                ~to_=1,
                                              )
                                              |> string}
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
                        <GridItem top="0" bottom="0" left="0" xs="auto">
                          <Typography
                            variant="subheading"
                            color="rgba(0,0,0,0.6)"
                            fontWeight="bolder">
                            {{js|【作法說明及執行確認】|js}
                             |> string}
                          </Typography>
                        </GridItem>
                        <GridItem bottom="0" left="0" xs="auto">
                          <Typography
                            variant="subheading"
                            color="rgba(0,0,0,0.6)"
                            fontWeight="bolder">
                            {{js|【資材處】|js} |> string}
                          </Typography>
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
                            value={item.action1}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeAction1(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            null
                          </TextFieldMultiline>
                        </GridItem>
                        <GridItem
                          top="0" right="6" bottom="6" left="6" xs="auto">
                          <GridContainer
                            direction="row" justify="start" alignItem="center">
                            {item.workitems
                             |> Array.map(workitem =>
                                  <GridItem
                                    top="0" bottom="0" left="0" xs="no">
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
                                             {Js_string.substring(
                                                workitem.mbValue,
                                                ~from=0,
                                                ~to_=1,
                                              )
                                              |> string}
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
                            value={item.work}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeWork(
                                   ReactEvent.Form.target(event)##value,
                                 )
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
                                             i
                                             |> clickItemWork(
                                                  worknoitem.value,
                                                )
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
                        <GridItem bottom="0" left="0" xs="auto">
                          <Typography
                            variant="subheading"
                            color="rgba(0,0,0,0.6)"
                            fontWeight="bolder">
                            {{js|【工程處】|js} |> string}
                          </Typography>
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
                            value={item.action2}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeAction2(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            null
                          </TextFieldMultiline>
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
                                             {Js_string.substring(
                                                mbitem.mbValue,
                                                ~from=0,
                                                ~to_=1,
                                              )
                                              |> string}
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
                                                          item.ecr,
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
                                value={item.code}
                                disabled=true>
                                {"Change Code" |> string}
                              </TextFieldStandard>
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
                        <GridItem bottom="0" left="0" xs="auto">
                          <Typography
                            variant="subheading"
                            color="rgba(0,0,0,0.6)"
                            fontWeight="bolder">
                            {{js|【品保處】|js} |> string}
                          </Typography>
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
                            value={item.action3}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeAction3(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            null
                          </TextFieldMultiline>
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
                        <GridItem bottom="0" left="0" xs="auto">
                          <Typography
                            variant="subheading"
                            color="rgba(0,0,0,0.6)"
                            fontWeight="bolder">
                            {{js|【生產處】|js} |> string}
                          </Typography>
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
                            value={item.action4}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeAction4(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            null
                          </TextFieldMultiline>
                        </GridItem>
                        <GridItem bottom="0" left="0" xs="auto">
                          <Typography
                            variant="subheading"
                            color="rgba(0,0,0,0.6)"
                            fontWeight="bolder">
                            {{js|【不知道】|js} |> string}
                          </Typography>
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
                            value={item.action5}
                            disabled={state.showProgress}
                            onChange={event =>
                              i
                              |> changeAction5(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            null
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
                                     ? "rgba(255,0,0,1)"
                                     : "rgba(255,255,255,1)"
                                 }
                                 backgroundColor={
                                   photoitem.photoDelete
                                     ? "rgba(255,0,0,0.8)"
                                     : "rgba(255,255,255,1)"
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
                                                      ? refreshWhite
                                                      : deleteBlack
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
               | 2 =>
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
                                     ? "rgba(255,0,0,1)"
                                     : "rgba(255,255,255,1)"
                                 }
                                 backgroundColor={
                                   grotoitem.grotoDelete
                                     ? "rgba(255,0,0,0.8)"
                                     : "rgba(255,255,255,1)"
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
                                                      ? refreshWhite
                                                      : deleteBlack
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
                 <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                   <GridContainer
                     direction="columnReverse"
                     justify="center"
                     alignItem="stretch">
                     {state.actionitems
                      |> Array.mapi((i, item) =>
                           <>
                             <GridItem
                               enterBorderRadius="15"
                               borderRadius="15"
                               xs="auto">
                               <GridContainer
                                 backgroundColor="transparent"
                                 direction="column"
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
                                   <GridContainer
                                     backgroundColor="transparent"
                                     direction="row"
                                     justify="center"
                                     alignItem="center">
                                     <GridItem
                                       top="0"
                                       right="0"
                                       bottom="0"
                                       left="0"
                                       enterBackgroundColor="transparent"
                                       backgroundColor="transparent"
                                       xs="no">
                                       <Avatar
                                         top="5"
                                         right="16"
                                         bottom="5"
                                         left="0">
                                         {Js_string.substring(
                                            item.actName,
                                            ~from=0,
                                            ~to_=1,
                                          )
                                          |> string}
                                       </Avatar>
                                     </GridItem>
                                     <GridItem
                                       top="0"
                                       right="0"
                                       bottom="0"
                                       left="0"
                                       enterBackgroundColor="transparent"
                                       backgroundColor="transparent"
                                       xs="auto">
                                       <Typography variant="subheading">
                                         {item.actDate |> string}
                                       </Typography>
                                     </GridItem>
                                   </GridContainer>
                                 </GridItem>
                                 <GridItem
                                   top="0"
                                   right="0"
                                   bottom="0"
                                   left="40"
                                   enterBackgroundColor="transparent"
                                   backgroundColor="transparent"
                                   xs="auto">
                                   <div
                                     dangerouslySetInnerHTML={
                                       "__html": item.actContent,
                                     }
                                   />
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
            <Iframe
              height={string_of_int(state.formHeight) ++ "px"}
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
            onClick=downloadFile>
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
