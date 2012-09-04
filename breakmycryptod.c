/*
 *  breakmycryptod
 *  Copyright (C) 2012  Petr Viktorin <encukou@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/random.h>
#include <poll.h>
#include <unistd.h>

int main() {
    if(geteuid()) {
        printf("You are not root. Go away.\n");
        return 1;
    }

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
    return 1;
}
