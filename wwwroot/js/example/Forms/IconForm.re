open React;
open Setting;

type item = {
  icon: string,
  value: string,
};

let borderColors = enter => enter ? "rgba(255,0,0,0.8)" : "transparent";

[@react.component]
let make = (~items: option(array(item))=?) =>
  <GridContainer direction="row" justify="center" alignItem="center">
    {items
     |> arrayObjects
     |> Array.map(item =>
          <GridItem
            style={ReactDOMRe.Style.make(
              ~height="120px",
              ~marginRight="12px",
              (),
            )}
            top="0"
            right="0"
            bottom="0"
            left="0"
            width="112px"
            cursor="pointer"
            enterBorderWidth="2"
            borderWidth="2"
            enterBorderColor="rgba(255,0,0,0.8)"
            borderRadius="1"
            xs="no">
            <Card>
              <GridContainer
                direction="column" justify="center" alignItem="center">
                <GridItem top="5" right="0" bottom="0" left="0" xs="auto">
                  <div
                    style={ReactDOMRe.Style.make(
                      ~position="relative",
                      ~height="90px",
                      (),
                    )}>
                    <div
                      style={ReactDOMRe.Style.make(
                        ~position="absolute",
                        ~top="50%",
                        ~right="50%",
                        ~transform="translate(50%,-50%)",
                        (),
                      )}>
                      <IconAction animation="leftRight" src={item.icon} />
                    </div>
                  </div>
                </GridItem>
                <GridItem
                  top="0" right="0" bottom="0" left="0" width="112px" xs="no">
                  <Typography
                    style={ReactDOMRe.Style.make(~textAlign="center", ())}
                    variant="subtitle2"
                    noWrap=true>
                    {item.value |> string}
                  </Typography>
                </GridItem>
              </GridContainer>
            </Card>
          </GridItem>
        )
     |> array}
  </GridContainer>;
