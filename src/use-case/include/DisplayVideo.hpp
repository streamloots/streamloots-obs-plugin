#ifndef useCase_DisplayVideo_hpp
#define useCase_DisplayVideo_hpp
#include <obs-module.h>
#include "../../responses/include/Response.hpp"

namespace useCase{
    class DisplayVideo {
        public:
            static responses::Response invoke(obs_data_t *baseRequest);
        
        private: 
            static void set_source_full_screen(obs_sceneitem_t *source);
            static void configure_settings(obs_source_t *source);
        };
}

#endif