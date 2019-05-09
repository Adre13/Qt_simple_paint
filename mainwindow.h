#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "paint_form.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    //void closeEvent(QCloseEvent* event) override;// for future - create check before close

private slots:
    void on_actionopen_triggered();

    void on_actionsave_triggered();

    void on_actionpenWidth_triggered();

    void on_actionPenColor_triggered();

    void on_actionclearImage_triggered();

    void on_actionrectangle_triggered();

    void on_actionellipse_triggered();

    void on_actionline_triggered();

private:
    Ui::MainWindow *ui;

    paint_form* paintArea;
    //QList<QAction *> saveAsActs;

};

#endif // MAINWINDOW_H
