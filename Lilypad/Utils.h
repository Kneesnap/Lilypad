#pragma once

extern byte* ReadMemory(int, int);
extern void WriteMemory(int, LPVOID, int);
extern void WriteByte(int, byte);
extern void WriteInteger(int, int);
extern void WriteShort(int, short);
extern void WriteBoolean(int, BOOL);
extern byte* NopCode(int, int);
extern int ReadByte(int);
extern int ReadInteger(int);
extern short ReadShort(int);

#define VK_KEY_0	0x30 /* '0' key */
#define VK_KEY_1	0x31 /* '1' key */
#define VK_KEY_2	0x32 /* '2' key */
#define VK_KEY_3	0x33 /* '3' key */
#define VK_KEY_4	0x34 /* '4' key */
#define VK_KEY_5	0x35 /* '5' key */
#define VK_KEY_6	0x36 /* '6' key */
#define VK_KEY_7	0x37 /* '7' key */
#define VK_KEY_8	0x38 /* '8' key */
#define VK_KEY_9	0x39 /* '9' key */

#define VK_KEY_A	0x41 /* 'A' key */
#define VK_KEY_B	0x42 /* 'B' key */
#define VK_KEY_C	0x43 /* 'C' key */
#define VK_KEY_D	0x44 /* 'D' key */
#define VK_KEY_E	0x45 /* 'E' key */
#define VK_KEY_F	0x46 /* 'F' key */
#define VK_KEY_G	0x47 /* 'G' key */
#define VK_KEY_H	0x48 /* 'H' key */
#define VK_KEY_I	0x49 /* 'I' key */
#define VK_KEY_J	0x4A /* 'J' key */
#define VK_KEY_K	0x4B /* 'K' key */
#define VK_KEY_L	0x4C /* 'L' key */
#define VK_KEY_M	0x4D /* 'M' key */
#define VK_KEY_N	0x4E /* 'N' key */
#define VK_KEY_O	0x4F /* 'O' key */
#define VK_KEY_P	0x50 /* 'P' key */
#define VK_KEY_Q	0x51 /* 'Q' key */
#define VK_KEY_R	0x52 /* 'R' key */
#define VK_KEY_S	0x53 /* 'S' key */
#define VK_KEY_T	0x54 /* 'T' key */
#define VK_KEY_U	0x55 /* 'U' key */
#define VK_KEY_V	0x56 /* 'V' key */
#define VK_KEY_W	0x57 /* 'W' key */
#define VK_KEY_X	0x58 /* 'X' key */
#define VK_KEY_Y	0x59 /* 'Y' key */
#define VK_KEY_Z	0x5A /* 'Z' key */

#define VK_NUMPAD0	0x60 /* Numeric keypad '0' key */
#define VK_NUMPAD1	0x61 /* Numeric keypad '1' key */
#define VK_NUMPAD2	0x62 /* Numeric keypad '2' key */
#define VK_NUMPAD3	0x63 /* Numeric keypad '3' key */
#define VK_NUMPAD4	0x64 /* Numeric keypad '4' key */
#define VK_NUMPAD5	0x65 /* Numeric keypad '5' key */
#define VK_NUMPAD6	0x66 /* Numeric keypad '6' key */
#define VK_NUMPAD7	0x67 /* Numeric keypad '7' key */
#define VK_NUMPAD8	0x68 /* Numeric keypad '8' key */
#define VK_NUMPAD9	0x69 /* Numeric keypad '9' key */