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
    std::function<void()> cb = [&]()
    {
        // pressKeys(request.keys);
        pressKeySeconds();
    };
    setTimeOut(10 * 1000, cb);

    return Response(request.messageId.toStdString());
}

void PressKey::pressKeySeconds()
{
    INPUT ip = getKey("A");
    ip.ki.time = 3000;
    SendInput(1, &ip, sizeof(INPUT));

    std::function<void()> cb = [&]()
    {
        INPUT ip2 = getKey("A");
        ip2.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip2, sizeof(INPUT));
    };
    setTimeOut(5 * 1000, cb);
}
void PressKey::pressKeys(OBSDataArrayAutoRelease keys)
{
    INPUT inputs[4] = {};
    ZeroMemory(inputs, sizeof(inputs));
    for (int i = 0; i < obs_data_array_count(keys); i++)
    {
        OBSDataAutoRelease keyObj = obs_data_array_item(keys, i);
        QString key = obs_data_get_string(keyObj, "key");
        blog(LOG_INFO, "string %s", key);
        INPUT ip = getKey(key);
        inputs[i] = ip;
    }
    for (int i = 0; i < obs_data_array_count(keys); i++)
    {
        OBSDataAutoRelease keyObj = obs_data_array_item(keys, i);
        QString key = obs_data_get_string(keyObj, "key");
        blog(LOG_INFO, "string %s", key);
        INPUT ip = getKey(key);
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        inputs[i + 2] = ip;
    }
    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
        blog(LOG_ERROR, "SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
    }
}

INPUT PressKey::getKey(QString str)
{
    char key = str.at(0).toLatin1();
    blog(LOG_INFO, "getting input %c", key);
    HKL kbl = GetKeyboardLayout(0);
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    if (str == "ALT")
    {
        ip.ki.wVk = 0x0012;
        return ip;
    }
    if (str == "F4")
    {
        ip.ki.wVk = 0x0073;
        return ip;
    }

    if ((int)key < 65 && (int)key > 90) //for lowercase
    {
        ip.ki.wScan = 0;
        ip.ki.wVk = VkKeyScanEx(key, kbl);
    }
    else //for uppercase
    {
        ip.ki.wScan = key;
        ip.ki.wVk = 0;
    }
    ip.ki.dwExtraInfo = 0;
    return ip;
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
