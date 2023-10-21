#include "screen.h"
#include "button.h"
#include <vector>
#include <conio.h>
#include "console.h"

void SET_COLOR_(int color)
{
	WORD wColor;
      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
	}
}

signed main() {
    stValue::appConsole.init();
    stValue::importImage.init(&stValue::appConsole);
    char keyPress = 0;
    int debug = 0;
    appConsole.setFullscreenBackgroundColor(BG_BLUE);
    while (true) {
        menuScreen* menu = new menuScreen();    
        menu->draw();
    	
    }
   int x;
   cin >> x;
   return 0;
}
