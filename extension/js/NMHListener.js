var NMHListener = function() {
  this.sudokuStorage = new SudokuStorage();

  this.port = null;
  this.tickCallback = null;

  this.connect(Settings.get('NMH_NAME'));
};

NMHListener.prototype.connect = function(hostName) {
  console.log("Connecting to native messaging host " + hostName)
  this.port = chrome.runtime.connectNative(hostName);
  this.port.onMessage.addListener((msg) => { this.onNativeMessage(msg) } );
  this.port.onDisconnect.addListener(() => { this.onDisconnect() } );
}

NMHListener.prototype.onNativeMessage = function(msg) {
  console.log('DEBUG: ' + JSON.stringify(msg));
  this.processMessage(msg);
}

NMHListener.prototype.onDisconnect = function() {
  console.log("Lost connection or failed to connect to: " + chrome.runtime.lastError.message);
  window.close();
}

NMHListener.prototype.processMessage = function(msg) {
  var keyValPair = this.parseMessage(msg);
  if(keyValPair != null) {
    switch(keyValPair.key) {
      case Settings.get('NMH_STATUS_KEY'):
        console.log("Received: NMH_STATUS_KEY");
        if(keyValPair.val === 'ready') {
          console.log("Native Message Host is ready");
          /* Possible memory leak, instantiated on every ready
          message butgetting removed also? */
          new UI(this);
          new Drawer(this.sudokuStorage);
        }
        break;
      case Settings.get('NMH_UNSOLVED_KEY'):
        console.log("Received: NMH_STATUS_KEY");
        if(!this.isTicking()){
          this.tickCallback = this.startTicking();
        }
        this.sudokuStorage.addUnsolvedSudoku(keyValPair.val);
        break;
      case Settings.get('NMH_SOLVED_KEY'):
        console.log("Received: NMH_SOLVED_KEY");
        if(this.isTicking()){
          this.stopTicking();
        }
        // Tries not implemented yet
        this.sudokuStorage.addSolvedSudoku(keyValPair.val);
        break;
      case Settings.get('NMH_TRIES_KEY'):
        console.log("Received: NMH_TRIES_KEY");
        break;
      case Settings.get('NMH_SUDOKU_KEY'):
        console.log("Received: NMH_SUDOKU_KEY");
        break;
      case Settings.get('NMH_SKIP_SOLUTION_COUNT_KEY'):
        console.log("Received: NMH_SKIP_SOLUTION_COUNT_KEY");
        break;
      case Settings.get('NMH_TICK_KEY'):
        console.log("Received: NMH_TICK_KEY");
        break;
    }
  }
}

NMHListener.prototype.parseMessage = function(msg) {
  var keys = Object.keys(msg);
  if (keys.length != 1) {
    console.log("Invalid message received");
    return null;
  }
  var key = keys[0];
  var val = msg[key];
  return {
    key: keys[0],
    val: msg[key]
  }
}

NMHListener.prototype.writeNativeMessage = function(key, val) {
  this.port.postMessage({[key]:val});
}

NMHListener.prototype.writeSudokuFields = function(sudokuFields, skipSolutionCount) {
  this.writeNativeMessage(Settings.get('NMH_SUDOKU_KEY'), sudokuFields);
  this.writeNativeMessage(Settings.get('NMH_SKIP_SOLUTION_COUNT_KEY'), skipSolutionCount);
}

NMHListener.prototype.writeTick = function() {
  this.writeNativeMessage(Settings.get('NMH_TICK_KEY'), 'next');
}

NMHListener.prototype.startTicking = function() {
  return setInterval(() => {
    this.writeTick();
  }, Settings.get('TICK_INTERVAL'));
}

NMHListener.prototype.stopTicking = function() {
  clearInterval(this.tickCallback);
  this.tickCallback = null;
}

NMHListener.prototype.isTicking = function() {
  return (this.tickCallback == null) ? false : true;
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