#include "readvtkdata.h"
#include <fstream>
#include <iostream>
#include <mpi.h>
#include <thread>
#include <EnableLoop.h>

ReadVTKData::ReadVTKData()
{
    dataWasReaded = false;
}

void ReadVTKData::readVTKFile(std::string stdstrFileName)
{
    std::ifstream file(stdstrFileName.c_str());
    std::string line;
    if(!file.is_open())
    {
        std::cout<<"File was not opened."<<std::endl;
    }
    else
    {
        std::string strTypeFile = "";
        for(unsigned int i = 0; i < stdstrFileName.length(); i++)           //Get type of file
        {
            if(stdstrFileName[i] == '.')
            {
                strTypeFile += stdstrFileName[i+1];
                strTypeFile += stdstrFileName[i+2];
                strTypeFile += stdstrFileName[i+3];
                break;
            }
        }

        std::getline(file,fileVersion);
        std::getline(file,header);
        std::getline(file,fileFormat);
        file>>line>>datasetStructure;

        //POINTS n dataType
        file>>line>>line>>type;
        std::istringstream(line)>>pointsNumber;
        std::getline(file,line);

        magnitude = new double[pointsNumber];
        points = new Pointd3D[pointsNumber];
        for(unsigned int i = 0; i < pointsNumber; i++)
        {
            std::getline(file,line);
            std::stringstream linestream;
            linestream<<line;
            linestream>>points[i].x>>points[i].y>>points[i].z;
        }

        //CELLS n size
        file>>line>>line;
        std::istringstream(line)>>cellsNumber;
        file>>line;
        std::istringstream(line)>>sizeCellList;
        std::getline(file,line);

        cells = new Cell[cellsNumber];
        for(unsigned int i = 0; i < cellsNumber; i++)
        {
            std::getline(file,line);
            std::stringstream linestream;
            linestream<<line;
            linestream>>cells[i].numberPoints>>cells[i].p0>>cells[i].p1>>cells[i].p2>>cells[i].p3>>cells[i].p4>>cells[i].p5;
        }

        // CELL_TYPES n
        file>>line>>line;
        std::istringstream(line)>>cellTypesNumber;
        for(unsigned int i = 0; i <= cellTypesNumber; i++)
        {
            file>>line;
        }

        //POINT_DATA n
        file>>line;
        std::stringstream(line)>>dataPointsNumber;

        if(strTypeFile == "vtk")
        {
            //SCALARS
            file>>line>>scalar;
            std::getline(file,line);
            std::getline(file,line);
            scalars = new double[dataPointsNumber];
            for(unsigned int i = 0; i < dataPointsNumber; i++)
            {
                std::getline(file,line);
                std::stringstream linestream;
                linestream<<line;
                linestream>>scalars[i];
                std::getline(file,line);
            }

            //VECTORS
            file>>line>>vector;
            std::getline(file,line);
            //vectors = new Pointd3D[dataPointsNumber];
            vecX = new double[dataPointsNumber];
            vecY = new double[dataPointsNumber];
            vecZ = new double[dataPointsNumber];
            for(unsigned int i = 0; i < dataPointsNumber; i++)
            {
                std::getline(file,line);
                std::stringstream linestream1;
                linestream1<<line;
                //linestream1>>vectors[i].x;
                linestream1>>vecX[i];
                std::getline(file,line);
                std::stringstream linestream2;
                linestream2<<line;
                //linestream2>>vectors[i].y;
                linestream1>>vecY[i];
                std::getline(file,line);
                std::stringstream linestream3;
                linestream3<<line;
                //linestream3>>vectors[i].z;
                linestream1>>vecZ[i];
                std::getline(file,line);
            }
        }
        else if(strTypeFile == "vtu")
        {
            //SCALARS
            file>>line>>scalar;
            std::getline(file,line);
            std::getline(file,line);
            scalars = new double[dataPointsNumber];
            for(unsigned int i = 0; i < dataPointsNumber; i++)
            {
                std::getline(file,line);
                std::stringstream linestream;
                linestream<<line;
                linestream>>scalars[i];
            }

            //VECTORS
            file>>line>>vector;
            std::getline(file,line);
            //vectors = new Pointd3D[dataPointsNumber];
            vecX = new double[dataPointsNumber];
            vecY = new double[dataPointsNumber];
            vecZ = new double[dataPointsNumber];
            for(unsigned int i = 0; i < dataPointsNumber; i++)
            {
                std::getline(file,line);
                std::stringstream linestream1;
                linestream1<<line;
                //linestream1>>vectors[i].x>>vectors[i].y>>vectors[i].z;
                linestream1>>vecX[i]>>vecY[i]>>vecZ[i];
            }
        }

        dataWasReaded = true;

        calculateMagnitude();
        findDelta();
 //       createArrayOfImages();



        /*
          for(unsigned int i = 0; i < dataPointsNumber; i++)
          {
              cout<<vectors[i].x<<" "<<vectors[i].y<<" "<<vectors[i].z<<endl;
          }
*/ /*
          for(unsigned int i = 0; i < dataPointsNumber; i++)
          {
              cout<<scalars[i]<<endl;
          }
*/

        /*          for(unsigned int i = 0; i < cellsNumber; i++)
          {
              cout<<cells[i].numberPoints<<" "<<cells[i].p0<<" "<<cells[i].p1<<" "<<cells[i].p2<<" "<<cells[i].p3
                 <<" "<<cells[i].p4<<" "<<cells[i].p5<<endl;
          }
*/
        /*
          cout<<datasetStructure<<endl;
          cout<<pointsNumber<<endl;
          cout<<type<<endl;
 //         cout<<line<<endl;

          cout<<endl;
          for(int i = 0; i < ipointsNumber; i++)
          {
              cout<<points[i].x<<" "<<points[i].y<<" "<<points[i].z<<endl;
          }
*/
        //        pointsNumber;
        //        type;
        /*        while(std::getline(file,line))
        {
            cout<<line<<endl;
        }*/
    }
    file.close();

}

void ReadVTKData::calculateMagnitude()
{
//    double max = sqrt(pow(vectors[0].x,2.0) + pow(vectors[0].y,2.0) + pow(vectors[0].z,2.0));
//    double min = sqrt(pow(vectors[0].x,2.0) + pow(vectors[0].y,2.0) + pow(vectors[0].z,2.0));
    unsigned int i;
    int NP;                 // Number of process
    double *result = new double[pointsNumber];

    std::cout<<"(--RVD--) pointsNumber: "<<pointsNumber<<std::endl;
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &NP);
    printf("ReadVTKData: Nmber of process = %d\r\n", NP);

    //std::cout<<vecX[0]<<std::endl;
    EnableLoop::Enable = true;
    for(i = 1; i < NP; i++)
    {
        MPI_Send(&pointsNumber, 1, MPI_INT, i, 9, MPI_COMM_WORLD);
        MPI_Send(vecX, pointsNumber, MPI_DOUBLE, i, 9, MPI_COMM_WORLD);
        MPI_Send(vecY, pointsNumber, MPI_DOUBLE, i, 9, MPI_COMM_WORLD);
        MPI_Send(vecZ, pointsNumber, MPI_DOUBLE, i, 9, MPI_COMM_WORLD);
    }

    if(NP > 1)
    {
        int mod = pointsNumber % (NP - 1);
        int offset = pointsNumber / (NP - 1);
        for(i = 1; i < NP; i++)
        {
            MPI_Recv(result, pointsNumber, MPI_DOUBLE, i, 9, MPI_COMM_WORLD, &status);
            if(i != (NP - 1))
            {    
                for(int j = (i-1)*offset; j < i*offset; j++)
                {
                    magnitude[j] = result[j];
                }
            }
            else
            {
                for(int j = (i-1)*offset; j < i*offset+mod; j++)
                {
                    magnitude[j] = result[j];
                }
            }
        }
    }
    else
    {
        for(i = 0; i < pointsNumber; i++)
        {

            //magnitude[i] = sqrt(pow(vectors[i].x,2.0) + pow(vectors[i].y,2.0) + pow(vectors[i].z,2.0)) * 255;
            magnitude[i] = sqrt(pow(vecX[i],2.0) + pow(vecY[i],2.0) + pow(vecZ[i],2.0)) * 255;
        }
    }
    EnableLoop::Enable = false;
    delete[] result;
}

void ReadVTKData::findDelta()
{
    minX = points[0].x;
    maxX = points[0].x;
    minY = points[0].y;
    maxY = points[0].y;
    minZ = points[0].z;
    maxZ = points[0].z;
    double maxCor;

    for(unsigned int i = 1; i < pointsNumber; i++)
    {
        if(points[i].x > maxX)
            maxX = points[i].x;
        else if(points[i].x < minX)
            minX = points[i].x;

        if(points[i].y > maxY)
            maxY = points[i].y;
        else if(points[i].y < minY)
            minY = points[i].y;

        if(points[i].z > maxZ)
            maxZ = points[i].z;
        else if(points[i].z < minZ)
            minZ = points[i].z;
    }
    /*
        std::cout<<maxX<<std::endl;
        std::cout<<maxY<<std::endl;
        std::cout<<maxZ<<std::endl;
        std::cout<<minZ<<std::endl;
*/
    deltaX = fabs(minX) + ((fabs(maxX) - fabs(minX)) / 2);
    deltaY = fabs(minY) + ((fabs(maxY) - fabs(minY)) / 2);

    if(fabs(maxX) > fabs(minX))
        deltaX = -deltaX;
    if(fabs(maxY) > fabs(minY))
        deltaY = -deltaY;

    for(unsigned int i = 0; i < pointsNumber; i++)          //Move object to center coordinate system
    {
        points[i].x += deltaX;
        points[i].y += deltaY;
    }

    maxCor = fabs(maxX);
    if(fabs(minX) > maxCor)
        maxCor = fabs(minX);
    if(fabs(maxY) > maxCor)
        maxCor = fabs(maxY);
    if(fabs(minY) > maxCor)
        maxCor = fabs(minY);
    if(maxZ > maxCor)
        maxCor = fabs(maxZ);

    correctZoom = -6.0 - (0.4 * maxCor);

    scalarMin = scalars[0];
    scalarMax = scalars[0];
    for(unsigned int i = 1; i < pointsNumber; i++)
    {
        if(scalars[i] > scalarMax)
            scalarMax = scalars[i];
        else if(scalars[i] < scalarMin)
            scalarMin = scalars[i];
    }

//    std::cout<<scalarMax<<std::endl;
//    std::cout<<scalarMin<<std::endl;

    if(scalarMin < 0)
    {
        double tmp = fabs(scalarMin);
        for(unsigned int i = 0; i < pointsNumber; i++)
        {
            scalars[i] += tmp;
        }
    }
    scalarMax += fabs(scalarMin);
    int k = 1;
    while((scalarMax / k) > 1)
        k++;
    for(unsigned int i = 0; i < pointsNumber; i++)
    {
        scalars[i] = (scalars[i] / k) * 255;
    }
}
