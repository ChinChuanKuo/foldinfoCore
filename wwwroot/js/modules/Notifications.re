[@bs.val] [@bs.scope "Notification"] external make: string = "permission";
[@bs.val] [@bs.scope "Notification"]
external request: unit => Js.Promise.t(string) = "requestPermission";
[@bs.new] external message: (string, Js.t('a)) => unit = "Notification";