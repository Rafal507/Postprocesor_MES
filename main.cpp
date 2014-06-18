#include "mainwindow.h"
#include <QApplication>
#include <mpi.h>
#include <thread>
#include <iostream>
#include <math.h>
#include <vector>
#include <EnableLoop.h>

#define MASTER 0


void calculate(int rank, int tid, int offset, int NT, double *magnitude, double *vecX, double* vecY, double* vecZ)
{
    int TMod = offset % NT;
    int TOffset = (int)(offset / NT);
    int begin = (rank - 1) * offset + tid * TOffset;
    int end;
    if(tid == (NT - 1))
        end = (rank - 1) * offset + (tid + 1) * TOffset + TMod;
    else
        end = (rank - 1) * offset + (tid + 1) * TOffset;
    std::cout<<"rank: "<<rank<<" tid: "<<tid<<" offset: "<<offset<<" NT: "<<NT<<" TMod: "<<TMod<<" TOffset: "<<TOffset<<" begin: "<<begin<<" end: "<<end<<std::endl;
    for(int i = begin; i < end; i++)
    {
        magnitude[i] = sqrt(vecX[i]*vecX[i] + vecY[i]*vecY[i] + vecZ[i]*vecZ[i]) * 255;
    }
}

void modCalculate(int rank, int tid, int offset, int NT, int mod, double *magnitude, double *vecX, double* vecY, double* vecZ)
{
    int TMod = (offset + mod) % NT;
    int TOffset = (int)((offset + mod) / NT);
    int begin = (rank - 1) * offset + tid * TOffset;
    int end;
    if(tid == (NT - 1))
        end = (rank - 1) * offset + (tid + 1) * TOffset + TMod;
    else
        end = (rank - 1) * offset + (tid + 1) * TOffset;
    std::cout<<"rank: "<<rank<<" tid: "<<tid<<" offset: "<<offset<<" NT: "<<NT<<" mod: "<<mod<<" TMod: "<<TMod<<" TOffset: "<<TOffset<<" begin: "<<begin<<" end: "<<end<<std::endl;
    for(int i = begin; i < end; i++)
    {
        magnitude[i] = sqrt(vecX[i]*vecX[i] + vecY[i]*vecY[i] + vecZ[i]*vecZ[i]) * 255;
    }
}

void wypisz(int tid, int tid2)
{
    std::cout<<"THREAD: "<<tid<<" "<<tid2<<std::endl;
}

bool EnableLoop::Enable = true;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    int rank, r = 1;
    int offset, mod, pointsNumber, numberOfProcess;
    int namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    unsigned int NT;                            //Threads number


    MPI_Init(&argc,&argv);
    printf("(main) Hello MPI\r\n");
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcess);
    printf("(main) Number of processor = %d\r\n", numberOfProcess);
    MPI_Get_processor_name(processor_name, &namelen);
    printf("(main) Process Name = %s\r\n", processor_name);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("(main) Process rank: %d\r\n", rank);

    if(rank != MASTER){
        MPI_Status status;
        int rr = 1;
        while(rr != 0){

            MPI_Recv(&pointsNumber, 1, MPI_INT, 0, 9, MPI_COMM_WORLD, &status);

            double *vecX = new double[pointsNumber];
            double *vecY = new double[pointsNumber];
            double *vecZ = new double[pointsNumber];

            MPI_Recv(vecX, pointsNumber, MPI_DOUBLE, 0, 9, MPI_COMM_WORLD, &status);
            MPI_Recv(vecY, pointsNumber, MPI_DOUBLE, 0, 9, MPI_COMM_WORLD, &status);
            MPI_Recv(vecZ, pointsNumber, MPI_DOUBLE, 0, 9, MPI_COMM_WORLD, &status);

            double *magnitude = new double[pointsNumber];

            /**
            *Wyznaczenie offsetu
            */
            mod = pointsNumber % (numberOfProcess - 1);
            offset = (int)(pointsNumber / (numberOfProcess - 1));
            std::cout<<"(--main--) pointsNumber: "<<pointsNumber<<" offset: "<<offset<<std::endl;

            /**
            *Pobranie liczby wątków procesora
            */
            NT = std::thread::hardware_concurrency();
            std::cout<<NT<<" concurrent threads are supported.\n";
            std::vector<std::thread> threads;

            /**
            *Wykonanie obliczeń
            */
            if(rank != (numberOfProcess - 1))
            {
                for(int i = 0; i < NT; i++){
                    threads.push_back(std::thread(calculate, rank, i, offset, NT, magnitude, vecX, vecY, vecZ));
                }
                for (int i = 0; i < NT; i++){
                    threads[i].join();
                }
                MPI_Send(magnitude, pointsNumber, MPI_DOUBLE, 0, 9, MPI_COMM_WORLD);
            }
            else
            {
                for(int i = 0; i < NT; i++){
                    threads.push_back(std::thread(modCalculate, rank, i, offset, NT, mod, magnitude, vecX, vecY, vecZ));
                }
                for (int i = 0; i < NT; i++){
                    threads[i].join();
                }
                MPI_Send(magnitude, pointsNumber, MPI_DOUBLE, 0, 9, MPI_COMM_WORLD);
            }
            delete[] vecX;
            delete[] vecY;
            delete[] vecZ;
            delete[] magnitude;

       }
        printf("(main) Process rank : %d\n\n", rank);
        MPI_Recv(&rr, 1, MPI_INT, 0, 9, MPI_COMM_WORLD, &status);
    }

    if(rank == MASTER){
        printf("(main) Process rank: %d\n\n", rank);
        w.show();

        r = a.exec();

        for(int i = 1; i < numberOfProcess; i++){
            MPI_Send(&r, 1, MPI_INT, i, 9, MPI_COMM_WORLD);
        }

    }
    MPI_Finalize();

    return r;
}
