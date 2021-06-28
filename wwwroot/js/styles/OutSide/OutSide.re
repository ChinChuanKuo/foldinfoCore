[@genType]
let menuOutSide =
  ReactDOMRe.Style.make(
    ~position="fixed",
    ~top="60px",
    ~minHeight="0px",
    ~zIndex="1200",
    (),
  );
[@genType]
let progressFixed =
  ReactDOMRe.Style.make(
    ~position="fixed",
    ~top="0",
    ~right="0",
    ~left="0",
    ~zIndex="2000",
    (),
  );
[@genType]
let butnRight =
  ReactDOMRe.Style.make(
    ~transition="margin-right 195ms cubic-bezier(0.4, 0, 0.6, 1) 0ms",
    (),
  );
[@genType]
let menuButn =
  ReactDOMRe.Style.make(
    ~position="absolute",
    ~zIndex="1350",
    ~left="15px",
    (),
  );
[@genType]
let drawerTube =
  ReactDOMRe.Style.make(~overflowX="hidden", ~whiteSpace="nowrap", ());
[@genType]
let drawerNewTube =
  ReactDOMRe.Style.make(
    ~overflowX="hidden",
    ~transition="left 195ms cubic-bezier(0.4, 0, 0.6, 1) 0ms",
    (),
  );
[@genType]
let mainTube =
  ReactDOMRe.Style.make(
    ~position="absolute",
    ~flexGrow="1",
    ~top="60px",
    ~height="auto",
    ~overflow="hidden",
    (),
  );
[@genType]
let errorForm =
  ReactDOMRe.Style.make(
    ~position="absolute",
    ~top="50%",
    ~right="50%",
    ~transform="translate(50%, -50%)",
    (),
  );
