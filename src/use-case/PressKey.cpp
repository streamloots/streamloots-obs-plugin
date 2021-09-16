#define WINVER 0x0500
#include <windows.h>
#include <winuser.h>
#include "../requests/include/PressKeyRequest.hpp"
#include "../responses/include/ResponseError.hpp"
#include "../utils/timers.h"
#include "./include/PressKey.hpp"

using namespace requests;
using namespace responses;
using useCase::PressKey;

Response PressKey::invoke(obs_data_t *baseRequest)
{
    PressKeyRequest request(baseRequest);
    ShowFilter();
    std::function<void()> cb = [&]()
    {
        blog(LOG_INFO, "pressing enter");
        ShowFilter();
    };
    setTimeOut(10 * 1000, cb);

    return Response(request.messageId.toStdString());
}

void PressKey::pressKeyB(char mK)
{
    HKL kbl = GetKeyboardLayout(0);
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.dwFlags = KEYEVENTF_UNICODE;
    if ((int)mK < 65 && (int)mK > 90) //for lowercase
    {
        ip.ki.wScan = 0;
        ip.ki.wVk = VkKeyScanEx(mK, kbl);
    }
    else //for uppercase
    {
        ip.ki.wScan = mK;
        ip.ki.wVk = 0;
    }
    ip.ki.dwExtraInfo = 0;
    SendInput(1, &ip, sizeof(INPUT));
}

void PressKey::pressEnter()
{
    blog(LOG_INFO, "pressing enter");
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.dwFlags = KEYEVENTF_UNICODE;
    ip.ki.wScan = VK_RETURN; //VK_RETURN is the code of Return key
    ip.ki.wVk = 0;

    ip.ki.dwExtraInfo = 0;
    SendInput(1, &ip, sizeof(INPUT));
}

void PressKey::ShowDesktop()
{
    blog(LOG_INFO, "Sending W+D");
    INPUT inputs[4] = {};
    ZeroMemory(inputs, sizeof(inputs));
    auto VK_D = 0x0044;

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_LWIN;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_D;

    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = VK_D;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_LWIN;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
        blog(LOG_ERROR, "SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
    }
}

void PressKey::ShowFilter()
{
    blog(LOG_INFO, "Sending CTRL+P");
    INPUT inputs[4] = {};
    ZeroMemory(inputs, sizeof(inputs));
    auto VK_D = 0x0044;
    auto VK_P = 0x0050;

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_LCONTROL;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_P;

    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = VK_P;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_LCONTROL;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
        blog(LOG_ERROR, "SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
    }
}
