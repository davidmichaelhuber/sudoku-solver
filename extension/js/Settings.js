var Settings = (function() {
  var params = {
    'NMH_NAME': 'sudoku_solver',
    'NMH_SUDOKU_KEY': 'key',
    'NMH_SKIP_SOLUTION_COUNT_KEY': 'skip_solution_count',
    'NMH_TICK_KEY': 'tick',
    'CANVAS_WIDTH': '1280',
    'CANVAS_HEIGHT': '720',
    'MAX_FPS': '1',
    'HISTORY_AMOUNT': '5',
    'MAX_PARTICLE_SPEED': '5',
    'TICK_INTERVAL': '250'
  };
  return {
    get: function(key) {
      return params[key];
    }
  };
})();