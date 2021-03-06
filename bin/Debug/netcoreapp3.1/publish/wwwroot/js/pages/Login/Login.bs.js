// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Block from "bs-platform/lib/es6/block.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Data$BtsCore from "../../features/Data.bs.js";
import * as Path$BtsCore from "../../features/Path.bs.js";
import * as Basic$BtsCore from "../../setting/Basic.bs.js";
import * as Status$BtsCore from "../../features/Status.bs.js";
import * as Axiosapi$BtsCore from "../../features/Axiosapi.bs.js";
import * as ReasonReactRouter from "reason-react/src/ReasonReactRouter.bs.js";
import * as ObjectFormat$BtsCore from "../../controls/ObjectFormat.bs.js";
import * as YoutubeLogin$BtsCore from "../../example/Account/Login/YoutubeLogin.bs.js";

function reducer(state, action) {
  switch (action.tag | 0) {
    case /* SettingUserId */0 :
        return {
                formLoad: !state.formLoad,
                error: state.error,
                loading: state.loading,
                showYoutube: state.showYoutube,
                youtubeText: state.youtubeText,
                disabled: state.disabled,
                userid: action[0],
                password: state.password
              };
    case /* ChangeUserId */1 :
        return {
                formLoad: state.formLoad,
                error: state.error,
                loading: state.loading,
                showYoutube: state.showYoutube,
                youtubeText: state.youtubeText,
                disabled: state.disabled,
                userid: action[0],
                password: state.password
              };
    case /* ChangePassword */2 :
        return {
                formLoad: state.formLoad,
                error: state.error,
                loading: state.loading,
                showYoutube: state.showYoutube,
                youtubeText: state.youtubeText,
                disabled: state.disabled,
                userid: state.userid,
                password: action[0]
              };
    case /* ActionOtherLoad */3 :
        var other = action[0];
        return {
                formLoad: state.formLoad,
                error: state.error,
                loading: other,
                showYoutube: state.showYoutube,
                youtubeText: state.youtubeText,
                disabled: other,
                userid: state.userid,
                password: state.password
              };
    case /* ActionErrorLoad */4 :
        return {
                formLoad: state.formLoad,
                error: action[0],
                loading: state.loading,
                showYoutube: state.showYoutube,
                youtubeText: state.youtubeText,
                disabled: state.disabled,
                userid: state.userid,
                password: state.password
              };
    case /* ActionSnackBar */5 :
        return {
                formLoad: state.formLoad,
                error: state.error,
                loading: state.loading,
                showYoutube: action[1],
                youtubeText: action[0],
                disabled: state.disabled,
                userid: state.userid,
                password: state.password
              };
    
  }
}

var initialState = {
  formLoad: false,
  error: false,
  loading: false,
  showYoutube: false,
  youtubeText: "",
  disabled: false,
  userid: "",
  password: ""
};

function autoLoginPath(value) {
  if (value === "") {
    return "/";
  } else {
    return value;
  }
}

function Login(Props) {
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
  React.useEffect((function () {
          if (state.formLoad) {
            return (function (param) {
                      console.log("action");
                      
                    });
          }
          Curry._1(dispatch, /* SettingUserId */Block.__(0, [ObjectFormat$BtsCore.checkObjects(sessionStorage.getItem("userid"))]));
          navigator.geolocation.getCurrentPosition(Basic$BtsCore.$$Location.success, Basic$BtsCore.$$Location.error, Basic$BtsCore.$$Location.items);
          return (function (param) {
                    
                  });
        }));
  var changeUserid = React.useCallback((function (value) {
          Curry._1(dispatch, /* ChangeUserId */Block.__(1, [value]));
          sessionStorage.setItem("userid", value);
          
        }));
  var changePassword = React.useCallback((function (value) {
          return Curry._1(dispatch, /* ChangePassword */Block.__(2, [value]));
        }));
  var restoreAction = function (param) {
    Curry._1(dispatch, /* ActionErrorLoad */Block.__(4, [true]));
    setTimeout((function (param) {
            Curry._1(dispatch, /* ActionErrorLoad */Block.__(4, [false]));
            return Curry._1(dispatch, /* ActionOtherLoad */Block.__(3, [false]));
          }), 500);
    
  };
  var barShowRestoreAction = function (youtubeText) {
    Curry._1(dispatch, /* ActionSnackBar */Block.__(5, [
            youtubeText,
            true
          ]));
    setTimeout((function (param) {
            return Curry._1(dispatch, /* ActionSnackBar */Block.__(5, [
                          "",
                          false
                        ]));
          }), 5000);
    
  };
  var forgetForm = React.useCallback((function (param) {
          Curry._1(dispatch, /* ActionOtherLoad */Block.__(3, [true]));
          Axiosapi$BtsCore.Login.checkUser(Data$BtsCore.userData(state.userid)).then((function (response) {
                    var match = response.data.status;
                    var tmp;
                    if (match === "istrue") {
                      sessionStorage.setItem("newid", response.data.newid);
                      tmp = ReasonReactRouter.push(Path$BtsCore.forgetPath);
                    } else {
                      restoreAction(undefined);
                      tmp = barShowRestoreAction(Status$BtsCore.accountModule(response.data.status));
                    }
                    return Promise.resolve(tmp);
                  })).catch((function (error) {
                  return Promise.resolve((console.log(error), undefined));
                }));
          
        }));
  var loginUserAJax = function (param) {
    Axiosapi$BtsCore.Login.loginUser(Data$BtsCore.loginData(state.userid, state.password, localStorage.getItem("longitude"), localStorage.getItem("latitude"))).then((function (response) {
              var match = response.data.status;
              var tmp;
              if (match === "istrue") {
                localStorage.setItem("newid", response.data.newid);
                localStorage.setItem("name", response.data.name);
                localStorage.setItem("allname", response.data.allname);
                tmp = ReasonReactRouter.push(autoLoginPath(ObjectFormat$BtsCore.checkObjects(sessionStorage.getItem("autoPath"))));
              } else {
                restoreAction(undefined);
                tmp = barShowRestoreAction(Status$BtsCore.accountModule(response.data.status));
              }
              return Promise.resolve(tmp);
            })).catch((function (error) {
            return Promise.resolve((console.log(error), undefined));
          }));
    
  };
  var keydownUserid = React.useCallback((function (keyCode) {
          if (keyCode === 13) {
            Curry._1(dispatch, /* ActionOtherLoad */Block.__(3, [true]));
            console.log(Data$BtsCore.loginData(state.userid, state.password, localStorage.getItem("longitude"), localStorage.getItem("latitude")));
            return loginUserAJax(undefined);
          }
          
        }));
  var keydownPassword = React.useCallback((function (keyCode) {
          if (keyCode === 13) {
            Curry._1(dispatch, /* ActionOtherLoad */Block.__(3, [true]));
            return loginUserAJax(undefined);
          }
          
        }));
  var sendForm = React.useCallback((function (param) {
          Curry._1(dispatch, /* ActionOtherLoad */Block.__(3, [true]));
          return loginUserAJax(undefined);
        }));
  return React.createElement(YoutubeLogin$BtsCore.make, {
              error: state.error,
              loading: state.loading,
              showYoutube: state.showYoutube,
              youtubeText: state.youtubeText,
              disabled: state.disabled,
              userid: state.userid,
              changeUserid: (function ($$event) {
                  return Curry._1(changeUserid, $$event.target.value);
                }),
              keydownUserid: (function ($$event) {
                  return Curry._1(keydownUserid, $$event.keyCode);
                }),
              password: state.password,
              changePassword: (function ($$event) {
                  return Curry._1(changePassword, $$event.target.value);
                }),
              keydownPassword: (function ($$event) {
                  return Curry._1(keydownPassword, $$event.keyCode);
                }),
              forgetForm: forgetForm,
              sendForm: sendForm,
              children: null
            });
}

var make = Login;

export {
  reducer ,
  initialState ,
  autoLoginPath ,
  make ,
  
}
/* react Not a pure module */
