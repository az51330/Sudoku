#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include <iostream>

class sudokuboard {
 public:
  sudokuboard();

  bool can_place(size_t r,size_t c,char n) const;
  // PRE: 0 <= r,c < 9
  // Return true iff position (r,c) is blank and 
  // n does not appear on this board in the given row, column, 
  // or box containing (r,c)

  void place(size_t r,size_t c, char n);
  // PRE: can_place(r, c, n)
  // make the cell at position (r,c) equal to n.
  
  bool solved() const;
  // Return true iff no cell is blank.

  void write(std::ostream & ostr) const;
  // Print this board on the given output stream

  char get(size_t r,size_t c) const;
  // PRE: 0 <= r,c < 9
  // Return the character at position (r,c)

  void remove(size_t r,size_t c);
  // PRE: 0 <= r,c < 9; at(r,c) != '_'
  // Remove the character at position (r,c)
  //  (make it '_')

 private:
  std::string rows[9];

};


#endif
