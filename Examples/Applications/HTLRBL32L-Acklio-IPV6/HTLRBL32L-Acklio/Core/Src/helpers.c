/**
 * @copyright 2021-2022 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Flavien Moullec flavien@ackl.io
 *
 * @brief Implementation of AT helper functions
 */

#include "helpers.h"
#include "at.h"
#include "platform.h"
#include "tiny_sscanf.h"

void print_d(int value)
{
  AT_PRINTF("%d\n", value);
}

void print_u(unsigned int value)
{
  AT_PRINTF("%u\n", value);
}

void print_16_02x(uint8_t *pt)
{
  AT_PRINTF("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%"
            "02x:%02x:%02x\n",
            pt[0], pt[1], pt[2], pt[3], pt[4], pt[5], pt[6], pt[7], pt[8],
            pt[9], pt[10], pt[11], pt[12], pt[13], pt[14], pt[15]);
}

void print_16_02x_2(uint8_t *pt)
{
  AT_PRINTF("%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:"
            "%02x%02x\n",
            pt[0], pt[1], pt[2], pt[3], pt[4], pt[5], pt[6], pt[7], pt[8],
            pt[9], pt[10], pt[11], pt[12], pt[13], pt[14], pt[15]);
}

int sscanf_uint32_as_hhx(const char *from, uint32_t *value)
{
  return tiny_sscanf(
      from, "%hhx:%hhx:%hhx:%hhx", &((unsigned char *)(value))[3],
      &((unsigned char *)(value))[2], &((unsigned char *)(value))[1],
      &((unsigned char *)(value))[0]);
}

void print_uint32_as_02x(uint32_t value)
{
  AT_PRINTF("%02x:%02x:%02x:%02x\n", (unsigned)((unsigned char *)(&value))[3],
            (unsigned)((unsigned char *)(&value))[2],
            (unsigned)((unsigned char *)(&value))[1],
            (unsigned)((unsigned char *)(&value))[0]);
}

void print_8_02x(uint8_t *pt)
{
  AT_PRINTF("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n", pt[0], pt[1], pt[2],
            pt[3], pt[4], pt[5], pt[6], pt[7]);
}

int sscanf_16_hhx(const char *from, uint8_t *pt)
{
  // Does not use tiny_sscanf anymore, as we got some bad side effects.
  // Check that we have minimal required length.
  if (strlen(from) != 47) return 0;
  // Check that we have the 15 separators.
  for (uint8_t i = 0; i < 15; i++)
  {
    if (from[3 * i + 2] != ':') return 1;
  }
  // Now convert every element.
  char c;
  int16_t d;
  for (uint8_t i = 0; i < 16; i++)
  {
    c = from[3 * i];
    d = asciiHexToInt(c);
    if (d == -1) return 2;
    pt[i] = (uint8_t)(d << 4);
    c = from[3 * i + 1];
    d = asciiHexToInt(c);
    if (d == -1) return 2;
    pt[i] += (uint8_t)d;
  }
  return 16;
}

int sscanf_4_hx(const char *from, uint16_t *pt)
{
  return tiny_sscanf(from,
                     "%hx:%hx:%hx:%hx",
                     &pt[0], &pt[1], &pt[2], &pt[3]);
}

int8_t asciiHexToInt(char c)
{
  c |= 0x20;

  if (c >= '0' && c <= '9')
  {
    return c - '0';
  }
  else if (c >= 'a' && c <= 'f')
  {
    return (c - 'a') + 10;
  }
  else
  {
    return -1;
  }
}

int get_int_len(int value)
{
  int l = 1;

  while (value > 9)
  {
    l++;
    value /= 10;
  }

  return l;
}
