// Alex Vild
// Project 6
// 4/13/2014
//------------

#include <cctype>

class piece
{
	public:
		piece() {king = false; team = 'n'; empty = true;}
		void set_team_blk() {team = 'b';}
		void set_team_red() {team = 'r';}
		void set_king() {king = true;}
		void not_king() {king = false;}
		void set_empty() {empty = true; team = 'n'; king = false;}
		void not_empty() {empty = false;}
		const char get_team() const {return team;}
		const bool is_king() const {return king;}
		const bool is_empty() const {return empty;}
		void operator = (const piece &p) {king = p.king; empty = p.empty; team = p.team;}
	private:
		bool king;
		char team;
		bool empty;
};
