#ifndef PREPAREDATA_H
#define PREPAREDATA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "readvtkdata.h"

class PrepareData
{
public:
    PrepareData(ReadVTKData* rvd);

    ReadVTKData* rvd;                       // Object which store readed data
    unsigned int* orientation;              // Vector to store information about orientation every cell
    double minX, maxX;
    double minY, maxY;
    static const unsigned int HEIGHT = 32;
    static const unsigned int WIDTH = 32;
    GLubyte texelArray[HEIGHT][WIDTH][4];     //Texel array for magnitude
    GLuint* magnitudeTexID;
    GLuint* scalarTexID;

    void findMinMaxCoordinates();
    void setOrientation();
    void copyMagnitudeToTexelArray();
    void copyScalarsToTexelArray();
    void lineInterpolation();
    void prepareToShow();
    void clearTexelArray();

private:
    unsigned int i, u, v;
    double deltaY1, deltaY2, deltaH, ideltaY, ideltaH;
};

#endif // PREPAREDATA_H
