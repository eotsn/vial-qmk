/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0x8A, 0x9E, 0x58, 0xA2, 0xF1, 0x65, 0xD0, 0x06}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 6 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }

// Configuration to reduce progmem/flash use
// #define VIAL_COMBO_ENTRIES 4
// #define VIAL_KEY_OVERRIDE_ENTRIES 4

// Extra configuration for the Frood - double tap to reset in bootloader mode
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED D5
