#include <iostream>
#include <cassert>
#include "sudokuboard.h"
#include "stack.h"


void make_board(sudokuboard &board)
{
  // take every string given as input and take each entry and place it into
  // the board
  std::string input;
  for(size_t r = 0; r < 9; ++r){
    std::cin >> input;
    for(size_t c = 0; c < 9; ++c)
      board.place(r, c, input[c]);
  }
}


void find_least_options(sudokuboard &board, stack &rows, stack &cols, stack &nums)
{
  // find most constricted location
  // amount of possible numbers can never be >9 so 10 will be changed with any
  // num coming first
  size_t smallest = 10;
  size_t count;
  size_t row;
  size_t col;
  // check every place with every num and count how many numbers work at that
  // location, set location with smallest count to row and col then push them
  // on the row col stacks
  for(size_t r = 0; r < 9; ++r)
    for(size_t c = 0; c < 9; ++c){
      count = 0;
      for(size_t num = 1; num <= 9; ++num){
        if (board.can_place(r, c, num))
          count++;
      }
      if ((count < smallest) and (count != 0)){
        smallest = count;
        row = r;
        col = c;
      }
    }
  rows.push(row);
  cols.push(col);
  // push ten as a place holder, since this num is impossible in the board
  // it tells the next function to start checking at 1
  nums.push(10);
}


void try_nums(sudokuboard &board, stack &rows, stack &cols, stack &nums)
{
  size_t start_num;
  char num_char;
  // if top num is ten start at 1
  if ((nums.top() == 10) or (nums.empty())){
    start_num = 1;
    nums.pop();
  }
  else {
    // start at top +1 if it's not to continue (for back tracking)
    start_num = nums.top() + 1;
    nums.pop();
  }
  // loop till nine, change start_num to a char so it can be passed correctly
  // if it can be placed, place it and push it onto number stack and end
  // function to go find next loc
  for(; start_num <= 9; ++start_num){
    num_char = '0' + start_num;
    if (board.can_place(rows.top(), cols.top(), num_char)){
      board.place(rows.top(), cols.top(), num_char);
      nums.push(start_num);
      return;
    }
  }
  // if no numbers work, get rid of this row and col and try a new number
  // in the last location saved by running this function again
  rows.pop();
  cols.pop();
  board.remove(rows.top(), cols.top());
  try_nums(board, rows, cols, nums);
}


int main()
{
  // create board and row col and number stacks
  sudokuboard board;
  stack rows;
  stack cols;
  stack nums;
  make_board(board);
  // until solved attempt to place numbers to solve it
  while(!board.solved()){
    find_least_options(board, rows, cols, nums);
    try_nums(board, rows, cols, nums);
  }
  // once it is solved, output the board
  board.write(std::cout);
}
