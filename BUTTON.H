#ifndef __BUTTON_H
#define __BUTTON_H
	
#ifndef __GUI_H
#include "gui.h"
#endif  // __GUI_H
#include "global.h"

class Button
{
  private:
	int Left,Top,Width,Height,ID;
	char Caption[50];
	BUTTON_STATUS btnStatus;
	bool State;

  public:
	Button(int left=0, int top=0, int width=0, int height=0, char caption[]=" ", int Id=0);
	void Highlight(char a);
	void Draw(int color);
	void EnableClickHandler();		
};	   
#endif // __BUTTON_H  			


















	

 
