[@bs.module "../i18n/en.json"] external en: array(Translation.t) = "default";
[@bs.module "../i18n/zh.json"] external zh: array(Translation.t) = "default";

type locale =
  | En
  | Zh;

let all = [|En, Zh|];

let toString =
  fun
  | En => "en"
  | Zh => "zh";

let translations =
  fun
  | En => en
  | Zh => zh;
