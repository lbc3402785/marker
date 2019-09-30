#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
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
    this->ui->canvas->setIsPictured(true);
}
void MainWindow::on_saveAs_triggered()
{
    if(this->ui->canvas->getIsLoaded()){
        QFileDialog fileDialog;
           QString fileName = fileDialog.getSaveFileName(this,tr("Open File"),".",tr("binary File(*.npy)"));
           if(fileName == "")
           {
               return;
           }
           QFile file(fileName);
           if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
           {
               QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
               return;
           }
           else
           {
               qDebug()<<fileName;
               QVector<QPoint> points=this->ui->canvas->getPoints();
               size_t n=points.size();
               std::vector<float> out(2*n,0.0f);
               for(size_t i=0;i<n;i++){
                   out[2*i]=points[i].x();
                   out[2*i+1]=points[i].y();
               }
               std::vector<size_t> size(2,0);
               size[0]=n;size[1]=2;
               cnpy::npy_save(fileName.toStdString(),out.data(),size,"w");
               QMessageBox::warning(this,tr("提示"),tr("保存文件成功"));
           }
    }
}

void MainWindow::on_load_triggered()
{
    if(!this->ui->canvas->getIsPictured()){
        QMessageBox::warning(NULL, "warning", "No picture!", QMessageBox::Cancel );
        return;
    }
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("文件对话框！"),
                                                    "E:",
                                                    tr("图片文件(*npy *npz);;"
                                                       "本本文件(*txt)"));
    qDebug()<<"filename : "<<fileName;
    try {
       cnpy::NpyArray npy=cnpy::npy_load(fileName.toStdString());
       std::vector<float> coord=npy.as_vec<float>();
       QVector<QPoint> points;
       for(int i=0;i<coord.size()/2;i++){
           points.push_back( QPoint(coord[2*i],coord[2*i+1]));
       }
       this->ui->canvas->setPoints(points);
       this->ui->canvas->setIsLoaded(true);
    } catch (std::exception&e) {
        std::cout<<e.what()<<std::endl;
    }
}

void MainWindow::on_edit_clicked()
{
    if(this->ui->canvas->getIsLoaded()){
        if(this->ui->canvas->getIsEditing()){
            this->ui->canvas->setIsEditing(false);
            this->ui->load->setDisabled(false);
            this->ui->open->setDisabled(false);
        }else{
            this->ui->canvas->setIsEditing(true);
            this->ui->load->setDisabled(true);
            this->ui->open->setDisabled(true);
        }
    }
}

void MainWindow::on_clear_clicked()
{
    if(this->ui->canvas->getIsEditing()){
        this->ui->canvas->clearPoints();
//        this->ui->load->setDisabled(false);
//        this->ui->open->setDisabled(false);
    }
}

void MainWindow::on_reset_clicked()
{
    if(this->ui->canvas->getIsEditing()){
        this->ui->canvas->resetPoints();
    }
}
