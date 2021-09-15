#include <obs-data.h>
#include "./include/Response.hpp"

using responses::Response;
using namespace std;

Response::Response(string messageId) {
    this->messageId= messageId.c_str();
    this->success = true;
}

string Response::toJson() {
    obs_data_t* response = obs_data_create();
    obs_data_set_string(response, "message-id", messageId);
	obs_data_set_bool(response, "success", success);
	
	return obs_data_get_json(response);
}