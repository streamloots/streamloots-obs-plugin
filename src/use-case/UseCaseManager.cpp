#pragma once
#include "UseCaseManager.h"
#include <QtCore/QString>
#include "../plugin-macros.generated.h"
#include "./DisplayImage.h"
#include "./RotateCamera.h"
#include "./PressKey.h"
#include "./HideCamera.h"
#include "../requests/include/RequestBase.hpp"
#include "../requests/include/RequestTypes.hpp"

using namespace requests;

//TODO: use hash https://github.com/Palakis/obs-websocket/blob/bbf4b321d741a5d09edb2497c764f9e6c6580318/src/WSRequestHandler.cpp#L31
void UseCaseManager::processUseCase(obs_data_t *request)
{
    blog(LOG_ERROR, "Procesing use case %s", obs_data_get_json(request));

    RequestBase parsedRequest(request);
    QString methodName = obs_data_get_string(request, "request-type");
    QString messageId = obs_data_get_string(request, "message-id");
    OBSDataAutoRelease metadata = obs_data_get_obj(request, "metadata");

    switch(parsedRequest.type) {
        case RequestType::Types::DisplayImageType:
            DisplayImage(messageId, metadata);
            break;
        case RequestType::Types::RotateCameraType:
            RotateCamera(messageId, metadata);
            break;
        case RequestType::Types::PressKeyType:
            PressKey(messageId, metadata);
            break;
        case RequestType::Types::HideCameraType:
            HideCamera(messageId, metadata);
            break;
    }
}