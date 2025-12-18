# Fork Android-Mod-Menu by ABS
This is just my vision of what version 5 should be like.

# 5.0 what's new:
- C++:
- Added xDL lib
- KittyMemory lib updated
- Macros.h & Utils.cpp:
- - xDL sym resolver added
- - HOOKs reworked with Dobby usage
- - PATCH_SWITCH, RESTORE has been returned and reworked
- - INST added (Dobby)
- - asm support added (KittyMemory::Keystone assembler)
- - Macro defines have been optimized
- Init() from Setup migrated to Menu for convenience
- And64InlineHook and Substrate libs removed (replaced by Dobby)
- get_device_api_level_inlines.h removed (replaced by JNI get_api_sdk)
-
- Java:
- CrashHandler.java updated:
- - more debug info
- - save path has been changed to: android/media/PACKAGE/files/LOG_DIR for all devices
- - clear old crash logs (keep last 5)
- Main.java minor changes
- Menu.java minor changes
-
- Project settings:
- Updated to SDK 36
- Upgraded gradle
- Minor gradle settings changes

# Introduction
![GitHub](https://img.shields.io/github/license/LGLTeam/Android-Mod-Menu?style=flat-square)

Floating mod menu for il2cpp and other native android games. KittyMemory, MSHook, And64InlineHook and basic string obfuscator (AY obfuscator) included. Assets are stored as base64 in cpp and does not need to be stored under assets folder.

Support Android 4.4.x up to Android 16. ARMv7 and ARM64 are supported.

![](Intro.gif)

# Known bug
- Spinner does not show on some devices running Android 11. Should work again on Android 12
- On some games, menu is using old layout such as Kitkat or Gingerbread when launched without permission. We have not found a way to fix it.

# Getting started
 
See "Docs" folder

# Need help

If you have an issue with Hooking and game crashes, you should go to the **support forums**. Here there are no teachers who can help you with such issues.

# Credits
Thanks to the following individuals whose code helped me develop this mod menu

* LGLTeam - (parent of fork) Mod menu - https://github.com/LGLTeam/Android-Mod-Menu
* Octowolve/Escanor - Mod menu: https://github.com/z3r0Sec/Substrate-Template-With-Mod-Menu
* VanHoevenTR - Mod menu - https://github.com/LGLTeam/VanHoevenTR_Android_Mod_Menu
* MrIkso - First mod menu template https://github.com/MrIkso/FloatingModMenu
* MJx0 A.K.A Ruit - https://github.com/MJx0/KittyMemory
* jmpews(AKA.zz) - https://github.com/jmpews/Dobby
* Kelun Cai & ruki - https://github.com/hexhacking/xDL
* And everyone else who provided input and contributions to this project!

# License
**GNU General Public License 3**

# Disclaimer
This project is for Educational Use only. We do not condone this project being used to gain an advantage against other people. This project was made for fun. If you are using this project for modding/hacking PU*G, C*DM, and any other Tencent games, we ask you to STOP immediately!

Do not buy any source codes on Telegram even if the author can be trusted, there is always a risk getting scammed. We will not be responsible for that. This project is always FREE to use