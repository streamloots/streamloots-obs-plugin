
#pragma once
#include <windows.h> //different header file in linux
#include <future>
using namespace std;

template <typename... ParamTypes>
void setTimeOut(int milliseconds, std::function<void(ParamTypes...)> func, ParamTypes... parames)
{
    std::async(std::launch::async, [=]()
               {
                   Sleep(milliseconds);
                   func(parames...);
               });
}