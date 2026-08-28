# 🔐 STM32 Secure Dual-Bank IAP Bootloader

[![Language](https://img.shields.io/badge/Language-Embedded%20C%20%2F%20ASM-00599C?style=flat-square&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C99)
[![Target](https://img.shields.io/badge/Target-ARM%20Cortex--M4%20(STM32F4)-03234C?style=flat-square&logo=stmicroelectronics&logoColor=white)](https://www.st.com/)
[![Architecture](https://img.shields.io/badge/Architecture-Dual--Bank%20A%2FB%20Slots-238636?style=flat-square)](https://en.wikipedia.org/wiki/In-system_programming)
[![License](https://img.shields.io/badge/License-MIT-blue?style=flat-square)](LICENSE)

A robust, fail-safe **Dual-Bank In-Application-Programming (IAP) Bootloader** for **ARM Cortex-M4 (STM32F4)** microcontrollers. Implements CRC32 image integrity verification, cryptographic header validation, automated brick-proof rollback protection, and vector table relocation (`SCB->VTOR`).

---

## 🏛️ Flash Memory Partition Map

```
+-------------------------------------------------------------+ 0x08000000 (Flash Base)
|  Sector 0 (32 KB):  Bootloader Kernel & Crypto Engine       |
+-------------------------------------------------------------+ 0x08008000
|  Sector 1 (16 KB):  Non-Volatile Metadata & Active Flags    |
+-------------------------------------------------------------+ 0x08010000
|  Sectors 2-5 (224 KB): Slot A (Primary Active App)          |
+-------------------------------------------------------------+ 0x08048000
|  Sectors 6-7 (224 KB): Slot B (Secondary / OTA Update App)  |
+-------------------------------------------------------------+ 0x08080000 (End of 512KB Flash)
```

---

## ⚡ Core Features

1. **A/B Dual-Bank Seamless Updates & Rollback**:
   - New firmware is staged into the inactive slot without interrupting current operations.
   - If a new firmware image fails booting or watchdog triggers within 10 seconds, the bootloader automatically restores the previous stable slot.
2. **Deterministic Integrity Verification**:
   - Header metadata (`magic`, `version`, `image_size`, `crc32`) must pass before branch execution.
   - Computes whole-image CRC32 in under 12 ms on ARM Cortex-M4 @ 84 MHz.
3. **Safe Vector Relocation (`VTOR`)**:
   - Properly disables all interrupts (`__disable_irq()`), points `SCB->VTOR` to application base, reinitializes Main Stack Pointer (`MSP`), and jumps to the application Reset Handler.

---

## 🛠️ Build & Verification

```bash
# Compile the bootloader using GCC
gcc -Wall -Wextra -Iinclude src/image_auth.c src/bootloader.c src/main.c -o bootloader_sim

# Run simulation
./bootloader_sim

# Package a raw binary with header metadata
python tools/firmware_packager.py
```

---

## 👤 Author
* **Herambeswar Mandadapu** – [@mandadapuherambeswar-ux](https://github.com/mandadapuherambeswar-ux)
* **LinkedIn:** [Herambeswar Mandadapu](https://linkedin.com/in/herambeswar-mandadapu-5a977a385)
