/**
 * @file flash_driver.c
 * @brief STM32 Embedded Flash Memory Controller Implementation
 * @author Herambeswar Mandadapu
 */

#include "flash_driver.h"
#include <stdio.h>

void Flash_Unlock(void)
{
    /*
     * Unlock sequence:
     * FLASH->KEYR = FLASH_KEY1;
     * FLASH->KEYR = FLASH_KEY2;
     */
}

void Flash_Lock(void)
{
    /* FLASH->CR |= (1 << 31); */
}

bool Flash_EraseSector(uint8_t sector_number)
{
    (void)sector_number;
    /*
     * 1. Wait for BSY bit
     * 2. Set SER bit and SNB (Sector Number) in FLASH->CR
     * 3. Set STRT bit
     * 4. Wait for BSY to clear
     */
    return true;
}

bool Flash_WriteWord(uint32_t address, uint32_t data)
{
    (void)address;
    (void)data;
    /* Program 32-bit word */
    return true;
}

bool Flash_WriteBuffer(uint32_t dest_address, const uint8_t *data, uint32_t length)
{
    if (!data || length == 0) return false;
    (void)dest_address;
    return true;
}
