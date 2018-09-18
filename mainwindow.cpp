#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&this->test,SIGNAL(updateState(QString)),this,SLOT(updateStatus(QString)));
    connect(&this->test,SIGNAL(workFinish(QList<QString>)),this,SLOT(on_finished(QStringList)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(this->ui->lineEdit_nextUrl->text()==QString(""))
    {
        ui->log->append(QString("input nextUrl RegExp!"));
        return;
    }
    if(this->ui->lineEdit_RegData->text()==QString(""))
    {
        ui->log->append(QString("input data RegExp!"));
        return;
    }
    if(this->ui->lineEdit_initUrl->text()==QString(""))
    {
        ui->log->append(QString("input init Url!"));
        return;
    }
    QRegExp reg;
    reg.setPattern(ui->lineEdit_RegData->text());
    this->test.setanalysisDataRegExp(reg);
    reg.setPattern(ui->lineEdit_nextUrl->text());
    this->test.setanalysisNextUrlRegExp(reg);
    this->test.setCurrentUrl(QUrl(ui->lineEdit_initUrl->text()));

    this->test.work();
}

void MainWindow::updateStatus(const QString &msg)
{
    ui->log->append(msg);
}

void MainWindow::on_finished(const QStringList &list)
{

}
