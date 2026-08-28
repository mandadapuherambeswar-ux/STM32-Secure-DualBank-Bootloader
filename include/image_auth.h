/**
 * @file image_auth.h
 * @brief Firmware Image Authentication & Integrity Check
 * @author Herambeswar Mandadapu
 */

#ifndef IMAGE_AUTH_H
#define IMAGE_AUTH_H

#include "bootloader.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t ImageAuth_CalculateCRC32(const uint8_t *data, size_t length);
bool ImageAuth_ValidateHeader(const ImageHeader_t *header);

#ifdef __cplusplus
}
#endif

#endif /* IMAGE_AUTH_H */
