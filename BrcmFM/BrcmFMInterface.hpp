//
//  BrcmFMInterface.hpp
//  BrcmFM
//
//  Created by CDD on 5/9/21.
//  Copyright © 2021 CDD. All rights reserved.
//

#ifndef BrcmFMInterface_hpp
#define BrcmFMInterface_hpp

#include <IOKit/network/IOEthernetInterface.h>

#define ETHERNET_MTU            1500

class BrcmFMInterface : public IOEthernetInterface {
    OSDeclareDefaultStructors( BrcmFMInterface )
    
public:
    virtual bool init( IONetworkController * controller ) override;
    
protected:
    
    virtual void free() override;
    
    virtual bool setMaxTransferUnit(UInt32 mtu) override;
};

#endif /* BrcmFMInterface_hpp */
