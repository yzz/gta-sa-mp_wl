#define RECORDING "beagle" //This is the filename of your recording without the extension.
#define RECORDING_TYPE 1 //1 for in vehicle and 2 for on foot.

//Mega Transport Pack By Memoryz of SA-MP Forums

#include <a_npc>
main(){}
public OnRecordingPlaybackEnd() StartRecordingPlayback(RECORDING_TYPE, RECORDING);
public OnNPCEnterVehicle(vehicleid, seatid) StartRecordingPlayback(RECORDING_TYPE, RECORDING);
public OnNPCExitVehicle() StopRecordingPlayback();
