#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <stdio.h>
#include <math.h>

const char* sites[4] = {
    "https://www.google.com/search?q=skibidi+toilet&oq=skibid&gs_lcrp=EgZjaHJvbWUqCggBEAAYsQMYgAQyBggAEEUYOTIKCAEQABixAxiABDIKCAIQLhixAxiABDIHCAMQABiABDIHCAQQABiABDIHCAUQABiABDIHCAYQLhiABDIHCAcQABiABDIHCAgQABiABDIHCAkQABiPAtIBCDIwNjNqMGo3qAIAsAIA&sourceid=chrome&ie=UTF-8",
    "https://c.tenor.com/rgegj1AOR1IAAAAd/tenor.gif",
    "https://c.tenor.com/L8N6vL3C0rIAAAAd/tenor.gif",
    "https://www.wikihow.com/Repair-a-Computer",
};

DWORD WINAPI windowsSounds(void*) {
        srand((time(NULL)));
        const TCHAR* systemSounds[] = {
        TEXT("MailBeep"),
        TEXT("LowBatteryAlarm"),
        TEXT("DeviceFail"),
        TEXT("FaxBeep"),
        TEXT("SystemAsterisk"),
        TEXT("MessageNudge"),
        TEXT("WindowsLogoff"),
        TEXT("WindowsLogon"),
    };


    int sleepTime = 200;
    int elapsedSeconds = 0;

    while (true) { 
        int random = rand() % (sizeof(systemSounds) / sizeof(systemSounds[0]));
        PlaySound(systemSounds[random], NULL, SND_ASYNC); 
        Sleep(sleepTime);
        elapsedSeconds++;

        if (elapsedSeconds % 20 == 0) {
            if (sleepTime > 20) {
                sleepTime -= 20; 
            }
        }
    }


}

DWORD WINAPI tunnelEffect(void*) {
    srand((time(NULL)));
    int sleepTime = 200;
    int elapsedSeconds = 0;

    while (true) {
        int x = GetSystemMetrics(SM_CXSCREEN);
        int y = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        StretchBlt(hdc, rand() % 100, rand() % 100, x - 100, y - 100, hdc, 0, 0, x, y, 0x100000);
        Sleep(sleepTime);
        ReleaseDC(NULL, hdc);
        elapsedSeconds++;

        if (elapsedSeconds % 30 == 0) {
            if (sleepTime > 20) {
                sleepTime -= 20; 
            }
        }
    }
}

DWORD WINAPI changePixels(void*) {
    srand((time(NULL)));
    while (true) {
        int x = GetSystemMetrics(SM_CXSCREEN);
        int y = GetSystemMetrics(SM_CYSCREEN);   

        HDC hdc5 = GetDC(NULL);
        COLORREF color = GetPixel(hdc5, rand() % x, rand() % y);
             
        int blockSize = 1000;
        for (int i = 0; i < blockSize; ++i) {
            for (int j = 0; j < blockSize; ++j) {
                if (rand() % 5 == 0) { 
                    continue;
                }
                SetPixel(hdc5, (rand() % x) + i, (rand() % y) + j, RGB(GetRValue(color), GetGValue(color), GetBValue(color)));
            }
        }

        ReleaseDC(NULL, hdc5);
        Sleep(10000); 
    }
    return 0;

}


DWORD WINAPI randomSites(void*) {
    srand((time(NULL)));
    for(int i =0; i <3;i++)
    {
        ShellExecuteA(NULL, "open", (LPCSTR)sites[rand() % 3], NULL, NULL, SW_SHOWDEFAULT);
        Sleep(2000 + rand() % 10000);
    }
    return 0;
}

DWORD WINAPI randomGDIDrawing(void*) {
    srand((time(NULL)));
    HDC hdc3 = GetDC(NULL);
    int centerX = GetSystemMetrics(SM_CXSCREEN) / 2; 
    int centerY = GetSystemMetrics(SM_CYSCREEN) / 2;  
    int radius = 2000; 

    while (true) {
            for (double angle = 0; angle < 360; angle += 0.5) { 
                HDC hdc3 = GetDC(NULL);
                HPEN hPen = CreatePen(PS_SOLID, 3, RGB(rand() % 256, rand() % 256, rand() % 256));
                SelectObject(hdc3, hPen);
                double radian = angle * 3.14 / 180;
                int endX = centerX + static_cast<int>(radius * cos(radian));
                int endY = centerY + static_cast<int>(radius * sin(radian));
                MoveToEx(hdc3, centerX, centerY, NULL);
                LineTo(hdc3, endX, endY);
                DeleteObject(hPen);
                ReleaseDC(NULL, hdc3);
        }
    }
    return 0;
}


DWORD WINAPI invert(void*)
{
    srand((time(NULL)));
    Sleep(5000);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    while (true) {
        HDC hdc2 = GetWindowDC(NULL);
        BitBlt(hdc2, 0, 0, screenWidth, screenHeight, hdc2, 0, 0, NOTSRCCOPY);
        Sleep(2000);
        ReleaseDC(NULL, hdc2);
    }
    return 0;
}

LRESULT CALLBACK msgBoxHook(int nCode, WPARAM wParam, LPARAM lParam) {
    srand((time(NULL)));
	if (nCode == HCBT_CREATEWND) {
        CREATESTRUCT* pcs = ((CBT_CREATEWND*)lParam)->lpcs;

        if ((pcs->style & WS_DLGFRAME) || (pcs->style & WS_POPUP)) {
            int screenWidth = GetSystemMetrics(SM_CXSCREEN);
            int screenHeight = GetSystemMetrics(SM_CYSCREEN);
            pcs->x = rand() % (screenWidth - pcs->cx); 
            pcs->y = rand() % (screenHeight - pcs->cy);
        }
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}


DWORD WINAPI createBox(void*) {
    srand((time(NULL)));
    while (true) 
    {
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        int randX = rand() % screenWidth;
        int randY = rand() % screenHeight;
        HHOOK hook = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
        MessageBoxW(NULL, L"ZAZA", L"lol", MB_OK | MB_ICONWARNING);
        UnhookWindowsHookEx(hook);
    }
    return 0;
}

DWORD WINAPI messegeBox(void*) {
    srand((time(NULL)));
    Sleep(10000);
    while (true) {
        CreateThread(NULL, 0, createBox , NULL, 0, NULL);
        Sleep(2000 + rand() % 5000 );
    } 

    return 0;
}

DWORD WINAPI screenPixels(void*) {
    srand((time(NULL)));
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    while (true)
    {
        HDC hdc = GetWindowDC(NULL);
        for (int x = 0; x < screenWidth; x++) {
            COLORREF color = RGB(rand() % 255, rand() % 255, rand() % 255);
            for (int y = 0; y < screenHeight; y++) {
                SetPixel(hdc, x, y, color);
            }
        }
        ReleaseDC(NULL, hdc);
    }
    return 0;
}

DWORD WINAPI icons(void*) {
    srand((time(NULL)));
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    while (true) {
        POINT p;
        HDC hdc = GetWindowDC(NULL);
        HDC hdc2 = GetWindowDC(NULL);
        GetCursorPos(&p);
        if(rand() % 150 == 0)
            DrawIcon(hdc2, p.x, p.y, LoadIcon(NULL, IDI_WARNING));
        if(rand() % 300 == 0 )
            DrawIcon(hdc, rand() % screenWidth, rand() % screenHeight, LoadIcon(NULL, IDI_ERROR));
        
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hdc2);
    }
    return 0;
}

int main() {
    
    if (MessageBoxA(NULL, "You're gonna get your screen's asshole unlocked by MalToN", "MalToN", MB_YESNO | MB_ICONWARNING) != IDYES ||
        MessageBoxA(NULL, "Are thee sure?", "MalToN", MB_YESNO | MB_ICONWARNING) != IDYES) 
			ExitProcess(0);		
    
    HANDLE hThread = CreateThread(NULL, 0, screenPixels, NULL, 0, NULL);
    Sleep(5000);
    HANDLE hThread2 = CreateThread(NULL, 0, messegeBox, NULL, 0, NULL); 
    Sleep(5000);
    HANDLE hThread3 = CreateThread(NULL, 0, invert, NULL, 0, NULL);
    Sleep(5000);
    HANDLE hThread4 = CreateThread(NULL, 0, windowsSounds, NULL, 0, NULL);
    Sleep(5000);
    HANDLE hThread5 = CreateThread(NULL, 0, icons, NULL, 0, NULL);
    Sleep(5000);
    HANDLE hThread6 = CreateThread(NULL, 0, randomGDIDrawing, NULL, 0, NULL);
    Sleep(5000);
    HANDLE hThread7 = CreateThread(NULL, 0, randomSites, NULL, 0, NULL);
    Sleep(5000);
    HANDLE hThread8 = CreateThread(NULL, 0, changePixels, NULL, 0, NULL);
    Sleep(5000);
    HANDLE hThread9 = CreateThread(NULL, 0, tunnelEffect, NULL, 0, NULL);

    WaitForSingleObject(hThread, INFINITE);
    //WaitForSingleObject(hThread2, INFINITE);
    WaitForSingleObject(hThread3, INFINITE);
    WaitForSingleObject(hThread4, INFINITE);
    WaitForSingleObject(hThread5, INFINITE);
    WaitForSingleObject(hThread6, INFINITE);
    WaitForSingleObject(hThread7, INFINITE);
    WaitForSingleObject(hThread8, INFINITE);
    WaitForSingleObject(hThread9, INFINITE);
    return 0;
    ExitProcess(0);
}
