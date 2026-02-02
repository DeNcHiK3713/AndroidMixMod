#ifndef ANDROIDMIXMOD_LOCALIZATION_ZHCH_H
#define ANDROIDMIXMOD_LOCALIZATION_ZHCH_H

#include "Localization.h"

locale_map zhCN = localization["zhCN"] = std::unordered_map<int, const char*>{
	{ LANGUAGE, "-10_Spinner_语言_使用游戏语言,English,Русский,中文 (简体)" },
	{ IGNORE_SCREEN_CUTOUTS, "-11_Toggle_禁用忽略屏幕切口"},
	{ TIMESCALE_ENABLED, "0_Toggle_启用时间刻度" },
	{ TIMESCALE_IN_GAME_ONLY, "25_Toggle_时间刻度仅在游戏中" },
	{ TIMESCALE, "1_SeekBar_时间刻度值_100_800" },
	{ SKIP_HERO_INTRO, "2_Toggle_禁用英雄介绍动画" },
	{ SHUTUP_BOB, "3_Toggle_禁用鲍勃在战场上的评论" },
	{ EXTENDED_BM, "4_Toggle_消除对情感使用的限制" },
	{ DISABLE_RANDOM_FOR_EMOTES, "5_Toggle_如果所有目标都是随机选择的，则禁用随机表情" },
	{ EMOTE_SPAM_BLOCKER, "6_Toggle_启用表情垃圾邮件拦截器" },
	{ EMOTES_BEFORE_BLOCK, "7_InputValue_情绪数量" },
	{ DISABLE_THINK_EMOTES, "8_Toggle_禁用角色的情绪和思想" },
	{ GOLDEN_TEXT, "9_Spinner_金卡变更_普通模式，所有卡牌和英雄均正确显示,比赛期间所有英雄和卡牌都会发生变化,你的所有英雄和卡牌都会在比赛期间改变,比赛中所有英雄和卡牌都会正常，没有动画" },
	{ DIAMOND_TEXT, "10_Spinner_钻石卡的变化_普通模式，所有卡牌和英雄均正确显示,比赛期间所有英雄和卡牌都会发生变化,你的所有英雄和卡牌都会在比赛期间改变,比赛中所有英雄和卡牌都会正常，没有动画" },
	{ SIGNATURE_TEXT, "21_Spinner_签名卡的变更_普通模式，所有卡牌和英雄均正确显示,比赛期间所有英雄和卡牌都会发生变化,你的所有英雄和卡牌都会在比赛期间改变,比赛中所有英雄和卡牌都会正常，没有动画" },
	{ SHOW_OPPONENT_RANK_IN_GAME, "11_Toggle_启用显示当前敌人的等级" },
	{ DEVICE_PRESET, "16_Spinner_设备模拟_标准设置,iPad,iPhone,Phone,Tablet,HuaweiPhone,PC,Mac,您的设置" },
	{ OPERATING_SYSTEM, "17_Spinner_用于模拟另一个设备的操作系统类型_PC,Mac,iOS,Android" },
	{ SCREEN_TEXT, "18_Spinner_仿真屏幕_Phone,MiniTablet,Tablet,PC" },
	{ DEVICE_NAME, "19_InputText_仿真设备名称" },
	{ MOVE_ENEMY_CARDS, "20_Toggle_时间刻度仅在游戏中" },
	{ COPY_BATTLETAG, "22_Button_复制战斗标签" },
	{ COPY_BATTLETAG_ON_BATTLEGROUNDS, "23_Toggle_在战场上复制 BattleTag" },
	{ SIMULATE_DISCONNECT, "24_Button_模拟关机" },
	{ SAVE_SETTINGS, "-1_Toggle_保存功能首选项" },
	{ AUTO_SIZE, "-3_Toggle_自动调整垂直大小" },
	{ CLOSE_SETTINGS, "-6_Button_<font color='red'>关闭设置</font>" }
};

#endif //ANDROIDMIXMOD_LOCALIZATION_ZHCH_H