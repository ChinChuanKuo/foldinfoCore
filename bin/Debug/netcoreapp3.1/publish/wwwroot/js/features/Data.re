[@genType]
let userData = userid => {"userid": userid};
[@genType]
let loginData = (userid, password, longitude, latitude) => {
  "userid": userid,
  "password": password,
  "longitude": longitude,
  "latitude": latitude,
};
[@genType]
let otherData = (userid, values) => {"userid": userid, "values": values};
[@genType]
let signupData = (userid, password, username, birthday) => {
  "userid": userid,
  "password": password,
  "username": username,
  "birthday": birthday,
};
[@genType]
let iIconData = (items, qaitems, newid) => {
  "items": items,
  "qaitems": qaitems,
  "newid": newid,
};
[@genType]
let iSecuData = (externip, newid) => {"externip": externip, "newid": newid};
[@genType]
let iNotiData = (isbool, newid) => {"isbool": isbool, "newid": newid};
[@genType]
let sRowsData = (formId, value, newid) => {
  "formId": formId,
  "value": value,
  "newid": newid,
};
[@genType]
let dFormData = (formId, newid) => {"formId": formId, "newid": newid};
[@genType]
let iItemsData = (items, newid) => {"items": items, "newid": newid};
[@genType]
let iFileData = (formId, original, encryption, extension, newid) => {
  "formId": formId,
  "original": original,
  "encryption": encryption,
  "extension": extension,
  "newid": newid,
};
[@genType]
let iFormData = (formId, tile, items, newid) => {
  "formId": formId,
  "tile": tile,
  "items": items,
  "newid": newid,
};
[@genType]
let sFileData = (imagePath, original, encryption, extension, newid) => {
  "imagePath": imagePath,
  "original": original,
  "encryption": encryption,
  "extension": extension,
  "newid": newid,
};
[@genType]
let rFileData =
    (imagePath, original, encryption, extension, first, final, newid) => {
  "imagePath": imagePath,
  "original": original,
  "encryption": encryption,
  "extension": extension,
  "first": first,
  "final": final,
  "newid": newid,
};

[@genType]
let sDesoData = (items, stdate, endate, record, value, newid) => {
  "items": items,
  "stdate": stdate,
  "endate": endate,
  "record": record,
  "value": value,
  "newid": newid,
};
[@genType]
let sScroData = (items, record, value, newid) => {
  "items": items,
  "record": record,
  "value": value,
  "newid": newid,
};
[@genType]
let sFidtData = (firdate, secdate, record, newid) => {
  "firdate": firdate,
  "secdate": secdate,
  "record": record,
  "newid": newid,
};
[@genType]
let sDeftData = (items, firdate, secdate, record, index, value, newid) => {
  "items": items,
  "firdate": firdate,
  "secdate": secdate,
  "record": record,
  "index": index,
  "value": value,
  "newid": newid,
};
[@genType]
let sFiltData = (items, index, value, record, newid) => {
  "items": items,
  "index": index,
  "value": value,
  "record": record,
  "newid": newid,
};
/*[@genType]
  let sFtCoData = (items, value, newid) => {
    "items": items,
    "value": value,
    "newid": newid,
  };*/
[@genType]
let iFormsData = (formId, tile, items, qaitems, newid) => {
  "formId": formId,
  "tile": tile,
  "items": items,
  "qaitems": qaitems,
  "newid": newid,
};
[@genType]
let iSideData = (items, photoitems, grotoitems, newid) => {
  "items": items,
  "photoitems": photoitems,
  "grotoitems": grotoitems,
  "newid": newid,
};
[@genType]
let iSirmsData = (formId, tile, items, photoitems, grotoitems, newid) => {
  "formId": formId,
  "tile": tile,
  "items": items,
  "photoitems": photoitems,
  "grotoitems": grotoitems,
  "newid": newid,
};
