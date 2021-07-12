// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Axios from "bs-axios/src/axios.js";
import * as Axios$1 from "axios";

function checkNew(data) {
  return Axios$1.post("/Form/checkNewData", data);
}

function loginForm(data) {
  return Axios$1.post("/Form/loginFormData", data);
}

function badgeForm(data) {
  return Axios$1.post("/Form/badgeFormData", data, {
              timeout: 30000
            });
}

function permiss(data) {
  return Axios$1.post("/Form/permissData", data);
}

function record(data) {
  return Axios$1.post("/Form/recordData", data);
}

function addCord(data) {
  return Axios$1.post("/Form/addCordData", data);
}

function badge(data) {
  return Axios$1.post("/Form/badgeData", data);
}

var Form = {
  checkNew: checkNew,
  loginForm: loginForm,
  badgeForm: badgeForm,
  permiss: permiss,
  record: record,
  addCord: addCord,
  badge: badge
};

function checkUser(data) {
  return Axios$1.post("/Login/checkUserData", data);
}

function loginUser(data) {
  return Axios$1.post("/Login/loginUserData", data);
}

var Login = {
  checkUser: checkUser,
  loginUser: loginUser
};

function forgetUser(data) {
  return Axios$1.post("/Forget/forgetUserData", data);
}

var Forget = {
  forgetUser: forgetUser
};

function codeUser(data) {
  return Axios$1.post("/Code/codeUserData", data);
}

var Code = {
  codeUser: codeUser
};

function resendUser(data) {
  return Axios$1.post("/Resend/resendUserData", data);
}

var Resend = {
  resendUser: resendUser
};

function signupUser(data) {
  return Axios$1.post("/Signup/signupUserData", data);
}

var Signup = {
  signupUser: signupUser
};

function search(data) {
  return Axios$1.post("/Icon/searchData", data);
}

function insert(data) {
  return Axios$1.post("/Icon/insertData", data);
}

var Icon = {
  search: search,
  insert: insert
};

function add(data) {
  return Axios$1.post("/Option/addData", data);
}

var $$Option = {
  add: add
};

function upload(formData) {
  return Axios$1.post("/Files/uploadData", formData, {
              headers: Axios.$$Headers.fromObj({
                    "Content-Type": "multipart/form-data"
                  })
            });
}

function website(data) {
  return Axios$1.post("/Files/websiteData", data);
}

function download(data) {
  return Axios$1.post("/Files/downloadData", data);
}

function transfer(data) {
  return Axios$1.post("/Files/transferData", data);
}

function total(data) {
  return Axios$1.post("/Files/totalData", data);
}

function remove(data) {
  return Axios$1.post("/Files/removeData", data);
}

function review(data) {
  return Axios$1.post("/Files/reviewData", data);
}

var Files = {
  upload: upload,
  website: website,
  download: download,
  transfer: transfer,
  total: total,
  remove: remove,
  review: review
};

function search$1(data) {
  return Axios$1.post("/Home/searchData", data);
}

function filter(data) {
  return Axios$1.post("/Home/filterData", data);
}

function scroll(data) {
  return Axios$1.post("/Home/scrollData", data);
}

function sRecord(data) {
  return Axios$1.post("/Home/sRecordData", data);
}

function sFiltDate(data) {
  return Axios$1.post("/Home/sFiltDateData", data);
}

function sFilter(data) {
  return Axios$1.post("/Home/sFilterData", data);
}

function clear(data) {
  return Axios$1.post("/Home/clearData", data);
}

function add$1(data) {
  return Axios$1.post("/Home/addData", data);
}

function remove$1(data) {
  return Axios$1.post("/Home/removeData", data);
}

function sItem(data) {
  return Axios$1.post("/Home/sItemData", data);
}

function sFile(data) {
  return Axios$1.post("/Home/sFileData", data);
}

function close(data) {
  return Axios$1.post("/Home/closeData", data);
}

function insert$1(data) {
  return Axios$1.post("/Home/insertData", data);
}

function send(data) {
  return Axios$1.post("/Home/sendData", data);
}

function stage(data) {
  return Axios$1.post("/Home/stageData", data);
}

var Default = {
  search: search$1,
  filter: filter,
  scroll: scroll,
  sRecord: sRecord,
  sFiltDate: sFiltDate,
  sFilter: sFilter,
  clear: clear,
  add: add$1,
  remove: remove$1,
  sItem: sItem,
  sFile: sFile,
  close: close,
  insert: insert$1,
  send: send,
  stage: stage
};

function search$2(data) {
  return Axios$1.post("/Inside/searchData", data);
}

function filter$1(data) {
  return Axios$1.post("/Inside/filterData", data);
}

function scroll$1(data) {
  return Axios$1.post("/Inside/scrollData", data);
}

function sRecord$1(data) {
  return Axios$1.post("/Inside/sRecordData", data);
}

function sFiltCord(data) {
  return Axios$1.post("/Inside/sFiltCordData", data);
}

function sFilter$1(data) {
  return Axios$1.post("/Inside/sFilterData", data);
}

function clear$1(data) {
  return Axios$1.post("/Inside/clearData", data);
}

function sItem$1(data) {
  return Axios$1.post("/Inside/sItemData", data);
}

function sFile$1(data) {
  return Axios$1.post("/Inside/sFileData", data);
}

function sGroto(data) {
  return Axios$1.post("/Inside/sGrotoData", data);
}

function sAction(data) {
  return Axios$1.post("/Inside/sActionData", data);
}

function insert$2(data) {
  return Axios$1.post("/Inside/insertData", data);
}

function send$1(data) {
  return Axios$1.post("/Inside/sendData", data);
}

var Inside = {
  search: search$2,
  filter: filter$1,
  scroll: scroll$1,
  sRecord: sRecord$1,
  sFiltCord: sFiltCord,
  sFilter: sFilter$1,
  clear: clear$1,
  sItem: sItem$1,
  sFile: sFile$1,
  sGroto: sGroto,
  sAction: sAction,
  insert: insert$2,
  send: send$1
};

function search$3(data) {
  return Axios$1.post("/IsoFile/searchData", data);
}

function filter$2(data) {
  return Axios$1.post("/IsoFile/filterData", data);
}

function scroll$2(data) {
  return Axios$1.post("/IsoFile/scrollData", data);
}

function sRecord$2(data) {
  return Axios$1.post("/IsoFile/sRecordData", data);
}

function sFiltCord$1(data) {
  return Axios$1.post("/IsoFile/sFiltCordData", data);
}

function sFilter$2(data) {
  return Axios$1.post("/IsoFile/sFilterData", data);
}

function clear$2(data) {
  return Axios$1.post("/IsoFile/clearData", data);
}

function sList(data) {
  return Axios$1.post("/IsoFile/sListData", data);
}

function previous(data) {
  return Axios$1.post("/IsoFile/previousData", data);
}

function next(data) {
  return Axios$1.post("/IsoFile/nextData", data);
}

function sItem$2(data) {
  return Axios$1.post("/IsoFile/sItemData", data);
}

function $$delete(data) {
  return Axios$1.post("/IsoFile/deleteData", data);
}

function order(data) {
  return Axios$1.post("/IsoFile/orderData", data);
}

function insert$3(data) {
  return Axios$1.post("/IsoFile/insertData", data);
}

function send$2(data) {
  return Axios$1.post("/IsoFile/sendData", data);
}

var IsoFile = {
  search: search$3,
  filter: filter$2,
  scroll: scroll$2,
  sRecord: sRecord$2,
  sFiltCord: sFiltCord$1,
  sFilter: sFilter$2,
  clear: clear$2,
  sList: sList,
  previous: previous,
  next: next,
  sItem: sItem$2,
  $$delete: $$delete,
  order: order,
  insert: insert$3,
  send: send$2
};

function search$4(data) {
  return Axios$1.post("/Product/searchData", data);
}

function filter$3(data) {
  return Axios$1.post("/Product/filterData", data);
}

function scroll$3(data) {
  return Axios$1.post("/Product/scrollData", data);
}

function sRecord$3(data) {
  return Axios$1.post("/Product/sRecordData", data);
}

function sFiltCord$2(data) {
  return Axios$1.post("/Product/sFiltCordData", data);
}

function sFilter$3(data) {
  return Axios$1.post("/Product/sFilterData", data);
}

function clear$3(data) {
  return Axios$1.post("/Product/clearData", data);
}

function sItem$3(data) {
  return Axios$1.post("/Product/sItemData", data);
}

function insert$4(data) {
  return Axios$1.post("/Product/insertData", data);
}

var Product = {
  search: search$4,
  filter: filter$3,
  scroll: scroll$3,
  sRecord: sRecord$3,
  sFiltCord: sFiltCord$2,
  sFilter: sFilter$3,
  clear: clear$3,
  sItem: sItem$3,
  insert: insert$4
};

function search$5(data) {
  return Axios$1.post("/CreateR/searchData", data);
}

function sGroup(data) {
  return Axios$1.post("/CreateR/sGroupData", data);
}

function sWorkno(data) {
  return Axios$1.post("/CreateR/sWorknoData", data);
}

function sXps(data) {
  return Axios$1.post("/CreateR/sXpsData", data);
}

function sPn(data) {
  return Axios$1.post("/CreateR/sPnData", data);
}

function sIssus(data) {
  return Axios$1.post("/CreateR/sIssusData", data);
}

function iPhoto(data) {
  return Axios$1.post("/CreateR/iPhotoData", data);
}

function insert$5(data) {
  return Axios$1.post("/CreateR/insertData", data);
}

function send$3(data) {
  return Axios$1.post("/CreateR/sendData", data);
}

function download$1(data) {
  return Axios$1.post("/CreateR/downloadData", data);
}

var CreateR = {
  search: search$5,
  sGroup: sGroup,
  sWorkno: sWorkno,
  sXps: sXps,
  sPn: sPn,
  sIssus: sIssus,
  iPhoto: iPhoto,
  insert: insert$5,
  send: send$3,
  download: download$1
};

function search$6(data) {
  return Axios$1.post("/CreateF/searchData", data);
}

function sSnno(data) {
  return Axios$1.post("/CreateF/sSnnoData", data);
}

function sGroup$1(data) {
  return Axios$1.post("/CreateF/sGroupData", data);
}

function sType(data) {
  return Axios$1.post("/CreateF/sTypeData", data);
}

function sMail(data) {
  return Axios$1.post("/CreateF/sMailData", data);
}

function sWorkno$1(data) {
  return Axios$1.post("/CreateF/sWorknoData", data);
}

function cWorkno(data) {
  return Axios$1.post("/CreateF/cWorknoData", data);
}

function sXps$1(data) {
  return Axios$1.post("/CreateF/sXpsData", data);
}

function sEcrno(data) {
  return Axios$1.post("/CreateF/sEcrnoData", data);
}

function sModel(data) {
  return Axios$1.post("/CreateF/sModelData", data);
}

function cGroto(data) {
  return Axios$1.post("/CreateF/cGrotoData", data);
}

function insert$6(data) {
  return Axios$1.post("/CreateF/insertData", data);
}

function send$4(data) {
  return Axios$1.post("/CreateF/sendData", data);
}

function download$2(data) {
  return Axios$1.post("/CreateF/downloadData", data);
}

var CreateF = {
  search: search$6,
  sSnno: sSnno,
  sGroup: sGroup$1,
  sType: sType,
  sMail: sMail,
  sWorkno: sWorkno$1,
  cWorkno: cWorkno,
  sXps: sXps$1,
  sEcrno: sEcrno,
  sModel: sModel,
  cGroto: cGroto,
  insert: insert$6,
  send: send$4,
  download: download$2
};

function search$7(data) {
  return Axios$1.post("/CreateI/searchData", data);
}

function sGroup$2(data) {
  return Axios$1.post("/CreateI/sGroupData", data);
}

function sModel$1(data) {
  return Axios$1.post("/CreateI/sModelData", data);
}

function sCustom(data) {
  return Axios$1.post("/CreateI/sCustomData", data);
}

function cCustom(data) {
  return Axios$1.post("/CreateI/cCustomData", data);
}

function insert$7(data) {
  return Axios$1.post("/CreateI/insertData", data);
}

function send$5(data) {
  return Axios$1.post("/CreateI/sendData", data);
}

var CreateI = {
  search: search$7,
  sGroup: sGroup$2,
  sModel: sModel$1,
  sCustom: sCustom,
  cCustom: cCustom,
  insert: insert$7,
  send: send$5
};

function search$8(data) {
  return Axios$1.post("/CreateP/searchData", data);
}

function sGroup$3(data) {
  return Axios$1.post("/CreateP/sGroupData", data);
}

function sModel$2(data) {
  return Axios$1.post("/CreateP/sModelData", data);
}

function sCustom$1(data) {
  return Axios$1.post("/CreateP/sCustomData", data);
}

function cCustom$1(data) {
  return Axios$1.post("/CreateP/cCustomData", data);
}

function insert$8(data) {
  return Axios$1.post("/CreateP/insertData", data);
}

var CreateP = {
  search: search$8,
  sGroup: sGroup$3,
  sModel: sModel$2,
  sCustom: sCustom$1,
  cCustom: cCustom$1,
  insert: insert$8
};

function search$9(data) {
  return Axios$1.post("/Signlist/searchData", data);
}

var Signlist = {
  search: search$9
};

function search$10(data) {
  return Axios$1.post("/SignlistR/searchData", data);
}

function sFile$2(data) {
  return Axios$1.post("/SignlistR/sFileData", data);
}

function send$6(data) {
  return Axios$1.post("/SignlistR/sendData", data);
}

function back(data) {
  return Axios$1.post("/SignlistR/backData", data);
}

var SignlistR = {
  search: search$10,
  sFile: sFile$2,
  send: send$6,
  back: back
};

function search$11(data) {
  return Axios$1.post("/SignlistF/searchData", data);
}

function sFile$3(data) {
  return Axios$1.post("/SignlistF/sFileData", data);
}

function sGroto$1(data) {
  return Axios$1.post("/SignlistF/sGrotoData", data);
}

function send$7(data) {
  return Axios$1.post("/SignlistF/sendData", data);
}

function back$1(data) {
  return Axios$1.post("/SignlistF/backData", data);
}

var SignlistF = {
  search: search$11,
  sFile: sFile$3,
  sGroto: sGroto$1,
  send: send$7,
  back: back$1
};

function search$12(data) {
  return Axios$1.post("/SignlistI/searchData", data);
}

function send$8(data) {
  return Axios$1.post("/SignlistI/sendData", data);
}

function back$2(data) {
  return Axios$1.post("/SignlistI/backData", data);
}

var SignlistI = {
  search: search$12,
  send: send$8,
  back: back$2
};

function search$13(data) {
  return Axios$1.post("/MailistR/searchData", data);
}

function sItem$4(data) {
  return Axios$1.post("/MailistR/sItemData", data);
}

function insert$9(data) {
  return Axios$1.post("/MailistR/insertData", data);
}

var MailistR = {
  search: search$13,
  sItem: sItem$4,
  insert: insert$9
};

function search$14(data) {
  return Axios$1.post("/MailistF/searchData", data);
}

function sItem$5(data) {
  return Axios$1.post("/MailistF/sItemData", data);
}

function insert$10(data) {
  return Axios$1.post("/MailistF/insertData", data);
}

var MailistF = {
  search: search$14,
  sItem: sItem$5,
  insert: insert$10
};

function search$15(data) {
  return Axios$1.post("/MailistI/searchData", data);
}

function sItem$6(data) {
  return Axios$1.post("/MailistI/sItemData", data);
}

function insert$11(data) {
  return Axios$1.post("/MailistI/insertData", data);
}

var MailistI = {
  search: search$15,
  sItem: sItem$6,
  insert: insert$11
};

function search$16(data) {
  return Axios$1.post("/SendistF/searchData", data);
}

function sGroup$4(data) {
  return Axios$1.post("/SendistF/sGroupData", data);
}

function insert$12(data) {
  return Axios$1.post("/SendistF/insertData", data);
}

var SendistF = {
  search: search$16,
  sGroup: sGroup$4,
  insert: insert$12
};

function search$17(data) {
  return Axios$1.post("/SendistR/searchData", data);
}

function add$2(data) {
  return Axios$1.post("/SendistR/addData", data);
}

function sGroup$5(data) {
  return Axios$1.post("/SendistR/sGroupData", data);
}

function insert$13(data) {
  return Axios$1.post("/SendistR/insertData", data);
}

var SendistR = {
  search: search$17,
  add: add$2,
  sGroup: sGroup$5,
  insert: insert$13
};

export {
  Form ,
  Login ,
  Forget ,
  Code ,
  Resend ,
  Signup ,
  Icon ,
  $$Option ,
  Files ,
  Default ,
  Inside ,
  IsoFile ,
  Product ,
  CreateR ,
  CreateF ,
  CreateI ,
  CreateP ,
  Signlist ,
  SignlistR ,
  SignlistF ,
  SignlistI ,
  MailistR ,
  MailistF ,
  MailistI ,
  SendistF ,
  SendistR ,
  
}
/* axios Not a pure module */
