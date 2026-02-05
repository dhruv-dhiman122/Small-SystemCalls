/*
 *  this file is trying to mount a SanDisk 64 GB to laptop
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mount.h>
#include <fcntl.h>
#include <sys/stat.h>

#define EXT_SUCCESS 0
#define EXT_FAILURE 1

void Mount() {
  const char* mountPoint = "/mnt/usb-sandisk";
  const char* device = "/dev/sdb1";
  
  //creating the mounting point
  if(mount(mountPoint, 0700) == 0) {
    printf("Mounting point is created without prooblem\n");
  }
  else {
    printf("Failed to create the mounting point\n");
    exit("EXT_FAILURE");
  }

  //mounting the USB to the point
  if(mount(mountPoint, device, NULL, MS_BIND, NULL) == 0) {
    printf("Created a bind mount point\n");
  }
  else {
    printf("Failed to create a bind mount point\n");
    exit(EXT_FAILURE);
  }
}

int main() {
  
  Mount();
  exit(EXT_SUCCESS);
}
