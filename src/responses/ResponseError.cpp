#include <obs-data.h>

#include "./include/ResponseError.hpp"

using responses::ResponseError;
using namespace std;

ResponseError::ResponseError(string error) : Response("")
{
	this->error = error.c_str();
	this->success = false;
}

ResponseError::ResponseError(string error, string messageId) : ResponseError(error)
{
	this->messageId = messageId.c_str();
}

string ResponseError::toJson()
{
	obs_data_t *response = Response::getBaseResponseData();
	obs_data_set_string(response, "error", error);

	return obs_data_get_json(response);
}
