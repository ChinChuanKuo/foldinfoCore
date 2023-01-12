open React;
let attachRecorder: unit => element = [%bs.raw
  stream => {| return new MediaRecorder(stream, { nimeType: 'video/webm;codecs=VP9' }); |}
];
//[@bs.new] external make: unit => Js.t('a) = "MediaRecorder";
[@bs.send] external start: element => unit = "start";
[@bs.send] external stop: element => unit = "stop";