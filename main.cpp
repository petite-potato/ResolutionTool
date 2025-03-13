#include <Windows.h>
#include <iostream>


int gethz() {
    DEVMODE devmode;

    if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devmode)) {
        return devmode.dmDisplayFrequency;
    }
    else {
        std::cerr << "failed" << std::endl;
        return -1;
    }
}

void setres(int width, int height, int refreshRate) {
    DEVMODE devmode;
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devmode);

    devmode.dmPelsWidth = width;
    devmode.dmPelsHeight = height;
    devmode.dmDisplayFrequency = refreshRate;
    devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

    if (ChangeDisplaySettings(&devmode, CDS_UPDATEREGISTRY) != DISP_CHANGE_SUCCESSFUL) {
        std::cout << "failed" << std::endl;
    }
    else {
        std::cout << "done"  << std::endl;
    }
}

int main() {
    int refreshrate = gethz();

    if (refreshrate == -1) {
        return 1;
    }
    std::cout << "f1 | 4:3 @ " << refreshrate << std::endl;
    std::cout << "f2 | 16:9 @ " << refreshrate << std::endl;
    std::cout << "f3 | 5:4 @ " << refreshrate << std::endl;
    std::cout << "ignore ur screen going black" << std::endl;
    while (true) { 
        // no case 4 u
        if (GetAsyncKeyState(VK_F1) & 0x8000) {
            setres(1440, 1080, refreshrate);
            break;
        }

        if (GetAsyncKeyState(VK_F2) & 0x8000) {
            setres(1920, 1080, refreshrate);
            break;
        }
        
        if (GetAsyncKeyState(VK_F3) & 0x8000) {
            setres(1280, 1080, refreshrate);
            break;
        }

        Sleep(100);
    }

    return 0;
}
