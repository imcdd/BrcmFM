//
//  BwfmHal.hpp
//  BrcmFM
//
//  Created by CDD on 5/5/21.
//  Copyright © 2021 CDD. All rights reserved.
//

#ifndef BwfmHal_hpp
#define BwfmHal_hpp

#include <HAL/ItlHalService.hpp>
#include <HAL/ItlDriverInfo.hpp>
#include <HAL/ItlDriverController.hpp>
//#include <compat.h>
//#include <linux/kernel.h>
//
//#include <sys/param.h>
//#include <sys/conf.h>
//#include <sys/kernel.h>
//#include <sys/malloc.h>
//#include <sys/mbuf.h>
//#include <sys/proc.h>
//#include <sys/socket.h>
//#include <sys/sockio.h>
//#include <sys/systm.h>
//#include <sys/endian.h>
//#include <sys/kpi_mbuf.h>
//
//#include <net/ethernet.h>
//#include <sys/pcireg.h>
//
//#include <IOKit/network/IOEthernetController.h>
//#include <IOKit/IOWorkLoop.h>
//#include <IOKit/network/IOGatedOutputQueue.h>
//#include <libkern/c++/OSString.h>
//#include <IOKit/IOService.h>
//#include <IOKit/pci/IOPCIDevice.h>
//#include <IOKit/IOLib.h>
//#include <libkern/OSKextLib.h>
//#include <IOKit/IOFilterInterruptEventSource.h>
//
//
//
#include <net/ethernet.h>
#include "bwfmreg.h"
#include "bwfmvar.h"
#include "if_bwfm_pci.h"

class Bwfm : public ItlHalService, ItlDriverInfo, ItlDriverController {
    OSDeclareDefaultStructors(Bwfm)
    
public:
    void free() override;
    virtual bool attach(IOPCIDevice *device) override;
    virtual void detach(IOPCIDevice *device) override;
    IOReturn enable(IONetworkInterface *netif) override;
    IOReturn disable(IONetworkInterface *netif) override;
    virtual struct ieee80211com *get80211Controller() override;
    
    virtual ItlDriverInfo *getDriverInfo() override;
    
    virtual ItlDriverController *getDriverController() override;
    
    //driver info
    virtual const char *getFirmwareVersion() override;
    
    virtual int16_t getBSSNoise() override;
    
    virtual bool is5GBandSupport() override;
    
    virtual int getTxNSS() override;
    
    virtual const char *getFirmwareName() override;
    
    virtual UInt32 supportedFeatures() override;

    virtual const char *getFirmwareCountryCode() override;

    virtual uint32_t getTxQueueSize() override;
    
    //driver controller
    virtual void clearScanningFlags() override;
    
    virtual IOReturn setMulticastList(IOEthernetAddress *addr, int count) override;
    
    
    void releaseAll();

    int tsleep_nsec(void *ident, int priority, const char *wmesg, int timo);
    
public:
    struct pci_attach_args pci;
    struct bwfm_pci_softc com;
};
#endif /* BwfmHal_hpp */
