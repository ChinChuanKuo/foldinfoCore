// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Block from "bs-platform/lib/es6/block.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Setting$BtsCore from "../../../setting/Setting.bs.js";

((require('../../scss/Paper/paper.scss')));

function reducer(state, action) {
  if (action.tag) {
    return {
            enter: state.enter,
            down: action[0]
          };
  }
  var enter = action[0];
  return {
          enter: enter,
          down: enter ? state.down : false
        };
}

var initialState = {
  enter: false,
  down: false
};

function paddingTopBottoms(topBottom) {
  if (topBottom !== undefined) {
    return topBottom + "px";
  } else {
    return "16px";
  }
}

function otherBackgroundColors(otherBackgroundColor) {
  if (otherBackgroundColor !== undefined) {
    return otherBackgroundColor;
  } else {
    return "rgba(255,255,255,1)";
  }
}

function backgroundColors(backgroundColor) {
  if (backgroundColor !== undefined) {
    return backgroundColor;
  } else {
    return "rgba(255,255,255,1)";
  }
}

function boxShadows(boxShadow) {
  if (boxShadow !== undefined) {
    return boxShadow;
  } else {
    return "0px 1px 10px 0px rgba(0, 0, 0, 0.2), 0px 1px 1px 0px rgba(0, 0, 0, 0.14), 0px 2px 1px -1px rgba(0, 0, 0, 0.12)";
  }
}

function borderRadiuses(borderRadius) {
  if (borderRadius !== undefined) {
    return borderRadius + "px";
  } else {
    return "4px";
  }
}

function classes(className) {
  var basic = "j1q4pwjm";
  if (className !== undefined) {
    return basic + (" " + className);
  } else {
    return basic;
  }
}

function Paper(Props) {
  var style = Props.style;
  var top = Props.top;
  var bottom = Props.bottom;
  var enterBackgroundColor = Props.enterBackgroundColor;
  var downBackgroundColor = Props.downBackgroundColor;
  var backgroundColor = Props.backgroundColor;
  var enterBoxShadow = Props.enterBoxShadow;
  var downBoxShadow = Props.downBoxShadow;
  var boxShadow = Props.boxShadow;
  var enterBorderRadius = Props.enterBorderRadius;
  var downBorderRadius = Props.downBorderRadius;
  var borderRadius = Props.borderRadius;
  var className = Props.className;
  var onClick = Props.onClick;
  var children = Props.children;
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
  var match$1 = state.enter;
  var match$2 = state.down;
  var match$3 = state.enter;
  var match$4 = state.down;
  var match$5 = state.enter;
  var match$6 = state.down;
  var tmp = {
    className: classes(className),
    style: Object.assign(({}), {
          backgroundColor: match$1 ? (
              match$2 ? (
                  downBackgroundColor !== undefined ? downBackgroundColor : "rgba(255,255,255,1)"
                ) : (
                  enterBackgroundColor !== undefined ? enterBackgroundColor : "rgba(255,255,255,1)"
                )
            ) : (
              backgroundColor !== undefined ? backgroundColor : "rgba(255,255,255,1)"
            ),
          paddingTop: paddingTopBottoms(top),
          paddingBottom: paddingTopBottoms(bottom),
          borderRadius: match$3 ? (
              match$4 ? borderRadiuses(downBorderRadius) : borderRadiuses(enterBorderRadius)
            ) : borderRadiuses(borderRadius),
          boxShadow: match$5 ? (
              match$6 ? (
                  downBoxShadow !== undefined ? downBoxShadow : "0px 1px 10px 0px rgba(0, 0, 0, 0.2), 0px 1px 1px 0px rgba(0, 0, 0, 0.14), 0px 2px 1px -1px rgba(0, 0, 0, 0.12)"
                ) : (
                  enterBoxShadow !== undefined ? enterBoxShadow : "0px 1px 10px 0px rgba(0, 0, 0, 0.2), 0px 1px 1px 0px rgba(0, 0, 0, 0.14), 0px 2px 1px -1px rgba(0, 0, 0, 0.12)"
                )
            ) : (
              boxShadow !== undefined ? boxShadow : "0px 1px 10px 0px rgba(0, 0, 0, 0.2), 0px 1px 1px 0px rgba(0, 0, 0, 0.14), 0px 2px 1px -1px rgba(0, 0, 0, 0.12)"
            )
        }, Setting$BtsCore.styleObjects(style)),
    onMouseDown: (function (param) {
        return Curry._1(dispatch, /* MouseUpDown */Block.__(1, [true]));
      }),
    onMouseEnter: (function (param) {
        return Curry._1(dispatch, /* MouseEnterLeave */Block.__(0, [true]));
      }),
    onMouseLeave: (function (param) {
        return Curry._1(dispatch, /* MouseEnterLeave */Block.__(0, [false]));
      }),
    onMouseUp: (function (param) {
        return Curry._1(dispatch, /* MouseUpDown */Block.__(1, [false]));
      })
  };
  if (onClick !== undefined) {
    tmp.onClick = Caml_option.valFromOption(onClick);
  }
  return React.createElement("div", tmp, children);
}

var make = Paper;

export {
  reducer ,
  initialState ,
  paddingTopBottoms ,
  otherBackgroundColors ,
  backgroundColors ,
  boxShadows ,
  borderRadiuses ,
  classes ,
  make ,
  
}
/*  Not a pure module */