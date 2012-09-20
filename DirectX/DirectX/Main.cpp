#define WIN32_LEARN_MEAN //Ei k‰yt‰ "turhia" windows s‰li‰

#include <Windows.h>

LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)

//hInstance = nykynen instanssi, prevInstance = edellinen instanssi
//w = wide unicode characters
int WINAPI xWinMain( HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow) {

	//K‰‰nt‰j‰ ei huomio seuraavia parametrej‰
	UNREFERENCED_PARAMETER( prevInstance);
	UNREFERENCED_PARAMETER(cmdLine);

	

	//Windows class
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof( WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = ( HBRUSH ) (COLOR_WINDOW +1 );
	wndClass.lpszMenuName = NULL;
	//Max char 256
	wndClass.lpszClassName = "DX11Class";

	if(!RegisterClassEx( &wndClass)){
		return -1;
	}

	//M‰‰ritell‰‰n ikkunan koko
	RECT rc = {0, 0, 860, 640};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hwnd = CreateWindowA( "DX11 Class", "Empty", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);

	if(!hwnd){
		return -1;
	}

	//N‰ytet‰‰n luotu ikkuna
	ShowWindow( hwnd, cmdShow);

	MSG msg = {0};

	while(msg.message != WM_QUIT){
		if( PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//TODO Update
			//TODO Render
		}
	}

	//Shutdow

	return static_cast<int>( msg.wParam );
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT paintStruct;
	HDC hDC;
	switch(message){
		case WM_PAINT:
			hDC = BeginPaint( hwnd, &paintStruct);
			EndPaint(hwnd, &paintStruct);
			break;
		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}
}