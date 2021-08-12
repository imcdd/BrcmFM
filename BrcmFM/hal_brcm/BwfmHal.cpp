//
//  BwfmHal.cpp
//  BrcmFM
//
//  Created by CDD on 5/5/21.
//  Copyright © 2021 CDD. All rights reserved.
//


#include "compat.h"
#include "BwfmHal.hpp"

#include <libkern/c++/OSMetaClass.h>
//
//#include <linux/types.h>
//#include <linux/kernel.h>
//#include <FwData.h>
//#include <crypto/sha1.h>
//
//#include <IOKit/IOInterruptController.h>
//#include <IOKit/IOCommandGate.h>
//#include <IOKit/network/IONetworkMedium.h>
//#include <net/ethernet.h>
//
//#include <sys/_task.h>
//#include <sys/pcireg.h>
//#include <net80211/ieee80211_priv.h>

#define super ItlHalService
OSDefineMetaClassAndStructors(Bwfm, ItlHalService)

bool Bwfm::attach(IOPCIDevice *device)
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    pci.pa_tag = device;
    pci.workloop = getMainWorkLoop();
    com.bwfm = this;
    com.sc_sc.sc_ic.ic_ac.ac_if.controller = getController();
    if (!bwfm_pci_attach(&com, &pci)) {
        detach(device);
        releaseAll();
        return false;
    }
    return true;
}

void Bwfm::
detach(IOPCIDevice *device)
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    struct _ifnet *ifp = &com.sc_sc.sc_ic.ic_ac.ac_if;
    ieee80211_ifdetach(ifp);
    taskq_destroy(systq);
    taskq_destroy(com.sc_sc.sc_taskq);
    releaseAll();
}

void Bwfm::
releaseAll()
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    pci_intr_handle *intrHandler = com.ih;
    
    if (intrHandler) {
        if (intrHandler->intr && intrHandler->workloop) {
//            intrHandler->intr->disable();
            intrHandler->workloop->removeEventSource(intrHandler->intr);
            intrHandler->intr->release();
        }
        intrHandler->intr = NULL;
        intrHandler->workloop = NULL;
        intrHandler->arg = NULL;
        intrHandler->dev = NULL;
        intrHandler->func = NULL;
        intrHandler->release();
        com.ih = NULL;
    }
    pci.pa_tag = NULL;
    pci.workloop = NULL;
}

void Bwfm::free()
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    XYLog("%s\n", __FUNCTION__);
    super::free();
}

ItlDriverInfo *Bwfm::
getDriverInfo()
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    return this;
}

ItlDriverController *Bwfm::
getDriverController()
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    return this;
}

IOReturn Bwfm::enable(IONetworkInterface *netif)
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    XYLog("%s\n", __FUNCTION__);
    struct _ifnet *ifp = &com.sc_sc.sc_ic.ic_ac.ac_if;
    ifp->if_flags |= IFF_UP;
    //iwx_activate(&com, DVACT_WAKEUP);
    return kIOReturnSuccess;
}

IOReturn Bwfm::disable(IONetworkInterface *netif)
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    XYLog("%s\n", __FUNCTION__);
    struct _ifnet *ifp = &com.sc_sc.sc_ic.ic_ac.ac_if;
    ifp->if_flags &= ~IFF_UP;
    //iwx_activate(&com, DVACT_QUIESCE);
    return kIOReturnSuccess;
}

void Bwfm::
clearScanningFlags()
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    //com.sc_sc.sc_flags &= ~(IWX_FLAG_SCANNING | IWX_FLAG_BGSCAN);
}

IOReturn Bwfm::
setMulticastList(IOEthernetAddress *addr, int count)
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    //struct ieee80211com *ic = &com.sc_ic;
//    struct iwx_mcast_filter_cmd *cmd;
//    int len;
    //uint8_t addr_count;
    int err;
    
//    if (ic->ic_state != IEEE80211_S_RUN || ic->ic_bss == NULL)
//        return kIOReturnError;
//    addr_count = count;
//    if (count > IWX_MAX_MCAST_FILTERING_ADDRESSES)
//        addr_count = 0;
//    if (addr == NULL)
//        addr_count = 0;
//    len = roundup(sizeof(struct iwx_mcast_filter_cmd) + addr_count * ETHER_ADDR_LEN, 4);
//    XYLog("%s multicast count=%d bssid=%s\n", __FUNCTION__, count, ether_sprintf(ic->ic_bss->ni_bssid));
//    cmd = (struct iwx_mcast_filter_cmd *)malloc(len, 0, 0);
//    if (!cmd)
//        return kIOReturnError;
//    cmd->pass_all = addr_count == 0;
//    cmd->count = addr_count;
//    cmd->port_id = 0;
//    IEEE80211_ADDR_COPY(cmd->bssid, ic->ic_bss->ni_bssid);
//    if (addr_count > 0)
//        memcpy(cmd->addr_list,
//               addr->bytes, ETHER_ADDR_LEN * cmd->count);
//    err = iwx_send_cmd_pdu(&com, IWX_MCAST_FILTER_CMD, IWX_CMD_ASYNC, len,
//                     cmd);
//    ::free(cmd);
    err = 0;
    return err ? kIOReturnError : kIOReturnSuccess;
}

const char *Bwfm::
getFirmwareVersion()
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    //return com.sc_fwver;
    return NULL;
}

const char *Bwfm::
getFirmwareName()
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    //return com.sc_fwname;
    return NULL;
}

UInt32 Bwfm::
supportedFeatures()
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    return 0;
}

const char *Bwfm::
getFirmwareCountryCode()
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    //return com.sc_fw_mcc;
    return NULL;
}

uint32_t Bwfm::
getTxQueueSize()
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    //return IWX_TX_RING_COUNT;
    return 0;
}

int16_t Bwfm::
getBSSNoise()
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    //return com.sc_noise;
    return 0;
}

bool Bwfm::
is5GBandSupport()
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    //return com.sc_nvm.sku_cap_band_52GHz_enable;
    return true;
}

int Bwfm::
getTxNSS()
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    //return !com.sc_nvm.sku_cap_mimo_disable ? (iwx_mimo_enabled(&com) ? 2 : 1) : 1;
    return 0;
}

struct ieee80211com *Bwfm::
get80211Controller()
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    return &com.sc_sc.sc_ic;
}

int Bwfm::
tsleep_nsec(void *ident, int priority, const char *wmesg, int timo)
{
    XYLog("BwfmHal: %s\n", __FUNCTION__);
    return super::tsleep_nsec(ident, priority, wmesg, timo);
}

