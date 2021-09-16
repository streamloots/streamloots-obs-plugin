#ifndef requests_DisplayImageRequest_hpp
#define requests_DisplayImageRequest_hpp
#include "./RequestBase.hpp"

using namespace std;

namespace requests {
    class DisplayImageRequest : public RequestBase {
        public:
            const char* url; //This cannot be a string due obs pluggin is in plain c
            int seconds;

            DisplayImageRequest(obs_data_t *request);
    };
}

#endif