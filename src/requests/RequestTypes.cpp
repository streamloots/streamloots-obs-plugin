#include "./include/RequestTypes.hpp"
#include <map>

using requests::RequestType;
using namespace std;

RequestType::Types RequestType::from(QString type) {
    map<QString, RequestType::Types> requestTypeMap = {
        {"display-image", DisplayImageType},
        {"rotate-camera", RotateCameraType},
        {"press-key", PressKeyType},
        {"hide-camera", HideCameraType}
    };

    return requestTypeMap[type];
}
