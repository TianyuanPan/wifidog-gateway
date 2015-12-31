/*
 * util_excut_cmd.h
 *
 *  Created on: Dec 30, 2015
 *      Author: TianyuanPan
 */

#ifndef UTIL_EXCUT_CMD_H_
#define UTIL_EXCUT_CMD_H_

#define  PREFIX "/tmp/.dogexcutcmdf/docmdout_"

typedef  struct {
	char name[1024];
	FILE *fp;
}FILE_T;

FILE_T * excute_open(const char *command, const char *mode);

size_t excute_read(void *ptr, size_t size, size_t nmemb, FILE_T *stream);

size_t excute_write(void *ptr, size_t size, size_t nmemb, FILE_T *stream);


int excute_close(FILE_T *pft);


#endif /* UTIL_EXCUT_CMD_H_ */
