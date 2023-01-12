open Setting;
[%bs.raw {|require('../../scss/IconStyle/iconStyle.scss')|}];

let sizes = size =>
  switch (size) {
  | None => "24px"
  | Some(size) => size ++ "px"
  };

let animations = animation =>
  switch (animation) {
  | "justLeftRight" => "justLeftRightAnimation 0.5s"
  | "justTopDown" => "justTopDownRorate180Animation 0.5s forwards"
  | "justDownTop" => "justDownTopRorate180Animation 0.5s forwards"
  | _ => animation
  };

let classes = className => {
  let basic = "icons";
  switch (className) {
  | None => basic
  | Some(className) => basic ++ " " ++ className
  };
};

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~width: option(string)=?,
      ~height: option(string)=?,
      ~animation: option(string)=?,
      ~className: option(string)=?,
      ~src: option(string)=?,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "span",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~width={
                width |> sizes;
              },
              ~height={
                height |> sizes;
              },
              ~animation={
                animation |> stringObjects |> animations;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className={
          className |> classes;
        },
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "img",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(
                ~width={
                  width |> sizes;
                },
                ~height={
                  height |> sizes;
                },
                ~display="block",
                (),
              );
            },
            ~src={
              src |> stringObjects;
            },
            (),
          ),
        [||],
      ),
    |],
  );
