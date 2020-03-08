#include <iostream>
#include <conio.h>//kbhit() and getch() and for color
#include <unistd.h>//sleep and usleep
using namespace std;

// Note:
// kbhit() return true if key is pressed 

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int main()
{
    int c = 0;
    while(1)
    {
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
            c='0';
            break;
        }
	}
		else{
			c='0';
		}
	
		// Game Update
		usleep(100000);
		char input=(char)c;
		cout<<input<<endl;
	
		//Per frame  
		system("cls");
	}
    return 0;
}	
