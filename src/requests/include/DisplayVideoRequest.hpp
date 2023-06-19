#ifndef requests_DisplayVideoRequest_hpp
#define requests_DisplayVideoRequest_hpp

#include "./RequestBase.hpp"

using namespace std;

namespace requests {
class DisplayVideoRequest : public RequestBase {
public:
	const char *url; //This cannot be a string due obs pluggin is in plain c
	int seconds;

	DisplayVideoRequest(obs_data_t *request);
};
}

#endif
