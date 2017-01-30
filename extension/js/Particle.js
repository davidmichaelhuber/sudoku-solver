var Particle = function(val) {
  this.val = val;
  // TODO: Update x and y on window resize
  this.x = Math.floor(Math.random() * Settings.get('CANVAS_WIDTH')) + 0;
  this.y = Math.floor(Math.random() * Settings.get('CANVAS_HEIGHT')) + 0;
  this.dx = Math.floor(Math.random() * Settings.get('MAX_PARTICLE_SPEED')) -
                      (Settings.get('MAX_PARTICLE_SPEED') / 2);
  this.dy = Math.floor(Math.random() * Settings.get('MAX_PARTICLE_SPEED')) -
                      (Settings.get('MAX_PARTICLE_SPEED') / 2);
};