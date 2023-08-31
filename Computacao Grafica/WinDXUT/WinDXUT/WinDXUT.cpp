//Classe de janela inicial
//Professor: Judson Santiago
#include "DXUT.h"

#include <sstream>
using std::stringstream;

//prototipo de funcoes e declaracoes globais
Window* window;
void Welcome();
void Bye();

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpcmdline, _In_ int nCmdShow)
{
    //configura e cria a janela
    window = new Window();
    window->Mode(WINDOWED);
    window->Size(1024, 600);
    window->Color(0, 122, 204);
    window->Title("DXUT Input");
    window->Icon(IDI_ICON);
    window->Cursor(IDC_CURSOR);
    window->Create();
   
    Input* input = new Input();
    MSG msg = { 0 };
    stringstream text;

    int x = window->CenterX();
    int y = window->CenterY();

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (input->KeyPress(VK_ESCAPE))
            window->Close();

        if (input->KeyDown(VK_CONTROL))
            window->Print("CTRL", x - 125, y + 150, RGB(255, 255, 255));
        if (input->KeyDown(VK_RETURN))
            window->Print("Enter", x - 25, y + 150, RGB(255, 255, 255));
        if (input->KeyDown(VK_SPACE))
            window->Print("SPACE", x + 75, y + 150, RGB(255, 255, 255));

        if (input->KeyDown(VK_LEFT))
            window->Print("LEFT", x - 45, y, RGB(255, 255, 255));
        if (input->KeyDown(VK_RIGHT))
            window->Print("RIGHT", x, y, RGB(255, 255, 255));
        if (input->KeyDown(VK_UP))
            window->Print("UP", x - 10, y - 20, RGB(255, 255, 255)); 
        if (input->KeyDown(VK_DOWN))
            window->Print("DOWN", x - 25, y + 20, RGB(255, 255, 255));

        if (input->KeyPress('R')) 
            window->Clear();
        
        //posicao do mouse
        text.str("");   //inicio com texto vazio
        text << input->MouseX() << " x " << input->MouseY();    //coloco esse valor

        //botoes do mouse
        if (input->KeyDown(VK_LBUTTON)) {
            window->Clear();
            window->Print("Botão esq", x - 45, y - 230, RGB(255, 255, 255));
            window->Print(text.str().c_str(), x - 32, y - 210, RGB(255, 255, 255)); //printo o text, que contem a posicao x e y
        }
        if (input->KeyDown(VK_MBUTTON)) {
            window->Clear();
            window->Print("Botão meio", x - 50, y - 230, RGB(255, 255, 255));
            window->Print(text.str().c_str(), x - 32, y - 210, RGB(255, 255, 255));
        }
        if (input->KeyDown(VK_RBUTTON)) {
            window->Clear();
            window->Print("Botão dir", x - 45, y - 230, RGB(255, 255, 255));
            window->Print(text.str().c_str(), x - 32, y - 210, RGB(255, 255, 255));
        }

        //scroll do mouse
        if (short rotation = input->MouseWheel(); rotation != 0) {
            window->Clear();
            window->Print("Rolagem", x - 35, y - 250, RGB(255, 255, 255));
            if (rotation > 0)
                window->Print("Para frente", x - 52, y - 230, RGB(255, 255, 255));
            else
                window->Print("Para tras", x - 40, y - 230, RGB(255, 255, 255));

            text.str("");
            text << rotation;
            window->Print(text.str().c_str(), x - 8, y - 210, RGB(255, 255, 255));
        }

        //inicia entrada de texto
        if (input->KeyPress(VK_INSERT))
            input->Read();

        window->Print(Input::Text(), x - 120, y - 120, RGB(255, 255, 255));
    }

    delete input;
    delete window;
    return 0;
}
