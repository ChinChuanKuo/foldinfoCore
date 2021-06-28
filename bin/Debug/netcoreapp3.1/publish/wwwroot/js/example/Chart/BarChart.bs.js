// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as $$Array from "bs-platform/lib/es6/array.js";
import * as React from "react";
import * as Caml_format from "bs-platform/lib/es6/caml_format.js";
import * as Animate$BtsCore from "../../material-ui/core/Animate/Animate.bs.js";
import * as BarLine$BtsCore from "../../material-ui/core/BarChart/BarLine.bs.js";
import * as BarText$BtsCore from "../../material-ui/core/BarChart/BarText.bs.js";
import * as Setting$BtsCore from "../../setting/Setting.bs.js";
import * as BarBoard$BtsCore from "../../material-ui/core/BarChart/BarBoard.bs.js";
import * as BarPillar$BtsCore from "../../material-ui/core/BarChart/BarPillar.bs.js";

function BarChart(Props) {
  var width = Props.width;
  var height = Props.height;
  var transform = Props.transform;
  var backgroundColor = Props.backgroundColor;
  var latitude = Props.latitude;
  var longitude = Props.longitude;
  var datas = Props.datas;
  var spacing = Props.spacing;
  var stroke = Props.stroke;
  var strokeWidth = Props.strokeWidth;
  var counts = Caml_format.caml_float_of_string(BarBoard$BtsCore.widths(width)) / datas.length;
  var proportion = function (datas,height){ let max = 0; for (var i = 0; i < datas.length; i++) { if (datas[i][1] > max) {max = datas[i][1];} } return height / max; };
  var barWidth = String(counts - spacing | 0);
  var barHeight = function (value) {
    return String(value * proportion(datas, Caml_format.caml_int_of_string(BarBoard$BtsCore.heights(height))) - spacing | 0);
  };
  var x = function (i) {
    return String(counts * i | 0);
  };
  var y = function (value) {
    return String(Caml_format.caml_float_of_string(BarBoard$BtsCore.heights(height)) - (value * proportion(datas, Caml_format.caml_int_of_string(BarBoard$BtsCore.heights(height))) - spacing) | 0);
  };
  return React.createElement(BarBoard$BtsCore.make, {
              width: BarBoard$BtsCore.widths(width),
              height: BarBoard$BtsCore.heights(height),
              transform: Setting$BtsCore.stringObjects(transform),
              backgroundColor: Setting$BtsCore.stringObjects(backgroundColor),
              children: null
            }, Setting$BtsCore.disabledObjects(latitude) ? React.createElement(BarLine$BtsCore.make, {
                    y2: BarBoard$BtsCore.heights(height)
                  }) : null, Setting$BtsCore.disabledObjects(longitude) ? React.createElement(BarLine$BtsCore.make, {
                    x2: BarBoard$BtsCore.widths(width),
                    y1: BarBoard$BtsCore.heights(height),
                    y2: BarBoard$BtsCore.heights(height)
                  }) : null, $$Array.mapi((function (i, data) {
                    return React.createElement(React.Fragment, undefined, React.createElement(BarPillar$BtsCore.make, {
                                    width: barWidth,
                                    height: barHeight(data.to_),
                                    color: data.color,
                                    stroke: Setting$BtsCore.stringObjects(stroke),
                                    strokeWidth: Setting$BtsCore.stringObjects(strokeWidth),
                                    x: x(i),
                                    y: y(data.to_),
                                    children: React.createElement(Animate$BtsCore.make, {
                                          attributeName: "height",
                                          to_: barHeight(data.to_)
                                        })
                                  }), React.createElement(BarText$BtsCore.make, {
                                    x: String(counts * i + (counts - spacing) / 2.0 | 0),
                                    y: String(Caml_format.caml_float_of_string(BarBoard$BtsCore.heights(height)) - data.to_ * proportion(datas, Caml_format.caml_int_of_string(BarBoard$BtsCore.heights(height))) + spacing / 2.0 | 0),
                                    children: String(data.to_ | 0)
                                  }));
                  }), datas));
}

var make = BarChart;

export {
  make ,
  
}
/* react Not a pure module */
