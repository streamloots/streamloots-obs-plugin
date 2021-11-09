#pragma once

#include <obs-frontend-api.h>
#include <QtCore/QString>
#include <QtCore/QSharedPointer>
#include <util/config-file.h>

class Config {
	public:
		Config();
		void Load();
		void Save();
		void SetDefaults();
		config_t* GetConfigStore();
        
		void MigrateFromGlobalSettings();

		int MonitoringType;
		bool SettingsLoaded;
};