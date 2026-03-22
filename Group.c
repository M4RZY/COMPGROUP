#include <stdio.h>
#include <Windows.h> // for the Sleep function

void Speeds(double Speed, double Target_Speed); // Prototype Function

int main()
{
    Speeds(80, 30);
    return 0;
}

void Speeds(double Speed, double Target_Speed)
{

    double Time = 0;
    double dt = 0.1; // Setting dt as 0.1 

    double Kp = 0.4; 
    double Ki = 0.01; 
    double Kd = 0.005;

    double Error = 0;       // Initialising Variables
    double Integral = 0;
    double Derivative = 0;

    double Prev_Error = 0;
    double Accel = 0;
    
    double Drag = 0;
    double Res = 0;


if (Speed < Target_Speed) // If we are Accelerating
    {
    while(Speed <= Target_Speed)
        {
        if((int)(Time * 1 + 0.05) % 1 == 0) // To print in second intervals use this
        {printf("Time = %5.1f | Speed = %5f | Error= %5f\n", Time, Speed, Error);}
        
        Error = Target_Speed - Speed;

        Derivative = (Error - Prev_Error)/dt;
    
        Integral += Error;

        Accel = (Kp * Error) + (Ki * Integral) + (Kd * Derivative);

        if(Accel > 8){Accel = 8;}
        else if(Accel < 0){Accel = 0;}

        Res = 0.8*dt;

        Drag = 0.0002*dt;

        Speed = (Speed/(1+Drag*Speed))-Res+Accel;

        Prev_Error = Error;

        Time += dt;

        Sleep(100);
        }
    }

else // If we are not Accelerating then we must be Decelerating 
    {
    while(Speed >= Target_Speed)
        {

        if((int)(Time * 1 + 0.05) % 1 == 0) // To print in second intervals use this
        {printf("Time = %5.1f | Speed = %-10.2f\n", Time, Speed);}

        Res = 0.8*dt;

        Drag = 0.0002*dt;

        Speed = (Speed/(1+Drag*Speed))-Res;

        Time += dt;

        Sleep(100);
        }
    }
}

/*
Excel Print
--------------
printf("%.1f, %.2f, %.2f\n", Time, Speed, Accel); 
Use this instead of the one that is there

*/