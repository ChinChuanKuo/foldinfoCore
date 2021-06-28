[@genType]
let changeObjects = (default, change) =>
  switch (default) {
  | "" => change
  | _ => default
  };
[@genType]
let checkObjects = default => {
  let objects = default |> Js.Nullable.toOption;
  switch (objects) {
  | None => ""
  | Some(default) => default
  };
};
[@genType]
let actionObjects = default =>
  switch (default) {
  | None => (_ => "action" |> Js.log)
  | Some(default) => default
  };
