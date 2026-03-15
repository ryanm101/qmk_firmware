MCU = CH579M
BOOTLOADER = ch-isp

MCU_FAMILY   = WCH
MCU_SERIES   = CH579
PLATFORM_KEY = chibios
BOARD        = WCH_CH579_KEY12

BLUETOOTH_ENABLE = no
AUDIO_ENABLE     = no
RGBLIGHT_ENABLE  = no
BOOTMAGIC_ENABLE = no   # needs EEPROM — not implemented yet
MOUSEKEY_ENABLE  = no
EXTRAKEY_ENABLE  = no   # adds USB descriptors — disable until USB baseline works
NKRO_ENABLE      = no   # adds USB descriptors — disable until USB baseline works
ENCODER_ENABLE   = no   # disable until matrix pins are confirmed

# Debug: brute-force GPIO scanner — prints row/col pin names over USB console.
# Run `qmk console` on the host to see output while pressing keys.
# Once pins are confirmed, set CUSTOM_MATRIX = no and fill in keyboard.json.
CONSOLE_ENABLE   = yes
CUSTOM_MATRIX    = yes
SRC             += matrix.c
