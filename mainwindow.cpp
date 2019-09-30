#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <vector>
#include "cnpy.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief MainWindow::on_open_triggered 原文链接：https://blog.csdn.net/zl_95520/article/details/82687556
 */
void MainWindow::on_open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("文件对话框！"),
                                                        "E:",
                                                        tr("图片文件(*png *jpg);;"
                                                           "本本文件(*txt)"));
//    qDebug()<<"filename : "<<fileName;
//    this->ui->canvas->setPic(fileName);
//    this->ui->canvas->setPixmap(*pic);
//    this->ui->canvas->setPixmap(QPixmap(fileName));
    this->ui->canvas->setPic(fileName);
}
void MainWindow::on_saveAs_triggered()
{

}

void MainWindow::on_load_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("文件对话框！"),
                                                    "E:",
                                                    tr("图片文件(*npy *npz);;"
                                                       "本本文件(*txt)"));
    qDebug()<<"filename : "<<fileName;
    try {
       cnpy::NpyArray npy=cnpy::npy_load(fileName.toStdString());
       std::vector<float> coord=npy.as_vec<float>();
       this->ui->canvas->landMarks.clear();
       for(int i=0;i<coord.size()/2;i++){
           this->ui->canvas->landMarks.push_back( QPoint(coord[2*i],coord[2*i+1]));
       }
    } catch (std::exception&e) {
        std::cout<<e.what()<<std::endl;
    }
}