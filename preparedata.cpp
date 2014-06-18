#include "preparedata.h"
#include <iostream>
#include <math.h>

PrepareData::PrepareData(ReadVTKData* rvd)
{
    this->rvd = rvd;
}

void PrepareData::findMinMaxCoordinates()
{
    minX = rvd->points[rvd->cells[i].p0].x;
    minY = rvd->points[rvd->cells[i].p0].y;
    maxX = rvd->points[rvd->cells[i].p0].x;
    maxY = rvd->points[rvd->cells[i].p0].y;

    if(rvd->points[rvd->cells[i].p1].x < minX)          // minX
        minX = rvd->points[rvd->cells[i].p1].x;
    else if(rvd->points[rvd->cells[i].p2].x < minX)
        minX = rvd->points[rvd->cells[i].p2].x;
    if(rvd->points[rvd->cells[i].p1].y < minY)          // minY
        minY = rvd->points[rvd->cells[i].p1].y;
    else if(rvd->points[rvd->cells[i].p2].y < minY)
        minY = rvd->points[rvd->cells[i].p2].y;
    if(rvd->points[rvd->cells[i].p1].x > maxX)          // maxX
        maxX = rvd->points[rvd->cells[i].p1].x;
    else if(rvd->points[rvd->cells[i].p2].x > maxX)
        maxX = rvd->points[rvd->cells[i].p2].x;
    if(rvd->points[rvd->cells[i].p1].y > maxY)          // maxY
        maxY = rvd->points[rvd->cells[i].p1].y;
    else if(rvd->points[rvd->cells[i].p2].y > maxY)
        maxY = rvd->points[rvd->cells[i].p2].y;
}

void PrepareData::setOrientation()
{
    if(rvd->points[rvd->cells[i].p0].x == minX && rvd->points[rvd->cells[i].p0].y == minY &&           // Orintation 0
            rvd->points[rvd->cells[i].p1].x == maxX && rvd->points[rvd->cells[i].p1].y == minY &&     ///
            rvd->points[rvd->cells[i].p2].x == maxX && rvd->points[rvd->cells[i].p2].y == maxY)      ////
            orientation[i] = 0;
    else if(rvd->points[rvd->cells[i].p0].x == maxX && rvd->points[rvd->cells[i].p0].y == minY &&      // Orintation 1
            rvd->points[rvd->cells[i].p1].x == maxX && rvd->points[rvd->cells[i].p1].y == maxY &&
            rvd->points[rvd->cells[i].p2].x == minX && rvd->points[rvd->cells[i].p2].y == minY)
            orientation[i] = 1;
    else if(rvd->points[rvd->cells[i].p0].x == maxX && rvd->points[rvd->cells[i].p0].y == maxY &&      // Orintation 2
            rvd->points[rvd->cells[i].p1].x == minX && rvd->points[rvd->cells[i].p1].y == minY &&
            rvd->points[rvd->cells[i].p2].x == maxX && rvd->points[rvd->cells[i].p2].y == minY)
            orientation[i] = 2;
    else if(rvd->points[rvd->cells[i].p0].x == maxX && rvd->points[rvd->cells[i].p0].y == minY &&    //// Orintation 3
            rvd->points[rvd->cells[i].p1].x == maxX && rvd->points[rvd->cells[i].p1].y == maxY &&     ///
            rvd->points[rvd->cells[i].p2].x == minX && rvd->points[rvd->cells[i].p2].y == maxY)        //
            orientation[i] = 3;
    else if(rvd->points[rvd->cells[i].p0].x == maxX && rvd->points[rvd->cells[i].p0].y == maxY &&      // Orintation 4
            rvd->points[rvd->cells[i].p1].x == minX && rvd->points[rvd->cells[i].p1].y == maxY &&
            rvd->points[rvd->cells[i].p2].x == maxX && rvd->points[rvd->cells[i].p2].y == minY)
            orientation[i] = 4;
    else if(rvd->points[rvd->cells[i].p0].x == minX && rvd->points[rvd->cells[i].p0].y == maxY &&      // Orintation 5
            rvd->points[rvd->cells[i].p1].x == maxX && rvd->points[rvd->cells[i].p1].y == minY &&
            rvd->points[rvd->cells[i].p2].x == maxX && rvd->points[rvd->cells[i].p2].y == maxY)
            orientation[i] = 5;
    else if(rvd->points[rvd->cells[i].p0].x == minX && rvd->points[rvd->cells[i].p0].y == minY &&    //// Orintation 6
            rvd->points[rvd->cells[i].p1].x == maxX && rvd->points[rvd->cells[i].p1].y == maxY &&    ///
            rvd->points[rvd->cells[i].p2].x == minX && rvd->points[rvd->cells[i].p2].y == maxY)      //
            orientation[i] = 6;
    else if(rvd->points[rvd->cells[i].p0].x == maxX && rvd->points[rvd->cells[i].p0].y == maxY &&      // Orintation 7
            rvd->points[rvd->cells[i].p1].x == minX && rvd->points[rvd->cells[i].p1].y == maxY &&
            rvd->points[rvd->cells[i].p2].x == minX && rvd->points[rvd->cells[i].p2].y == minY)
            orientation[i] = 7;
    else if(rvd->points[rvd->cells[i].p0].x == minX && rvd->points[rvd->cells[i].p0].y == maxY &&      // Orintation 8
            rvd->points[rvd->cells[i].p1].x == minX && rvd->points[rvd->cells[i].p1].y == minY &&
            rvd->points[rvd->cells[i].p2].x == maxX && rvd->points[rvd->cells[i].p2].y == maxY)
            orientation[i] = 8;
    else if(rvd->points[rvd->cells[i].p0].x == minX && rvd->points[rvd->cells[i].p0].y == minY &&    //   Orintation 9
            rvd->points[rvd->cells[i].p1].x == maxX && rvd->points[rvd->cells[i].p1].y == minY &&    ///
            rvd->points[rvd->cells[i].p2].x == minX && rvd->points[rvd->cells[i].p2].y == maxY)      ////
            orientation[i] = 9;
    else if(rvd->points[rvd->cells[i].p0].x == maxX && rvd->points[rvd->cells[i].p0].y == minY &&      // Orintation 10
            rvd->points[rvd->cells[i].p1].x == minX && rvd->points[rvd->cells[i].p1].y == maxY &&
            rvd->points[rvd->cells[i].p2].x == minX && rvd->points[rvd->cells[i].p2].y == minY)
            orientation[i] = 10;
    else if(rvd->points[rvd->cells[i].p0].x == minX && rvd->points[rvd->cells[i].p0].y == maxY &&      // Orintation 11
            rvd->points[rvd->cells[i].p1].x == minX && rvd->points[rvd->cells[i].p1].y == minY &&
            rvd->points[rvd->cells[i].p2].x == maxX && rvd->points[rvd->cells[i].p2].y == minY)
        orientation[i] = 11;
}

void PrepareData::copyMagnitudeToTexelArray()
{
    switch(orientation[i])
    {
    case 0:
        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p0]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;

        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p1]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;

        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p2]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;
        break;
    case 1:
        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p0]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;

        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p1]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;

        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p2]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;
        break;
    case 2:
        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p0]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;

        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p1]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;

        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p2]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;
        break;
    case 3:
        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p0]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;

        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p1]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;

        texelArray[0][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p2]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;
        break;
    case 4:
        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p0]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;

        texelArray[0][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p1]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;

        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p2]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;
        break;
    case 5:
        texelArray[0][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p0]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;

        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p1]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;

        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p2]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;
        break;
    case 6:
        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p0]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;

        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p1]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;

        texelArray[0][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p2]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;
        break;
    case 7:
        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p0]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;

        texelArray[0][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p1]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;

        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p2]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;
        break;
    case 8:
        texelArray[0][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p0]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;

        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p1]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;

        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p2]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;
        break;
    case 9:
        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p0]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;

        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p1]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;

        texelArray[0][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p2]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;
        break;
    case 10:
        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p0]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;

        texelArray[0][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p1]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;

        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p2]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;
        break;
    case 11:
        texelArray[0][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p0]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;

        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p1]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;

        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->magnitude[rvd->cells[i].p2]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;
        break;
    }
}

void PrepareData::copyScalarsToTexelArray()
{
    switch(orientation[i])
    {
    case 0:
        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p0]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;

        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p1]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;

        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p2]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;
        break;
    case 1:
        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p0]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;

        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p1]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;

        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p2]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;
        break;
    case 2:
        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p0]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;

        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p1]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;

        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p2]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;
        break;
    case 3:
        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p0]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;

        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p1]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;

        texelArray[0][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p2]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;
        break;
    case 4:
        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p0]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;

        texelArray[0][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p1]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;

        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p2]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;
        break;
    case 5:
        texelArray[0][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p0]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;

        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p1]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;

        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p2]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;
        break;
    case 6:
        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p0]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;

        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p1]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;

        texelArray[0][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p2]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;
        break;
    case 7:
        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p0]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;

        texelArray[0][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p1]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;

        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p2]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;
        break;
    case 8:
        texelArray[0][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p0]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;

        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p1]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;

        texelArray[0][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p2]);
        texelArray[0][WIDTH-1][1] = 0;
        texelArray[0][WIDTH-1][2] = (GLubyte)(255 - texelArray[0][WIDTH-1][0]);
        texelArray[0][WIDTH-1][3] = 255;
        break;
    case 9:
        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p0]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;

        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p1]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;

        texelArray[0][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p2]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;
        break;
    case 10:
        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p0]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;

        texelArray[0][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p1]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;

        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p2]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;
        break;
    case 11:
        texelArray[0][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p0]);
        texelArray[0][0][1] = 0;
        texelArray[0][0][2] = (GLubyte)(255 - texelArray[0][0][0]);
        texelArray[0][0][3] = 255;

        texelArray[HEIGHT-1][0][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p1]);
        texelArray[HEIGHT-1][0][1] = 0;
        texelArray[HEIGHT-1][0][2] = (GLubyte)(255 - texelArray[HEIGHT-1][0][0]);
        texelArray[HEIGHT-1][0][3] = 255;

        texelArray[HEIGHT-1][WIDTH-1][0] = (GLubyte)round(rvd->scalars[rvd->cells[i].p2]);
        texelArray[HEIGHT-1][WIDTH-1][1] = 0;
        texelArray[HEIGHT-1][WIDTH-1][2] = (GLubyte)(255 - texelArray[HEIGHT-1][WIDTH-1][0]);
        texelArray[HEIGHT-1][WIDTH-1][3] = 255;
        break;
    }
}

void PrepareData::lineInterpolation()
{
    if(orientation[i] == 0 || orientation[i] == 1 || orientation[i] == 2)
    {
        deltaY1 = (texelArray[0][WIDTH-1][0] - texelArray[HEIGHT-1][WIDTH-1][0]) / deltaH;
        deltaY2 = (texelArray[0][WIDTH-1][0] - texelArray[HEIGHT-1][0][0]) / deltaH;
        for(u = HEIGHT - 2; u > 0; u--)
        {
            texelArray[u][WIDTH-1][0] = texelArray[HEIGHT-1][WIDTH-1][0] + (GLubyte)round(deltaY1 * (HEIGHT - u - 1));
            texelArray[u][WIDTH-1][1] = 0;
            texelArray[u][WIDTH-1][2] = (GLubyte)(255 - texelArray[u][WIDTH-1][0]);
            texelArray[u][WIDTH-1][3] = 255;
            texelArray[u][WIDTH-1-u][0] = texelArray[HEIGHT-1][0][0] + (GLubyte)round(deltaY2 * (HEIGHT - u - 1));
            texelArray[u][WIDTH-1-u][1] = 0;
            texelArray[u][WIDTH-1-u][2] = (GLubyte)(255 - texelArray[u][WIDTH-1-u][0]);
            texelArray[u][WIDTH-1-u][3] = 255;

            ideltaH = u + 1;
            ideltaY = (texelArray[u+1][WIDTH-1][0] - texelArray[u+1][WIDTH-u-2][0]) / ideltaH;
            for(v = WIDTH - u - 1; v < WIDTH - 1; v++)
            {
                texelArray[u+1][v][0] = texelArray[u+1][WIDTH-u-2][0] + (GLubyte)round(ideltaY * (v - (WIDTH - u - 2)));
                texelArray[u+1][v][1] = 0;
                texelArray[u+1][v][2] = (GLubyte)(255 - texelArray[u+1][v][0]);
                texelArray[u+1][v][3] = 255;
            }
        }
    }
    else if(orientation[i] == 3 || orientation[i] == 4 || orientation[i] == 5)
    {
        deltaY1 = (texelArray[HEIGHT-1][WIDTH-1][0] - texelArray[0][WIDTH-1][0]) / deltaH;
        deltaY2 = (texelArray[HEIGHT-1][WIDTH-1][0] - texelArray[0][0][0]) / deltaH;
        for(u = 1; u < HEIGHT - 1; u++)
        {
            texelArray[u][WIDTH-1][0] = texelArray[0][WIDTH-1][0] + (GLubyte)round(deltaY1 * u);
            texelArray[u][WIDTH-1][1] = 0;
            texelArray[u][WIDTH-1][2] = (GLubyte)(255 - texelArray[u][WIDTH-1][0]);
            texelArray[u][WIDTH-1][3] = 255;
            texelArray[u][u][0] = texelArray[0][0][0] + (GLubyte)round(deltaY2 * u);
            texelArray[u][u][1] = 0;
            texelArray[u][u][2] = (GLubyte)(255 - texelArray[u][u][0]);
            texelArray[u][u][3] = 255;

            ideltaH = WIDTH - u;
            ideltaY = (texelArray[u-1][WIDTH-1][0] - texelArray[u-1][u-1][0]) / ideltaH;
            for(v = u; v < WIDTH - 1; v++)
            {
                texelArray[u-1][v][0] = texelArray[u-1][u-1][0] + (GLubyte)round(ideltaY * (v - u + 1));
                texelArray[u-1][v][1] = 0;
                texelArray[u-1][v][2] = (GLubyte)(255 - texelArray[u-1][v][0]);/*(255 - texelArray[u-1][u-1][0] + (ideltaY / ideltaH) * v);*/
                texelArray[u-1][v][3] = 255;
            }
        }
    }
    else if(orientation[i] == 6 || orientation[i] == 7 || orientation[i] == 8)
    {
        deltaY1 = (texelArray[HEIGHT-1][0][0] - texelArray[0][0][0]) / deltaH;
        deltaY2 = (texelArray[HEIGHT-1][0][0] - texelArray[0][WIDTH-1][0]) / deltaH;
        for(u = 1; u < HEIGHT - 1; u++)
        {
            texelArray[u][0][0] = texelArray[0][0][0] + (GLubyte)round(deltaY1 * u);
            texelArray[u][0][1] = 0;
            texelArray[u][0][2] = (GLubyte)(255 - texelArray[u][0][0]);
            texelArray[u][0][3] = 255;
            texelArray[u][WIDTH-u-1][0] = texelArray[0][WIDTH-1][0] + (GLubyte)round(deltaY2 * u);
            texelArray[u][WIDTH-u-1][1] = 0;
            texelArray[u][WIDTH-u-1][2] = (GLubyte)(255 - texelArray[u][WIDTH-u-1][0]);
            texelArray[u][WIDTH-u-1][3] = 255;

            ideltaH = WIDTH - u;
            ideltaY = (texelArray[u-1][WIDTH-u][0] - texelArray[u-1][0][0]) / ideltaH;
            for(v = 1; v < WIDTH - u; v++)
            {
                texelArray[u-1][v][0] = texelArray[u-1][0][0] + (GLubyte)round(ideltaY * v);
                texelArray[u-1][v][1] = 0;
                texelArray[u-1][v][2] = (GLubyte)(255 - texelArray[u-1][v][0]);
                texelArray[u-1][v][3] = 255;
            }
        }
    }
    else if(orientation[i] == 9 || orientation[i] == 10 || orientation[i] == 11)
    {
        deltaY1 = (texelArray[0][0][0] - texelArray[HEIGHT-1][0][0]) / deltaH;
        deltaY2 = (texelArray[0][0][0] - texelArray[HEIGHT-1][WIDTH-1][0]) / deltaH;
        for(u = HEIGHT - 2; u > 0; u--)
        {
            texelArray[u][0][0] = texelArray[HEIGHT-1][0][0] + (GLubyte)round(deltaY1 * (HEIGHT - u - 1));
            texelArray[u][0][1] = 0;
            texelArray[u][0][2] = (GLubyte)(255 -  texelArray[u][0][0]);
            texelArray[u][0][3] = 255;
            texelArray[u][u][0] = texelArray[HEIGHT-1][WIDTH-1][0] + (GLubyte)round(deltaY2 * (HEIGHT - u - 1));
            texelArray[u][u][1] = 0;
            texelArray[u][u][2] = (GLubyte)(255 - texelArray[u][u][0]);
            texelArray[u][u][3] = 255;

            ideltaH = u + 1;
            ideltaY = (texelArray[u+1][u+1][0] - texelArray[u+1][0][0]) / ideltaH;
            for(v = 1; v < u + 1; v++)
            {
                texelArray[u+1][v][0] = texelArray[u+1][0][0] + (GLubyte)round(ideltaY *  v);
                texelArray[u+1][v][1] = 0;
                texelArray[u+1][v][2] = (GLubyte)(255 - texelArray[u+1][v][0]);
                texelArray[u+1][v][3] = 255;
            }
        }
    }
}

void PrepareData::prepareToShow()
{
    magnitudeTexID = new GLuint[rvd->cellsNumber];
    scalarTexID = new GLuint[rvd->cellsNumber];
    orientation = new unsigned int[rvd->cellsNumber];
    deltaH = HEIGHT - 1;

    for(i = 0; i < rvd->cellsNumber; i++)
    {
  //      clearTexelArray();

        findMinMaxCoordinates();
/*
        if(i == 4)
        {
            std::cout<<"p0x: "<<rvd->points[rvd->cells[i].p0].x<<" p0y: "<<rvd->points[rvd->cells[i].p0].y<<std::endl;
            std::cout<<"p1x: "<<rvd->points[rvd->cells[i].p1].x<<" p1y: "<<rvd->points[rvd->cells[i].p1].y<<std::endl;
            std::cout<<"p2x: "<<rvd->points[rvd->cells[i].p2].x<<" p2y: "<<rvd->points[rvd->cells[i].p2].y<<std::endl;
            std::cout<<std::endl;
            std::cout<<"minX: "<<minX<<" "<<"maxX: "<<maxX<<std::endl;
            std::cout<<"minY: "<<minY<<" "<<"maxY: "<<maxY<<std::endl;
            std::cout<<std::endl;
        }
*/
        setOrientation();
        copyMagnitudeToTexelArray();

 /*       if(i == 4)
        {
            std::cout<<"Orientation["<<i<<"]: "<<orientation[i]<<std::endl;

            std::cout<<"Magnitude p0: "<<rvd->magnitude[rvd->cells[i].p0]<<" "<<rvd->cells[i].p0<<std::endl;
            std::cout<<"Magnitude p1: "<<rvd->magnitude[rvd->cells[i].p1]<<" "<<rvd->cells[i].p1<<std::endl;
            std::cout<<"Magnitude p2: "<<rvd->magnitude[rvd->cells[i].p2]<<" "<<rvd->cells[i].p2<<std::endl;

            for(u = 0; u < HEIGHT; u++)
            {
                for(v = 0; v < WIDTH; v++)
                {
                    std::cout<<(int)texelArray[u][v][0]<<" ";
                }
                std::cout<<std::endl;
            }
        }
*/
        lineInterpolation();

/*        if(i == 4)
        {
            std::cout<<std::endl;
            for(u = 0; u < HEIGHT; u++)
            {
                for(v = 0; v < WIDTH; v++)
                {
                    std::cout<<(int)texelArray[u][v][0]<<" ";
                }
                std::cout<<std::endl;
            }
        }

        if(i == 4)
        {
            std::cout<<std::endl;
            for(u = 0; u < HEIGHT; u++)
            {
                for(v = 0; v < WIDTH; v++)
                {
                    std::cout<<(int)texelArray[u][v][2]<<" ";
                }
                std::cout<<std::endl;
            }
        }
*/
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glGenTextures(1, &magnitudeTexID[i]);
        glBindTexture(GL_TEXTURE_2D, magnitudeTexID[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, texelArray);
        glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );


        copyScalarsToTexelArray();
        lineInterpolation();

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glGenTextures(1, &scalarTexID[i]);
        glBindTexture(GL_TEXTURE_2D, scalarTexID[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, texelArray);
        glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
    }
}

/*
void PrepareData::clearTexelArray()
{
    for(u = 0; u < HEIGHT; u++)
    {
        for(v = 0; v < WIDTH; v++)
        {
            texelArray[u][v][0] = 0;
            texelArray[u][v][1] = 0;
            texelArray[u][v][2] = 0;
            texelArray[u][v][3] = 0;
        }
    }
}
*/

