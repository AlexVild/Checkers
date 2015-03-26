// Alex Vild
// Project 6
// 4/13/2014
//------------

#include "game.h"
#include "piece.h"
#include <string>
#include <iostream>

class checkers :public main_savitch_14::game
{

   public:
   // VIRTUAL GAME FUNCTIONS
	void make_move(const std:: string& move);
	void restart();
	void display_status() const;
	bool is_legal(const std::string& move) const;
        bool is_game_over() const;
        bool is_jump(const std:: string& move) const;
        bool jump_availible() const;
        who winning() const;
        const std::string convert_to_string(const int i,const int j, const int i2, const int j2) const;
    private:
        piece bd[8][8];
};
