#pragma once

#include <QString>
#include <QSharedPointer>

#include <obs-frontend-api.h>

#include <util/config-file.h>

class Config {
public:
	Config();
	void Load();
	void Save();
	void SetDefaults();
	config_t *GetConfigStore();

	void MigrateFromGlobalSettings();

	int MonitoringType;
	double Volume;
	bool SettingsLoaded;
};
