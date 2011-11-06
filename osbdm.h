/*
 * Helpers for communicating with P&E micro OSBDM
 *
 * Copyright (c) 2011 Andreas Färber <andreas.faerber@web.de>
 *
 * Licensed under the GNU LGPL version 2.1 or (at your option) any later version.
 */
#ifndef OSBDM_H
#define OSBDM_H


#include <libusb-1.0/libusb.h>


int osbdm_get_version(libusb_device_handle *handle, uint16_t *version);


#endif
