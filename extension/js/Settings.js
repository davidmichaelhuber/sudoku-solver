var Settings = (function() {
  var params = {
    'NMH_NAME': 'sudoku_solver',
    'NMH_STATUS_KEY': 'status',
    'NMH_UNSOLVED_KEY': 'unsolved',
    'NMH_SOLVED_KEY': 'solved',
    'NMH_TRIES_KEY': 'tries',
    'NMH_SUDOKU_KEY': 'sudoku',
    'NMH_SKIP_SOLUTION_COUNT_KEY': 'skip_solution_count',
    'NMH_TICK_KEY': 'tick',
    'CANVAS_WIDTH': '1280',
    'CANVAS_HEIGHT': '720',
    'MAX_FPS': '1',
    'UNSOLVED_SUDOKU_AMOUNT': '5',
    'SOLVED_SUDOKU_AMOUNT': '10',
    'MAX_PARTICLE_SPEED': '5',
    'TICK_INTERVAL': '250'
  };
  return {
    get: function(key) {
      return params[key];
    },
    set: function(key, val) {
      params[key] = val;
    }
  };
})();