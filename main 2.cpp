#include <iostream>
#include <conio.h>//kbhit() and getch()
#include <unistd.h>//sleep and usleep
#include <windows.h>// I want to hide the cursor and colored something
using namespace std;

// Note:
// kbhit() return true if key is pressed 
//X vertical
//Y horizontal

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int maxX=10, maxY=20;//max map
int map[10][20];//maxX,maxY


int maxL=maxX*maxY;//max length
int sL=1;//Snake Length
bool moveE=true;//move enable

int x=0,y=0;

int tx,ty;

int c = 0;
int g=1;

struct snake{
	int X,Y;
	int cX,cY;
};
snake p[10*20];//maxX*maxY

int randomT(int maxX,int maxY){
	tx= rand() % maxX;
	ty= rand() % maxY;  
	if(tx>=maxX-1){
		tx=maxX-5;
	}
	else if(tx<=0){
		tx=5;
	}
	
	if(ty>=maxY-1){
		ty=maxY-5;
	}
	else if(ty<=0){
		ty=5;
	}
}

void setTextColor(int k){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, k);
}

//windows.h
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void Input(){
		// Checking for input
        c = 0;
		if(kbhit()){
		// Check arrow key 
        switch((c=getch())) {
        case KEY_UP:
            c='w';
            break;
        case KEY_DOWN:
            c='s';
            break;
        case KEY_LEFT:
            c='a';
            break;
        case KEY_RIGHT:
            c='d';
            break;
        default:
            //c='0';
            break;
        }
	}
		else{
			c='0';
		}
		//
}

void Setup(){
	g=1;
	
	maxL++;
	sL++;
	
	for(int i=0;i<maxX;i++){
		for(int j=0;j<maxY;j++){
			    map[i][j]=0;
		}
	}
		
	for(int i=0;i<maxL;i++){	
			    p[i].X=0;
			       p[i].Y=0;
			          p[i].cX=0;
			             p[i].cY=0;
	}
		
	p[0].X=5;
	p[0].Y=5;
	
	for(int i=1;i<maxL;i++){
		p[i].X=p[0].X;
		p[i].Y=p[0].Y-i;
	}
	y=1;
	
	randomT(maxX,maxY); 
}

Draw(){
	ShowConsoleCursor(false);
	system("cls");
	for(int i=0;i<maxX;i++){
			for(int j=0;j<maxY;j++){
				if(map[i][j]==0)
				cout<<" ";
				else if(map[i][j]==1){
					int color = rand()%15+1;
			    	setTextColor(color);//10
					cout<<"o";
					setTextColor(15);
				}
			    else if(map[i][j]==2){
			    	int color =15;// rand()%15+1;
			    	setTextColor(color);//12
					char a=1;
					cout<<a;
					setTextColor(15);
				}
				else if(map[i][j]==3){
					int color = rand()%15+1;
					setTextColor(color);//14
					char a=rand()%5+1;
					cout<<a;
					setTextColor(15);
				}
				else if(map[i][j]==5){
				//	setTextColor(9);
					cout<<".";
				//	setTextColor(15);
				}
				cout<<" ";
			}
			cout<<endl;
		}
		
		cout<<"Score: "<<sL-2<<endl;
}

Logic(){
		char input=(char)c;
		
		if(c=='w'){
			if(x!=1)
			x=-1; y=0;
		}
		if(c=='s'){
			if(x!=-1)
			x=1; y=0;
		}
		
		if(c=='d'){
			x=0;
			if(y!=-1)
			y=1;
		}
		if(c=='a'){
			x=0;
			if(y!=1)
			y=-1;
		}
		
		moveE=!moveE;
		
		if(moveE){
		p[0].X+=x;
		p[0].Y+=y;
		}
	
		
		//Snake bite itself
		for(int i=1;i<sL-1;i++){
			if(p[0].X==p[i].X && p[0].Y==p[i].Y){
				if(moveE)
				g=0;
			}
		}
		//check if player go outside of map
		if(p[0].X>=maxX-1||p[0].X<=0||p[0].Y>=maxY-1||p[0].Y<=0) g=0;
		
		p[1].cX=p[0].X;
		p[1].cY=p[0].Y;
			
		if(moveE){
		for(int i=1;i<maxL;i++){
			p[i+1].cX=p[i].X;
		 	p[i+1].cY=p[i].Y;	
			p[i].X=p[i].cX;
			p[i].Y=p[i].cY;
		}
		}
		
		for(int i=0;i<maxX;i++){
			for(int j=0;j<maxY;j++){
				if(j!=0&&j!=maxY-1){
					if(i!=0&& i!=maxX-1)
			    	map[i][j]=0;
			    	else
			    	map[i][j]=5;
				}
			    else
			    	map[i][j]=5;
			}
		}
	
		for(int i=0;i<sL;i++){
				map[p[i].X][p[i].Y]=1;
		}
			
		map[p[0].X][p[0].Y]=2;
		
		map[tx][ty]=3;
		
		if(tx==p[0].X&&ty==p[0].Y){
			randomT(maxX,maxY); 
			sL++;
			cout << '\a';
		}
}

void stop(){
	Beep(523.2511,500);  // 523.2511 hertz (C5) for 500 milliseconds
	sL=1;
	x=0;
	y=0;
	system("pause");
}

int main()
{
	again:
	Setup();
    while(g==1)
    {
    	Input();
		Logic();
		Draw(); 	
		usleep(1);
	}
	stop();
	goto again;
    return 0;
}	

