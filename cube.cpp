#include "cube.hpp"
#include <fstream>
#include <set>
#include <ctime>

cube_::cube_() {

    for (int i = 0; i < 6; i++) {

        switch (i) {

            case 0:
                cb.emplace_back(3, std::vector<char>(3, 'G'));
                break;

            case 1:
                cb.emplace_back(3, std::vector<char>(3, 'W'));
                break;

            case 2:
                cb.emplace_back(3, std::vector<char>(3, 'B'));
                break;

            case 3:
                cb.emplace_back(3, std::vector<char>(3, 'Y'));
                break;

            case 4:
                cb.emplace_back(3, std::vector<char>(3, 'R'));
                break;

            default:
                cb.emplace_back(3, std::vector<char>(3, 'O'));
                break;

        }

    }

}

bool cube_::save_the_state() {

    std::cout << "Enter the file name\n";
    std::cin >> file_name;
    std::ofstream file(file_name);

    if (!file)
        return false;

    for (size_t i = 0; i < cb.size(); i++) {

        if (i == 0)
            file << "Left\n";
        if (i == 1)
            file << "Top\n";
        if (i == 2)
            file << "Right\n";
        if (i == 3)
            file << "Bottom\n";
        if (i == 4)
            file << "Front\n";
        if (i == 5)
            file << "Back\n";

        for (size_t j = 0; j < 3; j++) {

            for (size_t k = 0; k < 3; k++)
                file << cb[i][j][k] << ' ';

            file << std::endl;
        }
    }

    return true;

}

bool cube_::read_the_state() {

    std::cout << "Enter the file name\n";
    std::cin >> file_name;
    std::ifstream file(file_name);

    if (!file)
        throw std::runtime_error("bad open");


    cb.resize(6, std::vector < std::vector < char >> (3));

    std::string tmp;
    int i;

    while (!file.eof()) {

        file >> tmp;

        if (tmp == "Left")
            i = 0;
        if (tmp == "Top")
            i = 1;
        if (tmp == "Right")
            i = 2;
        if (tmp == "Bottom")
            i = 3;
        if (tmp == "Front")
            i = 4;
        if (tmp == "Back")
            i = 5;

        for (size_t j = 0; j < 3; j++) {

            for (size_t k = 0; k < 3; k++)
                file >> cb[i][j][k];

        }
    }

    return true;

}

bool cube_::check_state_validness() const {

    bool state;

    state = check_num_of_colours();

    if (state)
        state = check_angles();

    if (state)
        state = check_centre();

    if (state)
        state = check_edges();

    return state;

}

bool check_rightness_ed(std::string &s) {

    if (s.find('W') != std::string::npos && s.find('B') != std::string::npos)
        return true;

    if (s.find('W') != std::string::npos && s.find('R') != std::string::npos)
        return true;

    if (s.find('W') != std::string::npos && s.find('G') != std::string::npos)
        return true;

    if (s.find('W') != std::string::npos && s.find('O') != std::string::npos)
        return true;

    if (s.find('Y') != std::string::npos && s.find('B') != std::string::npos)
        return true;

    if (s.find('Y') != std::string::npos && s.find('R') != std::string::npos)
        return true;

    if (s.find('Y') != std::string::npos && s.find('G') != std::string::npos)
        return true;

    if (s.find('Y') != std::string::npos && s.find('O') != std::string::npos)
        return true;

    if (s.find('G') != std::string::npos && s.find('R') != std::string::npos)
        return true;

    if (s.find('G') != std::string::npos && s.find('O') != std::string::npos)
        return true;

    if (s.find('B') != std::string::npos && s.find('R') != std::string::npos)
        return true;

    if (s.find('B') != std::string::npos && s.find('O') != std::string::npos)
        return true;

    return false;
}

bool cube_::check_edges() const {

    std::set <std::string> edgs;
    std::string ed;
    ed = ed + cb[0][0][1] + cb[1][1][0];
    if (!check_rightness_ed(ed) || edgs.count(ed) != 0)
        return false;
    edgs.insert(ed);
    ed.clear();

    ed = ed + cb[0][2][1] + cb[3][1][0];
    if (!check_rightness_ed(ed) || edgs.count(ed) != 0)
        return false;
    edgs.insert(ed);
    ed.clear();

    ed = ed + cb[0][1][2] + cb[4][1][0];
    if (!check_rightness_ed(ed) || edgs.count(ed) != 0)
        return false;
    edgs.insert(ed);
    ed.clear();

    ed = ed + cb[0][1][0] + cb[5][1][2];
    if (!check_rightness_ed(ed) || edgs.count(ed) != 0)
        return false;
    edgs.insert(ed);
    ed.clear();

    ed = ed + cb[2][0][1] + cb[1][1][2];

    if (!check_rightness_ed(ed) || edgs.count(ed) != 0)
        return false;
    edgs.insert(ed);
    ed.clear();

    ed = ed + cb[2][1][0] + cb[4][1][2];
    if (!check_rightness_ed(ed) || edgs.count(ed) != 0)
        return false;
    edgs.insert(ed);
    ed.clear();

    ed = ed + cb[2][2][1] + cb[3][1][2];
    if (!check_rightness_ed(ed) || edgs.count(ed) != 0)
        return false;
    edgs.insert(ed);
    ed.clear();

    ed = ed + cb[2][1][2] + cb[5][1][0];
    if (!check_rightness_ed(ed) || edgs.count(ed) != 0)
        return false;
    edgs.insert(ed);
    ed.clear();

    ed = ed + cb[1][2][1] + cb[4][0][1];
    if (!check_rightness_ed(ed) || edgs.count(ed) != 0)
        return false;
    edgs.insert(ed);
    ed.clear();

    ed = ed + cb[1][0][1] + cb[5][0][1];
    if (!check_rightness_ed(ed) || edgs.count(ed) != 0)
        return false;
    edgs.insert(ed);
    ed.clear();

    ed = ed + cb[3][0][1] + cb[5][2][1];
    if (!check_rightness_ed(ed) || edgs.count(ed) != 0)
        return false;
    edgs.insert(ed);
    ed.clear();

    ed = ed + cb[3][2][1] + cb[4][2][1];
    if (!check_rightness_ed(ed) || edgs.count(ed) != 0)
        return false;
    edgs.insert(ed);
    ed.clear();

    return true;
}

bool check_rightness_angle(std::string &s) {

    if (s.find('W') != std::string::npos && s.find('B') != std::string::npos && s.find('R') != std::string::npos)
        return true;

    if (s.find('W') != std::string::npos && s.find('B') != std::string::npos && s.find('O') != std::string::npos)
        return true;

    if (s.find('W') != std::string::npos && s.find('G') != std::string::npos && s.find('R') != std::string::npos)
        return true;

    if (s.find('W') != std::string::npos && s.find('G') != std::string::npos && s.find('O') != std::string::npos)
        return true;

    if (s.find('Y') != std::string::npos && s.find('B') != std::string::npos && s.find('R') != std::string::npos)
        return true;

    if (s.find('Y') != std::string::npos && s.find('B') != std::string::npos && s.find('O') != std::string::npos)
        return true;

    if (s.find('Y') != std::string::npos && s.find('G') != std::string::npos && s.find('R') != std::string::npos)
        return true;

    if (s.find('Y') != std::string::npos && s.find('G') != std::string::npos && s.find('O') != std::string::npos)
        return true;

    return false;

}

bool cube_::check_angles() const {

    std::set <std::string> angles;
    std::string s1;

    s1 = s1 + cb[0][0][0] + cb[5][0][2] + cb[1][0][0];
    if (!check_rightness_angle(s1) || angles.count(s1) != 0)
        return false;
    angles.insert(s1);
    s1.clear();

    s1 = s1 + cb[0][0][2] + cb[4][0][0] + cb[1][2][0];
    if (!check_rightness_angle(s1) || angles.count(s1) != 0)
        return false;
    angles.insert(s1);
    s1.clear();

    s1 = s1 + cb[0][2][2] + cb[4][2][0] + cb[3][2][0];
    if (!check_rightness_angle(s1) || angles.count(s1) != 0)
        return false;
    angles.insert(s1);
    s1.clear();

    s1 = s1 + cb[0][2][0] + cb[5][2][2] + cb[3][0][0];
    if (!check_rightness_angle(s1) || angles.count(s1) != 0)
        return false;
    angles.insert(s1);
    s1.clear();

    s1 = s1 + cb[2][0][0] + cb[4][0][2] + cb[1][2][2];
    if (!check_rightness_angle(s1) || angles.count(s1) != 0)
        return false;
    angles.insert(s1);
    s1.clear();

    s1 = s1 + cb[2][0][2] + cb[5][0][0] + cb[1][0][2];
    if (!check_rightness_angle(s1) || angles.count(s1) != 0)
        return false;
    angles.insert(s1);
    s1.clear();

    s1 = s1 + cb[2][2][0] + cb[4][2][2] + cb[3][2][2];
    if (!check_rightness_angle(s1) || angles.count(s1) != 0)
        return false;
    angles.insert(s1);
    s1.clear();

    s1 = s1 + cb[2][2][2] + cb[3][0][2] + cb[5][2][0];
    if (!check_rightness_angle(s1) || angles.count(s1) != 0)
        return false;
    angles.insert(s1);
    s1.clear();

    return true;

}

bool cube_::check_centre() const {

    std::string ss;

    for (const auto &i : cb)
        ss += i[1][1];

    for (size_t j = 0; j < ss.size(); j++)

        for (size_t i = 0; i < cb.size(); i++)

            if (ss[j] == cb[i][1][1] && j != i)
                return false;

    return true;

}

bool cube_::check_num_of_colours() const {

    std::vector<int> count(6, 0);

    for (auto &i: cb) {

        for (auto &j : i) {

            for (auto &k :j) {

                int num_of_edge = -1;

                switch (k) {
                    case 'G':
                        num_of_edge = 0;
                        break;
                    case 'W':
                        num_of_edge = 1;
                        break;
                    case 'B':
                        num_of_edge = 2;
                        break;
                    case 'Y':
                        num_of_edge = 3;
                        break;
                    case 'R':
                        num_of_edge = 4;
                        break;
                    case 'O':
                        num_of_edge = 5;
                        break;
                    default:
                        break;
                }

                count[num_of_edge]++;

                if (num_of_edge == -1 || count[num_of_edge] > 9)
                    return false;

            }

        }

    }

    return true;

}

void cube_::console_output() const {

    std::cout << "         Top\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "        ";
        for (int j = 0; j < 3; ++j) {
            std::cout << cb[1][j][2 - i] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << " Back   Left    Front   Right  \n";
    for (int q = 0; q < 3; ++q) {

        for (int i = 0; i < 3; ++i) {
            std::cout << cb[5][q][i] << ' ';
        }
        std::cout << "  ";
        for (int i = 0; i < 3; ++i) {
            std::cout << cb[0][q][i] << ' ';
        }
        std::cout << "  ";
        for (int i = 0; i < 3; ++i) {
            std::cout << cb[4][q][i] << ' ';
        }
        std::cout << "  ";
        for (int i = 0; i < 3; ++i) {
            std::cout << cb[2][q][i] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "        Bottom\n";

    for (int i = 0; i < 3; ++i) {
        std::cout << "        ";
        for (int j = 0; j < 3; ++j) {
            std::cout << cb[3][j][i] << ' ';
        }
        std::cout << std::endl;
    }

//    std::cout << " Left     Top     Right    Bottom   Front    Back\n";
//
//    for (int q = 0; q < 3; q++) {
//
//        for (int i = 0; i < 6; i++) {
//
//            for (int j = 0; j < 3; j++)
//                std::cout << cb[i][q][j] << ' ';
//
//            std::cout << "   ";
//
//        }
//
//        std::cout << std::endl;
//
//    }

}

void cube_::turn_edge(std::string &what_edge, std::string &where_to) {

    if (what_edge == "L") {
        if (where_to == "Left")
            Left_side_left(0, 1);
        else if (where_to == "Right")
            Left_side_right(0, 1);
    }

    if (what_edge == "R") {
        if (where_to == "Left")
            Right_side_left(1);
        else if (where_to == "Right")
            Right_side_right(1);
    }

    if (what_edge == "U") {
        if (where_to == "Left")
            Top_side_left(0, 1);
        else if (where_to == "Right")
            Top_side_right(0, 1);
    }

    if (what_edge == "D") {
        if (where_to == "Left")
            Bottom_side_left(1);
        else if (where_to == "Right")
            Bottom_side_right(1);
    }

    if (what_edge == "F") {
        if (where_to == "Left")
            Front_side_left(0, 1);
        else if (where_to == "Right")
            Front_side_right(0, 1);
    }

    if (what_edge == "B") {
        if (where_to == "Left")
            Back_side_left(1);
        else if (where_to == "Right")
            Back_side_right(1);
    }

}

void cube_::turn_side_left(int what_edge) {

    std::vector<char> tmp = {cb[what_edge][0][0], cb[what_edge][1][0], cb[what_edge][2][0]};

    cb[what_edge][0][0] = cb[what_edge][0][2];
    cb[what_edge][1][0] = cb[what_edge][0][1];
    cb[what_edge][2][0] = tmp[0];
    cb[what_edge][0][1] = cb[what_edge][1][2];
    cb[what_edge][0][2] = cb[what_edge][2][2];
    cb[what_edge][1][2] = cb[what_edge][2][1];
    cb[what_edge][2][2] = tmp[2];
    cb[what_edge][2][1] = tmp[1];

}

void cube_::turn_side_right(int what_edge) {

    std::vector<char> tmp = {cb[what_edge][0][0], cb[what_edge][1][0], cb[what_edge][2][0]};

    cb[what_edge][0][0] = cb[what_edge][2][0];
    cb[what_edge][1][0] = cb[what_edge][2][1];
    cb[what_edge][2][0] = cb[what_edge][2][2];
    cb[what_edge][2][1] = cb[what_edge][1][2];
    cb[what_edge][2][2] = cb[what_edge][0][2];
    cb[what_edge][1][2] = cb[what_edge][0][1];
    cb[what_edge][0][2] = tmp[0];
    cb[what_edge][0][1] = tmp[1];

}

void cube_::Left_side_left(int _num_of_edge, int what_to_do) {

    if (!what_to_do) {
        answer += "L' ";
    }
    if (_num_of_edge == 0)
        turn_side_left(0);
    if (_num_of_edge == 2)
        turn_side_right(2);

    std::vector<char> tmp = {cb[1][0][_num_of_edge], cb[1][1][_num_of_edge], cb[1][2][_num_of_edge]};

    cb[1][0][_num_of_edge] = cb[4][0][_num_of_edge];
    cb[1][1][_num_of_edge] = cb[4][1][_num_of_edge];
    cb[1][2][_num_of_edge] = cb[4][2][_num_of_edge];

    cb[4][0][_num_of_edge] = cb[3][2][_num_of_edge];
    cb[4][1][_num_of_edge] = cb[3][1][_num_of_edge];
    cb[4][2][_num_of_edge] = cb[3][0][_num_of_edge];

    cb[3][0][_num_of_edge] = cb[5][0][2 - _num_of_edge];
    cb[3][1][_num_of_edge] = cb[5][1][2 - _num_of_edge];
    cb[3][2][_num_of_edge] = cb[5][2][2 - _num_of_edge];

    cb[5][0][2 - _num_of_edge] = tmp[2];
    cb[5][1][2 - _num_of_edge] = tmp[1];
    cb[5][2][2 - _num_of_edge] = tmp[0];

}

void cube_::Left_side_right(int _num_of_edge, int what_to_do) {

    if (!what_to_do) {
        answer += "L ";
    }
    if (_num_of_edge == 0)
        turn_side_right(0);
    if (_num_of_edge == 2)
        turn_side_left(2);

    std::vector<char> tmp = {cb[1][0][_num_of_edge], cb[1][1][_num_of_edge], cb[1][2][_num_of_edge]};

    cb[1][0][_num_of_edge] = cb[5][2][2 - _num_of_edge];
    cb[1][1][_num_of_edge] = cb[5][1][2 - _num_of_edge];
    cb[1][2][_num_of_edge] = cb[5][0][2 - _num_of_edge];

    cb[5][0][2 - _num_of_edge] = cb[3][0][_num_of_edge];
    cb[5][1][2 - _num_of_edge] = cb[3][1][_num_of_edge];
    cb[5][2][2 - _num_of_edge] = cb[3][2][_num_of_edge];

    cb[3][0][_num_of_edge] = cb[4][2][_num_of_edge];
    cb[3][1][_num_of_edge] = cb[4][1][_num_of_edge];
    cb[3][2][_num_of_edge] = cb[4][0][_num_of_edge];

    cb[4][0][_num_of_edge] = tmp[0];
    cb[4][1][_num_of_edge] = tmp[1];
    cb[4][2][_num_of_edge] = tmp[2];

}

void cube_::Right_side_left(int what_to_do) {

    if (!what_to_do) {
        answer += "R' ";
    }

    Left_side_right(2);

}

void cube_::Right_side_right(int what_to_do) {

    if (!what_to_do)
        answer += "R ";

    Left_side_left(2);

}

void cube_::Top_side_left(int _num_of_layer, int what_to_do) {

    if (!what_to_do)
        answer += "U' ";

    if (_num_of_layer == 2)
        turn_side_left(3);

    if (_num_of_layer == 0)
        turn_side_left(1);


    std::vector<char> tmp = {cb[4][_num_of_layer][0], cb[4][_num_of_layer][1], cb[4][_num_of_layer][2]};

    cb[4][_num_of_layer][0] = cb[0][_num_of_layer][0];
    cb[4][_num_of_layer][1] = cb[0][_num_of_layer][1];
    cb[4][_num_of_layer][2] = cb[0][_num_of_layer][2];

    cb[0][_num_of_layer][0] = cb[5][_num_of_layer][0];
    cb[0][_num_of_layer][1] = cb[5][_num_of_layer][1];
    cb[0][_num_of_layer][2] = cb[5][_num_of_layer][2];

    cb[5][_num_of_layer][0] = cb[2][_num_of_layer][0];
    cb[5][_num_of_layer][1] = cb[2][_num_of_layer][1];
    cb[5][_num_of_layer][2] = cb[2][_num_of_layer][2];

    cb[2][_num_of_layer][0] = tmp[0];
    cb[2][_num_of_layer][1] = tmp[1];
    cb[2][_num_of_layer][2] = tmp[2];

}

void cube_::Top_side_right(int _num_of_layer, int what_to_do) {

    if (!what_to_do)
        answer += "U ";

    if (_num_of_layer == 2)
        turn_side_right(3);
    if (_num_of_layer == 0)
        turn_side_right(1);

    std::vector<char> tmp = {cb[4][_num_of_layer][0], cb[4][_num_of_layer][1], cb[4][_num_of_layer][2]};

    cb[4][_num_of_layer][0] = cb[2][_num_of_layer][0];
    cb[4][_num_of_layer][1] = cb[2][_num_of_layer][1];
    cb[4][_num_of_layer][2] = cb[2][_num_of_layer][2];

    cb[2][_num_of_layer][0] = cb[5][_num_of_layer][0];
    cb[2][_num_of_layer][1] = cb[5][_num_of_layer][1];
    cb[2][_num_of_layer][2] = cb[5][_num_of_layer][2];

    cb[5][_num_of_layer][0] = cb[0][_num_of_layer][0];
    cb[5][_num_of_layer][1] = cb[0][_num_of_layer][1];
    cb[5][_num_of_layer][2] = cb[0][_num_of_layer][2];

    cb[0][_num_of_layer][0] = tmp[0];
    cb[0][_num_of_layer][1] = tmp[1];
    cb[0][_num_of_layer][2] = tmp[2];

}

void cube_::Bottom_side_right(int what_to_do) {

    if (!what_to_do)
        answer += "D' ";

    Top_side_right(2);

}

void cube_::Bottom_side_left(int what_to_do) {

    if (!what_to_do)
        answer += "D ";


    Top_side_left(2);
}

void cube_::Front_side_left(int _num_of_layer, int what_to_do) {

    if (!what_to_do)
        answer += "F' ";

    if (_num_of_layer == 0)
        turn_side_left(4);
    if (_num_of_layer == 2)
        turn_side_right(5);

    std::vector<char> tmp = {cb[1][2 - _num_of_layer][0], cb[1][2 - _num_of_layer][1], cb[1][2 - _num_of_layer][2]};

    cb[1][2 - _num_of_layer][0] = cb[2][0][_num_of_layer];
    cb[1][2 - _num_of_layer][1] = cb[2][1][_num_of_layer];
    cb[1][2 - _num_of_layer][2] = cb[2][2][_num_of_layer];

    cb[2][0][_num_of_layer] = cb[3][2 - _num_of_layer][2];
    cb[2][1][_num_of_layer] = cb[3][2 - _num_of_layer][1];
    cb[2][2][_num_of_layer] = cb[3][2 - _num_of_layer][0];

    cb[3][2 - _num_of_layer][2] = cb[0][2][2 - _num_of_layer];
    cb[3][2 - _num_of_layer][1] = cb[0][1][2 - _num_of_layer];
    cb[3][2 - _num_of_layer][0] = cb[0][0][2 - _num_of_layer];

    cb[0][2][2 - _num_of_layer] = tmp[0];
    cb[0][1][2 - _num_of_layer] = tmp[1];
    cb[0][0][2 - _num_of_layer] = tmp[2];

}

void cube_::Front_side_right(int _num_of_layer, int what_to_do) {

    if (!what_to_do)
        answer += "F ";

    if (_num_of_layer == 0)
        turn_side_right(4);
    if (_num_of_layer == 2)
        turn_side_left(5);

    std::vector<char> tmp = {cb[1][2 - _num_of_layer][0], cb[1][2 - _num_of_layer][1], cb[1][2 - _num_of_layer][2]};

    cb[1][2 - _num_of_layer][0] = cb[0][2][2 - _num_of_layer];
    cb[1][2 - _num_of_layer][1] = cb[0][1][2 - _num_of_layer];
    cb[1][2 - _num_of_layer][2] = cb[0][0][2 - _num_of_layer];

    cb[0][2][2 - _num_of_layer] = cb[3][2 - _num_of_layer][2];
    cb[0][1][2 - _num_of_layer] = cb[3][2 - _num_of_layer][1];
    cb[0][0][2 - _num_of_layer] = cb[3][2 - _num_of_layer][0];

    cb[3][2 - _num_of_layer][2] = cb[2][0][_num_of_layer];
    cb[3][2 - _num_of_layer][1] = cb[2][1][_num_of_layer];
    cb[3][2 - _num_of_layer][0] = cb[2][2][_num_of_layer];

    cb[2][2][_num_of_layer] = tmp[2];
    cb[2][1][_num_of_layer] = tmp[1];
    cb[2][0][_num_of_layer] = tmp[0];
}

void cube_::Back_side_left(int what_to_do) {

    if (!what_to_do)
        answer += "B ";

    Front_side_left(2);

}

void cube_::Back_side_right(int what_to_do) {

    if (!what_to_do)
        answer += "B' ";

    Front_side_right(2);

}

void cube_::generate() {


    cube_ tmp;

    for (int ed = 0; ed < 6; ed++) {

        for (int s = 0; s < 3; s++) {

            for (int c = 0; c < 3; c++)
                cb[ed][s][c] = tmp.cb[ed][s][c];

        }

    }

    std::srand(time(nullptr));

    answer.clear();

    int time_turns = rand() % 1000, where_to_turn;
    std::cout << std::endl;

    for (int i = 0; i < time_turns; i++) {

        int what_edge_to_turn = rand() % 6;

        switch (what_edge_to_turn) {

            case 0:
                where_to_turn = rand() % 2;
                if (where_to_turn) {
                    std::cout << "L' ";
                    Left_side_left(0, 1);
                } else {
                    std::cout << "L ";
                    Left_side_right(0, 1);
                }
                break;

            case 1:
                where_to_turn = rand() % 2;
                if (where_to_turn) {
                    std::cout << "T' ";
                    Top_side_left(0, 1);
                } else {
                    std::cout << "T ";
                    Top_side_right(0, 1);
                }
                break;

            case 2:
                where_to_turn = rand() % 2;
                if (where_to_turn) {
                    std::cout << "R' ";
                    Right_side_left(1);
                } else {
                    std::cout << "R ";
                    Right_side_right(1);
                }
                break;

            case 3:
                where_to_turn = rand() % 2;
                if (where_to_turn) {
                    std::cout << "D' ";
                    Bottom_side_right(1);
                } else {
                    std::cout << "D ";
                    Bottom_side_left(1);
                }
                break;

            case 4:
                where_to_turn = rand() % 2;
                if (where_to_turn) {
                    std::cout << "F' ";
                    Front_side_left(0, 1);
                } else {
                    std::cout << "F ";
                    Front_side_right(0, 1);
                }
                break;

            default:
                where_to_turn = rand() % 2;
                if (where_to_turn) {
                    std::cout << "B' ";
                    Back_side_right(1);
                } else {
                    std::cout << "B ";
                    Back_side_left(1);
                }
                break;

        }

    }
    std::cout << std::endl;
}

void cube_::find_solution() {

    answer.clear();

    if (check_if_okay())
        return;

    make_white_cross();
    //console_output();
    make_white_corners();
    //console_output();
    make_second_layer();
    //console_output();
    make_yellow_cross();
    //console_output();
    make_yellow_corners();
    //console_output();
    make_bottom_corners();
    //console_output();
    finish_assembling();
    //console_output();

}

bool cube_::check_if_okay() {

    cube_ tmp;

    for (int ed = 0; ed < 6; ed++) {

        for (int s = 0; s < 3; s++) {

            for (int c = 0; c < 3; c++)
                if (cb[ed][s][c] != tmp.cb[ed][s][c])
                    return false;

        }

    }

    return true;

}

void cube_::make_white_cross() {
    while ((cb[1][0][1] != 'W' || cb[1][2][1] != 'W' || cb[1][1][0] != 'W' || cb[1][1][2] != 'W')
           || cb[0][0][1] != cb[0][1][1]
           || cb[2][0][1] != cb[2][1][1]
           || cb[4][0][1] != cb[4][1][1]
           || cb[5][0][1] != cb[5][1][1]) {
        while (cb[1][0][1] != 'W' || cb[1][2][1] != 'W' || cb[1][1][0] != 'W' || cb[1][1][2] != 'W') {
            for (int ed = 0; ed < 6; ed++) {

                if (ed != 1)
                    for (int s = 0; s < 3; s++) {

                        for (int c = 0; c < 3; c++) {

                            if (cb[ed][s][c] == 'W' && ed == 3) {

                                if (s == 1) {

                                    if (c == 0) {

                                        rotate_top_while_not_white(1, 0);
                                        Left_side_left();
                                        Left_side_left();

                                    }
                                    if (c == 2) {

                                        rotate_top_while_not_white(1, 2);
                                        Right_side_left();
                                        Right_side_left();

                                    }
                                }
                                if (c == 1) {

                                    if (s == 0) {

                                        rotate_top_while_not_white(0, 1);
                                        Back_side_right();
                                        Back_side_right();

                                    }
                                    if (s == 2) {

                                        rotate_top_while_not_white(2, 1);
                                        Front_side_left();
                                        Front_side_left();

                                    }

                                }

                            }

                            if (cb[ed][s][c] == 'W' && c == 1 && ed != 3) {

                                if (ed == 0) {

                                    rotate_top_while_not_white(1, 0);

                                    if (s == 0)
                                        Left_side_right();

                                    if (s == 2)
                                        Left_side_left();

                                    rotate_top_while_not_white(2, 1);
                                    Front_side_right();

                                }
                                if (ed == 2) {

                                    rotate_top_while_not_white(1, 2);

                                    if (s == 0)
                                        Right_side_left();

                                    if (s == 2)
                                        Right_side_right();

                                    rotate_top_while_not_white(2, 1);
                                    Front_side_left();

                                }
                                if (ed == 4) {

                                    rotate_top_while_not_white(2, 1);

                                    if (s == 0)
                                        Front_side_right();

                                    if (s == 2)
                                        Front_side_left();

                                    rotate_top_while_not_white(1, 2);
                                    Right_side_right();

                                }

                                if (ed == 5) {

                                    rotate_top_while_not_white(0, 1);

                                    if (s == 0)
                                        Back_side_right();

                                    if (s == 2)
                                        Back_side_left();

                                    rotate_top_while_not_white(1, 2);
                                    Right_side_left();

                                }
                            }

                            if (cb[ed][s][c] == 'W' && s == 1 && ed != 3) {

                                if (ed == 0) {

                                    if (c == 2) {

                                        rotate_top_while_not_white(2, 1);
                                        Front_side_right();

                                    }
                                    if (c == 0) {

                                        rotate_top_while_not_white(0, 1);
                                        Back_side_right();

                                    }
                                }
                                if (ed == 2) {

                                    if (c == 2) {

                                        rotate_top_while_not_white(2, 1);
                                        Back_side_left();

                                    }

                                    if (c == 0) {

                                        rotate_top_while_not_white(0, 1);
                                        Front_side_left();

                                    }
                                }
                                if (ed == 4) {

                                    if (c == 2) {

                                        rotate_top_while_not_white(1, 2);
                                        Right_side_right();

                                    }

                                    if (c == 0) {

                                        rotate_top_while_not_white(1, 0);
                                        Left_side_left();

                                    }
                                }
                                if (ed == 5) {

                                    if (c == 0) {

                                        rotate_top_while_not_white(1, 2);
                                        Right_side_left();

                                    }

                                    if (c == 2) {

                                        rotate_top_while_not_white(1, 0);
                                        Left_side_right();

                                    }

                                }

                            }

                        }

                    }

            }
        }
        int count_of_normal_edges = 0;
        while (count_of_normal_edges < 2) {
            count_of_normal_edges = 0;
            for (int ed = 0; ed < 6; ed++) {
                if (ed != 1 && ed != 3 && cb[ed][0][1] == cb[ed][1][1])
                    count_of_normal_edges++;
            }
            if (count_of_normal_edges < 2)
                Top_side_right();
        }

        if (count_of_normal_edges == 4)
            return;

        if (cb[0][0][1] != cb[0][1][1] && cb[2][0][1] != cb[2][1][1]) {

            Right_side_right();
            Top_side_right();
            Top_side_right();
            Right_side_left();
            Top_side_right();
            Top_side_right();
            Right_side_right();

        }
        if (cb[4][0][1] != cb[4][1][1] && cb[5][0][1] != cb[5][1][1]) {

            Front_side_right();
            Top_side_right();
            Top_side_right();
            Front_side_left();
            Top_side_right();
            Top_side_right();
            Front_side_right();

        }
        for (int ed = 0; ed < 6; ed++) {

            if (ed != 3 && ed != 1) {

                if (ed == 0) {

                    if (cb[ed][0][1] != cb[ed][1][1] && cb[4][0][1] != cb[4][1][1]) {

                        Left_side_right();
                        Top_side_right();
                        Left_side_left();
                        Top_side_left();
                        Left_side_right();

                    }

                }

                if (ed == 2) {

                    if (cb[ed][0][1] != cb[ed][1][1] && cb[5][0][1] != cb[5][1][1]) {

                        Right_side_right();
                        Top_side_right();
                        Right_side_left();
                        Top_side_left();
                        Right_side_right();

                    }

                }

                if (ed == 4) {

                    if (cb[ed][0][1] != cb[ed][1][1] && cb[2][0][1] != cb[2][1][1]) {

                        Front_side_right();
                        Top_side_right();
                        Front_side_left();
                        Top_side_left();
                        Front_side_right();

                    }

                }

                if (ed == 5) {

                    if (cb[ed][0][1] != cb[ed][1][1] && cb[0][0][1] != cb[0][1][1]) {
                        Back_side_right();
                        Top_side_right();
                        Back_side_left();
                        Top_side_left();
                        Back_side_right();

                    }

                }

            }

        }

    }
}

void cube_::angle_right_rotating(int num_of_edge) {

    if (num_of_edge == 0) {

        while (cb[1][2][0] != 'W' || cb[4][0][0] != 'R' || cb[0][0][2] != 'G') {

            Left_side_right();
            Bottom_side_left();
            Left_side_left();
            Bottom_side_right();

        }
        return;

    }

    if (num_of_edge == 2) {

        while (cb[1][0][2] != 'W' || cb[2][0][2] != 'B' || cb[5][0][0] != 'O') {

            Right_side_right();
            Bottom_side_left();
            Right_side_left();
            Bottom_side_right();

        }
        return;

    }
    if (num_of_edge == 4) {


        while (cb[1][2][2] != 'W' || cb[2][0][0] != 'B' || cb[4][0][2] != 'R') {

            Front_side_right();
            Bottom_side_left();
            Front_side_left();
            Bottom_side_right();

        }
        return;

    }
    if (num_of_edge == 5) {

        while (cb[1][0][0] != 'W' || cb[0][0][0] != 'G' || cb[5][0][2] != 'O') {

            Back_side_left();
            Bottom_side_left();
            Back_side_right();
            Bottom_side_right();

        }
        return;

    }

}

void cube_::make_white_corners() {
    while (cb[1][0][0] != 'W' || cb[1][2][0] != 'W' || cb[1][0][2] != 'W' || cb[1][2][2] != 'W') {

        make_right_pos(0, 0);

        if (check_of_corners_ok())
            break;
        make_right_pos(0, 2);

        if (check_of_corners_ok())
            break;
        make_right_pos(2, 0);

        if (check_of_corners_ok())
            break;
        make_right_pos(2, 2);

        if (check_of_corners_ok())
            break;
        make_right_pos(0, 0, 1);

        if (check_of_corners_ok())
            break;
        make_right_pos(0, 2, 1);

        if (check_of_corners_ok())
            break;
        make_right_pos(2, 0, 1);

        if (check_of_corners_ok())
            break;
        make_right_pos(2, 2, 1);

    }
}

void cube_::rotate_top_while_not_white(int s, int c) {
    while (cb[1][s][c] == 'W')
        Top_side_right();
}

bool cube_::check_rightness_of_angle(int s, int c) {

    if (s == 0 && c == 0 && cb[1][0][0] == 'W' && cb[0][0][0] == 'G' && cb[5][0][2] == 'O') {
        return true;
    }

    if (s == 2 && c == 0 && cb[1][2][0] == 'W' && cb[0][0][2] == 'G' && cb[4][0][0] == 'R') {
        return true;
    }

    if (s == 0 && c == 2 && cb[1][0][2] == 'W' && cb[2][0][2] == 'B' && cb[5][0][0] == 'O') {
        return true;
    }

    if (s == 2 && c == 2 && cb[1][2][2] == 'W' && cb[2][0][0] == 'B' && cb[4][0][2] == 'R') {
        return true;
    }

    return false;
}

void cube_::make_right_pos(int s, int c, int layer) {

    std::string angle;

    if (layer != 0 && !check_rightness_of_angle(s, c)) {

        angle += cb[1][s][c];

        if (s == 0 && c == 0)
            angle = angle + cb[0][0][0] + cb[5][0][2];

        if (s == 2 && c == 0)
            angle = angle + cb[0][0][2] + cb[4][0][0];

        if (s == 0 && c == 2)
            angle = angle + cb[2][0][2] + cb[5][0][0];

        if (s == 2 && c == 2)
            angle = angle + cb[2][0][0] + cb[4][0][2];

    }
    if (layer == 0) {
        angle += cb[3][s][c];

        if (s == 0 && c == 0)
            angle = angle + cb[0][2][0] + cb[5][2][2];

        if (s == 2 && c == 0)
            angle = angle + cb[0][2][2] + cb[4][2][0];

        if (s == 0 && c == 2)
            angle = angle + cb[2][2][2] + cb[5][2][0];

        if (s == 2 && c == 2)
            angle = angle + cb[2][2][0] + cb[4][2][2];
    }
    if (angle.find('W') != std::string::npos && angle.find('B') != std::string::npos &&
        angle.find('R') != std::string::npos) {
        if (s == 0 && c == 0 && layer == 0) {
            Bottom_side_right();
            Bottom_side_right();
        }
        if (s == 2 && c == 0 && layer == 0) {
            Bottom_side_left();
        }
        if (s == 0 && c == 2 && layer == 0) {
            Bottom_side_right();
        }
        if (layer != 0 && !check_rightness_of_angle(s, c)) {
            Front_side_right();
            Bottom_side_left();
            Front_side_left();
            Bottom_side_right();
        } else
            angle_right_rotating(4);
    }

    if (angle.find('W') != std::string::npos && angle.find('B') != std::string::npos &&
        angle.find('O') != std::string::npos) {
        if (s == 0 && c == 0 && layer == 0) {
            Bottom_side_right();
        }
        if (s == 2 && c == 0 && layer == 0) {
            Bottom_side_right();
            Bottom_side_right();
        }
        if (s == 2 && c == 2 && layer == 0) {
            Bottom_side_left();
        }
        if (layer != 0 && !check_rightness_of_angle(s, c)) {
            Right_side_right();
            Bottom_side_left();
            Right_side_left();
            Bottom_side_right();
        } else
            angle_right_rotating(2);
    }

    if (angle.find('W') != std::string::npos && angle.find('G') != std::string::npos &&
        angle.find('R') != std::string::npos) {
        if (s == 0 && c == 0 && layer == 0) {
            Bottom_side_left();
        }
        if (s == 0 && c == 2 && layer == 0) {
            Bottom_side_right();
            Bottom_side_right();
        }
        if (s == 2 && c == 2 && layer == 0) {
            Bottom_side_right();
        }
        if (layer != 0 && !check_rightness_of_angle(s, c)) {
            Left_side_right();
            Bottom_side_left();
            Left_side_left();
            Bottom_side_right();
        } else
            angle_right_rotating(0);
    }

    if (angle.find('W') != std::string::npos && angle.find('G') != std::string::npos &&
        angle.find('O') != std::string::npos) {
        if (s == 2 && c == 2 && layer == 0) {
            Bottom_side_right();
            Bottom_side_right();
        }
        if (s == 2 && c == 0 && layer == 0) {
            Bottom_side_right();
        }
        if (s == 0 && c == 2 && layer == 0) {
            Bottom_side_left();
        }
        if (layer != 0 && !check_rightness_of_angle(s, c)) {
            Back_side_left();
            Bottom_side_left();
            Back_side_right();
            Bottom_side_right();
        } else
            angle_right_rotating(5);
    }

}

bool cube_::check_of_corners_ok() {

    if (cb[1][0][0] == 'W' && cb[1][2][0] == 'W' && cb[1][0][2] == 'W' && cb[1][2][2] == 'W'
        && cb[2][0][0] == 'B' && cb[2][0][1] == 'B' && cb[2][0][2] == 'B'
        && cb[4][0][0] == 'R' && cb[4][0][1] == 'R' && cb[4][0][2] == 'R'
        && cb[0][0][0] == 'G' && cb[0][0][1] == 'G' && cb[0][0][2] == 'G'
        && cb[5][0][0] == 'O' && cb[5][0][1] == 'O' && cb[5][0][2] == 'O')
        return true;

    return false;

}

void cube_::make_second_layer() {

    while (cb[0][1][0] != 'G' || cb[0][1][1] != 'G' || cb[0][1][2] != 'G' ||
           cb[4][1][0] != 'R' || cb[4][1][1] != 'R' || cb[4][1][2] != 'R' ||
           cb[2][1][0] != 'B' || cb[2][1][1] != 'B' || cb[2][1][2] != 'B' ||
           cb[5][1][0] != 'O' || cb[5][1][1] != 'O' || cb[5][1][2] != 'O') {

        bool f1 = true, f2 = true, f3 = true, f4 = true;
        while ((f1 + f2 + f3 + f4)) {

            f1 = make_right_edge_pos(0, 1);
            f2 = make_right_edge_pos(1, 0);
            f3 = make_right_edge_pos(2, 1);
            f4 = make_right_edge_pos(1, 2);

        }

        if (cb[0][1][0] == cb[5][1][1] && cb[5][1][2] == cb[0][1][1]) {

            right_algo(0);
            Bottom_side_left();
            Bottom_side_left();
            right_algo(0);

        }
        if (cb[0][1][2] == cb[4][1][1] && cb[4][1][0] == cb[0][1][1]) {

            right_algo(4);
            Bottom_side_left();
            Bottom_side_left();
            right_algo(4);

        }
        if (cb[4][1][2] == cb[2][1][1] && cb[2][1][0] == cb[4][1][1]) {

            right_algo(2);
            Bottom_side_left();
            Bottom_side_left();
            right_algo(2);

        }
        if (cb[2][1][2] == cb[5][1][1] && cb[5][1][0] == cb[2][1][1]) {

            right_algo(5);
            Bottom_side_left();
            Bottom_side_left();
            right_algo(5);

        }

        if ((cb[0][1][0] != cb[5][1][1] && cb[0][1][0] != cb[0][1][1]) ||
            (cb[5][1][2] != cb[5][1][1] && cb[5][1][2] != cb[0][1][1])) {
            right_algo(0);
            continue;
        }

        if ((cb[0][1][2] != cb[4][1][1] && cb[0][1][2] != cb[0][1][1]) ||
            (cb[4][1][0] != cb[4][1][1] && cb[4][1][0] != cb[0][1][1])) {
            right_algo(4);
            continue;
        }

        if ((cb[4][1][2] != cb[2][1][1] && cb[4][1][2] != cb[4][1][1]) ||
            (cb[2][1][0] != cb[2][1][1] && cb[2][1][0] != cb[4][1][1])) {
            right_algo(2);
            continue;
        }

        if ((cb[2][1][2] != cb[5][1][1] && cb[2][1][2] != cb[2][1][1]) ||
            (cb[5][1][0] != cb[5][1][1] && cb[5][1][0] != cb[2][1][1])) {
            right_algo(5);
            continue;
        }

    }

}

bool cube_::make_right_edge_pos(int s, int c) {
    bool state = false;
    std::string angle;
    int curr_edge;
    angle += cb[3][s][c];

    if (s == 0 && c == 1) {
        angle = cb[5][2][1] + angle;
        curr_edge = 5;
    }

    if (s == 1 && c == 0) {
        angle = cb[0][2][1] + angle;
        curr_edge = 0;
    }

    if (s == 1 && c == 2) {
        angle = cb[2][2][1] + angle;
        curr_edge = 2;
    }

    if (s == 2 && c == 1) {
        angle = cb[4][2][1] + angle;
        curr_edge = 4;
    }


    if (angle.find('Y') == std::string::npos) {
        state = true;
        std::vector<int> edges = {0, 5, 2, 4};
        int ed_num = -1;

        for (int i = 0; i < 4; i++)
            if (edges[i] == curr_edge)
                ed_num = i;

        while (true) {

            if (cb[curr_edge][1][1] == angle[0])
                break;
            ed_num++;
            ed_num %= 4;
            curr_edge = edges[ed_num];
            Bottom_side_right();
        }
    }

    if (angle.find('B') != std::string::npos && angle.find('R') != std::string::npos) {

        if (angle[0] == 'B' && angle[1] == 'R') {
            right_algo(2);
        }

        if (angle[0] == 'R' && angle[1] == 'B') {
            left_algo(4);
        }

    }

    if (angle.find('B') != std::string::npos && angle.find('O') != std::string::npos) {

        if (angle[0] == 'B' && angle[1] == 'O') {
            left_algo(2);
        }

        if (angle[0] == 'O' && angle[1] == 'B') {
            right_algo(5);
        }

    }

    if (angle.find('G') != std::string::npos && angle.find('R') != std::string::npos) {

        if (angle[0] == 'G' && angle[1] == 'R') {
            left_algo(0);
        }

        if (angle[0] == 'R' && angle[1] == 'G') {
            right_algo(4);
        }

    }

    if (angle.find('G') != std::string::npos && angle.find('O') != std::string::npos) {

        if (angle[0] == 'G' && angle[1] == 'O') {
            right_algo(0);
        }

        if (angle[0] == 'O' && angle[1] == 'G') {
            left_algo(5);
        }
    }

    return state;

}

void cube_::right_algo(int edge) {

    if (edge == 0) {

        Bottom_side_left();
        Back_side_left();
        Bottom_side_right();
        Back_side_right();
        Left_side_right();
        Back_side_right();
        Left_side_left();
        Back_side_left();

    }

    if (edge == 4) {

        Bottom_side_left();
        Left_side_right();
        Bottom_side_right();
        Left_side_left();
        Front_side_right();
        Left_side_left();
        Front_side_left();
        Left_side_right();

    }

    if (edge == 5) {

        Bottom_side_left();
        Right_side_right();
        Bottom_side_right();
        Right_side_left();
        Back_side_left();
        Right_side_left();
        Back_side_right();
        Right_side_right();

    }

    if (edge == 2) {

        Bottom_side_left();
        Front_side_right();
        Bottom_side_right();
        Front_side_left();
        Right_side_right();
        Front_side_left();
        Right_side_left();
        Front_side_right();

    }

}

void cube_::left_algo(int edge) {

    if (edge == 0) {

        Bottom_side_right();
        Front_side_left();
        Bottom_side_left();
        Front_side_right();
        Left_side_left();
        Front_side_right();
        Left_side_right();
        Front_side_left();

    }

    if (edge == 4) {

        Bottom_side_right();
        Right_side_left();
        Bottom_side_left();
        Right_side_right();
        Front_side_left();
        Right_side_right();
        Front_side_right();
        Right_side_left();

    }

    if (edge == 5) {

        Bottom_side_right();
        Left_side_left();
        Bottom_side_left();
        Left_side_right();
        Back_side_right();
        Left_side_right();
        Back_side_left();
        Left_side_left();

    }

    if (edge == 2) {

        Bottom_side_right();
        Back_side_right();
        Bottom_side_left();
        Back_side_left();
        Right_side_left();
        Back_side_left();
        Right_side_right();
        Back_side_right();

    }

}

void cube_::make_yellow_cross() {

    if (cb[3][0][1] == 'Y' && cb[3][1][0] == 'Y' && cb[3][1][2] == 'Y' && cb[3][2][1] == 'Y')
        return;

    if (cb[3][1][0] == 'Y' && cb[3][1][1] == 'Y' && cb[3][1][2] == 'Y' && cb[3][0][1] != 'Y' && cb[3][2][1] != 'Y') {
        stick_algo(0);
        return;
    }

    if (cb[3][1][0] != 'Y' && cb[3][1][1] == 'Y' && cb[3][1][2] != 'Y' && cb[3][0][1] == 'Y' && cb[3][2][1] == 'Y') {
        stick_algo(4);
        return;
    }

    if (cb[3][1][0] == 'Y' && cb[3][1][1] == 'Y' && cb[3][1][2] != 'Y' && cb[3][0][1] != 'Y' && cb[3][2][1] == 'Y') {
        jackdaw_algo(2);
        return;
    }
    if (cb[3][1][0] == 'Y' && cb[3][1][1] == 'Y' && cb[3][1][2] != 'Y' && cb[3][0][1] == 'Y' && cb[3][2][1] != 'Y') {
        jackdaw_algo(4);
        return;
    }
    if (cb[3][1][0] != 'Y' && cb[3][1][1] == 'Y' && cb[3][1][2] == 'Y' && cb[3][0][1] == 'Y' && cb[3][2][1] != 'Y') {
        jackdaw_algo(0);
        return;
    }
    if (cb[3][1][0] != 'Y' && cb[3][1][1] == 'Y' && cb[3][1][2] == 'Y' && cb[3][0][1] != 'Y' && cb[3][2][1] == 'Y') {
        jackdaw_algo(5);
        return;
    }
    stick_algo(0);
    Bottom_side_left();
    Bottom_side_left();
    jackdaw_algo(0);

}

void cube_::stick_algo(int edge) {

    if (edge == 0) {

        Front_side_right();
        Left_side_right();
        Bottom_side_left();
        Left_side_left();
        Bottom_side_right();
        Front_side_left();

    }

    if (edge == 4) {

        Right_side_right();
        Front_side_right();
        Bottom_side_left();
        Front_side_left();
        Bottom_side_right();
        Right_side_left();

    }

}

void cube_::jackdaw_algo(int edge) {

    if (edge == 0) {

        Front_side_right();
        Bottom_side_left();
        Left_side_right();
        Bottom_side_right();
        Left_side_left();
        Front_side_left();

    }

    if (edge == 4) {

        Right_side_right();
        Bottom_side_left();
        Front_side_right();
        Bottom_side_right();
        Front_side_left();
        Right_side_left();

    }

    if (edge == 2) {

        Back_side_left();
        Bottom_side_left();
        Right_side_right();
        Bottom_side_right();
        Right_side_left();
        Back_side_right();

    }

    if (edge == 5) {

        Left_side_right();
        Bottom_side_left();
        Back_side_left();
        Bottom_side_right();
        Back_side_right();
        Left_side_left();

    }

}

void cube_::make_yellow_corners() {
    //left of right fish algo case
    while (cb[3][0][0] != 'Y' || cb[3][0][1] != 'Y' || cb[3][0][2] != 'Y' ||
           cb[3][1][0] != 'Y' || cb[3][1][1] != 'Y' || cb[3][1][2] != 'Y' ||
           cb[3][2][0] != 'Y' || cb[3][2][1] != 'Y' || cb[3][2][2] != 'Y') {


        if ((cb[3][0][0] == 'Y' && cb[3][2][0] != 'Y' && cb[3][0][2] != 'Y' && cb[3][2][2] != 'Y') ||
            (cb[3][0][0] != 'Y' && cb[3][2][0] == 'Y' && cb[3][0][2] != 'Y' && cb[3][2][2] != 'Y') ||
            (cb[3][0][0] != 'Y' && cb[3][2][0] != 'Y' && cb[3][0][2] == 'Y' && cb[3][2][2] != 'Y') ||
            (cb[3][0][0] != 'Y' && cb[3][2][0] != 'Y' && cb[3][0][2] != 'Y' && cb[3][2][2] == 'Y')) {

            while (cb[3][0][0] != 'Y')
                Bottom_side_left();


            if (cb[0][2][2] == 'Y' && cb[4][2][2] == 'Y') {
                left_fish_algo();
            }
            if (cb[2][2][0] == 'Y' && cb[5][2][0] == 'Y') {
                Bottom_side_left();
                Bottom_side_left();
                right_fish_algo();
            }
            continue;
        }
        if ((cb[3][0][0] == 'Y' && cb[3][0][2] == 'Y') || (cb[3][0][0] == 'Y' && cb[3][2][0] == 'Y') ||
            (cb[3][0][2] == 'Y' && cb[3][2][2] == 'Y') || (cb[3][2][0] == 'Y' && cb[3][2][2] == 'Y')) {

            while (cb[3][0][2] != 'Y' || cb[3][2][2] != 'Y')
                Bottom_side_left();

            if (cb[0][2][0] == 'Y' && cb[0][2][2] == 'Y') {

                left_fish_algo();
                Bottom_side_right();
                right_fish_algo();

            } else {
                Bottom_side_right();
                left_fish_algo();
                Bottom_side_left();
                right_fish_algo();
            }

            continue;

        }
        if ((cb[3][2][2] == 'Y' && cb[3][0][0] == 'Y') || (cb[3][2][0] == 'Y' && cb[3][0][2] == 'Y')) {

            if (cb[3][2][2] == 'Y' && cb[3][0][0] == 'Y')
                Bottom_side_left();
            if (cb[0][2][0] != 'Y') {
                Bottom_side_left();
                Bottom_side_left();
            }
            left_fish_algo();
            Bottom_side_left();
            Bottom_side_left();
            right_fish_algo();

            continue;
        }

        for (int q = 0; q < 4; q++) {

            if (cb[0][2][0] == 'Y' && cb[0][2][2] == 'Y') {

                right_fish_algo();
                continue;

            }
            if (cb[4][2][0] == 'Y') {

                right_fish_algo();
                Bottom_side_right();
                right_fish_algo();
                continue;

            }

            Bottom_side_left();

        }

    }
}

void cube_::right_fish_algo() {

    Left_side_right();
    Bottom_side_left();
    Left_side_left();
    Bottom_side_left();
    Left_side_right();
    Bottom_side_left();
    Bottom_side_left();
    Left_side_left();

}

void cube_::left_fish_algo() {

    Left_side_right();
    Bottom_side_left();
    Bottom_side_left();
    Left_side_left();
    Bottom_side_right();
    Left_side_right();
    Bottom_side_right();
    Left_side_left();

}

void cube_::make_bottom_corners() {
    while ((cb[4][2][0] != 'R' && cb[0][2][2] != 'G') ||
           (cb[2][2][0] != 'B' && cb[4][2][2] != 'R') ||
           (cb[5][2][0] != 'O' && cb[2][2][2] != 'B') ||
           (cb[0][2][0] != 'G' && cb[5][2][2] != 'O')) {

//    while (!((cb[4][2][0] == 'R' && cb[0][2][2] == 'G') && cb[2][2][0] != 'B' && cb[4][2][2] != 'R' &&
//             cb[5][2][0] != 'O' && cb[2][2][2] != 'B' && cb[0][2][0] != 'G' && cb[5][2][2] != 'O') ||
//           !((cb[4][2][0] != 'R' && cb[0][2][2] != 'G') && cb[2][2][0] == 'B' && cb[4][2][2] == 'R' &&
//             cb[5][2][0] != 'O' && cb[2][2][2] != 'B' && cb[0][2][0] != 'G' && cb[5][2][2] != 'O') ||
//           !((cb[4][2][0] != 'R' && cb[0][2][2] != 'G') && cb[2][2][0] != 'B' && cb[4][2][2] != 'R' &&
//             cb[5][2][0] == 'O' && cb[2][2][2] == 'B' && cb[0][2][0] != 'G' && cb[5][2][2] != 'O') ||
//           !((cb[4][2][0] != 'R' && cb[0][2][2] != 'G') && cb[2][2][0] != 'B' && cb[4][2][2] != 'R' &&
//             cb[5][2][0] != 'O' && cb[2][2][2] != 'B' && cb[0][2][0] == 'G' && cb[5][2][2] == 'O'))
//        Bottom_side_left();

        while (cb[4][2][2] != 'R')
            Bottom_side_left();

        int what_edge_to_turn = 0;

        if (cb[4][2][2] == 'R' && cb[2][2][2] == 'B') {

            while (cb[0][2][2] != 'G')
                Bottom_side_left();

            what_edge_to_turn = 5;

        } else if (cb[2][2][0] == 'B' && cb[4][2][0] == 'R') {

            while (cb[5][2][0] != 'O')
                Bottom_side_left();

            what_edge_to_turn = 4;

        } else if (cb[4][2][0] == 'R' && cb[0][2][0] == 'G') {

            while (cb[2][2][0] != 'B')
                Bottom_side_left();

            what_edge_to_turn = 0;

        } else if (cb[5][2][0] == 'O' && cb[0][2][0] == 'G') {

            while (cb[4][2][0] != 'R')
                Bottom_side_left();

            what_edge_to_turn = 5;

        }

        if (cb[4][2][2] == 'R' && cb[0][2][0] == 'G') {
            eye_on_the_right(0);
            continue;
        }
        while ((cb[4][2][0] != 'R' && cb[0][2][2] != 'G') ||
               (cb[2][2][0] != 'B' && cb[4][2][2] != 'R') ||
               (cb[5][2][0] != 'O' && cb[2][2][2] != 'B') ||
               (cb[0][2][0] != 'G' && cb[5][2][2] != 'O')) {

            eye_on_the_right(what_edge_to_turn);

        }
    }
}

void cube_::eye_on_the_right(int edge) {

    if (edge == 0) {

        Left_side_right();
        Left_side_right();
        Back_side_left();
        Back_side_left();
        Left_side_right();
        Front_side_right();
        Left_side_left();
        Back_side_left();
        Back_side_left();
        Left_side_right();
        Front_side_left();
        Left_side_right();

    }

    if (edge == 4) {

        Front_side_right();
        Front_side_right();
        Left_side_right();
        Left_side_right();
        Front_side_right();
        Right_side_right();
        Front_side_left();
        Left_side_right();
        Left_side_right();
        Front_side_right();
        Right_side_left();
        Front_side_right();

    }

    if (edge == 2) {

        Right_side_right();
        Right_side_right();
        Front_side_right();
        Front_side_right();
        Right_side_right();
        Back_side_left();
        Right_side_left();
        Front_side_right();
        Front_side_right();
        Right_side_right();
        Back_side_right();
        Right_side_right();

    }

    if (edge == 5) {

        Back_side_left();
        Back_side_left();
        Right_side_right();
        Right_side_right();
        Back_side_left();
        Left_side_right();
        Back_side_right();
        Right_side_right();
        Right_side_right();
        Back_side_left();
        Left_side_left();
        Back_side_left();

    }
}

void cube_::triangular(int edge) {

    if (edge == 0) {

        Left_side_right();
        Bottom_side_right();
        Left_side_right();
        Bottom_side_left();
        Left_side_right();
        Bottom_side_left();
        Left_side_right();
        Bottom_side_right();
        Left_side_left();
        Bottom_side_right();
        Left_side_right();
        Left_side_right();

    }

    if (edge == 4) {

        Front_side_right();
        Bottom_side_right();
        Front_side_right();
        Bottom_side_left();
        Front_side_right();
        Bottom_side_left();
        Front_side_right();
        Bottom_side_right();
        Front_side_left();
        Bottom_side_right();
        Front_side_right();
        Front_side_right();

    }

    if (edge == 2) {

        Right_side_right();
        Bottom_side_right();
        Right_side_right();
        Bottom_side_left();
        Right_side_right();
        Bottom_side_left();
        Right_side_right();
        Bottom_side_right();
        Right_side_left();
        Bottom_side_right();
        Right_side_right();
        Right_side_right();

    }

    if (edge == 5) {

        Back_side_left();
        Bottom_side_right();
        Back_side_left();
        Bottom_side_left();
        Back_side_left();
        Bottom_side_left();
        Back_side_left();
        Bottom_side_right();
        Back_side_right();
        Bottom_side_right();
        Back_side_left();
        Back_side_left();

    }

}

void cube_::finish_assembling() {

    if (cb[0][2][1] == 'B' && cb[4][2][1] == 'G') {
        triangular(0);
    }
    if (cb[5][2][1] == 'R' && cb[4][2][1] == 'G') {
        triangular(5);
    }
    if (cb[0][2][1] == 'O' && cb[2][2][1] == 'G') {
        triangular(2);
    }
    if (cb[4][2][1] == 'O' && cb[2][2][1] == 'R') {
        triangular(4);
    }


    if (cb[4][2][1] == 'B' && cb[0][2][1] == 'R') {

        triangular(0);
        triangular(0);

    }
    if (cb[4][2][1] == 'O' && cb[0][2][1] == 'R') {

        triangular(5);
        triangular(5);

    }
    if (cb[5][2][1] == 'G' && cb[0][2][1] == 'B') {

        triangular(2);
        triangular(2);

    }
    if (cb[4][2][1] == 'B' && cb[5][2][1] == 'R') {

        triangular(4);
        triangular(4);

    }

    if (cb[4][2][1] == 'G' && cb[0][2][1] == 'R') {

        triangular(0);
        Bottom_side_right();
        triangular(0);
        Bottom_side_left();

    }
    if (cb[4][2][1] == 'B' && cb[2][2][1] == 'R') {

        triangular(4);
        Bottom_side_right();
        triangular(4);
        Bottom_side_left();

    }

    if (cb[0][2][1] == 'B' && cb[2][2][1] == 'G') {
        triangular(0);
        Bottom_side_left();
        triangular(0);
        Bottom_side_right();
    }

}

void cube_::get_answer() {

    if (answer.empty())
        std::cout << " - " << std::endl;

    else
        std::cout << answer << std::endl;

}

