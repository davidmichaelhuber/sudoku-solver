var NMHListener = function() {
  this.port = null;
  this.connect(Settings.get('NMH_NAME'));
};

NMHListener.prototype.connect = function(hostName) {
  console.log("Connecting to native messaging host " + hostName)
  this.port = chrome.runtime.connectNative(hostName);
  this.port.onMessage.addListener(this.onNativeMessage);
  this.port.onDisconnect.addListener(this.onDisconnected);
}

NMHListener.prototype.onNativeMessage = function(msg) {
  console.log('NMH: ' + JSON.stringify(msg));
}

NMHListener.prototype.onDisconnect = function() {
  console.log("Lost connection or failed to connect to: " + chrome.runtime.lastError.message);
  port = null;
}

NMHListener.prototype.writeNativeMessage = function(key, val) {
  /*
  Easy: 136259748725418936489367150364780219518692374972134685240576893853921467697840520
  Hard: 002060000006000700010003004000601005090005000007000800050070400100000003200000100
  */
  port.postMessage({[key]:val});
}

NMHListener.prototype.writeSudoku = function(sudoku, skipSolutionCount) {
  this.writeNativeMessage(Settings.get('NMH_SUDOKU_KEY'), sudoku);
  this.writeNativeMessage(Settings.get('NMH_SKIP_SOLUTION_COUNT_KEY'), skipSolutionCount);
}

NMHListener.prototype.writeTick = function() {
  this.writeNativeMessage(Settings.get('NMH_TICK_KEY'), 'next');
}

// $("#connect-button").click(function(){
//   connect();
// });

// $("#send-sudoku-button").click(function(){
//   send({sudoku: "002060000006000700010003004000601005090005000007000800050070400100000003200000100"});
// });

// $("#send-skip-solution-count-button").click(function(){
//   send({skip_solution_count: "1"});
// });

// $("#send-tick-button").click(function(){
//   send({tick: "next"});
// });

// var port;

// function connect() {
//   var hostName = "sudoku_solver";
//   console.log("Connecting to native messaging host " + hostName)
//   port = chrome.runtime.connectNative(hostName);
//   port.onMessage.addListener(onNativeMessage);
//   port.onDisconnect.addListener(onDisconnected);
// }

// function onNativeMessage(message) {
//   // console.log("Received");
//   console.log(JSON.stringify(message));
// }

// function onDisconnected() {
//   console.log("Failed to connect: " + chrome.runtime.lastError.message);
//   port = null;
// }

// function send(obj) {
//   // console.log("Sending");
//   /* Easy
//   port.postMessage({sudoku: "136259748725418936489367150364780219518692374972134685240576893853921467697840520"}); */
//   /* Hard
//   port.postMessage({sudoku: "002060000006000700010003004000601005090005000007000800050070400100000003200000100"}); */
//   port.postMessage(obj);
// }