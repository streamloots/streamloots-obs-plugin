#ifndef UseCaseManager_hpp
#define UserCaseManager_hpp
#include <obs-module.h>

class UseCaseManager
{
    public:
        static void processUseCase(obs_data_t *request = nullptr);
};

#endif