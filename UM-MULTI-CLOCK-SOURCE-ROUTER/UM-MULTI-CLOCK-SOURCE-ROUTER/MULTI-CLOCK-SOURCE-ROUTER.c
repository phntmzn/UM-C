//
//  STEP-SEQUENCER-ENGINE.c
//  UM-MULTI-CLOCK-SOURCE-ROUTER
//
//  Created by bRx86 on 4/15/25.
//

#include "MULTI-CLOCK-SOURCE-ROUTER.h"
#include <CoreMIDI/CoreMIDI.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_SOURCES 4
#define CLOCK_INTERVAL_US 20833  // 120 BPM = 500ms per beat / 24 MIDI clocks

static MIDIClientRef routerClient;
static MIDIPortRef inputPort;
static MIDIPortRef outputPort;
static MIDIEndpointRef sources[MAX_SOURCES];
static MIDIEndpointRef destination;

void clock_router_callback(const MIDIPacketList *pktlist, void *refCon, void *connRefCon) {
    MIDISend(outputPort, destination, pktlist);
}

void initialize_clock_router(void) {
    MIDIClientCreate(CFSTR("MultiClockRouter"), NULL, NULL, &routerClient);
    MIDIInputPortCreate(routerClient, CFSTR("InputPort"), clock_router_callback, NULL, &inputPort);
    MIDIOutputPortCreate(routerClient, CFSTR("OutputPort"), &outputPort);

    for (int i = 0; i < MAX_SOURCES; i++) {
        sources[i] = MIDIGetSource(i);
        if (sources[i] != 0) {
            MIDIPortConnectSource(inputPort, sources[i], NULL);
        }
    }

    destination = MIDIGetDestination(0);
    if (destination == 0) {
        printf("No MIDI destination available.\n");
    }
}

void simulate_clock_output(void) {
    Byte clock_msg[1] = {0xF8};
    MIDIPacketList packetList;
    MIDIPacket *packet;

    while (1) {
        packet = MIDIPacketListInit(&packetList);
        MIDIPacketListAdd(&packetList, sizeof(packetList), packet, 0, 1, clock_msg);
        MIDISend(outputPort, destination, &packetList);
        usleep(CLOCK_INTERVAL_US);
    }
}
