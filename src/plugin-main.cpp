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

#include "plugin-macros.generated.h"
#include "./Config.hpp"

#include <iostream>

#include <QMainWindow>
#include <QAction>
#include <QTimer>
#include <QString>

#include <obs-module.h>
#include <obs-frontend-api.h>
#include <obs-data.h>

#include <graphics/vec2.h>

#include "./forms/settings-dialog.h"
#include "./server/include/WSServer.h"

using namespace server;

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

WSServer *_server = NULL;
SettingsDialog *settingsDialog = nullptr;
ConfigPtr _config;

void stop_server()
{
	if (_server != nullptr) {
		_server->stop();
	}
	_server = NULL;
}

void init_server()
{
	stop_server();
	_server = new WSServer();
	_server->start();
}

void on_front_loaded(enum obs_frontend_event event, void * /*private_data*/)
{
	if (event == OBS_FRONTEND_EVENT_FINISHED_LOADING) {
		blog(LOG_INFO, "front finished");
		try {
			init_server();
		} catch (...) {
			blog(LOG_INFO, "Cannot start server");
		}
	}
}

void ui()
{
	obs_frontend_push_ui_translation(obs_module_get_string);
	QMainWindow *mainWindow = (QMainWindow *)obs_frontend_get_main_window();
	settingsDialog = new SettingsDialog(mainWindow);
	obs_frontend_pop_ui_translation();

	const char *menuActionText = obs_module_text("Streamloots");
	QAction *menuAction = (QAction *)obs_frontend_add_tools_menu_qaction(menuActionText);
	QObject::connect(menuAction, &QAction::triggered, [] { settingsDialog->ToggleShowHide(); });
}

bool obs_module_load(void)
{
	blog(LOG_INFO, "plugin loaded successfully (version %s)", PLUGIN_VERSION);
	obs_frontend_add_event_callback(on_front_loaded, NULL);
	ui();

	_config = ConfigPtr(new Config());
	_config->MigrateFromGlobalSettings();
	_config->Load();

	return true;
}

void obs_module_unload()
{
	stop_server();
	_config.reset();
	blog(LOG_INFO, "plugin unloaded");
}

ConfigPtr GetConfig()
{
	return _config;
}
