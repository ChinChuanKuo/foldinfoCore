// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Block from "bs-platform/lib/es6/block.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Data$BtsCore from "../../features/Data.bs.js";
import * as Path$BtsCore from "../../features/Path.bs.js";
import * as Status$BtsCore from "../../features/Status.bs.js";
import * as Axiosapi$BtsCore from "../../features/Axiosapi.bs.js";
import * as ReasonReactRouter from "reason-react/src/ReasonReactRouter.bs.js";
import * as YoutubeSignup$BtsCore from "../../example/Account/Signup/YoutubeSignup.bs.js";

function reducer(state, action) {
  switch (action.tag | 0) {
    case /* ChangeUserid */0 :
        return {
                error: state.error,
                loading: state.loading,
                showYoutube: state.showYoutube,
                youtubeText: state.youtubeText,
                disabled: state.disabled,
                userid: action[0],
                password: state.password,
                username: state.username,
                birthday: state.birthday
              };
    case /* ChangePassword */1 :
        return {
                error: state.error,
                loading: state.loading,
                showYoutube: state.showYoutube,
                youtubeText: state.youtubeText,
                disabled: state.disabled,
                userid: state.userid,
                password: action[0],
                username: state.username,
                birthday: state.birthday
              };
    case /* ChangeUsername */2 :
        return {
                error: state.error,
                loading: state.loading,
                showYoutube: state.showYoutube,
                youtubeText: state.youtubeText,
                disabled: state.disabled,
                userid: state.userid,
                password: state.password,
                username: action[0],
                birthday: state.birthday
              };
    case /* ChangeBirthday */3 :
        return {
                error: state.error,
                loading: state.loading,
                showYoutube: state.showYoutube,
                youtubeText: state.youtubeText,
                disabled: state.disabled,
                userid: state.userid,
                password: state.password,
                username: state.username,
                birthday: action[0]
              };
    case /* ActionOtherLoad */4 :
        var other = action[0];
        return {
                error: state.error,
                loading: other,
                showYoutube: state.showYoutube,
                youtubeText: state.youtubeText,
                disabled: other,
                userid: state.userid,
                password: state.password,
                username: state.username,
                birthday: state.birthday
              };
    case /* ActionErrorLoad */5 :
        return {
                error: action[0],
                loading: state.loading,
                showYoutube: state.showYoutube,
                youtubeText: state.youtubeText,
                disabled: state.disabled,
                userid: state.userid,
                password: state.password,
                username: state.username,
                birthday: state.birthday
              };
    case /* ActionSnackBar */6 :
        return {
                error: state.error,
                loading: state.loading,
                showYoutube: action[1],
                youtubeText: action[0],
                disabled: state.disabled,
                userid: state.userid,
                password: state.password,
                username: state.username,
                birthday: state.birthday
              };
    
  }
}

var initialState = {
  error: false,
  loading: false,
  showYoutube: false,
  youtubeText: "",
  disabled: false,
  userid: "",
  password: "",
  username: "",
  birthday: ""
};

function Signup(Props) {
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
  var changeUserid = React.useCallback((function (value) {
          sessionStorage.setItem("userid", value);
          return Curry._1(dispatch, /* ChangeUserid */Block.__(0, [value]));
        }));
  var changePassword = React.useCallback((function (value) {
          return Curry._1(dispatch, /* ChangePassword */Block.__(1, [value]));
        }));
  var changeUsername = React.useCallback((function (value) {
          return Curry._1(dispatch, /* ChangeUsername */Block.__(2, [value]));
        }));
  var changeBirthday = React.useCallback((function (value) {
          return Curry._1(dispatch, /* ChangeBirthday */Block.__(3, [value]));
        }));
  setTimeout((function (param) {
          Curry._1(dispatch, /* ActionErrorLoad */Block.__(5, [false]));
          return Curry._1(dispatch, /* ActionOtherLoad */Block.__(4, [false]));
        }), 500);
  var barShowRestoreAction = function (youtubeText) {
    Curry._1(dispatch, /* ActionSnackBar */Block.__(6, [
            youtubeText,
            true
          ]));
    setTimeout((function (param) {
            return Curry._1(dispatch, /* ActionSnackBar */Block.__(6, [
                          "",
                          false
                        ]));
          }), 5000);
    
  };
  var signupUserAJax = function (param) {
    Axiosapi$BtsCore.Signup.signupUser(Data$BtsCore.signupData(state.userid, state.password, state.username, state.birthday)).then((function (response) {
              var match = response.data.status;
              var tmp;
              if (match === "istrue") {
                tmp = ReasonReactRouter.push(Path$BtsCore.loginPath);
              } else {
                Curry._1(dispatch, /* ActionErrorLoad */Block.__(5, [true]));
                tmp = barShowRestoreAction(Status$BtsCore.accountModule(response.data.status));
              }
              return Promise.resolve(tmp);
            })).catch((function (error) {
            return Promise.resolve((console.log(error), undefined));
          }));
    
  };
  var keydownUserid = React.useCallback((function (keyCode) {
          if (keyCode === 13) {
            Curry._1(dispatch, /* ActionOtherLoad */Block.__(4, [true]));
            return signupUserAJax(undefined);
          }
          
        }));
  var keydownPassword = React.useCallback((function (keyCode) {
          if (keyCode === 13) {
            Curry._1(dispatch, /* ActionOtherLoad */Block.__(4, [true]));
            return signupUserAJax(undefined);
          }
          
        }));
  var keydownUsername = React.useCallback((function (keyCode) {
          if (keyCode === 13) {
            Curry._1(dispatch, /* ActionOtherLoad */Block.__(4, [true]));
            return signupUserAJax(undefined);
          }
          
        }));
  var keydownBirthday = React.useCallback((function (keyCode) {
          if (keyCode === 13) {
            Curry._1(dispatch, /* ActionOtherLoad */Block.__(4, [true]));
            return signupUserAJax(undefined);
          }
          
        }));
  var nextForm = React.useCallback((function (param) {
          Curry._1(dispatch, /* ActionOtherLoad */Block.__(4, [true]));
          return signupUserAJax(undefined);
        }));
  return React.createElement(YoutubeSignup$BtsCore.make, {
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
              username: state.username,
              changeUsername: (function ($$event) {
                  return Curry._1(changeUsername, $$event.target.value);
                }),
              keydownUsername: (function ($$event) {
                  return Curry._1(keydownUsername, $$event.keyCode);
                }),
              birthday: state.birthday,
              changeBirthday: (function ($$event) {
                  return Curry._1(changeBirthday, $$event.target.value);
                }),
              keydownBirthday: (function ($$event) {
                  return Curry._1(keydownBirthday, $$event.keyCode);
                }),
              backForm: (function (param) {
                  return ReasonReactRouter.push(Path$BtsCore.loginPath);
                }),
              nextForm: nextForm
            });
}

var make = Signup;

export {
  reducer ,
  initialState ,
  make ,
  
}
/* react Not a pure module */
