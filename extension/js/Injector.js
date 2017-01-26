chrome.app.runtime.onLaunched.addListener(function() {
  chrome.app.window.create('../html/index.html', {
    'outerBounds': {
      'width': 1600,
      'height': 900
    }
  });
});