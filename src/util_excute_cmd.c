/*
 * util_excut_cmd.c
 *
 *  Created on: Dec 30, 2015
 *      Author: TianyuanPan
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "util.h"
#include "util_excute_cmd.h"

static void init_file_t(FILE_T *pft)
{
	memset(pft->name, 0, 1024);
	pft->fp = NULL;
}


FILE_T * excute_open(const char *command, const char *mode)
{
	printf("A:excute_open: cmd -> %s\n", command);
	FILE_T *pft = NULL;
	char cmd_line[4096];
	unsigned int rand_n;

	rand_n = rand()%(99999 - 111 + 1) + 111;

	pft = safe_malloc(sizeof(FILE_T));//malloc(sizeof(FILE_T));

	printf("B:excute_open: malloc pft -> 0x%x\n", pft);
	if (!pft)
		return NULL;

	init_file_t(pft);


	sprintf(pft->name, "%s%u", PREFIX, rand_n);

	sprintf(cmd_line, "%s > %s", command, pft->name);
	printf("C:excute_open: cmd_line -> %s\n",cmd_line);
	if (execute(cmd_line, 1) != 0){
		free(pft);
		return NULL;
	}

	pft->fp = fopen(pft->name, mode);

	if (!pft->fp){
		free(pft);
		return NULL;
	}

	return pft;
}

size_t excute_read(void *ptr, size_t size, size_t nmemb, FILE_T *stream)
{
	return fread(ptr, size, nmemb, stream->fp);
}

size_t excute_write(void *ptr, size_t size, size_t nmemb, FILE_T *stream)
{
	return fwrite(ptr, size, nmemb, stream->fp);
}


int excute_close(FILE_T *pft)
{
	fclose(pft->fp);

	if (remove(pft->name) != 0){
		free(pft);
		return -1;
	}

	free(pft);
	return 0;
}
