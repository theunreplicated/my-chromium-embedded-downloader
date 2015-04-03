#ifndef INC_FOLDER_SELECT_Like_FiLeNAME_H
#define INC_FOLDER_SELECT_Like_FiLeNAME_H
#include "File_Select_Dialog.h"
//@TODO(bugfix):funktioniert nicht,falls ordner in den standard dokumenten liegt,wahrscheinlich weil besonderheit da lokal und public dokumente0>Bibliotheken gehen nicht
struct OPENFILENAME_FOLDER_WRAPPER{
	OPENFILENAME of;
	OPENFILENAME_FOLDER_WRAPPER(TCHAR*title, TCHAR*initial_dir,LPOFNHOOKPROC OFNFolderHook){
		ZeroMemory(&of, sizeof(OPENFILENAME));
		of.lpstrTitle = title;
		of.lpstrInitialDir = initial_dir;
		of.lpstrDefExt = TEXT("");
		TCHAR fname[_MAX_PATH];
		fname[0] = 0;
		of.lpstrFile = fname;
		of.Flags = OFN_ENABLEHOOK | OFN_HIDEREADONLY | OFN_EXPLORER | OFN_NOCHANGEDIR | OFN_ENABLESIZING | OFN_DONTADDTORECENT;
		of.lpfnHook = OFNFolderHook;
	}

};
class Folder_Select_Dialog_like_FileName:public File_Select_Dialog{
	static WNDPROC oldProc;
	static RECT *g_Placement;
	static TCHAR folder_path[MAX_PATH];
	
public:
	
	//File_Select_Result result;//ist zwar unnötig,aber egal
	//static bool restore_proc;
	//Folder_Select_Dialog_like_FileName(TCHAR*location, TCHAR*title="");//vorsicht,hier,falls irgednwann mal mehrere Threads ist aber glaub nach Winapi ui sowieso nicht mäglich
	static  UINT APIENTRY FolderHook(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK OFNFolderProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	File_Select_Result performOpen(TCHAR*location, TCHAR*title);//@TODO:Das hier ist alles schlechtes Design,der konstruktor dard einfach keine essenzeille funktion übernehmen,sonst komische code(so komisch net) in der do while loop
};//naja jetzt ist es irgendwie unnöig,dafür ne eigene Klasse zu machen
#endif