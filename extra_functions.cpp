#include "HEADER.h"

using namespace std;


// *[ LOADING LINE FUNCTION ]* //
void LOADING_LINE(){
	
	int star = 20;
	int space = 65;
	int per = 25;
	
	clearScreen();			// CALLING THE CLEAR SCREEN FUNCTION.
	
    const char* color = ANSI_COLOR_RESET;
	cout<<"\n\n\t\t\t\t\t _____________________________________" ;
	cout<<"\n\t\t\t\t\t|                                     |";
	cout<<color<<ANSI_COLOR_RED<<"\n\t\t\t\t\t|  >>>    LOADING PLEASE WAIT     <<< |"<<ANSI_COLOR_RESET;
	cout<<"\n\t\t\t\t\t|_____________________________________|"<<endl;
	
	cout<<"\t\t "<<setfill('-')<<setw(89)<<"-"<<setfill(' ')<<endl;
	
	for(int i=0 ; i<=3 ; i++ )
	{
		Sleep(400);
		if(i==0){
			color = ANSI_COLOR_RED;
		}
		else if(i==1){
			color = ANSI_COLOR_PURPLE;
		}
		else if(i==2){
			color = ANSI_COLOR_ORANGE;
		}
		else if(i==3){
			color = ANSI_COLOR_GREEN;
		}
		
		cout<<"\t\t | "<<color<<setfill('*')<<setw(star)<<" "<<setfill(' ')<<setw(space)<<" "<<" | "<<per<<" %"<<ANSI_COLOR_RESET<<endl;
		
		star += 20 ;
		space -= 20;
		per += 25 ;
	}
	
	cout<<"\t\t "<<setfill('-')<<setw(89)<<"-"<<setfill(' ');
	
	cout<<"\n\t\t\t\t\t\t ___________________________" ;
	cout<<"\n\t\t\t\t\t\t|                           |";
	cout<<color<<ANSI_COLOR_GREEN<<"\n\t\t\t\t\t\t|  >>>    COMPLETED    <<<  |"<<ANSI_COLOR_RESET;
	cout<<"\n\t\t\t\t\t\t|___________________________|\n"<<endl;
		
return;
}



// *[ CLEAR-SCREEN FUNCTION ]* //
void clearScreen(){

    cout<<CLEAR_SCREEN;  		// USING THE DEFINED FUNCTIONALITY.
}



// *[ BUTTONS-MENU ]* //
void buttons()
{
    cout<<"\n\t\t ______________________________________";
    cout<<"\n\t\t|                                      |";
    cout<<ANSI_COLOR_GREEN<<"\n\t\t| > PRESS THE BUTTON {ONE AT A TIME} < |"<<ANSI_COLOR_RESET;
    cout<<ANSI_COLOR_RED<<"\n\t\t|      __________________________      |";
    cout<<"\n\t\t|     |                          |     |";
    cout<<"\n\t\t|     |    ' 1 '   ' 2 '   ' 3 ' |     |";
    cout<<"\n\t\t|     |                          |     |";
    cout<<"\n\t\t|     |    ' 4 '   ' 5 '   ' 6 ' |     |";
    cout<<"\n\t\t|     |                          |     |";
    cout<<"\n\t\t|     |    ' 7 '   ' 8 '   ' 9 ' |     |";
    cout<<"\n\t\t|     |__________________________|     |";
    cout<<"\n\t\t|                                      |";
    cout<<"\n\t\t|______________________________________|\n\n"<<ANSI_COLOR_RESET;
		
return;
}


void LMS(){

    Sleep(1000);
    cout<<endl<<endl;
    cout<<ANSI_COLOR_PURPLE<<"\t\t___________________________________________________________________"<<endl;
    cout<<"\t\t___________________________________________________________________"<<endl<<ANSI_COLOR_RESET;
    cout<<ANSI_COLOR_BOLD_RED<<"\t\t|||                                                             |||"<<endl;
    cout<<"\t\t|||        LL              M M            M M      SSSSS        |||"<<endl;
    cout<<"\t\t|||        LL              M M MM      MM M M     S     S       |||"<<endl;
    cout<<"\t\t|||        LL              M M   MM  MM   M M     S             |||"<<endl;
    cout<<ANSI_COLOR_BOLD_GREEN<<"\t\t|||        LL              M M     MM     M M      SSSSS        |||"<<endl;
    cout<<"\t\t|||        LL              M M            M M           S       |||"<<endl;
    cout<<"\t\t|||        LL              M M            M M     S     S       |||"<<endl;
    cout<<"\t\t|||        LLLLLLLLLLLL    M M            M M      SSSSS        |||"<<endl;
    cout<<"\t\t|||                                                             |||"<<endl<<ANSI_COLOR_RESET;
    cout<<ANSI_COLOR_PURPLE<<"\t\t __________________________________________________________________"<<endl;
    cout<<"\t\t __________________________________________________________________"<<endl<<ANSI_COLOR_RESET;

    cout<<endl<<endl;

    Sleep(3000);

return;
}