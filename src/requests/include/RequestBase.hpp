#ifndef requests_RequestBase_hpp
#define requests_RequestBase_hpp

#include <QString>

#include <obs-data.h>

#include "../../plugin-macros.generated.h"
#include "./RequestTypes.hpp"

namespace requests {
class RequestBase {
public:
	RequestType::Types type;
	QString messageId;
	OBSDataAutoRelease metadata;

	RequestBase(obs_data_t *request);
};
}

#endif
