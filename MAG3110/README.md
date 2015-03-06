This is the C code I made for the freescale MAG3110 3D magnetometer. This sensor works as a I<sup>2</sup>C slave. To interface this sensor with a system the following functions need to be defined. 

1. unt8_t MagWriteByte(uint8_t,uint8_t)
2. uint8_t MagWriteMultipleBytes(uint8_t,uint8_t *,uint8_t)
3. uint8_t MagReadByte(uint8_t,uint8_t *)
4. uint8_t MagReadMultipleByte(uint8_t,uint8_t *,uint8_t)

These functions should be implemented for I<sup>2</sup>C.

This should make the sensor work with any system. I have only tested the sensor using PSoC5LP.
