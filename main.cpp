#include <iostream>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

using namespace std;
void swap(int &a, int &b){
	int t=a;
	a = b;
	b = t;
}


WINDOW *create_newwin(int height,int width,int starty,int startx);
void destory_win(WINDOW *local_win);

int game_win_height=35;
int game_win_width=45;

int hint_win_height,hint_win_width;
WINDOW * game_win, *hint_win;
int key;

class Piece
{
public:
	int shape; 
	int next_shape;
	int head_x;
	int head_y;

	int box_shape[4][4];
	int box_map[34][44];

	

public:
	void initial();
	void set_shape(int shape);
	void move();
	void rotate();
	bool judge_right();
	bool judge_left();
	bool stop();
	void set_stop();
	
};




int main()
{

	initscr();
	//raw();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr,TRUE);

	refresh();

	
	hint_win_height=10;
	hint_win_width=20;


	// starty=(LINES - height)/2;
	// startx=(COLS - width)/2;

	game_win = create_newwin(game_win_height, game_win_width, 0,0);
	wborder(game_win, '*', '*', '*', '*', '*', '*', '*', '*');
	wrefresh(game_win);

	hint_win = create_newwin(hint_win_height, hint_win_width, 5, game_win_width+10);

	Piece* pp = new Piece;
	pp->initial();


	while(1)
	{
		srand((unsigned)time(0));
		pp->next_shape=rand()%7;
		pp->move();

	}

	endwin();
	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win,0,0);
	wrefresh(local_win);
	return local_win;
}

void destory_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}


void Piece::initial()
{
	this->head_x=game_win_width/2;
	this->head_y=1;
	this->box_map[34][44]=0;

	srand((unsigned)time(0));
	shape=rand()%7;
	set_shape(shape);

}

void Piece::set_shape(int shape)
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			box_shape[i][j]=0;
	switch(shape)
	{
		case 0:		// T
			this->box_shape[0][0]=1;
			this->box_shape[0][1]=1;
			this->box_shape[0][2]=1;
			this->box_shape[1][1]=1;
			break;
		case 1:		// S
			this->box_shape[0][1]=1;
			this->box_shape[0][2]=1;
			this->box_shape[1][0]=1;
			this->box_shape[1][1]=1;
			break;
		case 2:		// Z	
			this->box_shape[0][0]=1;
			this->box_shape[0][1]=1;
			this->box_shape[1][1]=1;
			this->box_shape[1][2]=1;
			break;
		case 3:		// J
			this->box_shape[0][1]=1;
			this->box_shape[1][1]=1;
			this->box_shape[2][0]=1;
			this->box_shape[2][1]=1;
			break;

		case 4:		// L
			this->box_shape[0][0]=1;
			this->box_shape[1][0]=1;
			this->box_shape[2][0]=1;
			this->box_shape[2][1]=1;
			break;

		case 5:		// I
			this->box_shape[0][0]=1;
			this->box_shape[1][0]=1;
			this->box_shape[2][0]=1;
			this->box_shape[3][0]=1;
			break;

		case 6:	// O
			this->box_shape[0][0]=1;
			this->box_shape[0][1]=1;
			this->box_shape[1][0]=1;
			this->box_shape[1][1]=1;
			break;
	}

}
void Piece::rotate()
{

	for(int i=0; i<4;i++)
		for(int j=0;j<4;j++){
			if(this->box_shape[i][j]==1){
				mvwaddch(game_win,head_y+i,head_x+j,' ');
				wrefresh(game_win);
			}
		}

	for(int i=0;i<4;i++)
		for(int j=0;j<4-i;j++)
			swap(this->box_shape[i][j],this->box_shape[4-1-j][4-1-i]);
	for(int i=0;i<4/2;i++)
		for(int j=0;j<4;j++)
			swap(this->box_shape[i][j],this->box_shape[4-1-i][j]);

	/*ru guo kao qian ze ni shi  zhen xuan zhuan*/

	for(int i=0; i<4;i++)
		for(int j=0;j<4;j++){
			if(this->box_shape[i][j]==1){
				mvwaddch(game_win,head_y+i,head_x+j,'#');
				wrefresh(game_win);
			}
		}

}

void Piece::move(){
	 fd_set set;
	 FD_ZERO(&set);
	 FD_SET(0, &set);
	      
	 struct timeval timeout;
	 timeout.tv_sec = 0;
	 timeout.tv_usec= 500000;
	      
  	if (select(1, &set, NULL, NULL, &timeout) == 0 && !stop()){
		for(int i=3; i>=0;i--)
			for(int j=0;j<4;j++){
				if(this->box_shape[i][j]==1){
					mvwaddch(game_win,head_y+i,head_x+j,' ');
					mvwaddch(game_win,head_y+i+1,head_x+j,'#');

				}
			}
		wrefresh(game_win);
		this->head_y++;
  	}
	      
	if (FD_ISSET(0, &set)) {
	        while ((key = getch()) == -1) ;

		if(key==KEY_LEFT){
			if(judge_left() && !stop()){
				for(int i=0; i<4;i++)
					for(int j=0;j<4;j++){
						if(this->box_shape[i][j]==1){
							mvwaddch(game_win,head_y+i,head_x+j,' ');
							mvwaddch(game_win,head_y+i,head_x+j-1,'#');

						}
					}

				wrefresh(game_win);
				this->head_x--;
			}
		}

		if(key==KEY_RIGHT){
			if(judge_right() && !stop()){
				for(int i=0; i<4;i++)
					for(int j=3;j>=0;j--){
						if(this->box_shape[i][j]==1){
							mvwaddch(game_win,head_y+i,head_x+j,' ');
							mvwaddch(game_win,head_y+i,head_x+j+1,'#');

						}
					}

				wrefresh(game_win);
				this->head_x++;
			}
		}

		if(key==KEY_DOWN){
			if(!stop()){
				usleep(100);
				for(int i=3; i>=0;i--)
					for(int j=0;j<4;j++){
						if(this->box_shape[i][j]==1){
							mvwaddch(game_win,head_y+i,head_x+j,' ');
							mvwaddch(game_win,head_y+i+1,head_x+j,'#');

						}
					}
				wrefresh(game_win);
				this->head_y++;
			}
		}

		if(key==KEY_UP)
		{
			// for(int i=0;i<4;i++)
			// 	for(int j=0;j<4-i;j++)
			// 		swap(this->box_shape[i][j],this->box_shape[4-1-j][4-1-i]);
			// for(int i=0;i<4/2;i++)
			// 	for(int j=0;j<4;j++)
			// 		swap(this->box_shape[i][j],this->box_shape[4-1-i][j]);
			rotate();
		}
	}
}

	/* detect the wall */

bool Piece::judge_right(){
	//the right wall
	for(int j=3;j>=0;j--)
		for(int i=0;i<4;i++)
			if(this->box_shape[i][j]==1)
				if((head_x+j+2)==game_win_width || box_map[head_y+i][head_x+j+1]==1)
					return false;
				else
					return true;
}

bool Piece::judge_left(){
	//the left wall
	for(int j=0;j<4;j++)
		for(int i=0;i<4;i++)
			if(this->box_shape[i][j]==1)
				if((head_x+j-1)==0 || box_map[head_y+i][head_x+j-1]==1)
					return false;
				else
					return true;
}

bool Piece::stop(){

	//detect the bottom box
	for(int i=3; i>=0;i--)
		for(int j=0;j<4;j++){
			if(this->box_shape[i][j]==1)
				if((head_y+i+2)==game_win_height){
					set_stop();
					return true;
				}
		}
	for(int i=3; i>=0;i--)
		for(int j=0;j<4;j++){
			if(this->box_shape[i][j]==1)
				if(box_map[head_y+i+1][head_x+j]==1){
					set_stop();
					return true;
				}
		}

	return false;
}

void Piece::set_stop(){

	for(int i=0; i<4;i++)
		for(int j=0;j<4;j++){
			if(this->box_shape[i][j]==1)
				this->box_map[head_y+i][head_x+j]=1;
		}
	head_x=game_win_width/2;
	head_y=1;
	shape=next_shape;
	set_shape(shape);

}