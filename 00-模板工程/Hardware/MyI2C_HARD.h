#ifndef __MYI2C_H
#define __MYI2C_H

void MyI2C_Init(void);
void MyI2C_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);

#endif
