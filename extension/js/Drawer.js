var Drawer = function(particleSudoku) {
  this.particleSudokuHistory = [];
  this.canvas = document.getElementById('sudoku-solver-canvas');
  this.ctx = this.canvas.getContext('2d');
  this.canvas.width = Settings.get('CANVAS_WIDTH');
  this.canvas.height = Settings.get('CANVAS_HEIGHT');
  this.canvas.style.backgroundColor = "white";
  this.particleSudokuHistory.push(particleSudoku);
  /* Ready to draw and animate, start render loop */
  requestAnimationFrame(() => { this.renderLoop() } );
};

Drawer.prototype.moveParticles = function() {
}

Drawer.prototype.drawParticles = function() {
  var img = new Image();
  img.src = "../svg/numbers/0.svg";
  this.ctx.drawImage(img, 0, 0);
  console.log(assetManager);
}

Drawer.prototype.renderLoop = function() {
  requestAnimationFrame(() => { this.renderLoop() } );
  this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
  this.drawParticles();
  this.moveParticles();
}