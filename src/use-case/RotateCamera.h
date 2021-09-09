#pragma once
#include "../utils/timers.h"
#include "../utils/scene_manager.h"
#include "../plugin-macros.generated.h"
#include "./utils.h"

inline void rotate_source(const char *name, int seconds)
{

    //TODO calculate coords, duplicate instead of use same source
    obs_source_t *source = obs_get_source_by_name(name);
    obs_scene_t *scene = get_current_scene();
    obs_sceneitem_t *scene_item = obs_scene_sceneitem_from_source(scene, source);
    if(!scene_item){
        blog(LOG_INFO, "cannot find item in scene");
        return;
    }
    obs_sceneitem_set_rot(scene_item, 180);

    std::function<void()> func1 = [&]()
    {
        blog(LOG_INFO, "rotating again");
        obs_sceneitem_set_rot(scene_item, 0);
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
        blog(LOG_INFO, "rotating camera: %s %s", name, kind);
        if(kind=="dshow_input"){
            rotate_source(name, seconds);
        }
    }

    // if (!scene_item)
    // {
    //     blog(LOG_ERROR, "no camera found");
    //     return;
    // }
    // QString name = obs_source_get_name(obs_sceneitem_get_source(scene_item));
    // blog(LOG_INFO, "rotating camera: %s", name);
}