#include <iostream>
#include <sstream>
#include "Board.hpp"
#include <constants.hpp>
#include <thread> 
#include "LiChessUCI.hpp"

void LiChessUCI::updatePosition(std::istringstream& is)
{
	std::string token, fen;

	is >> token;
	if (token == "startpos")
	{
		board = std::make_unique<Board>("");
		board->set_bitboards(STARTING_POSITIONS);
		//is >> token; // Consume "moves" token if any
	}
	else if (token == "fen")
	{
		while (is >> token && token != "moves")
		fen += token + " ";
		board = std::make_unique<Board>(fen);
	}
	else
	{
		return;
	}

	// Parse move list (if any)
	while (is >> token)
	{
		if (token != "moves")
		{	
			char one = token[0];
			char two = token[1];
			char three = token[2];
			char four = token[3];
			std::vector<Board> moves;
			// potential error here if board goes out of scope
			if (board->get_turn()) {
				moves = board->generate_bmoves();
			} else {
				moves = board->generate_wmoves();
			}
			std::cout << one << two << three << four << std::endl;
			for (auto &b : moves) {
				// std::cout << one << two << three << four << " " << FILENTC.at(b.pm_op_f()) << RANKNTC.at(b.pm_op_r()) << FILENTC.at(b.pm_np_f()) << RANKNTC.at(b.pm_np_r()) << " " << board->get_turn() << std::endl;
				// std::cout << (FILENTC.at(b.pm_op_f()) == one) << (RANKNTC.at(b.pm_op_r()) == two) << (FILENTC.at(b.pm_np_f()) == three) << (RANKNTC.at(b.pm_np_r()) == four) << std::endl;
				if (FILENTC.at(b.pm_op_f()) == one && RANKNTC.at(b.pm_op_r()) == two && FILENTC.at(b.pm_np_f()) == three && RANKNTC.at(b.pm_np_r()) == four) {
					board = std::make_unique<Board>(std::move(b));
					std::cout << "-found-"<< std::endl << std::endl;
					std::cout << board->can_brcastle() << std::endl;
					std::cout << board->can_blcastle() << std::endl;
					std::cout << board->can_wlcastle() << std::endl;
					std::cout << board->can_wrcastle() << std::endl;
					board->print_board();
					break;
				}
			}
		}
	}
	
	// Reassign search to new boardPtr
	// initSearch();
}

void LiChessUCI::search() {
	// board = std::make_unique<Board>(std::move(board->MCTS_next_move()));
	board = std::make_unique<Board>(std::move(board->negamax_next_move()));
	board->update_check();
	// board->print_board();
	std::cout << "bestmove " << FILENTC.at(board->pm_op_f()) << RANKNTC.at(board->pm_op_r()) << FILENTC.at(board->pm_np_f()) << RANKNTC.at(board->pm_np_r()) << std::endl;
}

void LiChessUCI::loop()
{
	std::string line;
	std::string token;
	LiChessUCI uciengine = LiChessUCI();
	// Make sure that the outputs are sent straight away to the GUI
	std::cout.setf (std::ios::unitbuf);

	// printOptions();

	while (std::getline(std::cin, line))
	{
		std::istringstream is(line);

		token.clear(); // getline() could return empty or blank line
		is >> std::skipws >> token;
		//	std::cout << token << std::endl;

		if (token == "uci")
		{
			std::cout << "id name COMP4121MCTSbot 1.0" << std::endl;
			std::cout << "id author Joshua Shim" << std::endl;
			// printOptions();
			std::cout << "uciok" << std::endl;
		}
		else if (token == "isready")
		{
			std::cout << "readyok" << std::endl;
		}
		// do setoptions later
		// else if (token == "setoption") 
        //     setoption(is);

		// else if (token == "color")

		// 	std::cout << "colorToPlay: " << myBoardPtr->getColorToPlay() << std::endl;

		else if (token == "ucinewgame")
		{
		    uciengine = LiChessUCI();
        }
        
		else if (token == "position")
			updatePosition(is);

		// else if (token == "print")
		// 	std::cout << *myBoardPtr << std::endl;

		// else if (token == "printOptions")
		// 	printOptions();

		else if (token == "go")
		{
			while (is >> token)
			{
				if (token == "wtime")          is >> wtime;
				else if (token == "btime")     is >> btime;
				else if (token == "winc")      is >> winc;
				else if (token == "binc")      is >> binc;
				else if (token == "movestogo") is >> movestogo;
			}

			// //http://stackoverflow.com/questions/12624271/c11-stdthread-giving-error-no-matching-function-to-call-stdthreadthread
			// thrd::thread thr(&Uci::search, this);
			// thrd::swap(thr, myThread);
			// myThread.join();
			search();
		}
		else if (token == "quit")
		{
			std::cout << "Terminating.." << std::endl;
			break;
		}
		else
			// Command not handled
			std::cout << "what?" << std::endl;
	}
}
