#pragma once

#include <QDialog>

#include "ui_settings-dialog.h"

class SettingsDialog : public QDialog {
	Q_OBJECT

public:
	explicit SettingsDialog(QWidget *parent = 0);
	~SettingsDialog();
	void showEvent(QShowEvent *event);
	void ToggleShowHide();

private Q_SLOTS:
	void FormAccepted();

private:
	Ui::SettingsDialog *ui;
};
