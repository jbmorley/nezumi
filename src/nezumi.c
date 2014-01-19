#include <pebble.h>
#include "actions.h"
#include "animation.h"

// Screen furniture.
Window *window;
Layer *layer;

// Animation timer.
AppTimer *timer;

// Current animation frame.
int frame = 0;
int set = 0;
int buttons = 0;

enum {
  ButtonSelect = 1,
  ButtonUp = 2,
  ButtonDown = 4
};


// Identifier for the timer.
#define ANIMATION_TIMER 1

// Draw a bitmap by resource id.
// TODO It would be good to include this as a separate header file
// and source file to avoid code bloat.
void draw_bitmap(int resource_id, GContext* context) {

  // Load the bitmap from the resources.
  GBitmap *bitmap = gbitmap_create_with_resource(resource_id);

  // Center the bitmap.
  GRect target = layer_get_frame(layer);
  GRect rect = GRect(0, 0, 90, 90);
  grect_align(&rect, &target, GAlignCenter, false);

  // Draw the bitmap in the layer.
  graphics_draw_bitmap_in_rect(context, bitmap, rect);

  // Destroy the bitmap.
  gbitmap_destroy(bitmap);

}

struct Action next_action(int identifier) {

  for (int i = 0; i < sets.items[set]->actions->length; i++) {
    struct Action *action = sets.items[set]->actions->items[i];
    if (action->identifier == identifier) {
      return *action;
    }
  }

  // If we have not managed to find an action we simply
  // maintain our current state.
  // TODO In the future we may wish this to reset our state.
  struct Action action = { identifier, set };
  return action;

}


void pick_next_set() {

  int identifier = ACTION_DEFAULT;
  if ((buttons & ButtonSelect) > 0) {
    identifier = ACTION_BUTTON_SELECT;
  } else if ((buttons & ButtonUp) > 0) {
    identifier = ACTION_BUTTON_UP;
  } else if ((buttons & ButtonDown) > 0) {
    identifier = ACTION_BUTTON_DOWN;
  }

  struct Action action = next_action(identifier);
  set = action.target;

}

// Render the animation frame.
void layer_update_callback(Layer *me, GContext* context) {

  draw_bitmap(sets.items[set]->frames->items[frame]->resource, context);
  frame = (frame + 1) % sets.items[set]->frames->length;

  // If we have reached the end of the set consider an alternative.
  if (frame == 0) {
    pick_next_set();
  }

}

void timer_callback(void *callback_data) {

  layer_mark_dirty(layer);
  timer = app_timer_register(sets.items[set]->frames->items[frame]->duration * 1000, &timer_callback, NULL);

}

void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  buttons |= ButtonSelect;
}

void select_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {
  buttons &= ~ButtonSelect;
}

void up_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  buttons |= ButtonUp;
}

void up_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {
  buttons &= ~ButtonUp;
}

void down_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  buttons |= ButtonDown;
}

void down_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {
  buttons &= ~ButtonDown;
}

void config_provider(Window *window) {

  // Configure the buttons.
  window_long_click_subscribe(BUTTON_ID_SELECT, 700, select_long_click_handler, select_long_click_release_handler);
  window_long_click_subscribe(BUTTON_ID_UP, 700, up_long_click_handler, up_long_click_release_handler);  
  window_long_click_subscribe(BUTTON_ID_DOWN, 700, down_long_click_handler, down_long_click_release_handler); 

}



void handle_init() {

  window = window_create();

  window_set_click_config_provider(window, (ClickConfigProvider) config_provider);

  // Present the window (animated)
  window_stack_push(window, true);

  // Init the layer for the main animation.
  // It looks like we may be able to do this with a BitmapLayer but the documentation
  // claims that it does the same thing under the hood anyhow.
  layer = layer_create(layer_get_frame(window_get_root_layer(window)));
  layer_set_update_proc(layer, &layer_update_callback);
  layer_add_child(window_get_root_layer(window), layer);

  // Initialize the timer.
  timer = app_timer_register(500, &timer_callback, NULL);
}


void handle_deinit() {
  // TODO Consider whether we need to deinit anything in here.
  // bmp_deinit_container(&container);
  layer_destroy(layer);
  window_destroy(window);
}

int main() {
  handle_init();
  app_event_loop();
  handle_deinit();
}


