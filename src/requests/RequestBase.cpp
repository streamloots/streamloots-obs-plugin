#include "./include/RequestBase.hpp"

using requests::RequestBase;

RequestBase::RequestBase(obs_data_t *request)
{
	QString methodName = obs_data_get_string(request, "request-type");
	type = RequestType::from(methodName);
	messageId = obs_data_get_string(request, "message-id");
	metadata = obs_data_get_obj(request, "metadata");
}