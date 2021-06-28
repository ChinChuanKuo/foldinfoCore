open Axios;
module Form = {
  let checkNew = data => postData("/Form/checkNewData", data);
  let loginForm = data => postData("/Form/loginFormData", data);
  let badgeForm = data =>
    postDatac("/Form/badgeFormData", data, makeConfig(~timeout=30000, ()));
  let permiss = data => postData("/Form/permissData", data);
  let record = data => postData("/Form/recordData", data);
  let addCord = data => postData("/Form/addCordData", data);
  let badge = data => postData("/Form/badgeData", data);
};

module Login = {
  let checkUser = data => postData("/Login/checkUserData", data);
  let loginUser = data => postData("/Login/loginUserData", data);
};

module Forget = {
  let forgetUser = data => postData("/Forget/forgetUserData", data);
};

module Code = {
  let codeUser = data => postData("/Code/codeUserData", data);
};

module Resend = {
  let resendUser = data => postData("/Resend/resendUserData", data);
};

module Signup = {
  let signupUser = data => postData("/Signup/signupUserData", data);
};

module Icon = {
  let search = data => postData("/Icon/searchData", data);
  let insert = data => postData("/Icon/insertData", data);
};

module Option = {
  let add = data => postData("/Option/addData", data);
};

module Files = {
  let upload = formData =>
    postDatac(
      "/Files/uploadData",
      formData,
      makeConfig(
        ~headers=Headers.fromObj({"Content-Type": "multipart/form-data"}),
        (),
      ),
    );
  let website = data => postData("/Files/websiteData", data);
  let download = data => postData("/Files/downloadData", data);
  let transfer = data => postData("/Files/transferData", data);
  let total = data => postData("/Files/totalData", data);
  let remove = data => postData("/Files/removeData", data);
  let review = data => postData("/Files/reviewData", data);
};

module Default = {
  let search = data => postData("/Home/searchData", data);
  let filter = data => postData("/Home/filterData", data);
  let scroll = data => postData("/Home/scrollData", data);
  let sRecord = data => postData("/Home/sRecordData", data);
  let sFiltDate = data => postData("/Home/sFiltDateData", data);
  let sFilter = data => postData("/Home/sFilterData", data);
  let clear = data => postData("/Home/clearData", data);
  let add = data => postData("/Home/addData", data);
  let remove = data => postData("/Home/removeData", data);
  let sItem = data => postData("/Home/sItemData", data);
  let sFile = data => postData("/Home/sFileData", data);
  let close = data => postData("/Home/closeData", data);
  let insert = data => postData("/Home/insertData", data);
  let send = data => postData("/Home/sendData", data);
  let stage = data => postData("/Home/stageData", data);
};

module Inside = {
  let search = data => postData("/Inside/searchData", data);
  let filter = data => postData("/Inside/filterData", data);
  let scroll = data => postData("/Inside/scrollData", data);
  let sRecord = data => postData("/Inside/sRecordData", data);
  let sFiltCord = data => postData("/Inside/sFiltCordData", data);
  let sFilter = data => postData("/Inside/sFilterData", data);
  let clear = data => postData("/Inside/clearData", data);
  let sItem = data => postData("/Inside/sItemData", data);
  let sFile = data => postData("/Inside/sFileData", data);
  let sGroto = data => postData("/Inside/sGrotoData", data);
  let sAction = data => postData("/Inside/sActionData", data);
  let insert = data => postData("/Inside/insertData", data);
  let send = data => postData("/Inside/sendData", data);
};

module IsoFile = {
  let search = data => postData("/IsoFile/searchData", data);
  let filter = data => postData("/IsoFile/filterData", data);
  let scroll = data => postData("/IsoFile/scrollData", data);
  let sRecord = data => postData("/IsoFile/sRecordData", data);
  let sFiltCord = data => postData("/IsoFile/sFiltCordData", data);
  let sFilter = data => postData("/IsoFile/sFilterData", data);
  let clear = data => postData("/IsoFile/clearData", data);
  let sList = data => postData("/IsoFile/sListData", data);
  let previous = data => postData("/IsoFile/previousData", data);
  let next = data => postData("/IsoFile/nextData", data);
  let sItem = data => postData("/IsoFile/sItemData", data);
  let delete = data => postData("/IsoFile/deleteData", data);
  let order = data => postData("/IsoFile/orderData", data);
  let insert = data => postData("/IsoFile/insertData", data);
  let send = data => postData("/IsoFile/sendData", data);
};

module Product = {
  let search = data => postData("/Product/searchData", data);
  let filter = data => postData("/Product/filterData", data);
  let scroll = data => postData("/Product/scrollData", data);
  let sRecord = data => postData("/Product/sRecordData", data);
  let sFiltCord = data => postData("/Product/sFiltCordData", data);
  let sFilter = data => postData("/Product/sFilterData", data);
  let clear = data => postData("/Product/clearData", data);
  let sItem = data => postData("/Product/sItemData", data);
  let insert = data => postData("/Product/insertData", data);
};

module CreateR = {
  let search = data => postData("/CreateR/searchData", data);
  let sGroup = data => postData("/CreateR/sGroupData", data);
  let sWorkno = data => postData("/CreateR/sWorknoData", data);
  let sXps = data => postData("/CreateR/sXpsData", data);
  let sPn = data => postData("/CreateR/sPnData", data);
  let sIssus = data => postData("/CreateR/sIssusData", data);
  let iPhoto = data => postData("/CreateR/iPhotoData", data);
  let insert = data => postData("/CreateR/insertData", data);
  let send = data => postData("/CreateR/sendData", data);
  let download = data => postData("/CreateR/downloadData", data);
};

module CreateF = {
  let search = data => postData("/CreateF/searchData", data);
  let sSnno = data => postData("/CreateF/sSnnoData", data);
  let sGroup = data => postData("/CreateF/sGroupData", data);
  let sType = data => postData("/CreateF/sTypeData", data);
  let sMail = data => postData("/CreateF/sMailData", data);
  let sWorkno = data => postData("/CreateF/sWorknoData", data);
  let cWorkno = data => postData("/CreateF/cWorknoData", data);
  let sXps = data => postData("/CreateF/sXpsData", data);
  let sEcrno = data => postData("/CreateF/sEcrnoData", data);
  let sModel = data => postData("/CreateF/sModelData", data);
  let cGroto = data => postData("/CreateF/cGrotoData", data);
  let insert = data => postData("/CreateF/insertData", data);
  let send = data => postData("/CreateF/sendData", data);
  let download = data => postData("/CreateF/downloadData", data);
};

module CreateI = {
  let search = data => postData("/CreateI/searchData", data);
  let sGroup = data => postData("/CreateI/sGroupData", data);
  let sModel = data => postData("/CreateI/sModelData", data);
  let sCustom = data => postData("/CreateI/sCustomData", data);
  let cCustom = data => postData("/CreateI/cCustomData", data);
  let insert = data => postData("/CreateI/insertData", data);
  let send = data => postData("/CreateI/sendData", data);
};

module CreateP = {
  let search = data => postData("/CreateP/searchData", data);
  let sGroup = data => postData("/CreateP/sGroupData", data);
  let sModel = data => postData("/CreateP/sModelData", data);
  let sCustom = data => postData("/CreateP/sCustomData", data);
  let cCustom = data => postData("/CreateP/cCustomData", data);
  let insert = data => postData("/CreateP/insertData", data);
};

module Signlist = {
  let search = data => postData("/Signlist/searchData", data);
};

module SignlistR = {
  let search = data => postData("/SignlistR/searchData", data);
  let sFile = data => postData("/SignlistR/sFileData", data);
  let send = data => postData("/SignlistR/sendData", data);
  let back = data => postData("/SignlistR/backData", data);
};

module SignlistF = {
  let search = data => postData("/SignlistF/searchData", data);
  let sFile = data => postData("/SignlistF/sFileData", data);
  let sGroto = data => postData("/SignlistF/sGrotoData", data);
  let send = data => postData("/SignlistF/sendData", data);
  let back = data => postData("/SignlistF/backData", data);
};

module SignlistI = {
  let search = data => postData("/SignlistI/searchData", data);
  let send = data => postData("/SignlistI/sendData", data);
  let back = data => postData("/SignlistI/backData", data);
};

module MailistR = {
  let search = data => postData("/MailistR/searchData", data);
  let sItem = data => postData("/MailistR/sItemData", data);
  let insert = data => postData("/MailistR/insertData", data);
};

module MailistF = {
  let search = data => postData("/MailistF/searchData", data);
  let sItem = data => postData("/MailistF/sItemData", data);
  let insert = data => postData("/MailistF/insertData", data);
};

module MailistI = {
  let search = data => postData("/MailistI/searchData", data);
  let sItem = data => postData("/MailistI/sItemData", data);
  let insert = data => postData("/MailistI/insertData", data);
};

module SendistF = {
  let search = data => postData("/SendistF/searchData", data);
  let sGroup = data => postData("/SendistF/sGroupData", data);
  let insert = data => postData("/SendistF/insertData", data);
};
