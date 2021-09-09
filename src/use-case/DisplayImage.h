#pragma once
#include "../utils/timers.h"
#include "../utils/scene_manager.h"
#include "../plugin-macros.generated.h"
#include "./utils.h"

inline void DisplayImage(QString messageId, obs_data_t* metadata)
{
    const char* url = obs_data_get_string(metadata, "url");
    auto seconds = getMetadataSeconds(metadata);
    blog(LOG_INFO, "url to display %s seconds:%d", url, seconds);
    obs_data_t *settings = obs_data_create();
    obs_data_set_string(settings, "url", url);
    
    obs_source_t *source = obs_source_create("browser_source", messageId.toStdString().c_str(), settings, NULL);
    auto scene_item = add_source_to_current_scene(source);
    center_source(scene_item);

    std::function<void()> func1 = [&]()
        {
            blog(LOG_INFO, "deleting source", url);
            obs_sceneitem_remove(scene_item);
        };      

    setTimeOut(seconds*1000, func1);
}