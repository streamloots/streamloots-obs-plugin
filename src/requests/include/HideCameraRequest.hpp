#ifndef requests_HideCameraRequest_hpp
#define requests_HideCameraRequest_hpp

#include "./RequestBase.hpp"

namespace requests {
class HideCameraRequest : public RequestBase {
public:
	int seconds;

	HideCameraRequest(obs_data_t *request);
};
}

#endif
