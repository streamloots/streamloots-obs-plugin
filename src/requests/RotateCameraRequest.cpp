#include "./include/RotateCameraRequest.hpp"
#include "./utils/metadata.hpp"

using requests::RotateCameraRequest;

RotateCameraRequest::RotateCameraRequest(obs_data_t *request): RequestBase(request) {
    seconds=getMetadataSeconds(metadata);
}