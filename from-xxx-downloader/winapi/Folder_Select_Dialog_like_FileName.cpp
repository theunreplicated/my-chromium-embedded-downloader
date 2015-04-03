#include "Folder_Select_Dialog_like_FileName.h"
#include "Shlwapi.h"
#include <shlobj.h>
WNDPROC Folder_Select_Dialog_like_FileName::oldProc;
RECT *Folder_Select_Dialog_like_FileName::g_Placement;
TCHAR Folder_Select_Dialog_like_FileName::folder_path[MAX_PATH];
UINT APIENTRY Folder_Select_Dialog_like_FileName::FolderHook(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam){
	if (uMsg == WM_INITDIALOG) {
		HWND hWnd = GetParent(hDlg);
		//SendMessage(hWnd, CDM_HIDECONTROL, cmb6, 0);//geaddet folgend
		SendMessage(hWnd, CDM_HIDECONTROL, IDCANCEL, 0); //bei buttons gits es immer so ids
		//SendMessage(hWnd, CDM_HIDECONTROL, cmb6, 0); 
		/*SendMessage(hWnd, CDM_HIDECONTROL, stc2, 0); // hide "Save as type"
		SendMessage(hWnd, CDM_HIDECONTROL, cmb1, 0); // hide the filter combo box
		SendMessage(hWnd, CDM_SETCONTROLTEXT, IDOK, (LPARAM)_T("Select"));*/
		//SendMessage(hWnd, CDM_SETCONTROLTEXT, stc3, (LPARAM)_T("Folder Name:"));
		// subclass the parent dialog
		oldProc = (WNDPROC)SetWindowLong(hWnd, GWLP_WNDPROC, (LONG)OFNFolderProc);

		if (g_Placement && (g_Placement->top >= g_Placement->bottom)) {
			// the first time center the dialog relative to its parent
			RECT rc1, rc2;
			HWND parent = GetParent(hWnd);
			if (parent) {
				GetClientRect(parent, &rc1);
				MapWindowPoints(parent, NULL, (POINT*)&rc1, 2);
			}
			else
				GetWindowRect(GetDesktopWindow(), &rc1);
			GetWindowRect(hWnd, &rc2);
			int x = rc1.left + ((rc1.right - rc1.left) - (rc2.right - rc2.left)) / 2;
			int y = rc1.top + ((rc1.bottom - rc1.top) - (rc2.bottom - rc2.top)) / 2;
			if (x<rc1.left) x = rc1.left;
			if (y<rc1.top) y = rc1.top;
			g_Placement->left = x;
			g_Placement->top = y;
			g_Placement->right = x + (rc2.right - rc2.left);
			g_Placement->bottom = y + (rc2.bottom - rc2.top);
		}

		return 1;
	}	
	if (uMsg == WM_NOTIFY && ((NMHDR*)lParam)->code == CDN_FILEOK) {
		// reject all files when the OK button is pressed
		// this will stop the dialog from closing
		SetWindowLong(hDlg, DWL_MSGRESULT, TRUE);
		return TRUE;
	}

	return 0;
}




LRESULT CALLBACK Folder_Select_Dialog_like_FileName::OFNFolderProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// if the OK button is pressed
	if (uMsg == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDOK) {

		bool valid = false;

		HWND list = GetDlgItem(GetDlgItem(hWnd, lst2), 1);
		int idx = ListView_GetNextItem(list, -1, LVNI_SELECTED);
		if (GetWindowTextLength(GetDlgItem(hWnd, cmb13))>0) {
			// the file name box is not empty
			// use the default processing, which will open the folder with that name
			CallWindowProc(oldProc, hWnd, uMsg, wParam, lParam);
			// then clear the text
			SetDlgItemText(hWnd, cmb13, TEXT(""));
			return TRUE;
		}
		else if (idx >= 0) {
			// if a folder is selected in the list view, its user data is a PIDL
			// get the full folder name as described here: http://msdn.microsoft.com/msdnmag/issues/03/09/CQA/
			LVITEM item = { LVIF_PARAM, idx, 0 };
			ListView_GetItem(list, &item);

			int len = SendMessage(hWnd, CDM_GETFOLDERIDLIST, 0, NULL);
			if (len>0) {
				LPMALLOC pMalloc;
				SHGetMalloc(&pMalloc);
				LPCITEMIDLIST pidlFolder = (LPCITEMIDLIST)pMalloc->Alloc(len);
				SendMessage(hWnd, CDM_GETFOLDERIDLIST, len, (LPARAM)pidlFolder);

				STRRET str = { STRRET_WSTR };

				IShellFolder *pDesktop, *pFolder;
				SHGetDesktopFolder(&pDesktop);
				if (SUCCEEDED(pDesktop->BindToObject(pidlFolder, NULL, IID_IShellFolder, (void**)&pFolder))) {
					if (FAILED(pFolder->GetDisplayNameOf((LPITEMIDLIST)item.lParam, SHGDN_FORPARSING, &str)))
						str.pOleStr = NULL;
					pFolder->Release();
					pDesktop->Release();
				}
				else {
					if (FAILED(pDesktop->GetDisplayNameOf((LPITEMIDLIST)item.lParam, SHGDN_FORPARSING, &str)))
						str.pOleStr = NULL;
					pDesktop->Release();
				}

				if (str.pOleStr) {
					DWORD attrib = GetFileAttributesW(str.pOleStr);
					if (attrib != INVALID_FILE_ATTRIBUTES && (attrib&FILE_ATTRIBUTE_DIRECTORY)) {
#ifdef _UNICODE
						wcsncpy(folder_path, str.pOleStr, _MAX_PATH);
#else
						WideCharToMultiByte(CP_ACP, 0, str.pOleStr, -1, folder_path, _MAX_PATH, NULL, NULL);
#endif
						folder_path[_MAX_PATH - 1] = 0;
						valid = true;
					}
					pMalloc->Free(str.pOleStr);
				}

				pMalloc->Free((void*)pidlFolder);
				pMalloc->Release();
			}
		}
		else {
			// no item is selected, use the current folder
			TCHAR path[_MAX_PATH];
			SendMessage(hWnd, CDM_GETFOLDERPATH, _MAX_PATH, (LPARAM)path);
			DWORD attrib = GetFileAttributes(path);
			if (attrib != INVALID_FILE_ATTRIBUTES && (attrib&FILE_ATTRIBUTE_DIRECTORY)) {
				//strcpy(g_Path, path);
				//:MessageBoxA(NULL, "ok,ende", "ok", MB_OK);
				strcpy_s(folder_path, _MAX_PATH, path);
				valid = true;
			}
		}
		if (valid) {
			EndDialog(hWnd, IDOK);
			return TRUE;
		}
	}

	if (uMsg == WM_SHOWWINDOW && wParam && g_Placement)
		SetWindowPos(hWnd, NULL, g_Placement->left, g_Placement->top, g_Placement->right - g_Placement->left, g_Placement->bottom - g_Placement->top, SWP_NOZORDER);

	if (uMsg == WM_DESTROY && g_Placement)
		GetWindowRect(hWnd, g_Placement);

	return CallWindowProc(oldProc, hWnd, uMsg, wParam, lParam);
}//@TODO:es gibt noch viel zu tun.V.a. Error-Handling und ne vieeel bessere struktur,weiﬂ z.t. selbst nicht was das macht hier
/*Folder_Select_Dialog_like_FileName::Folder_Select_Dialog_like_FileName(TCHAR*location,TCHAR*title){
	//performOpen(location, title);
	m_location = location;
	m_title = title;
}*/
File_Select_Result Folder_Select_Dialog_like_FileName::performOpen(TCHAR*location, TCHAR*title){
	OPENFILENAME_FOLDER_WRAPPER ofw(title, location, FolderHook);

	File_Select_Result res = OpenFileName<OPENFILENAME_FOLDER_WRAPPER>(TEXT("Ordner\0qqqqqqqqqqqqqqq.qqqqqqqqq\0"), ofw, NULL);
	res.location = folder_path;

	return res;

}
