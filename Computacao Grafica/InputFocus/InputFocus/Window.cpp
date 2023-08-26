#include "Window.h"

void (*Window::inFocus)() = nullptr; //nenhuma acao ao ganhar foco
void (*Window::lostFocus)() = nullptr; //nenhuma acao ao perder foco

Window::Window() {
    windowId = 0;	//id nulo porque a janela ainda nao existe
    windowWidth = GetSystemMetrics(SM_CXSCREEN); //a janela ocupa toda a tela
    windowHeight = GetSystemMetrics(SM_CYSCREEN); //a janela ocupa toda a tela
    windowIcon = LoadIcon(NULL, IDI_APPLICATION); //icone padrao de uma app
    windowCursor = LoadCursor(NULL, IDC_ARROW); //cursor padrao de uma app
    windowColor = RGB(0, 0, 0); //cor de fundo padrao, preta
    windowTitle = string("Windows App"); // titulo padrao
    windowStyle = WS_POPUP | WS_VISIBLE; // estilo para tela cheia
    windowMode = FULLSCREEN; //modo padrao, tela cheia
    windowPosX = 0; //posicao inicial do x
    windowPosY = 0; //posicao inicial do y
    windowCenterX = windowWidth / 2; //centro da janela x
    windowCenterY = windowHeight / 2; //centro da janela y
}

void Window::Mode(int mode) {
    windowMode = mode;

    if (mode == WINDOWED) {
        windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE;
    }
    else {
        windowStyle = WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE;
    }
}

void Window::Size(int width, int height) {
    windowWidth = width;
    windowHeight = height;

    windowCenterX = windowWidth / 2;
    windowCenterY = windowHeight / 2;

    windowPosX = (GetSystemMetrics(SM_CXSCREEN) / 2) - (windowWidth / 2);
    windowPosY = (GetSystemMetrics(SM_CYSCREEN / 2) - windowHeight / 2);
}

void Window::Print(string text, int x, int y, COLORREF color) {
    //essa funcao usa a GDI do windows (lenta) e deve ser usada apenas para depuracao

    HDC xdc = GetDC(windowId); //pega o contexto do dispositivo grafico
    SetTextColor(xdc, color); //define a cor do texto
    SetBkMode(xdc, TRANSPARENT); //define o fundo do texto como transparente
    TextOut(xdc, x, y, text.c_str(), (int)text.size()); //mostra o texto
    ReleaseDC(windowId, xdc); //libera o contexto do dispositivo
}

void Window::Clear()
{
    HDC hdc = GetDC(windowId);    // captura contexto do dispositivo

    // pega tamanho da área cliente
    RECT rect;
    GetClientRect(windowId, &rect);

    FillRect(hdc, &rect, CreateSolidBrush(Color()));  // limpa a área cliente
    ReleaseDC(windowId, hdc); // libera o contexto do dispositivo
}

bool Window::Create() {
    HINSTANCE appId = GetModuleHandle(NULL); //identificador da aplicacao
    // atualiza posicao da janela

    WNDCLASSEX wndClass;
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = Window::WinProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = appId;
    wndClass.hIcon = windowIcon;
    wndClass.hCursor = windowCursor;
    wndClass.hbrBackground = (HBRUSH)CreateSolidBrush(windowColor);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = "AppWindow";
    wndClass.hIconSm = windowIcon;

    if (!RegisterClassEx(&wndClass)) {
        MessageBox(NULL, "Erro na criacao da janela!", "Aplicação", MB_ICONERROR);
        return 0;
    }

    windowId = CreateWindowEx(
        NULL,   //estilos extras
        "AppWindow", //nome da classe da janela
        windowTitle.c_str(),    //titulo da janela
        windowStyle,
        windowPosX, windowPosY,
        windowWidth, windowHeight,
        NULL,
        NULL,
        appId,
        NULL);

    //ao usar o modo em janela é preciso levar em conta que as barras e bordas ocupam espaço na janela
    //o codigo abaixo ajusta o tamanho da janela de forma que a area cliente fique com o tamanho que nos passarmos

    if (windowMode == WINDOWED) {
        RECT winRect = { 0, 0, windowWidth, windowHeight }; // Retangulo com o tamanho da area cliente desejada

        // funcao AdjustWindowRectEx permite ajustar o tamanho da area cliente
        AdjustWindowRectEx(&winRect, // endereco de um RECT
            GetWindowStyle(windowId),    // estilo da janela
            GetMenu(windowId) != NULL,   // indica se tem menu
            GetWindowExStyle(windowId)); // estilos extra

        int posX = GetSystemMetrics(SM_CXSCREEN) / 2 - (winRect.right - winRect.left) / 2;
        int posY = GetSystemMetrics(SM_CYSCREEN) / 2 - (winRect.bottom - winRect.top) / 2;

        MoveWindow(windowId, posX, posY, winRect.right - winRect.left, winRect.bottom - winRect.top, true); // move e atualiza a janela pra um novo tamanho
    }
    //retorna estado da inicializacao (bem sucedida ou nao)
    return (windowId ? true : false);
}

LRESULT CALLBACK Window::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    //perdeu o foco
    case WM_KILLFOCUS:
        if (lostFocus) //se o ponteiro for nulo, ele é false
            lostFocus();
        return 0;
     //recebeu o foco
    case WM_SETFOCUS:
        if (inFocus)
            inFocus();
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
