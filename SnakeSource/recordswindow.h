#ifndef RECORDSWINDOW_H
#define RECORDSWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QList>
#include "user.h"

namespace Ui {
class RecordsWindow;
}

class RecordsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RecordsWindow(QWidget *parent = 0);
    ~RecordsWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RecordsWindow *ui;
    QList<User*> players;
};

#endif // RECORDSWINDOW_H
