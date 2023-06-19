#include "settings-dialog.h"

#include <QMessageBox>
#include <QComboBox>

#include <obs-module.h>
#include <obs-frontend-api.h>

#include "../plugin-macros.generated.h"
#include "../Config.hpp"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent, Qt::Dialog), ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);

	connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::FormAccepted);

	auto monitoringType = ui->audioMonitoring;

	// TODO: get translations
	monitoringType->addItem("None", (int)OBS_MONITORING_TYPE_NONE);
	monitoringType->addItem("MonitorOnly", (int)OBS_MONITORING_TYPE_MONITOR_ONLY);
	monitoringType->addItem("Both", (int)OBS_MONITORING_TYPE_MONITOR_AND_OUTPUT);

	auto volume = ui->volume;
	volume->setMinimum(0);
	volume->setMaximum(2000);
	volume->setSuffix("%");
}

void SettingsDialog::showEvent(QShowEvent * /*event*/)
{
	auto conf = GetConfig();

	if (conf) {
		auto mt = conf->MonitoringType;
		auto volume = conf->Volume;
		blog(LOG_INFO, "Option from config %d", mt);
		auto idx = ui->audioMonitoring->findData(mt);
		ui->audioMonitoring->setCurrentIndex(idx);

		ui->volume->setValue((int)volume);
		ui->volume->setFixedWidth(100);
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
	if (!conf) {
		return;
	}

	auto idx = ui->audioMonitoring->currentIndex();

	auto volume = ui->volume->value();

	conf->MonitoringType = idx;
	conf->Volume = (int)volume;

	blog(LOG_INFO, "Option from ui %d", idx);

	conf->Save();
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}
