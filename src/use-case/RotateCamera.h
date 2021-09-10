#pragma once
#include "../utils/timers.h"
#include "../utils/scene_manager.h"
#include "../utils/transforms.h"
#include "../plugin-macros.generated.h"
#include "./utils.h"


inline void rotate_source(const char *name, int seconds)
{
    obs_source_t *source = obs_get_source_by_name(name);
    obs_source_set_async_rotation(source, 180);

    std::function<void()> func1 = [&]()
    {
        blog(LOG_INFO, "restoring rotation");
        blog(LOG_INFO, "rotating source: %s", name);
        obs_source_t *source = obs_get_source_by_name(name);
        obs_source_set_async_rotation(source, 0);
    };

    setTimeOut(seconds * 1000, func1);
}

inline void RotateCamera(QString messageId, obs_data_t *metadata)
{
    OBSDataArrayAutoRelease items = getMediaItems();
    int seconds = getMetadataSeconds(metadata);
    for (int i = 0; i < obs_data_array_count(items); i++)
    {
        OBSDataAutoRelease item = obs_data_array_item(items, i);
        auto name = obs_data_get_string(item, "sourceName");
        QString kind = obs_data_get_string(item, "sourceKind");
        if(kind=="dshow_input"){
            blog(LOG_INFO, "rotating camera: %s %s", name, kind);
            rotate_source(name, seconds);
        }
    }
}