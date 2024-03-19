//1D convection NSE also known as "invisid Burgers' equation"
// it can generate shock waves
// ie can generate discontinuities in the solution from smooth IC
// similar to shock creation at supersonic speeds
// using the forward and backward euler method 

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <math.h>

using namespace std;

int main(){
    int nx = 20;
    int nt = 50;
    float dt = 0.01;
    float dx = 2.0 / (nx - 1);

    float u[nx];
    //populate IC array
    for(int i = 0; i < nx; i++){
        if(i >= 0.5 && i <= 1){
            u[i] = 2;
        }
        else{
            u[i] = 1;
        }
    }

    //print the initial condition
    printf("Initial u:\n");
    for(int i = 0; i < nx; i++){
        cout << i << ": " << u[i] << endl;
    }

    float un[nx];
    for(int it = 1; it < nt; it++){
        for(int i = 0; i < nx; i++){
            un[i] = u[i];
        }
        for(int i = 1; i < nx; i++){
            u[i] = un[i] - un[i]*dt/dx*(un[i] - un[i-1]);
        }
    }

    printf("Final u:\n");
    for(int i = 0; i < nx; i++){
        cout << i << ": " << un[i] << endl;
    }
    return 0;

}