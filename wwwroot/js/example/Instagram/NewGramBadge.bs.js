// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReactIntl from "react-intl";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Menu$BtsCore from "../../material-ui/core/Menu/Menu.bs.js";
import * as Icons$BtsCore from "../../material-ui/icon/Icons.bs.js";
import * as Avatar$BtsCore from "../../material-ui/core/Avatar/Avatar.bs.js";
import * as OutSide$BtsCore from "../../styles/OutSide/OutSide.bs.js";
import * as Setting$BtsCore from "../../setting/Setting.bs.js";
import * as GridItem$BtsCore from "../../material-ui/core/Grid/GridItem.bs.js";
import * as IconAction$BtsCore from "../../material-ui/core/IconStyle/IconAction.bs.js";
import * as IconButton$BtsCore from "../../material-ui/core/IconButton/IconButton.bs.js";
import * as Typography$BtsCore from "../../material-ui/core/Typography/Typography.bs.js";
import * as GridContainer$BtsCore from "../../material-ui/core/Grid/GridContainer.bs.js";
import * as BackgroundBoard$BtsCore from "../Boards/BackgroundBoard.bs.js";

function reducer(state, action) {
  return {
          showBadge: !state.showBadge
        };
}

var initialState = {
  showBadge: false
};

function transforms(showAnimation) {
  if (showAnimation) {
    return "translate(0px, 0px)";
  } else {
    return "translateX(200vh) translateX(0px)";
  }
}

function boardstyles(showAnimation) {
  return {
          position: "absolute",
          transition: "transform 225ms cubic-bezier(0, 0, 0.2, 1) 0ms",
          transform: showAnimation ? "translate(0px, 0px)" : "translateX(200vh) translateX(0px)"
        };
}

function NewGramBadge(Props) {
  var maxHeight = Props.maxHeight;
  var badge = Props.badge;
  var clickShow = Props.clickShow;
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
  var showBadge = React.useCallback((function (param) {
          return Curry._1(dispatch, /* ShowBadge */0);
        }));
  var tmp = {
    showBackground: true,
    backgroundColor: "transparent"
  };
  if (clickShow !== undefined) {
    tmp.onClick = Caml_option.valFromOption(clickShow);
  }
  return React.createElement(React.Fragment, undefined, React.createElement("div", {
                  style: Object.assign(({}), OutSide$BtsCore.menuOutSide, {
                        marginLeft: "-423px",
                        maxHeight: maxHeight,
                        maxWidth: "500px",
                        minWidth: "500px",
                        top: "54px",
                        width: "500px",
                        borderRadius: "10px"
                      })
                }, React.createElement(GridItem$BtsCore.make, {
                      style: boardstyles(!state.showBadge),
                      top: "0",
                      right: "0",
                      bottom: "0",
                      left: "0",
                      width: "100%",
                      enterBorderWidth: "0",
                      borderWidth: "0",
                      enterBorderRadius: "6",
                      borderRadius: "6",
                      xs: "12",
                      children: React.createElement(Menu$BtsCore.make, {
                            top: "12",
                            right: "16",
                            bottom: "13",
                            left: "16",
                            children: React.createElement(GridContainer$BtsCore.make, {
                                  backgroundColor: "transparent",
                                  direction: "column",
                                  justify: "start",
                                  alignItem: "stretch",
                                  children: null
                                }, React.createElement(GridItem$BtsCore.make, {
                                      top: "0",
                                      right: "0",
                                      bottom: "0",
                                      left: "0",
                                      cursor: "pointer",
                                      enterBackgroundColor: "transparent",
                                      backgroundColor: "transparent",
                                      xs: "auto",
                                      children: React.createElement("div", {
                                            onClick: showBadge
                                          }, React.createElement(GridContainer$BtsCore.make, {
                                                backgroundColor: "transparent",
                                                direction: "row",
                                                justify: "between",
                                                alignItem: "center",
                                                children: null
                                              }, React.createElement(GridItem$BtsCore.make, {
                                                    top: "0",
                                                    right: "0",
                                                    bottom: "0",
                                                    left: "0",
                                                    enterBackgroundColor: "transparent",
                                                    backgroundColor: "transparent",
                                                    xs: "no",
                                                    children: React.createElement(Avatar$BtsCore.make, {
                                                          style: {
                                                            height: "32px",
                                                            width: "32px"
                                                          },
                                                          top: "0",
                                                          right: "0",
                                                          bottom: "0",
                                                          left: "0",
                                                          enterBorderColor: "transparent",
                                                          downBorderColor: "transparent",
                                                          children: Setting$BtsCore.stringObjects(badge)
                                                        })
                                                  }), React.createElement(GridItem$BtsCore.make, {
                                                    top: "0",
                                                    bottom: "0",
                                                    enterBackgroundColor: "transparent",
                                                    backgroundColor: "transparent",
                                                    xs: "auto",
                                                    children: React.createElement(GridContainer$BtsCore.make, {
                                                          direction: "column",
                                                          justify: "start",
                                                          alignItem: "stretch",
                                                          children: null
                                                        }, React.createElement(GridItem$BtsCore.make, {
                                                              top: "0",
                                                              right: "0",
                                                              bottom: "0",
                                                              left: "0",
                                                              xs: "auto",
                                                              children: React.createElement(Typography$BtsCore.make, {
                                                                    variant: "subtitle2",
                                                                    fontWeight: "700",
                                                                    lineHeight: "1",
                                                                    children: React.createElement(ReactIntl.FormattedMessage, {
                                                                          id: "Gram.track",
                                                                          defaultMessage: "Track"
                                                                        })
                                                                  })
                                                            }), React.createElement(GridItem$BtsCore.make, {
                                                              top: "0",
                                                              right: "0",
                                                              bottom: "0",
                                                              left: "0",
                                                              xs: "auto",
                                                              children: React.createElement(Typography$BtsCore.make, {
                                                                    variant: "subtitle2",
                                                                    color: "rgba(142,142,142,1)",
                                                                    lineHeight: "1",
                                                                    children: React.createElement(ReactIntl.FormattedMessage, {
                                                                          id: "Gram.require",
                                                                          defaultMessage: "Require"
                                                                        })
                                                                  })
                                                            }))
                                                  }), React.createElement(GridItem$BtsCore.make, {
                                                    top: "0",
                                                    right: "0",
                                                    bottom: "0",
                                                    left: "0",
                                                    enterBackgroundColor: "transparent",
                                                    backgroundColor: "transparent",
                                                    xs: "no",
                                                    children: React.createElement(IconButton$BtsCore.make, {
                                                          enterBackgroundColor: "transparent",
                                                          downBackgroundColor: "transparent",
                                                          padding: "6",
                                                          children: React.createElement(IconAction$BtsCore.make, {
                                                                width: "15",
                                                                height: "15",
                                                                animation: "leftRight",
                                                                src: Icons$BtsCore.arrowForwardIosBlack
                                                              })
                                                        })
                                                  })))
                                    }), React.createElement(GridItem$BtsCore.make, {
                                      right: "0",
                                      left: "0",
                                      enterBackgroundColor: "transparent",
                                      backgroundColor: "transparent",
                                      xs: "auto",
                                      children: null
                                    }))
                          })
                    }), React.createElement(GridItem$BtsCore.make, {
                      style: boardstyles(state.showBadge),
                      top: "0",
                      right: "0",
                      bottom: "0",
                      left: "0",
                      width: "100%",
                      enterBorderWidth: "0",
                      borderWidth: "0",
                      enterBorderRadius: "6",
                      borderRadius: "6",
                      xs: "12",
                      children: React.createElement(Menu$BtsCore.make, {
                            top: "12",
                            right: "16",
                            bottom: "13",
                            left: "16",
                            children: null
                          })
                    })), React.createElement(BackgroundBoard$BtsCore.make, tmp));
}

var make = NewGramBadge;

export {
  reducer ,
  initialState ,
  transforms ,
  boardstyles ,
  make ,
  
}
/* react Not a pure module */
