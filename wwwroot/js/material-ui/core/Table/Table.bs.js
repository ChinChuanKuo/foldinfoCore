// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as Setting$BtsCore from "../../../setting/Setting.bs.js";

((require('../../scss/Table/table.scss')));

function minWidths(minWidth) {
  if (minWidth !== undefined) {
    return minWidth + "px";
  } else {
    return "961px";
  }
}

function Table(Props) {
  var style = Props.style;
  var minWidth = Props.minWidth;
  var children = Props.children;
  return React.createElement("table", {
              className: "j8ew6kj",
              style: Object.assign(({}), {
                    minWidth: minWidths(minWidth)
                  }, Setting$BtsCore.styleObjects(style))
            }, children);
}

var make = Table;

export {
  minWidths ,
  make ,
  
}
/*  Not a pure module */
