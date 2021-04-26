#pragma once

//typedef LONG NTSTATUS, * PNTSTATUS;
//#define STATUS_SUCCESS (0x00000000)

typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

RTL_OSVERSIONINFOW GetRealOSVersion()
{
    Protect();
    HMODULE hMod = ::GetModuleHandleW(L"ntdll.dll");
    if (hMod) 
    {
        RtlGetVersionPtr fxPtr = (RtlGetVersionPtr)::GetProcAddress(hMod, "RtlGetVersion");
        if (fxPtr != nullptr) 
        {
            RTL_OSVERSIONINFOW rovi = { 0 };
            rovi.dwOSVersionInfoSize = sizeof(rovi);
            if (0 == fxPtr(&rovi)) 
            {
                return rovi;
            }
        }
    }
    RTL_OSVERSIONINFOW rovi = { 0 };
    ProtectEnd();
    return rovi;
}
