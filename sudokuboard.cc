#include "sudokuboard.h"
#include <cassert>
#include <iostream>
#include <cmath>

#define DIM 9


sudokuboard::sudokuboard()
{
  // Make an empty board.  (This constructor provided by Prof. Campbell)
  for (int i=0;i<DIM;i++) {
    rows[i] = "";
    for (int j=0;j<DIM;j++)
      rows[i] = rows[i] + "_";
  }
}

bool sudokuboard::can_place(size_t r,size_t c,char n) const
{
  // pre: make sure r,c is in board
  assert(c < 9);
  assert(r < 9);
  // check if empty
  if (rows[r][c] != '_')
    return false;
  // check rows and cols for matching numbers to n
  for(size_t i = 0; i < 9; ++i){
    if (rows[r][i] == n)
      return false;
    if (rows[i][c] == n)
      return false;
  }
  // check box for matching numbers to n
  // box_start variables are 3*(r/3) bc that will give 0 for 0-2, 3 for 3-5
  // and 6 for 6-8 then just need to check 9 spaces in each miny grid starting
  // at these new locations for numbers = n
  size_t box_r_start = (r / 3) * 3;
  size_t box_c_start = (c / 3) * 3;
  size_t end_r = box_r_start + 3;
  size_t end_c = box_c_start + 3;
  for(;box_r_start < end_r; ++box_r_start){
    for(size_t j = box_c_start; j < end_c; ++j){
      if (rows[box_r_start][j] == n){
        return false;
      }
    }
  }
  // if it passes all of these then it is able to be placed
  return true;
}


bool sudokuboard::solved() const
{
  // This method provided by Professor Campbell
  for (int i=0;i<DIM;i++)
    if (rows[i].find('_')<(size_t)DIM)
      return false;
  return true;
}

void sudokuboard::write(std::ostream & ostr) const
{
  // This method provided by Professor Campbell
  for (int i=0;i<DIM;i++)
    ostr << rows[i] << std::endl;
}

void sudokuboard::place(size_t r,size_t c,char n)
{
  // pre: check that place is a possible position for n
  // assert(can_place(r, c, n));
  // needed to comment out precondition because it would not allow me to
  // make the board in the beginning, only called after a can_place besides
  // when taking input to make board
  // set location to number
  rows[r][c] = n;
}

char sudokuboard::get(size_t r,size_t c) const
{
  // pre: r,c is in board
  assert(c < 9);
  assert(r < 9);
  // return what is at the location
  return rows[r][c];
}

void sudokuboard::remove(size_t r,size_t c)
{
  // pre: r,c is in board
  assert(c < 9);
  assert(r < 9);
  // set location to _ which is empty
  rows[r][c] = '_';
}
