/* 
 * File:   temp_regulator.h
 * Author: RaD
 *
 * Created on May 15, 2025, 12:32 PM
 */

#ifndef TEMP_REGULATOR_H
#define	TEMP_REGULATOR_H

#ifdef	__cplusplus
extern "C" {
#endif

enum
{
    TEMP_WARNING_BALANCER,
    TEMP_WARNING_SMPS,
    TEMP_WARNING_BATT_12V,
    TEMP_WARNING_BATT_24V,
} typedef error;

enum
{
    TEMP_BALANCER,
    TEMP_SMPS,
    TEMP_BATT_12V,
    TEMP_BATT_24V,
} typedef temp_sensor;

uint16_t calculate_temp(temp_sensor temp);

#ifdef	__cplusplus
}
#endif

#endif	/* TEMP_REGULATOR_H */

