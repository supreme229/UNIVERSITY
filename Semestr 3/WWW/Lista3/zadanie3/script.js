var currentBox;
setInterval(function () {
  for (var i = 1; i <= 4; i++) {
    currentBox = document.getElementById(i.toString());
    setTimeout(function (currentBox) {
      currentBox.classList.toggle('square-animation');
    }, i * 200, currentBox)
  }
}, 1000)