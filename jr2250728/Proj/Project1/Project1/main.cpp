/*
 * Ruiz, Juan - Project 1 - 48130
 *
 * Project runs a game of minesweeper
 *
 */

#include <iostream>
#include <cstdlib>
#include <fstream>

enum DIFFICULTY {EASY, NORMAL, HARD};

struct MineField {
    enum DIFFICULTY {EASY, NORMAL, HARD};
    enum FLAGS {EMPTY=10, MINE, CLEAR, LOSER};
    int **data;
    int rows;
    int cols;
    DIFFICULTY d;   /// determines how many mines
    int nMines;     /// number of mines
    
};

MineField* create(int, int);
void destroy(MineField *);
void prntClr(MineField *);
void prntObscr(MineField *);
int nMines(MineField::DIFFICULTY);
void setMines(MineField *,  MineField::DIFFICULTY);
void setFlags(MineField *);
int nAdjacent(MineField *, int, int, int = MineField::MINE);
bool isClear(MineField *, int, int);
void clrArea(MineField *, int, int);
void setPerim(MineField *);
void showZeros(MineField *, int, int);
bool hasWon(MineField *);

void select(MineField *, int, int);
void setUpGame();
void prompt(int&, int&);

using namespace std;

int main(int argc, const char * argv[]) {
    setUpGame();
    
    return 0;
}

void setUpGame() {
    const int nrows = 10;
    const int ncols = 10;
    ///srand(time(0));
    MineField *mf = create(nrows, ncols);
    mf->nMines = nMines(MineField::EASY);
    setMines(mf, MineField::EASY);
    prntObscr(mf);
    int row, col;
    do {
        do {                                     /// get row input
            cout << "Enter the row: ";
            cin >> row;
        } while (row < 0 || row >= mf->rows);    /// check bounds
        do {                                     /// get column input
            cout << "Enter the column: ";
            cin >> col;
        } while (col < 0 || col >= mf->cols);    /// check bounds
        cout << endl;
        select(mf, row, col);
    } while (mf->data[row][col] != MineField::MINE && !hasWon(mf));
    
    if (hasWon(mf))
        cout << "You win\n";
    else
        mf->data[row][col]= MineField::LOSER;
    /// Print the complete minefield
    prntClr(mf);
    
    /// Write the result to a binary file
    fstream out("Result", ios::out | ios::binary);    /// open the file
    out.write(reinterpret_cast<char *>(&mf),sizeof(*mf)); /// write to the file
    out.close();
    
    
    /// Ask user if they want to see the result of the last game
    char response;
    cout << "Would you like to see the result of the last game?\n"
    "Hit 'y' if yes: ";
    cin >> response;
    if (response == 'y') {
        cout << "\nHere is the result:\n";
        /// Create space to hold the file read
        MineField *result;
        fstream in("Result", ios::in | ios::binary);
        in.read(reinterpret_cast<char *>(&result), sizeof(*result));
        prntClr(result);
        result = 0;
    }

    destroy(mf);                /// deallocate the game area
}

/// Function that creates the grid on which game will be played
MineField* create(int rows, int cols) {
    /// create a new minefield
    MineField *out = new MineField;
    out->rows=rows;
    out->cols = cols;
    out->data = new int *[rows];
    
    /// Create each row
    for (int row = 0; row != rows; ++row)
        out->data[row] = new int [cols];
    
    /// Make sure each square is empty
    for (int i = 0; i != rows; ++i)
        for (int j = 0; j != rows; ++j)
            out->data[i][j] = MineField::EMPTY;
    return out;
}

/// Function deallocates memory
void destroy(MineField *mf) {
    /// delete each dynamically allocated row
    for (int i = 0; i != mf->rows; ++i)
        delete[] mf->data[i];
    /// delete the dynamically allocated structure
    delete mf;
}

/// Functions prints the minefield with all the squares revealed.
/// used mostly after player loses
void prntClr(MineField* mf) {
    for (int row = 0; row != mf->rows; ++row){
        for (int col = 0; col != mf->cols; ++col) {
            ///
            if ( mf->data[row][col] == MineField::LOSER)
                cout << "T ";
            else
                cout << mf->data[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/// Function prints the minefield with spaces hidden
void prntObscr(MineField* mf) {
    /// Print the column index
    for (int i = 0; i != mf->cols; ++i){
        if (i==0)
            cout << "  ";
        cout << i << " ";
    }
    cout << endl;
    for (int row = 0; row != mf->rows; ++row){
        for (int col = 0; col != mf->cols; ++col){
            if(col == 0) cout << row << " ";            /// output row index
            /// KEEP EMPTY spaces and MINEs hidden
            if (mf->data[row][col] == MineField::EMPTY ||
                mf->data[row][col] == MineField::MINE)
                cout << "* ";
            /// print out the CLEARed area
            else if (mf->data[row][col] == MineField::CLEAR)
                cout << 0 << " ";
            /// Print out the actual value of the square
            else
                cout << mf->data[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/// Function returns the number of mines to set and
/// size of grid to based on the difficulty
int nMines(MineField::DIFFICULTY d) {
    if (d==MineField::EASY) return 15;
    else if (d==MineField::NORMAL) return 30;
    else if (d==MineField::HARD) return 45;
    else return 10;
}

/// Function places mines in grid
void setMines(MineField *mf,  MineField::DIFFICULTY diff) {
    /// holds how many mines will be used
    int mines = mf->nMines;
    
    /// keep looping through grid until all mines are set
    while (mines) {
        for (int i = 0; i != mf->rows; ++i) {
            for (int j = 0; j != mf->cols; ++j) {
                /// place mines if result of rand()%15 == 0
                if (rand() % 15 == 0){
                    ///only place mines if mines are still available
                    /// and current position does not have a mine
                    if (mines && mf->data[i][j] == MineField::EMPTY) {
                        mf->data[i][j] = MineField::MINE;  /// set the mine
                        --mines;         /// decrement number of mines available
                        //set = true;
                    }
                }
            }
        }
    }
}

/// Function returns how 'flag' elements surround a given square
int nAdjacent(MineField *mf, int row, int col, int FLAG) {
    int nAd=0;              /// the number of adjacent mines
    
    /// not on first or last row or first or last column
    /// most of the searches take place in this area
    if ( row > 0 && col > 0 && row < mf->rows-1 && col < mf->cols-1) {
        /// search the 3x3 grid surrounding a cell
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                if (mf->data[i][j] == FLAG)
                    ++nAd;
        }
    }
    /// on the first row, not on first or last column
    else if ( row == 0 && col > 0 && col < mf->cols - 1) {
        for (int i = row; i <= row+1; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                if (mf->data[i][j] == MineField::MINE)
                    ++nAd;
        }
    }
    /// on the last row, not on first or last column
    else if ( row == mf->rows-1 && col > 0 && col < mf->cols - 1) {
        for (int i = row-1; i <= row; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                if (mf->data[i][j] == MineField::MINE)
                    ++nAd;
        }
    }
    /// on the first column, not on first or last row
    /// search to the right
    else if ( col == 0 && row > 0 && row < mf->rows - 1) {
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col; j <= col+1; ++j)
                if (mf->data[i][j] == MineField::MINE)
                    ++nAd;
        }
    }
    /// on the last column, not on first or last row
    /// search to the left
    else if ( col == mf->cols-1 && row > 0 && row < mf->rows - 1) {
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col-1; j <= col; ++j)
                if (mf->data[i][j] == MineField::MINE)
                    ++nAd;
        }
    }
    /// top left corner
    else if (row == 0 && col == 0) {
        if (mf->data[row][col+1] == MineField::MINE) ++nAd;
        if (mf->data[row+1][col] == MineField::MINE) ++nAd;
        if (mf->data[row+1][col+1] == MineField::MINE) ++nAd;
    }
    /// top right corner
    else if (row == 0 && col == mf->cols-1) {
        if (mf->data[row][col-1] == MineField::MINE) ++nAd;
        if (mf->data[row+1][col] == MineField::MINE) ++nAd;
        if (mf->data[row+1][col-1] == MineField::MINE) ++nAd;
    }
    /// bottom left corner
    else if (row == mf->rows-1 && col == 0) {
        if (mf->data[row-1][col] == MineField::MINE) ++nAd;
        if (mf->data[row-1][col+1] == MineField::MINE) ++nAd;
        if (mf->data[row][col+1] == MineField::MINE) ++nAd;
    }
    /// bottom right corner
    else if (row == mf->rows-1 && col == mf->cols-1) {
        if (mf->data[row-1][col-1] == MineField::MINE) ++nAd;
        if (mf->data[row-1][col] == MineField::MINE) ++nAd;
        if (mf->data[row][col-1] == MineField::MINE) ++nAd;
    }
    /// return number of mines from appropriate if statement
    return nAd;
}

/// Function is true if there 0 landmines adjacent to
/// selected square
bool isClear(MineField * mf, int row, int col) {
    if (nAdjacent(mf, row, col))
        return false;            /// there was at least one mine adjacent
    return true;                 /// area was clear
}

void showZeros(MineField *mf, int row, int col) {
    /// check bounds
    if ( row >= mf->rows || row < 0 || col >= mf->cols || col < 0)
        return;
    if (isClear(mf, row, col) && mf->data[row][col] != MineField::CLEAR){
        mf->data[row][col] = MineField::CLEAR;
        showZeros(mf, row+1, col); /// go up one row
        showZeros(mf, row-1, col); /// go down one row
        showZeros(mf, row, col+1); /// go right one col
        showZeros(mf, row, col-1); /// go left one col
    }
    /// space was not clear or already shown
    else
        return;
}

/// Function shows how many mines are adjacent to selected square
void setFlags(MineField *mf) {
    for (int i = 0; i != mf->rows; ++i)
        for (int j = 0; j != mf->cols; ++j)
            /// don't look for adjacent mines in areas where
            /// mine is already located
            if (mf->data[i][j] != MineField::MINE)
                mf->data[i][j] = nAdjacent(mf, i, j);
}

/// Function reveals what is underneath the selected square
/// that the user has selected
void select(MineField * mf, int row, int col) {
    /// check if user selected a losing square
    if (mf->data[row][col] == MineField::MINE) {
        cout << "You lose\n"                    /// Output message informing
        "The t marks your grave.\n"     ///  user of their loss
        "Goodbye.\n\n";
        setFlags(mf);                           /// set all the spaces
        /// before printing
    }
    /// Square is a zero, clear the surrounding area if necessary
    else if (isClear(mf, row, col) ){
        showZeros(mf, row, col); /// show cleared area
        setPerim(mf);
        prntObscr(mf);
    }
    /// Square had adjacent landmine
    /// reveal the number to the user
    else {
        mf->data[row][col] = nAdjacent(mf, row, col);
        prntObscr(mf);
    }
}

/// Function checks whether the player has won
bool hasWon(MineField *mf) {
        for (int i = 0; i != mf->rows; ++i)
            for (int j = 0; j != mf->cols; ++j)
                /// if there are empty spaces player has not won
                if (mf->data[i][j] == MineField::EMPTY)
                    return false;
        /// there were no empty spaces left. Player has won
        return true;
    }

/// Function find the perimeter of the cleared areas
void setPerim(MineField *mf) {
    for (int row = 0; row != mf->rows; ++row ) {
        /// avoid search at left and right edge of array
        for (int col = 0; col != mf->cols; ++col) {
            /// when you're not on the bounds of the array
            if (row > 0 && row < mf->rows-1
                && col > 0 &&  col <mf->cols-1)
                if (mf->data[row][col] == MineField::CLEAR) {
                    /// check that the previous number has mines adjacent
                    if (mf->data[row][col-1] != MineField::CLEAR)
                        mf->data[row][col-1] = nAdjacent(mf, row, col-1);
                    /// check if the next number has mines adjacent
                    if (mf->data[row][col+1] != MineField::CLEAR)
                        mf->data[row][col+1] = nAdjacent(mf,row, col+1);
                    if (mf->data[row-1][col] != MineField::CLEAR)
                        mf->data[row-1][col] = nAdjacent(mf, row-1, col);
                    /// check if the next number has mines adjacent
                    if (mf->data[row+1][col] != MineField::CLEAR)
                        mf->data[row+1][col] = nAdjacent(mf,row+1, col);
                }
        }
    }
}
