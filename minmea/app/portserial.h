/*
 * This file is part of port serial.
 *
 * Copyright (c) 2008 Timur Sinitsyn
 * Copyright (c) 2011 Ferry Huberts
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*! \file */

#ifndef __PORT_SERIAL_H__
#define __PORT_SERIAL_H__

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop);
int gpsGetData(int fd, uint16_t times, uint8_t * pucBuffer, uint16_t usNBytes);

#ifdef  __cplusplus
}
#endif

#endif /* __PORT_SERIAL_H__ */
