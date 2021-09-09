#pragma once
#include <obs-module.h>
#include <obs-frontend-api.h>
#include <obs-data.h>
#include "../plugin-macros.generated.h"
#include <graphics/vec2.h>
#include <iostream>
#include <QString>

inline obs_source_t *create_img_source()
{
    obs_data_t *settings = obs_data_create_from_json("{\"url\":\"https:\/\/i.giphy.com\/media\/MFVI64gIopnOTDeeO9\/giphy.webp\"}");

    obs_source_t *source = obs_source_create("browser_source", "pepitogrillo", settings, NULL);
    return source;
}

inline obs_scene_t *get_current_scene()
{
    obs_source_t *scene_source = obs_frontend_get_current_scene();
    if (!scene_source)
    {
        blog(LOG_INFO, "No current scene");
        return nullptr;
    }
    else
    {
        blog(LOG_INFO, "current scene found");
        const char *name = obs_source_get_name(scene_source);
        blog(LOG_INFO, "Current scene %s", name);
        obs_scene_t *scene = obs_scene_from_source(scene_source);
        return scene;
    }
}

inline obs_sceneitem_t *add_source_to_scene(obs_scene_t *scene, obs_source_t *source)
{
    blog(LOG_INFO, "adding source to scene");
    obs_sceneitem_t *scene_item = obs_scene_add(scene, source);
    if (!scene_item)
    {
        blog(LOG_INFO, "Cannot add item");
    }

    return scene_item;
}

inline void center_source(obs_sceneitem_t *scene_item)
{
    //#center correctly
    struct vec2 position = {0.0f, 0.0f};
    struct vec2 scale = {2.0f, 2.0f};
    obs_sceneitem_set_pos(scene_item, &position);
    obs_sceneitem_set_scale(scene_item, &scale);
}

inline obs_sceneitem_t *add_source_to_current_scene(obs_source_t *source)
{
    obs_scene_t *scene = get_current_scene();
    if (scene)
    {
        blog(LOG_INFO, "ok scene current");
        const char *name = obs_source_get_name(source);
        blog(LOG_INFO, "New source name  %s", name);
        return add_source_to_scene(scene, source);
    }
    return nullptr;
}

inline void create_source()
{
    obs_scene_t *scene = get_current_scene();
    if (scene)
    {
        blog(LOG_INFO, "ok scene current");
        obs_source_t *img_source = create_img_source();
        const char *name = obs_source_get_name(img_source);
        blog(LOG_INFO, "New source name  %s", name);
        add_source_to_scene(scene, img_source);
    }
}

inline bool on_item_iterate(void *privateData, obs_source_t *source)
{
    obs_scene_t *scene = get_current_scene();
    const char *name = obs_source_get_name(source);
    enum obs_source_type sourceType = obs_source_get_type(source);
    char *typeString = "";
    switch (sourceType)
    {
    case OBS_SOURCE_TYPE_INPUT:
        typeString = "input";
        break;

    case OBS_SOURCE_TYPE_FILTER:
        typeString = "filter";
        break;

    case OBS_SOURCE_TYPE_TRANSITION:
        typeString = "transition";
        break;

    case OBS_SOURCE_TYPE_SCENE:
        typeString = "scene";
        break;

    default:
        typeString = "unknown";
        break;
    }

    const char *id = obs_source_get_id(source);
    blog(LOG_INFO, "source name  %s type %s id %s", name, typeString, id);

    if (strcmp(name, "Mic/Aux") == 0)
    {
        blog(LOG_INFO, "mutting mic");
        obs_source_set_muted(source, true);
    }
    if (strcmp(name, "Video Capture Device") == 0)
    {
        blog(LOG_INFO, "closing camera");
        obs_sceneitem_t *scene_item = obs_scene_sceneitem_from_source(scene, source);
        obs_sceneitem_set_visible(scene_item, false);
        obs_sceneitem_set_visible(scene_item, true);
        obs_source_t *filter = obs_source_get_filter_by_name(source, "Colour Key");
        obs_source_set_enabled(filter, true);
    }
    return true;
}

inline bool isMediaSource(const QString &sourceKind)
{
    return (sourceKind == "vlc_source" || sourceKind == "ffmpeg_source");
}

inline QString getSourceMediaState(obs_source_t *source)
{
    QString mediaState;
    enum obs_media_state mstate = obs_source_media_get_state(source);
    switch (mstate)
    {
    case OBS_MEDIA_STATE_NONE:
        mediaState = "none";
        break;
    case OBS_MEDIA_STATE_PLAYING:
        mediaState = "playing";
        break;
    case OBS_MEDIA_STATE_OPENING:
        mediaState = "opening";
        break;
    case OBS_MEDIA_STATE_BUFFERING:
        mediaState = "buffering";
        break;
    case OBS_MEDIA_STATE_PAUSED:
        mediaState = "paused";
        break;
    case OBS_MEDIA_STATE_STOPPED:
        mediaState = "stopped";
        break;
    case OBS_MEDIA_STATE_ENDED:
        mediaState = "ended";
        break;
    case OBS_MEDIA_STATE_ERROR:
        mediaState = "error";
        break;
    default:
        mediaState = "unknown";
    }
    return mediaState;
}

inline OBSDataArrayAutoRelease getMediaItems()
{
    OBSDataArrayAutoRelease sourcesArray = obs_data_array_create();
    auto iterate = [](void *privateData, obs_source_t *source) -> bool
    {
        obs_data_array_t *sourcesArray = (obs_data_array_t *)privateData;
        QString sourceKind = obs_source_get_id(source);
        OBSDataAutoRelease sourceData = obs_data_create();
        obs_data_set_string(sourceData, "sourceName", obs_source_get_name(source));
        obs_data_set_string(sourceData, "sourceKind", sourceKind.toUtf8());

        // QString mediaState = getSourceMediaState(source);
        // obs_data_set_string(sourceData, "mediaState", mediaState.toUtf8());

        obs_data_array_push_back(sourcesArray, sourceData);
        return true;
    };
    obs_enum_sources(iterate, sourcesArray);
    return sourcesArray;
}

inline void iterate_items()
{
    blog(LOG_INFO, "loading sources");
    obs_enum_sources(on_item_iterate, NULL);
}
