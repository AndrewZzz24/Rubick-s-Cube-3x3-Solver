#include <vector>
#include <sstream>
#include <iostream>

#ifndef IS_2020_PROG_2_SEM_CUBE_HPP
#define IS_2020_PROG_2_SEM_CUBE_HPP

class cube_ {

private:

    std::vector <std::vector<std::vector < char>>>
    cb;

    std::string answer;
    std::string file_name;

public:

    cube_(); //done

    bool save_the_state(); //done

    bool read_the_state(); //done

    [[nodiscard]] bool check_state_validness() const; //done

    void console_output() const; //done

    void turn_edge(std::string &what_edge, std::string &where_to); //done

    void generate(); //done

    void find_solution(); //done

    void get_answer(); //done

private:

    bool check_if_okay();

    [[nodiscard]] bool check_angles() const; //done

    [[nodiscard]] bool check_num_of_colours() const; //done

    [[nodiscard]] bool check_centre() const; //done

    [[nodiscard]] bool check_edges() const; //done

    void turn_side_left(int what_edge); //done

    void turn_side_right(int what_edge); //done

    void Left_side_left(int _num_of_edge = 0, int what_to_do = 0); //done

    void Left_side_right(int _num_of_edge = 0, int what_to_do = 0); //done

    void Top_side_left(int _num_of_layer = 0, int what_to_do = 0); //done

    void Top_side_right(int _num_of_layer = 0, int what_to_do = 0);//done

    void Right_side_left(int what_to_do = 0); //done

    void Right_side_right(int what_to_do = 0); //done

    void Bottom_side_left(int what_to_do = 0); //done

    void Bottom_side_right(int what_to_do = 0); //done

    void Front_side_left(int _num_of_layer = 0, int what_to_do = 0); //done

    void Front_side_right(int _num_of_layer = 0, int what_to_do = 0); //done

    void Back_side_left(int what_to_do = 0); //done

    void Back_side_right(int what_to_do = 0); //done

    void make_white_cross(); //done

    void rotate_top_while_not_white(int s, int c); //done

    void angle_right_rotating(int num_of_edge); //done

    void make_right_pos(int s, int c, int layer = 0); //done

    void make_white_corners(); //done

    bool check_of_corners_ok(); //done

    bool check_rightness_of_angle(int s, int c); //done

    void make_second_layer(); //done

    bool make_right_edge_pos(int s, int c); //done

    void right_algo(int edge); //done

    void left_algo(int edge); //done

    void make_yellow_cross();

    void stick_algo(int edge);

    void jackdaw_algo(int edges);

    void make_yellow_corners();

    void right_fish_algo();

    void left_fish_algo();

    void make_bottom_corners();

    void eye_on_the_right(int edge);

    void finish_assembling();

    void triangular(int edge);

};


#endif //IS_2020_PROG_2_SEM_CUBE_HPP
