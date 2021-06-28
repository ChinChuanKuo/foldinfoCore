[@react.component]
let make = _ =>
  <div>
    <ProgressCircular />
    <ProgressCircular animation="stop" />
    <ProgressLinear />
    <br />
    <ProgressLoading transform="0.5" />
    <br />
    <ProgressWaiting />
  </div>;