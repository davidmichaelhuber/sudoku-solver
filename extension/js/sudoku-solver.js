$("#connect-button").click(function(){
  connect();
});

$("#send-message-button").click(function(){
  send();
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
  console.log("Received");
  console.log(JSON.stringify(message));
}

function onDisconnected() {
  console.log("Failed to connect: " + chrome.runtime.lastError.message);
  port = null;
}

function send() {
	console.log("Sending");
	port.postMessage({text: "next_step"});
}