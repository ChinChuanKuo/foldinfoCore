[@genType]
let statusModule = status =>
  switch (status) {
  | "nodata" => "undefined about database"
  | "islock" => "can not use information"
  | "errorFormLogin" => "if want used features, you need login"
  | "errorFormLength" => "the field column is to long"
  | "errorSearch" => "sorry, you can not search information"
  | "deleteSuccess" => "delete item successfully"
  | "saveSuccess" => "this form save successfully"
  | "sendSuccess" => "this form Send successfully"
  | _ => status
  };
[@genType]
let accountModule = account =>
  switch (account) {
  | "nodata" => "undefined about database"
  | "islock" => "can not use information"
  | "resend" => "please find your mails"
  | "errorCode" => "please enter your verification code"
  | "errorForget" => "please enter your birthday"
  | "errorUserid" => "please enter your userid"
  | "errorPassword" => "please enter your password"
  | "errorDifPassword" => "please enter same password"
  | "errorResend" => "please enter your first & Second password"
  | "errorUsername" => "please enter your username"
  | "errorBirthday" => "please enter your birthday"
  | "errorEmail" => "please enter your email"
  | _ => account
  };
[@genType]
let uploadModels = upload =>
  switch (upload) {
  | "failed" => "sorry, this file uplaod failed"
  | "success" => "congratulations, this file upload successfully"
  | _ => upload
  };
[@genType]
let downloadModels = download =>
  switch (download) {
  | "nodata" => "sorry, this file undefined"
  | "success" => "congratulations, this file download successfully"
  | _ => download
  };
[@genType]
let permissModels = permiss =>
  switch (permiss) {
  | "errorInsert" => "sorry, you can not insert information"
  | "errorUpdate" => "sorry, you can not update information"
  | "errorDelete" => "sorry, you can not delete information"
  | "errorExport" => "sorry, you can not export information"
  | _ => permiss
  };

[@genType]
let signModels = sign =>
  switch (sign) {
  | "signInSuccess" => "this form sign in successfully"
  | "signOutSuccess" => "this form sign out successfully"
  | _ => sign
  };
