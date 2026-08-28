/**
 * @file image_auth.c
 * @brief Firmware Authentication Implementation
 * @author Herambeswar Mandadapu
 */

#include "image_auth.h"

uint32_t ImageAuth_CalculateCRC32(const uint8_t *data, size_t length)
{
    uint32_t crc = 0xFFFFFFFFUL;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            crc = (crc >> 1) ^ (0xEDB88320UL & -(crc & 1));
        }
    }
    return ~crc;
}

bool ImageAuth_ValidateHeader(const ImageHeader_t *header)
{
    if (!header) return false;
    if (header->magic != IMAGE_MAGIC_NUMBER) return false;
    if (header->image_size == 0 || header->image_size > APP_MAX_SIZE) return false;
    return true;
}
