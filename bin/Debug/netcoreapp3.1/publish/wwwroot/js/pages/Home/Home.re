open React;
open Together;
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

type formitem = {
  postdate: string,
  postGroup: string,
  postName: string,
  showFloorMenu: bool,
  flooritems: array(optionitem),
  floor: string,
  workno: string,
  showXps: bool,
  homepage1: string,
  pnumber: string,
  showMomoMenu: bool,
  momoitems: array(optionitem),
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
  amount: string,
  invest: string,
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
  releasedate: string,
  formDelete: bool,
  formEdit: bool,
  formWork: bool,
  formQuality: bool,
  formSend: bool,
  formModify: bool,
};

type item = {
  ids: string,
  numbers: string,
  subjects: string,
  postdates: string,
  postGroups: string,
  fails: string,
  homepage1s: string,
  homepageMomos: string,
  mbs: string,
  objs: string,
  worknumbers: string,
  repliers: string,
  issuesorts: string,
  belongs: string,
  stages: string,
  colors: string,
  status: string,
  itemPassed: bool,
  itemPlused: bool,
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
  firdate: string,
  secdate: string,
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
  showDrop: bool,
  photoitems: array(photoitem),
  showFileFull: bool,
  fileId: string,
  fileTile: string,
  filePath: string,
  fileSrc: string,
  showPhotoFull: bool,
  photoId: string,
  photoTile: string,
  photoImage: bool,
  photoAudio: bool,
  photoVideo: bool,
  photoPath: string,
  photoSrc: string,
  showAskDialog: bool,
  showYoutube: bool,
  youtubeText: string,
};

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
  | RefreshFormItem(string, string)
  | ShowAnimationFull(int, string, string, array(formitem))
  | ShowRecord(bool)
  | ClickRecordItems(array(recorditem))
  | ChangeRecord(string)
  | ClickItemRecord(string)
  | ClearFilterItems
  | ChangeFirDate(string)
  | ChangeSecDate(string)
  | ShowMenu(int)
  | ClickMenu(string, int)
  | ClearItem(string)
  | SettingItem(int)
  | ClickItemTab(int)
  | SettingPhotoItems(array(photoitem))
  | ShowFloorMenu(int)
  | ClickFloorMenu(string, int)
  | ChangeWorkno(string, int)
  | SettingItemWorkno(
      string,
      bool,
      string,
      string,
      string,
      array(optionitem),
      string,
      array(optionitem),
      string,
      int,
    )
  | ChangePage1(string, int)
  | ChangePnumber(string, int)
  | ShowMomoMenu(int)
  | ClickMomoMenu(string, int)
  | ShowMbMenu(int)
  | ClickMbMenu(string, int)
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
  | ChangeReleasedate(string, int)
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
  | CloseAnimationFull
  | SendAnimationFull(int)
  | ClearAnimationFull(string)
  | SettingFileItem(string, string, string, string)
  | CloseFileFull
  | SettingPhotoItem(string, string, bool, bool, bool, string, string)
  | ClosePhotoFull
  | CloseAskFull
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
  | ChangeFirDate(value) => {...state, firdate: value}
  | ChangeSecDate(value) => {...state, secdate: value}
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
  | SettingItem(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, itemPlused: !item.itemPlused} : item,
          state.items,
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
  | ShowFloorMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showFloorMenu: !item.showFloorMenu} : item,
          state.formitems,
        ),
    }
  | ClickFloorMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                floor: value,
                showFloorMenu: !item.showFloorMenu,
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ChangeWorkno(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                workno: value,
                formWork: value == "NA",
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | SettingItemWorkno(
      workno,
      showXps,
      homepage1,
      pnumber,
      homepageMomo,
      momoitems,
      mb,
      mbitems,
      amount,
      index,
    ) => {
      ...state,
      formitems:
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
                momoitems,
                mb,
                mbitems,
                amount,
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
  | ShowMomoMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showMomoMenu: !item.showMomoMenu} : item,
          state.formitems,
        ),
    }
  | ClickMomoMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                homepageMomo: value,
                showMomoMenu: !item.showMomoMenu,
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ShowMbMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showMbMenu: !item.showMbMenu} : item,
          state.formitems,
        ),
    }
  | ClickMbMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                mb: value,
                showMbMenu: !item.showMbMenu,
                formModify: true,
              }
              : item,
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
  | ShowPn(showPn, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, showPn} : item,
          state.formitems,
        ),
    }
  | SettingItemPn(items, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, pnitems: items, showPn: true} : item,
          state.formitems,
        ),
    }
  | ChangePn(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, pn: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ClickItemPn(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, pn: value, showPn: !item.showPn, formModify: true}
              : item,
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
  | ChangeInvest(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                invest:
                  int_of_string(value) > int_of_string(item.amount)
                    ? "0" : value,
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ChangeFail(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                fail:
                  int_of_string(value) > int_of_string(item.invest)
                    ? "0" : value,
                formModify: true,
              }
              : item,
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
  | ChangeContainment(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, containment: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeCause(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, cause: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ShowRegroupMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showRegroupMenu: !item.showRegroupMenu} : item,
          state.formitems,
        ),
    }
  | ClickRegroupMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                reGroup: value,
                showRegroupMenu: !item.showRegroupMenu,
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ShowReplierMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showReplierMenu: !item.showReplierMenu} : item,
          state.formitems,
        ),
    }
  | SettingItemReplier(items, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, replieritems: items} : item,
          state.formitems,
        ),
    }
  | ClickReplierMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                replier: value,
                showReplierMenu: !item.showReplierMenu,
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ShowIssueMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showIssueMenu: !item.showIssueMenu} : item,
          state.formitems,
        ),
    }
  | ClickIssueMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                issuesort: value,
                showIssueMenu: !item.showIssueMenu,
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ShowCauseMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showCauseMenu: !item.showCauseMenu} : item,
          state.formitems,
        ),
    }
  | SettingItemCause(items, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, causeitems: items} : item,
          state.formitems,
        ),
    }
  | ClickCauseMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                causeclass: value,
                showCauseMenu: !item.showCauseMenu,
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ChangeDirectPt(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, directPt: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeIndirectPt(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, indirectPt: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeCorrectiveaction1(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, correctiveaction1: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ChangeCorrectiveaction2(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, correctiveaction2: value, formModify: true} : item,
          state.formitems,
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
      formitems:
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
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ChangeClosure(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, closure: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | SwitchNotice(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, notice: !item.notice, formModify: true} : item,
          state.formitems,
        ),
    }
  | SwitchNonstatistical(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                nonstatistical: !item.nonstatistical,
                formModify: true,
              }
              : item,
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
  | ShowBelongMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showBelongMenu: !item.showBelongMenu} : item,
          state.formitems,
        ),
    }
  | ClickBelongMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                belong: value,
                showBelongMenu: !item.showBelongMenu,
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ChangeBelonger(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, belonger: value, formModify: true} : item,
          state.formitems,
        ),
    }
  | ShowStageMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showStageMenu: !item.showStageMenu} : item,
          state.formitems,
        ),
    }
  | ClickStageMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                stage: value,
                showStageMenu: !item.showStageMenu,
                formModify: true,
              }
              : item,
          state.formitems,
        ),
    }
  | ChangeReleasedate(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => index == i ? {...item, releasedate: value} : item,
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
          newitem(
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
  | ClearAnimationFull(id) => {
      ...state,
      itemCount: state.itemCount - 1,
      items: Js_array.filter((item: item) => item.ids !== id, state.items),
      showFull: !state.showFull,
    }
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
  | SettingPhotoItem(id, tile, image, audio, video, path, src) => {
      ...state,
      photoId: id,
      photoTile: tile,
      photoImage: image,
      photoAudio: audio,
      photoVideo: video,
      photoPath: path,
      photoSrc: src,
      showPhotoFull: !state.showPhotoFull,
      showFull: !state.showFull,
    }
  | ClosePhotoFull => {...state, showPhotoFull: !state.showPhotoFull}
  | CloseAskFull => {...state, showAskDialog: !state.showAskDialog }
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
  firdate: "",
  secdate: "",
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
    {showTab: false, tabImage: collectionsBlack},
  ],
  index: 0,
  formitems: [||],
  showDrop: false,
  photoitems: [||],
  showFileFull: false,
  fileId: "",
  fileTile: "",
  filePath: "",
  fileSrc: "",
  showPhotoFull: false,
  photoId: "",
  photoTile: "",
  photoImage: false,
  photoAudio: false,
  photoVideo: false,
  photoPath: "",
  photoSrc: "",
  showAskDialog: false,
  showYoutube: false,
  youtubeText: "",
};

let defaultFloat = value =>
  switch (value) {
  | "" => "0.0"
  | _ => value
  };

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
      state.items
      |> Js_array.length
      |> string_of_int
      |> otherData("newid" |> Locals.select)
      |> Default.search
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
      |> Default.filter
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
      |> sDesoData(
           Js_array.filter(
             (filitem: filitem) => filitem.filtValue !== "",
             state.filitems,
           ),
           state.firdate,
           state.secdate,
           state.record,
           length,
         )
      |> Default.scroll
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
      state.items |> Js_array.length |> string_of_int |> scrollAJax;
    });

  let sRecordAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Default.sRecord
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

  let sFiltDateAJax = (firdate, secdate, record) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> sFidtData(firdate, secdate, record)
      |> Default.sFiltDate
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
        state.record |> sFiltDateAJax(state.firdate, state.secdate);
      }
    );

  let clickItemRecord =
    useCallback(value => {
      ClickItemRecord(value) |> dispatch;
      value |> sFiltDateAJax(state.firdate, state.secdate);
    });

  let changeFirDate =
    useCallback(value => {
      ChangeFirDate(value) |> dispatch;
      state.record |> sFiltDateAJax(value, state.secdate);
    });

  let changeSecDate =
    useCallback(value => {
      ChangeSecDate(value) |> dispatch;
      state.record |> sFiltDateAJax(state.firdate, value);
    });

  let exportForm =
    useCallback(_ =>
      "/Excel/exampleData?record="
      ++ state.record
      ++ "&firdate="
      ++ state.firdate
      ++ "&secdate="
      ++ state.secdate
      ++ "&items=[]&newid="
      ++ checkObjects("newid" |> Locals.select)
      |> Window.Locations.assign
    );

  let showMenu = useCallback(index => ShowMenu(index) |> dispatch);

  let sfilterAJax = (index, value) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> sDeftData(
           Js_array.filter(
             (filitem: filitem) => filitem.filtValue !== "",
             state.filitems,
           ),
           state.firdate,
           state.secdate,
           state.record,
           index,
           value,
         )
      |> Default.sFilter
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
               response##data##status |> statusModule |> barShowRestoreAction
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
      |> Default.sItem
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
      |> Default.clear
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

  let addAJax = (id, i) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(id)
      |> Default.add
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               SettingItem(i) |> dispatch;
               "saveSuccess" |> statusModule |> barShowRestoreAction;
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

  let addItem =
    useCallback((id, i, event) => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      i |> addAJax(id);
    });

  let removeAJax = (id, i) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(id)
      |> Default.remove
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               SettingItem(i) |> dispatch;
               "saveSuccess" |> statusModule |> barShowRestoreAction;
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

  let removeItem =
    useCallback((id, i, event) => {
      ReactEvent.Mouse.preventDefault(event);
      ReactEvent.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      i |> removeAJax(id);
    });

  let sFileAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Default.sFile
      |> then_(response =>
           SettingPhotoItems(response##data##items) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickItemTab =
    useCallback(i => {
      ClickItemTab(i) |> dispatch;
      if (i == 1) {
        sFileAJax();
      };
    });

  let clearAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Default.clear
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               ClearAnimationFull(state.formId) |> dispatch;
               "deleteSuccess" |> statusModule |> barShowRestoreAction;
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

  let clearForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      clearAJax();
    });

  let insertAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iFormsData(
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
         )
      |> Default.insert
      |> then_(response =>
           {
             switch (response##data##status) {
             | "isask" =>  
                CloseAnimationFull |> dispatch; 
                ActionShowProgress |> dispatch;
                CloseAskFull |> dispatch;
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

  let insertForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      insertAJax();
    });

  let sendAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iFormsData(
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
         )
      |> Default.send
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

  let showFloorMenu = useCallback(i => ShowFloorMenu(i) |> dispatch);

  let clickFloorMenu =
    useCallback((value, i) => ClickFloorMenu(value, i) |> dispatch);

  let changeWorkno =
    useCallback((value, i) => ChangeWorkno(value, i) |> dispatch);

  let sWorknoAJax = (value, i) =>
    Js.Promise.(
      value
      |> otherData("newid" |> Locals.select)
      |> CreateR.sWorkno
      |> then_(response =>
           SettingItemWorkno(
             response##data##items[0]##workno,
             response##data##items[0]##showxps,
             response##data##items[0]##custname,
             response##data##items[0]##pnumber,
             response##data##items[0]##mbname,
             response##data##items[0]##momoitems,
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
      |> CreateR.sXps
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
               response##data |> Js.log;
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

  let showMomoMenu = useCallback(i => ShowMomoMenu(i) |> dispatch);

  let clickMomoMenu =
    useCallback((value, i) => ClickMomoMenu(value, i) |> dispatch);

  let showMbMenu = useCallback(i => ShowMbMenu(i) |> dispatch);

  let clickMbMenu =
    useCallback((value, i) => ClickMbMenu(value, i) |> dispatch);

  let showObjMenu = useCallback(i => ShowObjMenu(i) |> dispatch);

  let clickObjMenu =
    useCallback((value, i) => ClickObjMenu(value, i) |> dispatch);

  let sPnAJax = (workno, value, i) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> sRowsData(workno, value)
      |> CreateR.sPn
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
      |> CreateR.sGroup
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
      |> CreateR.sIssus
      |> then_(response =>
           SettingItemCause(response##data##items, i) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickIssueMenu =
    useCallback((value, i) => {
      ClickIssueMenu(value, i) |> dispatch;
      sIssueAJax(value, i);
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

  let changeReleasedate =
    useCallback((value, i) => ChangeReleasedate(value, i) |> dispatch);

  let refreshAJax = (color, status) =>
    RefreshFormItem(color, status) |> dispatch;

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

  let downloadImage = useCallback(value => Window.Locations.href(value, "_blank"));

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
      |> CreateR.download
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

  let showPhotoFull = (image, audio, video, path, src) =>
    SettingPhotoItem(
      state.formId,
      state.formTitle,
      image,
      audio,
      video,
      path,
      src,
    )
    |> dispatch;

  let closePhotoFull =
    useCallback(_ => {
      CloseAnimationFull |> dispatch;
      ClosePhotoFull |> dispatch;
    });

  let stageAJax = () => 
    Js.Promise.(
      "newid" |> Locals.select
      |> dFormData(state.formId)
      |> Default.stage
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
                CloseAskFull |> dispatch;
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

  let stageForm = 
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      stageAJax();
    });

  let closeAskFull = useCallback(_ => CloseAskFull |> dispatch);

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
              <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                <TextFieldStandard
                  top="12"
                  labelColor="rgba(255,0,0,0.8)"
                  enterBorderColor="rgba(255,0,0,0.8)"
                  downBorderColor="rgba(255,0,0,0.6)"
                  borderColor="rgba(0,0,0,0.2)"
                  type_="date"
                  value={state.firdate}
                  disabled={state.showProgress}
                  onChange={event =>
                    ReactEvent.Form.target(event)##value |> changeFirDate
                  }>
                  <FormattedMessage
                    id="Default.firdate"
                    defaultMessage="Firdate"
                  />
                </TextFieldStandard>
              </GridItem>
              <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                <TextFieldStandard
                  top="12"
                  labelColor="rgba(255,0,0,0.8)"
                  enterBorderColor="rgba(255,0,0,0.8)"
                  downBorderColor="rgba(255,0,0,0.6)"
                  borderColor="rgba(0,0,0,0.2)"
                  type_="date"
                  value={state.secdate}
                  disabled={state.showProgress}
                  onChange={event =>
                    ReactEvent.Form.target(event)##value |> changeSecDate
                  }>
                  <FormattedMessage
                    id="Default.secdate"
                    defaultMessage="Secdate"
                  />
                </TextFieldStandard>
              </GridItem>
              <GridItem top="0" right="8" bottom="0" left="0" xs="no">
                <Button disabled={state.showProgress} onClick=exportForm>
                  <FormattedMessage id="export" defaultMessage="Export" />
                </Button>
              </GridItem>
            </GridContainer>
          </GridItem>
          <GridItem
            style={ReactDOMRe.Style.make(
              ~position="sticky",
              ~top="142px",
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
                            <Typography variant="tile" fontWeight="600">
                              {item.numbers |> string}
                            </Typography>
                          </GridItem>
                          {switch (item.itemPassed, item.itemPlused) {
                           | (true, true) =>
                             <GridItem
                               top="0"
                               bottom="0"
                               left="0"
                               enterBackgroundColor="none"
                               backgroundColor="none"
                               xs="no">
                               <IconButton
                                 padding="8"
                                 disabled={state.showProgress}
                                 onClick={event =>
                                   event |> removeItem(item.ids, i)
                                 }>
                                 <Tooltip
                                   location="bottom"
                                   backgroundColor="rgba(255,0,0,0.8)">
                                   <FormattedMessage
                                     id="Default.removePass"
                                     defaultMessage="RemovePass"
                                   />
                                 </Tooltip>
                                 <IconAction
                                   animation="circle"
                                   src=clearBlack
                                 />
                               </IconButton>
                             </GridItem>
                           | (true, false) =>
                             <GridItem
                               top="0"
                               bottom="0"
                               left="0"
                               enterBackgroundColor="none"
                               backgroundColor="none"
                               xs="no">
                               <IconButton
                                 padding="8"
                                 disabled={state.showProgress}
                                 onClick={event =>
                                   event |> addItem(item.ids, i)
                                 }>
                                 <Tooltip
                                   location="bottom"
                                   backgroundColor="rgba(255,0,0,0.8)">
                                   <FormattedMessage
                                     id="Default.addPass"
                                     defaultMessage="AddPass"
                                   />
                                 </Tooltip>
                                 <IconAction animation="circle" src=addBlack />
                               </IconButton>
                             </GridItem>
                           | (_, _) => null
                           }}
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
                        top="3"
                        left="14"
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <Typography variant="subheading">
                          {item.subjects |> string}
                        </Typography>
                      </GridItem>
                      <GridItem
                        top="0"
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
                            <Typography variant="subheading" color="#606060">
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
                            <Typography variant="subheading" color="#606060">
                              {item.postGroups |> string}
                            </Typography>
                          </GridItem>
                          <GridItem
                            top="0"
                            right="0"
                            bottom="0"
                            left="0"
                            enterBackgroundColor="none"
                            backgroundColor="none"
                            xs="auto">
                            <Typography variant="subheading" color="#606060">
                              {item.homepage1s |> string}
                            </Typography>
                          </GridItem>
                        </GridContainer>
                      </GridItem>
                      <GridItem
                        top="0"
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
                            <Typography variant="subheading" color="#606060">
                              {item.homepageMomos |> string}
                            </Typography>
                          </GridItem>
                          <GridItem
                            top="0"
                            bottom="0"
                            left="0"
                            enterBackgroundColor="none"
                            backgroundColor="none"
                            xs="no">
                            <Typography variant="subheading" color="#606060">
                              {item.mbs |> string}
                            </Typography>
                          </GridItem>
                          <GridItem
                            top="0"
                            right="0"
                            bottom="0"
                            left="0"
                            enterBackgroundColor="none"
                            backgroundColor="none"
                            xs="auto">
                            <Typography variant="subheading" color="#606060">
                              {item.fails |> string}
                            </Typography>
                          </GridItem>
                        </GridContainer>
                      </GridItem>
                      <GridItem
                        top="0"
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
                            <Typography variant="subheading" color="#606060">
                              {item.objs |> string}
                            </Typography>
                          </GridItem>
                          <GridItem
                            top="0"
                            bottom="0"
                            left="0"
                            enterBackgroundColor="none"
                            backgroundColor="none"
                            xs="no">
                            <Typography variant="subheading" color="#606060">
                              {item.worknumbers |> string}
                            </Typography>
                          </GridItem>
                          <GridItem
                            top="0"
                            right="0"
                            bottom="0"
                            left="0"
                            enterBackgroundColor="none"
                            backgroundColor="none"
                            xs="auto">
                            <Typography variant="subheading" color="#606060">
                              {item.repliers |> string}
                            </Typography>
                          </GridItem>
                        </GridContainer>
                      </GridItem>
                      <GridItem
                        top="0"
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
                            <Typography variant="subheading" color="#606060">
                              {item.issuesorts |> string}
                            </Typography>
                          </GridItem>
                          <GridItem
                            top="0"
                            right="0"
                            bottom="0"
                            left="0"
                            enterBackgroundColor="none"
                            backgroundColor="none"
                            xs="auto">
                            <Typography variant="subheading" color="#606060">
                              {item.belongs |> string}
                            </Typography>
                          </GridItem>
                        </GridContainer>
                      </GridItem>
                      <GridItem
                        top="0"
                        enterBackgroundColor="none"
                        backgroundColor="none"
                        xs="auto">
                        <Typography variant="subheading" color={item.colors}>
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
                  {state.formitems
                   |> Array.map(item =>
                        <>
                          {item.formDelete
                             ? <GridItem
                                 top="0" right="0" bottom="0" left="0" xs="no">
                                 <Button
                                   disabled={state.showProgress}
                                   onClick=clearForm>
                                   <FormattedMessage
                                     id="deleted"
                                     defaultMessage="Deleted"
                                   />
                                 </Button>
                               </GridItem>
                             : null}
                          {item.formEdit || item.formQuality
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
                             : null}
                          {item.formSend
                             ? <GridItem
                                 top="0" right="0" bottom="0" left="0" xs="no">
                                 <Button
                                   enterBackgroundColor="rgba(40,167,69,0.8)"
                                   downBackgroundColor="rgba(40,167,69,0.8)"
                                   backgroundColor="rgba(40,167,69,1)"
                                   disabled={state.showProgress}
                                   onClick=sendForm>
                                   <FormattedMessage
                                     id="send"
                                     defaultMessage="Send"
                                   />
                                 </Button>
                               </GridItem>
                             : null}
                        </>
                      )
                   |> array}
                </GridContainer>
              </GridItem>
              {switch (state.index) {
               | 0 =>
                 state.formitems
                 |> Array.mapi((i, item) =>
                      <>
                        <GridItem bottom="0" left="0" xs="auto">
                          <Typography
                            variant="subheading"
                            color="rgba(0,0,0,0.6)"
                            fontWeight="bolder">
                            {{js|【Characterize】問題描述|js} |> string}
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
                              <TextFieldStandard
                                top="12"
                                right="0"
                                left="0"
                                labelColor="rgba(255,0,0,0.8)"
                                enterBorderColor="rgba(255,0,0,0.8)"
                                downBorderColor="rgba(255,0,0,0.6)"
                                borderColor="rgba(0,0,0,0.2)"
                                value={item.postGroup}
                                disabled=true>
                                {{js|提出部門|js} |> string}
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
                                value={item.postName}
                                disabled=true>
                                {{js|提出者|js} |> string}
                              </TextFieldStandard>
                            </GridItem>
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
                                disabled={
                                  state.showProgress
                                  || !item.formEdit
                                  || !state.update
                                }
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
                              <GridContainer
                                direction="row"
                                justify="between"
                                alignItem="center">
                                <GridItem
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
                                    value={item.workno}
                                    disabled={
                                      state.showProgress
                                      || !item.formEdit
                                      || !state.update
                                    }
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
                                   ? <GridItem
                                       top="0"
                                       right="0"
                                       bottom="0"
                                       left="0"
                                       xs="no">
                                       <IconButton
                                         padding="2"
                                         disabled={state.showProgress}
                                         onClick={_ =>
                                           item.workno |> showXpsFile
                                         }>
                                         <IconAction
                                           animation="circle"
                                           src=visibilityBlack
                                         />
                                       </IconButton>
                                     </GridItem>
                                   : null}
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
                                value={item.homepage1}
                                disabled={
                                  state.showProgress
                                  || !item.formWork
                                  || !state.update
                                }
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
                                disabled={
                                  state.showProgress
                                  || !item.formWork
                                  || !state.update
                                }
                                onChange={event =>
                                  i
                                  |> changePnumber(
                                       ReactEvent.Form.target(event)##value,
                                     )
                                }>
                                {{js|產品規格單|js} |> string}
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
                                tile={js|機種|js}
                                labelColor="rgba(255,0,0,0.8)"
                                enterBorderColor="rgba(255,0,0,0.8)"
                                downBorderColor="rgba(255,0,0,0.6)"
                                borderColor="rgba(0,0,0,0.2)"
                                value={item.homepageMomo}
                                disabled={
                                  state.showProgress
                                  || !item.formWork
                                  || !state.update
                                }
                                onClick={_ => i |> showMomoMenu}>
                                ...(
                                     item.showMomoMenu
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
                                           {item.momoitems
                                            |> Array.map(momoitem =>
                                                 <MenuItem
                                                   top="0"
                                                   right="8"
                                                   bottom="0"
                                                   left="8"
                                                   disablePadding={
                                                                    momoitem.
                                                                    optionPadding
                                                                  }
                                                   topLeft="12"
                                                   topRight="12"
                                                   bottomRight="12"
                                                   bottomLeft="12"
                                                   onClick={_ =>
                                                     i
                                                     |> clickMomoMenu(
                                                          momoitem.value,
                                                        )
                                                   }>
                                                   {momoitem.value |> string}
                                                 </MenuItem>
                                               )
                                            |> array}
                                         </SelectMenu>
                                       : null,
                                     <IconGeneral
                                       animation={
                                         item.showMomoMenu |> topDownRorate
                                       }
                                       src=arrowDownBlack
                                     />,
                                   )
                              </SelectStandard>
                              <BackgroundBoard
                                showBackground={item.showMomoMenu}
                                backgroundColor="transparent"
                                onClick={_ => i |> showMomoMenu}
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
                                value={item.mb}
                                disabled={
                                  state.showProgress
                                  || !item.formEdit
                                  || !state.update
                                }
                                onClick={_ => i |> showMbMenu}>
                                ...(
                                     item.showMbMenu
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
                                           {item.mbitems
                                            |> Array.map(mbitem =>
                                                 <MenuItem
                                                   top="0"
                                                   right="8"
                                                   bottom="0"
                                                   left="8"
                                                   disablePadding={
                                                                    mbitem.
                                                                    optionPadding
                                                                  }
                                                   topLeft="12"
                                                   topRight="12"
                                                   bottomRight="12"
                                                   bottomLeft="12"
                                                   onClick={_ =>
                                                     i
                                                     |> clickMbMenu(
                                                          mbitem.value,
                                                        )
                                                   }>
                                                   {mbitem.value |> string}
                                                 </MenuItem>
                                               )
                                            |> array}
                                         </SelectMenu>
                                       : null,
                                     <IconGeneral
                                       animation={
                                         item.showMbMenu |> topDownRorate
                                       }
                                       src=arrowDownBlack
                                     />,
                                   )
                              </SelectStandard>
                              <BackgroundBoard
                                showBackground={item.showMbMenu}
                                backgroundColor="transparent"
                                onClick={_ => i |> showMbMenu}
                              />
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
                                disabled={
                                  state.showProgress
                                  || !item.formEdit
                                  || !state.update
                                }
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
                            value={item.pn}
                            disabled={
                              state.showProgress
                              || !item.formEdit
                              || !state.update
                            }
                            onChange={event =>
                              i
                              |> changePn(
                                   ReactEvent.Form.target(event)##value,
                                   item.workno,
                                 )
                            }>
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
                                type_="number"
                                value={item.amount}
                                disabled={
                                  state.showProgress
                                  || !item.formWork
                                  || !state.update
                                }
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
                                disabled={
                                  state.showProgress
                                  || !item.formQuality
                                  || !state.update
                                }
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
                                disabled={
                                  state.showProgress
                                  || !item.formQuality
                                  || !state.update
                                }
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
                              <Typography
                                variant="subheading" fontWeight="bolder">
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
                            disabled={
                              state.showProgress
                              || !item.formEdit
                              || !state.update
                            }
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
                              disabled={
                                state.showProgress
                                || !item.formQuality
                                || !state.update
                              }
                              onClick=chooseFile
                              onChange={event =>
                                i
                                |> changeOtherFile(
                                     ReactEvent.Form.target(event)##files[0],
                                   )
                              }
                              onDownload={_ => downloadImage(item.path ++ item.src)}
                            />
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
                                tile={js|處理部門|js}
                                labelColor="rgba(255,0,0,0.8)"
                                enterBorderColor="rgba(255,0,0,0.8)"
                                downBorderColor="rgba(255,0,0,0.6)"
                                borderColor="rgba(0,0,0,0.2)"
                                value={item.reGroup}
                                disabled={
                                  state.showProgress
                                  || !item.formQuality
                                  || !state.update
                                }
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
                                disabled={
                                  state.showProgress
                                  || !item.formQuality
                                  || !state.update
                                }
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
                                tile={js|原因分類|js}
                                labelColor="rgba(255,0,0,0.8)"
                                enterBorderColor="rgba(255,0,0,0.8)"
                                downBorderColor="rgba(255,0,0,0.6)"
                                borderColor="rgba(0,0,0,0.2)"
                                value={item.issuesort}
                                disabled={
                                  state.showProgress
                                  || !item.formQuality
                                  || !state.update
                                }
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
                                disabled={
                                  state.showProgress
                                  || !item.formQuality
                                  || !state.update
                                }
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
                                type_="number"
                                value={item.directPt}
                                disabled={
                                  state.showProgress
                                  || !item.formEdit
                                  || !state.update
                                }
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
                                disabled={
                                  state.showProgress
                                  || !item.formQuality
                                  || !state.update
                                }
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
                            value={item.containment}
                            disabled={
                              state.showProgress
                              || !item.formQuality
                              || !state.update
                            }
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
                            value={item.cause}
                            disabled={
                              state.showProgress
                              || !item.formQuality
                              || !state.update
                            }
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
                            {{js|【Corrective Action】改善對策|js}
                             |> string}
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
                            value={item.correctiveaction1}
                            disabled={
                              state.showProgress
                              || !item.formQuality
                              || !state.update
                            }
                            onChange={event =>
                              i
                              |> changeCorrectiveaction1(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            {"Short Term" |> string}
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
                            value={item.correctiveaction2}
                            disabled={
                              state.showProgress
                              || !item.formQuality
                              || !state.update
                            }
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
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <GridContainer
                            direction="row"
                            justify="center"
                            alignItem="center">
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="auto">
                              <Switch
                                right="0"
                                checked={item.notice}
                                circleColor={item.notice |> circle}
                                linearColor={item.notice |> linear}
                                fontColor={item.notice |> font}
                                disabled={
                                  state.showProgress
                                  || !item.formQuality
                                  || !state.update
                                }
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
                                disabled={
                                  state.showProgress
                                  || !item.formQuality
                                  || !state.update
                                }
                                onClick={_ => i |> switchNonstatistical}>
                                {{js|不列入統計資料|js} |> string}
                              </Switch>
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
                                disabled={
                                  state.showProgress
                                  || !item.formQuality
                                  || !state.update
                                }
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
                                disabled={
                                  state.showProgress
                                  || !item.formQuality
                                  || !state.update
                                }
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
                                tile={js|責任單位|js}
                                labelColor="rgba(255,0,0,0.8)"
                                enterBorderColor="rgba(255,0,0,0.8)"
                                downBorderColor="rgba(255,0,0,0.6)"
                                borderColor="rgba(0,0,0,0.2)"
                                value={item.belong}
                                disabled={
                                  state.showProgress
                                  || !item.formQuality
                                  || !state.update
                                }
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
                                disabled={
                                  state.showProgress
                                  || !item.formQuality
                                  || !state.update
                                }
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
                                disabled={
                                  state.showProgress
                                  || !item.formQuality
                                  || !state.update
                                }
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
                            <GridItem
                              top="20"
                              right="0"
                              bottom="0"
                              left="0"
                              xs="auto">
                              <Typography
                                variant="subheading" fontWeight="bolder">
                                {{js|結案日期:|js}
                                ++ item.releasedate
                                |> string}
                              </Typography>
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
            backgroundColor="transparent">
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
    <DialogFull
      showAnimation={state.showPhotoFull} backgroundColor="rgba(0,0,0,0.8)">
      <DialogTitle top="22" left="64" backgroundColor="transparent">
        <Typography
          variant="tile" color="rgba(255,255,255,1)" fontWeight="600">
          {state.photoTile |> string}
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
            backgroundColor="transparent">
            {switch (state.photoImage, state.photoAudio, state.photoVideo) {
             | (true, false, false) =>
               <Image
                 width="auto"
                 height="200px"
                 borderRadius="6"
                 src={state.photoPath ++ state.photoSrc}
               />
             | (false, true, false) =>
               <Media
                 width="auto"
                 height="200px"
                 borderRadius="6"
                 src={state.photoPath ++ state.photoSrc}
               />
             | (false, false, true) =>
               <Media
                 variant="audio"
                 borderRadius="6"
                 src={state.photoPath ++ state.photoSrc}
               />
             | (_, _, _) => null
             }}
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
            onClick=closePhotoFull>
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
    <DialogAnimationRight showAnimation={state.showAskDialog}> 
      <DialogTitle
        backgroundColor="rgba(255,0,0,1)" color="rgba(255,255,255,1)">
        {state.formTitle |> string}
      </DialogTitle>
      <DialogContent right="0" bottom="12" left="0">
        <DialogContentText>
          <GridItem top="30" right="25" left="25" xs="12">
           <FormattedMessage id="Default.askMessage" defaultMessage="AskMessage" />
          </GridItem>
        </DialogContentText>
      </DialogContent>
      <DialogActions top="0" right="16" bottom="12" left="16">
        <GridContainer
            direction="rowReverse" justify="start" alignItem="center">
            <GridItem top="0" bottom="0" xs="no">
              <Button disabled={state.showProgress} onClick=stageForm>
                <IconAction animation="circle" src=sendWhite />
                <FormattedMessage id="send" defaultMessage="Send" />
              </Button>
            </GridItem>
             <GridItem top="0" bottom="0" xs="no">
              <Button disabled={state.showProgress} onClick=closeAskFull>
                <IconAction animation="circle" src=clearWhite />
                <FormattedMessage id="closed" defaultMessage="Closed" />
              </Button>
            </GridItem>
        </GridContainer>
      </DialogActions>
    </DialogAnimationRight>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
