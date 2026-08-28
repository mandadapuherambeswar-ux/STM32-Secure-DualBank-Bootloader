# 🔐 STM32 Secure Dual-Bank IAP Bootloader

[![Language](https://img.shields.io/badge/Language-Embedded%20C%20%2F%20ASM-00599C?style=flat-square&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C99)
[![Target](https://img.shields.io/badge/Target-ARM%20Cortex--M4%20(STM32F4)-03234C?style=flat-square&logo=stmicroelectronics&logoColor=white)](https://www.st.com/)
[![Architecture](https://img.shields.io/badge/Architecture-Dual--Bank%20A%2FB%20Slots-238636?style=flat-square)](https://en.wikipedia.org/wiki/In-system_programming)
[![License](https://img.shields.io/badge/License-MIT-blue?style=flat-square)](LICENSE)

A robust, fail-safe **Dual-Bank In-Application-Programming (IAP) Bootloader** for **ARM Cortex-M4 (STM32F4)** microcontrollers. Implements CRC32 image integrity verification, cryptographic header validation, automated brick-proof rollback protection, and vector table relocation (`SCB->VTOR`).

---

## 🔌 Hardware Circuit Diagram & In-System Programming (IAP) Interface

```
                          +3.3V Power Bus
                                |
 +------------------------------+-------------------------------------------------+
 |                              |                                                 |
 |                             3V3                                                |
 |                                                                                |
 |    [ STM32F401 MCU ]                                                           |
 |                                                                                |
 |      (SWDIO)       (SWCLK)       (NRST)        (BOOT0)       (TX)       (RX)   |
 |        PA13          PA14         NRST          BOOT0         PA2        PA3   |
 +---------+-------------+------------+--------------+------------+----------+----+
           |             |            |              |            |          |
           |             |            |          [ 10kΩ ]         |          |
           |             |            |              |            |          |
           v             v            v             GND           v          v
 +------------------------------------+               +---------------------------+
 |       ST-LINK V2 / J-Link Debugger |               |  FT232R USB-UART Adapter  |
 |        (SWD Firmware Flasher)      |               |  (IAP UART Firmware OTA)  |
 +------------------------------------+               +---------------------------+
```

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

## ⚡ Hardware Pinout Matrix

| Pin Name | MCU Pin | Description | Purpose |
| :--- | :--- | :--- | :--- |
| **SWDIO** | `PA13` | Serial Wire Data I/O | JTAG/SWD Debugging & Initial Bootloader Flash |
| **SWCLK** | `PA14` | Serial Wire Clock | SWD Clock Line |
| **BOOT0** | `BOOT0`| Boot Mode Selector | Pulled to GND via 10kΩ resistor (Boot from Flash) |
| **USART2 TX** | `PA2` | Serial Telemetry Output | IAP Status & Boot Logs (115200 baud) |
| **USART2 RX** | `PA3` | Firmware Ingestion Input | YMODEM / Binary Frame Ingestion |

---

## 🛠️ Build & Verification

```bash
# Compile the bootloader using GCC
gcc -Wall -Wextra -Iinclude src/image_auth.c src/flash_driver.c src/bootloader.c src/main.c -o bootloader_sim

# Run simulation
./bootloader_sim

# Package a raw binary with header metadata
python tools/firmware_packager.py
```

---

## 👤 Author
* **Herambeswar Mandadapu** – [@mandadapuherambeswar-ux](https://github.com/mandadapuherambeswar-ux)
* **LinkedIn:** [Herambeswar Mandadapu](https://linkedin.com/in/herambeswar-mandadapu-5a977a385)
