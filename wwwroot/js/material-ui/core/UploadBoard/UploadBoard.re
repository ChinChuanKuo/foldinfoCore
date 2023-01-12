open ReasonReact;
open Setting;
[%bs.raw {|require('../../scss/UploadBoard/uploadBoard.scss')|}];

type tupleChildren = (reactElement, reactElement);

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "rgba(0,0,0,0.8)"
  | Some(backgroundColor) => backgroundColor
  };

let opacitys = showUpload => showUpload ? "1" : "0";

let visibilitys = showUpload => showUpload ? "visible" : "hidden";

let boardShows = showUpload =>
  showUpload ? "uploadDropModal-2kTwbc" : "uploadDropModal";

let positionColors = positionColor =>
  switch (positionColor) {
  | None => "rgba(255,0,0,.6)"
  | Some(positionColor) => positionColor
  };

let positionShows = showUpload => showUpload ? "bgScale-1otPtc" : "bgScale";

let linearShows = showUpload => showUpload ? "inner-3nWsbo" : "inner-test";

let iconsBoardShows = showUpload => showUpload ? "icons-1w691d" : "icons-test";

let titleBoardShows = showUpload => showUpload ? "tile-2Vtl4y" : "tile-test";

let instructionsBoardShows = showUpload =>
  showUpload ? "instructions-2Du9gG" : "instuctions-test";

[@react.component]
let make =
    (
      ~style: option(ReactDOMRe.style)=?,
      ~showUpload: option(bool)=?,
      ~backgroundColor: option(string)=?,
      ~positionColor: option(string)=?,
      ~children: tupleChildren,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~backgroundColor={
                backgroundColor |> backgroundColors;
              },
              ~opacity={
                showUpload |> disabledObjects |> opacitys;
              },
              ~visibility={
                showUpload |> disabledObjects |> visibilitys;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~className="uploadArea-3QgLtW",
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~className={
              showUpload |> disabledObjects |> boardShows;
            },
            (),
          ),
        [|
          ReactDOMRe.createDOMElementVariadic(
            "div",
            ~props=
              ReactDOMRe.domProps(
                ~style={
                  ReactDOMRe.Style.make(
                    ~backgroundColor={
                      positionColor |> positionColors;
                    },
                    (),
                  );
                },
                ~className={
                  showUpload |> disabledObjects |> positionShows;
                },
                (),
              ),
            [||],
          ),
          ReactDOMRe.createDOMElementVariadic(
            "div",
            ~props=
              ReactDOMRe.domProps(
                ~className={
                  showUpload |> disabledObjects |> linearShows;
                },
                (),
              ),
            [|
              ReactDOMRe.createDOMElementVariadic(
                "div",
                ~props=
                  ReactDOMRe.domProps(
                    ~className={
                      showUpload |> disabledObjects |> iconsBoardShows;
                    },
                    (),
                  ),
                [|fst(children)|],
              ),
              ReactDOMRe.createDOMElementVariadic(
                "div",
                ~props=
                  ReactDOMRe.domProps(
                    ~className={
                      showUpload |> disabledObjects |> titleBoardShows;
                    },
                    (),
                  ),
                [|
                  {
                    "Drop & Down" |> string;
                  },
                |],
              ),
              ReactDOMRe.createDOMElementVariadic(
                "div",
                ~props=
                  ReactDOMRe.domProps(
                    ~className={
                      showUpload |> disabledObjects |> instructionsBoardShows;
                    },
                    (),
                  ),
                [|snd(children)|],
              ),
            |],
          ),
        |],
      ),
    |],
  );