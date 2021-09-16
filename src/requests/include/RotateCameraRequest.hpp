#ifndef requests_RotateCameraRequest_hpp
#define requests_RotateCameraRequest_hpp
#include "./RequestBase.hpp"

using namespace std;

namespace requests {
    class RotateCameraRequest : public RequestBase {
        public:
            string url;
            int seconds;

            RotateCameraRequest(obs_data_t *request);
    };
}
#endif