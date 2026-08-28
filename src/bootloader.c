/**
 * @file bootloader.c
 * @brief Bootloader Core Logic & Vector Table Relocation
 * @author Herambeswar Mandadapu
 */

#include "bootloader.h"
#include "image_auth.h"
#include <stdio.h>
#include <string.h>

typedef void (*pFunction)(void);

void Bootloader_Init(void)
{
    /* Initialize peripherals, clocks, and watchdog */
}

bool Bootloader_VerifySlot(uint32_t slot_addr)
{
    const ImageHeader_t *header = (const ImageHeader_t *)slot_addr;
    if (!ImageAuth_ValidateHeader(header)) {
        return false;
    }

    const uint8_t *app_binary = (const uint8_t *)(slot_addr + sizeof(ImageHeader_t));
    uint32_t calculated_crc = ImageAuth_CalculateCRC32(app_binary, header->image_size);

    return (calculated_crc == header->image_crc32);
}

ActiveSlot_t Bootloader_SelectValidSlot(void)
{
    /* Prefer Slot A, fallback to Slot B if corrupt */
    if (Bootloader_VerifySlot(APP_SLOT_A_ADDR)) {
        return SLOT_A;
    } else if (Bootloader_VerifySlot(APP_SLOT_B_ADDR)) {
        return SLOT_B;
    }
    return SLOT_INVALID;
}

void Bootloader_JumpToApplication(uint32_t app_address)
{
    uint32_t app_entry = *(volatile uint32_t *)(app_address + sizeof(ImageHeader_t) + 4);
    uint32_t app_stack = *(volatile uint32_t *)(app_address + sizeof(ImageHeader_t));

    (void)app_entry;
    (void)app_stack;

    /*
     * Cortex-M Vector Relocation & Branch Sequence:
     * __disable_irq();
     * SCB->VTOR = (app_address + sizeof(ImageHeader_t));
     * __set_MSP(app_stack);
     * ((pFunction)app_entry)();
     */
}
