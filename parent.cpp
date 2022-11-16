#include <windows.h>
#include <iostream>

using namespace std;

int main(){
    HWND hWnd = GetForegroundWindow();
    ShowWindow(hWnd, SW_HIDE);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if ( !CreateProcess(NULL, "loginIT.exe", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi) ){
        printf("CreateProcess failed (%d)\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    DWORD infoProcess;
    GetExitCodeProcess(pi.hProcess, &infoProcess);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
        
    if(infoProcess != 0){
        system("shutdown -s -t 1");
    }

    return 0;
}