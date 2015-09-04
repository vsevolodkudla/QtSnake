#include "recordswindow.h"
#include "ui_recordswindow.h"
#include <QTextStream>

RecordsWindow::RecordsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RecordsWindow)
{
    ui->setupUi(this);
    on_pushButton_clicked();
}

RecordsWindow::~RecordsWindow()
{
    delete ui;
}

bool menshe(User *a, User *b)
{
    return (a->point > b->point);
}

void RecordsWindow::on_pushButton_clicked()
{
    ui->listWidget->clear();
    players.clear();

    QFile file("result.txt");
    if (!file.open(QIODevice::ReadOnly))
        return;
    User *tmp;

    QTextStream out(&file);
    while (!out.atEnd()) {
        tmp = new User;
        out >> tmp->name >> tmp->point;
        players.append(tmp);
    }
    file.close();
    qSort(players.begin(), players.end(), menshe);
    int i = 1;
    for(QList<User*>::iterator iter = players.begin();
        iter != players.end(); iter++)
    {
        QString s;
        s = QString::number(i++) + "\t" + (*iter)->name + "\t" + QString::number((*iter)->point);
        ui->listWidget->addItem(s);
    }
}
