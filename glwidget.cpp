#include "glwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/freeglut.h>
#include <objectrotation.h>
#include <math.h>
#include <iostream>

// User Defined Variables
GLUquadricObj *quadratic;											// Used for Quadric

const float PI2 = 2.0*3.1415926535f;								// PI Squared

Matrix4fT   Transform   = {  1.0f,  0.0f,  0.0f,  0.0f,				// NEW: Final Transform
                             0.0f,  1.0f,  0.0f,  0.0f,
                             0.0f,  0.0f,  1.0f,  0.0f,
                             0.0f,  0.0f,  0.0f,  1.0f };

Matrix3fT   LastRot     = {  1.0f,  0.0f,  0.0f,					// NEW: Last Rotation
                             0.0f,  1.0f,  0.0f,
                             0.0f,  0.0f,  1.0f };

Matrix3fT   ThisRot     = {  1.0f,  0.0f,  0.0f,					// NEW: This Rotation
                             0.0f,  1.0f,  0.0f,
                             0.0f,  0.0f,  1.0f };

ObjectRotation_t ObjectRotation(640.0f, 480.0f);        			// NEW: ObjectRotation Instance
Point2fT         MousePt;												// NEW: Current Mouse Point

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    mouseIsPressed = false;
    mouseIsDragging = false;
    typeOfView = 0;
    typeOfColoring = 0;
    zoom = -6.0f;
    rvd = new ReadVTKData();
    pd = new PrepareData(rvd);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(myTimerSlot()));
}

void GLWidget::initializeGL()
{
    glClearColor (0.35f, 0.35f, 0.4f, 0.5f);                        // Background color
    glColor4f(0.35f, 0.35f, 0.4f,1.0f);
    glClearDepth (1.0f);											// Depth Buffer Setup
    glDepthFunc(GL_LEQUAL);										// The Type Of Depth Testing (Less Or Equal)
    glEnable(GL_DEPTH_TEST);										// Enable Depth Testing
    glShadeModel(GL_FLAT);											// Select Flat Shading (Nice Definition Of Objects)
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);				// Set Perspective Calculations To Most Accurate
    quadratic = gluNewQuadric();                                    // Create A Pointer To The Quadric Object
    gluQuadricNormals(quadratic, GLU_SMOOTH);						// Create Smooth Normals
    gluQuadricTexture(quadratic, GL_TRUE);							// Create Texture Coords

    glMatrixMode(GL_TEXTURE);

  //  glEnable(GL_LIGHTING);											// Enable Lighting
  //  glEnable(GL_COLOR_MATERIAL);									// Enable Color Material

 //   glEnable(GL_LIGHT0);											// Enable Default Light
 //   glEnable(GL_LIGHT1);


 //     float light_diffuse[] = {0.4, 0.4, 0.8, 1.0};
//    float light_position[] = {0.0,-1000.0,0.0,0.0};
//    float light_position1[] = {0.0,0.0,100.0,0.0};
 //     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  //  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
 //   glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

//    float material[] = { 0.5, 0.5, 0.5, 1.0};
 //   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);

//    glEnable(GL_NORMALIZE);
}

void GLWidget::resizeGL(int width, int height)                      // Reshape The Window When It's Moved Or Resized
{
    glViewport(0, 0, width, height);                                // Reset The Current Viewport
    glMatrixMode(GL_PROJECTION);                                    // Select The Projection Matrix
    glLoadIdentity ();												// Reset The Projection Matrix

    if( width < height && width > 0 )
        glFrustum( -0.1, 0.1, -0.1 * height / width, 0.1 * height / width, 0.1, 100.0 );
    else if( width >= height && height > 0 )
        glFrustum( -0.1 * width / height, 0.1 * width / height, -0.1, 0.1, 0.1, 100.0 );

//    gluPerspective(90.0f,(GLfloat)width/(GLfloat)height,1.0f,100.0f);   // Calculate The Aspect Ratio Of The Window
    glMatrixMode(GL_MODELVIEW);                                     // Select The Modelview Matrix
    glLoadIdentity();                                               // Reset The Modelview Matrix

    ObjectRotation.setBounds((GLfloat)width, (GLfloat)height);              //*NEW* Update mouse bounds for objectrotation
}

void GLWidget::Update(/*DWORD milliseconds*/)									// Perform Motion Updates Here
{

 /*   if (isRClicked)													// If Right Mouse Clicked, Reset All Rotations
    {
        Matrix3fSetIdentity(&LastRot);								// Reset Rotation
        Matrix3fSetIdentity(&ThisRot);								// Reset Rotation
        Matrix4fSetRotationFromMatrix3f(&Transform, &ThisRot);		// Reset Rotation
    }
*/
    if (!mouseIsDragging)												// Not Dragging
    {
        if (mouseIsPressed)												// First Click
        {
            this->mouseIsDragging = true;							// Prepare For Dragging
            LastRot = ThisRot;										// Set Last Static Rotation To Last Dynamic One
            ObjectRotation.click(&MousePt);								// Update Start Vector And Prepare For Dragging
        }
    }
    else
    {
        if (mouseIsPressed)												// Still Clicked, So Still Dragging
        {
            Quat4fT     ThisQuat;

            ObjectRotation.drag(&MousePt, &ThisQuat);						// Update End Vector And Get Rotation As Quaternion
            Matrix3fSetRotationFromQuat4f(&ThisRot, &ThisQuat);		// Convert Quaternion Into Matrix3fT
            Matrix3fMulMatrix3f(&ThisRot, &LastRot);				// Accumulate Last Rotation Into This One
            Matrix4fSetRotationFromMatrix3f(&Transform, &ThisRot);	// Set Our Final Transform's Rotation From This One
        }
        else														// No Longer Dragging
            mouseIsDragging = false;
    }
}

void GLWidget::drawWireframeMonoColor()
{
    unsigned int i;
    glLineWidth(1.5f);
    for(i = 0; i < rvd->cellsNumber; i++)
    {
        glBegin(GL_LINE_LOOP);
            glColor3d(0.0,0.0,0.5);
            glVertex3d(rvd->points[rvd->cells[i].p0].x, rvd->points[rvd->cells[i].p0].y, rvd->points[rvd->cells[i].p0].z);
            glVertex3d(rvd->points[rvd->cells[i].p1].x, rvd->points[rvd->cells[i].p1].y, rvd->points[rvd->cells[i].p1].z);
            glVertex3d(rvd->points[rvd->cells[i].p2].x, rvd->points[rvd->cells[i].p2].y, rvd->points[rvd->cells[i].p2].z);
/*            glVertex3d(rvd->points[rvd->cells[i].p0].x, rvd->points[rvd->cells[i].p0].y, rvd->points[rvd->cells[i].p0].z);
            glVertex3d(rvd->points[rvd->cells[i].p3].x, rvd->points[rvd->cells[i].p3].y, rvd->points[rvd->cells[i].p3].z);
            glVertex3d(rvd->points[rvd->cells[i].p4].x, rvd->points[rvd->cells[i].p4].y, rvd->points[rvd->cells[i].p4].z);
            glVertex3d(rvd->points[rvd->cells[i].p5].x, rvd->points[rvd->cells[i].p5].y, rvd->points[rvd->cells[i].p5].z);
            glVertex3d(rvd->points[rvd->cells[i].p3].x, rvd->points[rvd->cells[i].p3].y, rvd->points[rvd->cells[i].p3].z);
            glVertex3d(rvd->points[rvd->cells[i].p5].x, rvd->points[rvd->cells[i].p5].y, rvd->points[rvd->cells[i].p5].z);
            glVertex3d(rvd->points[rvd->cells[i].p2].x, rvd->points[rvd->cells[i].p2].y, rvd->points[rvd->cells[i].p2].z);
            glVertex3d(rvd->points[rvd->cells[i].p1].x, rvd->points[rvd->cells[i].p1].y, rvd->points[rvd->cells[i].p1].z);
            glVertex3d(rvd->points[rvd->cells[i].p4].x, rvd->points[rvd->cells[i].p4].y, rvd->points[rvd->cells[i].p4].z);
 */      glEnd();
    }

}

void GLWidget::draw()
{
    glPointSize(2);
    glLineWidth(1.0f);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    for(unsigned i = 0; i < rvd->cellsNumber; i++)
    {
        switch(typeOfColoring)
        {
        case 0:
            glBindTexture(GL_TEXTURE_2D, pd->scalarTexID[i]);
            break;
        case 1:
            glBindTexture(GL_TEXTURE_2D, pd->magnitudeTexID[i]);
            break;
        default:
            break;
        }

        switch(typeOfView)
        {
        case 0:
            glBegin(GL_POINTS);                                           //Drawing points
            break;
        case 1:
            glBegin(GL_TRIANGLES);                                          //Drawing surface
            break;
        case 2:
            glBegin(GL_TRIANGLES);                                           //Drawing surface with monocolor wireframe
            break;
        case 3:
            glBegin(GL_LINE_LOOP);                                        //Drawing wireframe
            break;
        }

        switch (pd->orientation[i])
        {
        case 0:
            glTexCoord2f(0.0, 1.0);
            glVertex3f(rvd->points[rvd->cells[i].p0].x, rvd->points[rvd->cells[i].p0].y, rvd->points[rvd->cells[i].p0].z);

            glTexCoord2f(1.0, 1.0);
            glVertex3d(rvd->points[rvd->cells[i].p1].x, rvd->points[rvd->cells[i].p1].y, rvd->points[rvd->cells[i].p1].z);

            glTexCoord2f(1.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p2].x, rvd->points[rvd->cells[i].p2].y, rvd->points[rvd->cells[i].p2].z);
            break;
        case 1:
            glTexCoord2f(0.0, 1.0);
            glVertex3f(rvd->points[rvd->cells[i].p2].x, rvd->points[rvd->cells[i].p2].y, rvd->points[rvd->cells[i].p2].z);

            glTexCoord2f(1.0, 1.0);
            glVertex3d(rvd->points[rvd->cells[i].p0].x, rvd->points[rvd->cells[i].p0].y, rvd->points[rvd->cells[i].p0].z);

            glTexCoord2f(1.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p1].x, rvd->points[rvd->cells[i].p1].y, rvd->points[rvd->cells[i].p1].z);
            break;
        case 2:
            glTexCoord2f(0.0, 1.0);
            glVertex3f(rvd->points[rvd->cells[i].p0].x, rvd->points[rvd->cells[i].p0].y, rvd->points[rvd->cells[i].p0].z);

            glTexCoord2f(1.0, 1.0);
            glVertex3d(rvd->points[rvd->cells[i].p1].x, rvd->points[rvd->cells[i].p1].y, rvd->points[rvd->cells[i].p1].z);

            glTexCoord2f(1.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p2].x, rvd->points[rvd->cells[i].p2].y, rvd->points[rvd->cells[i].p2].z);
            break;
        case 3:
            glTexCoord2f(1.0, 1.0);
            glVertex3f(rvd->points[rvd->cells[i].p0].x, rvd->points[rvd->cells[i].p0].y, rvd->points[rvd->cells[i].p0].z);

            glTexCoord2f(1.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p1].x, rvd->points[rvd->cells[i].p1].y, rvd->points[rvd->cells[i].p1].z);

            glTexCoord2f(0.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p2].x, rvd->points[rvd->cells[i].p2].y, rvd->points[rvd->cells[i].p2].z);
            break;
        case 4:
            glTexCoord2f(1.0, 1.0);
            glVertex3f(rvd->points[rvd->cells[i].p2].x, rvd->points[rvd->cells[i].p2].y, rvd->points[rvd->cells[i].p2].z);

            glTexCoord2f(1.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p0].x, rvd->points[rvd->cells[i].p0].y, rvd->points[rvd->cells[i].p0].z);

            glTexCoord2f(0.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p1].x, rvd->points[rvd->cells[i].p1].y, rvd->points[rvd->cells[i].p1].z);
            break;
        case 5:
            glTexCoord2f(1.0, 1.0);
            glVertex3f(rvd->points[rvd->cells[i].p1].x, rvd->points[rvd->cells[i].p1].y, rvd->points[rvd->cells[i].p1].z);

            glTexCoord2f(1.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p2].x, rvd->points[rvd->cells[i].p2].y, rvd->points[rvd->cells[i].p2].z);

            glTexCoord2f(0.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p0].x, rvd->points[rvd->cells[i].p0].y, rvd->points[rvd->cells[i].p0].z);
            break;
        case 6:
            glTexCoord2f(0.0, 1.0);
            glVertex3d(rvd->points[rvd->cells[i].p0].x, rvd->points[rvd->cells[i].p0].y, rvd->points[rvd->cells[i].p0].z);

            glTexCoord2f(1.0, 0.0);
            glVertex3f(rvd->points[rvd->cells[i].p1].x, rvd->points[rvd->cells[i].p1].y, rvd->points[rvd->cells[i].p1].z);

            glTexCoord2f(0.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p2].x, rvd->points[rvd->cells[i].p2].y, rvd->points[rvd->cells[i].p2].z);
            break;
        case 7:
            glTexCoord2f(0.0, 1.0);
            glVertex3d(rvd->points[rvd->cells[i].p2].x, rvd->points[rvd->cells[i].p2].y, rvd->points[rvd->cells[i].p2].z);

            glTexCoord2f(1.0, 0.0);
            glVertex3f(rvd->points[rvd->cells[i].p0].x, rvd->points[rvd->cells[i].p0].y, rvd->points[rvd->cells[i].p0].z);

            glTexCoord2f(0.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p1].x, rvd->points[rvd->cells[i].p1].y, rvd->points[rvd->cells[i].p1].z);
            break;
        case 8:
            glTexCoord2f(0.0, 1.0);
            glVertex3d(rvd->points[rvd->cells[i].p1].x, rvd->points[rvd->cells[i].p1].y, rvd->points[rvd->cells[i].p1].z);

            glTexCoord2f(1.0, 0.0);
            glVertex3f(rvd->points[rvd->cells[i].p2].x, rvd->points[rvd->cells[i].p2].y, rvd->points[rvd->cells[i].p2].z);

            glTexCoord2f(0.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p0].x, rvd->points[rvd->cells[i].p0].y, rvd->points[rvd->cells[i].p0].z);
            break;
        case 9:
            glTexCoord2f(0.0, 1.0);
            glVertex3f(rvd->points[rvd->cells[i].p0].x, rvd->points[rvd->cells[i].p0].y, rvd->points[rvd->cells[i].p0].z);

            glTexCoord2f(1.0, 1.0);
            glVertex3d(rvd->points[rvd->cells[i].p1].x, rvd->points[rvd->cells[i].p1].y, rvd->points[rvd->cells[i].p1].z);

            glTexCoord2f(0.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p2].x, rvd->points[rvd->cells[i].p2].y, rvd->points[rvd->cells[i].p2].z);
            break;
        case 10:
            glTexCoord2f(0.0, 1.0);
            glVertex3f(rvd->points[rvd->cells[i].p2].x, rvd->points[rvd->cells[i].p2].y, rvd->points[rvd->cells[i].p2].z);

            glTexCoord2f(1.0, 1.0);
            glVertex3d(rvd->points[rvd->cells[i].p0].x, rvd->points[rvd->cells[i].p0].y, rvd->points[rvd->cells[i].p0].z);

            glTexCoord2f(0.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p1].x, rvd->points[rvd->cells[i].p1].y, rvd->points[rvd->cells[i].p1].z);
            break;
        case 11:
            glTexCoord2f(0.0, 1.0);
            glVertex3f(rvd->points[rvd->cells[i].p1].x, rvd->points[rvd->cells[i].p1].y, rvd->points[rvd->cells[i].p1].z);

            glTexCoord2f(1.0, 1.0);
            glVertex3d(rvd->points[rvd->cells[i].p2].x, rvd->points[rvd->cells[i].p2].y, rvd->points[rvd->cells[i].p2].z);

            glTexCoord2f(0.0, 0.0);
            glVertex3d(rvd->points[rvd->cells[i].p0].x, rvd->points[rvd->cells[i].p0].y, rvd->points[rvd->cells[i].p0].z);
            break;
        default:
            break;
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    if(typeOfView == 2)
        drawWireframeMonoColor();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();												// Reset The Current Modelview Matrix

    glTranslatef(0.0f,0.0f,this->zoom);                                   // Zoom

    glPushMatrix();													// NEW: Prepare Dynamic Transform
    glMultMatrixf(Transform.M);										// NEW: Apply Dynamic Transform

    if(rvd->dataWasReaded)
    {
        draw();
    }

    glPopMatrix();													// NEW: Unapply Dynamic Transform
    glFlush ();														// Flush The GL Rendering Pipeline
}

void GLWidget::myTimerSlot()
{
    Update();
    paintGL();
    makeCurrent();
    swapBuffers();
}

void GLWidget::getPathToFile(std::string strPath)
{
    if(strPath != "")
    {
        timer->stop();
        rvd->readVTKFile(strPath);
        if(rvd->dataWasReaded)
        {
            zoom = rvd->correctZoom;
            emit setCombobox_2(rvd->scalar,rvd->vector);
            pd->prepareToShow();
            timer->start();
        }
    }
}

void GLWidget::getTypeOfView(int type)
{
    typeOfView = type;
}

void GLWidget::getTypeOfColoring(int type)
{
    typeOfColoring = type;
}

void GLWidget::mouseMoveEvent(QMouseEvent *ev)
{ 
    this->x = ev->x();
    this->y = ev->y();
    MousePt.s.X = ev->x();
    MousePt.s.Y = ev->y();
}

void GLWidget::mousePressEvent(QMouseEvent *)
{
    this->mouseIsPressed = true;
}

void GLWidget::mouseReleaseEvent(QMouseEvent *)
{
    this->mouseIsPressed = false;
}

void GLWidget::wheelEvent(QWheelEvent *ev)
{
    if(ev->angleDelta().y() > 0)
    {
        zoom += 0.2;
    }
    else
    {
        zoom -= 0.2;
    }
}
