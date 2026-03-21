MCU = CH579M
BOOTLOADER = ch-isp

MCU_FAMILY   = WCH
MCU_SERIES   = CH579
PLATFORM_KEY = chibios
BOARD        = WCH_CH579_KEY12

BLUETOOTH_ENABLE = no
AUDIO_ENABLE     = no
RGBLIGHT_ENABLE  = no
BOOTMAGIC_ENABLE = yes  # hold ENC1 button at power-on to reset
MOUSEKEY_ENABLE  = no
EXTRAKEY_ENABLE  = yes  # needed for KC_VOLU/VOLD consumer codes
NKRO_ENABLE      = no   # adds USB descriptors — disable until USB baseline works
ENCODER_ENABLE   = yes  # encoder 1: B0(CW)/B1(CCW), encoder 2: A0(CW)/A5(CCW)

CONSOLE_ENABLE   = yes
KEYBOARD_SHARED_EP = no
CUSTOM_MATRIX    = lite
SRC             += matrix.c hooks.c
