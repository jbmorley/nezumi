#include <pebble.h>
#include "animation.h"

// Screen furniture.
Window *window;
Layer *layer;

// Animation timer.
AppTimer *timer;

// Current animation frame.
int frame = 0;
int set = 0;
int nextSet = 0;


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

// Render the animation frame.
void layer_update_callback(Layer *me, GContext* context) {

  draw_bitmap(sets.items[set]->frames->items[frame]->resource, context);
  frame = (frame + 1) % sets.items[set]->frames->length;

  // If we have reached the end of the set consider an alternative.
  if (frame == 0) {
    set = nextSet;
  }

}

void timer_callback(void *callback_data) {

  layer_mark_dirty(layer);
  timer = app_timer_register(sets.items[set]->frames->items[frame]->duration * 1000, &timer_callback, NULL);

}


void down_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  nextSet = 1;
}

void select_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  nextSet = 0;
}

void select_multi_click_handler(ClickRecognizerRef recognizer, void *context) {

}
void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {

}

void select_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {

}


void config_provider(Window *window) {
 // single click / repeat-on-hold config:
  window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_SELECT, 1000, select_single_click_handler);
  // multi click config:
  window_multi_click_subscribe(BUTTON_ID_SELECT, 2, 10, 0, true, select_multi_click_handler);
  // long click config:
  window_long_click_subscribe(BUTTON_ID_SELECT, 700, select_long_click_handler, select_long_click_release_handler);
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


