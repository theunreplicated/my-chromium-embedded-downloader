#inclxxxx-geheimes-Wort!!e "xxxx-geheimes-Wort!!_cef_dl_basic_taskdialog.h"


int xxxx-geheimes-Wort!!_cef_dl_basic_taskdialog(PCWSTR text_maininstruction, PCWSTR text_content, const TASKDIALOG_BUTTON buttons[], UINT num_buttons, PCWSTR expanded_information){
	int nButtonPressed = 0;//http://weblogs.asp.net/kennykerr/Windows-Vista-for-Developers-_1320_-Part-2-_1320_-Task-Dialogs-in-Depth
	//https://msdn.microsoft.com/en-us/library/windows/desktop/bb760544(v=vs.85).aspx
	TASKDIALOGCONFIG config = { 0 };

	config.cbSize = sizeof(config);
	config.hInstance = NULL;
	//config.dwCommonButtons = TDCBF_CANCEL_BUTTON;
	config.pszMainIcon = TD_SHIELD_ICON;
	config.pszMainInstruction = text_maininstruction;
	config.pszContent = text_content;
	config.pButtons = buttons;
	config.cButtons = num_buttons;
	config.dwFlags = TDF_USE_COMMAND_LINKS;
	config.pszExpandedInformation = expanded_information;
	//SendMessage(GetActiveWindow(), TDM_SET_BUTTON_ELEVATION_REQUIRED_STATE, IDCANCEL, true);
	TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL);

	return nButtonPressed;
}