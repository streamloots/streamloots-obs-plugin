#include "./include/DisplayVideoRequest.hpp"
#include "./utils/metadata.hpp"

using requests::DisplayVideoRequest;

DisplayVideoRequest::DisplayVideoRequest(obs_data_t *request) : RequestBase(request)
{
	url = obs_data_get_string(metadata, "url");
	seconds = getMetadataSeconds(metadata);
}