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
#include "server/WSServer.h"

void ___source_dummy_addref(obs_source_t*) {}
void ___sceneitem_dummy_addref(obs_sceneitem_t*) {}
void ___data_dummy_addref(obs_data_t*) {}
void ___data_array_dummy_addref(obs_data_array_t*) {}
void ___output_dummy_addref(obs_output_t*) {}

void ___data_item_dummy_addref(obs_data_item_t*) {}
void ___data_item_release(obs_data_item_t* dataItem) {
	obs_data_item_release(&dataItem);
}

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

WSServer *_server = NULL;


void stop_server() {
    if(_server != nullptr) {
        _server->stop();
    } 
    _server = NULL;
}

void init_server(){
    stop_server();
    _server = new WSServer();
    _server->start(9006);
}


void on_front_loaded(enum obs_frontend_event event, void *private_data){
    if (event == OBS_FRONTEND_EVENT_FINISHED_LOADING) {
        blog(LOG_INFO, "front finished");
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
    stop_server();
    blog(LOG_INFO, "plugin unloaded");
}
