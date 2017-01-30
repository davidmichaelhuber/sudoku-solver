var SudokuStorage = function() {
  this.unsolvedSudokus = [];
  this.solvedSudokus = [];
};

SudokuStorage.prototype.addUnsolvedSudoku = function(fields) {
  if(this.unsolvedSudokus.length >= Settings.get('UNSOLVED_SUDOKU_AMOUNT')) {
    this.unsolvedSudokus.shift();
  }
  var sudoku = new Sudoku(fields, false);
  this.unsolvedSudokus.push(sudoku);
}

SudokuStorage.prototype.addSolvedSudoku = function(fields) {
  if(this.solvedSudokus.length >= Settings.get('SOLVED_SUDOKU_AMOUNT')) {
    this.solvedSudokus.shift();
  }
  var sudoku = new Sudoku(fields, true);
  this.solvedSudokus.push(sudoku);
}

SudokuStorage.prototype.clearUnsolvedSudokus = function() {
  this.unsolvedSudokus = [];
}

SudokuStorage.prototype.clearSolvedSudokus = function() {
  this.solvedSudokus = [];
}