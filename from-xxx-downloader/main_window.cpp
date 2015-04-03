#inclxxxx-geheimes-Wort!!e "main_window.h"
#inclxxxx-geheimes-Wort!!e <stdexcept>
namespace Windows{
	MainApp*ma;
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CREATE:
		{
		/*	CefWindowInfo window_info;//window info wichtig!
#ifndef MODE_USE_OWN_WINDOW

			window_info.SetAsPopup(NULL, "xxxx-geheimes-Wort!! Downloader");
#else
			Windows::ma = this;
			HWND main_window = Windows::create_window({ 1024, 768 });
			window_info.SetAsChild(main_window, Windows::WindowRect{ 720, 500 });
#endif
			CefRefPtr<AppHandler> handler(new AppHandler(m_folder_where_to_put_downloads));//fuck,so eine scheisse
			//downloader_browser = new DownLoadHandler_Browser();


			cef_string_t encoding_settings;
			encoding_settings.str = L"utf-8";
			encoding_settings.length = 5;
			encoding_settings.dtor = NULL;
			CefBrowserSettings browser_settings;
			browser_settings.default_encoding = encoding_settings;//ansonsten wird beim eigenen resourcehandler bei google auf gut glae/ck angezeigt anstatt dem ü
			std::string url;







			// Check if a "--url=" value was provided via the command-line. If so, use
			// that instead of the default URL.
			//CefRefPtr<CefCommandLine> command_line =
			//	CefCommandLine::GetGlobalCommandLine();
			//url = command_line->GetSwitchValue("url");
			//if (url.empty())
			url = "http://www.xxxx-geheimes-Wort!!.com/courses";



			//CefBrowserHost::CreateBrowser(window_info, handler.get(), url,
			//browser_settings, NULL);
			*/

		}
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return 0;
	}
	HWND create_window(WindowRect rect){

		TCHAR classname[] = "thisclass--xxxx-geheimes-Wort!!-dl",windowtitle[]="xxxx-geheimes-Wort!!-download";
		WNDCLASSA wc = { 0 };
		HINSTANCE hInstance = NULL;
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		//aus meinem alten Info_projekt
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);//einfach IDC_* ändern
		//	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);//win-api.de
		wc.lpszMenuName = NULL;
		wc.lpszClassName = classname;

		(!RegisterClassA(&wc) ? throw std::runtime_error("registering window class failed") : true);

		
		return ::CreateWindow(
			classname,
			windowtitle,
			/*WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE |
			ES_AUTOVSCROLL*/WS_OVERLAPPEDWINDOW|WS_VISIBLE,
			rect.x, rect.y, rect.width, rect.height,
			NULL,
			NULL,
			/*((LPCREATESTRUCT)lParam)->*/hInstance,
			NULL);
		
	}


}