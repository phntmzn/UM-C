//
//  MARKOV-CHAIN-GENERATOR.c
//  UM-MARKOV-CHAIN
//
//  Created by bRx86 on 4/15/25.
//

#include "MARKOV-CHAIN-GENERATOR.h"
#include <CoreMIDI/CoreMIDI.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define NUM_NOTES 5
#define NOTE_DURATION_MS 300

static MIDIClientRef markovClient;
static MIDIPortRef markovOutPort;
static MIDIEndpointRef markovDest;

static int notes[NUM_NOTES] = {60, 62, 64, 65, 67};
static float transition[NUM_NOTES][NUM_NOTES] = {
    {0.1, 0.3, 0.3, 0.2, 0.1},
    {0.2, 0.1, 0.4, 0.2, 0.1},
    {0.3, 0.2, 0.1, 0.3, 0.1},
    {0.1, 0.2, 0.3, 0.2, 0.2},
    {0.2, 0.1, 0.2, 0.3, 0.2}
};

void send_markov_note_on(int note) {
    Byte buffer[3] = {0x90, note, 100};
    MIDIPacketList packetList;
    MIDIPacket *packet = MIDIPacketListInit(&packetList);
    packet = MIDIPacketListAdd(&packetList, sizeof(packetList), packet, 0, 3, buffer);
    MIDISend(markovOutPort, markovDest, &packetList);
}

void send_markov_note_off(int note) {
    Byte buffer[3] = {0x80, note, 0};
    MIDIPacketList packetList;
    MIDIPacket *packet = MIDIPacketListInit(&packetList);
    packet = MIDIPacketListAdd(&packetList, sizeof(packetList), packet, 0, 3, buffer);
    MIDISend(markovOutPort, markovDest, &packetList);
}

int choose_next_note(int current) {
    float r = (float)rand() / RAND_MAX;
    float sum = 0.0;
    for (int i = 0; i < NUM_NOTES; i++) {
        sum += transition[current][i];
        if (r <= sum) return i;
    }
    return current;
}

void initialize_markov_generator() {
    MIDIClientCreate(CFSTR("MarkovChain"), NULL, NULL, &markovClient);
    MIDIOutputPortCreate(markovClient, CFSTR("OutputPort"), &markovOutPort);
    markovDest = MIDIGetDestination(0);
    if (markovDest == 0) {
        printf("No MIDI destination found.\n");
    }
    srand((unsigned int)time(NULL));
}

void run_markov_melody() {
    int current = 0;
    while (1) {
        int note = notes[current];
        send_markov_note_on(note);
        usleep(NOTE_DURATION_MS * 1000 / 2);
        send_markov_note_off(note);
        usleep(NOTE_DURATION_MS * 1000 / 2);
        current = choose_next_note(current);
    }
}
