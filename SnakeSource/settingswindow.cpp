#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_pushButton_clicked()
{
    emit startGame(ui->checkBox->isChecked(),
                   ui->horizontalSlider->value(),
                   ui->horizontalSlider_2->value());
    hide();
}

void SettingsWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->label_2->setText(QString::number(value));
}

void SettingsWindow::on_horizontalSlider_2_valueChanged(int value)
{
    ui->label_4->setText(QString::number(value));
}
