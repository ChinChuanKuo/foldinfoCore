module ExecCommands = {
  [@bs.val] [@bs.scope "document"]
  external make: (string, bool, string) => unit = "execCommand";
};

module GetElementById = {
  [@bs.val] [@bs.scope "document"]
  external make: string => Js.t('a) = "getElementById";
};