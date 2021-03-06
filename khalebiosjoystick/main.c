#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


struct js_event {
          __u32 time;     // event timestamp in milliseconds
          __s16 value;    // value
          __u8 type;      // event type
          __u8 number;    // axis/button number
  };

int open_joystick(char *device_name) {
  int joystick_fd = -1;

  if (device_name == NULL) return joystick_fd;

  joystick_fd = open(device_name, O_RDONLY | O_NONBLOCK);

  if (joystick_fd < 0) {
    printf("Could not locate joystick device %s\n", device_name);
    return joystick_fd;
  }

  return joystick_fd;
}


int read_event(int joystick_fd, struct js_event *jse) {
  int bytes;

  bytes = read(joystick_fd, jse, sizeof(*jse));

  if (bytes == -1) return 0;
  if (bytes == sizeof(*jse)) return 1;

  printf("Unexpected bytes from joystick:%d\n", bytes);

  return -1;
}


int main() {
 int fd, result;
  struct js_event jse;
  fd = open_joystick("/dev/input/js0");



 while (1) {
    result = read_event(fd, &jse);
    usleep(1000);
    if (result == 1)
      printf("Event: time %8u, value %8hd, type: %3u, axis/button: %u\n",
             jse.time, jse.value, jse.type, jse.number);
  }


  return 0;
}
