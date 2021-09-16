#include "./include/RequestTypes.hpp"

using requests::RequestType;
using namespace std;

map<QString, RequestType::Types> RequestType::requestTypeMap = {
        {"display-image", DisplayImageType},
        {"rotate-camera", RotateCameraType},
        {"press-key", PressKeyType},
        {"hide-camera", HideCameraType}
    };

RequestType::Types RequestType::from(QString type) {
    if(requestTypeMap.find(type) == requestTypeMap.end()) {
        return Unknown;
    }

    return requestTypeMap[type];
}
