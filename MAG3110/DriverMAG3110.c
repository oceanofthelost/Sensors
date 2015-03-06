#include <stdint.h>
#include "DriverMAG3110.h"

extern uint8_t MagWriteByte			(uint8_t,uint8_t);
extern uint8_t MagWriteMultipleBytes(uint8_t,uint8_t *,uint8_t);
extern uint8_t MagReadByte			(uint8_t,uint8_t *);
extern uint8_t MagReadMultipleByte	(uint8_t,uint8_t *,uint8_t);

static uint8_t SetReg1(uint8_t mask, uint8_t constant)
{
	uint8_t currentReg1Flags;
	ReadCtrlReg1(&currentReg1Flags);

	currentReg1Flags &= constant; 
	currentReg1Flags |= mask; 
	
	return WriteCtrlReg1(currentReg1Flags);
}

static uint8_t SetReg2(uint8_t mask, uint8_t constant)
{
	uint8_t currentReg2Flags;
	ReadCtrlReg1(&currentReg2Flags);

	currentReg2Flags &= constant;
	currentReg2Flags |= mask; 

	return WriteCtrlReg2(currentReg2Flags);
}

uint8_t SetOverSampleAndDataRate(uint8_t CONSTANT)
{
	
	uint8_t currentReg1Flags;
	ReadCtrlReg1(&currentReg1Flags);

	currentReg1Flags &= 0x07; 
	currentReg1Flags |= CONSTANT; 

	return WriteCtrlReg1(currentReg1Flags);
}

uint8_t ReadMagData(int16_t *readPtr)
{
    uint8_t readBuffer[6] = {0};
    uint8_t *readLocalPtr = readBuffer;

    MagReadMultipleByte(OUT_X_MSB, readLocalPtr,6);
    for (uint8_t i = 0; i <= 2; ++i)
    {
    	readPtr[i] = (readBuffer[i * 2] << 8) | readBuffer[i * 2 + 1];
    }

    return 0;
}

uint8_t WriteOffsetCorrection(uint16_t *offsetData)
{

    uint8_t writeData[6] = {0};
    uint8_t *writePtr = writeData;

    for (uint8_t i = 0; i < 3; i++)
    {
        writeData[i] = offsetData[i] >> 8;
        writeData[i + 1] = offsetData[i] << 8;
    }
    
    return MagWriteMultipleBytes(OFF_X_MSB, writePtr, 6);
}

static uint8_t AutoResetToggle(uint8_t mask)
{
	return SetReg2(mask,0x7F);
}

static uint8_t ToggleData(uint8_t mask)
{
	return SetReg2(mask,0xF7);
}

static uint8_t ReadModeToggle(uint8_t mask)
{
	return SetReg1(mask,0xFB);
}

static uint8_t SetMode(uint8_t mask)
{
	return SetReg1(mask,0xFC);
}

uint8_t WriteCtrlReg1(uint8_t data)
{
    return MagWriteByte(CTRL_REG1, data);
}

uint8_t WriteCtrlReg2(uint8_t data)
{
    return MagWriteByte(CTRL_REG2, data);
}

uint8_t SetCtrlReg1Default()
{
	return WriteCtrlReg1(CTRL_REG1_DEFAULT);
}

uint8_t SetCtrlReg2Default()
{
	return WriteCtrlReg2(CTRL_REG2_DEFAULT);
}

uint8_t SetContinuousMode()
{
	return SetMode(CTRL_REG1_CONTINUOUS);
}

uint8_t SetStandbyMode()
{
	return SetMode(CTRL_REG1_STANDBY);
}

uint8_t SetSingleMeasurmentMode()
{ 
	return SetMode(CTRL_REG1_SINGLE_MEASURMENT);
}

uint8_t SetTriggerMeasurmentMode()
{
	return SetMode(CTRL_REG1_TRIGGER_MEASURMENT);
}

uint8_t SetFastReadOn()
{	
	return ReadModeToggle(CTRL_REG1_FAST_READ_EN);
}

uint8_t SetFastReadOff()
{
	return ReadModeToggle(CTRL_REG1_FAST_READ_NENEN);
}

uint8_t SetAutoResetOn()
{
	return  AutoResetToggle(CTRL_REG2_AUTO_MRST_EN);
}
uint8_t SetAutoResetOff	()
{
	return  AutoResetToggle(CTRL_REG2_AUTO_MRST_NENEN);
}

uint8_t SetUserCorrectedData()
{
	return ToggleData( CTRL_REG2_RAW_NEN);
}

uint8_t SetRawData()
{
	return ToggleData( CTRL_REG2_RAW_EN);
}

uint8_t ResetMag()
{
	return WriteCtrlReg2(CTRL_REG2_MAG_RST);
}

uint8_t ReadDrStatus(uint8_t *readPtr)
{
    return MagReadByte(DR_STATUS, readPtr);
}

uint8_t ReadWhoAmI(uint8_t *readPtr)
{ 
    return MagReadByte(WHO_AM_I, readPtr);
}

uint8_t ReadSysMod(uint8_t *readPtr)
{
    return MagReadByte(SYSMOD, readPtr);
}

int8_t ReadDieTep(int8_t *readPtr)
{
    return MagReadByte(DIE_TEMP, readPtr);
}

uint8_t ReadCtrlReg1(uint8_t *readPtr)
{
    return MagReadByte(CTRL_REG1, readPtr);
}

uint8_t ReadCtrlReg2(uint8_t *readPtr)
{
    return MagReadByte(CTRL_REG2, readPtr);
}