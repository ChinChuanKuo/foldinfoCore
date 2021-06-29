// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as Path$BtsCore from "../../features/Path.bs.js";
import * as Icons$BtsCore from "../../material-ui/icon/Icons.bs.js";
import * as List_$BtsCore from "../../material-ui/core/List_/List_.bs.js";
import * as Avatar$BtsCore from "../../material-ui/core/Avatar/Avatar.bs.js";
import * as Drawer$BtsCore from "../../material-ui/core/Drawer/Drawer.bs.js";
import * as Divider$BtsCore from "../../material-ui/core/Divider/Divider.bs.js";
import * as ListIcon$BtsCore from "../../material-ui/core/ListItem/ListIcon.bs.js";
import * as ReasonReactRouter from "reason-react/src/ReasonReactRouter.bs.js";
import * as IconButton$BtsCore from "../../material-ui/core/IconButton/IconButton.bs.js";
import * as Typography$BtsCore from "../../material-ui/core/Typography/Typography.bs.js";
import * as IconGeneral$BtsCore from "../../material-ui/core/IconStyle/IconGeneral.bs.js";
import * as ObjectFormat$BtsCore from "../../controls/ObjectFormat.bs.js";

function Bookmarks(Props) {
  return React.createElement(Drawer$BtsCore.make, {
              style: {
                borderRight: "0",
                overflow: "hidden",
                whiteSpace: "nowrap",
                transition: "width 225ms cubic-bezier(0.4, 0, 0.6, 1) 0ms"
              },
              top: "60",
              left: "0",
              width: "100vw",
              height: "64",
              zIndex: "1000",
              location: "left",
              children: null
            }, React.createElement(List_$BtsCore.make, {
                  top: "16",
                  children: null
                }, React.createElement(ListIcon$BtsCore.make, {
                      style: {
                        height: "52px"
                      },
                      enterBackgroundColor: "rgba(0,0,0,0.12)",
                      downBackgroundColor: "rgba(0,0,0,0.06)",
                      topLeft: "20",
                      topRight: "20",
                      bottomRight: "20",
                      bottomLeft: "20",
                      right: "0",
                      left: "0",
                      onClick: (function (param) {
                          return ReasonReactRouter.push(Path$BtsCore.homePath);
                        }),
                      children: /* tuple */[
                        React.createElement(Avatar$BtsCore.make, {
                              top: "0",
                              right: "0",
                              bottom: "0",
                              left: "0",
                              color: "#909090",
                              backgroundColor: "rgba(0,0,0,0.08)",
                              children: ObjectFormat$BtsCore.checkObjects(localStorage.getItem("name"))
                            }),
                        React.createElement(Typography$BtsCore.make, {
                              variant: "subheading",
                              children: ObjectFormat$BtsCore.checkObjects(localStorage.getItem("allname"))
                            })
                      ]
                    }), React.createElement(ListIcon$BtsCore.make, {
                      style: {
                        height: "52px"
                      },
                      enterBackgroundColor: "rgba(0,0,0,0.12)",
                      downBackgroundColor: "rgba(0,0,0,0.06)",
                      topLeft: "20",
                      topRight: "20",
                      bottomRight: "20",
                      bottomLeft: "20",
                      right: "0",
                      left: "0",
                      onClick: (function (param) {
                          return ReasonReactRouter.push(Path$BtsCore.homePath);
                        }),
                      children: /* tuple */[
                        React.createElement(IconButton$BtsCore.make, {
                              backgroundColor: "rgba(0,0,0,0.08)",
                              children: React.createElement(IconGeneral$BtsCore.make, {
                                    src: Icons$BtsCore.transmissionBlack
                                  })
                            }),
                        React.createElement(Typography$BtsCore.make, {
                              variant: "subheading",
                              children: "品異單"
                            })
                      ]
                    }), React.createElement(ListIcon$BtsCore.make, {
                      style: {
                        height: "52px"
                      },
                      enterBackgroundColor: "rgba(0,0,0,0.12)",
                      downBackgroundColor: "rgba(0,0,0,0.06)",
                      topLeft: "20",
                      topRight: "20",
                      bottomRight: "20",
                      bottomLeft: "20",
                      right: "0",
                      left: "0",
                      onClick: (function (param) {
                          return ReasonReactRouter.push(Path$BtsCore.insidePath);
                        }),
                      children: /* tuple */[
                        React.createElement(IconButton$BtsCore.make, {
                              backgroundColor: "rgba(0,0,0,0.08)",
                              children: React.createElement(IconGeneral$BtsCore.make, {
                                    src: Icons$BtsCore.factoryBlack
                                  })
                            }),
                        React.createElement(Typography$BtsCore.make, {
                              variant: "subheading",
                              children: "工廠內部通告"
                            })
                      ]
                    }), React.createElement(ListIcon$BtsCore.make, {
                      style: {
                        height: "52px"
                      },
                      enterBackgroundColor: "rgba(0,0,0,0.12)",
                      downBackgroundColor: "rgba(0,0,0,0.06)",
                      topLeft: "20",
                      topRight: "20",
                      bottomRight: "20",
                      bottomLeft: "20",
                      right: "0",
                      left: "0",
                      onClick: (function (param) {
                          return ReasonReactRouter.push(Path$BtsCore.isoFilePath);
                        }),
                      children: /* tuple */[
                        React.createElement(IconButton$BtsCore.make, {
                              backgroundColor: "rgba(0,0,0,0.08)",
                              children: React.createElement(IconGeneral$BtsCore.make, {
                                    src: Icons$BtsCore.fileCopyBlack
                                  })
                            }),
                        React.createElement(Typography$BtsCore.make, {
                              variant: "subheading",
                              children: "ISO三階文件"
                            })
                      ]
                    }), React.createElement(ListIcon$BtsCore.make, {
                      style: {
                        height: "52px"
                      },
                      enterBackgroundColor: "rgba(0,0,0,0.12)",
                      downBackgroundColor: "rgba(0,0,0,0.06)",
                      topLeft: "20",
                      topRight: "20",
                      bottomRight: "20",
                      bottomLeft: "20",
                      right: "0",
                      left: "0",
                      onClick: (function (param) {
                          return ReasonReactRouter.push(Path$BtsCore.productPath);
                        }),
                      children: /* tuple */[
                        React.createElement(IconButton$BtsCore.make, {
                              backgroundColor: "rgba(0,0,0,0.08)",
                              children: React.createElement(IconGeneral$BtsCore.make, {
                                    src: Icons$BtsCore.homeBlack
                                  })
                            }),
                        React.createElement(Typography$BtsCore.make, {
                              variant: "subheading",
                              children: "生產注意事項"
                            })
                      ]
                    })), React.createElement(Divider$BtsCore.make, { }), React.createElement(List_$BtsCore.make, {
                  top: "16",
                  children: null
                }, React.createElement(ListIcon$BtsCore.make, {
                      style: {
                        height: "52px"
                      },
                      enterBackgroundColor: "rgba(0,0,0,0.12)",
                      downBackgroundColor: "rgba(0,0,0,0.06)",
                      topLeft: "20",
                      topRight: "20",
                      bottomRight: "20",
                      bottomLeft: "20",
                      right: "0",
                      left: "0",
                      onClick: (function (param) {
                          return ReasonReactRouter.push(Path$BtsCore.signlistPath);
                        }),
                      children: /* tuple */[
                        React.createElement(IconButton$BtsCore.make, {
                              backgroundColor: "rgba(0,0,0,0.08)",
                              children: React.createElement(IconGeneral$BtsCore.make, {
                                    src: Icons$BtsCore.homeBlack
                                  })
                            }),
                        React.createElement(Typography$BtsCore.make, {
                              variant: "subheading",
                              children: "簽核總列表"
                            })
                      ]
                    }), React.createElement(ListIcon$BtsCore.make, {
                      style: {
                        height: "52px"
                      },
                      enterBackgroundColor: "rgba(0,0,0,0.12)",
                      downBackgroundColor: "rgba(0,0,0,0.06)",
                      topLeft: "20",
                      topRight: "20",
                      bottomRight: "20",
                      bottomLeft: "20",
                      right: "0",
                      left: "0",
                      onClick: (function (param) {
                          return ReasonReactRouter.push(Path$BtsCore.mailistRPath);
                        }),
                      children: /* tuple */[
                        React.createElement(IconButton$BtsCore.make, {
                              backgroundColor: "rgba(0,0,0,0.08)",
                              children: React.createElement(IconGeneral$BtsCore.make, {
                                    src: Icons$BtsCore.mailBlack
                                  })
                            }),
                        React.createElement(Typography$BtsCore.make, {
                              variant: "subheading",
                              children: "MAIL通知列表"
                            })
                      ]
                    }), React.createElement(ListIcon$BtsCore.make, {
                      style: {
                        height: "52px"
                      },
                      enterBackgroundColor: "rgba(0,0,0,0.12)",
                      downBackgroundColor: "rgba(0,0,0,0.06)",
                      topLeft: "20",
                      topRight: "20",
                      bottomRight: "20",
                      bottomLeft: "20",
                      right: "0",
                      left: "0",
                      onClick: (function (param) {
                          return ReasonReactRouter.push(Path$BtsCore.sendistFPath);
                        }),
                      children: /* tuple */[
                        React.createElement(IconButton$BtsCore.make, {
                              backgroundColor: "rgba(0,0,0,0.08)",
                              children: React.createElement(IconGeneral$BtsCore.make, {
                                    src: Icons$BtsCore.mailBlack
                                  })
                            }),
                        React.createElement(Typography$BtsCore.make, {
                              variant: "subheading",
                              children: "SEND列表"
                            })
                      ]
                    })));
}

var make = Bookmarks;

export {
  make ,
  
}
/* react Not a pure module */