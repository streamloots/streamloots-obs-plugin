#include "settings-dialog.h"

#include <obs-frontend-api.h>
#include <obs-module.h>
#include <QtWidgets/QMessageBox>
#include <QComboBox>

#include "../Config.hpp"
#include "../plugin-macros.generated.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent, Qt::Dialog),
												  ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);

	connect(ui->buttonBox, &QDialogButtonBox::accepted,
			this, &SettingsDialog::FormAccepted);

	auto monitoringType = ui->audioMonitoring;

	// TODO: get translations
	monitoringType->addItem("None",
							(int)OBS_MONITORING_TYPE_NONE);
	monitoringType->addItem("MonitorOnly",
							(int)OBS_MONITORING_TYPE_MONITOR_ONLY);
	monitoringType->addItem("Both",
							(int)OBS_MONITORING_TYPE_MONITOR_AND_OUTPUT);
}

void SettingsDialog::showEvent(QShowEvent *event)
{
	auto conf = GetConfig();

	if (conf)
	{
		auto mt = conf->MonitoringType;
		blog(LOG_INFO, "Option from config %d", mt);
		auto idx = ui->audioMonitoring->findData(mt);
		ui->audioMonitoring->setCurrentIndex(idx);
	}
}

void SettingsDialog::ToggleShowHide()
{
	if (!isVisible())
		setVisible(true);
	else
		setVisible(false);
}

void SettingsDialog::FormAccepted()
{
	auto conf = GetConfig();
	if (!conf)
	{
		return;
	}

	auto idx = ui->audioMonitoring->currentIndex();
	obs_monitoring_type mt = (obs_monitoring_type)ui->audioMonitoring->itemData(idx).toInt();

	conf->MonitoringType = idx;
	blog(LOG_INFO, "Option from ui %d", idx);
	conf->Save();
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}