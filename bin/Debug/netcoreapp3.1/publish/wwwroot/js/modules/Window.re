module Locations = {
  [@bs.val] [@bs.scope "window.location"]
  external assign: string => unit = "assign";
  [@bs.val] [@bs.scope "window"]
  external href: (string, string) => unit = "open";
};

module Listeners = {
  [@bs.val] [@bs.scope "window"]
  external add: (string, Js.t('a) => unit, bool) => unit = "addEventListener";
  [@bs.val] [@bs.scope "window"]
  external remove: (string, Js.t('a) => unit) => unit = "removeEventListener";
};

module Sizes = {
  [@bs.val] [@bs.scope "window"] external width: int = "innerWidth";
  [@bs.val] [@bs.scope "window"] external height: int = "innerHeight";
};