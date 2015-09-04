#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QtGui>
#include "cell.h"
#include "user.h"
#include <QStack>
#include "recordswindow.h"
#include "settingswindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
        void StartGame(bool onWalls, int size, int eat);
protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_NewGButton_clicked();
    void next_step();

    void on_CloseButton_clicked();

    void on_ChangeNButton_clicked();

    void on_RecordsButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer timerGame;
    QList<Cell*> qlSnake;
    QList<Cell*> qlEat;
    QList<Cell*> qlWall;
    QList<User> players;
    Cell NextCell;
    Cell PrevCell;
    int speed;
    int level;
    int maxSizeSnake;
    long point;
    int iSize;
    int iSizeCell;
    int countEat;
    RecordsWindow rw;
    SettingsWindow sw;
    bool bWalls;


    void keyPressEvent( QKeyEvent *event );
    bool CellIsFree(Cell *p);


};

#endif // MAINWINDOW_H
