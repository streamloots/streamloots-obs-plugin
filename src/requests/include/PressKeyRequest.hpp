#ifndef requests_PressKeyRequest_hpp
#define requests_PressKeyRequest_hpp
#include "./RequestBase.hpp"

namespace requests {
    class PressKeyRequest : public RequestBase {
        public:
            PressKeyRequest(obs_data_t *request);
    };
}

#endif