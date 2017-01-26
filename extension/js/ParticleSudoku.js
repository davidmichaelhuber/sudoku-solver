var ParticleSudoku = function(sudoku) {
  this.particles = [];
  for(var i = 0; i < sudoku.fields.length; i++) {
    this.particles[i] = new Particle(Number(sudoku.fields[i]));
  };
};