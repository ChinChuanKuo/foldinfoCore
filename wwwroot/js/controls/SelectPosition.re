module Position = {
  [@genType]
  let top = i => i < 1 ? "0" : "50%";
  [@genType]
  let transform = i => i < 1 ? "translate(0, 0)" : "translate(0, -50%)";
};