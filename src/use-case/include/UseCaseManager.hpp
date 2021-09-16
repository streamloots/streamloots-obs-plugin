#ifndef useCase_UseCaseManager_hpp
#define useCase_UserCaseManager_hpp
#include <obs-module.h>
#include "../../responses/include/Response.hpp"

namespace useCase{
    class UseCaseManager
    {
        public:
            static responses::Response processUseCase(obs_data_t *request = nullptr);
    };
}

#endif