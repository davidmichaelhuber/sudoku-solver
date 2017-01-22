$("#connect-button").click(function(){
  connect();
});

$("#send-sudoku-button").click(function(){
  send({sudoku: "002060000006000700010003004000601005090005000007000800050070400100000003200000100"});
});

$("#send-skip-solution-count-button").click(function(){
  send({skip_solution_count: "100000"});
});

$("#send-tick-button").click(function(){
  send({tick: "next"});
});

var port;

function connect() {
  var hostName = "sudoku_solver";
  console.log("Connecting to native messaging host " + hostName)
  port = chrome.runtime.connectNative(hostName);
  port.onMessage.addListener(onNativeMessage);
  port.onDisconnect.addListener(onDisconnected);
}

function onNativeMessage(message) {
  // console.log("Received");
  console.log(JSON.stringify(message));
}

function onDisconnected() {
  console.log("Failed to connect: " + chrome.runtime.lastError.message);
  port = null;
}

function send(obj) {
	// console.log("Sending");
  /* Easy
	port.postMessage({sudoku: "136259748725418936489367150364780219518692374972134685240576893853921467697840520"}); */
  /* Hard
  port.postMessage({sudoku: "002060000006000700010003004000601005090005000007000800050070400100000003200000100"}); */
  port.postMessage(obj);
}