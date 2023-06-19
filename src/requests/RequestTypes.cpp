#include "./include/RequestTypes.hpp"

using requests::RequestType;
using namespace std;

map<QString, RequestType::Types> RequestType::requestTypeMap = {{"display-image", DisplayImageType},
								{"rotate-camera", RotateCameraType},
								{"press-key", PressKeyType},
								{"hide-camera", HideCameraType},
								{"display-video", DisplayVideo}};

RequestType::Types RequestType::from(QString type)
{
	map<QString, RequestType::Types>::iterator it = requestTypeMap.find(type);

	if (it == requestTypeMap.end()) {
		return Unknown;
	}

	return it->second;
}
