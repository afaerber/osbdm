/*
 * Test code for communicating with Freescale StarterTRAK TRK-MPC5604B
 *
 * Copyright (c) 2011 Andreas Färber <andreas.faerber@web.de>
 *
 * Licensed under the GNU GPL version 2 or (at your option) any later version.
 */

#include <stdlib.h>
#include <stdio.h>
#include <libusb-1.0/libusb.h>
#include "qorivva.h"

static libusb_device_handle *osbdm_open(libusb_context *usb_context)
{
    libusb_device_handle *handle;
    handle = libusb_open_device_with_vid_pid(usb_context, USB_VID_FREESCALE, USB_PID_FREESCALE_OSBDM);
    if (handle == NULL)
        return NULL;

    int ret;

    ret = libusb_kernel_driver_active(handle, 0);
    if (ret == 1) {
        printf("kernel driver active\n");
    } else if (ret == 0) {
        //printf("kernel driver not active\n");
    } else {
        fprintf(stderr, "libusb_kernel_driver_active = %d\n", ret);
    }
    ret = libusb_claim_interface(handle, 0);
    if (ret != LIBUSB_SUCCESS) {
        fprintf(stderr, "claiming interface failed: %d\n", ret);
        libusb_close(handle);
        return NULL;
    }

    return handle;
}

static void osbdm_close(libusb_device_handle *handle)
{
    libusb_release_interface(handle, 0);
    libusb_close(handle);
}

static void test(libusb_device_handle *handle)
{
}

static void connect(libusb_context *usb_context)
{
    printf("Opening TRK-MPC5604B device...\n");
    libusb_device_handle *handle = osbdm_open(usb_context);
    if (handle == NULL) {
        fprintf(stderr, "Opening the device failed.\n");
        return;
    }
    test(handle);
    osbdm_close(handle);
}

int main(void)
{
    int ret;
    libusb_context *usb_context;
    ret = libusb_init(&usb_context);
    if (ret != 0) {
        fprintf(stderr, "USB init failed.\n");
        return -1;
    }

    connect(usb_context);

    libusb_exit(usb_context);
    return 0;
}
