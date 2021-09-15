#include "WSRequest.h"
#include <QtCore/QString>
#include "../plugin-macros.generated.h"
#include "../use-case/UseCaseManager.h"
#include "../requests/include/RequestBase.hpp"
#include "../responses/include/ResponseError.hpp"
#include "../responses/include/Response.hpp"

using namespace responses;
using namespace requests;

std::string WSRequest::processMessage(std::string message)
{
	std::string msgContainer(message);
	const char* msg = msgContainer.c_str();

	blog(LOG_INFO, "processing %s", msg);

	obs_data_t * data = obs_data_create_from_json(msg);
	if (!data) {
		blog(LOG_ERROR, "invalid JSON payload received for %s", msg);
		ResponseError error("invalid JSON payload received for: " + msgContainer);
		return error.toJson();
	}

	if (!obs_data_has_user_value(data, "request-type") || !obs_data_has_user_value(data, "message-id")
    ) {
		blog(LOG_ERROR, "missing request parameters");
		ResponseError error("missing request parameters");
		return error.toJson();
	}

	blog(LOG_ERROR, "Data received %s", obs_data_get_json(data));
	QString messageId = obs_data_get_string(data, "message-id");
	
	UseCaseManager::processUseCase(data);
	return Response(messageId.toStdString()).toJson();
}