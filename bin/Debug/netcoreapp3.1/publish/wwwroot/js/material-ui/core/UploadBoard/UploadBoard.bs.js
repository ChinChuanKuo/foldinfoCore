// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as Setting$BtsCore from "../../../setting/Setting.bs.js";

((require('../../scss/UploadBoard/uploadBoard.scss')));

function backgroundColors(backgroundColor) {
  if (backgroundColor !== undefined) {
    return backgroundColor;
  } else {
    return "rgba(0,0,0,0.8)";
  }
}

function opacitys(showUpload) {
  if (showUpload) {
    return "1";
  } else {
    return "0";
  }
}

function visibilitys(showUpload) {
  if (showUpload) {
    return "visible";
  } else {
    return "hidden";
  }
}

function boardShows(showUpload) {
  if (showUpload) {
    return "uploadDropModal-2kTwbc";
  } else {
    return "uploadDropModal";
  }
}

function positionColors(positionColor) {
  if (positionColor !== undefined) {
    return positionColor;
  } else {
    return "rgba(255,0,0,.6)";
  }
}

function positionShows(showUpload) {
  if (showUpload) {
    return "bgScale-1otPtc";
  } else {
    return "bgScale";
  }
}

function linearShows(showUpload) {
  if (showUpload) {
    return "inner-3nWsbo";
  } else {
    return "inner-test";
  }
}

function iconsBoardShows(showUpload) {
  if (showUpload) {
    return "icons-1w691d";
  } else {
    return "icons-test";
  }
}

function titleBoardShows(showUpload) {
  if (showUpload) {
    return "tile-2Vtl4y";
  } else {
    return "tile-test";
  }
}

function instructionsBoardShows(showUpload) {
  if (showUpload) {
    return "instructions-2Du9gG";
  } else {
    return "instuctions-test";
  }
}

function UploadBoard(Props) {
  var style = Props.style;
  var showUpload = Props.showUpload;
  var backgroundColor = Props.backgroundColor;
  var positionColor = Props.positionColor;
  var children = Props.children;
  var showUpload$1 = Setting$BtsCore.disabledObjects(showUpload);
  var showUpload$2 = Setting$BtsCore.disabledObjects(showUpload);
  var showUpload$3 = Setting$BtsCore.disabledObjects(showUpload);
  var showUpload$4 = Setting$BtsCore.disabledObjects(showUpload);
  var showUpload$5 = Setting$BtsCore.disabledObjects(showUpload);
  var showUpload$6 = Setting$BtsCore.disabledObjects(showUpload);
  var showUpload$7 = Setting$BtsCore.disabledObjects(showUpload);
  var showUpload$8 = Setting$BtsCore.disabledObjects(showUpload);
  return React.createElement("div", {
              className: "uploadArea-3QgLtW",
              style: Object.assign(({}), {
                    backgroundColor: backgroundColor !== undefined ? backgroundColor : "rgba(0,0,0,0.8)",
                    visibility: showUpload$1 ? "visible" : "hidden",
                    opacity: showUpload$2 ? "1" : "0"
                  }, Setting$BtsCore.styleObjects(style))
            }, React.createElement("div", {
                  className: showUpload$3 ? "uploadDropModal-2kTwbc" : "uploadDropModal"
                }, React.createElement("div", {
                      className: showUpload$4 ? "bgScale-1otPtc" : "bgScale",
                      style: {
                        backgroundColor: positionColor !== undefined ? positionColor : "rgba(255,0,0,.6)"
                      }
                    }), React.createElement("div", {
                      className: showUpload$5 ? "inner-3nWsbo" : "inner-test"
                    }, React.createElement("div", {
                          className: showUpload$6 ? "icons-1w691d" : "icons-test"
                        }, children[0]), React.createElement("div", {
                          className: showUpload$7 ? "tile-2Vtl4y" : "tile-test"
                        }, "Drop & Down"), React.createElement("div", {
                          className: showUpload$8 ? "instructions-2Du9gG" : "instuctions-test"
                        }, children[1]))));
}

var make = UploadBoard;

export {
  backgroundColors ,
  opacitys ,
  visibilitys ,
  boardShows ,
  positionColors ,
  positionShows ,
  linearShows ,
  iconsBoardShows ,
  titleBoardShows ,
  instructionsBoardShows ,
  make ,
  
}
/*  Not a pure module */