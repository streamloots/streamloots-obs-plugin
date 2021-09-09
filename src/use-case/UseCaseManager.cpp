#pragma once
#include "UseCaseManager.h"
#include <QtCore/QString>
#include "../plugin-macros.generated.h"
#include "./DisplayImage.h"
#include "./RotateCamera.h"
#include "./PressKey.h"
#include "./HideCamera.h"

//TODO: use hash https://github.com/Palakis/obs-websocket/blob/bbf4b321d741a5d09edb2497c764f9e6c6580318/src/WSRequestHandler.cpp#L31
void UseCaseManager::processUseCase(obs_data_t *request)
{
    blog(LOG_ERROR, "Procesing use case %s", obs_data_get_json(request));

    QString methodName = obs_data_get_string(request, "request-type");
    QString messageId = obs_data_get_string(request, "message-id");
    OBSDataAutoRelease metadata = obs_data_get_obj(request, "metadata");

    if (methodName == "display-image")
    {
        DisplayImage(messageId, metadata);
    }
    if (methodName == "rotate-camera")
    {
        RotateCamera(messageId, metadata);
    }
    if (methodName == "press-key")
    {
        PressKey(messageId, metadata);
    }
    if (methodName == "hide-camera")
    {
        HideCamera(messageId, metadata);
    }
}