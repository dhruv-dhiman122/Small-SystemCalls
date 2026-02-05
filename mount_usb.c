/*
 *  this file is trying to mount a SanDisk 64 GB to laptop
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mount.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define EXT_SUCCESS 0
#define EXT_FAILURE 1

void Mount() {
  const char* mountPoint = "/mnt/usb_sandisk";
  const char* device = "/dev/sdb2";
  const char* fstype = "ntfs-3g";  // NTFS filesystem
  
  //creating the mounting point
  if(mkdir(mountPoint, 0755) == 0) {
    printf("Mounting point is created without problem\n");
  }
  else {
    if(errno == EEXIST) {
      printf("Mounting point already exists, continuing...\n");
    } else {
      printf("Failed to create the mounting point: %s\n", strerror(errno));
      exit(EXT_FAILURE);
    }
  }
  
  //mounting the USB to the point
  if(mount(device, mountPoint, fstype, 0, NULL) == 0) {
    printf("Successfully mounted %s to %s\n", device, mountPoint);
  }
  else {
    printf("Failed to mount: %s\n", strerror(errno));
    exit(EXT_FAILURE);
  }
}

int main() {
  Mount();
  exit(EXT_SUCCESS);
}
