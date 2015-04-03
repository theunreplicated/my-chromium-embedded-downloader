#ifndef INC_MAIN_WINDOW_H
#define INC_MAIN_WINDOW_H
#inclxxxx-geheimes-Wort!!e <Windows.h>
#inclxxxx-geheimes-Wort!!e <algorithm>
#inclxxxx-geheimes-Wort!!e "MainApp.h"
namespace Windows{
	extern MainApp*ma;
	struct WindowRect{
		//	WindowRect() :width(0){};//struct ohne KonstruktOOOOR leider nur begrenzt einsetzbar,aber mit {} init werden alle anderen Values auf default-null gesetzt
		int width, height, x, y;
		void fromRect(RECT rect){//mit dem from* ist eigentlich schlechter Stil
			width = std::abs(rect.right - rect.left);
			height = std::abs(rect.bottom - rect.top);
			x = rect.left; y = rect.top;
		};
		operator RECT(){
			RECT rect;
			rect.left = x;
			rect.top = y;
			rect.right = width + rect.left;//@TODO:wenn oben abs,dann unten signum-funktion
			rect.bottom = height + rect.top;
			return rect;
		};
	};//QUelle:altes info-projekt
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HWND create_window(WindowRect rect);
	

};

#endif