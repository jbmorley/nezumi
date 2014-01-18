struct Frame {
  float duration;
  int resource;
};

struct Action {
  int button;
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
int sets_item_0_frames_item_0_resource = RESOURCE_ID_FRAME_BLINK_01;
struct Frame sets_item_0_frames_item_0 = { 1.0, RESOURCE_ID_FRAME_BLINK_01 };
float sets_item_0_frames_item_1_duration = 0.15;
int sets_item_0_frames_item_1_resource = RESOURCE_ID_FRAME_BLINK_02;
struct Frame sets_item_0_frames_item_1 = { 0.15, RESOURCE_ID_FRAME_BLINK_02 };
float sets_item_0_frames_item_2_duration = 0.15;
int sets_item_0_frames_item_2_resource = RESOURCE_ID_FRAME_BLINK_03;
struct Frame sets_item_0_frames_item_2 = { 0.15, RESOURCE_ID_FRAME_BLINK_03 };
float sets_item_0_frames_item_3_duration = 0.15;
int sets_item_0_frames_item_3_resource = RESOURCE_ID_FRAME_BLINK_02;
struct Frame sets_item_0_frames_item_3 = { 0.15, RESOURCE_ID_FRAME_BLINK_02 };
struct Frame * sets_item_0_frames_items[4] = { &sets_item_0_frames_item_0, &sets_item_0_frames_item_1, &sets_item_0_frames_item_2, &sets_item_0_frames_item_3 };
struct __array__Frame sets_item_0_frames = { 4, sets_item_0_frames_items };
int sets_item_0_actions_item_0_button = 1;
struct Action sets_item_0_actions_item_0 = { 1 };
struct Action * sets_item_0_actions_items[1] = { &sets_item_0_actions_item_0 };
struct __array__Action sets_item_0_actions = { 1, sets_item_0_actions_items };
struct AnimationSet sets_item_0 = { &sets_item_0_frames, &sets_item_0_actions };
struct AnimationSet * sets_items[1] = { &sets_item_0 };
struct __array__AnimationSet sets = { 1, sets_items };
