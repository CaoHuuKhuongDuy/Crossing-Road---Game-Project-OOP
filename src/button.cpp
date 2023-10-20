#include "button.h"

void GotoXY(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void SET_COLOR(int color)
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

Button::Button() {}

Button::Button(std::string text_, COORD pos_, int colorNormal_, int colorClicked_) 
    : text( text_ + ".txt"), pos(pos_), colorButton(colorNormal_), colorNormal(colorNormal_), colorClicked(colorClicked_), highlighted(false){};


void Button::toggleHighlight() {
    highlighted = !highlighted;
}

void Button::changeText() {
    colorButton = (highlighted ? colorClicked : colorNormal);

}

void Button::draw() {
    changeText();
    fstream file;
	file.open(text,ios::in);
	string t;
	int j = 0;
	while(!file.eof()){
		getline(file,t);
		char* arr = new char [t.length()+1];
		strcpy(arr, t.c_str());
		    for (int i = 0; i < t.length(); i++) 
    { 
    	SET_COLOR(colorButton);
    	GotoXY(pos.X+i,pos.Y+j);
        std::cout << arr[i]; 
    }  
    j++;
    cout << endl ;
    delete[] arr;
	}



}
