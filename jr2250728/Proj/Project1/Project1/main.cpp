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
    /// Determines how many mines to set
    enum DIFFICULTY {EASY, NORMAL, HARD};
    /// Flags representing various square possibilities
    enum FLAGS {EMPTY=10, MINE, CLEAR, LOSER};
    short **data;      /// This is the minefield
    short rows;        /// number of rows
    short cols;        /// Number of columns
    DIFFICULTY d;    /// determines how many mines
    short mines;       /// number of mines
};

MineField* create(short, short);
void destroy(MineField *);
void prntClr(MineField *);
void prntObscr(MineField *);
void nMines(MineField *, MineField::DIFFICULTY);
void setMines(MineField *);
void setFlags(MineField *);
short nAdjacent(MineField *, short, short, short = MineField::MINE);
bool isClear(MineField *, short, short);
void clrArea(MineField *, short, short);
void setPerim(MineField *);
void showZeros(MineField *, short, short);
bool hasWon(MineField *);
void rwFile(MineField *);
void fields();
bool cont(MineField *, short, short);
void playGame();
void prompt(short&, short&);
char * userName();
using namespace std;


int main(int argc, const char * argv[]) {
    playGame();
    //fields();
    return 0;
}

void playGame() {
    const short nrows = 10;
    const short ncols = 10;
    srand(time(0));
    /// Get the user name
    char *player = userName();
    MineField *mf = create(nrows, ncols);
    nMines(mf, MineField::EASY);
    setMines(mf);
    prntObscr(mf);
    short row, col;
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
    } while (cont(mf, row, col) && !hasWon(mf));
    /// Prepare to print completed minefield
    if (hasWon(mf)) {
        cout << player << "You win\n";
        setFlags(mf);
    }
    else{
        cout << player << "you have lost\n";
        setFlags(mf);
        mf->data[row][col]= MineField::LOSER;
    }
    /// Print the complete minefield
    prntClr(mf);
    
    /// write and read binary file
    rwFile(mf);
    delete player;
    destroy(mf);                /// deallocate the game area
}

char *userName() {
    cout << "Enter your name: ";
    string in;
    cin >> in;
    
    short size = in.size();
    char *name = new char[size+1]; /// make room for '\0'
    for (short i = 0; i != size; ++i) {
        *(name+i) = in[i];
    }
    *(name+size+1) = '\0';
    
    return name;
}

/// Function that creates the grid on which game will be played
MineField* create(short rows, short cols) {
    /// create a new minefield
    MineField *out = new MineField;
    out->rows=rows;
    out->cols = cols;
    out->data = new short *[rows];
    
    /// Create each row
    for (short row = 0; row != rows; ++row)
        out->data[row] = new short [cols];
    
    /// Make sure each square is empty
    for (short i = 0; i != rows; ++i)
        for (short j = 0; j != rows; ++j)
            out->data[i][j] = MineField::EMPTY;
    return out;
}

/// Function deallocates memory
void destroy(MineField *mf) {
    /// delete each dynamically allocated row
    for (short i = 0; i != mf->rows; ++i)
        delete[] mf->data[i];
    /// delete the dynamically allocated structure
    delete mf;
}

/// Functions prints the minefield with all the squares revealed.
/// used mostly after player loses
void prntClr(MineField* mf) {
    for (short row = 0; row != mf->rows; ++row){
        for (short col = 0; col != mf->cols; ++col) {
            ///
            if ( *(*(mf->data+row) + col) == MineField::LOSER)
                cout << "T ";
            else if (*(*(mf->data+row) + col) == MineField::MINE)
                cout << "x ";
            else if (!isClear(mf, row, col))
                     cout << nAdjacent(mf, row, col) << " ";
            else
                cout << "0 ";
        }
        cout << endl;
    }
    cout << endl;
}

/// Function prints the minefield with spaces hidden
void prntObscr(MineField* mf) {
    /// Print the column index
    for (short i = 0; i != mf->cols; ++i){
        if (i==0)
            cout << "  ";
        cout << i << " ";
    }
    cout << endl;
    for (short row = 0; row != mf->rows; ++row){
        for (short col = 0; col != mf->cols; ++col){
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

/// Function returns the number of mines to set based on difficulty
void nMines(MineField *mf, MineField::DIFFICULTY d) {
    if (d==MineField::EASY)
        mf->mines = 15;
    else if (d==MineField::NORMAL)
        mf->mines = 30;
    else if (d==MineField::HARD)
        mf->mines = 45;
}

/// Function places mines in grid
void setMines(MineField *mf) {
    /// holds how many mines will be used
    short mines = mf->mines;
    
    /// keep looping through grid until all mines are set
    while (mines) {
        for (short i = 0; i != mf->rows; ++i) {
            for (short j = 0; j != mf->cols; ++j) {
                /// place mines if result of rand()%15 == 0
                if ((rand() % 100) % 10 == 0){
                    ///only place mines if mines are still available
                    /// and current is empty
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
short nAdjacent(MineField *mf, short row, short col, short FLAG) {
    short nAd=0;              /// the number of adjacent mines
    
    /// not on first or last row or first or last column
    /// most of the searches take place in this area
    if ( row > 0 && col > 0 && row < mf->rows-1 && col < mf->cols-1) {
        /// search the 3x3 grid surrounding a cell
        for (short i = row-1; i <= row+1; ++i) {
            for (short j = col-1; j <= col+1; ++j)
                if (mf->data[i][j] == FLAG)
                    ++nAd;
        }
    }
    /// on the first row, not on first or last column
    else if ( row == 0 && col > 0 && col < mf->cols - 1) {
        for (short i = row; i <= row+1; ++i) {
            for (short j = col-1; j <= col+1; ++j)
                if (mf->data[i][j] == MineField::MINE)
                    ++nAd;
        }
    }
    /// on the last row, not on first or last column
    else if ( row == mf->rows-1 && col > 0 && col < mf->cols - 1) {
        for (short i = row-1; i <= row; ++i) {
            for (short j = col-1; j <= col+1; ++j)
                if (mf->data[i][j] == MineField::MINE)
                    ++nAd;
        }
    }
    /// on the first column, not on first or last row
    /// search to the right
    else if ( col == 0 && row > 0 && row < mf->rows - 1) {
        for (short i = row-1; i <= row+1; ++i) {
            for (short j = col; j <= col+1; ++j)
                if (mf->data[i][j] == MineField::MINE)
                    ++nAd;
        }
    }
    /// on the last column, not on first or last row
    /// search to the left
    else if ( col == mf->cols-1 && row > 0 && row < mf->rows - 1) {
        for (short i = row-1; i <= row+1; ++i) {
            for (short j = col-1; j <= col; ++j)
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
bool isClear(MineField * mf, short row, short col) {
    if (nAdjacent(mf, row, col))
        return false;            /// there was at least one mine adjacent
    return true;                 /// area was clear
}

void showZeros(MineField *mf, short row, short col) {
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
/// for the entire minefield
void setFlags(MineField *mf) {
    for (short i = 0; i != mf->rows; ++i)
        for (short j = 0; j != mf->cols; ++j)
            /// don't look for adjacent mines in areas where
            /// mine is already located
            if (mf->data[i][j] != MineField::MINE)
                mf->data[i][j] = nAdjacent(mf, i, j);
}

/// Function reveals what is underneath the square that the user has selected
/// and whether to continue based on what is revealed
/// i.e selecting a mines means you lost
bool cont(MineField * mf, short row, short col) {
    /// check if user selected a losing square
    if (mf->data[row][col] == MineField::MINE)
        return false;

    /// Square is a zero, clear the surrounding area if necessary
    else if (isClear(mf, row, col) ){
        showZeros(mf, row, col); /// show cleared area
        setPerim(mf);
        prntObscr(mf);
        return true;
    }
    /// Square had adjacent mine
    /// reveal the number to the user
    else {
        mf->data[row][col] = nAdjacent(mf, row, col);
        prntObscr(mf);
        return true;
    }
}

/// Function checks whether the player has won
bool hasWon(MineField *mf) {
        for (short i = 0; i != mf->rows; ++i)
            for (short j = 0; j != mf->cols; ++j)
                /// if there are empty spaces player has not won
                if (mf->data[i][j] == MineField::EMPTY)
                    return false;
        /// there were no empty spaces left. Player has won
        return true;
    }

/// Function find the perimeter of the cleared areas
void setPerim(MineField *mf) {
    for (short row = 0; row != mf->rows; ++row ) {
        /// avoid search at left and right edge of array
        for (short col = 0; col != mf->cols; ++col) {
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
                    /// check the adjacent corners
                    if (mf->data[row+1][col-1] != MineField::CLEAR)
                        mf->data[row-1][col-1] = nAdjacent(mf,row-1, col-1);
                    if (mf->data[row-1][col+1] != MineField::CLEAR)
                        mf->data[row-1][col+1] = nAdjacent(mf,row-1, col+1);
                    if (mf->data[row+1][col-1] != MineField::CLEAR)
                        mf->data[row+1][col-1] = nAdjacent(mf,row+1, col-1);
                    if (mf->data[row+1][col+1] != MineField::CLEAR)
                        mf->data[row+1][col+1] = nAdjacent(mf,row+1, col+1);  
                }
        }
    }
}

/// This function writes to and reads from a binary file
void rwFile(MineField *mf) {
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
        cout << "\nResult of your last game:\n";
        /// Create space to hold the file read
        MineField *result;
        fstream in("Result", ios::in | ios::binary);
        in.read(reinterpret_cast<char *>(&result), sizeof(*result));
        prntClr(result);
        result = 0;
    }
}

/// This function is to show that I can create an array of structures
void fields() {
    cout << "How many mine fields do you want to see: ";
    int n;
    cin >> n;
    
    MineField **mf = new MineField*[n];
    const int row = 10;
    const int col = 10;
    /// create the fields
    for (int i = 0; i != n; ++i) {
        mf[i] = create(row, col);               /// Create each field
        nMines(*(mf+i), MineField::EASY);
        setMines(*(mf+i));   /// place the mines
        setFlags(*(mf+i));                      ///  set the flags
        prntClr(*(mf+i));
        cout << endl;   
    }
    cout << endl;
    
    for (int i = 0; i != n; ++i) {
        destroy(*(mf+i));
    }
    delete mf;
}