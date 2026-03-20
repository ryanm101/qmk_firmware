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
EXTRAKEY_ENABLE  = yes  # needed for KC_VOLU/VOLD consumer codes
NKRO_ENABLE      = no   # adds USB descriptors — disable until USB baseline works
ENCODER_ENABLE   = yes  # encoder 2: A0(CW)/A5(CCW) confirmed; encoder 1 pins TBD

CONSOLE_ENABLE   = yes
KEYBOARD_SHARED_EP = no
CUSTOM_MATRIX    = lite
SRC             += matrix.c hooks.c
