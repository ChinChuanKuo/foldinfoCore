open ReasonApollo;
open ReactIntl;
open Navigator;

[@react.component]
let make = () => {
  let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();
  let httpLink =
    ApolloLinks.createHttpLink(~uri="http://localhost:8080/graphql", ());
  let instance = createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());
  let chooseLocale = () => {
    switch (Js_string.split("-", Language.make)[0]) {
    | "zh" => Locale.Zh
    | _ => Locale.En
    };
  };

  <Provider client=instance>
    <IntlProvider
      locale={chooseLocale()->Locale.toString}
      messages={chooseLocale()->Locale.translations->Translation.toDict}>
      <Route />
    </IntlProvider>
  </Provider>;
};
