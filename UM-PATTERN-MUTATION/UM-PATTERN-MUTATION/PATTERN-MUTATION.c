//  PATTERN-MUTATION.c
//  UM-PATTERN-MUTATION
//
//  Created by bRx86 on 4/15/25.
//

#include "PATTERN-MUTATION.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <CoreMIDI/CoreMIDI.h>
#include <mach/mach_time.h>

extern MIDIClientRef client;
extern MIDIPortRef outPort;
extern MIDIEndpointRef dest;

void generateRandomPattern(MIDIPattern *pattern, int length) {
    if (length > MAX_PATTERN_LENGTH) length = MAX_PATTERN_LENGTH;
    srand((unsigned int)time(NULL));

    pattern->length = length;
    for (int i = 0; i < length; ++i) {
        pattern->notes[i].note = 60 + (rand() % 24);       // C4 to B5
        pattern->notes[i].velocity = 80 + (rand() % 48);   // Velocity between 80–127
        pattern->notes[i].delay_ms = i * 250;              // 250ms step interval
    }
}

void mutatePattern(MIDIPattern *pattern, float mutation_rate) {
    for (int i = 0; i < pattern->length; ++i) {
        float r = (float)rand() / RAND_MAX;
        if (r < mutation_rate) {
            pattern->notes[i].note = 60 + (rand() % 24);       // Random new note
            pattern->notes[i].velocity = 60 + (rand() % 68);   // Random new velocity
        }
    }
}

void printPattern(const MIDIPattern *pattern) {
    static mach_timebase_info_data_t info = {0};
    if (info.denom == 0) mach_timebase_info(&info);

    UInt64 baseTime = mach_absolute_time();

    for (int i = 0; i < pattern->length; ++i) {
        const MIDINote *n = &pattern->notes[i];
        printf("Note %d: pitch=%d velocity=%d delay=%llu ms\n",
               i, n->note, n->velocity, n->delay_ms);

        Byte msg[3] = { 0x90, n->note, n->velocity };
        MIDIPacketList packetList;
        MIDIPacket *packet = MIDIPacketListInit(&packetList);

        UInt64 nanos = n->delay_ms * 1000000;
        UInt64 hostTime = baseTime + (nanos * info.denom / info.numer);

        packet = MIDIPacketListAdd(&packetList, sizeof(packetList), packet, hostTime, 3, msg);
        if (packet) {
            MIDISend(outPort, dest, &packetList);
        }
    }
}
