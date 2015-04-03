#ifndef FILE_SELECT_DiALOG_H
#define FILE_SELECT_DiALOG_H
#include <Windows.h>
struct OPENFILENAME_DEFAULT_WRAPPER{
	OPENFILENAME of;
	OPENFILENAME_DEFAULT_WRAPPER(TCHAR*title){
		ZeroMemory(&of, sizeof(OPENFILENAME));
		of.lpstrTitle = title;
	
	}

};
struct File_Select_Result{
	bool status; TCHAR*location;
};
class File_Select_Dialog{
public:
	template <class T = OPENFILENAME_DEFAULT_WRAPPER>
	File_Select_Result OpenFileName(TCHAR*filter_Text, T& off, HWND parent);

};
#include "File_Select_Dialog.cpp"
#endif