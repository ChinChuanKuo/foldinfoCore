module Sessions = {
  [@bs.val] [@bs.scope "sessionStorage"]
  external select: string => Js.Nullable.t(string) = "getItem";
  [@bs.val] [@bs.scope "sessionStorage"]
  external create: (string, string) => unit = "setItem";
};

module Locals = {
  [@bs.val] [@bs.scope "localStorage"]
  external select: string => Js.Nullable.t(string) = "getItem";
  [@bs.val] [@bs.scope "localStorage"]
  external create: (string, string) => unit = "setItem";
};