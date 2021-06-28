// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as Setting$BtsCore from "../../../setting/Setting.bs.js";

((require('../../scss/Dialog/dialogAnimationBottom.scss')));

function visibilitys(showAnimation) {
  if (showAnimation) {
    return "";
  } else {
    return "hidden";
  }
}

function opacitys(showAnimation) {
  if (showAnimation) {
    return "1";
  } else {
    return "0";
  }
}

function outtransitions(showAnimation) {
  if (showAnimation) {
    return "opacity 225ms cubic-bezier(0.4, 0, 0.2, 1) 0ms";
  } else {
    return "opacity 195ms cubic-bezier(0.4, 0, 0.2, 1) 0ms";
  }
}

function transforms(showAnimation) {
  if (showAnimation) {
    return "translate(0px, 0px)";
  } else {
    return "translateX(100vh) translateX(0px)";
  }
}

function transitions(showAnimation) {
  if (showAnimation) {
    return "transform 225ms cubic-bezier(0, 0, 0.2, 1) 0ms";
  } else {
    return "";
  }
}

function backgroundColors(backgroundColor) {
  if (backgroundColor !== undefined) {
    return backgroundColor;
  } else {
    return "rgba(255,255,255,1)";
  }
}

function widths(width) {
  if (width !== undefined) {
    return width;
  } else {
    return "600px";
  }
}

function DialogAnimationRight(Props) {
  var showAnimation = Props.showAnimation;
  var style = Props.style;
  var backgroundColor = Props.backgroundColor;
  var width = Props.width;
  var maxWidth = Props.maxWidth;
  var children = Props.children;
  var showAnimation$1 = Setting$BtsCore.disabledObjects(showAnimation);
  var showAnimation$2 = Setting$BtsCore.disabledObjects(showAnimation);
  var showAnimation$3 = Setting$BtsCore.disabledObjects(showAnimation);
  var showAnimation$4 = Setting$BtsCore.disabledObjects(showAnimation);
  var showAnimation$5 = Setting$BtsCore.disabledObjects(showAnimation);
  return React.createElement("div", {
              className: "jupvbsj",
              role: "dialog",
              style: {
                backgroundColor: "rgba(0,0,0,0.54)",
                visibility: showAnimation$1 ? "" : "hidden"
              }
            }, React.createElement("div", {
                  className: "j1hwasmh",
                  style: {
                    opacity: showAnimation$2 ? "1" : "0",
                    transition: showAnimation$3 ? "opacity 225ms cubic-bezier(0.4, 0, 0.2, 1) 0ms" : "opacity 195ms cubic-bezier(0.4, 0, 0.2, 1) 0ms"
                  }
                }), React.createElement("div", {
                  className: "jlbc39s j1olfzzh",
                  style: {
                    transition: showAnimation$4 ? "transform 225ms cubic-bezier(0, 0, 0.2, 1) 0ms" : "",
                    transform: showAnimation$5 ? "translate(0px, 0px)" : "translateX(100vh) translateX(0px)"
                  }
                }, React.createElement("div", {
                      className: "j1iocy8x ji1kkbr j116tjkx j1bnredm jrkcwvt",
                      style: Object.assign(({}), {
                            backgroundColor: backgroundColor !== undefined ? backgroundColor : "rgba(255,255,255,1)",
                            maxWidth: maxWidth !== undefined ? maxWidth : "600px",
                            width: width !== undefined ? width : "600px"
                          }, Setting$BtsCore.styleObjects(style))
                    }, children)));
}

var make = DialogAnimationRight;

export {
  visibilitys ,
  opacitys ,
  outtransitions ,
  transforms ,
  transitions ,
  backgroundColors ,
  widths ,
  make ,
  
}
/*  Not a pure module */
