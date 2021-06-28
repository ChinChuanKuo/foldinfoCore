[@bs.new] external make: unit => Js.t('a) = "FormData";
[@bs.send] external append: (Js.t('a), string, 'a) => unit = "append";