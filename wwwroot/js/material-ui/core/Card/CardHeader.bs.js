// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as Setting$BtsCore from "../../../setting/Setting.bs.js";

function paddings(padding) {
  if (padding !== undefined) {
    return padding + "px";
  } else {
    return "16px";
  }
}

function CardHeader(Props) {
  var style = Props.style;
  var top = Props.top;
  var right = Props.right;
  var bottom = Props.bottom;
  var left = Props.left;
  var children = Props.children;
  return React.createElement("div", {
              style: Object.assign(({}), {
                    paddingTop: paddings(top),
                    paddingRight: paddings(right),
                    paddingBottom: paddings(bottom),
                    paddingLeft: paddings(left)
                  }, Setting$BtsCore.styleObjects(style))
            }, children);
}

var make = CardHeader;

export {
  paddings ,
  make ,
  
}
/* react Not a pure module */
