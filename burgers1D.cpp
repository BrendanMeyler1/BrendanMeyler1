//#include "cuda_runtime.h"
//#include "device_launch_parameters.h"
//#include <iostream> // Include the missing header file

#include <iostream>
#include <math.h>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

int main(){
    int nx = 20;
    int nt = 60;
    double dt = 0.01;
    double vis = 0.05;
    double dx = 2.0f/(nx-1);

    int ipl[nx];
    int iml[nx];
    double x[nx];
    //create auxillary variables for our difference formulas
    for(int i = 1; i < nx; i++){
        ipl[i] = i+1;
        iml[i] = i-1;
        x[i] = (i-1)*dx;
    }

    //intial point and final point, use them to establish periodic boundary conditions
    double phi = 0.0;
    double dphi = 0.0;
    double u[nx];
    for(int i=1; i<nx; i++){
        phi = exp(-pow(x[i],(2/4/vis))) + exp( -pow(x[i]-2*M_PI,(2/4/vis)));

        dphi = -0.5/vis*x[i]*exp(-pow(x[i], 2/4/vis)) - 0.5/vis*(x[i]-2*M_PI)*exp(-pow(x[i]-2*M_PI,2/4/vis));

        u[i] = -2*vis*(dphi/phi) + 4;
    }
    double ua[nx];
    for(int it = 1; it < nt; it++){
        double t = (it-1)*dt;
        for(int i = 1; i < nx; i++){
            phi = exp( -pow(x[i]-4*t, 2/4/vis/(t+1) )) + exp( -pow(x[i]-4*t-2*M_PI,2/4/vis/(t+1)));
            
            dphi = -0.5/vis/(t+1)*( x[i]-4*t) * exp( -pow(x[i]-4*t, 2/4/vis/(t+1))) -0.5/vis/(t+1)*(x[i]-4*t-2*M_PI) * exp( -pow(x[i]-4*t-2*M_PI, 2/4/vis/(t+1)));

            ua[i] = -2*vis*dphi/phi + 4;
        }
        double un[nx];
        for(int j = 0; j < nx; j++){
            un[j] = u[j];
        }
        for(int i = 1; i < nx; i++){
            u[i] = un[i] - un[i]*(dt/dx)*( un[i] - un[iml[i]] ) + vis*dt/pow(dx, 2) * ( un[ipl[i]] - 2*un[i] + un[iml[i]]);
        }
    }
    cout << "Final ipl:\n";
    for(int i = 0; i < nx; i++){
        cout << i << ": " << ipl[i] << endl;
    }
    cout << "Final iml:\n";
    for(int i = 0; i < nx; i++){
        cout << i << ": " << iml[i] << endl;
    }
    cout << "Final x:\n";
    for(int i = 0; i < nx; i++){
        cout << i << ": " << x[i] << endl;
    }
    cout << "Final ua:\n";
    for(int i = 0; i < nx; i++){
        cout << i << ": " << ua[i] << endl;
    }
    // cout << "Final un:\n";
    // for(int i = 0; i < nx; i++){
    //     cout << i << ": " << un[i] << endl;
    // }




    cout << "Final u:\n";
    for(int i = 0; i < nx; i++){
        cout << i << ": " << u[i] << endl;
    }
    
    return 0;
}