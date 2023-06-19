#ifndef server_WSRequest_hpp
#define server_WSRequest_hpp
#include <obs-data.h>
#include <string>

namespace server {
class WSRequest {
public:
	static std::string processMessage(std::string message);

private:
	static std::string validateData(std::string message, obs_data_t *data);
	static const std::string NO_VALIDATION_ERROR;
};
}

#endif