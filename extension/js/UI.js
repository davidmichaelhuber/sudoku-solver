var UI = function(nmhListener) {
  this.nmhListener = nmhListener;
  this.canvasWrapper =  document.getElementById("canvas-wrapper");
  this.controlsWrapper = document.getElementById("controls-wrapper");
  this.pickSudokuButton = document.getElementById("pick-sudoku-button");
  this.sudokuSolverCanvas = document.getElementById("sudoku-solver-canvas");
  this.setButtonHandlers();
};

UI.prototype.setButtonHandlers = function() {
  this.pickSudokuButton.onclick = (() => { this.pickSudoku() });
}

UI.prototype.pickSudoku = function() {
  var sudokuFields = this.pickSudokuButton.dataset.sudokuFields;
  var skipSolutionCount = this.pickSudokuButton.dataset.skipSolutionCount;
  this.nmhListener.writeSudokuFields(sudokuFields, skipSolutionCount);
}