open Storage;
module Location = {
  [@genType]
  let success = event => {
    event##coords##longitude |> Locals.create("longitude");
    event##coords##latitude |> Locals.create("latitude");
  };
  [@genType]
  let error = event => event |> Js.log;
  [@genType]
  type item = {
    enableHighAccuracy: bool,
    maximumAge: int,
    timeout: int,
  };
  [@genType]
  let items = [|
    {enableHighAccuracy: true, maximumAge: 30000, timeout: 27000},
  |];
};

module Browser = {
  [@genType]
  let success = useragent =>
    switch (Js_string.indexOf("Safari", useragent)) {
    | (-1) =>
      switch (Js_string.indexOf("Trident", useragent)) {
      | (-1) =>
        switch (Js_string.indexOf("Edge", useragent)) {
        | (-1) => Locals.create("browser", "FireFox")
        | _ => Locals.create("browser", "IeEdge")
        }
      | _ => Locals.create("browser", "IeEdge")
      }
    | _ => Locals.create("browser", "Safari/Google")
    };
};