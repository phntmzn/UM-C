#include <CoreMIDI/CoreMIDI.h>
#include <CoreServices/CoreServices.h>
#include <mach/mach_time.h>
#include <unistd.h>
#include <stdio.h>

MIDIClientRef client;
MIDIPortRef outPort;
MIDIEndpointRef dest;

void send_midi_note(UInt8 note, UInt8 velocity, UInt8 channel, UInt64 delay_ms) {
    Byte buffer[3];
    buffer[0] = 0x90 | (channel & 0x0F); // Note On
    buffer[1] = note;
    buffer[2] = velocity;

    MIDIPacketList packetList;
    MIDIPacket* packet = MIDIPacketListInit(&packetList);

    // Get timestamp in host time units
    UInt64 time = mach_absolute_time();
    // Convert ms to host time units
    static mach_timebase_info_data_t info = {0};
    if (info.denom == 0) mach_timebase_info(&info);
    UInt64 nanos = delay_ms * 1000000;
    UInt64 host_time = time + (nanos * info.denom / info.numer);

    packet = MIDIPacketListAdd(&packetList, sizeof(packetList), packet, host_time, 3, buffer);
    if (packet == NULL) {
        fprintf(stderr, "Failed to add packet\n");
        return;
    }

    MIDISend(outPort, dest, &packetList);
}

int main(void) {
    MIDIClientCreate(CFSTR("MIDI Scheduler"), NULL, NULL, &client);
    MIDIOutputPortCreate(client, CFSTR("Output Port"), &outPort);
    
    ItemCount count = MIDIGetNumberOfDestinations();
    if (count == 0) {
        fprintf(stderr, "No MIDI destinations found\n");
        return 1;
    }

    dest = MIDIGetDestination(0);
    
    // Example: Schedule a C major triad
    send_midi_note(60, 100, 0, 0);    // C4 now
    send_midi_note(64, 100, 0, 500);  // E4 in 500ms
    send_midi_note(67, 100, 0, 1000); // G4 in 1000ms

    sleep(2); // Let the notes play before quitting
    return 0;
}
