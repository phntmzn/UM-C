//
//  STEP-SEQUENCER-ENGINE.c
//  UM-STEP-ARPEGGIATOR
//
//  Created by bRx86 on 4/15/25.
//

#include "STEP-SEQUENCER-ENGINE.h"
#include <CoreMIDI/CoreMIDI.h>
#include <unistd.h>
#include <stdio.h>

static MIDIClientRef arpeggiatorClient;
static MIDIPortRef arpeggiatorOutPort;
static MIDIEndpointRef arpeggiatorDest;

// Notes in arpeggio (C major triad)
static int arpeggioNotes[] = {60, 64, 67};
static int numNotes = sizeof(arpeggioNotes) / sizeof(int);

// Tempo in BPM and time per note (quarter note)
#define ARP_BPM 120
#define NOTE_DURATION_MS 250

void send_arp_note_on(int note) {
    Byte buffer[3] = {0x90, note, 100};
    MIDIPacketList packetList;
    MIDIPacket *packet = MIDIPacketListInit(&packetList);
    packet = MIDIPacketListAdd(&packetList, sizeof(packetList), packet, 0, 3, buffer);
    MIDISend(arpeggiatorOutPort, arpeggiatorDest, &packetList);
}

void send_arp_note_off(int note) {
    Byte buffer[3] = {0x80, note, 0};
    MIDIPacketList packetList;
    MIDIPacket *packet = MIDIPacketListInit(&packetList);
    packet = MIDIPacketListAdd(&packetList, sizeof(packetList), packet, 0, 3, buffer);
    MIDISend(arpeggiatorOutPort, arpeggiatorDest, &packetList);
}

void initialize_arpeggiator(void) {
    MIDIClientCreate(CFSTR("StepArpeggiator"), NULL, NULL, &arpeggiatorClient);
    MIDIOutputPortCreate(arpeggiatorClient, CFSTR("ArpOutputPort"), &arpeggiatorOutPort);
    arpeggiatorDest = MIDIGetDestination(0);
    if (arpeggiatorDest == 0) {
        printf("No MIDI destination available.\n");
    }
}

void run_arpeggiator(void) {
    int step = 0;
    while (1) {
        int note = arpeggioNotes[step];
        send_arp_note_on(note);
        usleep(NOTE_DURATION_MS * 1000 / 2);
        send_arp_note_off(note);
        usleep(NOTE_DURATION_MS * 1000 / 2);
        step = (step + 1) % numNotes;
    }
}
