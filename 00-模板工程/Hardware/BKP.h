#ifndef __BKP_H
#define __BKP_H

void BKP_Init(void);
void BKP_write(uint16_t BKP_DR, uint16_t Data);
uint16_t BKP_Read(uint16_t BKP_DR);

#endif
