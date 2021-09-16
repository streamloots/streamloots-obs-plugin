#pragma once
#include "../requests/include/RequestBase.hpp"
#include "../requests/include/RequestTypes.hpp"
#include "../responses/include/ResponseError.hpp"
#include "./include/UseCaseManager.hpp"
#include "./include/DisplayImage.hpp"
#include "./include/HideCamera.hpp"
#include "./include/PressKey.hpp"
#include "./include/RotateCamera.hpp"


using namespace requests;
using namespace responses;
using namespace useCase;

//TODO: use hash https://github.com/Palakis/obs-websocket/blob/bbf4b321d741a5d09edb2497c764f9e6c6580318/src/WSRequestHandler.cpp#L31
Response UseCaseManager::processUseCase(obs_data_t *request)
{
    blog(LOG_INFO, "Procesing use case %s", obs_data_get_json(request));

    RequestBase baseRequest(request);

    switch(baseRequest.type) {
        case RequestType::Types::DisplayImageType:
        {
            return DisplayImage::invoke(request);
        }            
        case RequestType::Types::RotateCameraType:
        {
            return RotateCamera::invoke(request);
        }            
        case RequestType::Types::PressKeyType:
        {
            return PressKey::invoke(request);
        }            
        case RequestType::Types::HideCameraType:
        {
            return HideCamera::invoke(request);
        }
        default: {
            return ResponseError("unknown request-type", baseRequest.messageId.toStdString());
        }            
    }
}