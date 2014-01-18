struct Frame {
  float * duration;
  int * resource;
};

struct Action {
  int * button;
};

struct __array__Frame {
  int * length;
  struct Frame * * items;
};

struct __array__Action {
  int * length;
  struct Action * * items;
};

struct AnimationSet {
  struct __array__Frame * frames;
  struct __array__Action * actions;
};

int action_button = 1;
struct Action action = { &action_button };
float set_frames_item_0_duration = 1.0;
int set_frames_item_0_resource = RESOURCE_ID_FRAME_BLINK_01;
struct Frame set_frames_item_0 = { &set_frames_item_0_duration, &set_frames_item_0_resource };
float set_frames_item_1_duration = 0.15;
int set_frames_item_1_resource = RESOURCE_ID_FRAME_BLINK_02;
struct Frame set_frames_item_1 = { &set_frames_item_1_duration, &set_frames_item_1_resource };
float set_frames_item_2_duration = 0.15;
int set_frames_item_2_resource = RESOURCE_ID_FRAME_BLINK_03;
struct Frame set_frames_item_2 = { &set_frames_item_2_duration, &set_frames_item_2_resource };
float set_frames_item_3_duration = 0.15;
int set_frames_item_3_resource = RESOURCE_ID_FRAME_BLINK_02;
struct Frame set_frames_item_3 = { &set_frames_item_3_duration, &set_frames_item_3_resource };
struct Frame * set_frames_items[4] = { &set_frames_item_0, &set_frames_item_1, &set_frames_item_2, &set_frames_item_3 };
int set_frames_length = 4;
struct __array__Frame set_frames = { &set_frames_length, set_frames_items };
int set_actions_item_0_button = 1;
struct Action set_actions_item_0 = { &set_actions_item_0_button };
struct Action * set_actions_items[1] = { &set_actions_item_0 };
int set_actions_length = 1;
struct __array__Action set_actions = { &set_actions_length, set_actions_items };
struct AnimationSet set = { &set_frames, &set_actions };
float complexArray_item_0_duration = 0.5;
int complexArray_item_0_resource = 1;
struct Frame complexArray_item_0 = { &complexArray_item_0_duration, &complexArray_item_0_resource };
struct Frame * complexArray_items[1] = { &complexArray_item_0 };
int complexArray_length = 1;
struct __array__Frame complexArray = { &complexArray_length, complexArray_items };
