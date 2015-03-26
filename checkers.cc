// Alex Vild
// Project 6
// 4/13/2014
//------------

#include "checkers.h"
#include "colors.h"
#include <iostream>
#include <string>

using namespace std;



				// MAKE MOVE
void checkers::make_move(const std:: string& move)
{	
	int j, i, j2, i2, x, y, x2, y2;
	bool was_jump = false;
	
	j = tolower(move[0]) - 'a';
	i = move[1] - '0';
	j2 = tolower(move[2]) - 'a';
	i2 = move[3] - '0';

	if (is_jump(move))
	{
		x = (j2-j)/2;
		y = (i2-i)/2;
		x2 = j+x;
		y2 = i+y;
		cout << "JUMP" << endl;
		bd[y2][x2].set_empty();
		was_jump = true;
	}
	bd[i2][j2] = bd[i][j];
	bd[i][j].set_empty();
	if (bd[i2][j2].get_team() == 'b' && i2 == 0)
	{
		bd[i2][j2].set_king();
		game::make_move(move);
		return;		
	}
	else if (bd[i2][j2].get_team() == 'r' && i2 == 7)
	{	
		bd[i2][j2].set_king();
		game::make_move(move);
		return;
	}
	else if(jump_availible() && was_jump)
	{
		x = i2;
		y = j2;
		x2 = x+2;
		y2 = y+2;
		string tmp;
		tmp = convert_to_string(x, y, x2, y2);
		if (is_legal(tmp))
		{
			make_move(tmp);
		}
		x = i2;
		y = j2;
		x2 = x-2;
		y2 = y+2;
		tmp = convert_to_string(x, y, x2, y2);
		if (is_legal(tmp))
		{
			make_move(tmp);
		}
		x = i2;
		y = j2;
		x2 = x+2;
		y2 = y-2;
		tmp = convert_to_string(x, y, x2, y2);
		if (is_legal(tmp))
		{
			make_move(tmp);
		}
		x = i2;
		y = j2;
		x2 = x-2;
		y2 = y-2;
		tmp = convert_to_string(x, y, x2, y2);
		if (is_legal(tmp))
		{
			make_move(tmp);
		}
	}
	else
	{
		game::make_move(move);
		
	}
}



				// RESTART
void checkers::restart()
{
// i = rows, j = columns
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
//RED TEAM init
			if (i < 3)
			{
				if (i%2 == 0)
				{
					if (j%2==0)
					{
						bd[i][j].set_team_red();
						bd[i][j].not_empty();
						bd[i][i].not_king();
					}
					else
					{
						bd[i][j].set_empty();
						bd[i][i].not_king();
					}
				}
				else
				{
					if (j%2==1)
					{
						bd[i][j].set_team_red();
						bd[i][j].not_empty();
						bd[i][i].not_king();
					}
					else
					{
						bd[i][j].set_empty();
						bd[i][i].not_king();
					}
				}
			}
// BLUE TEAM init
			else if (i > 4)
			{
				if (i%2 == 0)
				{
					if (j%2==0)
					{
						bd[i][j].set_team_blk();
						bd[i][j].not_empty();
						bd[i][i].not_king();
					}
					else
					{
						bd[i][j].set_empty();
						bd[i][i].not_king();
					}
				}
				else
				{
					if (j%2==1)
					{
						bd[i][j].set_team_blk();
						bd[i][j].not_empty();
						bd[i][i].not_king();
					}	
					else
					{
						bd[i][j].set_empty();
						bd[i][i].not_king();
					}
				}	
			}
			else
			{
				bd[i][j].set_empty();
				bd[i][i].not_king();
			}
		}
	}
	return;
}



				// IS LEGAL
bool checkers::is_legal(const std:: string& move) const
{
// CONVERTING MOVE
	int j, i, j2, i2;
	
	j = tolower(move[0]) - 'a';
	i = move[1] - '0';
	j2 = tolower(move[2]) - 'a';
	i2 = move[3] - '0';
	
	//--------RULES--------	
	

// CHECKING FOR EMPTY SPOT INITIAL
	if(bd[i][j].is_empty())
	{
		cout << "Piece does not exist." << endl;
		return false;
	}
	
// CHECKING FOR EMPTY MOVE
	if(!bd[i2][j2].is_empty())
	{
		cout << "Spot you are moving to is not empty." << endl;
		return false;
	}
	
//CHECKING FOR STRAIGHT MOVE
	if(j == j2)
	{
		cout << "Can't move straight." << endl;
		return false;
	}
	if(i == i2)
	{
		cout << "Can't move straight." << endl;
		return false;
	}
	
//CHECKING FOR RED SPACE MOVE
	if (i2%2==0)
	{
		if (j2%2 == 1)
		{
			cout << "Can't move on red space." << endl;
			return false;	
		}
	}
	if (i2%2==1)
	{
		if (j2%2 == 0)
		{
			cout << "Can't move on red space." << endl;
			return false;	
		}
	}
	
// CHECK FOR OUT OF BOUNDS PIECE/MOVE
	if (i >= 8 || j >= 8)
	{
		cout << "Piece not on board." << endl;
		return false;
	}
	if (i2 >= 8 || j2 >= 8)
	{
		cout << "Space does not exist." << endl;
		return false;
	}
	
// CHECK FOR BLACK TEAM BACKWARDS MOVE
	if (bd[i][j].get_team() == 'b')
	{
		if (!bd[i][j].is_king() && i2 > i)
		{
			cout << "Non-king piece can't move backwards." << endl;
			return false;
		}
	}
	if (bd[i][j].get_team() == 'r')
	{
		if (!bd[i][j].is_king() && i2 < i)
		{
			cout << "Non-king piece can't move backwards." << endl;
			return false;
		}
	}

// WHO'S MOVING WHAT
	if (last_mover() == COMPUTER)
	{
		if (bd[i][j].get_team() == 'r')
		{
			cout << "Wrong team." << endl;
			return false;
		}
	}
	if (last_mover() == HUMAN)
	{
		if (bd[i][j].get_team() == 'b')
		{
			cout << "Wrong team." << endl;
			return false;
		}
	}

// FORCE JUMP
	if (jump_availible())
	{
		if (!is_jump(move))
		{
			cout << "There is a jump available." << endl;
			return false;
		}
		else
			return true;
	}
	
// HOW FAR
	if (i2 > i+2 || i2 < i - 2 || j2 > j+2 || j2 < j-2)
	{
		cout << "Jumped too far." << endl;
		return false;
	}
	
// MOVE IS LEGAL
	return true;
}	



				// DISPLAY STATUS
void checkers::display_status() const
{
// i = rows, j = columns
	int i = 0, j = 0;
// Outputs column markers on top
	cout << B_BLUE << BOLD << YELLOW << "    A  B  C  D  E  F  G  H    " << B_BLACK << endl;
	cout << RESET;
	for (int i = 0; i < 8; i++)
	{
		if (i%2 == 0)
		{
// Outputs the checkerboard
			cout << B_BLUE << BOLD << YELLOW << " " << i << " ";			
			for (j = 0; j < 8; j++)
			{
			  if (bd[i][j].is_empty())
		       	  {
			    if (j%2 == 0)
				cout << B_BLACK << "   ";
			    else
				cout << B_RED << "   ";
			  }
			  else if (bd[i][j].get_team() == 'r')
			  {
				if (bd[i][j].is_king())
					cout<< B_BLACK << " " << RED << "K" << " ";
				else
					cout<< B_BLACK << " " << RED << "O" << " ";
			  }
			  else if (bd[i][j].get_team() == 'b')
			  {
				if(bd[i][j].is_king())
					cout<< B_BLACK << " " << BLUE << "K" << " ";
				else
					cout<< B_BLACK << " " << BLUE << "O" << " ";
			  } 
			}
// Adds blue border
			cout << B_BLUE << "   ";
			cout << RESET;
		}
		else
		{
			cout << B_BLUE << BOLD << YELLOW << " " << i << " ";			
			for (int j = 0; j < 8; j++)
			  if (bd[i][j].is_empty())
		       	  {
			    if (j%2 == 0)
				cout << B_RED<< "   ";
			    else
				cout << B_BLACK << "   ";
			  }
			  else if (bd[i][j].get_team() == 'r')
			  {
				if(bd[i][j].is_king())
					cout<< B_BLACK << " " << RED << "K" << " ";
				else
					cout<< B_BLACK << " " << RED << "O" << " ";
			  }
			  else if (bd[i][j].get_team() == 'b')
			  {
				if(bd[i][j].is_king())
					cout << B_BLACK << " " << BLUE << "K" << " ";
				else
					cout << B_BLACK << " " << BLUE << "O" << " ";
			  }
			cout << B_BLUE << "   ";
			cout << RESET;
		}
	cout << endl;
	}
	
	cout << B_BLUE << BOLD << YELLOW << "    A  B  C  D  E  F  G  H    " << B_BLACK;
	cout << RESET << endl;
}



				// IS GAME OVER
bool checkers::is_game_over() const
{
	int blk_pc = 0, red_pc = 0, total = 0;
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(!bd[i][j].is_empty())
			{
				if(bd[i][j].get_team() == 'r')
					red_pc++;
				if(bd[i][j].get_team() == 'b')
					blk_pc++;
				total++;
			}
		}
	}
	
	if (total == red_pc)
		return true;
	if (total == blk_pc)
		return true;
	return false;
}



				// LEGAL JUMP?
bool checkers::is_jump(const std:: string& move) const
{
	string tmp;
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
// KING JUMP
			if (bd[i][j].is_king())
			{
// BLACK TEAM
				if(bd[i][j].get_team() == 'b' && last_mover() == COMPUTER)
				{
					if (bd[i-1][j-1].get_team() == 'r')
					{
						if (bd[i-2][j-2].is_empty())
						{
							tmp = convert_to_string(i, j, i-2, j-2);
							if ((i-2 < 8 && i-2 >= 0) && (j-2 < 8 && j-2 >= 0))
							{
								if (tmp == move)
									return true;
							}
						}
					}
					if (bd[i-1][j+1].get_team() == 'r')
					{
						if (bd[i-2][j+2].is_empty())
						{
							tmp = convert_to_string(i, j, i-2, j+2);
							if ((i-2 < 8 && i-2 >= 0) && (j+2 < 8 && j+2 >= 0))
							{
								if (tmp == move)
									return true;
							}
						}
					}
					if (bd[i+1][j+1].get_team() == 'r')
					{
						if (bd[i+2][j+2].is_empty())
						{
							tmp = convert_to_string(i, j, i+2, j+2);
							if ((i+2 < 8 && i+2 >= 0) && (j+2 < 8 && j+2 >= 0))
							{
								if (tmp == move)
									return true;
							}
						}
					}
					if (bd[i+1][j-1].get_team() == 'r')
					{
						if (bd[i+2][j-2].is_empty())
						{
							tmp = convert_to_string(i, j, i+2, j-2);
							if ((i+2 < 8 && i+2 >= 0) && (j-2 < 8 && j-2 >= 0))
							{
								if (tmp == move)
									return true;
							}
						}
					}
				}
				
// RED TEAM
				if(bd[i][j].get_team() == 'r' && last_mover() == HUMAN)
				{
					if (bd[i-1][j-1].get_team() == 'b')
					{
						if (bd[i-2][j-2].is_empty())
						{
							tmp = convert_to_string(i, j, i-2, j-2);
							if ((i-2 < 8 && i-2 >= 0) && (j-2 < 8 && j-2 >= 0))
							{
								if (tmp == move)
									return true;
							}
						}
					}
					if (bd[i-1][j+1].get_team() == 'b')
					{
						if (bd[i-2][j+2].is_empty())
						{
							tmp = convert_to_string(i, j, i-2, j+2);
							if ((i-2 < 8 && i-2 >= 0) && (j+2 < 8 && j+2 >= 0))
							{
								if (tmp == move)
									return true;
							}
						}
					}
					if (bd[i+1][j+1].get_team() == 'b')
					{
						if (bd[i+2][j+2].is_empty())
						{
							tmp = convert_to_string(i, j, i+2, j+2);
							if ((i+2 < 8 && i+2 >= 0) && (j+2 < 8 && j+2 >= 0))
							{
								if (tmp == move)
									return true;
							}
						}
					}
					if (bd[i+1][j-1].get_team() == 'b')
					{
						if (bd[i+2][j-2].is_empty())
						{
							tmp = convert_to_string(i, j, i+2, j-2);
							if ((i+2 < 8 && i+2 >= 0) && (j-2 < 8 && j-2 >= 0))
							{
								if (tmp == move)
									return true;
							}
						}
					}
				}			
			}
// NOT KING
// BLACK TEAM
				if(bd[i][j].get_team() == 'b' && last_mover() == COMPUTER)
				{
					if (bd[i-1][j-1].get_team() == 'r')
					{
						if (bd[i-2][j-2].is_empty())
						{
							tmp = convert_to_string(i, j, i-2, j-2);
							if ((i-2 < 8 && i-2 >= 0) && (j-2 < 8 && j-2 >= 0))
							{
								if (tmp == move)
									return true;
							}
						}
					}
					if (bd[i-1][j+1].get_team() == 'r')
					{
						if (bd[i-2][j+2].is_empty())
						{
							tmp = convert_to_string(i, j, i-2, j+2);
							if ((i-2 < 8 && i-2 >= 0) && (j+2 < 8 && j+2 >= 0))
							{
								if (tmp == move)
									return true;
							}
						}
					}
				}
// RED TEAM
				if(bd[i][j].get_team() == 'r' && last_mover() == HUMAN)
				{
					if (bd[i+1][j-1].get_team() == 'b')
					{
						if (bd[i+2][j-2].is_empty())
						{
							tmp = convert_to_string(i, j, i+2, j-2);
							if ((i+2 < 8 && i+2 >= 0) && (j-2 < 8 && j-2 >= 0))
							{
								if (tmp == move)
									return true;
							}
						}
					}
					if (bd[i+1][j+1].get_team() == 'b')
					{
						if (bd[i+2][j+2].is_empty())
						{
							tmp = convert_to_string(i, j, i+2, j+2);
							if ((i+2 < 8 && i+2 >= 0) && (j+2 < 8 && j+2 >= 0))
							{
								if (tmp == move)
									return true;
							}
						}
					}
				}
		}
	}
	return false;
}



				// IS JUMP AVAILIBLE?
bool checkers::jump_availible() const
{	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
// KING JUMP
			if (bd[i][j].is_king())
			{
// BLACK TEAM
				if(bd[i][j].get_team() == 'b' && last_mover() == COMPUTER)
				{
					if (bd[i-1][j-1].get_team() == 'r')
					{
						if (bd[i-2][j-2].is_empty()&& (i-2 < 8 && i-2 >= 0) && (j-2 < 8 && j-2 >= 0))
						{
							return true;
						}
					}
					if (bd[i-1][j+1].get_team() == 'r')
					{
						if (bd[i-2][j+2].is_empty()&& (i-2 < 8 && i-2 >= 0) && (j+2 < 8 && j+2 >= 0))
						{
							return true;
						}
					}
					if (bd[i+1][j+1].get_team() == 'r')
					{
						if (bd[i+2][j+2].is_empty()&& (i+2 < 8 && i+2 >= 0) && (j-2 < 8 && j-2 >= 0))
						{
							return true;
						}
					}
					if (bd[i+1][j-1].get_team() == 'r')
					{
						if (bd[i+2][j-2].is_empty()&& (i+2 < 8 && i+2 >= 0) && (j-2 < 8 && j-2 >= 0))
						{
							return true;
						}
					}
				}
				
// RED TEAM
				if(bd[i][j].get_team() == 'r' && last_mover() == HUMAN)
				{
					if (bd[i-1][j-1].get_team() == 'b')
					{
						if (bd[i-2][j-2].is_empty()&& (i-2 < 8 && i-2 >= 0) && (j-2 < 8 && j-2 >= 0))
						{
							return true;
						}
					}
					if (bd[i-1][j+1].get_team() == 'b')
					{
						if (bd[i-2][j+2].is_empty() && (i-2 < 8 && i-2 >= 0) && (j+2 < 8 && j+2 >= 0))
						{
							return true;
						}
					}
					if (bd[i+1][j+1].get_team() == 'b')
					{
						if (bd[i+2][j+2].is_empty() && (i+2 < 8 && i+2 >= 0) && (j+2 < 8 && j+2 >= 0))
						{
							return true;
						}
					}
					if (bd[i+1][j-1].get_team() == 'b')
					{
						if (bd[i+2][j-2].is_empty() && (i+2 < 8 && i+2 >= 0) && (j-2 < 8 && j-2 >= 0))
						{
							return true;
						}
					}
				}			
			}
// NOT KING
// BLACK TEAM
				if(bd[i][j].get_team() == 'b' && last_mover() == COMPUTER)
				{
					if (bd[i-1][j-1].get_team() == 'r')
					{
						if (bd[i-2][j-2].is_empty()&& (i-2 < 8 && i-2 >= 0) && (j-2 < 8 && j-2 >= 0))
						{
							return true;
						}
					}
					if (bd[i-1][j+1].get_team() == 'r')
					{
						if (bd[i-2][j+2].is_empty()&& (i-2 < 8 && i-2 >= 0) && (j+2 < 8 && j+2 >= 0))
						{
							return true;
						}
					}
				}
// RED TEAM
				if(bd[i][j].get_team() == 'r' && last_mover() == HUMAN)
				{
					if (bd[i+1][j-1].get_team() == 'b')
					{
						if (bd[i+2][j-2].is_empty()&& (i+2 < 8 && i+2 >= 0) && (j-2 < 8 && j-2 >= 0))
						{
							return true;
						}
					}
					if (bd[i+1][j+1].get_team() == 'b')
					{
						if (bd[i+2][j+2].is_empty()&& (i+2 < 8 && i+2 >= 0) && (j+2 < 8 && j+2 >= 0))
						{
							return true;
						}
					}
				}
		}
	}
	return false;
}


				// CONVERT TO STRING
const string checkers::convert_to_string(const int i,const int j, const int i2, const int j2) const
{
	string tmp;
	char sj, si, sj2, si2;
	
	sj = j + 'a';
	si = i + '0';
	sj2 = j2 + 'a';
	si2 = i2 + '0';
	
	tmp += sj;
	tmp += si;
	tmp += sj2;
	tmp += si2;
	
	return tmp;
}	




				// WINNING
main_savitch_14::game::who checkers::winning() const
{
	int blk_pc = 0, red_pc = 0, total = 0;
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(!bd[i][j].is_empty())
			{
				if(bd[i][j].get_team() == 'r')
					red_pc++;
				if(bd[i][j].get_team() == 'b')
					blk_pc++;
				total++;
			}
		}
	}
	
	if (total == red_pc)
		return COMPUTER;
	if (total == blk_pc)
		return HUMAN;
}
