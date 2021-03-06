// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Block from "bs-platform/lib/es6/block.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Data$BtsCore from "../../features/Data.bs.js";
import * as Path$BtsCore from "../../features/Path.bs.js";
import * as Basic$BtsCore from "../../setting/Basic.bs.js";
import * as Icons$BtsCore from "../../material-ui/icon/Icons.bs.js";
import * as AppBar$BtsCore from "../../material-ui/core/AppBar/AppBar.bs.js";
import * as Axiosapi$BtsCore from "../../features/Axiosapi.bs.js";
import * as GridItem$BtsCore from "../../material-ui/core/Grid/GridItem.bs.js";
import * as Together$BtsCore from "../../styles/Together/Together.bs.js";
import * as ReasonReactRouter from "reason-react/src/ReasonReactRouter.bs.js";
import * as IconAction$BtsCore from "../../material-ui/core/IconStyle/IconAction.bs.js";
import * as IconButton$BtsCore from "../../material-ui/core/IconButton/IconButton.bs.js";
import * as NewGramUser$BtsCore from "./NewGramUser.bs.js";
import * as NewGramBadge$BtsCore from "./NewGramBadge.bs.js";
import * as ObjectFormat$BtsCore from "../../controls/ObjectFormat.bs.js";
import * as GridContainer$BtsCore from "../../material-ui/core/Grid/GridContainer.bs.js";
import * as TextFieldOutline$BtsCore from "../../material-ui/core/TextField/TextFieldOutline.bs.js";

((require('../../../scss/example/Instagram/instagram.scss')));

function reducer(state, action) {
  if (typeof action === "number") {
    switch (action) {
      case /* ShowRecord */0 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  value: state.value,
                  showRecord: !state.showRecord,
                  showItemRecord: state.showItemRecord,
                  recorditems: state.recorditems,
                  index: state.index,
                  badge: state.badge,
                  showBadge: state.showBadge,
                  showUser: state.showUser,
                  beforeLoad: state.beforeLoad,
                  showItemBadge: state.showItemBadge
                };
      case /* ShowBadge */1 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  value: state.value,
                  showRecord: state.showRecord,
                  showItemRecord: state.showItemRecord,
                  recorditems: state.recorditems,
                  index: state.index,
                  badge: state.badge,
                  showBadge: !state.showBadge,
                  showUser: state.showUser,
                  beforeLoad: state.beforeLoad,
                  showItemBadge: state.showItemBadge
                };
      case /* ShowUser */2 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  value: state.value,
                  showRecord: state.showRecord,
                  showItemRecord: state.showItemRecord,
                  recorditems: state.recorditems,
                  index: state.index,
                  badge: state.badge,
                  showBadge: state.showBadge,
                  showUser: !state.showUser,
                  beforeLoad: state.beforeLoad,
                  showItemBadge: state.showItemBadge
                };
      
    }
  } else {
    switch (action.tag | 0) {
      case /* SettingFormLoad */0 :
          return {
                  formLoad: !state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  value: action[0],
                  showRecord: state.showRecord,
                  showItemRecord: state.showItemRecord,
                  recorditems: state.recorditems,
                  index: action[1],
                  badge: state.badge,
                  showBadge: state.showBadge,
                  showUser: state.showUser,
                  beforeLoad: state.beforeLoad,
                  showItemBadge: state.showItemBadge
                };
      case /* SettingFormWidth */1 :
          return {
                  formLoad: state.formLoad,
                  formWidth: action[0],
                  formHeight: action[1],
                  value: state.value,
                  showRecord: state.showRecord,
                  showItemRecord: state.showItemRecord,
                  recorditems: state.recorditems,
                  index: state.index,
                  badge: state.badge,
                  showBadge: state.showBadge,
                  showUser: state.showUser,
                  beforeLoad: state.beforeLoad,
                  showItemBadge: state.showItemBadge
                };
      case /* SettingBadge */2 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  value: state.value,
                  showRecord: state.showRecord,
                  showItemRecord: state.showItemRecord,
                  recorditems: state.recorditems,
                  index: state.index,
                  badge: action[0],
                  showBadge: state.showBadge,
                  showUser: state.showUser,
                  beforeLoad: state.beforeLoad,
                  showItemBadge: state.showItemBadge
                };
      case /* ChangeField */3 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  value: action[0],
                  showRecord: state.showRecord,
                  showItemRecord: state.showItemRecord,
                  recorditems: state.recorditems,
                  index: state.index,
                  badge: state.badge,
                  showBadge: state.showBadge,
                  showUser: state.showUser,
                  beforeLoad: state.beforeLoad,
                  showItemBadge: state.showItemBadge
                };
      case /* ClickRecordItems */4 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  value: state.value,
                  showRecord: state.showRecord,
                  showItemRecord: action[0],
                  recorditems: action[1],
                  index: state.index,
                  badge: state.badge,
                  showBadge: state.showBadge,
                  showUser: state.showUser,
                  beforeLoad: !state.beforeLoad,
                  showItemBadge: state.showItemBadge
                };
      case /* ClickBadgeItems */5 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  value: state.value,
                  showRecord: state.showRecord,
                  showItemRecord: state.showItemRecord,
                  recorditems: state.recorditems,
                  index: state.index,
                  badge: state.badge,
                  showBadge: state.showBadge,
                  showUser: state.showUser,
                  beforeLoad: !state.beforeLoad,
                  showItemBadge: action[0]
                };
      
    }
  }
}

var initialState_recorditems = [];

var initialState = {
  formLoad: false,
  formWidth: 0,
  formHeight: 0,
  value: "",
  showRecord: false,
  showItemRecord: false,
  recorditems: initialState_recorditems,
  index: 0,
  badge: "",
  showBadge: false,
  showUser: false,
  beforeLoad: true,
  showItemBadge: false
};

function NewGramBoard(Props) {
  var autoPath = Props.autoPath;
  var children = Props.children;
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
  var maxHeight = String(state.formHeight) + "px";
  var badgeFormAJax = function (param) {
    Axiosapi$BtsCore.Form.badgeForm(Data$BtsCore.userData(localStorage.getItem("newid"))).then((function (response) {
              return Promise.resolve(Curry._1(dispatch, /* SettingBadge */Block.__(2, [response.data.status])));
            })).catch((function (error) {
            return Promise.resolve((console.log(error), undefined));
          }));
    
  };
  var notification = function (param) {
    new Notification("New message from dcode !", {
          body: "test",
          icon: ""
        });
    
  };
  var notificationAJax = function (param) {
    if (Notification.permission === "granted") {
      return notification(undefined);
    } else if (Notification.permission !== "denied") {
      Notification.requestPermission().then((function (response) {
                return Promise.resolve(response === "granted" ? notification(undefined) : undefined);
              })).catch((function (error) {
              return Promise.resolve((console.log(error), undefined));
            }));
      return ;
    } else {
      return ;
    }
  };
  var loginFormAJax = function (param) {
    Axiosapi$BtsCore.Form.loginForm(Data$BtsCore.userData(localStorage.getItem("newid"))).then((function (response) {
              var match = response.data.status;
              var tmp;
              if (match === "istrue") {
                localStorage.setItem("name", response.data.name);
                localStorage.setItem("allname", response.data.allname);
                navigator.geolocation.getCurrentPosition(Basic$BtsCore.$$Location.success, Basic$BtsCore.$$Location.error, Basic$BtsCore.$$Location.items);
                Basic$BtsCore.Browser.success(navigator.userAgent);
                notificationAJax(undefined);
                tmp = badgeFormAJax(undefined);
              } else {
                localStorage.setItem("newid", "");
                sessionStorage.setItem("autoPath", autoPath);
                tmp = ReasonReactRouter.push(Path$BtsCore.loginPath);
              }
              return Promise.resolve(tmp);
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
          Curry._1(dispatch, /* SettingFormLoad */Block.__(0, [
                  ObjectFormat$BtsCore.checkObjects(sessionStorage.getItem("search")),
                  ["/"].indexOf(autoPath)
                ]));
          Curry._1(dispatch, /* SettingFormWidth */Block.__(1, [
                  window.innerWidth,
                  window.innerHeight
                ]));
          var badgeId = loginFormAJax(undefined);
          return (function (param) {
                    return badgeId;
                  });
        }));
  var handleResize = function ($$event) {
    return Curry._1(dispatch, /* SettingFormWidth */Block.__(1, [
                  $$event.currentTarget.innerWidth,
                  $$event.currentTarget.innerHeight
                ]));
  };
  React.useEffect((function () {
          window.addEventListener("resize", handleResize, true);
          return (function (param) {
                    
                  });
        }), ([]));
  var changeField = React.useCallback((function (value) {
          Curry._1(dispatch, /* ChangeField */Block.__(3, [value]));
          sessionStorage.setItem("search", value);
          
        }));
  var searchRecord = React.useCallback((function (param) {
          Curry._1(dispatch, /* ShowRecord */0);
          Axiosapi$BtsCore.Form.record(Data$BtsCore.userData(localStorage.getItem("newid"))).then((function (response) {
                    return Promise.resolve(Curry._1(dispatch, /* ClickRecordItems */Block.__(4, [
                                      response.data.showItem,
                                      response.data.items
                                    ])));
                  })).catch((function (error) {
                  return Promise.resolve((console.log(error), undefined));
                }));
          
        }));
  var keydownField = React.useCallback((function (keyCode) {
          if (keyCode === 13 && state.value !== "") {
            return ReasonReactRouter.push(Path$BtsCore.searchPath + ("#" + state.value));
          }
          
        }));
  var showBadge = React.useCallback((function (param) {
          return Curry._1(dispatch, /* ShowBadge */1);
        }));
  var showUser = React.useCallback((function (param) {
          return Curry._1(dispatch, /* ShowUser */2);
        }));
  var clickOut = React.useCallback((function (param) {
          localStorage.setItem("newid", "");
          sessionStorage.setItem("autoPath", autoPath);
          return ReasonReactRouter.push(Path$BtsCore.loginPath);
        }));
  return React.createElement(React.Fragment, undefined, React.createElement(AppBar$BtsCore.make, {
                  backgroundColor: "rgba(255,255,255,1)",
                  minHeight: "54",
                  children: React.createElement(GridItem$BtsCore.make, {
                        style: Together$BtsCore.marginAuto,
                        top: "0",
                        right: "20",
                        bottom: "0",
                        left: "20",
                        xs: "12",
                        maxWidth: "933px",
                        children: React.createElement(GridContainer$BtsCore.make, {
                              direction: "row",
                              justify: "center",
                              alignItem: "center",
                              children: null
                            }, React.createElement(GridItem$BtsCore.make, {
                                  top: "0",
                                  right: "0",
                                  bottom: "0",
                                  left: "0",
                                  xs: "auto",
                                  children: React.createElement(IconButton$BtsCore.make, {
                                        backgroundColor: "rgba(0,0,0,0.08)",
                                        padding: "10",
                                        children: React.createElement(IconAction$BtsCore.make, {
                                              animation: "circleTop",
                                              src: Icons$BtsCore.menuBlack
                                            })
                                      })
                                }), state.formWidth < 683 ? null : React.createElement(GridItem$BtsCore.make, {
                                    style: {
                                      minWidth: "125px"
                                    },
                                    top: "0",
                                    right: "0",
                                    bottom: "0",
                                    left: "0",
                                    width: "215px",
                                    xs: "no",
                                    children: React.createElement(TextFieldOutline$BtsCore.make, {
                                          top: "0",
                                          right: "0",
                                          bottom: "0",
                                          left: "0",
                                          borderTop: "6",
                                          borderBottom: "6",
                                          borderRadius: "6",
                                          enterBorderColor: "rgba(219,219,219,1)",
                                          downBorderColor: "rgba(219,219,219,1)",
                                          borderColor: "rgba(219,219,219,1)",
                                          fontColor: "rgba(38,38,38,1)",
                                          value: state.value,
                                          onChange: (function ($$event) {
                                              return Curry._1(changeField, $$event.target.value);
                                            }),
                                          onKeyDown: (function ($$event) {
                                              return Curry._1(keydownField, $$event.keyCode);
                                            }),
                                          onClick: searchRecord,
                                          children: null
                                        })
                                  }), React.createElement(GridItem$BtsCore.make, {
                                  top: "0",
                                  right: "0",
                                  bottom: "0",
                                  left: "0",
                                  xs: "auto",
                                  children: React.createElement(GridContainer$BtsCore.make, {
                                        direction: "row",
                                        justify: "end",
                                        alignItem: "center",
                                        children: null
                                      }, React.createElement(GridItem$BtsCore.make, {
                                            top: "0",
                                            right: "0",
                                            bottom: "0",
                                            left: "0",
                                            xs: "no",
                                            children: React.createElement(IconButton$BtsCore.make, {
                                                  enterBackgroundColor: "transparent",
                                                  downBackgroundColor: "transparent",
                                                  padding: "6",
                                                  children: React.createElement(IconAction$BtsCore.make, {
                                                        style: Together$BtsCore.zIndexGrow,
                                                        width: "28",
                                                        height: "28",
                                                        animation: "leftRight",
                                                        src: Icons$BtsCore.homeBlack
                                                      })
                                                })
                                          }), React.createElement(GridItem$BtsCore.make, {
                                            top: "0",
                                            right: "0",
                                            bottom: "0",
                                            left: "0",
                                            xs: "no",
                                            children: React.createElement(IconButton$BtsCore.make, {
                                                  enterBackgroundColor: "transparent",
                                                  downBackgroundColor: "transparent",
                                                  padding: "6",
                                                  children: React.createElement(IconAction$BtsCore.make, {
                                                        style: Together$BtsCore.zIndexGrow,
                                                        width: "28",
                                                        height: "28",
                                                        animation: "leftRight",
                                                        src: Icons$BtsCore.sendBlack
                                                      })
                                                })
                                          }), React.createElement(GridItem$BtsCore.make, {
                                            top: "0",
                                            right: "0",
                                            bottom: "0",
                                            left: "0",
                                            xs: "no",
                                            children: React.createElement(IconButton$BtsCore.make, {
                                                  enterBackgroundColor: "transparent",
                                                  downBackgroundColor: "transparent",
                                                  padding: "6",
                                                  children: React.createElement(IconAction$BtsCore.make, {
                                                        style: Together$BtsCore.zIndexGrow,
                                                        width: "28",
                                                        height: "28",
                                                        animation: "leftRight",
                                                        src: Icons$BtsCore.exploreBlack
                                                      })
                                                })
                                          }), React.createElement(GridItem$BtsCore.make, {
                                            top: "0",
                                            right: "0",
                                            bottom: "0",
                                            left: "0",
                                            xs: "no",
                                            children: null
                                          }, React.createElement(IconButton$BtsCore.make, {
                                                enterBackgroundColor: "transparent",
                                                downBackgroundColor: "transparent",
                                                padding: "6",
                                                onClick: showBadge,
                                                children: React.createElement(IconAction$BtsCore.make, {
                                                      style: Together$BtsCore.zIndexGrow,
                                                      width: "28",
                                                      height: "28",
                                                      animation: "leftRight",
                                                      src: Icons$BtsCore.favoriteBorderBlack
                                                    })
                                              }), state.showBadge ? React.createElement(NewGramBadge$BtsCore.make, {
                                                  maxHeight: maxHeight,
                                                  badge: state.badge,
                                                  clickShow: showBadge
                                                }) : null), React.createElement(GridItem$BtsCore.make, {
                                            top: "0",
                                            right: "0",
                                            bottom: "0",
                                            left: "0",
                                            xs: "no",
                                            children: null
                                          }, React.createElement(IconButton$BtsCore.make, {
                                                enterBackgroundColor: "transparent",
                                                downBackgroundColor: "transparent",
                                                padding: "6",
                                                onClick: showUser,
                                                children: React.createElement(IconAction$BtsCore.make, {
                                                      style: Together$BtsCore.zIndexGrow,
                                                      width: "28",
                                                      height: "28",
                                                      animation: "leftRight",
                                                      src: Icons$BtsCore.personBlack
                                                    })
                                              }), state.showUser ? React.createElement(NewGramUser$BtsCore.make, {
                                                  clickOut: clickOut,
                                                  clickShow: showUser
                                                }) : null))
                                }))
                      })
                }), children);
}

var make = NewGramBoard;

export {
  reducer ,
  initialState ,
  make ,
  
}
/*  Not a pure module */
