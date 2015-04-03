#define NOMINMAX
#inclxxxx-geheimes-Wort!!e <Windows.h>
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/cef_sandbox_win.h"
#inclxxxx-geheimes-Wort!!e "MainApp.h"
#inclxxxx-geheimes-Wort!!e <fstream>
#inclxxxx-geheimes-Wort!!e <sstream>
#inclxxxx-geheimes-Wort!!e "winapi\Folder_Select_Dialog_like_FileName.h"
#inclxxxx-geheimes-Wort!!e "config_file_io.h"
#inclxxxx-geheimes-Wort!!e "path_helper.h"
//using std::ios_base;
//using std::ios;
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	bool one_time_do = false;
	
	std::string folder_to_put_downloads;
	if (!one_time_do){
		

		one_time_do = true;

		std::string path_config_file = "xxxx-geheimes-Wort!!_dl_config_file.conf3000.txt";
		//std::fstream config_file_check(path+path_config_file, ios_base::binary | ios_base::in);
	//http://stackoverflow.com/questions/875249/how-to-get-current-directory
		
		Config_File_IO cfio(get_current_application_path()+"\\"+path_config_file);
		auto check = cfio.check_if_exists();
		if (check.result_operation){//                      nur 3000 warum nicht mehr
			//na drauslesen,was denn sonst,was will er denn sonst mit machen??überleg.hmm.kein Rätsel.kein Quiz
			//std::stringstream cff_StreaM; cff_StreaM << config_file_check.rdbuf();
			//folder_to_put_downloads = cff_StreaM.str(); config_file_check.close();
			folder_to_put_downloads = check.contents_get();
		}
		else{//select dir.the choice(stage)is yours /up to you
			//config_file_check.close();
			//std::ofstream of(path + path_config_file, ios::binary | ios::out);
			Folder_Select_Dialog_like_FileName*fsdlf = new Folder_Select_Dialog_like_FileName();
			File_Select_Result fsr;
			do{
				fsr = fsdlf->performOpen("C:\\", "Ort wo die Downloads zu speichern sind");
			} while (fsr.status != true);
			folder_to_put_downloads = std::string(fsr.location);
			//of << fsr.location;
			//of.close();
			check.put_contents(folder_to_put_downloads);
	
		}
	}
	//CefScopedSandboxInfo scoped_sandbox;
	//void*sandbox_info = scoped_sandbox.sandbox_info();//sandbox hier aktiviert,muss man aber net
	void*sandbox_info = NULL;//sandbox deaktiviert,da bei allen winapi/file calls permission denied kommt
	CefMainArgs main_args(hInstance);

	CefRefPtr<MainApp> app(new MainApp(folder_to_put_downloads));
	int exit_code = CefExecuteProcess(main_args, app.get(), sandbox_info);
	if (exit_code >= 0) {
		return exit_code;
	}


	CefSettings settings;//wird fürs initialize gebraucht
	settings.no_sandbox = true;
	CefInitialize(main_args, settings, app.get(), sandbox_info);
	CefRunMessageLoop();
	CefShutdown();
	return 0;

}