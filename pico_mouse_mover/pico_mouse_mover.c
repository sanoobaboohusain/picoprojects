/*
 * Natural USB HID Mouse Movement
 * Creates natural mouse movement patterns with random timing every 5 seconds
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board_api.h"
#include "tusb.h"
#include "usb_descriptors.h"

//--------------------------------------------------------------------+
// NATURAL MOUSE MOVEMENT
//--------------------------------------------------------------------+

// Simple pseudo-random number generator
static uint32_t random_seed = 12345;

static uint32_t simple_random(void)
{
  random_seed = random_seed * 1103515245 + 12345;
  return (random_seed >> 16) & 0x7FFF;
}

// Generate random number in range [min, max]
static int32_t random_range(int32_t min, int32_t max)
{
  return min + (simple_random() % (max - min + 1));
}

static void send_natural_mouse_movement(void)
{
  // skip if hid is not ready yet
  if (!tud_hid_ready()) return;

  // Random movement between -15 to +15 pixels for more natural feel
  int8_t delta_x = (int8_t)random_range(-15, 15);
  int8_t delta_y = (int8_t)random_range(-15, 15);
  
  // Avoid zero movement (no point in sending a report with no movement)
  if (delta_x == 0 && delta_y == 0) {
    delta_x = random_range(1, 3);  // Small movement
    delta_y = random_range(1, 3);
  }
  
  // Send the mouse movement
  tud_hid_mouse_report(REPORT_ID_MOUSE, 0x00, delta_x, delta_y, 0, 0);
}

void mouse_task(void)
{
  // Main cycle: every 5 seconds
  const uint32_t cycle_interval_ms = 5000;  // 5 seconds
  static uint32_t cycle_start_ms = 0;
  
  // Movement pattern variables
  static uint32_t movement_start_ms = 0;
  static uint32_t movement_duration_ms = 0;
  static uint32_t next_movement_ms = 0;
  static bool movement_active = false;
  static bool cycle_started = false;

  uint32_t current_ms = board_millis();

  // Start new 5-second cycle
  if (current_ms - cycle_start_ms >= cycle_interval_ms) {
    cycle_start_ms = current_ms;
    movement_start_ms = current_ms;
    cycle_started = true;
    movement_active = true;
    
    // Random total duration for this cycle (1-3 seconds)
    movement_duration_ms = random_range(1000, 3000);
    
    // Start first movement immediately
    next_movement_ms = current_ms;
    
    // Update seed for better randomness
    random_seed += current_ms;
  }

  // Handle movement within the active period
  if (cycle_started && movement_active) {
    // Check if movement period is over
    if (current_ms - movement_start_ms >= movement_duration_ms) {
      movement_active = false;
    }
    
    // Send movement at random intervals
    if (current_ms >= next_movement_ms) {
      send_natural_mouse_movement();
      
      // Random delay until next movement (50-200ms for smooth movement)
      uint32_t delay = random_range(50, 200);
      next_movement_ms = current_ms + delay;
    }
  }
}

//--------------------------------------------------------------------+
// MAIN
//--------------------------------------------------------------------+

int main(void)
{
  board_init();

  // Initialize USB device
  tusb_rhport_init_t dev_init = {
    .role = TUSB_ROLE_DEVICE,
    .speed = TUSB_SPEED_AUTO
  };
  tusb_init(BOARD_TUD_RHPORT, &dev_init);

  board_init_after_tusb();

  while (1) {
    tud_task();        // TinyUSB device task
    mouse_task();      // Mouse movement task
  }
}

//--------------------------------------------------------------------+
// USB HID Callbacks (Required)
//--------------------------------------------------------------------+

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  (void) instance; (void) report_id; (void) report_type; (void) buffer; (void) reqlen;
  return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  (void) instance; (void) report_id; (void) report_type; (void) buffer; (void) bufsize;
}