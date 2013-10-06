#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x5C, 0x91, 0x99, 0xF8, 0xC3, 0x77, 0x46, 0x86, 0xBD, 0x63, 0x83, 0x2D, 0xC8, 0x07, 0x14, 0xC9 }
PBL_APP_INFO(MY_UUID,
             "Nezumi", "InSeven Limited",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
Layer layer;
BmpContainer image;

AppTimerHandle timer;

int frame;

struct animation {
  int length;
  int *frames;
};

int frames[3] = { RESOURCE_ID_FRAME_BLINK_01, RESOURCE_ID_FRAME_BLINK_02, RESOURCE_ID_FRAME_BLINK_03 };
struct animation blink = { 3, frames };


// Identifier for the timer.
#define ANIMATION_TIMER 1

void draw_bitmap(int resource_id, GContext* context) {
  // This appears to be the way we load an image resource, using the BmpContainer to
  // manage the memory for us.
  // TODO Consider whether we should be using a HeapBitmap here. It looks like this
  // might be the 'better' solution.
  bmp_init_container(resource_id, &image);

  // Draw the bitmap in the layer.
  // We make sure the dimensions of the GRect to draw into
  // are equal to the size of the bitmap--otherwise the image
  // will automatically tile. Which might be what *you* want.
  GRect destination = layer_get_frame(&image.layer.layer);
  destination.origin.y = 5;
  destination.origin.x = 5;
  graphics_draw_bitmap_in_rect(context, &image.bmp, destination);

  bmp_deinit_container(&image);

}

void layer_update_callback(Layer *me, GContext* ctx) {
  frame = (frame + 1) % blink.length;
  draw_bitmap(blink.frames[frame], ctx);
}

void handle_timer(AppContextRef ctx, AppTimerHandle handle, uint32_t cookie) {
  if (cookie == ANIMATION_TIMER) {
    layer_mark_dirty(&layer);
    timer = app_timer_send_event(ctx, 500, ANIMATION_TIMER);
  }

}

void handle_init(AppContextRef ctx) {
  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);

  // Init the layer for the minute display
  layer_init(&layer, window.layer.frame);
  layer.update_proc = &layer_update_callback;
  layer_add_child(&window.layer, &layer);

  // Load the resources
  resource_init_current_app(&VERSION);

  // Initialize the timer.
  timer = app_timer_send_event(ctx, 500, ANIMATION_TIMER);
}


void handle_deinit(AppContextRef ctx) {
  // TODO Consider whether we need to deinit anything in here.
  // bmp_deinit_container(&container);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit,
    .timer_handler = &handle_timer
  };

  frame = 0;

  app_event_loop(params, &handlers);
}


