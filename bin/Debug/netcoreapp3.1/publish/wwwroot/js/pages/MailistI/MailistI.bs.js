// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as List from "bs-platform/lib/es6/list.js";
import * as $$Array from "bs-platform/lib/es6/array.js";
import * as Block from "bs-platform/lib/es6/block.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReactIntl from "react-intl";
import * as Tab$BtsCore from "../../material-ui/core/Tabs/Tab.bs.js";
import * as Data$BtsCore from "../../features/Data.bs.js";
import * as Path$BtsCore from "../../features/Path.bs.js";
import * as Tabs$BtsCore from "../../material-ui/core/Tabs/Tabs.bs.js";
import * as Icons$BtsCore from "../../material-ui/icon/Icons.bs.js";
import * as Button$BtsCore from "../../material-ui/core/Button/Button.bs.js";
import * as Status$BtsCore from "../../features/Status.bs.js";
import * as Switch$BtsCore from "../../material-ui/core/Switch/Switch.bs.js";
import * as Tooltip$BtsCore from "../../material-ui/core/Tooltip/Tooltip.bs.js";
import * as Axiosapi$BtsCore from "../../features/Axiosapi.bs.js";
import * as GridItem$BtsCore from "../../material-ui/core/Grid/GridItem.bs.js";
import * as Together$BtsCore from "../../styles/Together/Together.bs.js";
import * as ReasonReactRouter from "reason-react/src/ReasonReactRouter.bs.js";
import * as DialogFull$BtsCore from "../../material-ui/core/Dialog/DialogFull.bs.js";
import * as IconAction$BtsCore from "../../material-ui/core/IconStyle/IconAction.bs.js";
import * as IconButton$BtsCore from "../../material-ui/core/IconButton/IconButton.bs.js";
import * as Typography$BtsCore from "../../material-ui/core/Typography/Typography.bs.js";
import * as DialogTitle$BtsCore from "../../material-ui/core/Dialog/DialogTitle.bs.js";
import * as NewFacetube$BtsCore from "../../example/Facebook/NewFacetube.bs.js";
import * as SwitchColor$BtsCore from "../../controls/SwitchColor.bs.js";
import * as DialogActions$BtsCore from "../../material-ui/core/Dialog/DialogActions.bs.js";
import * as DialogContent$BtsCore from "../../material-ui/core/Dialog/DialogContent.bs.js";
import * as GridContainer$BtsCore from "../../material-ui/core/Grid/GridContainer.bs.js";
import * as SnackbarYoutube$BtsCore from "../../material-ui/core/Snackbar/SnackbarYoutube.bs.js";
import * as DialogContentText$BtsCore from "../../material-ui/core/Dialog/DialogContentText.bs.js";

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
                  tabitems: state.tabitems,
                  index: state.index,
                  items: state.items,
                  showFull: state.showFull,
                  formId: state.formId,
                  formTitle: state.formTitle,
                  formitems: state.formitems,
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
                  tabitems: state.tabitems,
                  index: state.index,
                  items: state.items,
                  showFull: state.showFull,
                  formId: state.formId,
                  formTitle: state.formTitle,
                  formitems: state.formitems,
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
                  tabitems: state.tabitems,
                  index: state.index,
                  items: state.items,
                  showFull: state.showFull,
                  formId: state.formId,
                  formTitle: state.formTitle,
                  formitems: state.formitems,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* CloseAnimationFull */3 :
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
                  tabitems: state.tabitems,
                  index: state.index,
                  items: state.items,
                  showFull: !state.showFull,
                  formId: state.formId,
                  formTitle: state.formTitle,
                  formitems: state.formitems,
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
                  tabitems: state.tabitems,
                  index: state.index,
                  items: state.items,
                  showFull: state.showFull,
                  formId: state.formId,
                  formTitle: state.formTitle,
                  formitems: state.formitems,
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
                  tabitems: state.tabitems,
                  index: state.index,
                  items: state.items,
                  showFull: state.showFull,
                  formId: state.formId,
                  formTitle: state.formTitle,
                  formitems: state.formitems,
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
                  tabitems: state.tabitems,
                  index: state.index,
                  items: action[0],
                  showFull: state.showFull,
                  formId: state.formId,
                  formTitle: state.formTitle,
                  formitems: state.formitems,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* ClickItemTab */3 :
          var index = action[0];
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
                  tabitems: List.mapi((function (i, tabitem) {
                          return {
                                  showTab: index === i,
                                  tabImage: tabitem.tabImage
                                };
                        }), state.tabitems),
                  index: index,
                  items: state.items,
                  showFull: state.showFull,
                  formId: state.formId,
                  formTitle: state.formTitle,
                  formitems: state.formitems,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* ShowAnimationFull */4 :
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
                  tabitems: state.tabitems,
                  index: state.index,
                  items: state.items,
                  showFull: !state.showFull,
                  formId: action[0],
                  formTitle: action[1],
                  formitems: action[2],
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* SwitchNotice */5 :
          var index$1 = action[0];
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
                  tabitems: state.tabitems,
                  index: state.index,
                  items: state.items,
                  showFull: state.showFull,
                  formId: state.formId,
                  formTitle: state.formTitle,
                  formitems: $$Array.mapi((function (i, item) {
                          if (index$1 === i) {
                            return {
                                    newid: item.newid,
                                    username: item.username,
                                    notice: !item.notice,
                                    formModify: true
                                  };
                          } else {
                            return item;
                          }
                        }), state.formitems),
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* ActionSnackBar */6 :
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
                  tabitems: state.tabitems,
                  index: state.index,
                  items: state.items,
                  showFull: state.showFull,
                  formId: state.formId,
                  formTitle: state.formTitle,
                  formitems: state.formitems,
                  showYoutube: action[1],
                  youtubeText: action[0]
                };
      
    }
  }
}

var initialState_tabitems = /* :: */[
  {
    showTab: false,
    tabImage: Icons$BtsCore.transmissionBlack
  },
  /* :: */[
    {
      showTab: false,
      tabImage: Icons$BtsCore.factoryBlack
    },
    /* :: */[
      {
        showTab: true,
        tabImage: Icons$BtsCore.fileCopyBlack
      },
      /* [] */0
    ]
  ]
];

var initialState_items = [];

var initialState_formitems = [];

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
  tabitems: initialState_tabitems,
  index: 2,
  items: initialState_items,
  showFull: false,
  formId: "",
  formTitle: "",
  formitems: initialState_formitems,
  showYoutube: false,
  youtubeText: ""
};

function MailistI(Props) {
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
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
  var searchAJax = function (param) {
    Axiosapi$BtsCore.MailistI.search(Data$BtsCore.otherData(localStorage.getItem("newid"), String(state.items.length))).then((function (response) {
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
          var match = state.formLoad;
          if (match) {
            return (function (param) {
                      console.log("action");
                      
                    });
          }
          Curry._1(dispatch, /* SettingFormLoad */1);
          Curry._1(dispatch, /* SettingFormWidth */Block.__(0, [
                  window.innerWidth,
                  window.innerHeight
                ]));
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
  var clickItemTab = React.useCallback((function (i) {
          if (i === 0) {
            return ReasonReactRouter.push(Path$BtsCore.mailistRPath);
          } else if (i === 2) {
            return ReasonReactRouter.push(Path$BtsCore.mailistIPath);
          } else {
            return ;
          }
        }));
  var clickFormBoard = React.useCallback((function (value) {
          Curry._1(dispatch, /* ActionShowProgress */2);
          Axiosapi$BtsCore.MailistI.sItem(Data$BtsCore.otherData(localStorage.getItem("newid"), value)).then((function (response) {
                    var match = response.data.status;
                    var tmp;
                    if (match === "istrue") {
                      Curry._1(dispatch, /* ShowAnimationFull */Block.__(4, [
                              value,
                              response.data.tile,
                              response.data.items
                            ]));
                      tmp = Curry._1(dispatch, /* ActionShowProgress */2);
                    } else {
                      barShowRestoreAction(Status$BtsCore.statusModule(response.data.status));
                      tmp = Curry._1(dispatch, /* ActionShowProgress */2);
                    }
                    return Promise.resolve(tmp);
                  })).catch((function (error) {
                  return Promise.resolve((console.log(error), undefined));
                }));
          
        }));
  var insertForm = React.useCallback((function (param) {
          Curry._1(dispatch, /* ActionShowProgress */2);
          Axiosapi$BtsCore.MailistI.insert(Data$BtsCore.iFormData(state.formId, state.formTitle, state.formitems.filter((function (formitem) {
                              return formitem.formModify === true;
                            })), localStorage.getItem("newid"))).then((function (response) {
                    var match = response.data.status;
                    var tmp;
                    if (match === "istrue") {
                      Curry._1(dispatch, /* CloseAnimationFull */3);
                      barShowRestoreAction(Status$BtsCore.statusModule("saveSuccess"));
                      tmp = Curry._1(dispatch, /* ActionShowProgress */2);
                    } else {
                      barShowRestoreAction(Status$BtsCore.statusModule(response.data.status));
                      tmp = Curry._1(dispatch, /* ActionShowProgress */2);
                    }
                    return Promise.resolve(tmp);
                  })).catch((function (error) {
                  return Promise.resolve((console.log(error), undefined));
                }));
          
        }));
  var switchNotice = React.useCallback((function (i) {
          return Curry._1(dispatch, /* SwitchNotice */Block.__(5, [i]));
        }));
  var closeAnimationFull = React.useCallback((function (param) {
          return Curry._1(dispatch, /* CloseAnimationFull */3);
        }));
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
                              children: null
                            }, React.createElement(GridItem$BtsCore.make, {
                                  style: {
                                    position: "sticky",
                                    top: "0px",
                                    zIndex: "1000"
                                  },
                                  top: "0",
                                  bottom: "6",
                                  left: "0",
                                  xs: "auto",
                                  children: React.createElement(Tabs$BtsCore.make, {
                                        id: "mail-",
                                        index: state.index,
                                        height: "3",
                                        children: $$Array.of_list(List.mapi((function (i, tabitem) {
                                                    return React.createElement(Tab$BtsCore.make, {
                                                                showTab: tabitem.showTab,
                                                                maxWidth: "111.6",
                                                                borderRadius: "15",
                                                                id: "mail-" + String(i),
                                                                animationName: "none",
                                                                onClick: (function (param) {
                                                                    return Curry._1(clickItemTab, i);
                                                                  }),
                                                                children: React.createElement(IconAction$BtsCore.make, {
                                                                      width: "28",
                                                                      height: "28",
                                                                      animation: "leftRight",
                                                                      src: tabitem.tabImage
                                                                    })
                                                              });
                                                  }), state.tabitems))
                                      })
                                }), $$Array.map((function (item) {
                                    return React.createElement("div", {
                                                onClick: (function (param) {
                                                    return Curry._1(clickFormBoard, item);
                                                  })
                                              }, React.createElement(GridItem$BtsCore.make, {
                                                    style: {
                                                      cursor: "pointer"
                                                    },
                                                    enterBorderRadius: "10",
                                                    enterBackgroundColor: "rgba(0,0,0,0.1)",
                                                    xs: "auto",
                                                    children: React.createElement(Typography$BtsCore.make, {
                                                          variant: "subheading",
                                                          children: item
                                                        })
                                                  }));
                                  }), state.items))
                      })
                }), React.createElement(DialogFull$BtsCore.make, {
                  showAnimation: state.showFull,
                  children: null
                }, React.createElement(DialogTitle$BtsCore.make, {
                      top: "22",
                      left: "64",
                      children: React.createElement(Typography$BtsCore.make, {
                            variant: "tile",
                            fontWeight: "600",
                            children: state.formTitle
                          })
                    }), React.createElement(DialogContent$BtsCore.make, {
                      children: React.createElement(DialogContentText$BtsCore.make, {
                            children: React.createElement(GridItem$BtsCore.make, {
                                  style: Together$BtsCore.marginAuto,
                                  top: "0",
                                  right: "0",
                                  bottom: "0",
                                  left: "54",
                                  xs: "12",
                                  maxWidth: "770px",
                                  children: React.createElement(GridContainer$BtsCore.make, {
                                        direction: "column",
                                        justify: "center",
                                        alignItem: "stretch",
                                        children: null
                                      }, React.createElement(GridItem$BtsCore.make, {
                                            style: {
                                              position: "sticky",
                                              top: "0px",
                                              zIndex: "1000"
                                            },
                                            top: "0",
                                            bottom: "6",
                                            left: "0",
                                            xs: "auto",
                                            children: React.createElement(GridContainer$BtsCore.make, {
                                                  direction: "rowReverse",
                                                  justify: "center",
                                                  alignItem: "center",
                                                  children: null
                                                }, React.createElement(GridItem$BtsCore.make, {
                                                      top: "0",
                                                      right: "0",
                                                      bottom: "0",
                                                      left: "0",
                                                      xs: "no",
                                                      children: React.createElement(Button$BtsCore.make, {
                                                            disabled: state.showProgress,
                                                            onClick: insertForm,
                                                            children: React.createElement(ReactIntl.FormattedMessage, {
                                                                  id: "save",
                                                                  defaultMessage: "Save"
                                                                })
                                                          })
                                                    }), React.createElement(GridItem$BtsCore.make, {
                                                      top: "0",
                                                      right: "0",
                                                      bottom: "0",
                                                      left: "0",
                                                      xs: "auto",
                                                      children: null
                                                    }))
                                          }), $$Array.mapi((function (i, item) {
                                              return React.createElement(GridItem$BtsCore.make, {
                                                          style: {
                                                            cursor: "pointer"
                                                          },
                                                          enterBorderRadius: "10",
                                                          enterBackgroundColor: "rgba(0,0,0,0.1)",
                                                          xs: "auto",
                                                          children: React.createElement(GridContainer$BtsCore.make, {
                                                                backgroundColor: "transparent",
                                                                direction: "row",
                                                                justify: "around",
                                                                alignItem: "center",
                                                                children: null
                                                              }, React.createElement(GridItem$BtsCore.make, {
                                                                    top: "0",
                                                                    right: "0",
                                                                    bottom: "0",
                                                                    left: "0",
                                                                    enterBackgroundColor: "transparent",
                                                                    backgroundColor: "transparent",
                                                                    xs: "auto",
                                                                    children: React.createElement(Typography$BtsCore.make, {
                                                                          variant: "subheading",
                                                                          children: item.username
                                                                        })
                                                                  }), React.createElement(GridItem$BtsCore.make, {
                                                                    top: "0",
                                                                    right: "0",
                                                                    bottom: "0",
                                                                    left: "0",
                                                                    enterBackgroundColor: "transparent",
                                                                    backgroundColor: "transparent",
                                                                    xs: "no",
                                                                    children: React.createElement(Switch$BtsCore.make, {
                                                                          right: "0",
                                                                          checked: item.notice,
                                                                          circleColor: SwitchColor$BtsCore.circle(item.notice),
                                                                          linearColor: SwitchColor$BtsCore.linear(item.notice),
                                                                          fontColor: SwitchColor$BtsCore.font(item.notice),
                                                                          disabled: state.showProgress,
                                                                          onClick: (function (param) {
                                                                              return Curry._1(switchNotice, i);
                                                                            }),
                                                                          children: "???????????????"
                                                                        })
                                                                  }))
                                                        });
                                            }), state.formitems))
                                })
                          })
                    }), React.createElement(DialogActions$BtsCore.make, {
                      children: React.createElement("div", {
                            style: {
                              left: "10px",
                              position: "fixed",
                              top: "10px"
                            }
                          }, React.createElement(IconButton$BtsCore.make, {
                                padding: "12",
                                disabled: state.showProgress,
                                onClick: closeAnimationFull,
                                children: null
                              }, React.createElement(Tooltip$BtsCore.make, {
                                    location: "bottom",
                                    backgroundColor: "rgba(255,0,0,0.8)",
                                    children: React.createElement(ReactIntl.FormattedMessage, {
                                          id: "closed",
                                          defaultMessage: "Closed"
                                        })
                                  }), React.createElement(IconAction$BtsCore.make, {
                                    animation: "circle",
                                    src: Icons$BtsCore.clearBlack
                                  })))
                    })), React.createElement(SnackbarYoutube$BtsCore.make, {
                  showYoutube: state.showYoutube,
                  position: "bottomLeft",
                  children: /* tuple */[
                    React.createElement("span", undefined, state.youtubeText),
                    null
                  ]
                }));
}

var make = MailistI;

export {
  reducer ,
  initialState ,
  make ,
  
}
/*  Not a pure module */
