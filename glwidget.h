#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include <readvtkdata.h>
#include <preparedata.h>

struct MyColor
{
    double r, g, b;
};

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void drawWireframeMonoColor();
    void draw();
//    void normal(unsigned int i);

    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);

    void Update ();

    QTimer *timer;

    int x, y;
    bool mouseIsPressed;
    bool mouseIsDragging;
    ReadVTKData *rvd;
    PrepareData *pd;

private:
    double nx, ny, nz;
    int typeOfView;
    int typeOfColoring;
    float zoom;
    MyColor *color;

signals:
 //   void Mouse_Pos();
 //   void Mouse_Pressed();
 //   void Mouse_Released();
    void setCombobox_2(std::string, std::string);

public slots:
    void myTimerSlot();
    void getPathToFile(std::string);
    void getTypeOfView(int index);
    void getTypeOfColoring(int index);

};

#endif // GLWIDGET_H
