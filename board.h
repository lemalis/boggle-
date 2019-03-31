#ifndef board_h
#define board_h


typedef struct GuiTile {
    char value;
    int visited;
} GuiTile;

typedef struct GameBoard {
    int size;
    int vertices;
    GuiTile ** adj;
} GameBoard;


GameBoard * createGameBoard( int size);
void freeGameBoard(GameBoard * board);
void unvisitGameBoard(GameBoard * board);
void displayBoard(int size, GameBoard* board);


#endif /* board_h */
