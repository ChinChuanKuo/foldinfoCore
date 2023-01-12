type mediaSource;
[@bs.val] [@bs.scope "document"]
external make: string => Dom.element = "getElementById";

[@bs.val] [@bs.scope "navigator.mediaDevices"]
external getUserMedia: Js.t('a) => Js.Promise.t(unit) = "getUserMedia";

let attachMedia: (Dom.element, unit) => mediaSource = [%bs.raw
  (video, stream) => {| video.srcObject = stream; return video; |}
];

[@bs.send] external play: Dom.element => unit = "play";