var SETTINGS = (function() {
  var params = {
    'CANVAS_WIDTH': '1280',
    'CANVAS_HEIGHT': '720',
    'MAX_PARTICLE_SPEED': '5',
    'MAX_FPS': '1',
    'HISTORY_AMOUNT': '5',
    'TICK_INTERVAL': '250'
  };
  return {
    get: function(key) {
      return params[key];
    }
  };
})();

var Drawer = function(particleSudoku) {
  this.particleSudokuHistory = [];
  this.canvas = document.getElementById('sudoku-solver-canvas');
  this.ctx = this.canvas.getContext('2d');
  this.canvas.width = SETTINGS.get('CANVAS_WIDTH');
  this.canvas.height = SETTINGS.get('CANVAS_HEIGHT');
  this.canvas.style.backgroundColor = "white";
  this.particleSudokuHistory.push(particleSudoku);
  /* Ready to draw and animate, start render loop */
  requestAnimationFrame(() => { this.renderLoop() } );
};

Drawer.prototype.moveParticles = function() {
}

Drawer.prototype.drawParticles = function() {
  for(var i = 0; i < this.particleSudokuHistory.length; i++) {
    for(var j = 0; j < this.particleSudokuHistory[i].particles.length; j++) {
      var particle = this.particleSudokuHistory[i].particles[j];
      this.ctx.font = '14px sans-serif';
      this.ctx.fillText(particle.val, particle.x, particle.y);
    }
  }
}

Drawer.prototype.renderLoop = function() {
  requestAnimationFrame(() => { this.renderLoop() } );
  this.drawParticles();
  this.moveParticles();
}

var Particle = function(val) {
  this.val = val;
  this.x = Math.floor(Math.random() * SETTINGS.get('CANVAS_WIDTH')) + 0;
  this.y = Math.floor(Math.random() * SETTINGS.get('CANVAS_HEIGHT')) + 0;
  this.dx = Math.floor(Math.random() * SETTINGS.get('MAX_PARTICLE_SPEED')) -
                      (SETTINGS.get('MAX_PARTICLE_SPEED') / 2);
  this.dy = Math.floor(Math.random() * SETTINGS.get('MAX_PARTICLE_SPEED')) -
                      (SETTINGS.get('MAX_PARTICLE_SPEED') / 2);
};

var ParticleSudoku = function(sudoku) {
  this.particles = [];
  for(var i = 0; i < sudoku.fields.length; i++) {
    this.particles[i] = new Particle(Number(sudoku.fields[i]));
  };
};

var NMHListener = function(sudoku) {
  var particleSudoku = new ParticleSudoku(sudoku);
  this.drawer = new Drawer(particleSudoku);
};

var Sudoku = function(fields) {
  this.fields = fields;
  this.solved = false;
  this.tries = 0;
};

/* User picks or enters a sudoku, sudoku is shown, particles moving but values
are not updating yet */
var sudoku = new Sudoku("002060000006000700010003004000601005090005000007000800050070400100000003200000100");

var listener = new NMHListener(sudoku);

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