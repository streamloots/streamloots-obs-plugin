#ifndef requests_RequestTypes_hpp
#define requests_RequestTypes_hpp
#include <QtCore/QString>
#include <map>

namespace requests {
    class RequestType {
        public:
            static enum Types { DisplayImageType, RotateCameraType, PressKeyType, HideCameraType, Unknown };
            static Types from(QString type);

        private:
            static std::map<QString, RequestType::Types> requestTypeMap;
    };    
}

#endif