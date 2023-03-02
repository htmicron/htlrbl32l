/**
 *
 * Copyright (c) 2021 HT Micron Semicondutors S.A.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <stdint.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

/* Variables */
//extern int errno;
extern int __io_putchar(int ch) __attribute__((weak));

int _close(int32_t file) {
	return -1;
}

int _fstat(int32_t file, struct stat *st) {
	st->st_mode = S_IFCHR;
	return 0;
}

int _isatty(int32_t file) {
	return 1;
}

int _lseek(int32_t file, int32_t ptr, int32_t dir) {
	return 0;
}

__attribute__((weak)) int _write(int file, char *ptr, int len) {
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
		__io_putchar(*ptr++);

	return len;
}

__attribute__((weak)) int _read(int file, char *ptr, int len) {
	return len;
}

/************************ HT MICRON SEMICONDUCTORS S.A - syscalls.c *****END OF FILE****/
