#ifndef UseCaseManager_hpp
#define UserCaseManager_hpp
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