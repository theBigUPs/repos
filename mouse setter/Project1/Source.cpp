#include <Windows.h>
#include <iostream>

int main()
{
	//implement a counter for multiple presses
	POINT cursor ;

	float mouse_x = 0;
	float mouse_y = 0;

	while (true)
	{
		if (GetKeyState('C') & 0x8000) //places the mouse
		{			
			SetCursorPos(mouse_x, mouse_y);	
		}
		if (GetKeyState('Q') & 0x8000) //sets the mouse
		{
			GetCursorPos(&cursor);
			mouse_x = cursor.x;
			mouse_y = cursor.y;
			std::cout << mouse_x << std::endl ;
			std::cout << mouse_y << std::endl;
		}
		if (GetKeyState('X') & 0x8000) //left clicks
		{
			INPUT    Input = { 0 };
			// left down 
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			::SendInput(1, &Input, sizeof(INPUT));

			// left up
			::ZeroMemory(&Input, sizeof(INPUT));
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			::SendInput(1, &Input, sizeof(INPUT));
			//std::cout << "left clicked";
		}
		if (GetKeyState('L') & 0x8000) //close program
		{
			break;
		}
	
	}
	//getchar();
	return 0;
}