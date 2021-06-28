// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as $$Array from "bs-platform/lib/es6/array.js";
import * as Block from "bs-platform/lib/es6/block.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Data$BtsCore from "../../features/Data.bs.js";
import * as Status$BtsCore from "../../features/Status.bs.js";
import * as Divider$BtsCore from "../../material-ui/core/Divider/Divider.bs.js";
import * as Axiosapi$BtsCore from "../../features/Axiosapi.bs.js";
import * as GridItem$BtsCore from "../../material-ui/core/Grid/GridItem.bs.js";
import * as Together$BtsCore from "../../styles/Together/Together.bs.js";
import * as ReasonReactRouter from "reason-react/src/ReasonReactRouter.bs.js";
import * as Typography$BtsCore from "../../material-ui/core/Typography/Typography.bs.js";
import * as NewFacetube$BtsCore from "../../example/Facebook/NewFacetube.bs.js";
import * as ObjectFormat$BtsCore from "../../controls/ObjectFormat.bs.js";
import * as GridContainer$BtsCore from "../../material-ui/core/Grid/GridContainer.bs.js";
import * as SnackbarYoutube$BtsCore from "../../material-ui/core/Snackbar/SnackbarYoutube.bs.js";

((require('../../../scss/pages/Together/together.scss')));

function reducer(state, action) {
  if (typeof action === "number") {
    switch (action) {
      case /* SettingError */0 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  showProgress: state.showProgress,
                  error: !state.error,
                  insert: state.insert,
                  update: state.update,
                  delete: state.delete,
                  export: state.export,
                  items: state.items,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* SettingFormLoad */1 :
          return {
                  formLoad: !state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  showProgress: state.showProgress,
                  error: state.error,
                  insert: state.insert,
                  update: state.update,
                  delete: state.delete,
                  export: state.export,
                  items: state.items,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* ActionShowProgress */2 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  showProgress: !state.showProgress,
                  error: state.error,
                  insert: state.insert,
                  update: state.update,
                  delete: state.delete,
                  export: state.export,
                  items: state.items,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      
    }
  } else {
    switch (action.tag | 0) {
      case /* SettingFormWidth */0 :
          return {
                  formLoad: state.formLoad,
                  formWidth: action[0],
                  formHeight: action[1],
                  showProgress: state.showProgress,
                  error: state.error,
                  insert: state.insert,
                  update: state.update,
                  delete: state.delete,
                  export: state.export,
                  items: state.items,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* ActionPermissItems */1 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  showProgress: state.showProgress,
                  error: state.error,
                  insert: action[0],
                  update: action[1],
                  delete: action[2],
                  export: action[3],
                  items: state.items,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* SettingFormItems */2 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  showProgress: state.showProgress,
                  error: state.error,
                  insert: state.insert,
                  update: state.update,
                  delete: state.delete,
                  export: state.export,
                  items: action[0],
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* ActionSnackBar */3 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  showProgress: state.showProgress,
                  error: state.error,
                  insert: state.insert,
                  update: state.update,
                  delete: state.delete,
                  export: state.export,
                  items: state.items,
                  showYoutube: action[1],
                  youtubeText: action[0]
                };
      
    }
  }
}

var initialState_items = [];

var initialState = {
  formLoad: false,
  formWidth: 0,
  formHeight: 0,
  showProgress: true,
  error: false,
  insert: false,
  update: false,
  delete: false,
  export: false,
  items: initialState_items,
  showYoutube: false,
  youtubeText: ""
};

function Signlist(Props) {
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
  var barShowRestoreAction = function (youtubeText) {
    Curry._1(dispatch, /* ActionSnackBar */Block.__(3, [
            youtubeText,
            true
          ]));
    setTimeout((function (param) {
            return Curry._1(dispatch, /* ActionSnackBar */Block.__(3, [
                          "",
                          false
                        ]));
          }), 5000);
    
  };
  var searchAJax = function (param) {
    Axiosapi$BtsCore.Signlist.search(Data$BtsCore.userData(localStorage.getItem("newid"))).then((function (response) {
              var match = response.data.status;
              var tmp;
              if (match === "istrue") {
                Curry._1(dispatch, /* SettingFormItems */Block.__(2, [response.data.items]));
                tmp = Curry._1(dispatch, /* ActionShowProgress */2);
              } else {
                Curry._1(dispatch, /* SettingError */0);
                barShowRestoreAction(Status$BtsCore.statusModule(response.data.status));
                tmp = Curry._1(dispatch, /* ActionShowProgress */2);
              }
              return Promise.resolve(tmp);
            })).catch((function (error) {
            return Promise.resolve((console.log(error), undefined));
          }));
    
  };
  var permissAJax = function (param) {
    Axiosapi$BtsCore.Form.permiss(Data$BtsCore.userData(localStorage.getItem("newid"))).then((function (response) {
              return Promise.resolve((Curry._1(dispatch, /* ActionPermissItems */Block.__(1, [
                                  response.data.insert,
                                  response.data.update,
                                  response.data.delete,
                                  response.data.export
                                ])), searchAJax(undefined)));
            })).catch((function (error) {
            return Promise.resolve((console.log(error), undefined));
          }));
    
  };
  React.useEffect((function () {
          if (state.formLoad) {
            return (function (param) {
                      console.log("action");
                      
                    });
          }
          Curry._1(dispatch, /* SettingFormLoad */1);
          Curry._1(dispatch, /* SettingFormWidth */Block.__(0, [
                  window.innerWidth,
                  window.innerHeight
                ]));
          var match = ObjectFormat$BtsCore.checkObjects(sessionStorage.getItem("form"));
          var testId;
          var exit = 0;
          switch (match) {
            case "signInSuccess" :
            case "signOutSuccess" :
                exit = 1;
                break;
            default:
              console.log("action");
              testId = undefined;
          }
          if (exit === 1) {
            barShowRestoreAction(Status$BtsCore.signModels(ObjectFormat$BtsCore.checkObjects(sessionStorage.getItem("form"))));
            sessionStorage.setItem("form", "");
            testId = undefined;
          }
          var timeId = permissAJax(undefined);
          return (function (param) {
                    return timeId;
                  });
        }));
  var handleResize = function ($$event) {
    return Curry._1(dispatch, /* SettingFormWidth */Block.__(0, [
                  $$event.currentTarget.innerWidth,
                  $$event.currentTarget.innerHeight
                ]));
  };
  React.useEffect((function () {
          window.addEventListener("resize", handleResize, true);
          return (function (param) {
                    
                  });
        }), ([]));
  var clickFormBoard = React.useCallback(ReasonReactRouter.push);
  return React.createElement(React.Fragment, undefined, React.createElement(NewFacetube$BtsCore.make, {
                  showProgress: state.showProgress,
                  error: state.error,
                  children: React.createElement(GridItem$BtsCore.make, {
                        style: Together$BtsCore.marginAuto,
                        top: "0",
                        right: "32",
                        bottom: "0",
                        left: "32",
                        xs: "12",
                        maxWidth: "770px",
                        children: React.createElement(GridContainer$BtsCore.make, {
                              direction: "column",
                              justify: "center",
                              alignItem: "stretch",
                              children: $$Array.map((function (item) {
                                      return React.createElement(React.Fragment, undefined, React.createElement(GridItem$BtsCore.make, {
                                                      top: "0",
                                                      right: "0",
                                                      bottom: "0",
                                                      left: "0",
                                                      cursor: "pointer",
                                                      enterBorderRadius: "10",
                                                      borderRadius: "10",
                                                      enterBackgroundColor: "rgba(0,0,0,0.1)",
                                                      xs: "auto",
                                                      onClick: (function (param) {
                                                          return Curry._1(clickFormBoard, item.id);
                                                        }),
                                                      children: React.createElement(GridContainer$BtsCore.make, {
                                                            backgroundColor: "none",
                                                            direction: "column",
                                                            justify: "center",
                                                            alignItem: "stretch",
                                                            children: null
                                                          }, React.createElement(GridItem$BtsCore.make, {
                                                                enterBackgroundColor: "none",
                                                                backgroundColor: "none",
                                                                xs: "auto",
                                                                children: React.createElement(Typography$BtsCore.make, {
                                                                      variant: "tile",
                                                                      fontWeight: "600",
                                                                      children: item.tile
                                                                    })
                                                              }), React.createElement(GridItem$BtsCore.make, {
                                                                top: "0",
                                                                enterBackgroundColor: "none",
                                                                backgroundColor: "none",
                                                                xs: "auto",
                                                                children: React.createElement(Typography$BtsCore.make, {
                                                                      variant: "subheading",
                                                                      children: item.subject
                                                                    })
                                                              }), React.createElement(GridItem$BtsCore.make, {
                                                                top: "0",
                                                                enterBackgroundColor: "none",
                                                                backgroundColor: "none",
                                                                xs: "auto",
                                                                children: React.createElement(GridContainer$BtsCore.make, {
                                                                      backgroundColor: "none",
                                                                      direction: "row",
                                                                      justify: "start",
                                                                      alignItem: "center",
                                                                      children: null
                                                                    }, React.createElement(GridItem$BtsCore.make, {
                                                                          top: "0",
                                                                          bottom: "0",
                                                                          left: "0",
                                                                          enterBackgroundColor: "none",
                                                                          backgroundColor: "none",
                                                                          xs: "no",
                                                                          children: React.createElement(Typography$BtsCore.make, {
                                                                                variant: "subheading",
                                                                                color: "#606060",
                                                                                children: item.postdate
                                                                              })
                                                                        }), React.createElement(GridItem$BtsCore.make, {
                                                                          top: "0",
                                                                          bottom: "0",
                                                                          left: "0",
                                                                          enterBackgroundColor: "none",
                                                                          backgroundColor: "none",
                                                                          xs: "no",
                                                                          children: React.createElement(Typography$BtsCore.make, {
                                                                                variant: "subheading",
                                                                                color: "#606060",
                                                                                children: item.postGroup
                                                                              })
                                                                        }), React.createElement(GridItem$BtsCore.make, {
                                                                          top: "0",
                                                                          bottom: "0",
                                                                          left: "0",
                                                                          enterBackgroundColor: "none",
                                                                          backgroundColor: "none",
                                                                          xs: "no",
                                                                          children: React.createElement(Typography$BtsCore.make, {
                                                                                variant: "subheading",
                                                                                color: "#606060",
                                                                                children: item.postName
                                                                              })
                                                                        }))
                                                              }))
                                                    }), React.createElement(GridItem$BtsCore.make, {
                                                      top: "6",
                                                      right: "0",
                                                      bottom: "6",
                                                      left: "0",
                                                      xs: "auto",
                                                      children: React.createElement(Divider$BtsCore.make, { })
                                                    }));
                                    }), state.items)
                            })
                      })
                }), React.createElement(SnackbarYoutube$BtsCore.make, {
                  showYoutube: state.showYoutube,
                  position: "bottomLeft",
                  children: /* tuple */[
                    React.createElement("span", undefined, state.youtubeText),
                    null
                  ]
                }));
}

var make = Signlist;

export {
  reducer ,
  initialState ,
  make ,
  
}
/*  Not a pure module */
