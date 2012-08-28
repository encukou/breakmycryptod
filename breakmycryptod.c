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
#include <poll.h>

int main() {
    int have;
    int add = 4096;
    int d = open("/dev/random", O_WRONLY);

    struct pollfd poll_data = {
        .fd=d,
        .events=POLLOUT,
        .revents=0,
    };

    printf("breakmycryptod: Your system is now INSECURE!!!\n");

    while(poll(&poll_data, 1, -1) > 0) {
        ioctl(d, RNDGETENTCNT, &have);
        printf("breakmycryptod: Entropy estimate fell to %d, replenishing.\n", have);

        ioctl(d, RNDADDTOENTCNT, &add);
    }

    printf("breakmycryptod: An error occurred, exiting.\n");
}
