#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x5C, 0x91, 0x99, 0xF8, 0xC3, 0x77, 0x46, 0x86, 0xBD, 0x63, 0x83, 0x2D, 0xC8, 0x07, 0x14, 0xC9 }
PBL_APP_INFO(MY_UUID,
             "Nezumi", "InSeven Limited",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;
BmpContainer container;


void handle_init(AppContextRef ctx) {
  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);

  // Load the resources
  resource_init_current_app(&VERSION);

  // Initialize the bitmap container.
  bmp_init_container(RESOURCE_ID_FRAME_BLINK_01, &container);

  // Add the bitmap container layer to the window layer.
  // Can we not draw directly into the window layer?
  layer_add_child(&window.layer, &container.layer.layer);

}

void handle_deinit(AppContextRef ctx) {
  bmp_deinit_container(&container);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit
  };
  app_event_loop(params, &handlers);
}
