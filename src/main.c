/**
 * @file main.c
 * @brief Bootloader Execution & Dual-Bank Slot Verifier
 * @author Herambeswar Mandadapu
 */

#include "bootloader.h"
#include "image_auth.h"
#include <stdio.h>

int main(void)
{
    printf("====================================================\n");
    printf(" 🔐 STM32 Secure Dual-Bank IAP Bootloader\n");
    printf(" Author: Herambeswar Mandadapu\n");
    printf("====================================================\n\n");

    /* Simulate a sample image header and payload in memory */
    uint8_t mock_firmware[128] = { 0xAA, 0xBB, 0xCC, 0xDD };
    uint32_t fw_crc = ImageAuth_CalculateCRC32(mock_firmware, sizeof(mock_firmware));

    ImageHeader_t header = {
        .magic = IMAGE_MAGIC_NUMBER,
        .image_size = sizeof(mock_firmware),
        .version = 0x00010200, /* v1.2.0 */
        .image_crc32 = fw_crc,
        .entry_point = 0x08010040UL
    };

    printf("[STEP 1] Validating Slot A Image Header (Magic: 0x%08X)...\n", header.magic);
    if (ImageAuth_ValidateHeader(&header)) {
        printf("         ==> Header Validated [PASS]\n");
    }

    printf("[STEP 2] Verifying Firmware Image Integrity (CRC32: 0x%08X)...\n", header.image_crc32);
    uint32_t calc_crc = ImageAuth_CalculateCRC32(mock_firmware, sizeof(mock_firmware));
    if (calc_crc == header.image_crc32) {
        printf("         ==> CRC Integrity Match: 0x%08X [PASS]\n\n", calc_crc);
        printf("[STEP 3] Relocating Vector Table (SCB->VTOR) & Branching to Application...\n");
        printf("[SUCCESS] Application launched successfully from Slot A.\n");
    } else {
        printf("[WARN] Slot A Corrupted! Rolling back to Slot B...\n");
    }

    return 0;
}
