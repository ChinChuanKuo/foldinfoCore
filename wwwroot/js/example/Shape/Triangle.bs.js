// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as Setting$BtsCore from "../../setting/Setting.bs.js";

function borderWidths(bottom, height) {
  if (bottom !== undefined) {
    if (height !== undefined) {
      return "0px " + (bottom + ("px " + (height + ("px " + (bottom + "px")))));
    } else {
      return "0px " + (bottom + ("px 20px " + (bottom + "px")));
    }
  } else if (height !== undefined) {
    return "0px 10px " + (height + "px 10px");
  } else {
    return "0px 10px 20px 10px";
  }
}

function borderColors(color) {
  if (color !== undefined) {
    return "transparent transparent " + (color + " transparent");
  } else {
    return "transparent transparent rgba(255,0,0,0.8) transparent";
  }
}

function borderStyles(style) {
  if (style !== undefined) {
    return style;
  } else {
    return "solid";
  }
}

function Triangle(Props) {
  var style = Props.style;
  var bottom = Props.bottom;
  var height = Props.height;
  var borderColor = Props.borderColor;
  var borderStyle = Props.borderStyle;
  return React.createElement("div", {
              style: Object.assign(({}), {
                    borderColor: borderColors(borderColor),
                    borderStyle: borderStyle !== undefined ? borderStyle : "solid",
                    borderWidth: borderWidths(bottom, height),
                    height: "0px",
                    width: "0px"
                  }, Setting$BtsCore.styleObjects(style))
            });
}

var make = Triangle;

export {
  borderWidths ,
  borderColors ,
  borderStyles ,
  make ,
  
}
/* react Not a pure module */
