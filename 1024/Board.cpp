#include <iostream>
#include "Board.hpp"
#include <typeinfo>
#include <iomanip>
#include <vector>

// Board::Board():Board(3,3) {
// }

// Board::Board(int m):Board(m,m) {

// }

// Board::Board(int m, int n) {
//     if(m >= 1 && n >= 1) {
//         numRows = m;
//         numCols = n;
//     } else {
//         numRows = 3;
//         numCols = 3;
//     }

//     panel = new int*[numRows];
//     for(int i = 0; i<numRows;i++) {
//         panel[i] = new int[numCols];
//         for(int j = 0; j < numCols; j++)
//             panel[i][j] = 0;
//     }
//     target = 32;
//     max = 0;

// }

Board::~Board()
{
    // for(int i = 0; i < numRows; i++) {
    //     delete[]  panel[i];
    //     panel[i] = nullptr;
    // }

    int i = 0;
    while (i < numRows)
    {
        delete[] panel[i];
        panel[i] = nullptr;
        i++;
    }

    delete[] panel;
    panel = nullptr;
}

void Board::print() const
{
    //    std::cout << typeid(**panel).name() << std::endl;

    int row = 0;
    while (row < numRows)
    {
        int col = 0;
        while (col < numCols)
        {
            std::cout << "+----";
            col++;
        }
        std::cout << "+" << std::endl;
        col = 0;
        while (col < numCols)
        {
            std::cout << "|" << std::setw(4);
            if (panel[row][col] != 0)
            {
                std::cout << std::setw(4) << panel[row][col];
            }
            else
            {
                std::cout << "    ";
            }
            col++;
        }
        std::cout << "|" << std::endl;
        row++;
    }

    //Fill last bottom
    int col = 0;
    while (col < numCols)
    {
        std::cout << "+----";
        col++;
    }
    std::cout << "+" << std::endl;
}

void Board::selectRandomCell(int &row, int &col)
{
    struct Coor
    {
        int row;
        int col;
    };

    std::vector<Coor> emptyCells;

    Coor cell;

    int i = 0;
    while (i < numRows)
    {
        int j = 0;
        while (j < numCols)
        {
            if (panel[i][j] == 0)
            {
                cell.row = i;
                cell.col = j;
                emptyCells.push_back(cell);
            }
            j++;
        }
        i++;
    }

    int size = emptyCells.size();
    switch (size)
    {
    case 0:
        if (noAdjacentSameValue() && max < target)
        {
            std::cout << "Game over. Try again." << std::endl;
            exit(0);
        }
        else
            return;
        break;

    default:
        //srand(time ( NULL ));
        int index = rand() % size;
        Coor element = emptyCells[index];
        row = element.row;
        col = element.col;
        panel[element.row][element.col] = 1;
        break;
    }

    print();

    if (size == 1 && noAdjacentSameValue() == true && max < target)
    {
        std::cout << "Game over. Try again." << std::endl;
        exit(0);
    }
}

bool Board::noAdjacentSameValue() const
{
    // check value in horizontal direction
    int i = 0;
    while (i < numRows)
    {
        int j = 0;
        while (j < numCols - 1)
        {
            if (panel[i][j] == panel[i][j + 1])
            {
                return false;
            }
            j++;
        }
        i++;
    }

    //check same value in vertial direction
    int j = 0;
    while (j < numCols)
    {
        int i = 0;
        while (i < numRows - 1)
        {
            if (panel[i][j] == panel[i + 1][j])
            {
                return false;
            }
            i++;
        }
        j++;
    }

    return true;
}

void Board::start()
{
    int a = 0;
    int b = 0;
    selectRandomCell(a, b);
}

void Board::pressDown() {

  int * temp = new int[numRows];
  int toWrite;

  int j = 0;
  while (j < numCols) {

    int k = 0;
    while (k < numRows) {
      temp[k] = 0;
      k++;
    }

    toWrite = numRows - 1; //next position to write in temp

    int i = numRows - 1;
    while (i >= 0) {
      if (panel[i][j] > 0) {
        temp[toWrite] = panel[i][j];
        toWrite--;
      }
      i--;
    }

    k = numRows - 1;
    while (k > 0) {
      if (temp[k] == temp[k - 1]) {
        temp[k] *= 2;
        if (max < temp[k]) {
          max = temp[k];
        }
        temp[k - 1] = 0;
        k--;
      }
      k--;
    }

    i = numRows - 1; //to write in jth comumn of panel
    k = numRows - 1;

    for (; k >= 0; k--) {
      if (temp[k] > 0) {
        panel[i][j] = temp[k];
        i--;
      }
    }

    for (; i >= 0; i--) {
      panel[i][j] = 0;
    }

    j++;
  }

  delete[] temp;
  temp = nullptr;

  int row = -1;
  int col = -1;
  selectRandomCell(row, col);
}


void Board::pressUp() {
  int * temp = new int[numRows];
  int toWrite;

  int j = 0;
  while (j < numCols) {

    int k = 0;
    while (k < numRows) {
      temp[k] = 0;
      k++;
    }

    toWrite = 0;

    int i = 0;
    while (i < numRows) {
      if (panel[i][j] > 0) {
        temp[toWrite] = panel[i][j];
        toWrite++;
      }
      i++;
    }

    k = 0;
    while (k < numRows) {
      if (temp[k] == temp[k + 1]) {
        temp[k + 1] *= 2;
        if (max < temp[k]) {
          max = temp[k];
        }
        temp[k] = 0;
        k++;
      }
      k++;
    }

    i = 0;
    k = 0;
    for (; k < numRows; k++) {
      if (temp[k] > 0) {
        panel[i][j] = temp[k];
        i++;
      }
    }

    for (; i < numRows; i++) {
      panel[i][j] = 0;
    }

    j++;
  }

  delete[] temp;
  temp = nullptr;

  int row = -1;
  int col = -1;
  selectRandomCell(row, col);
}

void Board::pressLeft() {
  int * temp = new int[numCols];
  int toWrite;

  int j = 0;
  while (j < numRows) {
    int k = 0;
    while (k < numCols) {
      temp[k] = 0;
      k++;
    }

    toWrite = 0;

    int i = 0;
    while (i < numCols) {
      if (panel[j][i] > 0) {
        temp[toWrite] = panel[j][i];
        toWrite++;
      }
      i++;
    }

    j = 0;
    while (j < numCols) {

      if (temp[j] == temp[j + 1]) {
        temp[j + 1] *= 2;

        if (max < temp[j]) {
          max = temp[j];
        }

        temp[j] = 0;
        j++;
      }

      j++;
    }

    i = 0;
    k = 0;
    for (; k < numCols; k++) {
      if (temp[k] > 0) {
        panel[j][i] = temp[k];
        i++;
      }
    }

    for (; i < numCols; i++) {
      panel[j][i] = 0;
    }
  }

  delete[] temp;
  temp = nullptr;

  int row = -1;
  int col = -1;
  selectRandomCell(row, col);
}

void Board::pressRight()
{
    int *temp = new int[numCols];
    int toWrite;

    int j = 0;
    while (j < numRows)
    {
        int k = 0;
        while (k < numCols)
        {
            temp[k] = 0;
            k++;
        }

        toWrite = numCols - 1;

        int i = numCols - 1;
        while (i >= 0)
        {
            if (panel[j][i] > 0)
            {
                temp[toWrite] = panel[j][i];
                toWrite--;
            }
            i--;
        }

        for (int j = numCols - 1; j > 0; j--)
        {
            if (temp[j] == temp[j - 1])
            {
                temp[j] *= 2;

                if (max < temp[j])
                {
                    max = temp[j];
                }

                temp[j - 1] = 0;
                j--;
            }
        }

        i = numCols - 1;
        k = numCols - 1;
        for (; k >= 0; k--)
        {
            if (temp[k] > 0)
            {
                panel[j][i] = temp[k];
                i--;
            }
        }

        for (; i >= 0; i--)
        {
            panel[j][i] = 0;
        }
        j++;
    }

    delete[] temp;
    temp = nullptr;

    int row = -1;
    int col = -1;
    selectRandomCell(row, col);
}
