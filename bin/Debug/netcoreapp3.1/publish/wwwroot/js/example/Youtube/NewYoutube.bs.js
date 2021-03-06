// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReactIntl from "react-intl";
import * as Icons$BtsCore from "../../material-ui/icon/Icons.bs.js";
import * as List_$BtsCore from "../../material-ui/core/List_/List_.bs.js";
import * as Drawer$BtsCore from "../../material-ui/core/Drawer/Drawer.bs.js";
import * as OutSide$BtsCore from "../../styles/OutSide/OutSide.bs.js";
import * as Setting$BtsCore from "../../setting/Setting.bs.js";
import * as GridItem$BtsCore from "../../material-ui/core/Grid/GridItem.bs.js";
import * as ListItem$BtsCore from "../../material-ui/core/ListItem/ListItem.bs.js";
import * as Together$BtsCore from "../../styles/Together/Together.bs.js";
import * as IconAction$BtsCore from "../../material-ui/core/IconStyle/IconAction.bs.js";
import * as IconButton$BtsCore from "../../material-ui/core/IconButton/IconButton.bs.js";
import * as Typography$BtsCore from "../../material-ui/core/Typography/Typography.bs.js";
import * as IconGeneral$BtsCore from "../../material-ui/core/IconStyle/IconGeneral.bs.js";
import * as GridContainer$BtsCore from "../../material-ui/core/Grid/GridContainer.bs.js";
import * as ProgressLinear$BtsCore from "../../material-ui/core/Progress/ProgressLinear.bs.js";
import * as BackgroundBoard$BtsCore from "../Boards/BackgroundBoard.bs.js";

((require('../../../scss/example/Youtube/newYoutube.scss')));

function reducer(state, action) {
  if (typeof action === "number") {
    if (action !== 0) {
      return {
              formLoad: state.formLoad,
              formWidth: state.formWidth,
              formHeight: state.formHeight,
              showOpen: !state.showOpen
            };
    } else {
      return {
              formLoad: !state.formLoad,
              formWidth: state.formWidth,
              formHeight: state.formHeight,
              showOpen: state.showOpen
            };
    }
  } else {
    return {
            formLoad: state.formLoad,
            formWidth: action[0],
            formHeight: action[1],
            showOpen: state.showOpen
          };
  }
}

var initialState = {
  formLoad: false,
  formWidth: 0,
  formHeight: 0,
  showOpen: false
};

function widths(width) {
  if (width !== undefined) {
    return width + "%";
  } else {
    return "80%";
  }
}

function bottoms(bottom) {
  if (bottom !== undefined) {
    return bottom + "px";
  } else {
    return "0px";
  }
}

function NewYoutube(Props) {
  var showProgress = Props.showProgress;
  var error = Props.error;
  var width = Props.width;
  var bottom = Props.bottom;
  var children = Props.children;
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
  React.useEffect((function () {
          if (state.formLoad) {
            return (function (param) {
                      console.log("action");
                      
                    });
          }
          Curry._1(dispatch, /* SettingFormLoad */0);
          var formId = Curry._1(dispatch, /* SettingFormWidth */[
                window.innerWidth,
                window.innerHeight
              ]);
          return (function (param) {
                    return formId;
                  });
        }));
  var handleResize = function ($$event) {
    return Curry._1(dispatch, /* SettingFormWidth */[
                $$event.currentTarget.innerWidth,
                $$event.currentTarget.innerHeight
              ]);
  };
  React.useEffect((function () {
          window.addEventListener("resize", handleResize, true);
          return (function (param) {
                    
                  });
        }), ([]));
  var showOpen = React.useCallback((function (param) {
          return Curry._1(dispatch, /* ShowOpen */1);
        }));
  return React.createElement(React.Fragment, undefined, Setting$BtsCore.disabledObjects(showProgress) ? React.createElement(ProgressLinear$BtsCore.make, {
                    style: OutSide$BtsCore.progressFixed
                  }) : null, React.createElement(IconButton$BtsCore.make, {
                  style: OutSide$BtsCore.menuButn,
                  padding: "8",
                  onClick: showOpen,
                  children: React.createElement(IconAction$BtsCore.make, {
                        animation: "circleTop",
                        src: Icons$BtsCore.menuBlack
                      })
                }), React.createElement(Drawer$BtsCore.make, {
                  style: OutSide$BtsCore.drawerNewTube,
                  left: state.formWidth < 960 ? "-72" : "0",
                  width: "72px",
                  height: "64",
                  location: "left",
                  children: React.createElement(List_$BtsCore.make, {
                        children: React.createElement(ListItem$BtsCore.make, {
                              top: "0",
                              right: "0",
                              bottom: "0",
                              left: "0",
                              children: React.createElement(GridContainer$BtsCore.make, {
                                    backgroundColor: "transparent",
                                    direction: "column",
                                    justify: "center",
                                    alignItem: "center",
                                    children: null
                                  }, React.createElement(GridItem$BtsCore.make, {
                                        style: {
                                          height: "26px"
                                        },
                                        top: "0",
                                        right: "0",
                                        bottom: "0",
                                        left: "0",
                                        enterBackgroundColor: "transparent",
                                        backgroundColor: "transparent",
                                        xs: "auto",
                                        children: React.createElement(IconGeneral$BtsCore.make, {
                                              src: Icons$BtsCore.homeBlack
                                            })
                                      }), React.createElement(GridItem$BtsCore.make, {
                                        top: "0",
                                        right: "0",
                                        bottom: "0",
                                        left: "0",
                                        enterBackgroundColor: "transparent",
                                        backgroundColor: "transparent",
                                        xs: "auto",
                                        children: React.createElement(Typography$BtsCore.make, {
                                              variant: "subheading",
                                              children: React.createElement(ReactIntl.FormattedMessage, {
                                                    id: "Path.home",
                                                    defaultMessage: "Home"
                                                  })
                                            })
                                      }))
                            })
                      })
                }), React.createElement(Drawer$BtsCore.make, {
                  style: Object.assign(({}), OutSide$BtsCore.drawerTube, {
                        transition: state.showOpen ? "left 225ms cubic-bezier(0.4, 0, 0.6, 1) 0ms" : "left 195ms cubic-bezier(0.4, 0, 0.6, 1) 0ms"
                      }),
                  left: state.showOpen ? "0" : "-240",
                  width: "240px",
                  height: "64",
                  location: "left",
                  children: React.createElement(List_$BtsCore.make, {
                        children: React.createElement(ListItem$BtsCore.make, {
                              top: "0",
                              right: "8",
                              bottom: "0",
                              left: "8",
                              children: React.createElement(GridContainer$BtsCore.make, {
                                    backgroundColor: "transparent",
                                    direction: "row",
                                    justify: "center",
                                    alignItem: "center",
                                    children: null
                                  }, React.createElement(GridItem$BtsCore.make, {
                                        style: {
                                          height: "26px"
                                        },
                                        top: "0",
                                        right: "22",
                                        bottom: "0",
                                        left: "0",
                                        enterBackgroundColor: "transparent",
                                        backgroundColor: "transparent",
                                        xs: "no",
                                        children: React.createElement(IconGeneral$BtsCore.make, {
                                              src: Icons$BtsCore.homeBlack
                                            })
                                      }), React.createElement(GridItem$BtsCore.make, {
                                        top: "0",
                                        right: "0",
                                        bottom: "0",
                                        left: "0",
                                        enterBackgroundColor: "transparent",
                                        backgroundColor: "transparent",
                                        xs: "auto",
                                        children: React.createElement(Typography$BtsCore.make, {
                                              variant: "subheading",
                                              children: React.createElement(ReactIntl.FormattedMessage, {
                                                    id: "Path.home",
                                                    defaultMessage: "Home"
                                                  })
                                            })
                                      }))
                            })
                      })
                }), React.createElement("main", {
                  className: "tubelayout",
                  style: Object.assign(({}), OutSide$BtsCore.mainTube, {
                        bottom: bottoms(bottom),
                        right: "0px",
                        transition: "left 195ms cubic-bezier(0.4, 0, 0.6, 1) 0ms, right 195ms cubic-bezier(0.4, 0, 0.6, 1) 0ms"
                      })
                }, React.createElement("div", {
                      style: Together$BtsCore.divScrollbar
                    }, React.createElement("div", {
                          style: Object.assign(({}), Together$BtsCore.marginAuto, {
                                maxWidth: widths(width),
                                width: widths(width),
                                flexBasis: widths(width)
                              })
                        }, Setting$BtsCore.disabledObjects(error) ? React.createElement("div", {
                                style: OutSide$BtsCore.errorForm
                              }, React.createElement(Typography$BtsCore.make, {
                                    variant: "tile",
                                    color: "rgba(255,0,0,0.8)",
                                    fontSize: "x-large",
                                    noWrap: true,
                                    children: "UNDEFINED THIS PAGE"
                                  })) : children))), React.createElement(BackgroundBoard$BtsCore.make, {
                  showBackground: state.showOpen,
                  backgroundColor: "rgba(0,0,0,0.2)",
                  onClick: showOpen
                }));
}

var make = NewYoutube;

export {
  reducer ,
  initialState ,
  widths ,
  bottoms ,
  make ,
  
}
/*  Not a pure module */
