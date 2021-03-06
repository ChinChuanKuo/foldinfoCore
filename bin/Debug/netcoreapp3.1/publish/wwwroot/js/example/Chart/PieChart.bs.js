// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as $$Array from "bs-platform/lib/es6/array.js";
import * as React from "react";
import * as Caml_format from "bs-platform/lib/es6/caml_format.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Animate$BtsCore from "../../material-ui/core/Animate/Animate.bs.js";
import * as PiePath$BtsCore from "../../material-ui/core/PieChart/PiePath.bs.js";
import * as Setting$BtsCore from "../../setting/Setting.bs.js";
import * as PieBoard$BtsCore from "../../material-ui/core/PieChart/PieBoard.bs.js";

function PieChart(Props) {
  var size = Props.size;
  var backgroundColor = Props.backgroundColor;
  var datas = Props.datas;
  var enterOpacity = Props.enterOpacity;
  var downOpacity = Props.downOpacity;
  var stroke = Props.stroke;
  var enterStrokeWidth = Props.enterStrokeWidth;
  var downStrokeWidth = Props.downStrokeWidth;
  var strokeWidth = Props.strokeWidth;
  var onClick = Props.onClick;
  var circles = Caml_format.caml_float_of_string(PieBoard$BtsCore.sizes(size)) / 2.0;
  var total = function (datas){ let total = 0; for (var i = 0; i < datas.length; i++) {total += datas[i][1];} return total; };
  var from = function (datas,index){ if (index == 0) {return 0.0;} let before = 0; for (var i = 0; i < index; i++) {before += datas[i][1];} return before; };
  var to_ = function (datas,index,to_){ if (index == 0) {return to_;} let before = 0; for (var i = 0; i <= index; i++) {before += datas[i][1];} return before; };
  return React.createElement(PieBoard$BtsCore.make, {
              size: PieBoard$BtsCore.sizes(size),
              backgroundColor: Setting$BtsCore.stringObjects(backgroundColor),
              children: $$Array.mapi((function (i, data) {
                      var tmp = {
                        circles: circles,
                        color: data.color,
                        enterOpacity: Setting$BtsCore.stringObjects(enterOpacity),
                        downOpacity: Setting$BtsCore.stringObjects(downOpacity),
                        stroke: Setting$BtsCore.stringObjects(stroke),
                        enterStrokeWidth: Setting$BtsCore.stringObjects(enterStrokeWidth),
                        downStrokeWidth: Setting$BtsCore.stringObjects(downStrokeWidth),
                        strokeWidth: Setting$BtsCore.stringObjects(strokeWidth),
                        from: from(datas, i) / total(datas),
                        to_: to_(datas, i, data.to_) / total(datas),
                        children: React.createElement(Animate$BtsCore.make, {
                              attributeName: "opacity",
                              to_: "1"
                            })
                      };
                      if (onClick !== undefined) {
                        tmp.onClick = Caml_option.valFromOption(onClick);
                      }
                      return React.createElement(PiePath$BtsCore.make, tmp);
                    }), datas)
            });
}

var make = PieChart;

export {
  make ,
  
}
/* react Not a pure module */
