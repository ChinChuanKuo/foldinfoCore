[@genType]
let styleObjects = style =>
  switch (style) {
  | None => ReactDOMRe.Style.make()
  | Some(style) => style
  };
[@genType]
let disabledObjects = disabled =>
  switch (disabled) {
  | None => false
  | Some(disabled) => disabled
  };
[@genType]
let stringObjects = value =>
  switch (value) {
  | None => ""
  | Some(value) => value
  };
[@genType]
let floatObjects = value =>
  switch (value) {
  | None => 0.0
  | Some(value) => value
  };
[@genType]
let intObjects = value =>
  switch (value) {
  | None => 0
  | Some(value) => value
  };
[@genType]
let arrayObjects = default =>
  switch (default) {
  | None => [||]
  | Some(default) => default
  };
[@genType]
let refObjects = refs =>
  switch (refs) {
  | None => React.useRef(Js.Nullable.null)
  | Some(refs) => refs
  };
[@genType]
let pathObjects = (count, default, hash) =>
  switch (count, hash) {
  | (0, _) => "/"
  | (_, "") => Array.of_list(default)[0]
  | (_, _) => Array.of_list(default)[0] ++ "#" ++ hash
  };