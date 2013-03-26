/*
 * Copyright (C) 2013 Hewlett-Packard Development Company, L.P.
 *
 * Author: Juerg Haefliger <juerg.haefliger@hp.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/module.h>

#include "reljmp.h"

/* This is our function that replaces the kernel's original printk() */
static int __attribute__ ((used)) reljmp_printk(const char *fmt, ...)
{
	va_list args;
	int r;

	vprintk("Redirected: ", args);

	va_start(args, fmt);
	r = vprintk(fmt, args);
	va_end(args);

	return r;
}

/* Dummy init handler. Can be used to lookup addresses of symbols that our
 * replacement function requires but which are not exported to modules */
int reljmp_init_handler(void)
{
	return 0;
}

/* Set up the jump structure. All that's required is:
 * from_symbol_name: name of the original kernel function that is to be
 *                   replaced
 * to_symbol_name:   name of our function that replaces the original function
 * init_handler:     pointer to an init handler that is called at
 *                   initialization time */
struct reljmp rj_printk = {
	.from_symbol_name = "printk",
        .to_symbol_name = "reljmp_printk",
        .init_handler = reljmp_init_handler,
};
