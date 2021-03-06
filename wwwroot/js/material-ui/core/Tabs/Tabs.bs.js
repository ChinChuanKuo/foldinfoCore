// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as Setting$BtsCore from "../../../setting/Setting.bs.js";

((require('../../scss/Tabs/tabs.scss')));

function maxWidths(maxWidth) {
  if (maxWidth !== undefined) {
    return maxWidth + "px";
  } else {
    return "100%";
  }
}

function displays(display) {
  if (display !== undefined) {
    return display;
  } else {
    return "inline-block";
  }
}

function justifys(justify) {
  if (justify === "center") {
    return " MuiTabs-centered";
  } else {
    return "";
  }
}

function indexLefts (id,index,short){ return document.getElementById(id+index) == null ? 0 : index * document.getElementById(id+index).offsetWidth + short / 2; };

function indexMaxWidths (id,index,short){ return document.getElementById(id+index) == null ? 0 : document.getElementById(id+index).offsetWidth - short; };

function heights(height) {
  if (height !== undefined) {
    return height + "px";
  } else {
    return "2px";
  }
}

function backgroundColors(linearColor) {
  if (linearColor !== undefined) {
    return linearColor;
  } else {
    return "rgba(220,0,78,1)";
  }
}

function Tabs(Props) {
  var style = Props.style;
  var maxWidth = Props.maxWidth;
  var display = Props.display;
  var justify = Props.justify;
  var id = Props.id;
  var index = Props.index;
  var $$short = Props.short;
  var height = Props.height;
  var color = Props.color;
  var children = Props.children;
  return React.createElement("div", {
              className: "MuiTabs-root",
              style: {
                margin: "0 auto",
                maxWidth: maxWidths(maxWidth)
              }
            }, React.createElement("div", {
                  className: "MuiTabs-scroller MuiTabs-fixed",
                  style: {
                    display: display !== undefined ? display : "inline-block"
                  }
                }, React.createElement("div", {
                      className: "MuiTabs-flexContainer" + justifys(justify),
                      role: "tablist"
                    }, children), React.createElement("span", {
                      className: "jss296",
                      style: Object.assign(({}), {
                            backgroundColor: color !== undefined ? color : "rgba(220,0,78,1)",
                            height: heights(height),
                            left: indexLefts(id, Setting$BtsCore.intObjects(index), Setting$BtsCore.intObjects($$short)),
                            maxWidth: indexMaxWidths(id, Setting$BtsCore.intObjects(index), Setting$BtsCore.intObjects($$short))
                          }, Setting$BtsCore.styleObjects(style))
                    })));
}

var make = Tabs;

export {
  maxWidths ,
  displays ,
  justifys ,
  indexLefts ,
  indexMaxWidths ,
  heights ,
  backgroundColors ,
  make ,
  
}
/*  Not a pure module */
