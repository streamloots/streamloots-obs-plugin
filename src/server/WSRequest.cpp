#include "WSRequest.h"
#include <QtCore/QString>
#include "../plugin-macros.generated.h"
#include "../use-case/UseCaseManager.h"

std::string WSRequest::processMessage(std::string message)
{
	std::string msgContainer(message);
	const char* msg = msgContainer.c_str();

	blog(LOG_INFO, "processing %s", msg);

	OBSDataAutoRelease data = obs_data_create_from_json(msg);
	if (!data) {
		blog(LOG_ERROR, "invalid JSON payload received for %s", msg);
		return jsonDataToString(
			errorResponse(nullptr, "invalid JSON payload")
		);
	}

	if (!obs_data_has_user_value(data, "request-type") || !obs_data_has_user_value(data, "message-id")
    ) {
		return jsonDataToString(
			errorResponse(nullptr, "missing request parameters")
		);
	}

	blog(LOG_ERROR, "Data received %s", obs_data_get_json(data));
	QString methodName = obs_data_get_string(data, "request-type");
	OBSDataAutoRelease params = obs_data_create();
	obs_data_apply(params, data);
	obs_data_unset_user_value(params, "request-type");
	obs_data_unset_user_value(params, "message-id");

	UseCaseManager::processUseCase(data);

	return jsonDataToString(
			successResponse(nullptr, nullptr)
		);
}

obs_data_t* WSRequest::successResponse(const char* messageId, obs_data_t* fields)
{
	return buildResponse(messageId, "ok", fields);
}

obs_data_t* WSRequest::errorResponse(const char* messageId, const char* errorMessage, obs_data_t* additionalFields)
{
	OBSDataAutoRelease fields = obs_data_create();
	if (additionalFields) {
		obs_data_apply(fields, additionalFields);
	}
	obs_data_set_string(fields, "error", errorMessage);
	return buildResponse(messageId, "error", fields);
}

obs_data_t* WSRequest::buildResponse(const char* messageId, const char* status, obs_data_t* fields)
{
	obs_data_t* response = obs_data_create();
	if (messageId) {
		obs_data_set_string(response, "message-id", messageId);
	}
	obs_data_set_string(response, "status", status);

	if (fields) {
		obs_data_apply(response, fields);
	}

	return response;
}

std::string WSRequest::jsonDataToString(obs_data_t *data)
{
	std::string responseString = obs_data_get_json(data);
	return responseString;
}