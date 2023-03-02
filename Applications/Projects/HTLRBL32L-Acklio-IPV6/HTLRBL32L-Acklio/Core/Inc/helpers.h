/**
 * @copyright 2021 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Flavien Moullec flavien@ackl.io
 *
 * @brief AT helper functions
 */

#ifndef AT_HELPERS_H
#define AT_HELPERS_H

#include <stdint.h>

#define IPV6_ADDRESS_LENGTH_BYTES 16
#define IPV6_ADDRESS_PREFIX_LENGTH_BYTES 8
#define IPV6_ADDRESS_IID_LENGTH_BYTES 8
#define IPV4_ADDRESS_LENGTH_BYTES 4
#define IP_ADDRESS_MAX_LENGTH_BYTES IPV6_ADDRESS_LENGTH_BYTES

void print_d(int value);

void print_u(unsigned int value);

void print_16_02x(uint8_t *pt);

void print_16_02x_2(uint8_t *pt);

int sscanf_uint32_as_hhx(const char *from, uint32_t *value);

void print_uint32_as_02x(uint32_t value);

void print_8_02x(uint8_t *pt);

/**
 * Required input format: hh:hh:...hh.
 *   h: an hexadecimal character, 0..9, a..f. Lower case or upper case. Must be ASCII.
 *   hh repeated 16 times
 * Returns 0 if incorrect length, 1 if not enough separators, 2 if conversion error.
 */
int sscanf_16_hhx(const char *from, uint8_t *pt);

/**
 * Scans IPv6 prefix or IID.
 */
int sscanf_4_hx(const char *from, uint16_t *pt);

/**
 * Input: an ASCII hexadecimal character, in '0' to '9', 'a' to 'f', 'A' to 'F'.
 * Returns -1 for invalid input character.
 */
int8_t asciiHexToInt(char c);

int get_int_len(int value);

#endif /* AT_HELPERS_H */
