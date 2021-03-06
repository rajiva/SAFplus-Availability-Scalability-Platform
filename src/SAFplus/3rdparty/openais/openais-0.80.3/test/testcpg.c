/*
 * Copyright (c) 2006-2007 Red Hat, Inc.
 *
 * All rights reserved.
 *
 * Author: Patrick Caulfield <pcaulfie@redhat.com>
 *
 * This software licensed under BSD license, the text of which follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the MontaVista Software, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "saAis.h"
#include "cpg.h"

static int quit = 0;
static int show_ip = 0;

void print_cpgname (struct cpg_name *name)
{
	int i;

	for (i = 0; i < name->length; i++) {
		printf ("%c", name->value[i]);
	}
}

void DeliverCallback (
	cpg_handle_t handle,
	struct cpg_name *groupName,
	uint32_t nodeid,
	uint32_t pid,
	void *msg,
	int msg_len)
{
	if (show_ip) {
		struct in_addr saddr;
		saddr.s_addr = nodeid;
		printf("DeliverCallback: message (len=%d)from node/pid %s/%d: '%s'\n",
		       msg_len, inet_ntoa(saddr), pid, (char *)msg);
	}
	else {
		printf("DeliverCallback: message (len=%d)from node/pid %d/%d: '%s'\n", msg_len, nodeid, pid, (char *)msg);
	}
}

void ConfchgCallback (
	cpg_handle_t handle,
	struct cpg_name *groupName,
	struct cpg_address *member_list, int member_list_entries,
	struct cpg_address *left_list, int left_list_entries,
	struct cpg_address *joined_list, int joined_list_entries)
{
	int i;
	struct in_addr saddr;

	printf("\nConfchgCallback: group '");
	print_cpgname(groupName);
	printf("'\n");
	for (i=0; i<joined_list_entries; i++) {
		if (show_ip) {
			saddr.s_addr = joined_list[i].nodeid;
			printf("joined node/pid: %s/%d reason: %d\n",
			       inet_ntoa (saddr), joined_list[i].pid,
			       joined_list[i].reason);
		}
		else {
			printf("joined node/pid: %x/%d reason: %d\n",
			       joined_list[i].nodeid, joined_list[i].pid,
			       joined_list[i].reason);
		}
	}

	for (i=0; i<left_list_entries; i++) {
		if (show_ip) {
			saddr.s_addr = left_list[i].nodeid;
			printf("left node/pid: %s/%d reason: %d\n",
			       inet_ntoa (saddr), left_list[i].pid,
			       left_list[i].reason);
		}
		else {
			printf("left node/pid: %x/%d reason: %d\n",
			       left_list[i].nodeid, left_list[i].pid,
			       left_list[i].reason);
		}
	}

	printf("nodes in group now %d\n", member_list_entries);
	for (i=0; i<member_list_entries; i++) {
		if (show_ip) {
			saddr.s_addr = member_list[i].nodeid;
			printf("node/pid: %s/%d\n",
			       inet_ntoa (saddr), member_list[i].pid);
		}
		else {
			printf("node/pid: %x/%d\n",
			       member_list[i].nodeid, member_list[i].pid);
		}
	}

	/* Is it us??
	   NOTE: in reality we should also check the nodeid */
	if (left_list_entries && left_list[0].pid == getpid()) {
		printf("We have left the building\n");
		quit = 1;
	}
}

cpg_callbacks_t callbacks = {
	.cpg_deliver_fn =            DeliverCallback,
	.cpg_confchg_fn =            ConfchgCallback,
};

void sigintr_handler (int signum) {
	exit (0);
}
static struct cpg_name group_name;

int main (int argc, char *argv[]) {
	cpg_handle_t handle;
	fd_set read_fds;
	int select_fd;
	int result;
	const char *options = "i";
	int opt;
	unsigned int nodeid;

	while ( (opt = getopt(argc, argv, options)) != -1 ) {
		switch (opt) {
		case 'i':
			show_ip = 1;
			break;
		}
	}

	if (argc > optind) {
		strcpy(group_name.value, argv[optind]);
		group_name.length = strlen(argv[optind])+1;
	}
	else {
		strcpy(group_name.value, "GROUP");
		group_name.length = 6;
	}

	result = cpg_initialize (&handle, &callbacks);
	if (result != SA_AIS_OK) {
		printf ("Could not initialize Cluster Process Group API instance error %d\n", result);
		exit (1);
	}
	result = cpg_local_get (handle, &nodeid);
	if (result != SA_AIS_OK) {
		printf ("Could not get local node id\n");
		exit (1);
	}

	printf ("Local node id is %x\n", nodeid);

	result = cpg_join(handle, &group_name);
	if (result != SA_AIS_OK) {
		printf ("Could not join process group, error %d\n", result);
		exit (1);
	}

	FD_ZERO (&read_fds);
	cpg_fd_get(handle, &select_fd);
	printf ("Type EXIT to finish\n");
	do {
		FD_SET (select_fd, &read_fds);
		FD_SET (STDIN_FILENO, &read_fds);
		result = select (select_fd + 1, &read_fds, 0, 0, 0);
		if (result == -1) {
			perror ("select\n");
		}
		if (FD_ISSET (STDIN_FILENO, &read_fds)) {
			char inbuf[132];
			struct iovec iov;

			fgets(inbuf, sizeof(inbuf), stdin);
			if (strncmp(inbuf, "EXIT", 4) == 0) {
				cpg_leave(handle, &group_name);
			}
			else {
				iov.iov_base = inbuf;
				iov.iov_len = strlen(inbuf)+1;
				cpg_mcast_joined(handle, CPG_TYPE_AGREED, &iov, 1);
			}
		}
		if (FD_ISSET (select_fd, &read_fds)) {
			if (cpg_dispatch (handle, CPG_DISPATCH_ALL) != SA_AIS_OK)
				exit(1);
		}
	} while (result && !quit);


	result = cpg_finalize (handle);
	printf ("Finalize  result is %d (should be 1)\n", result);
	return (0);
}
