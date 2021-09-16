#include "./include/DisplayImageRequest.hpp"
#include "./utils/metadata.hpp"

using requests::DisplayImageRequest;

DisplayImageRequest::DisplayImageRequest(obs_data_t *request): RequestBase(request) {
    url = obs_data_get_string(metadata, "url");
    seconds=getMetadataSeconds(metadata);
}