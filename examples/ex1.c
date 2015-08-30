/* Simple example use of libwdog API for the watchdogd process monitor
 *
 * Copyright (c) 2015  Joachim Nilsson <troglobit@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include "../api.h"

char *__progname;

int main(void)
{
	int id, i;
	int ack;

	printf("%s: Starting ...\n", __progname);

	id = wdog_pmon_subscribe(NULL, 3000, &ack);
	if (id < 0) {
		perror("Failed connecting to pmon");
		return 1;
	}

	for (i = 0; i < 20; i++) {
		printf("%s: Kicking ...\n", __progname);
		if (wdog_pmon_kick(id, &ack))
			perror("Failed kicking");
		sleep(2);
	}

	printf("%s: Exiting ...\n", __progname);
	wdog_pmon_unsubscribe(id, ack);

	return 0;
}

/**
 * Local Variables:
 *  version-control: t
 *  indent-tabs-mode: t
 *  c-file-style: "linux"
 * End:
 */
