#pragma once

#include <string>
#include <obs-data.h>
class WSRequest
{
public:
	static std::string processMessage(std::string message);

private:
	static obs_data_t* successResponse(const char* messageId, obs_data_t* fields = nullptr);
	static obs_data_t* errorResponse(const char* messageId, const char* errorMessage, obs_data_t* additionalFields = nullptr);
	static obs_data_t* buildResponse(const char* messageId, const char*, obs_data_t* fields = nullptr);
	static std::string jsonDataToString(obs_data_t *data);
};