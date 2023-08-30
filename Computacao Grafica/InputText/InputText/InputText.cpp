//Inicio de nova classe input, para interaçao
//Professor: Judson Santiago
#include "DXUT.h"

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpcmdline, _In_ int nCmdShow)
{
    //configura e cria a janela
    Window* window = new Window();

    window->Mode(WINDOWED);
    window->Size(1024, 600);
    window->Color(0, 122, 204);
    window->Title("Input Text");
    window->Icon(IDI_ICON);
    window->Cursor(IDC_CURSOR);
    window->Create();

    //leitura da entrada
    Input* input = new Input();

    MSG msg = { 0 };

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (input->KeyPress(VK_ESCAPE))
            window->Close();

        if (input->KeyPress(VK_INSERT))
            input->Read();

        window->Print(Input::Text(), 390, 300, RGB(255, 255, 255));
    }

    delete input;
    delete window;
    return 0;
}

