/**
 * @file bootloader.h
 * @brief STM32 Secure Dual-Bank IAP Bootloader Header
 * @author Herambeswar Mandadapu
 */

#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Flash Partition Memory Layout (STM32F4 512KB Example) */
#define FLASH_BASE_ADDR            0x08000000UL
#define BOOTLOADER_ADDR            0x08000000UL   /* 32 KB */
#define METADATA_SECTOR_ADDR       0x08008000UL   /* 16 KB */
#define APP_SLOT_A_ADDR            0x08010000UL   /* 224 KB - Primary */
#define APP_SLOT_B_ADDR            0x08048000UL   /* 224 KB - Secondary / OTA */

#define APP_MAX_SIZE               (224 * 1024)
#define IMAGE_MAGIC_NUMBER         0x46575550UL   /* "FWUP" */

/* Firmware Image Header Descriptor */
typedef struct __attribute__((packed)) {
    uint32_t magic;            /* 0x46575550 ("FWUP") */
    uint32_t image_size;       /* Size in bytes */
    uint32_t version;          /* Semantic version (Major.Minor.Patch) */
    uint32_t image_crc32;      /* CRC32 Checksum of the image */
    uint32_t entry_point;      /* Reset Handler address */
    uint8_t  signature[32];    /* Optional cryptographic signature */
} ImageHeader_t;

/* Slot Selection Enumeration */
typedef enum {
    SLOT_INVALID = 0,
    SLOT_A = 1,
    SLOT_B = 2
} ActiveSlot_t;

/* Function Prototypes */
void Bootloader_Init(void);
ActiveSlot_t Bootloader_SelectValidSlot(void);
bool Bootloader_VerifySlot(uint32_t slot_addr);
void Bootloader_JumpToApplication(uint32_t app_address);

#ifdef __cplusplus
}
#endif

#endif /* BOOTLOADER_H */
