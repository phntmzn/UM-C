//
//  STEP-SEQUENCER-ENGINE.c
//  UM-STEP-SEQUNCER-ENGINE
//
//  Created by bRx86 on 4/15/25.
//

#include "STEP-SEQUENCER-ENGINE.h"
#include <CoreMIDI/CoreMIDI.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

#define NUM_STEPS 16
#define TEMPO_BPM 120
#define TICKS_PER_BEAT 24

static MIDIClientRef midiClient;
static MIDIPortRef midiOutPort;
static MIDIEndpointRef dest;

// Step sequence (each step is a MIDI note or 0 for rest)
static int steps[NUM_STEPS] = {
    60, 0, 60, 0,
    62, 0, 62, 0,
    64, 0, 64, 0,
    65, 0, 67, 0
};

void send_note_on(int note) {
    Byte buffer[3] = {0x90, note, 100}; // Note On, velocity 100
    MIDIPacketList packetList;
    MIDIPacket *packet = MIDIPacketListInit(&packetList);
    packet = MIDIPacketListAdd(&packetList, sizeof(packetList), packet, 0, 3, buffer);
    MIDISend(midiOutPort, dest, &packetList);
}

void send_note_off(int note) {
    Byte buffer[3] = {0x80, note, 0}; // Note Off
    MIDIPacketList packetList;
    MIDIPacket *packet = MIDIPacketListInit(&packetList);
    packet = MIDIPacketListAdd(&packetList, sizeof(packetList), packet, 0, 3, buffer);
    MIDISend(midiOutPort, dest, &packetList);
}

void run_sequencer(void) {
    double seconds_per_step = 60.0 / TEMPO_BPM / 4.0;
    for (;;) {
        for (int i = 0; i < NUM_STEPS; ++i) {
            int note = steps[i];
            if (note > 0) {
                send_note_on(note);
            }
            usleep(seconds_per_step * 500000); // half duration
            if (note > 0) {
                send_note_off(note);
            }
            usleep(seconds_per_step * 500000); // rest of the duration
        }
    }
}

void initialize_sequencer(void) {
    MIDIClientCreate(CFSTR("StepSequencer"), NULL, NULL, &midiClient);
    MIDIOutputPortCreate(midiClient, CFSTR("OutputPort"), &midiOutPort);
    dest = MIDIGetDestination(0); // use first destination
    if (dest == 0) {
        printf("No MIDI destinations found.\n");
    }
}
