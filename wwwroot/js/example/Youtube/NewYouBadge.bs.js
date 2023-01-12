// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as $$Array from "bs-platform/lib/es6/array.js";
import * as React from "react";
import * as ReactIntl from "react-intl";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Menu$BtsCore from "../../material-ui/core/Menu/Menu.bs.js";
import * as Path$BtsCore from "../../features/Path.bs.js";
import * as Icons$BtsCore from "../../material-ui/icon/Icons.bs.js";
import * as Avatar$BtsCore from "../../material-ui/core/Avatar/Avatar.bs.js";
import * as Divider$BtsCore from "../../material-ui/core/Divider/Divider.bs.js";
import * as OutSide$BtsCore from "../../styles/OutSide/OutSide.bs.js";
import * as Setting$BtsCore from "../../setting/Setting.bs.js";
import * as GridItem$BtsCore from "../../material-ui/core/Grid/GridItem.bs.js";
import * as MenuItem$BtsCore from "../../material-ui/core/MenuItem/MenuItem.bs.js";
import * as ReasonReactRouter from "reason-react/src/ReasonReactRouter.bs.js";
import * as IconButton$BtsCore from "../../material-ui/core/IconButton/IconButton.bs.js";
import * as Typography$BtsCore from "../../material-ui/core/Typography/Typography.bs.js";
import * as IconGeneral$BtsCore from "../../material-ui/core/IconStyle/IconGeneral.bs.js";
import * as GridContainer$BtsCore from "../../material-ui/core/Grid/GridContainer.bs.js";
import * as BackgroundBoard$BtsCore from "../Boards/BackgroundBoard.bs.js";
import * as ProgressCircular$BtsCore from "../../material-ui/core/Progress/ProgressCircular.bs.js";

function NewYouBadge(Props) {
  var maxHeight = Props.maxHeight;
  var beforeLoad = Props.beforeLoad;
  var showItem = Props.showItem;
  var items = Props.items;
  var clickShow = Props.clickShow;
  var match = Setting$BtsCore.disabledObjects(beforeLoad);
  var match$1 = Setting$BtsCore.disabledObjects(showItem);
  var tmp = {
    showBackground: true,
    backgroundColor: "transparent"
  };
  if (clickShow !== undefined) {
    tmp.onClick = Caml_option.valFromOption(clickShow);
  }
  return React.createElement(React.Fragment, undefined, React.createElement("div", {
                  style: Object.assign(({}), OutSide$BtsCore.menuOutSide, {
                        maxHeight: maxHeight,
                        maxWidth: "480px",
                        minWidth: "480px",
                        right: "80px",
                        width: "480px"
                      })
                }, React.createElement(Menu$BtsCore.make, {
                      topLeft: "12",
                      topRight: "12",
                      bottomRight: "12",
                      bottomLeft: "12",
                      children: React.createElement(GridContainer$BtsCore.make, {
                            backgroundColor: "transparent",
                            direction: "column",
                            justify: "center",
                            alignItem: "stretch",
                            children: null
                          }, React.createElement(GridItem$BtsCore.make, {
                                top: "0",
                                right: "0",
                                bottom: "0",
                                left: "0",
                                enterBackgroundColor: "transparent",
                                backgroundColor: "transparent",
                                xs: "auto",
                                children: React.createElement(MenuItem$BtsCore.make, {
                                      top: "0",
                                      right: "6",
                                      bottom: "0",
                                      left: "6",
                                      enterBackgroundColor: "rgba(255,255,255,1)",
                                      downBackgroundColor: "rgba(255,255,255,1)",
                                      backgroundColor: "rgba(255,255,255,1)",
                                      topLeft: "12",
                                      topRight: "12",
                                      bottomRight: "12",
                                      bottomLeft: "12",
                                      onClick: (function (param) {
                                          return ReasonReactRouter.push(Path$BtsCore.homePath);
                                        }),
                                      children: React.createElement(GridContainer$BtsCore.make, {
                                            backgroundColor: "transparent",
                                            direction: "row",
                                            justify: "between",
                                            alignItem: "center",
                                            children: null
                                          }, React.createElement(GridItem$BtsCore.make, {
                                                top: "0",
                                                right: "0",
                                                bottom: "0",
                                                enterBackgroundColor: "transparent",
                                                backgroundColor: "transparent",
                                                xs: "no",
                                                children: React.createElement(Typography$BtsCore.make, {
                                                      variant: "tile",
                                                      children: React.createElement(ReactIntl.FormattedMessage, {
                                                            id: "Action.notice",
                                                            defaultMessage: "Notice"
                                                          })
                                                    })
                                              }), React.createElement(GridItem$BtsCore.make, {
                                                top: "0",
                                                right: "0",
                                                bottom: "0",
                                                left: "0",
                                                enterBackgroundColor: "transparent",
                                                backgroundColor: "transparent",
                                                xs: "no",
                                                children: React.createElement(IconButton$BtsCore.make, {
                                                      padding: "6",
                                                      children: React.createElement(IconGeneral$BtsCore.make, {
                                                            width: "28",
                                                            height: "28",
                                                            src: Icons$BtsCore.settingsApplicationsBlack
                                                          })
                                                    })
                                              }))
                                    })
                              }), React.createElement(GridItem$BtsCore.make, {
                                top: "0",
                                right: "0",
                                bottom: "0",
                                left: "0",
                                xs: "auto",
                                children: React.createElement(Divider$BtsCore.make, { })
                              }), match ? React.createElement(GridItem$BtsCore.make, {
                                  xs: "auto",
                                  children: React.createElement(GridContainer$BtsCore.make, {
                                        direction: "row",
                                        justify: "center",
                                        alignItem: "center",
                                        children: React.createElement(GridItem$BtsCore.make, {
                                              top: "0",
                                              right: "0",
                                              bottom: "0",
                                              left: "0",
                                              xs: "no",
                                              children: React.createElement(ProgressCircular$BtsCore.make, {
                                                    size: "80",
                                                    color: "rgba(0,0,0,0.08)"
                                                  })
                                            })
                                      })
                                }) : (
                              match$1 ? $$Array.map((function (item) {
                                        return React.createElement(GridItem$BtsCore.make, {
                                                    top: "0",
                                                    right: "0",
                                                    bottom: "0",
                                                    left: "0",
                                                    enterBackgroundColor: "transparent",
                                                    backgroundColor: "transparent",
                                                    xs: "auto",
                                                    children: React.createElement(MenuItem$BtsCore.make, {
                                                          enterBackgroundColor: "rgba(0,0,0,0.06)",
                                                          downBackgroundColor: "rgba(0,0,0,0.08)",
                                                          topLeft: "12",
                                                          topRight: "12",
                                                          bottomRight: "12",
                                                          bottomLeft: "12",
                                                          onClick: (function (param) {
                                                              return ReasonReactRouter.push(item.link);
                                                            }),
                                                          children: React.createElement(GridContainer$BtsCore.make, {
                                                                backgroundColor: "transparent",
                                                                direction: "row",
                                                                justify: "start",
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
                                                                            height: "48px",
                                                                            width: "48px"
                                                                          },
                                                                          top: "0",
                                                                          right: "0",
                                                                          bottom: "0",
                                                                          left: "0",
                                                                          enterBorderColor: "transparent",
                                                                          downBorderColor: "transparent",
                                                                          onClick: (function (param) {
                                                                              return ReasonReactRouter.push(item.link);
                                                                            }),
                                                                          children: React.createElement(Typography$BtsCore.make, {
                                                                                variant: "tile",
                                                                                children: item.name
                                                                              })
                                                                        })
                                                                  }), React.createElement(GridItem$BtsCore.make, {
                                                                    top: "0",
                                                                    right: "0",
                                                                    bottom: "0",
                                                                    enterBackgroundColor: "transparent",
                                                                    backgroundColor: "transparent",
                                                                    xs: "auto",
                                                                    children: React.createElement(GridContainer$BtsCore.make, {
                                                                          backgroundColor: "transparent",
                                                                          direction: "column",
                                                                          justify: "center",
                                                                          alignItem: "stretch",
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
                                                                                    children: item.value
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
                                                                                    variant: "subtitle2",
                                                                                    children: item.datetime
                                                                                  })
                                                                            }))
                                                                  }))
                                                        })
                                                  });
                                      }), Setting$BtsCore.arrayObjects(items)) : React.createElement(GridItem$BtsCore.make, {
                                      top: "18",
                                      right: "18",
                                      bottom: "18",
                                      left: "32",
                                      xs: "auto",
                                      children: React.createElement(Typography$BtsCore.make, {
                                            variant: "tile",
                                            noWrap: true,
                                            children: "undefined this database"
                                          })
                                    })
                            ))
                    })), React.createElement(BackgroundBoard$BtsCore.make, tmp));
}

var make = NewYouBadge;

export {
  make ,
  
}
/* react Not a pure module */
