#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    speed = 1;
    level = 1;
    maxSizeSnake = 20;
    point = 0;
    iSize = 30;
    countEat = 1;
    bWalls = false;

    connect(&timerGame, SIGNAL(timeout()), this, SLOT(next_step()));



    QPalette palette(MainWindow::palette());
    palette.setColor(backgroundRole(), Qt::black);
    setPalette(palette);

}

void MainWindow::paintEvent(QPaintEvent *pPaintEvent)
{
    QPainter painter(this);
    int iStartX = ui->SceneWidget->x(),
            iStartY = ui->SceneWidget->y();

    if (ui->SceneWidget->geometry().width() <
            ui->SceneWidget->geometry().height())
        iSizeCell = ui->SceneWidget->geometry().width() / iSize;
    else
        iSizeCell = ui->SceneWidget->geometry().height() / iSize;


    painter.setPen(Qt::red);
    painter.drawRect(iStartX, iStartY, (iSize + 1) * iSizeCell,
                     (iSize + 1) * iSizeCell);


    painter.setPen(Qt::green);
    painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
    for(QList<Cell*>::iterator iter = qlEat.begin();iter != qlEat.end(); iter++)
    {
        painter.drawEllipse(iStartX + (*iter)->x * iSizeCell,
                            iStartY + (*iter)->y * iSizeCell,
                            iSizeCell, iSizeCell);
    }

    if(bWalls)
    {
    painter.setPen(Qt::red);
    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    for(QList<Cell*>::iterator iter = qlWall.begin();iter != qlWall.end(); iter++)
    {
        painter.drawRect(iStartX + (*iter)->x * iSizeCell,
                         iStartY + (*iter)->y * iSizeCell,
                         iSizeCell, iSizeCell);
    }
    }

    painter.setPen(Qt::white);
    painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    for (QList<Cell*>::iterator iter = qlSnake.begin(); iter != qlSnake.end(); iter++)
    {
        painter.drawRect(iStartX + (*iter)->x * iSizeCell,
                         iStartY + (*iter)->y * iSizeCell,
                         iSizeCell, iSizeCell);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::next_step()
{
    if( NextCell == 0)
    {

    }else
    {
    bool gameover = false;
    bool noeatapple = true;
    if ((PrevCell.x + NextCell.x == 0
            && PrevCell.y == 0
            && NextCell.y == 0)
            ||
        (PrevCell.y + NextCell.y == 0
         && PrevCell.x == 0
         && NextCell.x == 0))
        NextCell = PrevCell;

    Cell *cHead = new Cell;
    cHead->Add(*qlSnake.begin());
    cHead->Add(&NextCell);

    if(cHead->x >= 0 && cHead->y >= 0 &&
            cHead->x <= iSize && cHead->y <= iSize)
    {
        if(!CellIsFree(cHead))
        {
                gameover = true;
        }
        else
        for(QList<Cell*>::iterator iter = qlEat.begin(); iter != qlEat.end(); iter++)
        {
            if(**iter == *cHead)
            {
                noeatapple = false;
                qlSnake.push_front(cHead);

                delete *iter;
                qlEat.append( new Cell(rand()%iSize, rand()%iSize));
                point += speed*100*(level*1.2);
                if(qlSnake.length()%5 == 0)
                    speed++;
                break;
            }
        }
        if (noeatapple)
        {
            *qlSnake.last() = *cHead;
            qlSnake.move(qlSnake.length()-1,0);
        }
        PrevCell = NextCell;
        if(qlSnake.length() == maxSizeSnake)
        {
            level++;
            speed -= 4;
            qlSnake.clear();
            qlSnake.append(new Cell(rand()%iSize,rand()%iSize));
            PrevCell.x = 0;
            PrevCell.y = 0;
        }
    }
    else
    {
        gameover = true;
    }
    if (gameover)
    {
        QMessageBox msgBox;
        msgBox.setText("Набрана кількість балів: " + QString::number(point));
        msgBox.exec();

        QFile file("result.txt");
        if (!file.open(QIODevice::Append))
            return;
        QTextStream in(&file);
        in << ui->NameLabel->text() << "\t" << point << endl;
        file.close();
        speed = 1;
        point = 0;
        level = 1;
        timerGame.stop();
    }
    else
    {
        timerGame.setInterval(((float)3/(speed+(level*1.2)))*100);
        this->update();
    }
    }
    ui->SpeedLabel->setText(QString::number(speed));
    ui->ScoresLabel->setText(QString::number(point));
    ui->LevelLabel->setText(QString::number(level));
}

void MainWindow::on_NewGButton_clicked()
{
    connect(&sw,SIGNAL(startGame(bool,int,int)),this,SLOT(StartGame(bool,int,int)));
    sw.show();

}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch ( event->key() ) {
        case Qt::Key_Left:
            NextCell.x = -1;
            NextCell.y = 0;
            break;
        case Qt::Key_Up:
            NextCell.x = 0;
            NextCell.y = -1;
            break;
        case Qt::Key_Right:
            NextCell.x = 1;
            NextCell.y = 0;
            break;
        case Qt::Key_Down:
            NextCell.x = 0;
            NextCell.y = 1;
            break;
    }
}

void MainWindow::on_CloseButton_clicked()
{
    close();
}

void MainWindow::on_ChangeNButton_clicked()
{
    if(ui->NameEdit->text() != "")
        ui->NameLabel->setText(ui->NameEdit->text());
}

void MainWindow::on_RecordsButton_clicked()
{
    rw.show();
}

bool MainWindow::CellIsFree(Cell *p)
{
    if(bWalls)
    {
    for(QList<Cell*>::iterator iter = qlWall.begin();
        iter != qlWall.end(); iter++)
    {
        if(**iter == *p)
        {
            return false;
        }
    }
    }
    for(QList<Cell*>::iterator iter = qlSnake.begin();
        iter != qlSnake.end(); iter++)
    {
        if(**iter == *p)
        {
            return false;
        }
    }
    return true;
}

void MainWindow::StartGame(bool onWalls, int size, int eat)
{
    iSize = size;
    bWalls = onWalls;
    countEat = eat;
    qlWall.clear();
    qlEat.clear();
    qlSnake.clear();

    PrevCell.x = 0;
    PrevCell.y = 0;

    if(bWalls)
    {

    int randX = rand()%iSize;
    for (int i = rand()%(iSize/2); i < (iSize/2 + rand()%iSize); i++)
        qlWall.append( new Cell(randX, i));
    int randY = rand()%iSize;
    for (int i = rand()%(iSize/2); i < (iSize/2 + rand()%iSize); i++)
        qlWall.append( new Cell(i, randY));
    randX = rand()%iSize;
    for (int i = rand()%(iSize/2); i < (iSize/2 + rand()%iSize); i++)
        qlWall.append( new Cell(randX, i));
    randY = rand()%iSize;
    for (int i = rand()%(iSize/2); i < (iSize/2 + rand()%iSize); i++)
        qlWall.append( new Cell(i, randY));
    }

    Cell *tmp;
    {
        tmp = new Cell(rand()%iSize, rand()%iSize);
    }while(!CellIsFree(tmp));
    qlSnake.append(tmp);

    while(eat > 0)
    {
        {
            tmp = new Cell(rand()%iSize, rand()%iSize);
        }while(!CellIsFree(tmp));
        qlEat.append(tmp);
        eat--;
    }

    ui->centralWidget->setFocus();
    timerGame.start(((float)3/speed)*100);
}
