#ifndef requests_RequestTypes_hpp
#define requests_RequestTypes_hpp
#include <QString>
#include <map>

namespace requests {
class RequestType {
public:
	enum Types { DisplayImageType, RotateCameraType, PressKeyType, HideCameraType, DisplayVideo, Unknown };
	static Types from(QString type);

private:
	static std::map<QString, RequestType::Types> requestTypeMap;
};
}

#endif
