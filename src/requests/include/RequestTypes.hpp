#ifndef requests_RequestTypes_hpp
#define requests_RequestTypes_hpp
#include <QtCore/QString>

namespace requests {
    class RequestType {
        public:
        static enum Types { DisplayImageType, RotateCameraType, PressKeyType, HideCameraType };
        static Types from(QString type);
    };    
}

#endif