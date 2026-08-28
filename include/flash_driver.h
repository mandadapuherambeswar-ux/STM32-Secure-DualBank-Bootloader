/**
 * @file flash_driver.h
 * @brief STM32 Embedded Flash Memory Controller Driver Header
 * @author Herambeswar Mandadapu
 */

#ifndef FLASH_DRIVER_H
#define FLASH_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

#define FLASH_KEY1  0x45670123UL
#define FLASH_KEY2  0xCDEF89ABUL

void Flash_Unlock(void);
void Flash_Lock(void);
bool Flash_EraseSector(uint8_t sector_number);
bool Flash_WriteWord(uint32_t address, uint32_t data);
bool Flash_WriteBuffer(uint32_t dest_address, const uint8_t *data, uint32_t length);

#endif /* FLASH_DRIVER_H */
