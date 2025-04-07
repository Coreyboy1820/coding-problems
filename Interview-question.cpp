#include <stdint.h>
#include <stdio.h>
#include <map>

#define length_of_table 10

struct application_param
{
    float velocity[length_of_table] = {0, 10, 50, 100};
    float chamber_pressure[length_of_table] = {10, 20, 100, 200};
};

float get_cp_from_vel(float velocity, float* velocities, float* chamber_pressures, uint32_t length)
{
    static float last_chamber_pressure = 0.0;
    float ret_val = 0;
    float current_vel = 0, last_vel = 0;
    for(size_t i = 0; i < length; i++)
    {
        current_vel = velocities[i];
        if((current_vel > velocity) && (last_vel <= velocity))
        {
            
            if(i == 0) ret_val = chamber_pressures[i];
            else ret_val = chamber_pressures[i-1];
            last_chamber_pressure = ret_val;
            return ret_val;
        }

        last_vel = current_vel;
    }
    return last_chamber_pressure;
}

void application(application_param params)
{
    float chamber_pressure = get_cp_from_vel(50.0f, params.velocity, params.chamber_pressure, length_of_table);
    printf("%f", chamber_pressure);
}

int main()
{
    application_param params;

    application(params);

    printf("%X\n", 1);
    return 1;
}