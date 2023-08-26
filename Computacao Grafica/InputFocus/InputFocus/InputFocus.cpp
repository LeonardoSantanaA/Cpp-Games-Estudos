//Teste de Foco da janela
//Professor: Judson Santiago
#include "DXUT.h"

    //configura e cria a janela
Window* window = new Window();
void Welcome();
void Bye();


int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpcmdline, _In_ int nCmdShow)
{

    window->Mode(WINDOWED);
    window->Size(1024, 600);
    window->Color(0, 122, 204);
    window->Title("Input Focus");
    window->Icon(IDI_ICON);
    window->Cursor(IDC_CURSOR);
    window->Create();

    //Teste de focus
    window->InFocus(Welcome);
    window->LostFocus(Bye);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    delete window;
    return 0;
}

void Welcome() {
    window->Clear();
    window->Print("De volta?", 485, 300, RGB(255, 255, 255));
}
void Bye() {
    window->Clear();
    window->Print("Até Logo!", 485, 300, RGB(255, 255, 255));
}