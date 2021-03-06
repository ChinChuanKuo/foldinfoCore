// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as ReactIntl from "react-intl";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Button$BtsCore from "../../material-ui/core/Button/Button.bs.js";
import * as Setting$BtsCore from "../../setting/Setting.bs.js";
import * as PasteBoard$BtsCore from "../../material-ui/core/PasteBoard/PasteBoard.bs.js";
import * as PasteInformation$BtsCore from "../../material-ui/core/PasteBoard/PasteInformation.bs.js";
import * as ProgressCircular$BtsCore from "../../material-ui/core/Progress/ProgressCircular.bs.js";

function GeneralUpload(Props) {
  var webLoad = Props.webLoad;
  var showDrop = Props.showDrop;
  var fileRef = Props.fileRef;
  var onDragOver = Props.onDragOver;
  var onDragLeave = Props.onDragLeave;
  var onDrop = Props.onDrop;
  var disabled = Props.disabled;
  var onClick = Props.onClick;
  var onChange = Props.onChange;
  if (Setting$BtsCore.disabledObjects(webLoad)) {
    return React.createElement(PasteBoard$BtsCore.make, {
                children: null
              }, React.createElement(PasteInformation$BtsCore.make, {
                    tile: "Reviewing File..."
                  }), React.createElement(ProgressCircular$BtsCore.make, {
                    size: "80",
                    color: "rgba(255,0,0,0.8)"
                  }));
  }
  var tmp = {
    children: null
  };
  if (onDragOver !== undefined) {
    tmp.onDragOver = Caml_option.valFromOption(onDragOver);
  }
  if (onDragLeave !== undefined) {
    tmp.onDragLeave = Caml_option.valFromOption(onDragLeave);
  }
  if (onDrop !== undefined) {
    tmp.onDrop = Caml_option.valFromOption(onDrop);
  }
  var tmp$1 = {
    variant: "button",
    color: "rgba(255,255,255,1)",
    border: "contained",
    size: "medium",
    disabled: Setting$BtsCore.disabledObjects(disabled),
    children: React.createElement(ReactIntl.FormattedMessage, {
          id: "choose",
          defaultMessage: "Choose"
        })
  };
  if (onClick !== undefined) {
    tmp$1.onClick = Caml_option.valFromOption(onClick);
  }
  var tmp$2 = {
    ref: Setting$BtsCore.refObjects(fileRef),
    style: {
      display: "none"
    },
    type: "file"
  };
  if (onChange !== undefined) {
    tmp$2.onChange = Caml_option.valFromOption(onChange);
  }
  return React.createElement(PasteBoard$BtsCore.make, tmp, Setting$BtsCore.disabledObjects(showDrop) ? React.createElement(PasteInformation$BtsCore.make, {
                    tile: "Please Let Go"
                  }) : React.createElement(PasteInformation$BtsCore.make, {
                    tile: "Please Drop Photo In Here",
                    instruction: "or you can ..."
                  }), React.createElement(Button$BtsCore.make, tmp$1), React.createElement("input", tmp$2));
}

var make = GeneralUpload;

export {
  make ,
  
}
/* react Not a pure module */
