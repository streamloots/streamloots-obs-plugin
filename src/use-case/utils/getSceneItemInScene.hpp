#pragma once
#include <obs-module.h>

inline obs_sceneitem_t *getSceneItemInScene(const char *name)
{
	obs_source_t *source = obs_get_source_by_name(name);
	obs_scene_t *scene = get_current_scene();
	obs_sceneitem_t *scene_item = obs_scene_sceneitem_from_source(scene, source);
	return scene_item;
}