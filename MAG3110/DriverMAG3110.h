//#include <device.h>
#include <stdint.h>

/* Define Constants */

#ifndef DRIVER_MAG3110_H
#define DRIVER_MAG3110_H

/* Device Slave Address */
#define SLAVE_ADDRESS   0x0E

/* Register Address */
#define DR_STATUS   	0x00
#define OUT_X_MSB   	0x01
#define OUT_X_LSB   	0x02
#define OUT_Y_MSB   	0x03
#define OUT_Y_LSB   	0x04
#define OUT_Z_MSB   	0x05
#define OUT_Z_LSB   	0x06
#define WHO_AM_I    	0x07
#define SYSMOD      	0x08
#define OFF_X_MSB   	0x09
#define OFF_X_LSB   	0x0A
#define OFF_Y_MSB   	0x0B
#define OFF_Y_LSB   	0x0C
#define OFF_Z_MSB   	0x0D
#define OFF_Z_LSB 	0x0E
#define DIE_TEMP	0x0F
#define CTRL_REG1 	0x10
#define CTRL_REG2 	0x11

/* Control Register Modes */

/* Control Register 1 */
/*  When implementing functions that alter this register
    so that the setting we want to change are the only ones changed.
    This is done by using the ReadCtrlReg2  and the & functions along with
    the #define that te user wants to change. This way the seetings that
    they dont want to change will not be altered.
*/

/* Over-Sampling Ratio and Data Rate Description Constants */
/*  The folling consants are in the form
    CTR_REG1_V_W_X_Y_Z

    V = Output Rate         wx.yz   ( Hz)
    W = Over Sample Ratio   xyz
    X = ADC Rate            wxyz    (Hz)
    Y = Current Typ         wxy.z   (uA)
    Z = Noise Typ           x.yz    (uT rms)

    All follow the format above.
*/
#define CTRL_REG1_8000_016_1280_9000_040	0x00
#define CTRL_REG1_4000_032_1280_9000_035	0x08
#define CTRL_REG1_2000_064_1280_9000_030	0x10
#define CTRL_REG1_1000_128_1280_9000_025	0x18

#define CTRL_REG1_4000_016_0640_5500_040	0x20
#define CTRL_REG1_2000_032_0640_5500_035	0x28
#define CTRL_REG1_1000_064_0640_5500_030	0x30
#define CTRL_REG1_0500_128_0640_5500_025	0x38

#define CTRL_REG1_2000_016_0320_2750_040	0x40
#define CTRL_REG1_1000_032_0320_2750_035	0x48
#define CTRL_REG1_0500_064_0320_2750_030	0x50
#define CTRL_REG1_0250_128_0320_2750_025	0x58

#define CTRL_REG1_1000_016_0128_1375_040	0x60
#define CTRL_REG1_0500_032_0128_1375_035	0x68
#define CTRL_REG1_0250_064_0128_1375_030	0x70
#define CTRL_REG1_0125_128_0128_1375_025	0x78

#define CTRL_REG1_0500_016_0080_0688_040	0x80
#define CTRL_REG1_0250_032_0080_0688_035	0x88
#define CTRL_REG1_0125_064_0080_0688_030	0x90
#define CTRL_REG1_0063_128_0080_0688_025	0x98

#define CTRL_REG1_0250_016_0080_0344_040	0xA0
#define CTRL_REG1_0125_032_0080_0344_035	0xA8
#define CTRL_REG1_0063_064_0080_0344_030	0xB0
#define CTRL_REG1_0031_128_0080_0344_025	0xB8

#define CTRL_REG1_0125_016_0080_0172_040	0xC0
#define CTRL_REG1_0063_032_0080_0172_035	0xC8
#define CTRL_REG1_0031_064_0080_0172_030	0xD0
#define CTRL_REG1_0016_128_0080_0172_025	0xD8

#define CTRL_REG1_0063_016_0080_0086_040	0xE0
#define CTRL_REG1_0031_032_0080_0086_035	0xE8
#define CTRL_REG1_0016_064_0080_0086_030	0xF0
#define CTRL_REG1_0008_128_0080_0086_025	0xF8

#define CTRL_REG1_FAST_READ_EN 			0x04
#define CTRL_REG1_FAST_READ_NEN			0x00

#define CTRL_REG1_DEFAULT			0x00
#define CTRL_REG1_STANDBY 			0x00
#define CTRL_REG1_CONTINUOUS			0x01
#define CTRL_REG1_SINGLE_MEASURMENT		0x02
#define CTRL_REG1_TRIGGER_MEASURMENT		0x03

/* Control Register 2 */
/*  When implementing functions that alter this register
    so that the setting we want to change are the only ones changed.
    This is done by using the ReadCtrlReg2  and the & functions along with
    the #define that te user wants to change. This way the seetings that
    they dont want to change will not be altered.
*/
#define CTRL_REG2_DEFAULT       	0x00
#define CTRL_REG2_AUTO_MRST_EN  	0x80
#define CTRL_REG2_AUTO_MRST_NEN  0x00
#define CTRL_REG2_RAW_NEN       	0x00
#define CTRL_REG2_RAW_EN        	0x20
#define CTRL_REG2_MAG_RST       	0x10

/* Function Prototypes */
/* Write Functions */
uint8_t WriteOffSetCorrection	(uint16_t *);
uint8_t WriteCtrlReg1		(uint8_t);
uint8_t WriteCtrlReg2		(uint8_t);

/* Set Functions */
uint8_t SetOverSampleAndDataRate(uint8_t);
uint8_t SetStandbyMode		(); 
uint8_t SetCtrlReg1Default	();					
uint8_t SetContinuousMode	(); 			
uint8_t SetSingleMeasurmentMode	();
uint8_t SetTriggerMeasurmentMode();			
uint8_t SetFastReadOn		();
uint8_t SetFastReadOff		();		
uint8_t SetCtrlReg2Default	();
uint8_t SetAutoResetOn		();
uint8_t SetAutoResetOff		();
uint8_t SetUserCorrectedData	();
uint8_t SetRawData		();
uint8_t ResetMag		();

/* Read Functions */
uint8_t ReadDrStatus    	(uint8_t *);
uint8_t ReadMagData    (int16_t *);
uint8_t ReadWhoAmI	(uint8_t *);
uint8_t ReadSysMod      (uint8_t *);
int8_t  ReadDieTep    	(int8_t *);
uint8_t ReadCtrlReg1    (uint8_t *);
uint8_t ReadCtrlReg2    (uint8_t *);

#endif
