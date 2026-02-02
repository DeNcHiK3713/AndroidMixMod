#ifndef ANDROIDMIXMOD_LOCALIZATION_H
#define ANDROIDMIXMOD_LOCALIZATION_H

#define LANGUAGE 27
#define IGNORE_SCREEN_CUTOUTS 26
#define TIMESCALE_ENABLED 0
#define TIMESCALE_IN_GAME_ONLY 25
#define TIMESCALE 1
#define SKIP_HERO_INTRO 2
#define SHUTUP_BOB 3
#define EXTENDED_BM 4
#define DISABLE_RANDOM_FOR_EMOTES 5
#define EMOTE_SPAM_BLOCKER 6
#define EMOTES_BEFORE_BLOCK 7
#define DISABLE_THINK_EMOTES 8
#define GOLDEN_TEXT 9
#define DIAMOND_TEXT 10
#define SIGNATURE_TEXT 21
#define SHOW_OPPONENT_RANK_IN_GAME 11
#define DEVICE_PRESET 16
#define OPERATING_SYSTEM 17
#define SCREEN_TEXT 18
#define DEVICE_NAME 19
#define MOVE_ENEMY_CARDS 20
#define COPY_BATTLETAG 22
#define COPY_BATTLETAG_ON_BATTLEGROUNDS 23
#define SIMULATE_DISCONNECT 24
#define SAVE_SETTINGS 28
#define AUTO_SIZE 29
#define CLOSE_SETTINGS 30

#include <unordered_map>

typedef std::unordered_map<int, const char*> locale_map;
typedef std::unordered_map<std::string, locale_map> localization_map;
localization_map localization;

locale_map enUS = localization["enUS"] = std::unordered_map<int, const char*>{
	{ LANGUAGE, "-10_Spinner_Language_Use game language,English,Русский,中文 (简体)" },
	{ IGNORE_SCREEN_CUTOUTS, "-11_Toggle_Disable ignoring screen cutouts"},
	{ TIMESCALE_ENABLED, "0_Toggle_Timescale" },
	{ TIMESCALE_IN_GAME_ONLY, "25_Toggle_Timescale only in game" },
	{ TIMESCALE, "1_SeekBar_Timescale value_100_800" },
	{ SKIP_HERO_INTRO, "2_Toggle_Disable hero introduction animation" },
	{ SHUTUP_BOB, "3_Toggle_Disable Bob's comments on Battlegrounds" },
	{ EXTENDED_BM, "4_Toggle_Remove restrictions on the use of emotions" },
	{ DISABLE_RANDOM_FOR_EMOTES, "5_Toggle_Disable the use of random emotes if all targets are randomly selected" },
	{ EMOTE_SPAM_BLOCKER, "6_Toggle_Enable emote spam blocker" },
	{ EMOTES_BEFORE_BLOCK, "7_InputValue_The amount of emotion" },
	{ DISABLE_THINK_EMOTES, "8_Toggle_Disable the characters' emotions and thoughts" },
	{ GOLDEN_TEXT, "9_Spinner_Changes for Gold Cards_Normal mode,All heroes and cards will be changed during the match,All your heroes and cards will be changed during the match,All heroes and cards during the match will be normal (without animations)" },
	{ DIAMOND_TEXT, "10_Spinner_Changes for Diamond Cards_Normal mode,All heroes and cards will be changed during the match,All your heroes and cards will be changed during the match,All heroes and cards during the match will be normal (without animations)" },
	{ SIGNATURE_TEXT, "21_Spinner_Changes for Signature Cards_Normal mode,All heroes and cards will be changed during the match,All your heroes and cards will be changed during the match,All heroes and cards during the match will be normal (without animations)" },
	{ SHOW_OPPONENT_RANK_IN_GAME, "11_Toggle_Enable display of current enemy's rank" },
	{ DEVICE_PRESET, "16_Spinner_Device simulation_Default,iPad,iPhone,Phone,Tablet,HuaweiPhone,PC,Mac,Custom" },
	{ OPERATING_SYSTEM, "17_Spinner_Operating system_PC,Mac,iOS,Android" },
	{ SCREEN_TEXT, "18_Spinner_Screen_Phone,MiniTablet,Tablet,PC" },
	{ DEVICE_NAME, "19_InputText_Device name" },
	{ MOVE_ENEMY_CARDS, "20_Toggle_Unfold the cards in your opponent's hand in spectator mode" },
	{ COPY_BATTLETAG, "22_Button_Copy BattleTag" },
	{ COPY_BATTLETAG_ON_BATTLEGROUNDS, "23_Toggle_Copy BattleTag on Battlegrounds" },
	{ SIMULATE_DISCONNECT, "24_Button_Simulate disconnect" },
	{ SAVE_SETTINGS, "-1_Toggle_Save feature preferences"},
	{ AUTO_SIZE, "-3_Toggle_Auto size vertically"},
	{ CLOSE_SETTINGS, "-6_Button_<font color='red'>Close settings</font>"}
};

#endif //ANDROIDMIXMOD_LOCALIZATION_H
