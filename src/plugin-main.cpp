/*
Plugin Name
Copyright (C) <Year> <Developer> <Email Address>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <obs-module.h>
#include <obs-frontend-api.h>
#include <obs-data.h>
#include "plugin-macros.generated.h"
#include <graphics/vec2.h>
#include <iostream>
#include <QString>
#include "WSServer.h"


OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

obs_source_t *create_img_source(){
    obs_data_t *settings = obs_data_create_from_json("{\"url\":\"https:\/\/i.giphy.com\/media\/MFVI64gIopnOTDeeO9\/giphy.webp\"}");
    
    obs_source_t *source = obs_source_create("browser_source", "pepitogrillo", settings, NULL);
    return source;
}


obs_scene_t *get_current_scene(){
    obs_source_t *scene_source = obs_frontend_get_current_scene();
    if(!scene_source){
        blog(LOG_INFO, "No current scene");
    }else{
        blog(LOG_INFO, "current scene found");
        const char *name = obs_source_get_name(scene_source);
        blog(LOG_INFO, "Current scene %s", name);
        obs_scene_t  *scene = obs_scene_from_source(scene_source);
        return scene;
    }
}

obs_sceneitem_t *add_source_to_scene(obs_scene_t *scene, obs_source_t *source){
    blog(LOG_INFO, "adding source to scene");
    obs_sceneitem_t *scene_item = obs_scene_add(scene, source);
    if(!scene_item){
        blog(LOG_INFO, "Cannot add item");
    }

    struct vec2 position =  {0.0f, 1.0f};
    struct vec2 scale =  {2.0f, 2.0f};
    obs_sceneitem_set_pos(scene_item, &position);
    obs_sceneitem_set_scale(scene_item, &scale);
    return scene_item;
}

void create_source(){
    obs_scene_t *scene = get_current_scene();
    if(scene){
        blog(LOG_INFO, "ok scene current");
        obs_source_t *img_source = create_img_source();
        const char *name = obs_source_get_name(img_source);
        blog(LOG_INFO, "New source name  %s", name);
        add_source_to_scene(scene, img_source);
    }
}

bool on_item_iterate(void* privateData, obs_source_t* source){
    obs_scene_t *scene = get_current_scene();
    const char *name = obs_source_get_name(source);
    enum obs_source_type sourceType = obs_source_get_type(source);
    char *typeString ="";
    switch (sourceType) {
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

    if(strcmp(name, "Mic/Aux")==0){
        blog(LOG_INFO, "mutting mic");
        obs_source_set_muted(source, true);
    }
    if(strcmp(name, "Video Capture Device")==0){
        blog(LOG_INFO, "closing camera");
        obs_sceneitem_t *scene_item = obs_scene_sceneitem_from_source(scene, source);
        obs_sceneitem_set_visible(scene_item, false);
        obs_sceneitem_set_visible(scene_item, true);
        obs_source_t *filter = obs_source_get_filter_by_name(source, "Colour Key");
        obs_source_set_enabled(filter, true);
    }
    return true;
}

void iterate_items(){
    blog(LOG_INFO, "loading sources");
    obs_enum_sources(on_item_iterate, NULL);
}


void init_server(){
    WSServer *server = new WSServer();
    server->start(9006);
}


void on_front_loaded(enum obs_frontend_event event, void *private_data){
    if (event == OBS_FRONTEND_EVENT_FINISHED_LOADING) {
        blog(LOG_INFO, "front finished");
        // iterate_items();
        // create_source();

    try{
        init_server();
    }catch(...){
        blog(LOG_INFO, "Cannot start server");
    }
    }
} 

bool obs_module_load(void)
{
    blog(LOG_INFO, "plugin loaded successfully (version %s)", PLUGIN_VERSION);
    obs_frontend_add_event_callback(on_front_loaded, NULL);

    return true;
}

void obs_module_unload()
{
    blog(LOG_INFO, "plugin unloaded");
}
