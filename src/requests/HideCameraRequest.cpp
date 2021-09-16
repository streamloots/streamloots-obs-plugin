#include "./include/HideCameraRequest.hpp"
#include "./utils/metadata.hpp"

using requests::HideCameraRequest;

HideCameraRequest::HideCameraRequest(obs_data_t *request): RequestBase(request) {
    seconds=getMetadataSeconds(metadata);
}