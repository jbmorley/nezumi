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

float set_frames_item_0_duration = 1.0;
int set_frames_item_0_resource = RESOURCE_ID_FRAME_BLINK_01;
struct Frame set_frames_item_0 = { 1.0, RESOURCE_ID_FRAME_BLINK_01 };
float set_frames_item_1_duration = 0.15;
int set_frames_item_1_resource = RESOURCE_ID_FRAME_BLINK_02;
struct Frame set_frames_item_1 = { 0.15, RESOURCE_ID_FRAME_BLINK_02 };
float set_frames_item_2_duration = 0.15;
int set_frames_item_2_resource = RESOURCE_ID_FRAME_BLINK_03;
struct Frame set_frames_item_2 = { 0.15, RESOURCE_ID_FRAME_BLINK_03 };
float set_frames_item_3_duration = 0.15;
int set_frames_item_3_resource = RESOURCE_ID_FRAME_BLINK_02;
struct Frame set_frames_item_3 = { 0.15, RESOURCE_ID_FRAME_BLINK_02 };
struct Frame * set_frames_items[4] = { &set_frames_item_0, &set_frames_item_1, &set_frames_item_2, &set_frames_item_3 };
struct __array__Frame set_frames = { 4, set_frames_items };
int set_actions_item_0_button = 1;
struct Action set_actions_item_0 = { 1 };
struct Action * set_actions_items[1] = { &set_actions_item_0 };
struct __array__Action set_actions = { 1, set_actions_items };
struct AnimationSet set = { &set_frames, &set_actions };
