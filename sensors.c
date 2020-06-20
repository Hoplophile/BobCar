/*
 * sensors.c
 *
 * Created: 20.06.2020 11:49:04
 *  Author: piotr
 */ 

#include "sensors.h"

sr_04 *RR_proximity;
sr_04 *RL_proximity;
sr_04 *FR_proximity;
sr_04 *FL_proximity;

void SENS_Init(){	
	// rear right proximity sensor
	RR_proximity = sensor_new(4, &DDRB, DDB1, &PORTB, PORTB1, &DDRB, DDB2, &PINB, PINB2);
	// rear left proximity sensor
	RL_proximity = sensor_new(4, &DDRC, DDC3, &PORTC, PORTC3, &DDRC, DDC4, &PINC, PINC4);
	// front right proximity sensor
	FR_proximity = sensor_new(4, &DDRD, DDD3, &PORTD, PORTD3, &DDRD, DDD6, &PIND, PIND6);
	// front left proximity sensor
	FL_proximity = sensor_new(4, &DDRB, DDB5, &PORTB, PORTB5, &DDRB, DDB4, &PINB, PINB4);
}

void SENS_CheckForObstacles(int warn_distance, int critical_distance){
	switch(car_state){
		case DRV_FWD:
		case DRV_FWD_L:
		case DRV_FWD_R:
			get_dist_mm(FL_proximity);
			get_dist_mm(FR_proximity);
			CTRL_SendDistance((FL_proximity->_last_distance_mm)/10, (FR_proximity->_last_distance_mm)/10);
			break;
		case DRV_BWD:
		case DRV_BWD_L:
		case DRV_BWD_R:
			get_dist_mm(RL_proximity);
			get_dist_mm(RR_proximity);
			CTRL_SendDistance((RL_proximity->_last_distance_mm)/10, (RR_proximity->_last_distance_mm)/10);
			break;
		default:
			break;
	}
	
	switch (car_state){
		case STOPPED:
			LnS_BuzzerSwitch(OFF);
			break;
		case DRV_FWD:
			if((FL_proximity->_last_distance_mm <= critical_distance) ||
			   (FR_proximity->_last_distance_mm <= critical_distance)){
				POWTR_BlockDrivingForward();
				LnS_BuzzerSwitch(ON);
			} else if((FL_proximity->_last_distance_mm <= warn_distance) ||
					  (FR_proximity->_last_distance_mm <= warn_distance)){
				POWTR_UnblockDrivingForward();
				LnS_BuzzerSwitch(ON);
			} else {
				POWTR_UnblockDrivingForward();
				LnS_BuzzerSwitch(OFF);
			}
			break;
		case DRV_FWD_L:
			if((FL_proximity->_last_distance_mm <= critical_distance) ||
			   (FR_proximity->_last_distance_mm <= critical_distance/2)){
				POWTR_BlockDrivingForward();
				LnS_BuzzerSwitch(ON);
			} else if((FL_proximity->_last_distance_mm <= warn_distance) ||
					  (FR_proximity->_last_distance_mm <= warn_distance/2)){
				POWTR_UnblockDrivingForward();
				LnS_BuzzerSwitch(ON);
			} else {
				POWTR_UnblockDrivingForward();
				LnS_BuzzerSwitch(OFF);
			}
			break;
		case DRV_FWD_R:
			if((FL_proximity->_last_distance_mm <= critical_distance/2) ||
			   (FR_proximity->_last_distance_mm <= critical_distance)){
				POWTR_BlockDrivingForward();
				LnS_BuzzerSwitch(ON);
			} else if((FL_proximity->_last_distance_mm <= warn_distance/2) ||
					  (FR_proximity->_last_distance_mm <= warn_distance)){
				POWTR_UnblockDrivingForward();
				LnS_BuzzerSwitch(ON);
			} else {
				POWTR_UnblockDrivingForward();
				LnS_BuzzerSwitch(OFF);
			}
			break;
		case DRV_BWD:
			if((RL_proximity->_last_distance_mm <= critical_distance) ||
			   (RR_proximity->_last_distance_mm <= critical_distance)){
				POWTR_BlockDrivingBackward();
				LnS_BuzzerSwitch(ON);
			} else if((RL_proximity->_last_distance_mm <= warn_distance) ||
					  (RR_proximity->_last_distance_mm <= warn_distance)){
				POWTR_UnblockDrivingBackward();
				LnS_BuzzerSwitch(ON);
			} else {
				POWTR_UnblockDrivingBackward();
				LnS_BuzzerSwitch(OFF);
			}
			break;
		case DRV_BWD_L:
			if((RL_proximity->_last_distance_mm <= critical_distance) ||
			   (RR_proximity->_last_distance_mm <= critical_distance/2)){
				POWTR_BlockDrivingBackward();
				LnS_BuzzerSwitch(ON);
			} else if((RL_proximity->_last_distance_mm <= warn_distance) ||
					  (RR_proximity->_last_distance_mm <= warn_distance/2)){
				POWTR_UnblockDrivingBackward();
				LnS_BuzzerSwitch(ON);
			} else {
				POWTR_UnblockDrivingBackward();
				LnS_BuzzerSwitch(OFF);
			}
			break;
		case DRV_BWD_R:
			if((RL_proximity->_last_distance_mm <= critical_distance/2) ||
			   (RR_proximity->_last_distance_mm <= critical_distance)){
				POWTR_BlockDrivingBackward();
				LnS_BuzzerSwitch(ON);
			} else if((RL_proximity->_last_distance_mm <= warn_distance/2) ||
					  (RR_proximity->_last_distance_mm <= warn_distance)){
				POWTR_UnblockDrivingBackward();
				LnS_BuzzerSwitch(ON);
			} else {
				POWTR_UnblockDrivingBackward();
				LnS_BuzzerSwitch(OFF);
			}
			break;
		default:
			break;
	}
}