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

#define VERBOSE 1

extern struct reljmp rj_printk;

static int __init reljmp_module_init(void)
{
	int retval;

	/* Initialize the jump(s) */
	retval = reljmp_init_once();
	if (retval)
		return retval;
	retval = reljmp_init(&rj_printk);
	if (retval)
		return retval;

	/* Register the jump(s) */
	reljmp_register(&rj_printk, VERBOSE);

	printk("reljmp: module loaded\n");
	return 0;
}

static void __exit reljmp_module_exit(void)
{
	/* Unregister the jumps */
	reljmp_unregister(&rj_printk, VERBOSE);

	printk("reljmp: module unloaded\n");
}

MODULE_AUTHOR("Juerg Haefliger <juerg.haefliger@hp.com>");
MODULE_DESCRIPTION("Replace kernel functions");
MODULE_LICENSE("GPL");

module_init(reljmp_module_init);
module_exit(reljmp_module_exit);
