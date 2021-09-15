#pragma once
#include "../utils/timers.h"
#include "../utils/scene_manager.h"
#include "../plugin-macros.generated.h"
#include "./utils.h"
#include "../requests/include/DisplayImageRequest.hpp"

using namespace requests;

inline void DisplayImage(DisplayImageRequest request)
{
    blog(LOG_INFO, "url to display %s seconds:%d", request.url, request.seconds);
    obs_data_t *settings = obs_data_create();
    obs_data_set_string(settings, "url", request.url);
    obs_data_set_bool(settings, "shutdown", true);
    
    obs_source_t *source = obs_source_create("browser_source", request.messageId.toStdString().c_str(), settings, NULL);
    auto scene_item = add_source_to_current_scene(source);
    center_source(scene_item);

    std::function<void()> func1 = [&]()
        {
            blog(LOG_INFO, "deleting source", request.url);
            obs_sceneitem_remove(scene_item);
        };      

    setTimeOut(request.seconds*1000, func1);
}