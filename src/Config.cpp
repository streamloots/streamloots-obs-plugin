#include <obs-frontend-api.h>

#include <QtCore/QObject>
#include <QtCore/QCryptographicHash>
#include <QtCore/QTime>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>

#define PARAM_MONITORING "MonitoringType"
#define SECTION_NAME "Streamloots"

#include "Config.hpp"

#define QT_TO_UTF8(str) str.toUtf8().constData()

Config::Config() :
	MonitoringType(OBS_MONITORING_TYPE_MONITOR_AND_OUTPUT),
	SettingsLoaded(false)
{
	SetDefaults();
}


void Config::Load()
{
	config_t* obsConfig = GetConfigStore();

	MonitoringType = config_get_int(obsConfig, SECTION_NAME, PARAM_MONITORING);
}

void Config::Save()
{
	config_t* obsConfig = GetConfigStore();

	config_set_int(obsConfig, SECTION_NAME, PARAM_MONITORING, MonitoringType);
	config_save(obsConfig);
}

void Config::SetDefaults()
{
	config_t* obsConfig = GetConfigStore();
	if (obsConfig) {
		config_set_default_int(obsConfig,
			SECTION_NAME, PARAM_MONITORING, OBS_MONITORING_TYPE_MONITOR_AND_OUTPUT);
	}
}

config_t* Config::GetConfigStore()
{
	return obs_frontend_get_profile_config();
}

void Config::MigrateFromGlobalSettings()
{
	config_t* source = obs_frontend_get_global_config();
	config_t* destination = obs_frontend_get_profile_config();
	if(config_has_user_value(source, SECTION_NAME, PARAM_MONITORING)) {
		int value = config_get_int(source, SECTION_NAME, PARAM_MONITORING);
		config_set_int(destination, SECTION_NAME, PARAM_MONITORING, value);
		config_remove_value(source, SECTION_NAME, PARAM_MONITORING);
	}

	config_save(destination);
}
