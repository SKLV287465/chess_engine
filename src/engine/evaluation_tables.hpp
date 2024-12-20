#ifndef EVALUATION_TABLES_HPP
#define EVALUATION_TABLES_HPP

/*
    Deepov, a UCI chess playing engine.

    Copyright (c) 20014-2016 Romain Goussault, Navid Hedjazian

    Deepov is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deepov is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deepov.  If not, see <http://www.gnu.org/licenses/>.
*/

// this code is from deepov. I decided to take their evaluation tables in order to speed things up.

/*
    [0][][] is for white, [1][][] is for black
    [][1][6] is for midgame
    [][1][6] is for endgame

    Last dimension : same as for moves
    0 Pawn, 1 Knight, 2 Bishop, 3 Rook, 4 Queen, 5 King
    */

const int AllPSQT[2][2][6][64] = {

    { // Start White
    { // Start Opening

    //PawnSTOpening =
    {
      0,  0,  0,  0,  0,  0,  0,  0,
    -10,-10,-10,-40,-40,-10,-10,-10,
    -10,-15,-15,  0,  0,-15,-15,-10,
    -15,-10,  0,+20,+20,  0,-10,-15,
    -20,-20, +5,+40,+40, +5,-20,-20,
    -20,-20,+15,+30,+30,+15,-20,-20,
    -20,-20,+10,+10,+10,+10,-20,-20,
      0,  0,  0,  0,  0,  0,  0,  0
    },

    //KnightSTOpening =
    {
    -70,-20,-30,-25,-25,-30,-20,-70,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -30,  5, 10, 20, 20, 10,  5,-30,
    -30,  0, 15, 15, 15, 15,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -40,-20,-15,-10,-10,-15,-20,-40,
    -60,-40,-35,-30,-30,-35,-40,-60
    },

    //BishopSTOpening =
    {
    -20,-10,-40,-10,-10,-40,-10,-20,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
    },

    // RookSTOpening =
    {
    -15,-10, -5,  5,  5, -5,-10,-15,
    -15,-10,  0, 10, 10,  0,-10,-15,
    -15,-10,  0, 10, 10,  0,-10,-15,
    -15,-10,  0, 10, 10,  0,-10,-15,
    -15,-10,  0, 10, 10,  0,-10,-15,
    -15,-10,  0, 10, 10,  0,-10,-15,
    -15,-10,  0, 10, 10,  0,-10,-15,
    -15,-10, -5,  0,  0, -5,-10,-15
    },

    // QueenSTOpening =
    {
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0
    },

    // KingSTOpening =
    {
     20, 30, 10,  0,  0, 10, 30, 20,
     20, 20,  0,  0,  0,  0, 20, 20,
    -10,-20,-20,-20,-20,-20,-20,-10,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    }

    },

    { // Start Endgame

    // PawnSTEnding =
    {
     0,  0,  0,  0,  0,  0,  0,  0,
     5, -5, -5,  0,  0, -5, -5,  5,
     5, -5, -5,  0,  0, -5, -5,  5,
    10,  0,  0,  5,  5,  0,  0, 10,
    10,  8, 10, 12, 12, 10,  8, 10,
     5,  5, 10, 12, 12, 10,  5,  5,
    15, 15, 15, 17, 17, 15, 15, 15,
     0,  0,  0,  0,  0,  0,  0,  0
    },

    // KnightSTEnding =
    {
    -50,-30,-20,-20,-20,-20,-30,-50,
    -30,-20,  0,  5,  5,  0,-20,-30,
    -20,  0, 10, 15, 15, 10,  0,-20,
    -20,  5, 15, 20, 20, 15,  5,-20,
    -20,  5, 15, 20, 20, 15,  5,-20,
    -20,  0, 10, 15, 15, 10,  0,-20,
    -30,-20,  0,  5,  5,  0,-20,-30,
    -50,-30,-20,-20,-20,-20,-30,-50
    },

    // BishopSTEnding =
    {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
    },

    // RookSTEnding =
    {
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0
    },

    //QueenSTEnding =
    {
    -50,-30,-30,-30,-30,-30,-30,-50,
    -30,-30,  0,  0,  0,  0,-30,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-20,-10,  0,  0,-10,-20,-30,
    -50,-40,-30,-20,-20,-30,-40,-50
    },

    // KingSTEnding =
    {
    -50,-30,-30,-30,-30,-30,-30,-50,
    -30,-30,  0,  0,  0,  0,-30,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-20,-10,  0,  0,-10,-20,-30,
    -50,-40,-30,-20,-20,-30,-40,-50

    }

    }  // END ENDGAME
    }, // END WHITE

    {  // START BLACK
    { // Start Opening

    //PawnSTOpening =
    {
      0,  0,  0,  0,  0,  0,  0,  0,
    -20,-20,+10,+10,+10,+10,-20,-20,
    -20,-20,+15,+30,+30,+15,-20,-20,
    -20,-20, +5,+40,+40, +5,-20,-20,
    -15,-10,  0,+20,+20,  0,-10,-15,
    -10,-15,-15,  0,  0,-15,-15,-10,
    -10,-10,-10,-40,-40,-10,-10,-10,
      0,  0,  0,  0,  0,  0,  0,  0
    },

    //KnightSTOpening =
    {
    -60,-40,-35,-30,-30,-35,-40,-60,
    -40,-20,-15,-10,-10,-15,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 15, 15, 15,  0,-30,
    -30,  5, 10, 20, 20, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -70,-20,-30,-25,-25,-30,-20,-70
    },

    //BishopSTOpening =
    {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-40,-10,-10,-40,-10,-20
    },

    // RookSTOpening =
    {
    -15,-10, -5,  0,  0, -5,-10,-15,
    -15,-10,  0, 10, 10,  0,-10,-15,
    -15,-10,  0, 10, 10,  0,-10,-15,
    -15,-10,  0, 10, 10,  0,-10,-15,
    -15,-10,  0, 10, 10,  0,-10,-15,
    -15,-10,  0, 10, 10,  0,-10,-15,
    -15,-10,  0, 10, 10,  0,-10,-15,
    -15,-10, -5,  5,  5, -5,-10,-15
    },

    // QueenSTOpening =
    {
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0
    },

    // KingSTOpening =
    {
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -10,-20,-20,-20,-20,-20,-20,-10,
     20, 20,  0,  0,  0,  0, 20, 20,
     20, 30, 10,  0,  0, 10, 30, 20
    }

    },

    { // Start Endgame

    // PawnSTEnding =
    {
     0,  0,  0,  0,  0,  0,  0,  0,
    15, 15, 15, 17, 17, 15, 15, 15,
     5,  5, 10, 12, 12, 10,  5,  5,
    10,  8, 10, 12, 12, 10,  8, 10,
    10,  0,  0,  5,  5,  0,  0, 10,
     5, -5, -5,  0,  0, -5, -5,  5,
     5, -5, -5,  0,  0, -5, -5,  5,
     0,  0,  0,  0,  0,  0,  0,  0
    },

    // KnightSTEnding =
    {
    -50,-30,-20,-20,-20,-20,-30,-50,
    -30,-20,  0,  5,  5,  0,-20,-30,
    -20,  0, 10, 15, 15, 10,  0,-20,
    -20,  5, 15, 20, 20, 15,  5,-20,
    -20,  5, 15, 20, 20, 15,  5,-20,
    -20,  0, 10, 15, 15, 10,  0,-20,
    -30,-20,  0,  5,  5,  0,-20,-30,
    -50,-30,-20,-20,-20,-20,-30,-50
    },

    // BishopSTEnding =
    {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
    },

    // RookSTEnding =
    {
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0
    },

    //QueenSTEnding =
    {
    -50,-40,-30,-20,-20,-30,-40,-50,
    -30,-20,-10,  0,  0,-10,-20,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-30,  0,  0,  0,  0,-30,-30,
    -50,-30,-30,-30,-30,-30,-30,-50
    },

    // KingSTEnding =
    {
    -50,-40,-30,-20,-20,-30,-40,-50,
    -30,-20,-10,  0,  0,-10,-20,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-30,  0,  0,  0,  0,-30,-30,
    -50,-30,-30,-30,-30,-30,-30,-50
    }

    }  // END ENDGAME
    } // BLACK VALUES

    };

#endif