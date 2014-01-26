struct Frame {
  float duration;
  int resource;
};

struct Action {
  int identifier;
  int target;
};

struct __array__Frame {
  int length;
  struct Frame ** items;
};

struct __array__Action {
  int length;
  struct Action ** items;
};

struct AnimationSet {
  struct __array__Frame * frames;
  int identifier;
  struct __array__Action * actions;
};

struct __array__AnimationSet {
  int length;
  struct AnimationSet ** items;
};

float sets_item_0_frames_item_0_duration = 1.0;
int sets_item_0_frames_item_0_resource = RESOURCE_ID_BLINK_01;
struct Frame sets_item_0_frames_item_0 = { 1.0, RESOURCE_ID_BLINK_01 };
float sets_item_0_frames_item_1_duration = 0.15;
int sets_item_0_frames_item_1_resource = RESOURCE_ID_BLINK_02;
struct Frame sets_item_0_frames_item_1 = { 0.15, RESOURCE_ID_BLINK_02 };
float sets_item_0_frames_item_2_duration = 0.15;
int sets_item_0_frames_item_2_resource = RESOURCE_ID_BLINK_03;
struct Frame sets_item_0_frames_item_2 = { 0.15, RESOURCE_ID_BLINK_03 };
float sets_item_0_frames_item_3_duration = 0.15;
int sets_item_0_frames_item_3_resource = RESOURCE_ID_BLINK_02;
struct Frame sets_item_0_frames_item_3 = { 0.15, RESOURCE_ID_BLINK_02 };
struct Frame * sets_item_0_frames_items[4] = { &sets_item_0_frames_item_0, &sets_item_0_frames_item_1, &sets_item_0_frames_item_2, &sets_item_0_frames_item_3 };
struct __array__Frame sets_item_0_frames = { 4, sets_item_0_frames_items };
int sets_item_0_identifier = ANIMATION_SET_BLINK;
int sets_item_0_actions_item_0_identifier = ACTION_DEFAULT;
int sets_item_0_actions_item_0_target = ANIMATION_SET_BLINK;
struct Action sets_item_0_actions_item_0 = { ACTION_DEFAULT, ANIMATION_SET_BLINK };
int sets_item_0_actions_item_1_identifier = ACTION_BUTTON_SELECT;
int sets_item_0_actions_item_1_target = ANIMATION_SET_PET_START;
struct Action sets_item_0_actions_item_1 = { ACTION_BUTTON_SELECT, ANIMATION_SET_PET_START };
int sets_item_0_actions_item_2_identifier = ACTION_ACCELEROMETER_TAP;
int sets_item_0_actions_item_2_target = ANIMATION_SET_MAD;
struct Action sets_item_0_actions_item_2 = { ACTION_ACCELEROMETER_TAP, ANIMATION_SET_MAD };
int sets_item_0_actions_item_3_identifier = ACTION_TIME_NIGHT;
int sets_item_0_actions_item_3_target = ANIMATION_SET_SLEEP;
struct Action sets_item_0_actions_item_3 = { ACTION_TIME_NIGHT, ANIMATION_SET_SLEEP };
struct Action * sets_item_0_actions_items[4] = { &sets_item_0_actions_item_0, &sets_item_0_actions_item_1, &sets_item_0_actions_item_2, &sets_item_0_actions_item_3 };
struct __array__Action sets_item_0_actions = { 4, sets_item_0_actions_items };
struct AnimationSet sets_item_0 = { &sets_item_0_frames, ANIMATION_SET_BLINK, &sets_item_0_actions };
float sets_item_1_frames_item_0_duration = 0.4;
int sets_item_1_frames_item_0_resource = RESOURCE_ID_SLEEP_01;
struct Frame sets_item_1_frames_item_0 = { 0.4, RESOURCE_ID_SLEEP_01 };
float sets_item_1_frames_item_1_duration = 0.4;
int sets_item_1_frames_item_1_resource = RESOURCE_ID_SLEEP_02;
struct Frame sets_item_1_frames_item_1 = { 0.4, RESOURCE_ID_SLEEP_02 };
float sets_item_1_frames_item_2_duration = 0.4;
int sets_item_1_frames_item_2_resource = RESOURCE_ID_SLEEP_03;
struct Frame sets_item_1_frames_item_2 = { 0.4, RESOURCE_ID_SLEEP_03 };
float sets_item_1_frames_item_3_duration = 0.4;
int sets_item_1_frames_item_3_resource = RESOURCE_ID_SLEEP_04;
struct Frame sets_item_1_frames_item_3 = { 0.4, RESOURCE_ID_SLEEP_04 };
float sets_item_1_frames_item_4_duration = 0.4;
int sets_item_1_frames_item_4_resource = RESOURCE_ID_SLEEP_05;
struct Frame sets_item_1_frames_item_4 = { 0.4, RESOURCE_ID_SLEEP_05 };
float sets_item_1_frames_item_5_duration = 0.4;
int sets_item_1_frames_item_5_resource = RESOURCE_ID_SLEEP_06;
struct Frame sets_item_1_frames_item_5 = { 0.4, RESOURCE_ID_SLEEP_06 };
float sets_item_1_frames_item_6_duration = 0.4;
int sets_item_1_frames_item_6_resource = RESOURCE_ID_SLEEP_07;
struct Frame sets_item_1_frames_item_6 = { 0.4, RESOURCE_ID_SLEEP_07 };
struct Frame * sets_item_1_frames_items[7] = { &sets_item_1_frames_item_0, &sets_item_1_frames_item_1, &sets_item_1_frames_item_2, &sets_item_1_frames_item_3, &sets_item_1_frames_item_4, &sets_item_1_frames_item_5, &sets_item_1_frames_item_6 };
struct __array__Frame sets_item_1_frames = { 7, sets_item_1_frames_items };
int sets_item_1_identifier = ANIMATION_SET_SLEEP;
int sets_item_1_actions_item_0_identifier = ACTION_DEFAULT;
int sets_item_1_actions_item_0_target = ANIMATION_SET_WAKE;
struct Action sets_item_1_actions_item_0 = { ACTION_DEFAULT, ANIMATION_SET_WAKE };
int sets_item_1_actions_item_1_identifier = ACTION_TIME_NIGHT;
int sets_item_1_actions_item_1_target = ANIMATION_SET_SLEEP;
struct Action sets_item_1_actions_item_1 = { ACTION_TIME_NIGHT, ANIMATION_SET_SLEEP };
struct Action * sets_item_1_actions_items[2] = { &sets_item_1_actions_item_0, &sets_item_1_actions_item_1 };
struct __array__Action sets_item_1_actions = { 2, sets_item_1_actions_items };
struct AnimationSet sets_item_1 = { &sets_item_1_frames, ANIMATION_SET_SLEEP, &sets_item_1_actions };
float sets_item_2_frames_item_0_duration = 0.15;
int sets_item_2_frames_item_0_resource = RESOURCE_ID_PET_03;
struct Frame sets_item_2_frames_item_0 = { 0.15, RESOURCE_ID_PET_03 };
float sets_item_2_frames_item_1_duration = 0.15;
int sets_item_2_frames_item_1_resource = RESOURCE_ID_PET_04;
struct Frame sets_item_2_frames_item_1 = { 0.15, RESOURCE_ID_PET_04 };
float sets_item_2_frames_item_2_duration = 0.15;
int sets_item_2_frames_item_2_resource = RESOURCE_ID_PET_05;
struct Frame sets_item_2_frames_item_2 = { 0.15, RESOURCE_ID_PET_05 };
float sets_item_2_frames_item_3_duration = 0.15;
int sets_item_2_frames_item_3_resource = RESOURCE_ID_PET_04;
struct Frame sets_item_2_frames_item_3 = { 0.15, RESOURCE_ID_PET_04 };
float sets_item_2_frames_item_4_duration = 0.15;
int sets_item_2_frames_item_4_resource = RESOURCE_ID_PET_03;
struct Frame sets_item_2_frames_item_4 = { 0.15, RESOURCE_ID_PET_03 };
struct Frame * sets_item_2_frames_items[5] = { &sets_item_2_frames_item_0, &sets_item_2_frames_item_1, &sets_item_2_frames_item_2, &sets_item_2_frames_item_3, &sets_item_2_frames_item_4 };
struct __array__Frame sets_item_2_frames = { 5, sets_item_2_frames_items };
int sets_item_2_identifier = ANIMATION_SET_PET;
int sets_item_2_actions_item_0_identifier = ACTION_DEFAULT;
int sets_item_2_actions_item_0_target = ANIMATION_SET_PET_END;
struct Action sets_item_2_actions_item_0 = { ACTION_DEFAULT, ANIMATION_SET_PET_END };
int sets_item_2_actions_item_1_identifier = ACTION_BUTTON_SELECT;
int sets_item_2_actions_item_1_target = ANIMATION_SET_PET;
struct Action sets_item_2_actions_item_1 = { ACTION_BUTTON_SELECT, ANIMATION_SET_PET };
struct Action * sets_item_2_actions_items[2] = { &sets_item_2_actions_item_0, &sets_item_2_actions_item_1 };
struct __array__Action sets_item_2_actions = { 2, sets_item_2_actions_items };
struct AnimationSet sets_item_2 = { &sets_item_2_frames, ANIMATION_SET_PET, &sets_item_2_actions };
float sets_item_3_frames_item_0_duration = 0.15;
int sets_item_3_frames_item_0_resource = RESOURCE_ID_PET_01;
struct Frame sets_item_3_frames_item_0 = { 0.15, RESOURCE_ID_PET_01 };
float sets_item_3_frames_item_1_duration = 0.15;
int sets_item_3_frames_item_1_resource = RESOURCE_ID_PET_02;
struct Frame sets_item_3_frames_item_1 = { 0.15, RESOURCE_ID_PET_02 };
struct Frame * sets_item_3_frames_items[2] = { &sets_item_3_frames_item_0, &sets_item_3_frames_item_1 };
struct __array__Frame sets_item_3_frames = { 2, sets_item_3_frames_items };
int sets_item_3_identifier = ANIMATION_SET_PET_START;
int sets_item_3_actions_item_0_identifier = ACTION_DEFAULT;
int sets_item_3_actions_item_0_target = ANIMATION_SET_BLINK;
struct Action sets_item_3_actions_item_0 = { ACTION_DEFAULT, ANIMATION_SET_BLINK };
int sets_item_3_actions_item_1_identifier = ACTION_BUTTON_SELECT;
int sets_item_3_actions_item_1_target = ANIMATION_SET_PET;
struct Action sets_item_3_actions_item_1 = { ACTION_BUTTON_SELECT, ANIMATION_SET_PET };
struct Action * sets_item_3_actions_items[2] = { &sets_item_3_actions_item_0, &sets_item_3_actions_item_1 };
struct __array__Action sets_item_3_actions = { 2, sets_item_3_actions_items };
struct AnimationSet sets_item_3 = { &sets_item_3_frames, ANIMATION_SET_PET_START, &sets_item_3_actions };
float sets_item_4_frames_item_0_duration = 0.15;
int sets_item_4_frames_item_0_resource = RESOURCE_ID_PET_02;
struct Frame sets_item_4_frames_item_0 = { 0.15, RESOURCE_ID_PET_02 };
float sets_item_4_frames_item_1_duration = 0.15;
int sets_item_4_frames_item_1_resource = RESOURCE_ID_PET_01;
struct Frame sets_item_4_frames_item_1 = { 0.15, RESOURCE_ID_PET_01 };
struct Frame * sets_item_4_frames_items[2] = { &sets_item_4_frames_item_0, &sets_item_4_frames_item_1 };
struct __array__Frame sets_item_4_frames = { 2, sets_item_4_frames_items };
int sets_item_4_identifier = ANIMATION_SET_PET_END;
int sets_item_4_actions_item_0_identifier = ACTION_DEFAULT;
int sets_item_4_actions_item_0_target = ANIMATION_SET_BLINK;
struct Action sets_item_4_actions_item_0 = { ACTION_DEFAULT, ANIMATION_SET_BLINK };
int sets_item_4_actions_item_1_identifier = ACTION_BUTTON_SELECT;
int sets_item_4_actions_item_1_target = ANIMATION_SET_PET_START;
struct Action sets_item_4_actions_item_1 = { ACTION_BUTTON_SELECT, ANIMATION_SET_PET_START };
struct Action * sets_item_4_actions_items[2] = { &sets_item_4_actions_item_0, &sets_item_4_actions_item_1 };
struct __array__Action sets_item_4_actions = { 2, sets_item_4_actions_items };
struct AnimationSet sets_item_4 = { &sets_item_4_frames, ANIMATION_SET_PET_END, &sets_item_4_actions };
float sets_item_5_frames_item_0_duration = 0.25;
int sets_item_5_frames_item_0_resource = RESOURCE_ID_MAD_01;
struct Frame sets_item_5_frames_item_0 = { 0.25, RESOURCE_ID_MAD_01 };
float sets_item_5_frames_item_1_duration = 0.25;
int sets_item_5_frames_item_1_resource = RESOURCE_ID_MAD_02;
struct Frame sets_item_5_frames_item_1 = { 0.25, RESOURCE_ID_MAD_02 };
float sets_item_5_frames_item_2_duration = 0.25;
int sets_item_5_frames_item_2_resource = RESOURCE_ID_MAD_03;
struct Frame sets_item_5_frames_item_2 = { 0.25, RESOURCE_ID_MAD_03 };
float sets_item_5_frames_item_3_duration = 0.25;
int sets_item_5_frames_item_3_resource = RESOURCE_ID_MAD_04;
struct Frame sets_item_5_frames_item_3 = { 0.25, RESOURCE_ID_MAD_04 };
float sets_item_5_frames_item_4_duration = 0.25;
int sets_item_5_frames_item_4_resource = RESOURCE_ID_MAD_05;
struct Frame sets_item_5_frames_item_4 = { 0.25, RESOURCE_ID_MAD_05 };
float sets_item_5_frames_item_5_duration = 0.25;
int sets_item_5_frames_item_5_resource = RESOURCE_ID_MAD_04;
struct Frame sets_item_5_frames_item_5 = { 0.25, RESOURCE_ID_MAD_04 };
float sets_item_5_frames_item_6_duration = 0.25;
int sets_item_5_frames_item_6_resource = RESOURCE_ID_MAD_03;
struct Frame sets_item_5_frames_item_6 = { 0.25, RESOURCE_ID_MAD_03 };
float sets_item_5_frames_item_7_duration = 0.25;
int sets_item_5_frames_item_7_resource = RESOURCE_ID_MAD_02;
struct Frame sets_item_5_frames_item_7 = { 0.25, RESOURCE_ID_MAD_02 };
float sets_item_5_frames_item_8_duration = 0.25;
int sets_item_5_frames_item_8_resource = RESOURCE_ID_MAD_01;
struct Frame sets_item_5_frames_item_8 = { 0.25, RESOURCE_ID_MAD_01 };
struct Frame * sets_item_5_frames_items[9] = { &sets_item_5_frames_item_0, &sets_item_5_frames_item_1, &sets_item_5_frames_item_2, &sets_item_5_frames_item_3, &sets_item_5_frames_item_4, &sets_item_5_frames_item_5, &sets_item_5_frames_item_6, &sets_item_5_frames_item_7, &sets_item_5_frames_item_8 };
struct __array__Frame sets_item_5_frames = { 9, sets_item_5_frames_items };
int sets_item_5_identifier = ANIMATION_SET_MAD;
int sets_item_5_actions_item_0_identifier = ACTION_DEFAULT;
int sets_item_5_actions_item_0_target = ANIMATION_SET_BLINK;
struct Action sets_item_5_actions_item_0 = { ACTION_DEFAULT, ANIMATION_SET_BLINK };
struct Action * sets_item_5_actions_items[1] = { &sets_item_5_actions_item_0 };
struct __array__Action sets_item_5_actions = { 1, sets_item_5_actions_items };
struct AnimationSet sets_item_5 = { &sets_item_5_frames, ANIMATION_SET_MAD, &sets_item_5_actions };
float sets_item_6_frames_item_0_duration = 0.25;
int sets_item_6_frames_item_0_resource = RESOURCE_ID_WAKE_01;
struct Frame sets_item_6_frames_item_0 = { 0.25, RESOURCE_ID_WAKE_01 };
float sets_item_6_frames_item_1_duration = 0.25;
int sets_item_6_frames_item_1_resource = RESOURCE_ID_WAKE_02;
struct Frame sets_item_6_frames_item_1 = { 0.25, RESOURCE_ID_WAKE_02 };
float sets_item_6_frames_item_2_duration = 0.25;
int sets_item_6_frames_item_2_resource = RESOURCE_ID_WAKE_03;
struct Frame sets_item_6_frames_item_2 = { 0.25, RESOURCE_ID_WAKE_03 };
float sets_item_6_frames_item_3_duration = 0.25;
int sets_item_6_frames_item_3_resource = RESOURCE_ID_WAKE_04;
struct Frame sets_item_6_frames_item_3 = { 0.25, RESOURCE_ID_WAKE_04 };
float sets_item_6_frames_item_4_duration = 0.25;
int sets_item_6_frames_item_4_resource = RESOURCE_ID_WAKE_05;
struct Frame sets_item_6_frames_item_4 = { 0.25, RESOURCE_ID_WAKE_05 };
float sets_item_6_frames_item_5_duration = 0.25;
int sets_item_6_frames_item_5_resource = RESOURCE_ID_WAKE_06;
struct Frame sets_item_6_frames_item_5 = { 0.25, RESOURCE_ID_WAKE_06 };
float sets_item_6_frames_item_6_duration = 0.25;
int sets_item_6_frames_item_6_resource = RESOURCE_ID_WAKE_07;
struct Frame sets_item_6_frames_item_6 = { 0.25, RESOURCE_ID_WAKE_07 };
float sets_item_6_frames_item_7_duration = 0.25;
int sets_item_6_frames_item_7_resource = RESOURCE_ID_WAKE_08;
struct Frame sets_item_6_frames_item_7 = { 0.25, RESOURCE_ID_WAKE_08 };
float sets_item_6_frames_item_8_duration = 0.25;
int sets_item_6_frames_item_8_resource = RESOURCE_ID_WAKE_09;
struct Frame sets_item_6_frames_item_8 = { 0.25, RESOURCE_ID_WAKE_09 };
float sets_item_6_frames_item_9_duration = 0.25;
int sets_item_6_frames_item_9_resource = RESOURCE_ID_WAKE_10;
struct Frame sets_item_6_frames_item_9 = { 0.25, RESOURCE_ID_WAKE_10 };
float sets_item_6_frames_item_10_duration = 0.25;
int sets_item_6_frames_item_10_resource = RESOURCE_ID_WAKE_11;
struct Frame sets_item_6_frames_item_10 = { 0.25, RESOURCE_ID_WAKE_11 };
float sets_item_6_frames_item_11_duration = 0.25;
int sets_item_6_frames_item_11_resource = RESOURCE_ID_WAKE_12;
struct Frame sets_item_6_frames_item_11 = { 0.25, RESOURCE_ID_WAKE_12 };
float sets_item_6_frames_item_12_duration = 0.25;
int sets_item_6_frames_item_12_resource = RESOURCE_ID_WAKE_13;
struct Frame sets_item_6_frames_item_12 = { 0.25, RESOURCE_ID_WAKE_13 };
float sets_item_6_frames_item_13_duration = 0.5;
int sets_item_6_frames_item_13_resource = RESOURCE_ID_YAWN_01;
struct Frame sets_item_6_frames_item_13 = { 0.5, RESOURCE_ID_YAWN_01 };
float sets_item_6_frames_item_14_duration = 0.25;
int sets_item_6_frames_item_14_resource = RESOURCE_ID_WAKE_13;
struct Frame sets_item_6_frames_item_14 = { 0.25, RESOURCE_ID_WAKE_13 };
float sets_item_6_frames_item_15_duration = 0.25;
int sets_item_6_frames_item_15_resource = RESOURCE_ID_WAKE_14;
struct Frame sets_item_6_frames_item_15 = { 0.25, RESOURCE_ID_WAKE_14 };
float sets_item_6_frames_item_16_duration = 0.25;
int sets_item_6_frames_item_16_resource = RESOURCE_ID_WAKE_15;
struct Frame sets_item_6_frames_item_16 = { 0.25, RESOURCE_ID_WAKE_15 };
float sets_item_6_frames_item_17_duration = 0.25;
int sets_item_6_frames_item_17_resource = RESOURCE_ID_WAKE_16;
struct Frame sets_item_6_frames_item_17 = { 0.25, RESOURCE_ID_WAKE_16 };
float sets_item_6_frames_item_18_duration = 0.25;
int sets_item_6_frames_item_18_resource = RESOURCE_ID_WAKE_17;
struct Frame sets_item_6_frames_item_18 = { 0.25, RESOURCE_ID_WAKE_17 };
float sets_item_6_frames_item_19_duration = 0.25;
int sets_item_6_frames_item_19_resource = RESOURCE_ID_WAKE_18;
struct Frame sets_item_6_frames_item_19 = { 0.25, RESOURCE_ID_WAKE_18 };
struct Frame * sets_item_6_frames_items[20] = { &sets_item_6_frames_item_0, &sets_item_6_frames_item_1, &sets_item_6_frames_item_2, &sets_item_6_frames_item_3, &sets_item_6_frames_item_4, &sets_item_6_frames_item_5, &sets_item_6_frames_item_6, &sets_item_6_frames_item_7, &sets_item_6_frames_item_8, &sets_item_6_frames_item_9, &sets_item_6_frames_item_10, &sets_item_6_frames_item_11, &sets_item_6_frames_item_12, &sets_item_6_frames_item_13, &sets_item_6_frames_item_14, &sets_item_6_frames_item_15, &sets_item_6_frames_item_16, &sets_item_6_frames_item_17, &sets_item_6_frames_item_18, &sets_item_6_frames_item_19 };
struct __array__Frame sets_item_6_frames = { 20, sets_item_6_frames_items };
int sets_item_6_identifier = ANIMATION_SET_WAKE;
int sets_item_6_actions_item_0_identifier = ACTION_DEFAULT;
int sets_item_6_actions_item_0_target = ANIMATION_SET_BLINK;
struct Action sets_item_6_actions_item_0 = { ACTION_DEFAULT, ANIMATION_SET_BLINK };
struct Action * sets_item_6_actions_items[1] = { &sets_item_6_actions_item_0 };
struct __array__Action sets_item_6_actions = { 1, sets_item_6_actions_items };
struct AnimationSet sets_item_6 = { &sets_item_6_frames, ANIMATION_SET_WAKE, &sets_item_6_actions };
struct AnimationSet * sets_items[7] = { &sets_item_0, &sets_item_1, &sets_item_2, &sets_item_3, &sets_item_4, &sets_item_5, &sets_item_6 };
struct __array__AnimationSet sets = { 7, sets_items };
