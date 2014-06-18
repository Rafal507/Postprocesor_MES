#ifndef READVTKDATA_H
#define READVTKDATA_H

#include <sstream>
#include <QtCore>

struct Pointd3D
{
    double x, y, z;
};

struct Cell
{
    unsigned int numberPoints, p0, p1, p2, p3, p4, p5;
};

class ReadVTKData
{
public:
    ReadVTKData();
    void readVTKFile(std::string stdstrFileName);
    void calculateMagnitude();

    Pointd3D *points;
    Cell *cells;
    double *scalars;
    double *magnitude;
    //Pointd3D *vectors;
    double *vecX;
    double *vecY;
    double *vecZ;
    bool dataWasReaded;

    std::string fileVersion;
    std::string header;
    std::string fileFormat;
    std::string datasetStructure;
    std::string type;
    unsigned int pointsNumber;
    unsigned int cellsNumber;
    unsigned int sizeCellList;
    unsigned int cellTypesNumber;
    unsigned int dataPointsNumber;
    std::string scalar;
    std::string vector;
    float correctZoom;
    double scalarMin, scalarMax;

private:
    void findDelta();

    double deltaX, deltaY;
    double minX, maxX;
    double minY, maxY;
    double minZ, maxZ;

};

#endif // READVTKDATA_H
