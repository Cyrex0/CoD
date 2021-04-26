#pragma comment (lib, "dwmapi.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "winmm.lib")

#define IMGUI_IMPL_WIN32_DISABLE_GAMEPAD

#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include <dwmapi.h>
#include <ctime>
#include <string>
#include <sstream>
#include <algorithm>
#include "maintwo.h"
#include "Maintwo.cpp"

static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND hwnd;

MARGINS gMargin = { 0, 0, 600, 600 };
MARGINS zero = { -1, -1, -1, -1 };

typedef struct _ScreenInfo {
    int width;
    int height;
} ScreenInfo;

ScreenInfo GetScreenInfo()
{
    ScreenInfo sci = { 0 };
    sci.width = GetSystemMetrics(SM_CXSCREEN);
    sci.height = GetSystemMetrics(SM_CYSCREEN);
    return sci;
}

void ClickThough(bool click)
{
    if (click)
    {
        SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);
    }
    else
    {
        SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_LAYERED);
    }
}
static DWORD LastFrameTime = 0;
void LimitFPS(int targetfps)
{
    DWORD currentTime = timeGetTime();
    if ((currentTime - LastFrameTime) < (1000 / targetfps))
    {
        Sleep(currentTime - LastFrameTime);
    }
    LastFrameTime = currentTime;
}
static bool ShowMenu = true;
static int LastTick = 0;

void Overlay::Loop(void* blank)
{
    // 
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("b"), NULL };
    ::RegisterClassEx(&wc);
    hwnd = ::CreateWindow(wc.lpszClassName, _T(""), WS_EX_TOPMOST | WS_POPUP, 0, 0, GetScreenInfo().width, GetScreenInfo().height, NULL, NULL, wc.hInstance, NULL);
    ClickThough(true);
    SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
    gMargin = { 0, 0, GetScreenInfo().width, GetScreenInfo().height };
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.IniFilename = NULL;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Tahoma.ttf", 18.0f);


    //g_Vars->width = GetScreenInfo().width;
    //g_Vars->height = GetScreenInfo().height;

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }
        ::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        LimitFPS(90);
        if (GetKeyState(VK_INSERT) & 0x8000)
        {
            if ((GetTickCount() - LastTick) > 1000)
            {
                ShowMenu = !ShowMenu;
                INPUT input;
                WORD vKey = VK_ESCAPE;
                input.type = INPUT_KEYBOARD;
                input.ki.wScan = MapVirtualKey(vKey, MAPVK_VK_TO_VSC);
                input.ki.time = 0;
                input.ki.dwExtraInfo = 0;
                input.ki.wVk = vKey;
                input.ki.dwFlags = 0;
                SendInput(1, &input, sizeof(INPUT));
                input.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &input, sizeof(INPUT));
                LastTick = GetTickCount();
            }
        }

        if (ShowMenu)
        {
            //  SetStyle();
            Helper::RenderMenu();
            ClickThough(false);
        }
        else
        {
            ImVec4* colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            Render::Start();
            Helper::RenderStatic();
            Helper::RenderFeatures();
            Render::End();
            ClickThough(true);
        }

        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * 255.0f), (int)(clear_color.y * 255.0f), (int)(clear_color.z * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);
    //  
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    g_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;
    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    //
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    if (msg == WM_PAINT)
    {

        DwmExtendFrameIntoClientArea(hWnd, &zero);
    }
    if (msg == WM_SIZE)
    {
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    }
    if (msg == WM_SYSCOMMAND)
    {
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
    }
    if (msg == WM_DESTROY)
    {
        ::PostQuitMessage(0);
    }
    // 
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
void Render::Start()
{
    //  
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(GetScreenInfo().width, GetScreenInfo().height), ImGuiCond_Always);
    ImGui::Begin(" ", (bool*)true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.70f);
    //   
}

void Render::End()
{
    ImGui::End();
}

void Render::Text(ImVec2 pos, float fontsize, ImColor color, const char* text_begin, const char* text_end, float wrap_width,
    const ImVec4* cpu_fine_clip_rect)
{
    ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), fontsize, pos, color, text_begin, text_end,
        wrap_width, cpu_fine_clip_rect);
}

void Render::RectFilled(int x0, int y0, int x1, int y1, ImColor color, float rounding, int rounding_corners_flags)
{
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x0, y0), ImVec2(x1, y1), color, rounding, rounding_corners_flags);
}

void Render::Line(ImVec2 a, ImVec2 b, ImColor color, float thickness)
{
    ImGui::GetWindowDrawList()->AddLine(a, b, color, thickness);
}

void Render::EasyText(ImVec2 pos, ImColor color, const char* text)
{
    Render::Text(ImVec2(pos.x + 1.f, pos.y + 1.f), 17.f, ImColor(0.f, 0.f, 0.f, 1.f), text, text + strlen(text), 800, 0);
    Render::Text(ImVec2(pos.x - 1.f, pos.y - 1.f), 17.f, ImColor(0.f, 0.f, 0.f, 1.f), text, text + strlen(text), 800, 0);
    Render::Text(ImVec2(pos.x, pos.y - 1.f), 17.f, ImColor(0.f, 0.f, 0.f, 1.f), text, text + strlen(text), 800, 0);
    Render::Text(ImVec2(pos.x, pos.y + 1.f), 17.f, ImColor(0.f, 0.f, 0.f, 1.f), text, text + strlen(text), 800, 0);
    Render::Text(ImVec2(pos.x, pos.y), 17.f, color, text, text + strlen(text), 800, 0);
}
void Render::HotBarText(ImVec2 pos, ImColor color, const char* text)
{
    Render::Text(ImVec2(pos.x, pos.y), 17.f, color, text, text + strlen(text), 800, 0);
}
void Render::DrawBox(ImColor color, int x, int y, int w, int h)
{
    float thicc = 2.0f;

    // ------
    // |    |
    Line(ImVec2(x, y), ImVec2(x + w, y), color, thicc);

    // |
    // |
    // |
    Line(ImVec2(x, y), ImVec2(x, y + h), color, thicc);

    //      |
    //      |
    //      |
    Line(ImVec2(x + w, y), ImVec2(x + w, y + h), color, thicc);

    // |    |
    // ------
    Line(ImVec2(x, y + h), ImVec2(x + w, y + h), color, thicc);
}

void Render::Circle(ImColor color)
{
    //ImVec2 center = ImVec2(g_Vars->width / 2, g_Vars->height / 2);
    //ImGui::GetWindowDrawList()->AddCircle(center, g_Vars->settings.aim.MaxFOV, color, 100, 2.f);
}

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
void Render::HealthBar(int x, int y, int w, int h, int phealth)
{
    int healthValue = max(0, min(phealth, 100));
    float HealthPerc = healthValue / 100.f;

    ImColor barColor = ImColor
    (
        min(510 * (100 - healthValue) / 100, 255),
        min(510 * healthValue / 100, 255),
        25,
        255
    );

    RectFilled(x, y, x + w, y + (int)(((float)h / 100.0f) * (float)phealth), barColor, 0.0f, 0);
}
void Render::ShieldBar(int x, int y, int w, int h, int pshield)
{
    int pshieldValue = max(0, min(pshield, 100));
    float shieldPerc = pshieldValue / 100.f;

    ImColor barColor = ImColor(1.f, 0.f, 1.f, 1.0f);
    if (pshieldValue > 100)
    {
        barColor = ImColor(1.f * 200, 0.f, 0.f, 1.f);
    }
    else if (pshieldValue > 75)
    {
        barColor = ImColor(0.772f, 0.f, 1.f, 1.f);
    }
    else if (pshieldValue > 50)
    {
        barColor = ImColor(0.f, 0.f, 1.f, 1.f);
    }
    else if (pshieldValue > 0)
    {
        barColor = ImColor(1.f, 1.f, 1.f, 1.0f);
    }

    RectFilled(x, y, x + w, y + (int)(((float)h / 100.0f) * (float)pshield), barColor, 0.0f, 0);
}

void Helper::RenderStatic()
{
    std::string toptext;

    toptext = "";

    const char* text = toptext.c_str();
    Render::EasyText(ImVec2(10, 10), ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)), text);
}

static int keystatus = 0;
void ChangeKey(void* blank)
{
    keystatus = 1;
    while (true)
    {
        for (int i = 0; i < 0x87; i++)
        {
            if (GetKeyState(i) & 0x8000)
            {
                //g_Vars->settings.aim.aimkey = i;
                keystatus = 0;
                return;
            }
        }
    }
}

static int switchTabs = 4;
float sliderFloat = 0.f;
static int sliderInt = 0;
static float indentFloat = 0.f;
const ImVec4 menuHeader1;
const ImVec4 buttonTextColor = ImVec4(255.00f, 255.00f, 0.00f, 1.00f);
const ImVec4 yellowTextColor = ImVec4(255.00f, 0.00f, 0.00f, 1.00f);
const ImVec4 yellowMenuBar = ImVec4(255.00f, 255.00f, 0.00f, 1.00f);
const ImVec4 orangeColor = ImVec4(244.00f, 113.00f, 0.00f, 0.20f);
const char column1 = 1;

void Helper::RenderMenu()
{
    ImVec4* colors2 = ImGui::GetStyle().Colors;
 
    ImVec4* checkBoxColor = ImGui::GetStyle().Colors;
    auto& style = ImGui::GetStyle();
    ImVec4* buttonColor = ImGui::GetStyle().Colors;
    style.Colors[ImGuiCol_TitleBg] = ImVec4{ 190.f / 255.f, 80.f / 255.f, 10.f / 255.f, 1.f };// Title InActive
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4{ 190.f / 255.f, 80.f / 255.f, 10.f / 255.f, 1.f };//Title Active
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 190.f / 255.f, 80.f / 255.f, 10.f / 255.f, 1.f };//Title collapsed

    style.Colors[ImGuiCol_WindowBg] = ImVec4{ 27.f / 255.f, 25.f / 255.f, 26.f / 255.f, 1 };//Background

    style.Colors[ImGuiCol_Border] = ImVec4{ 190.f / 255.f, 80.f / 255.f, 10.f / 255.f, 1.f };//Border

    style.Colors[ImGuiCol_Button] = ImVec4{ 190.f / 255.f, 80.f / 255.f, 10.f / 255.f, 1.f };//Tab
    style.Colors[ImGuiCol_ButtonActive] = ImVec4{ 178.f / 255.f, 61.f / 255.f, 10.f / 255.f, 1.f };//Tab pressed
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4{ 178.f / 255.f, 61.f / 255.f, 10.f / 255.f, 1.f };//Tab hovered

    style.Colors[ImGuiCol_FrameBg] = ImVec4{ 50.f / 255.f, 50.f / 255.f, 50.f / 255.f, 1.f }; //Button BG
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4{ 178.f / 255.f, 61.f / 255.f, 10.f / 255.f, 1.f }; //Button BG pressed
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4{ 178.f / 255.f, 61.f / 255.f, 10.f / 255.f, 1.f }; //Button BG hovered
    style.Colors[ImGuiCol_CheckMark] = ImVec4{ 178.f / 255.f, 61.f / 255.f, 10.f / 255.f, 1.f }; //Button Checkmark



    style.Colors[ImGuiCol_FrameBg] = ImVec4{ 50.f / 255.f, 50.f / 255.f, 50.f / 255.f, 1.f }; //Button BG
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4{ 178.f / 255.f, 61.f / 255.f, 10.f / 255.f, 1.f }; //Button BG pressed
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4{ 178.f / 255.f, 61.f / 255.f, 10.f / 255.f, 1.f }; //Button BG hovered

    ImGuiWindowFlags windowflags = 0;
    windowflags |= ImGuiWindowFlags_NoResize;
    ImGui::SetNextWindowSize({ 410, 410 });

    
   
    
    checkBoxColor[ImGuiCol_Text] = ImVec4(255.00f, 255.00f, 255.00f, 1.00f);


   
  
    windowflags |= ImGuiWindowFlags_NoResize;
    static bool open = true;
    if (!open) ExitProcess(0);
    ImGui::Begin("Rise Cheats | Call Of Duty: Black Ops");
    ImGui::TextColored(menuHeader1, "oof");
    ImGui::Indent(indentFloat = 100.f);
    // ImGui::Text("[ Zombies Menu ]");
    ImGui::TextColored(menuHeader1, "oof");
    //  ImGui::Spacing();
    ImGui::Unindent(indentFloat = 80.f);
    if (ImGui::Button("Global"))
        switchTabs = 4;
    ImGui::SameLine(0.0, 10.0f);
    if (ImGui::Button("P1", ImVec2(60.0f, 0.0f)))
        switchTabs = 0;
    ImGui::SameLine(0.0, 10.0f);
    if (ImGui::Button("P2", ImVec2(60.0f, 0.0f)))
        switchTabs = 1;
    ImGui::SameLine(0.0, 10.0f);
    if (ImGui::Button("P3", ImVec2(60.0f, 0.0f)))
        switchTabs = 2;
    ImGui::SameLine(0.0, 10.0f);
    if (ImGui::Button("P4", ImVec2(60.0f, 0.0f)))
        switchTabs = 3;
    ImGui::SameLine(0.0, 10.0f);

    switch (switchTabs)
    {
    case 0:
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::TextColored(ImVec4(255, 255, 255, 1), "Player 1 Options");
        ImGui::Separator();

        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Godmode", &infiniteHealth);
        //  ImGui::SameLine();

        //  ImGui::Text("[ Extra Goodies ]");

        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Infinite Ammo", &infiniteAmmo);
        //  ImGui::SameLine();

        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Infinite Points", &infinitePoints);
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Force Headshots", &alwaysCrit);
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Weapon Cycle [NUM1]", &p1WCycle);
        break;
    case 1:
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::TextColored(ImVec4(255, 255, 255, 1), "Player 2 Options");
        ImGui::Separator();

        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Godmode", &p2infiniteHealth);
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Infinite Ammo", &p2infiniteAmmo);
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Infinite Points", &p2infinitePoints);
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Force Headshots", &p2alwaysCrit);
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Weapon Cycle [NUM2]", &p2WCycle);
        //    ImGui::TextColored(menuHeader1, "oof");
       //     ImGui::Text("[ Extra Goodies ]");
       //     ImGui::Unindent(indentFloat = 82.f);  
    //    //    ImGui::TextColored(menuHeader1, "oof");
        //    ImGui::Checkbox("L/C | '5'", &p2LCycle);
     //       ImGui::TextColored(menuHeader1, "oof");
     //       ImGui::Checkbox("T/C | '6'", &p2TCycle);
     //       ImGui::TextColored(menuHeader1, "oof");
       //     ImGui::Checkbox("FU/C | 'NUM 1'", &p2FUCycle);
        //    ImGui::TextColored(menuHeader1, "oof");
         //   ImGui::Checkbox("WW/C | 'NUM 2'", &p2WWCycle);
        break;
    case 2:
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::TextColored(ImVec4(255, 255, 255, 1), "Player 3 Options");
        ImGui::Separator();

        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Godmode", &p3infiniteHealth);
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Infinite Ammo", &p3infiniteAmmo);
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Infinite Points", &p3infinitePoints);
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Force Headshots", &p3alwaysCrit);
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Weapon Cycle [NUM3]", &p3WCycle);
        //  ImGui::TextColored(menuHeader1, "oof");
         // ImGui::Indent(indentFloat = 82.f);
     //     ImGui::Text("[ Extra Goodies ]");
      //    ImGui::Unindent(indentFloat = 82.f);
       //   ImGui::Checkbox("W/C | '9'", &p3WCycle);
       //   ImGui::TextColored(menuHeader1, "oof");
       //   ImGui::Checkbox("L/C | '0'", &p3LCycle);
       //   ImGui::TextColored(menuHeader1, "oof");
       //   ImGui::Checkbox("T/C | '-'", &p3TCycle);
       //   ImGui::TextColored(menuHeader1, "oof");
       //   ImGui::Checkbox("FU/C | 'NUM 4'", &p3FUCycle);
       //   ImGui::TextColored(menuHeader1, "oof");
       //   ImGui::Checkbox("WW/C | 'NUM 5'", &p3WWCycle);
        break;
    case 3:
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::TextColored(ImVec4(255, 255, 255, 1), "Player 4 Options");
        ImGui::Separator();

        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Godmode", &p4infiniteHealth);
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Infinite Ammo", &p4infiniteAmmo);
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Infinite Points", &p4infinitePoints);
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Force Headshots", &p4alwaysCrit);
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Checkbox("Weapon Cycle [NUM4]", &p4WCycle);
        //    ImGui::Text("[ Extra Goodies ]");
      //      ImGui::Unindent(indentFloat = 82.f);
    //ImGui::Checkbox("W/C | ','", &p4WCycle);
       //     ImGui::TextColored(menuHeader1, "oof");
       //     ImGui::Checkbox("L/C | '.'", &p4LCycle);
       //     ImGui::TextColored(menuHeader1, "oof");
        //    ImGui::Checkbox("T/C | '/'", &p4TCycle);
        //    ImGui::TextColored(menuHeader1, "oof");
        //    ImGui::Checkbox("FU/C | 'NUM 7'", &p4FUCycle);
        //    ImGui::TextColored(menuHeader1, "oof");
       //     ImGui::Checkbox("WW/C | 'NUM 8'", &p4WWCycle);
        break;
    case 4:
        ImGui::TextColored(menuHeader1, "oof");
        ImGui::TextColored(ImVec4(255, 255, 255, 1), "Global Options");
        ImGui::Separator();



        ImGui::TextColored(menuHeader1, "oof");
        ImGui::Text("[ Lobby Options ]");
        ImGui::SameLine(0.0, 50.0f);
        ImGui::Text("[ Options ]");
        ImGui::Checkbox("Speedhack", &p1Speed);


        ImGui::SameLine(0.0, 85);

        if (ImGui::Button("End Game"))
        {
            disconnectGame = true;
        }

        ImGui::Checkbox("Super Jump", &jumpHeight);


        ImGui::SameLine(0.0, 78);

        if (ImGui::Button("Restart Game"))
        {
            restartGame = true;
        }


        ImGui::TextColored(menuHeader1, "oof");

        ImGui::Text("[ XP Options ]");
        ImGui::SameLine(0.0, 70.0f);
        ImGui::Text("[ One Shot Gold ]");
        ImGui::Checkbox("Player Rank XP", &playerRankXP);
        ImGui::SameLine(0.0, 48.0f);
        if (ImGui::Button("Gold Gun"))
        {
            blaznOneShot = true;
        }
        ImGui::Checkbox("Weapon Rank XP", &playerWeaponXP);


        /*ImGui::Text("[ XP Options ]");
        ImGui::SameLine(0.0, 60.0f);
        ImGui::Text("[ One Shot Gold ]");
        ImGui::Checkbox("Player Rank XP", &playerRankXP);
        ImGui::SameLine(0.0, 25.0f);
        ImGui::Checkbox("Speedhack", &p1Speed);
        ImGui::Checkbox("Weapon Rank XP", &playerWeaponXP);
        ImGui::SameLine(0.0, 25.0f);
        ImGui::Checkbox("Super Jump", &jumpHeight);
        */




        // ImGui::SliderFloat("", &xpval, 1, 250, "%.3f", 1);


        ImGui::TextColored(menuHeader1, "oof");

        ImGui::Text("[ Zombie Options ]");
        ImGui::SameLine(0.0, 42.0f);
        ImGui::Text("[ Experimental ]");
        ImGui::Checkbox("Zombie TP", &zombieTP);
       // ImGui::SameLine(0.0, 84.0f);
     //   ImGui::Checkbox("Freeze Box", &freezeBox);
        if (ImGui::Button("Set TP Location"))
        {
            newZombieLocation = true;
        }
       // ImGui::SameLine(0.0, 57.0f);
      //  ImGui::Checkbox("Long Revive", &longRevive);
    }
    ImGui::End();
}

void Helper::RenderFeatures()
{
    //cheat method
}