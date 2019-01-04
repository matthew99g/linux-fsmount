// EXAMPLE: sudo ./main -t vfat /dev/sdb /media/okole

#include <sys/mount.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
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

	while ((opt = getopt(argc, argv, "o:t:f:")) != -1) {
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
						case 'b': flags |= MS_BIND;			break;
						case 'd': flags |= MS_DIRSYNC;		break;
						case 'l': flags |= MS_MANDLOCK;		break;
						case 'm': flags |= MS_MOVE;			break;
						case 'A': flags |= MS_NOATIME;		break;
						case 'V': flags |= MS_NODEV;		break;
						case 'D': flags |= MS_NODIRATIME;	break;
						case 'E': flags |= MS_NOEXEC;		break;
						case 'S': flags |= MS_NOSUID;		break;
						case 'r': flags |= MS_RDONLY;		break;
						case 'c': flags |= MS_REC;			break;
						case 'R': flags |= MS_REMOUNT;		break;
						case 's': flags |= MS_SYNCHRONOUS;	break;
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
