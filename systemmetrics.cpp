#include "systemmetrics.h"

/*
 * format: "Name|Units|Decimals|Too Low Value|Good Value|Warning Value|Critical Value"
 */
const char *SystemMetricsFormat[] = {
    "Vehicle Speed|MPH|0|0|",
    "Battery Percentage|%|0|",
    "Battery Temperature|°C|0|",
    "Motor Temperature|°C|0|",
    "Power|kW|0|",
    "Water Status|status|0|",
    "Cooling Status|status|0|",
    "Engine Speed|RPM|0|"
};

/*
 * CAN message structure:
 *      name            bytes   type            range               unit
 *  display0 (Frame 0)
 *      frame_number0   1       unsigned int    [0,1]               frame number
 *      mph             1       signed int      [-999,999]          MPH
 *      battery_percent 1       unsigned int    [0,100]             %
 *      battery_temp    1       unsigned int    [0,250]             °C
 *      motor_temp      1       signed int      [-55,200]           °C
 *      output_power    1       unsigned int    [0,999]             kW
 *      water_status    1       unsigned int    [0,1]               good/bad
 *      cooling_status  1       unsigned int    [0,2]               good/warning/bad
 *  display1 (Frame 1)
 *      frame_number1   1       unsigned int    [0,1]               frame number
 *      rpm             4       signed int      [-120000,120000]    RPM
 */

float getValue(volatile unsigned char data[CANMessageFrames][CANMessageBytes], SystemMetrics metric) {
    switch (metric) {
    case VCU_SPEED_MPH:
        return (signed int)(data[0][1]);
    case VCU_BATTERY_CHARGE_PERCENTAGE:
        return (unsigned int)(data[0][2]) * 0.5; // scaled
    case VCU_BATTERY_TEMPERATURE_DEGREES_C:
        return (unsigned int)(data[0][3]);
    case VCU_MOTOR_TEMPERATURE_DEGREES_C:
        return (signed int)(data[0][4]);
    case VCU_BATTERY_POWER_KW:
        return (unsigned int)(data[0][5]);
    case VCU_WATER_STATUS:
        return (unsigned int)(data[0][6]);
    case VCU_COOLING_SYSTEM_STATUS:
        return (unsigned int)(data[0][7]);
    case VCU_ENGINE_SPEED_RPM:
        return (signed int)(
            data[1][1] +(data[1][2] << 8) + (data[1][3] << 16) + (data[1][4] << 24));
    default:
        return -1;
    }
}
