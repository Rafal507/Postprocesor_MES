
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "readvtkdata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setComboboxItems(std::string, std::string);
/*    void Mouse_current_pos();
    void Mouse_Pressed();
    void Mouse_Released();
*/
    void on_actionOpen_triggered();

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

signals:
    void getPath(std::string);
    void getComboIndex(int index);
    void getComboIndex_2(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
