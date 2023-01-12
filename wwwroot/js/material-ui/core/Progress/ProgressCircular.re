open Setting;
[%bs.raw {|require('../../scss/Progress/progressCircular.scss')|}];

let sizes = size =>
  switch (size) {
  | None => "40px"
  | Some(size) => size ++ "px"
  };

let colors = color =>
  switch (color) {
  | None => "rgba(255,0,0,0.8)"
  | Some(color) => color
  };

let boardAnimations = animation =>
  switch (animation) {
  | None => "general-rotate 1.4s linear infinite"
  | Some("stop") => "stop-rotate 1.4s linear infinite"
  | Some(animation) => animation
  };

let boardAnimationNames = animationName =>
  switch (animationName) {
  | None => "jfkdi1n"
  | Some("stop") => "jvtfs4rs"
  | Some(animationName) => animationName
  };

let circleAnimations = animation =>
  switch (animation) {
  | None => "general-dash 1.4s ease-in-out infinite"
  | Some("stop") => "stop-dash 1.4s ease-in-out infinite"
  | Some(animation) => animation
  };

let circleAnimationNames = animationName =>
  switch (animationName) {
  | None
  | Some("stop") => "jt5d5h8"
  | Some(animationName) => animationName
  };

let circleClasses = animation => {
  let basic = "jovpot2";
  switch (animation) {
  | None => basic ++ " " ++ "jgh6iqb"
  | Some("stop") => basic ++ " " ++ "jgh6iqbc"
  | _ => basic
  };
};

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~size: option(string)=?,
      ~color: option(string)=?,
      ~animation: option(string)=?,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~width={
                size |> sizes;
              },
              ~height={
                size |> sizes;
              },
              ~color={
                color |> colors;
              },
              ~animation={
                animation |> boardAnimations;
              },
              ~animationName={
                animation |> boardAnimationNames;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~role="progressbar",
        ~className="j6v5fg1 jwtxf5o",
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "svg",
        ~props=ReactDOMRe.domProps(~viewBox="22 22 44 44", ()),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "circle",
            ~props=
              ReactDOMRe.domProps(
                ~style={
                  ReactDOMRe.Style.make(
                    ~animation={
                      animation |> circleAnimations;
                    },
                    ~animationName={
                      animation |> circleAnimationNames;
                    },
                    (),
                  );
                },
                ~className={
                  animation |> circleClasses;
                },
                ~cx="44",
                ~cy="44",
                ~r="20.2",
                ~fill="none",
                ~strokeWidth="3.6",
                (),
              ),
            [||],
          ),
        |],
      ),
    |],
  );