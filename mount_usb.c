/*
 *  this file is trying to mount a SanDisk 64 GB to laptop
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mount.h>

#define EXT_SUCCESS 0
#define EXT_FAILURE 1

void MountSUB() {
  const char* mountPoint = "/mnt/usb-sandisk";
  const char* device = "/dev/sdb1";
}

int main() {
  

  exit(EXT_SUCCESS);
}
