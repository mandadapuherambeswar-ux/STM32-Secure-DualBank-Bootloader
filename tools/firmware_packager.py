#!/usr/bin/env python3
"""
Dual-Bank Firmware Packaging & Signing Tool
Author: Herambeswar Mandadapu
"""

import struct
import zlib

MAGIC_HEADER = 0x46575550  # "FWUP"

def package_binary(input_bytes: bytes, version_tuple=(1, 0, 0)) -> bytes:
    major, minor, patch = version_tuple
    ver_int = (major << 16) | (minor << 8) | patch
    
    crc32_val = zlib.crc32(input_bytes) & 0xFFFFFFFF
    size_val = len(input_bytes)
    entry_pt = 0x08010040
    signature = b'\x00' * 32
    
    # 4B magic + 4B size + 4B version + 4B crc + 4B entry + 32B sig = 52 Bytes Header
    header = struct.pack("<IIIII32s", MAGIC_HEADER, size_val, ver_int, crc32_val, entry_pt, signature)
    
    print(f"[*] Packaging Binary: Size={size_val}B, Version=v{major}.{minor}.{patch}, CRC32=0x{crc32_val:08X}")
    return header + input_bytes

if __name__ == "__main__":
    print("====================================================")
    print(" 🔐 STM32 Firmware Image Packager")
    print("====================================================\n")
    sample_data = b"STM32_APPLICATION_BINARY_DEMO_DATA" * 4
    packaged = package_binary(sample_data, (1, 2, 0))
    print(f"[+] Total Packaged Output Size: {len(packaged)} Bytes [SUCCESS]")
