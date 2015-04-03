#ifndef FILE_SELECT_DIALOG_CPP
#define FILE_SELECT_DIALOG_CPP
#include "File_Select_Dialog.h"
template <class T = OPENFILENAME_WRAPPER>
File_Select_Result  File_Select_Dialog::OpenFileName(TCHAR*filter_Text, T &off, HWND parent){
	
	//TCHAR path2[_MAX_PATH];
	//TCHAR fname[_MAX_PATH];
	//fname[0] = 0;
	//TCHAR*filter_Text = TEXT("Folders\0qqqqqqqqqqqqqqq.qqqqqqqqq\0");
//	memset(&of, 0, sizeof(of));
	OPENFILENAME of=off.of;//=off.of;
	//ZeroMemory(&of, sizeof(OPENFILENAME));

	TCHAR fname[_MAX_PATH];
	fname[0] = 0;
	of.lpstrFile = fname;//@TODO:das hier wegmachen können ohne diese komischen Störungen da im Dateiname

	
	//of.lStructSize = sizeof(of);
	of.hwndOwner = parent;
	// weird filter to exclude all files and just keep the folders
	of.lStructSize = sizeof(OPENFILENAME);
	of.lpstrFilter = filter_Text;
	of.nFilterIndex = 1;
	//of.lpstrInitialDir =initial_dir; 
	//of.lpstrFile = fname;
	//of.lpstrTitle = title;
	of.nMaxFile = _MAX_PATH;
	//of.Flags = OFN_ENABLEHOOK | OFN_HIDEREADONLY | OFN_EXPLORER | OFN_NOCHANGEDIR | OFN_ENABLESIZING | OFN_DONTADDTORECENT;
	//of.lpstrDefExt = TEXT("");
	//of.lpfnHook = OFNFolderHook;



	
	return{(GetOpenFileName(&of) != FALSE), of.lpstrFile };
}
#endif