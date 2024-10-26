/***********************************************************************
 * Source File:
 *    TEST PAWN
 * Author:
 *    Nathan Bird, Jared Davey, Brock Hoskins
 * Summary:
 *    The unit tests for the pawn
 ************************************************************************/

#include "board.h"
#include "move.h"
#include "piece.h"
#include "piecePawn.h"
#include "pieceType.h"
#include "testPawn.h"
#include "unitTest.h"
#include <set>


 /*************************************
  * GET MOVES TEST Simple
  * White pawn in the middle of the board: b4
  *
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5     .               5
  * 4    (p)              4
  * 3                     3
  * 2                     2
  * 1                     1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestPawn::getMoves_simpleWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*fWhite*/);
   pawn.position.set(1, 3);
   pawn.fWhite = true;
   pawn.nMoves = 1;
   board.board[1][3] = &pawn;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 1);
   assertUnit(moves.find(Move("b4b5")) != moves.end());

   // TEARDOWN
   board.board[1][3] = nullptr;
}

/*************************************
 * GET MOVES TEST Simple
 * Black pawn in the middle of the board: b4
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4    (P)              4
 * 3     .               3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_simpleBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*fWhite*/);
   pawn.position.set(1, 3);
   pawn.nMoves = 1;
   pawn.fWhite = false;
   board.board[1][3] = &pawn;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 1);
   assertUnit(moves.find(Move("b4b3")) != moves.end());

   // TEARDOWN
   board.board[1][3] = nullptr;
}


/*************************************
 * GET MOVES TEST InitialAdvance
 * White pawn initial advance
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4     .               4
 * 3     .               3
 * 2    (p)              2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*fWhite*/);
   pawn.position.set(1, 1);
   pawn.fWhite = true;
   pawn.nMoves = 0;
   board.board[1][1] = &pawn;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("b2b3")) != moves.end());
   assertUnit(moves.find(Move("b2b4")) != moves.end());
   

   // TEARDOWN
   board.board[1][1] = nullptr;
}

/*************************************
 * GET MOVES TEST InitialAdvance
 * Black pawn initial advance
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7      (P)            7
 * 6       .             6
 * 5       .             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*fWhite*/);
   pawn.position.set(2, 6);
   pawn.fWhite = false;
   pawn.nMoves = 0;
   board.board[2][6] = &pawn;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("c7c6")) != moves.end());
   assertUnit(moves.find(Move("c7c5")) != moves.end());
   
   // TEARDOWN
   board.board[2][6] = nullptr;
}


/*************************************
 * GET MOVES TEST Capture
 * Double capture: move pawn to b6 and capture
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7   P P P             7
 * 6    (p)              6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureWhite()
{
          // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*fWhite*/);
   pawn.position.set(1, 5);
   pawn.fWhite = true;
   pawn.nMoves = 1;
   board.board[1][5] = &pawn;
   Black black1(PAWN);
   board.board[0][6] = &black1;
   Black black2(PAWN);
   board.board[1][6] = &black2;
   Black black3(PAWN);
   board.board[2][6] = &black3;
   set <Move> moves;
   

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("b6c7p")) != moves.end());
   assertUnit(moves.find(Move("b6a7p")) != moves.end());
   

   // TEARDOWN
   board.board[1][5] = nullptr;
   board.board[0][6] = nullptr;
   board.board[1][6] = nullptr;
   board.board[2][6] = nullptr;
}


/*************************************
 * GET MOVES TEST Capture
 * Double capture: move pawn to b6 and capture
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6    (P)              6
 * 5   p p p             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*fWhite*/);
   pawn.position.set(1, 5);
   pawn.fWhite = false;
   pawn.nMoves = 1;
   board.board[1][5] = &pawn;
   White white1(PAWN);
   board.board[0][4] = &white1;
   White white2(PAWN);
   board.board[1][4] = &white2;
   White white3(PAWN);
   board.board[2][4] = &white3;
   set <Move> moves;
   

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("b6a5p")) != moves.end());
   assertUnit(moves.find(Move("b6c5p")) != moves.end());
   

   // TEARDOWN
   board.board[1][5] = nullptr;
   board.board[0][4] = nullptr;
   board.board[1][4] = nullptr;
   board.board[2][4] = nullptr;
}

/*************************************
 * GET MOVES TEST Enpassant
 * Enpassant b5a6E
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6   . P .             6
 * 5   P(p)P             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*fWhite*/);
   pawn.position.set(1, 4);
   pawn.fWhite = true;
   pawn.nMoves = 1;
   board.board[1][4] = &pawn;
   Black black1(PAWN);
   black1.lastMove = 1;
   board.board[0][4] = &black1;
   Black black2(PAWN);
   board.board[1][5] = &black2;
   Black black3(PAWN); 
   black3.lastMove = 1;
   board.board[2][4] = &black3;
   board.numMoves = 1;
   set <Move> moves;
   
   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("b5a6E")) != moves.end());
   assertUnit(moves.find(Move("b5c6E")) != moves.end());

   // TEARDOWN
   board.board[1][4] = nullptr; // pawn
   board.board[0][4] = nullptr; // black1
   board.board[1][5] = nullptr; // black2
   board.board[2][4] = nullptr; // black3
}


/*************************************
 * GET MOVES TEST Enpassant
 * Enpassant f4g3E
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4           p(P)p     4
 * 3           . p .     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*fWhite*/);
   pawn.position.set(5, 3);
   pawn.fWhite = false;
   pawn.nMoves = 1;
   board.board[5][3] = &pawn;
   White white1(PAWN);
   white1.lastMove = 1;
   White white2(PAWN);
   White white3(PAWN); 
   white3.lastMove = 1;
   board.board[4][3] = &white1;
   board.board[5][2] = &white2;
   board.board[6][3] = &white3;
   board.numMoves = 1;
   set <Move> moves;
   

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("f4g3E")) != moves.end());
   assertUnit(moves.find(Move("f4e3E")) != moves.end());
   

   // TEARDOWN
   board.board[5][3] = nullptr;
   board.board[4][3] = nullptr;
   board.board[5][2] = nullptr;
   board.board[6][3] = nullptr;
}

/*************************************
 * GET MOVES TEST Promotion
 * Promotion: b6a7rQ
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   P . P             8
 * 7    (p)              7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn whitePawn(7, 7, false /*fWhite*/);
   whitePawn.fWhite = true;
   whitePawn.position.set(1, 6);
   Black blackUpLeft(PAWN);
   Black blackUpRight(PAWN);
   board.board[1][6] = &whitePawn;
   board.board[0][7] = &blackUpLeft;
   board.board[2][7] = &blackUpRight;
   set<Move> moves;

   // EXERCISE
   whitePawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 3);
   assertUnit(moves.find(Move("b7b8Q")) != moves.end());
   assertUnit(moves.find(Move("b7a8pQ")) != moves.end());
   assertUnit(moves.find(Move("b7c8pQ")) != moves.end());

   // TEARDOWN
   board.board[1][6] = nullptr; // whitePawn
   board.board[0][7] = nullptr; // blackUpLeft
   board.board[2][7] = nullptr; // blackUpRight
}


/*************************************
 * GET MOVES TEST Promotion
 * Promotion: e2d1rQ
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2          (P)        2
 * 1         r . r       1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn blackPawn(7, 7, true /*fWhite*/);
   blackPawn.fWhite = false;
   blackPawn.position.set(4, 1);
   White whiteLowLeft(ROOK);
   White whiteLowRight(ROOK);
   board.board[4][1] = &blackPawn;
   board.board[3][0] = &whiteLowLeft;
   board.board[5][0] = &whiteLowRight;
   set<Move> moves;

   // EXERCISE
   blackPawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 3);
   assertUnit(moves.find(Move("e2e1Q")) != moves.end());
   assertUnit(moves.find(Move("e2d1rQ")) != moves.end());
   assertUnit(moves.find(Move("e2f1rQ")) != moves.end());

   // TEARDOWN
   board.board[4][1] = nullptr;
   board.board[3][0] = nullptr;
   board.board[5][0] = nullptr;
}


/*************************************
 * GET TYPE : pawn
 * Input:
 * Output: PAWN
 **************************************/
void TestPawn::getType()
{
   // SETUP
   Pawn pawn(7, 7, false /*fWhite*/);
   pawn.position.set(1, 4);
   pawn.fWhite = false;

   // EXERCISE
   PieceType pt = pawn.getType();

   // VERIFY
   assertUnit(pt == PieceType::PAWN);
   assertUnit(pawn.fWhite == false);
   assertUnit(pawn.position.getCol() == 1);
   assertUnit(pawn.position.getRow() == 4);
   
}  // TEARDOWN

