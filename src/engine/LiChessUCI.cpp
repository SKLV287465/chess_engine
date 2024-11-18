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
	// other piece promotions to do.
	int num = 0;
	while (is >> token)
	{
		if (token != "moves")
		{	
			++num;
			char one = token[0];
			char two = token[1];
			char three = token[2];
			char four = token[3];
			char five;
			if (token.size() > 4) {
				five = token[4];
			}
			std::deque<Board> moves;
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
					board->print_board();
					break;
				}
			}
		}
	}
	moves_made = num;
	board->update_check();
	
	// Reassign search to new boardPtr
	// initSearch();
}

void LiChessUCI::search() {
	// board = std::make_unique<Board>(std::move(board->MCTS_next_move()));
	auto prev_board = std::move(board);
	// board = std::make_unique<Board>(prev_board->MCTS_next_move());
	if (moves_made < 4) {
		switch (moves_made) {
			case 0:
				{
				auto one = 'd';
				auto two = '2';
				auto three = 'd';
				auto four = '4';
				std::cout << "bestmove " << one << two << three << four << std::endl;
				auto moves = board->generate_bmoves();
				for (auto &b : moves) {
					if (FILENTC.at(b.pm_op_f()) == one && RANKNTC.at(b.pm_op_r()) == two && FILENTC.at(b.pm_np_f()) == three && RANKNTC.at(b.pm_np_r()) == four) {
						board = std::make_unique<Board>(std::move(b));
						break;
					}
				}
				break;
				}
			case 1:
				{
				auto one = 'e';
				auto two = '7';
				auto three = 'e';
				auto four = '6';
				std::cout << "bestmove " << one << two << three << four << std::endl;
				auto moves = board->generate_wmoves();
				for (auto &b : moves) {
					if (FILENTC.at(b.pm_op_f()) == one && RANKNTC.at(b.pm_op_r()) == two && FILENTC.at(b.pm_np_f()) == three && RANKNTC.at(b.pm_np_r()) == four) {
						board = std::make_unique<Board>(std::move(b));
						break;
					}
				}
				break;
				}
			case 2:
				{
				auto one = 'g';
				auto two = '1';
				auto three = 'f';
				auto four = '3';
				std::cout << "bestmove " << one << two << three << four << std::endl;
				auto moves = board->generate_bmoves();
				for (auto &b : moves) {
					if (FILENTC.at(b.pm_op_f()) == one && RANKNTC.at(b.pm_op_r()) == two && FILENTC.at(b.pm_np_f()) == three && RANKNTC.at(b.pm_np_r()) == four) {
						board = std::make_unique<Board>(std::move(b));
						break;
					}
				}
				break;
				}
			case 3:
				{
				auto one = 'd';
				auto two = '7';
				auto three = 'd';
				auto four = '5';
				std::cout << "bestmove " << one << two << three << four << std::endl;
				auto moves = board->generate_wmoves();
				for (auto &b : moves) {
					if (FILENTC.at(b.pm_op_f()) == one && RANKNTC.at(b.pm_op_r()) == two && FILENTC.at(b.pm_np_f()) == three && RANKNTC.at(b.pm_np_r()) == four) {
						board = std::make_unique<Board>(std::move(b));
						break;
					}
				}
				break;
				}
		}

	} else {
		board = std::make_unique<Board>(prev_board->negamax_next_move(wpieces, bpieces));
		auto promotion = std::string{};
		if (board->pm_np_r() == RANK_1 || board->pm_np_r() == RANK_8) {
			if (prev_board->piece_at_square(board->pm_op_r(), board->pm_op_f()) == 0 || prev_board->piece_at_square(board->pm_op_r(), board->pm_op_f()) == 6) {
				promotion.push_back('q');
			}
		}
		
		std::cout << "bestmove " << FILENTC.at(board->pm_op_f()) << RANKNTC.at(board->pm_op_r()) << FILENTC.at(board->pm_np_f()) << RANKNTC.at(board->pm_np_r())  << promotion << std::endl;
	}
	// count how many pieces are left
	wpieces = 0;
	bpieces = 0;
	for (int i = 0; i < 6; ++i) {
		wpieces += __builtin_popcountll(board->bitboards[i]);
	}
	for (int i = 6; i < 12; ++i) {
		bpieces += __builtin_popcountll(board->bitboards[i]);
	}
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
