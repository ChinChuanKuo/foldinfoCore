open React;
open Icons;

type main = {
  mainTitle: string,
  mainValue: string,
};

type other = {
  otherTitle: string,
  otherValue: string,
};

type desc = {
  descTitle: string,
  descValue: string,
  others: array(other),
};

type item = {
  isShow: bool,
  active: bool,
  mains: array(main),
  descs: array(desc),
};

type state = {
  formLoad: bool,
  showProgress: bool,
  items: array(item),
};

type action =
  | ShowPanel(int)
  | ClickActive(int, bool);

let reducer = (state, action) =>
  switch (action) {
  | ShowPanel(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, isShow: !item.isShow} : item,
          state.items,
        ),
    }
  | ClickActive(index, active) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, isShow: !item.isShow, active} : item,
          state.items,
        ),
    }
  };

let initialState = {
  formLoad: false,
  showProgress: true,
  items: [|
    {
      isShow: false,
      active: false,
      mains: [|
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
      |],
      descs: [|
        {
          descTitle: "Customer",
          descValue: "0001-Touch Dynamic",
          others: [|
            {otherTitle: "Model", otherValue: "K755"},
            {otherTitle: "Standard", otherValue: "KK755D36C011"},
            {otherTitle: "Order Unit", otherValue: "1_POS-USA"},
            {otherTitle: "MB Model", otherValue: "D36"},
            {otherTitle: "MB Number", otherValue: "51D360V21001"},
            {otherTitle: "Before Six Month Total", otherValue: "1100"},
            {otherTitle: "Average Use In Month", otherValue: "183"},
            {otherTitle: "Ord_2019 04", otherValue: "0"},
            {otherTitle: "Ord_2019 05", otherValue: "0"},
            {otherTitle: "Fcst_2019 05", otherValue: "300"},
            {otherTitle: "Ord_2019 06", otherValue: "0"},
            {otherTitle: "Fcst_2019 06", otherValue: "300"},
            {otherTitle: "Ord_2019 07", otherValue: "0"},
            {otherTitle: "Fcst_2019 07", otherValue: "300"},
            {otherTitle: "Ord_2019 08", otherValue: "0"},
            {otherTitle: "Fcst_2019 08", otherValue: "0"},
            {otherTitle: "Ord_2019 09", otherValue: "0"},
            {otherTitle: "Fcst_2019 09", otherValue: "0"},
            {otherTitle: "Ord_2019 10", otherValue: "0"},
            {otherTitle: "Fcst_2019 10", otherValue: "0"},
            {otherTitle: "Shipment Order", otherValue: "1"},
            {otherTitle: "Customer", otherValue: "Touch Dynamic"},
          |],
        },
        {
          descTitle: "Customer",
          descValue: "0001-Touch Dynamic",
          others: [|
            {otherTitle: "Model", otherValue: "K755"},
            {otherTitle: "Standard", otherValue: "KK755D36C011"},
            {otherTitle: "Order Unit", otherValue: "1_POS-USA"},
            {otherTitle: "MB Model", otherValue: "D36"},
            {otherTitle: "MB Number", otherValue: "51D360V21001"},
            {otherTitle: "Before Six Month Total", otherValue: "1100"},
            {otherTitle: "Average Use In Month", otherValue: "183"},
            {otherTitle: "Ord_2019 04", otherValue: "0"},
            {otherTitle: "Ord_2019 05", otherValue: "0"},
            {otherTitle: "Fcst_2019 05", otherValue: "300"},
            {otherTitle: "Ord_2019 06", otherValue: "0"},
            {otherTitle: "Fcst_2019 06", otherValue: "300"},
            {otherTitle: "Ord_2019 07", otherValue: "0"},
            {otherTitle: "Fcst_2019 07", otherValue: "300"},
            {otherTitle: "Ord_2019 08", otherValue: "0"},
            {otherTitle: "Fcst_2019 08", otherValue: "0"},
            {otherTitle: "Ord_2019 09", otherValue: "0"},
            {otherTitle: "Fcst_2019 09", otherValue: "0"},
            {otherTitle: "Ord_2019 10", otherValue: "0"},
            {otherTitle: "Fcst_2019 10", otherValue: "0"},
            {otherTitle: "Shipment Order", otherValue: "1"},
            {otherTitle: "Customer", otherValue: "Touch Dynamic"},
          |],
        },
      |],
    },
    {
      isShow: false,
      active: false,
      mains: [|
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
        {mainTitle: "JAN", mainValue: "150"},
      |],
      descs: [|
        {
          descTitle: "Customer",
          descValue: "0001-Touch Dynamic",
          others: [|
            {otherTitle: "Model", otherValue: "K755"},
            {otherTitle: "Standard", otherValue: "KK755D36C011"},
            {otherTitle: "Order Unit", otherValue: "1_POS-USA"},
            {otherTitle: "MB Model", otherValue: "D36"},
            {otherTitle: "MB Number", otherValue: "51D360V21001"},
            {otherTitle: "Before Six Month Total", otherValue: "1100"},
            {otherTitle: "Average Use In Month", otherValue: "183"},
            {otherTitle: "Ord_2019 04", otherValue: "0"},
            {otherTitle: "Ord_2019 05", otherValue: "0"},
            {otherTitle: "Fcst_2019 05", otherValue: "300"},
            {otherTitle: "Ord_2019 06", otherValue: "0"},
            {otherTitle: "Fcst_2019 06", otherValue: "300"},
            {otherTitle: "Ord_2019 07", otherValue: "0"},
            {otherTitle: "Fcst_2019 07", otherValue: "300"},
            {otherTitle: "Ord_2019 08", otherValue: "0"},
            {otherTitle: "Fcst_2019 08", otherValue: "0"},
            {otherTitle: "Ord_2019 09", otherValue: "0"},
            {otherTitle: "Fcst_2019 09", otherValue: "0"},
            {otherTitle: "Ord_2019 10", otherValue: "0"},
            {otherTitle: "Fcst_2019 10", otherValue: "0"},
            {otherTitle: "Shipment Order", otherValue: "1"},
            {otherTitle: "Customer", otherValue: "Touch Dynamic"},
          |],
        },
        {
          descTitle: "Customer",
          descValue: "0001-Touch Dynamic",
          others: [|
            {otherTitle: "Model", otherValue: "K755"},
            {otherTitle: "Standard", otherValue: "KK755D36C011"},
            {otherTitle: "Order Unit", otherValue: "1_POS-USA"},
            {otherTitle: "MB Model", otherValue: "D36"},
            {otherTitle: "MB Number", otherValue: "51D360V21001"},
            {otherTitle: "Before Six Month Total", otherValue: "1100"},
            {otherTitle: "Average Use In Month", otherValue: "183"},
            {otherTitle: "Ord_2019 04", otherValue: "0"},
            {otherTitle: "Ord_2019 05", otherValue: "0"},
            {otherTitle: "Fcst_2019 05", otherValue: "300"},
            {otherTitle: "Ord_2019 06", otherValue: "0"},
            {otherTitle: "Fcst_2019 06", otherValue: "300"},
            {otherTitle: "Ord_2019 07", otherValue: "0"},
            {otherTitle: "Fcst_2019 07", otherValue: "300"},
            {otherTitle: "Ord_2019 08", otherValue: "0"},
            {otherTitle: "Fcst_2019 08", otherValue: "0"},
            {otherTitle: "Ord_2019 09", otherValue: "0"},
            {otherTitle: "Fcst_2019 09", otherValue: "0"},
            {otherTitle: "Ord_2019 10", otherValue: "0"},
            {otherTitle: "Fcst_2019 10", otherValue: "0"},
            {otherTitle: "Shipment Order", otherValue: "1"},
            {otherTitle: "Customer", otherValue: "Touch Dynamic"},
          |],
        },
      |],
    },
  |],
};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);
  <NewYoutube showProgress={state.showProgress}>
    {state.items
     |> Array.mapi((i, item) =>
          <GridItem xs="12">
            <div>
              <ExpansionPanel showPanel={item.isShow}>
                ...(
                     <ExpansionSummary
                       showSummary={item.isShow}
                       onClick={_ => dispatch(ShowPanel(i))}>
                       ...(
                            <Typography
                              variant="tile" color="rgba(0,0,0,1)" noWrap=true>
                              {"POS355/D36,D88U" |> string}
                            </Typography>,
                            <IconGeneral
                              src={item.isShow ? arrowUpBlack : arrowDownBlack}
                            />,
                          )
                     </ExpansionSummary>,
                     <div style={ReactDOMRe.Style.make(~width="100%", ())}>
                       {item.mains
                        |> Array.map(main =>
                             <div
                               style={ReactDOMRe.Style.make(
                                 ~float="left",
                                 ~height="20px",
                                 ~marginRight="30px",
                                 ~marginTop="10px",
                                 (),
                               )}>
                               <ExpansionBasis>
                                 <span>
                                   {main.mainTitle
                                    ++ " : "
                                    ++ main.mainValue
                                    |> string}
                                 </span>
                               </ExpansionBasis>
                             </div>
                           )
                        |> array}
                     </div>,
                   )
              </ExpansionPanel>
              <ExpansionPanel showPanel={item.isShow}>
                ...(
                     <ExpansionSummary
                       showSummary={item.isShow}
                       onClick={_ => dispatch(ShowPanel(i))}>
                       ...(
                            <>
                              <ExpansionBasis>
                                {item.isShow
                                   ? <>
                                       <IconButton
                                         variant="span"
                                         style={ReactDOMRe.Style.make(
                                           ~marginRight="12px",
                                           (),
                                         )}
                                         padding="6"
                                         onClick={_ =>
                                           dispatch(ClickActive(i, true))
                                         }>
                                         <IconAction
                                           animation="circle"
                                           src=addBlack
                                         />
                                       </IconButton>
                                       {item.active
                                          ? <IconButton
                                              variant="span"
                                              style={ReactDOMRe.Style.make(
                                                ~marginRight="12px",
                                                (),
                                              )}
                                              padding="6"
                                              onClick={_ =>
                                                dispatch(
                                                  ClickActive(i, false),
                                                )
                                              }>
                                              <IconAction
                                                animation="leftRight"
                                                src=saveBlack
                                              />
                                            </IconButton>
                                          : <IconButton
                                              variant="span"
                                              style={ReactDOMRe.Style.make(
                                                ~marginRight="12px",
                                                (),
                                              )}
                                              padding="6"
                                              onClick={_ =>
                                                dispatch(
                                                  ClickActive(i, true),
                                                )
                                              }>
                                              <IconAction
                                                animation="leftRight"
                                                src=editBlack
                                              />
                                            </IconButton>}
                                     </>
                                   : null}
                                <span
                                  style={ReactDOMRe.Style.make(
                                    ~color="red",
                                    (),
                                  )}>
                                  {string(
                                     item.isShow
                                       ? "CLICK TO CLOSE" : "CLICK TO EXPAND",
                                   )}
                                </span>
                              </ExpansionBasis>
                            </>,
                            <IconGeneral
                              src={item.isShow ? arrowDownBlack : arrowUpBlack}
                            />,
                          )
                     </ExpansionSummary>,
                     <GridContainer
                       direction="column" justify="start" alignItem="start">
                       {item.descs
                        |> Array.map(desc =>
                             <>
                               <GridItem bottom="0" xs="auto">
                                 <Typography
                                   variant="body1"
                                   color="rgba(0,0,0,1)"
                                   noWrap=true>
                                   {desc.descTitle
                                    ++ " : "
                                    ++ desc.descValue
                                    |> string}
                                 </Typography>
                               </GridItem>
                               <GridItem xs="auto">
                                 {desc.others
                                  |> Array.map(other =>
                                       <div
                                         style={ReactDOMRe.Style.make(
                                           ~float="left",
                                           ~height="20px",
                                           ~marginRight="30px",
                                           ~marginTop="10px",
                                           (),
                                         )}>
                                         <ExpansionBasis>
                                           <Typography
                                             variant="body2"
                                             color="rgba(0, 0, 0, 0.8)"
                                             noWrap=true>
                                             {other.otherTitle
                                              ++ " : "
                                              ++ other.otherValue
                                              |> string}
                                           </Typography>
                                         </ExpansionBasis>
                                       </div>
                                     )
                                  |> array}
                               </GridItem>
                             </>
                           )
                        |> array}
                     </GridContainer>,
                   )
              </ExpansionPanel>
            </div>
          </GridItem>
        )
     |> array}
  </NewYoutube>;
};
