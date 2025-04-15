//
//  UM-SYNC-TO-DAW.c
//  UM-SYNC-TO-DAW
//
//  Created by bRx86 on 4/15/25.
//

#include "UM-SYNC-TO-DAW.h"
#include <CoreMIDI/CoreMIDI.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define SYNC_BPM 120
#define MIDI_CLOCK_RATE_US (500000 / 24)  // 500ms per beat / 24 clocks

static MIDIClientRef syncClient;
static MIDIPortRef syncOutPort;
static MIDIEndpointRef dawDest;

void initialize_daw_sync(void) {
    MIDIClientCreate(CFSTR("UMSyncToDAW"), NULL, NULL, &syncClient);
    MIDIOutputPortCreate(syncClient, CFSTR("UMSyncOutPort"), &syncOutPort);
    dawDest = MIDIGetDestination(0);
    if (dawDest == 0) {
        printf("No DAW destination found.\n");
    }
}

void send_midi_clock(void) {
    Byte msg[1] = {0xF8};  // MIDI Clock
    MIDIPacketList packetList;
    MIDIPacket *packet = MIDIPacketListInit(&packetList);
    packet = MIDIPacketListAdd(&packetList, sizeof(packetList), packet, 0, 1, msg);
    MIDISend(syncOutPort, dawDest, &packetList);
}

void send_start_signal(void) {
    Byte msg[1] = {0xFA};  // Start
    MIDIPacketList packetList;
    MIDIPacket *packet = MIDIPacketListInit(&packetList);
    packet = MIDIPacketListAdd(&packetList, sizeof(packetList), packet, 0, 1, msg);
    MIDISend(syncOutPort, dawDest, &packetList);
}

void run_daw_sync_loop(void) {
    send_start_signal();
    while (1) {
        send_midi_clock();
        usleep(MIDI_CLOCK_RATE_US);
    }
}
