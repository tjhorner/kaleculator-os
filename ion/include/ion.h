#ifndef ION_ION_H
#define ION_ION_H

#include <ion/backlight.h>
#include <ion/battery.h>
#include <ion/charset.h>
#include <ion/display.h>
#include <ion/events.h>
#include <ion/keyboard.h>
#include <ion/led.h>
#include <ion/log.h>
#include <ion/power.h>
#include <stdint.h>
#include <string.h>

/* ION is not your regular library. It is a library you link against, but it
 * will take care of configuring the whole environment for you. In POSIX terms,
 * ION will implement the "main" function.
 * Don't worry though, once all its initialization will be performed, ION will
 * jump to your code at ion_app, which you have to implement yourself. */

void ion_app();

namespace Ion {

void msleep(long ms);
void usleep(long us);

/* CAUTION: This is a complete reset! */
void reset();

// CRC32 : non xor-ed, non reversed, direct, polynomial 4C11DB7
// Only accepts whole 32bit values
uint32_t crc32(const uint32_t * data, size_t length);

// Provides a true random number
uint32_t random();

}

#endif
