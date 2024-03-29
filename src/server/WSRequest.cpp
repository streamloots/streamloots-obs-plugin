#include <QString>
#include "../plugin-macros.generated.h"
#include "../use-case/include/UseCaseManager.hpp"
#include "../requests/include/RequestBase.hpp"
#include "../responses/include/ResponseError.hpp"
#include "../responses/include/Response.hpp"
#include "./include/WSRequest.hpp"

using namespace std;
using namespace responses;
using namespace requests;
using namespace useCase;
using server::WSRequest;

const string WSRequest::NO_VALIDATION_ERROR = "";

string WSRequest::processMessage(string message)
{
	string msgContainer(message);
	const char *msg = msgContainer.c_str();
	blog(LOG_INFO, "processing %s", msg);

	obs_data_t *data = obs_data_create_from_json(msg);
	string error = validateData(message, data);
	if (error != NO_VALIDATION_ERROR) {
		return error;
	}

	blog(LOG_INFO, "Data received %s", obs_data_get_json(data));
	return UseCaseManager::processUseCase(data).toJson();
}

string WSRequest::validateData(string message, obs_data_t *data)
{
	if (!data) {
		blog(LOG_ERROR, "invalid JSON payload received for %s", message.c_str());
		ResponseError error("invalid JSON payload received for: " + message);
		return error.toJson();
	}

	if (!obs_data_has_user_value(data, "message-id")) {
		blog(LOG_ERROR, "missing message-id");
		ResponseError error("missing message-id");
		return error.toJson();
	}

	if (!obs_data_has_user_value(data, "request-type")) {
		QString messageId = obs_data_get_string(data, "message-id");
		blog(LOG_ERROR, "missing request-type on message: %s", messageId.toStdString().c_str());
		ResponseError error("missing request-type", messageId.toStdString());
		return error.toJson();
	}

	return NO_VALIDATION_ERROR;
}
