#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <math.h>

using namespace std;

int main(){
    int nx = 30; // number of grid points (domain size)
    int nt = 60; // total time
    float c = 1; //convective speed
    float dx = 2.0 / (nx - 1); // distance between grid points
    float dt = 0.0025; //time step size
    float u[nx]; //intialize the array to hold IC

    //populate IC array
    for(int i = 0; i < nx; i++){ 
        if(i >= 0.5 && i <= 3){
            u[i] = 2;
        }else{
            u[i] = 1;
        }
    }
    //print the initial condition
    printf("Initial u:\n");
    for(int i = 0; i < nx; i++){
        cout << i << ": " << u[i] << endl;
    }

    // loop to update the array
    float un[nx];
    for(int i = 0; i < nt; i++){
        //cout << "Array update" << endl;
        for(int j = 0; j < nx; j++){
            un[j] = u[j];
            //cout << un[j] << endl;
        }
        for(int j = 2; j < nx-1; j++){
            u[j] = un[j] - c * dt / dx * (un[j] - un[j - 1]);
            //cout << u[j] << endl;
        }
    }
    printf("Final u:\n");
    for(int i = 0; i < nx; i++){
        cout << i << ": " << un[i] << endl;
    }
    return 0;
}