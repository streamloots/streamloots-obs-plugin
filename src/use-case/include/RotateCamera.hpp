#ifndef RotateCamera_hpp
#define RotateCamera_hpp
#include <obs-module.h>
#include "../../responses/include/Response.hpp"

namespace useCase{
    class RotateCamera {
        public:
            static responses::Response invoke(obs_data_t *baseRequest);
        
        private:
            static inline void rotate_source(const char *name, int seconds);
        };
}

#endif