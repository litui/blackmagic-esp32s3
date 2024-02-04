#if ENABLE_DEBUG != 1
#include <sys/stat.h>
#include <string.h>

typedef struct stat stat_s;
#endif

#include "general.h"
#include "platform.h"
#include "gdb_if.h"
#include "usb_serial.h"
#ifdef PLATFORM_HAS_TRACESWO
#include "traceswo.h"
#endif
// #include "aux_serial.h"
#include "rtt.h"
#include "rtt_if.h"
#include "usb_types.h"

#include "usb-glue.h"

static bool gdb_serial_dtr = true;

static void usb_serial_set_state(usbd_device *dev, uint16_t iface, uint8_t ep);

static void debug_serial_send_callback(usbd_device *dev, uint8_t ep);
static void debug_serial_receive_callback(usbd_device *dev, uint8_t ep);

static bool debug_serial_send_complete = true;

#if ENABLE_DEBUG == 1 && defined(PLATFORM_HAS_DEBUG)
/*
 * This call initialises "SemiHosting", only we then do our own SVC interrupt things to
 * route all output through to the debug USB serial interface if debug_bmp is true.
 *
 * https://github.com/mirror/newlib-cygwin/blob/master/newlib/libc/sys/arm/syscalls.c#L115
 */
void initialise_monitor_handles(void);

static char debug_serial_debug_buffer[512];
static uint8_t debug_serial_debug_write_index;
static uint8_t debug_serial_debug_read_index;
#endif

void debug_serial_send_stdout(const uint8_t *const data, const size_t len)
{
    usb_glue_cdc_send(data, len, true);
}