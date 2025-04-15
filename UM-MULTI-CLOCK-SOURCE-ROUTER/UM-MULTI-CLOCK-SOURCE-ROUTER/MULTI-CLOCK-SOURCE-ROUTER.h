//
//  STEP-SEQUENCER-ENGINE.h
//  UM-MULTI-CLOCK-SOURCE-ROUTER
//
//  Created by bRx86 on 4/15/25.
//

#ifndef MULTI_CLOCK_SOURCE_ROUTER_h
#define MULTI_CLOCK_SOURCE_ROUTER_h

#include <CoreMIDI/CoreMIDI.h>
#include <stdio.h>

#define MAX_SOURCES 4
#define CLOCK_INTERVAL_US 20833  // For 120 BPM

void initialize_clock_router(void);
void simulate_clock_output(void);
void clock_router_callback(const MIDIPacketList *pktlist, void *refCon, void *connRefCon);

extern MIDIClientRef routerClient;
extern MIDIPortRef inputPort;
extern MIDIPortRef outputPort;
extern MIDIEndpointRef sources[MAX_SOURCES];
extern MIDIEndpointRef destination;

#endif /* MULTI_CLOCK_SOURCE_ROUTER_h */
