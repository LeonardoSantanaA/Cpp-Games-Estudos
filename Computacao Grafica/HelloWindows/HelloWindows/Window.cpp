//Esqueleto Básico de criacao de uma janela no Windows utilizando a API Win32.
//Professor: Judson Santiago

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// prototipo do window procedure
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

// principal
int APIENTRY WinMain(_In_ HINSTANCE hInstance, 
                     _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpcmdline, _In_ int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    // - Definir uma Window Class Name
    wndclass.style = CS_HREDRAW | CS_VREDRAW; // redefinir janela quando o usuario mexer no tamanho dela
    wndclass.lpfnWndProc = WinProc; // Nome da funcao que vai tratar as mensagens
    wndclass.cbClsExtra = 0; // bytes extra
    wndclass.cbWndExtra = 0; // bytes extra
    wndclass.hInstance = hInstance; // identificado da aplicacao
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // carregar o icone
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);  // carregar o cursor  
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   // cor de fundo
    wndclass.lpszMenuName = NULL;   // nao tenho menu nessa janela
    wndclass.lpszClassName = "AppWindow";   // nome da classe que estou criando

    // - Registrar a Window Class Name
    if (!RegisterClass(&wndclass)) { //verifica se conseguiu registrar a classe
        MessageBox(NULL, "Erro na criação da janela!", "Aplicação", MB_ICONERROR);
        return 0;
    }
    
    // - Criar uma janela baseada na Widow Class Name
    hwnd = CreateWindow(
        "AppWindow",    // nome da classe da janela
        "Aplicação",    // titulo da janela
        WS_OVERLAPPEDWINDOW | 
        WS_VISIBLE,     // estilo da janela
        CW_USEDEFAULT,  // posicao x inicial
        CW_USEDEFAULT,  // posicao y inicial
        CW_USEDEFAULT,  // largura inicial
        CW_USEDEFAULT,  // altura inicial
        NULL,           // identificador da janela pai
        NULL,           // identificador do menu
        hInstance,      //identificador da aplicacao
        NULL);          //parametros da criacao

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// - Definindo Window Procedure
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        //janela foi fechada
    case WM_DESTROY:
        //envia uma mensagem WM_QUIT para encerrar a aplicacao
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}
