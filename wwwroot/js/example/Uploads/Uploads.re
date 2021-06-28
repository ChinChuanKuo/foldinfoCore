open ReasonReact;
[@react.component]
let make = (~showUpload: bool) => {
  <UploadBoard showUpload>
    ...(
         <UploadSVG />,
         <UploadInformation>
           ...(
                "You Can Write Information Before Upload" |> string,
                "Press Shift Can Be Upload" |> string,
              )
         </UploadInformation>,
       )
  </UploadBoard>;
};