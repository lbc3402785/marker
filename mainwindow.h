#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_triggered();

    void on_saveAs_triggered();

    void on_load_triggered();

    void on_edit_clicked();

    void on_clear_clicked();

    void on_reset_clicked();

    void on_save_clicked();
private:
    Ui::MainWindow *ui;
    QString keyFileName;
};

#endif // MAINWINDOW_H
