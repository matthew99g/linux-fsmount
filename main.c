// EXAMPLE: sudo ./main -t vfat /dev/sdb /media/okole

#include <sys/mount.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "errlib.h"
#include "mem.h"

int
main (const int argc, char *argv[])
{
	unsigned long flags;
	char *data, *fstype;
	int j, opt;

	flags = 0;
	data = 0x0;
	fstype = 0x0;

	while ((opt = getopt(argc, argv, "o:t:f")) != -1) {
		switch (opt) {
			case 'o':
				data = optarg;
				break;
			case 't':
				fstype = optarg;
				break;
			case 'f':
				for (j = 0; j < strlen(optarg); j++) {
					switch (optarg[j]) {
						case 'b': flags |= MS_BIND;
						case 'd': flags |= MS_DIRSYNC;
						case 'l': flags |= MS_MANDLOCK;
						case 'm': flags |= MS_MOVE;
						case 'A': flags |= MS_NOATIME;
						case 'V': flags |= MS_NODEV;
						case 'D': flags |= MS_NODIRATIME;
						case 'E': flags |= MS_NOEXEC;
						case 'S': flags |= MS_NOSUID;
						case 'r': flags |= MS_RDONLY;
						case 'c': flags |= MS_REC;
						case 'R': flags |= MS_REMOUNT;
						case 's': flags |= MS_SYNCHRONOUS;
						default: fatal("User input error");
					}
				}
				break;
			default:
				fatal("User input error");
		}
	}

	if (argc != optind + 2)
		fatal("Wrong number of arguments");

	if (mount(argv[optind], argv[optind + 1], fstype, flags, data) == -1)
		errnoExit("Failed to mount device\n");

	printf("Mounted %s on %s successfully.\n", argv[optind], argv[optind + 1]);
	exit(EXIT_SUCCESS);
}
