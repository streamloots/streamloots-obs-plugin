#pragma once
#include "../requests/include/RequestBase.hpp"
#include "../requests/include/RequestTypes.hpp"
#include "../requests/include/DisplayImageRequest.hpp"
#include "../requests/include/RotateCameraRequest.hpp"
#include "../requests/include/PressKeyRequest.hpp"
#include "../requests/include/HideCameraRequest.hpp"
#include "./UseCaseManager.h"
#include "./DisplayImage.h"
#include "./RotateCamera.h"
#include "./PressKey.h"
#include "./HideCamera.h"

using namespace requests;

//TODO: use hash https://github.com/Palakis/obs-websocket/blob/bbf4b321d741a5d09edb2497c764f9e6c6580318/src/WSRequestHandler.cpp#L31
void UseCaseManager::processUseCase(obs_data_t *request)
{
    blog(LOG_INFO, "Procesing use case %s", obs_data_get_json(request));

    RequestBase baseRequest(request);

    switch(baseRequest.type) {
        case RequestType::Types::DisplayImageType:
        {
            DisplayImageRequest parsedRequest(request);
            DisplayImage(parsedRequest);
            break;
        }            
        case RequestType::Types::RotateCameraType:
        {
            RotateCameraRequest parsedRequest(request);
            RotateCamera(parsedRequest);
            break;
        }            
        case RequestType::Types::PressKeyType:
        {
            PressKeyRequest parsedRequest(request);
            PressKey(parsedRequest);
            break;
        }            
        case RequestType::Types::HideCameraType:
        {
            HideCameraRequest parsedRequest(request);
            HideCamera(parsedRequest);
            break;
        }            
    }
}