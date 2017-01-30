var Sudoku = function(fields, solved) {
  this.fields = fields;
  this.solved = solved;
  /* Not implemented yet
  this.tries = tries; */
  this.particles = [];
  for(var i = 0; i < fields.length; i++) {
    this.particles.push(new Particle(fields[i]));
  }
};