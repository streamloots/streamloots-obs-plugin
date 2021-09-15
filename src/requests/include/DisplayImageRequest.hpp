#ifndef requests_DisplayImageRequest_hpp
#define requests_DisplayImageRequest_hpp
#include <string>
#include "./RequestBase.hpp"

using namespace std;

namespace requests {
    class DisplayImageRequest : public RequestBase {
        public:
            string url;
            int seconds;

            DisplayImageRequest(obs_data_t *request);
    };
}

#endif