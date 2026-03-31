#include <stdio.h>

void Speeds(double Speed, double Target_Speed);  // Prototype Function So main recognises the function.

int main(void)
{
    Speeds(50, 80);                             // Going from 50 km/h to 80 km/h.
    printf("\n");                               // new line to make printing subsequent scenarios neater.
    Speeds(80, 50);
    printf("\n");
    Speeds(120, 80);
    printf("\n");
    Speeds(0, 60);

    return 0;
}

void Speeds(double Speed, double Target_Speed)
{
    double Time = 0.0;               // Setting dt as 0.1
    double dt = 0.1;

    double Resistance = 0.8 * dt;   // constants
    double Drag = 0.0002 * dt;

    double Kp = 0.15;
    double Ki = 0.020;
    double Kd = 0.005;

    double Error = 0.0;            // Initialising Variables
    double Integral = 0.0;
    double Derivative = 0.0;
    double Prev_Error = 0.0;
    double Accel = 0.0;

    int step = 0;
    int printInterval = (int)(1.0 / dt);                                                        // Prints every second not mattter what dt is 

    printf("Initial Speed = %.2f km/h | Target Speed = %.2f km/h\n", Speed, Target_Speed);

    if (Speed < Target_Speed)                                                                   // If current speed is below target, use PID controller to accelerate 
    {
        while (Target_Speed - Speed > 0.05)                                                     // Loop until speed is within 0.05 km/h of target (acceptable tolerance)
        {
            Error = Target_Speed - Speed;                                                       // PID components: error (difference), integral (sum over time), derivative (rate of change)
            Derivative = (Error - Prev_Error) / dt;
            Integral += Error * dt;

            Accel = (Kp * Error) + (Ki * Integral) + (Kd * Derivative);                         // Calculate control output using PID formula

            if (Accel > 8.0) Accel = 8.0;                                                       // Limit accelerator between 0 and 8 as specified in assignment
            if (Accel < 0.0) Accel = 0.0;

            Speed = (Speed / (1 + Drag * Speed)) - Resistance + Accel;                          // Update speed using given car model (includes drag and resistance)

            if (step % printInterval == 0)                                                      // Once the step counter evenly divides into the printing interval it prints out the data
            {
                printf("Time = %-4.1f | Speed = %-6.2f | Accel = %-4.2f | Error = %-6.2f\n",
                    Time, Speed, Accel, Error);
            }

            Prev_Error = Error;                                                                 // set the previous error variable equal to the error so as the next time the loop iterates the previous error will be equal to the old error value 
            Time += dt;
            step++;
        }
    }
    else                                                                                        // If above target, set accelerator to zero (no braking, only drag and resistance act)
    {
        while (Speed - Target_Speed > 0.05)
        {
            Accel = 0.0;
            Speed = (Speed / (1 + Drag * Speed)) - Resistance + Accel;

            if (step % printInterval == 0)                                                      // Once the step counter evenly divides into the printing interval it prints out the data
            {
                printf("Time = %-4.1f | Speed = %-6.2f | Accel = %-4.2f\n",
                    Time, Speed, Accel);
            }

            Time += dt;
            step++;
        }
    }

    printf("Final Time = %.1f s | Final Speed = %.2f km/h\n", Time, Speed);                     // Printing the final time and speed values.
}
