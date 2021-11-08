#include "./include/PressKeyRequest.hpp"

using requests::PressKeyRequest;

PressKeyRequest::PressKeyRequest(obs_data_t *request) : RequestBase(request)
{
    keys = obs_data_get_array(metadata, "keys");
}