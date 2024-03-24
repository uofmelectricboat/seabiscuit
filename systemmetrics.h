#ifndef SYSTEMMETRICS_H
#define SYSTEMMETRICS_H

#include <QtGlobal>
#include <QByteArray>

#define CANMessageFrames 2
#define CANMessageBytes 8

enum SystemMetrics {
    VCU_SPEED_MPH,
    VCU_BATTERY_CHARGE_PERCENTAGE,
    VCU_BATTERY_TEMPERATURE_DEGREES_C,
    VCU_MOTOR_TEMPERATURE_DEGREES_C,
    VCU_BATTERY_POWER_KW,
    VCU_WATER_STATUS,
    VCU_COOLING_SYSTEM_STATUS,
    VCU_ENGINE_SPEED_RPM
};

float getValue(volatile unsigned char data[CANMessageFrames][CANMessageBytes], SystemMetrics param);

#endif // SYSTEMMETRICS_H
