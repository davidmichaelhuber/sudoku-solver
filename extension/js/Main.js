window.onload = function() {
  // /* User picks or enters a sudoku, sudoku is shown, particles moving but values
  // are not updating yet */
  // var sudoku = new Sudoku("002060000006000700010003004000601005090005000007000800050070400100000003200000100");

  // // Load all assets, launch NMHListener afterwards
  // var assetManager = new AssetManager();
  // for(var i = 0; i < 10; i++) assetManager.queueDownload('../svg/numbers/' + i + '.svg');
  // assetManager.downloadAll(function() {
  //   console.log("All assets loaded successfully");
  //   new NMHListener(sudoku);
  // });

  // Load all assets, wait until finished loading, launch NMHListener
  var assetManager = new AssetManager();
  for(var i = 0; i < 10; i++) assetManager.queueDownload('../svg/numbers/' + i + '.svg');
  assetManager.downloadAll(function() {
    console.log("All assets loaded successfully");
    new NMHListener();
  });
};