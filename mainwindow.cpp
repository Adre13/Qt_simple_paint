#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    paintArea = new paint_form(this);
    setCentralWidget(paintArea);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void MainWindow::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());

    if(!fileName.isEmpty())
        paintArea->openImage(fileName);
}

void MainWindow::on_actionsave_triggered()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();

    saveFile(fileFormat);
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{

    QString initialPath = QDir::currentPath() + "/untitled.jpg";

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), initialPath);

    if(fileName.isEmpty())
    {
        return false;
    }else
    {
        paintArea->saveImage(fileName, fileFormat.constData());
        return true;
    }
}

void MainWindow::on_actionpenWidth_triggered()
{
    bool ok;

    int newWidth = QInputDialog::getInt(this, tr("Scribble"), tr("Select pen width:"),
                                        paintArea->penWidth(), 1, 50, 1, &ok);

    if(ok)
        paintArea->setPenWidth(newWidth);
}

void MainWindow::on_actionPenColor_triggered()
{
    QColor newColor = QColorDialog::getColor(paintArea->penColor());

    if(newColor.isValid())
        paintArea->setPenColor(newColor);
}

void MainWindow::on_actionclearImage_triggered()
{
    paintArea->clearImage();
}
