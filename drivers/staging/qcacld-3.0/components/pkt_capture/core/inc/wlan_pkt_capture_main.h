/*
 * Copyright (c) 2020 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/**
 * DOC: Declare private API which shall be used internally only
 * in pkt_capture component. This file shall include prototypes of
 * various notification handlers and logging functions.
 *
 * Note: This API should be never accessed out of pkt_capture component.
 */

#ifndef _WLAN_PKT_CAPTURE_MAIN_H_
#define _WLAN_PKT_CAPTURE_MAIN_H_

#include <qdf_types.h>
#include "wlan_pkt_capture_priv.h"
#include "wlan_pkt_capture_objmgr.h"
#include "wlan_objmgr_vdev_obj.h"

#define pkt_capture_log(level, args...)
#define pkt_capture_logfl(level, format, args...)
#define pkt_capture_fatal(format, args...)
#define pkt_capture_err(format, args...)
#define pkt_capture_warn(format, args...)
#define pkt_capture_info(format, args...)
#define pkt_capture_debug(format, args...)
#define PKT_CAPTURE_ENTER()
#define PKT_CAPTURE_EXIT()

#define NORMALIZED_TO_NOISE_FLOOR (-96)
/**
 * enum pkt_capture_tx_status - packet capture tx status
 * @pktcapture_tx_status_ok: successfully sent + acked
 * @pktcapture_tx_status_discard: discard - not sent
 * @pktcapture_tx_status_no_ack: no_ack - sent, but no ack
 *
 * This enum has tx status types for packet capture mode
 */
enum pkt_capture_tx_status {
	pkt_capture_tx_status_ok,
	pkt_capture_tx_status_discard,
	pkt_capture_tx_status_no_ack,
};

/**
 * pkt_capture_get_vdev() - Get pkt capture objmgr vdev.
 *
 * Return: pkt capture objmgr vdev
 */
struct wlan_objmgr_vdev *pkt_capture_get_vdev(void);

/**
 * pkt_capture_vdev_create_notification() - Handler for vdev create notify.
 * @vdev: vdev which is going to be created by objmgr
 * @arg: argument for notification handler.
 *
 * Allocate and attach vdev private object.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS
pkt_capture_vdev_create_notification(struct wlan_objmgr_vdev *vdev, void *arg);

/**
 * pkt_capture_vdev_destroy_notification() - Handler for vdev destroy notify.
 * @vdev: vdev which is going to be destroyed by objmgr
 * @arg: argument for notification handler.
 *
 * Deallocate and detach vdev private object.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS
pkt_capture_vdev_destroy_notification(struct wlan_objmgr_vdev *vdev, void *arg);

/**
 * pkt_capture_get_mode() - get packet capture mode
 * @psoc: pointer to psoc object
 *
 * Return: enum pkt_capture_mode
 */
enum pkt_capture_mode pkt_capture_get_mode(struct wlan_objmgr_psoc *psoc);

/**
 * pkt_capture_psoc_create_notification() - Handler for psoc create notify.
 * @psoc: psoc which is going to be created by objmgr
 * @arg: argument for notification handler.
 *
 * Allocate and attach psoc private object.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS
pkt_capture_psoc_create_notification(struct wlan_objmgr_psoc *psoc, void *arg);

/**
 * pkt_capture_psoc_destroy_notification() - Handler for psoc destroy notify.
 * @psoc: psoc which is going to be destroyed by objmgr
 * @arg: argument for notification handler.
 *
 * Deallocate and detach psoc private object.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS
pkt_capture_psoc_destroy_notification(struct wlan_objmgr_psoc *psoc, void *arg);

/**
 * ucfg_pkt_capture_psoc_config(): API to update the psoc user configurations
 * @psoc: objmgr psoc handle
 * @cfg: packet capture psoc configurations
 *
 * Return: QDF_STATUS
 */
QDF_STATUS pkt_capture_psoc_config(struct wlan_objmgr_psoc *psoc,
				   struct pkt_capture_cfg *cfg);

/**
 * pkt_capture_register_callbacks - Register packet capture callbacks
 * @vdev: pointer to wlan vdev object manager
 * @mon_cb: callback to call
 * @context: callback context
 *
 * Return: QDF_STATUS
 */
QDF_STATUS
pkt_capture_register_callbacks(struct wlan_objmgr_vdev *vdev,
			       QDF_STATUS (*mon_cb)(void *, qdf_nbuf_t),
			       void *context);

/**
 * pkt_capture_deregister_callbacks - De-register packet capture callbacks
 * @vdev: pointer to wlan vdev object manager
 *
 * Return: QDF_STATUS
 */
QDF_STATUS pkt_capture_deregister_callbacks(struct wlan_objmgr_vdev *vdev);

/**
 * pkt_capture_set_pktcap_mode - Set packet capture mode
 * @psoc: pointer to psoc object
 * @mode: mode to be set
 *
 * Return: None
 */
void pkt_capture_set_pktcap_mode(struct wlan_objmgr_psoc *psoc,
				 enum pkt_capture_mode mode);

/**
 * pkt_capture_get_pktcap_mode - Get packet capture mode
 *
 * Return: enum pkt_capture_mode
 */
enum pkt_capture_mode
pkt_capture_get_pktcap_mode(void);

/**
 * pkt_capture_drop_nbuf_list() - drop an nbuf list
 * @buf_list: buffer list to be dropepd
 *
 * Return: number of buffers dropped
 */
uint32_t pkt_capture_drop_nbuf_list(qdf_nbuf_t buf_list);

/**
 * pkt_capture_record_channel() - Update Channel Information
 * for packet capture mode
 *
 * Return: None
 */
void pkt_capture_record_channel(void);

/**
 * pkt_capture_mon() - Wrapper function to invoke mon cb
 * @cb_ctx: packet capture callback context
 * @msdu: packet
 * @vdev: objmgr vdev
 * @chan_num: channel number
 *
 * Return: None
 */
void pkt_capture_mon(struct pkt_capture_cb_context *cb_ctx,
		     qdf_nbuf_t msdu, struct wlan_objmgr_vdev *vdev,
		     uint8_t chan_num);
#endif /* end of _WLAN_PKT_CAPTURE_MAIN_H_ */
