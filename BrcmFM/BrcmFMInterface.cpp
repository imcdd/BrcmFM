//
//  BrcmFMInterface.cpp
//  BrcmFM
//
//  Created by CDD on 5/9/21.
//  Copyright © 2021 CDD. All rights reserved.
//

#include "BrcmFMInterface.hpp"

#define super IOEthernetInterface
OSDefineMetaClassAndStructors( BrcmFMInterface, IOEthernetInterface )

bool BrcmFMInterface::init(IONetworkController *controller)
{
    if (!super::init(controller))
        return false;
    setMaxTransferUnit(1482);
    return true;
}

bool BrcmFMInterface::setMaxTransferUnit(UInt32 mtu) {
    IOLog("itlwm setting MTU to %d\n", mtu);
    if (mtu > ETHERNET_MTU) {
        return false;
    }
    super::setMaxTransferUnit(mtu);
    return true;
}

void BrcmFMInterface::free()
{
    super::free();
}
