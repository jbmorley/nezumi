#define STATE_PET_END 0
#define STATE_PET 1
#define STATE_BLINK 2
#define STATE_PET_START 3
#define STATE_WAKE 4
#define STATE_MAD 5
#define STATE_SLEEP 6
#define STATE_EAT 7

struct animation {
  int length;
  int *frames;
  int *durations;
};

struct states {
  int length;
  struct animation **states;
};

int resource_frames_pet_end[2] = { RESOURCE_ID_FRAME_PET_02, RESOURCE_ID_FRAME_PET_01 };
int resource_durations_pet_end[2] = { 150, 150 };
struct animation resource_state_pet_end = { 2, resource_frames_pet_end, resource_durations_pet_end };

int resource_frames_pet[5] = { RESOURCE_ID_FRAME_PET_03, RESOURCE_ID_FRAME_PET_04, RESOURCE_ID_FRAME_PET_05, RESOURCE_ID_FRAME_PET_04, RESOURCE_ID_FRAME_PET_03 };
int resource_durations_pet[5] = { 150, 150, 150, 150, 150 };
struct animation resource_state_pet = { 5, resource_frames_pet, resource_durations_pet };

int resource_frames_blink[4] = { RESOURCE_ID_FRAME_BLINK_01, RESOURCE_ID_FRAME_BLINK_02, RESOURCE_ID_FRAME_BLINK_03, RESOURCE_ID_FRAME_BLINK_02 };
int resource_durations_blink[4] = { 1000, 150, 150, 150 };
struct animation resource_state_blink = { 4, resource_frames_blink, resource_durations_blink };

int resource_frames_pet_start[2] = { RESOURCE_ID_FRAME_PET_01, RESOURCE_ID_FRAME_PET_02 };
int resource_durations_pet_start[2] = { 150, 150 };
struct animation resource_state_pet_start = { 2, resource_frames_pet_start, resource_durations_pet_start };

int resource_frames_wake[20] = { RESOURCE_ID_FRAME_WAKE_01, RESOURCE_ID_FRAME_WAKE_02, RESOURCE_ID_FRAME_WAKE_03, RESOURCE_ID_FRAME_WAKE_04, RESOURCE_ID_FRAME_WAKE_05, RESOURCE_ID_FRAME_WAKE_06, RESOURCE_ID_FRAME_WAKE_07, RESOURCE_ID_FRAME_WAKE_08, RESOURCE_ID_FRAME_WAKE_09, RESOURCE_ID_FRAME_WAKE_10, RESOURCE_ID_FRAME_WAKE_11, RESOURCE_ID_FRAME_WAKE_12, RESOURCE_ID_FRAME_WAKE_13, RESOURCE_ID_FRAME_YAWN_01, RESOURCE_ID_FRAME_WAKE_13, RESOURCE_ID_FRAME_WAKE_14, RESOURCE_ID_FRAME_WAKE_15, RESOURCE_ID_FRAME_WAKE_16, RESOURCE_ID_FRAME_WAKE_17, RESOURCE_ID_FRAME_WAKE_18 };
int resource_durations_wake[20] = { 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 500, 250, 250, 250, 250, 250, 250 };
struct animation resource_state_wake = { 20, resource_frames_wake, resource_durations_wake };

int resource_frames_mad[9] = { RESOURCE_ID_FRAME_MAD_01, RESOURCE_ID_FRAME_MAD_02, RESOURCE_ID_FRAME_MAD_03, RESOURCE_ID_FRAME_MAD_04, RESOURCE_ID_FRAME_MAD_05, RESOURCE_ID_FRAME_MAD_04, RESOURCE_ID_FRAME_MAD_03, RESOURCE_ID_FRAME_MAD_02, RESOURCE_ID_FRAME_MAD_01 };
int resource_durations_mad[9] = { 250, 250, 250, 250, 250, 250, 250, 250, 250 };
struct animation resource_state_mad = { 9, resource_frames_mad, resource_durations_mad };

int resource_frames_sleep[7] = { RESOURCE_ID_FRAME_SLEEP_01, RESOURCE_ID_FRAME_SLEEP_02, RESOURCE_ID_FRAME_SLEEP_03, RESOURCE_ID_FRAME_SLEEP_04, RESOURCE_ID_FRAME_SLEEP_05, RESOURCE_ID_FRAME_SLEEP_06, RESOURCE_ID_FRAME_SLEEP_07 };
int resource_durations_sleep[7] = { 250, 250, 250, 250, 250, 250, 250 };
struct animation resource_state_sleep = { 7, resource_frames_sleep, resource_durations_sleep };

int resource_frames_eat[1] = { RESOURCE_ID_FRAME_EAT_01 };
int resource_durations_eat[1] = { 2000 };
struct animation resource_state_eat = { 1, resource_frames_eat, resource_durations_eat };

struct animation *resource_states[8] = { &resource_state_pet_end, &resource_state_pet, &resource_state_blink, &resource_state_pet_start, &resource_state_wake, &resource_state_mad, &resource_state_sleep, &resource_state_eat };
struct states resources = { 8, resource_states };
