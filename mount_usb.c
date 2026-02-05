#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define EXT_SUCCESS 0
#define EXT_FAILURE 1

void Mount() {
  const char* mountPoint = "/mnt/usb_sandisk";
  const char* device = "/dev/sdb1";
  
  printf("Step 1: Unmounting if already mounted...\n");
  umount2(device, MNT_FORCE);
  umount2(mountPoint, MNT_FORCE);
  
  printf("Step 2: Removing old mount point...\n");
  rmdir(mountPoint);
  
  printf("Step 3: Creating fresh mount point...\n");
  if(mkdir(mountPoint, 0755) != 0) {
    printf("mkdir failed: %s\n", strerror(errno));
    exit(EXT_FAILURE);
  }
  
  printf("Step 4: Mounting %s to %s...\n", device, mountPoint);
  
  // Try ntfs3
  if(mount(device, mountPoint, "ntfs3", 0, NULL) == 0) {
    printf("✓ Successfully mounted with ntfs3!\n");
    return;
  }
  printf("ntfs3 failed: %s\n", strerror(errno));
  
  // Try ntfs
  if(mount(device, mountPoint, "ntfs", 0, NULL) == 0) {
    printf("✓ Successfully mounted with ntfs!\n");
    return;
  }
  printf("ntfs failed: %s\n", strerror(errno));
  
  // Try vfat (just in case)
  if(mount(device, mountPoint, "vfat", 0, NULL) == 0) {
    printf("✓ Successfully mounted with vfat!\n");
    return;
  }
  
  printf("✗ All mount attempts failed\n");
  exit(EXT_FAILURE);
}

int main() {
  if(getuid() != 0) {
    printf("ERROR: Must run as root\n");
    exit(EXT_FAILURE);
  }
  
  Mount();
  exit(EXT_SUCCESS);
}
