var Drawer = function(sudokuStorage) {
  this.sudokuStorage = sudokuStorage;

  this.assetManager = new AssetManager();
  this.downloadAssets();

  this.canvas = document.getElementById('sudoku-solver-canvas');
  this.ctx = this.canvas.getContext('2d');
  this.canvas.style.backgroundColor = "white";

  this.canvas.width  = window.innerWidth;
  this.canvas.height = window.innerHeight;
  Settings.set('CANVAS_WIDTH', this.canvas.width);
  Settings.set('CANVAS_HEIGHT', this.canvas.height);
};

Drawer.prototype.moveParticles = function() {
  for(var i = 0; i < this.sudokuStorage.unsolvedSudokus.length; i++) {
    for(var j = 0; j < this.sudokuStorage.unsolvedSudokus[i].particles.length; j++) {
      var particle = this.sudokuStorage.unsolvedSudokus[i].particles[j];
      var num = particle.val;
      var newX = particle.x + particle.dx;
      var newY = particle.y + particle.dy;
      if(newX < 0) {
        newX = Settings.get('CANVAS_WIDTH');
      }
      else if(newX > Settings.get('CANVAS_WIDTH')) {
        newX = 0;
      }
      if(newY < 0) {
        newY = Settings.get('CANVAS_HEIGHT');
      }
      else if(newY > Settings.get('CANVAS_HEIGHT')) {
        newY = 0;
      }
      particle.x = newX;
      particle.y = newY;
    }
  }
}

Drawer.prototype.drawParticles = function() {
  for(var i = 0; i < this.sudokuStorage.unsolvedSudokus.length; i++) {
    for(var j = 0; j < this.sudokuStorage.unsolvedSudokus[i].particles.length; j++) {
      var particle = this.sudokuStorage.unsolvedSudokus[i].particles[j];
      var num = particle.val;
      var img = this.assetManager.getAsset("../svg/numbers/" + num + ".svg");
      this.ctx.drawImage(img, particle.x, particle.y, 12, 21);
    }
  }
  /*
  for(var i = 0; i < this.sudokuStorage.solvedSudokus.length; i++) {
    for(var j = 0; j < this.sudokuStorage.solvedSudokus[i].particles.length; j++) {
      var num = this.sudokuStorage.solvedSudokus[i].particles[j].val;
      var img = this.assetManager.getAsset("../svg/numbers/" + num + ".svg");
      this.ctx.drawImage(img, j * 15, (i * 30) + 300, 12, 21);
    }
  }
  */
}

Drawer.prototype.renderLoop = function() {
  requestAnimationFrame(() => { this.renderLoop() } );
  this.resizeCanvas();
  this.clearCanvas();
  this.drawParticles();
  /* Particles should not be bound to a specific sudoku due to valeus will jump
  around if so due to for each unsolved solution new particles get calculated.
  TODO: Pregenerate particles and update their values when a new unsolved solution
  was found */
  this.moveParticles();
}

Drawer.prototype.resizeCanvas = function() {
  this.canvas.width  = window.innerWidth;
  this.canvas.height = window.innerHeight;
  Settings.set('CANVAS_WIDTH', this.canvas.width);
  Settings.set('CANVAS_HEIGHT', this.canvas.height);
}

Drawer.prototype.clearCanvas = function() {
  this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
}

Drawer.prototype.downloadAssets = function() {
  this.assetManager.queueDownload('../svg/numbers/0.svg');
  this.assetManager.queueDownload('../svg/numbers/1.svg');
  this.assetManager.queueDownload('../svg/numbers/2.svg');
  this.assetManager.queueDownload('../svg/numbers/3.svg');
  this.assetManager.queueDownload('../svg/numbers/4.svg');
  this.assetManager.queueDownload('../svg/numbers/5.svg');
  this.assetManager.queueDownload('../svg/numbers/6.svg');
  this.assetManager.queueDownload('../svg/numbers/7.svg');
  this.assetManager.queueDownload('../svg/numbers/8.svg');
  this.assetManager.queueDownload('../svg/numbers/9.svg');
  this.assetManager.downloadAll(() => {
    console.log("All assets loaded, start render loop");
    /* Ready to draw and animate, start render loop */
    requestAnimationFrame(() => { this.renderLoop() } );
  });
}