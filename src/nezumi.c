#include <pebble.h>
#include "animation.h"

// Screen furniture.
Window *window;
Layer *layer;

// Animation timer.
AppTimer *timer;

// Current animation frame.
int frame;


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

  draw_bitmap(set.frames->items[frame]->resource, context);
  frame = (frame + 1) % set.frames->length;

}

void timer_callback(void *callback_data) {

  layer_mark_dirty(layer);
  timer = app_timer_register(set.frames->items[frame]->duration * 1000, &timer_callback, NULL);

}


void handle_init() {

  window = window_create();

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


