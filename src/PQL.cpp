//============================================================================
// Name        : PQL.cpp
// Author      : Michael Blot
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "tests/test_deck.cpp"
#include "tests/test_table.cpp"



using namespace std;

int main() {
/******* TEST HAND MANAGER */
	test_deck test_d = test_deck();
//	test_d.test_card();
//	test_d.test_deck_distribute();
//	test_d.test_hand_config_and_eval();
//	test_d.test_all_combos();
//	test_d.test_all_hands();
//	test_d.test_MC_hand_value();
//	test_d.test_two_cards_monte_carlo();
//	test_d.test_hash_function();

/******* TEST TABLE & GAME */
	test_table test = test_table();

//	test.test_plot();

//	test.test_save_and_load_player();

//	test.test_gui_player();
//	test.test_random_player();
//	test.test_train_table();
	test.test_torch();
//	test.test_graphic_table();
//	test.test_session();


	//	test.test_complete_average_value();


	return 0;
}
