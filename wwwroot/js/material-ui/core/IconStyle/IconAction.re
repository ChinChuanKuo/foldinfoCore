open React;
open Setting;
[%bs.raw {|require('../../scss/IconStyle/iconStyle.scss')|}];

type state = {enter: bool};

type action =
  | MouseEnterLeave(bool);

let reducer = (_, action) =>
  switch (action) {
  | MouseEnterLeave(enter) => {enter: enter}
  };

let initialState = {enter: false};

let sizes = size =>
  switch (size) {
  | None => "24px"
  | Some(size) => size ++ "px"
  };

let animations = animation =>
  switch (animation) {
  | "circle" => "circleAnimation 0.8s infinite"
  | "circleTop" => "circleTopAnimation 1s infinite"
  | "leftRight" => "leftRightAnimation 0.5s infinite"
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
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
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
                state.enter ? animation |> stringObjects |> animations : "";
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className={
          className |> classes;
        },
        ~onMouseEnter=_ => MouseEnterLeave(true) |> dispatch,
        ~onMouseLeave=_ => MouseEnterLeave(false) |> dispatch,
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
};
