#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    connect(ui->widget, SIGNAL(Mouse_Pos()), this, SLOT(Mouse_current_pos()));
//    connect(ui->widget, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed()));
//    connect(ui->widget, SIGNAL(Mouse_Released()), this, SLOT(Mouse_Released()));
    connect(ui->widget, SIGNAL(setCombobox_2(std::string,std::string)), this, SLOT(setComboboxItems(std::string,std::string)));
    connect(this, SIGNAL(getPath(std::string)), ui->widget, SLOT(getPathToFile(std::string)));
    connect(this, SIGNAL(getComboIndex(int)), ui->widget, SLOT(getTypeOfView(int)));
    connect(this, SIGNAL(getComboIndex_2(int)), ui->widget, SLOT(getTypeOfColoring(int)));
}


MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::setComboboxItems(std::string scalar,std::string vector)
{
    QString qstrScalar = QString::fromStdString(scalar);
    QString qstrVector = QString::fromStdString(vector);
    ui->comboBox_2->setItemText(0,qstrScalar);
    ui->comboBox_2->setItemText(1,qstrVector);
}

void MainWindow::on_actionOpen_triggered()
{
    // Select file
    QString fileNameVTK = QFileDialog::getOpenFileName(this,tr("Open File"),QDir::currentPath(),tr("VTK Files (*.vtk);;VTU Files (*.vtu)"));
    std::string stdstrFileNameVTK = fileNameVTK.toUtf8().constData();
    emit getPath(stdstrFileNameVTK);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    emit getComboIndex(index);
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    emit getComboIndex_2(index);
}
