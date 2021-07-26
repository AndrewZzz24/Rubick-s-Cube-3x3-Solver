#include <iostream>
#include "cube.hpp"

void show_main_menu() {

    std::stringstream ss;
    ss << "Choose the command\n"
       << "1 - Save and read current state of cube from the file\n"
       << "2 - Check if the cube is valid\n"
       << "3 - Output the current state of the cube\n"
       << "4 - Turn the cube's edges\n"
       << "5 - Generate a random valid Cube state\n"
       << "6 - Find the solution for the current state\n"
       << "7 - Exit the program\n";
    std::cout << ss.str();

}

void show_menu_for_saving_or_reading() {

    std::stringstream ss;
    ss << "Choose the act:\n"
       << "1 - Save the current state in file\n"
       << "2 - Read the state from the file\n"
       << "3 - Get back to the main menu\n";
    std::cout << ss.str();

}

void show_menu_for_turning_edges() {

    std::stringstream ss;
    ss << "Chose the edge you want to turn:\n"
       << "- L\n"
       << "- U\n"
       << "- R\n"
       << "- D\n"
       << "- F\n"
       << "- B\n"
       << "- Get back to the main menu(Write 'b')\n";
    std::cout << ss.str();

}

void show_menu_where_to_turn() {
    std::stringstream ss;
    ss << "Choose where do you want to turn the edge to:\n"
       << "- Left\n"
       << "- Right\n";
    std::cout << ss.str();
}

void run() {

    int action = -1;
    cube_ cube;

    while (action != 7) {

        show_main_menu();
        std::cin >> action;

        switch (action) {
            case 1:

                show_menu_for_saving_or_reading();
                std::cin >> action;

                switch (action) {

                    case 1:

                        cube.save_the_state();
                        std::cout << "Saved!\n";
                        break;

                    case 2:

                        cube.read_the_state();
                        std::cout << "Done!\n";
                        break;

                    default:

                        break;

                }

                break;

            case 2:

                if (cube.check_state_validness())
                    std::cout << "Cube's state is VALID!\n";

                else
                    std::cout << "Cube's state is NOT VALID!\n";

                break;

            case 3:

                cube.console_output();
                break;

            case 4:

                while (true) {

                    show_menu_for_turning_edges();

                    std::string edge, where_turn;
                    std::cin >> edge;

                    if (edge == "b")
                        break;

                    show_menu_where_to_turn();
                    where_turn = "-1";

                    while (where_turn != "Right" && where_turn != "Left") {
                        std::cin >> where_turn;

                        if (where_turn != "Right" && where_turn != "Left") {
                            std::cout << "Invalid way, choose again\n";
                        }

                    }

                    if (where_turn == "Back")
                        continue;

                    cube.turn_edge(edge, where_turn);

                }
                break;

            case 5:

                cube.generate();
                break;

            case 6:

                cube.find_solution();
                std::cout << "Done!\nSolution: ";
                cube.get_answer();
                break;

            case 7:
                return;

            default:
                std::cout << "Invalid number of command\n";

        }
    }
}

int main() {
    run();
}


