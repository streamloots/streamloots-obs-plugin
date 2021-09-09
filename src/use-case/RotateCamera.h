#pragma once
#include "../utils/timers.h"
#include "../utils/scene_manager.h"
#include "../utils/transforms.h"
#include "../plugin-macros.generated.h"
#include "./utils.h"


inline void rotate_source(const char *name, int seconds)
{

    //TODO calculate coords, duplicate instead of use same source
    auto scene_item = getSceneItemInScene(name);

    obs_data_t *wrapper = obs_scene_save_transform_states(get_current_scene(), true);

    vec3 tl = GetItemTL(scene_item); //Save position, position change on rotation
    obs_sceneitem_set_rot(scene_item, 180);
    SetItemTL(scene_item, tl);

    std::function<void()> func1 = [&]()
    {
        blog(LOG_INFO, "rotating again");
        // obs_sceneitem_set_rot(scene_item, 0); //this reset rotation
        // SetItemTL(scene_item, tl);
        obs_scene_load_transform_states(obs_data_get_json(wrapper)); //this reset transform state, we can use it for more complex iterations
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

    // if (!scene_item)
    // {
    //     blog(LOG_ERROR, "no camera found");
    //     return;
    // }
    // QString name = obs_source_get_name(obs_sceneitem_get_source(scene_item));
    // blog(LOG_INFO, "rotating camera: %s", name);
}