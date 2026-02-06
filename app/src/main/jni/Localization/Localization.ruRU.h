#ifndef ANDROIDMIXMOD_LOCALIZATION_RURU_H
#define ANDROIDMIXMOD_LOCALIZATION_RURU_H

#include "Localization.h"

locale_map ruRU = localization["ruRU"] = std::unordered_map<int, const char*>{
    { LANGUAGE, "-10_Spinner_Язык_Использовать язык игры,English,Русский,中文 (简体)" },
    { IGNORE_SCREEN_CUTOUTS, "-11_Toggle_Отключить игнорирование вырезов экрана"},
    { TIMESCALE_ENABLED, "0_Toggle_Ускорение анимации" },
    { TIMESCALE_IN_GAME_ONLY, "25_Toggle_Ускорение только в игре" },
    { TIMESCALE, "1_SeekBar_Cкорость_100_800" },
    { SKIP_HERO_INTRO, "2_Toggle_Пропуск представления героев" },
    { SHUTUP_BOB, "3_Toggle_Заткнуть боба на полях сражений" },
    { EXTENDED_BM, "4_Toggle_Убрать ограничение на использование эмоций" },
    { DISABLE_RANDOM_FOR_EMOTES, "5_Toggle_Отключить рандом для эмоций" },
    { EMOTE_SPAM_BLOCKER, "6_Toggle_Блокировщик спама эмоциями" },
    { EMOTES_BEFORE_BLOCK, "7_InputValue_Количество эмоций" },
    { DISABLE_THINK_EMOTES, "8_Toggle_Отключить эмоции раздумья героев" },
    { GOLDEN_TEXT, "9_Spinner_Изменения для золотых карт_Обычный режим,Все герои и карты будут золотыми,Все ваши герои и карты будут золотыми,Все герои и карты будут обычными" },
    { DIAMOND_TEXT, "10_Spinner_Изменения для бриллиантовых карт_Обычный режим,Все герои и карты будут бриллиантовыми,Все ваши герои и карты будут бриллиантовыми,Все герои и карты будут обычными" },
    { SIGNATURE_TEXT, "21_Spinner_Изменения для сигнатурных карт_Обычный режим,Все герои и карты будут сигнатурными,Все ваши герои и карты будут сигнатурными,Все герои и карты будут обычными" },
    { SHOW_OPPONENT_RANK_IN_GAME, "11_Toggle_Включить отображение ранга противника" },
    { DEVICE_PRESET, "16_Spinner_Настройки устройства_Стандартно,iPad,iPhone,Phone,Tablet,HuaweiPhone,PC,Mac,Вручную" },
    { OPERATING_SYSTEM, "17_Spinner_Операционная система_PC,Mac,iOS,Android" },
    { SCREEN_TEXT, "18_Spinner_Экран_Phone,MiniTablet,Tablet,PC" },
    { DEVICE_NAME, "19_InputText_Имя устройства" },
    { MOVE_ENEMY_CARDS, "20_Toggle_Переворт карт в режиме зрителя" },
    { COPY_BATTLETAG, "22_Button_Скопировать BattleTag" },
    { COPY_BATTLETAG_ON_BATTLEGROUNDS, "23_Toggle_Копировать BattleTag на полях сражений" },
    { SIMULATE_DISCONNECT, "24_Button_Симулировать отключение" },
    { SAVE_SETTINGS, "-1_Toggle_Сохранять настройки" },
    { AUTO_SIZE, "-3_Toggle_Авторазмер по вертикали" },
    { CLOSE_SETTINGS, "-6_Button_<font color='red'>Закрыть настройки</font>" }
};

#endif //ANDROIDMIXMOD_LOCALIZATION_RURU_H