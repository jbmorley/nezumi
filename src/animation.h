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
int sets_item_0_actions_item_0_identifier = 0;
int sets_item_0_actions_item_0_target = 0;
struct Action sets_item_0_actions_item_0 = { 0, 0 };
int sets_item_0_actions_item_1_identifier = 1;
int sets_item_0_actions_item_1_target = 1;
struct Action sets_item_0_actions_item_1 = { 1, 1 };
struct Action * sets_item_0_actions_items[2] = { &sets_item_0_actions_item_0, &sets_item_0_actions_item_1 };
struct __array__Action sets_item_0_actions = { 2, sets_item_0_actions_items };
struct AnimationSet sets_item_0 = { &sets_item_0_frames, &sets_item_0_actions };
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
int sets_item_1_actions_item_0_identifier = 0;
int sets_item_1_actions_item_0_target = 0;
struct Action sets_item_1_actions_item_0 = { 0, 0 };
int sets_item_1_actions_item_1_identifier = 1;
int sets_item_1_actions_item_1_target = 1;
struct Action sets_item_1_actions_item_1 = { 1, 1 };
struct Action * sets_item_1_actions_items[2] = { &sets_item_1_actions_item_0, &sets_item_1_actions_item_1 };
struct __array__Action sets_item_1_actions = { 2, sets_item_1_actions_items };
struct AnimationSet sets_item_1 = { &sets_item_1_frames, &sets_item_1_actions };
struct AnimationSet * sets_items[2] = { &sets_item_0, &sets_item_1 };
struct __array__AnimationSet sets = { 2, sets_items };
