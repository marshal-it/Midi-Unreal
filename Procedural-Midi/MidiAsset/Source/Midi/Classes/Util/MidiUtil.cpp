// Copyright -> Scott Bishel

#include "MidiPrivatePCH.h"
#include "MidiUtil.h"

#include <sstream>

using namespace std;

/**
* MIDI Unit Conversions
*/
long MidiUtil::ticksToMs(long ticks, int mpqn, int resolution) {
	return ((ticks * (uint64)mpqn) / resolution) / 1000;
}
long MidiUtil::ticksToMs(long ticks, float bpm, int resolution) {
	return ticksToMs(ticks, bpmToMpqn(bpm), resolution);
}

double MidiUtil::msToTicks(long ms, int mpqn, int ppq) {
	return ((ms * 1000.0) * ppq) / mpqn;
}
double MidiUtil::msToTicks(long ms, float bpm, int ppq) {
	return msToTicks(ms, bpmToMpqn(bpm), ppq);
}

int MidiUtil::bpmToMpqn(float bpm) {
	return (int)(60000000 / bpm);
}
float MidiUtil::mpqnToBpm(int mpqn) {
	return 60000000.0f / mpqn;
}

/**
* Utility methods for working with bytes and byte buffers
*/
int MidiUtil::bytesToInt(char buff[], int off, int len) {

	int num = 0;

	int shift = 0;
	for (int i = off + len - 1; i >= off; i--) {

		num += (buff[i] & 0xFF) << shift;
		shift += 8;
	}

	return num;
}

char * MidiUtil::intToBytes(int val, int byteCount) {
	static char buffer[32];

	for (int i = 0; i < 32; i++)
		buffer[i] = 0;

	for (int i = 0; i < byteCount; i++) {
		buffer[byteCount - i - 1] = (char)(val & 0xFF);

		val = val >> 8;

		if (val == 0) {
			break;
		}
	}
	return buffer;
}

bool MidiUtil::bytesEqual(char buf1[], char buf2[], int off, int len) {

	for (int i = off; i < off + len; i++) {
		if (i >= sizeof(&buf1) || i >= sizeof(&buf2)) {
			return false;
		}
		if (buf1[i] != buf2[i]) {
			return false;
		}
	}
	return true;
}

char * MidiUtil::extractBytes(char buffer[], int off, int len) {
	
	char * ret = new char[len];

	for (int i = 0; i < len; i++) {
		ret[i] = buffer[off + i];
	}

	return ret;
}

const char MidiUtil::HEX[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'd', 'E', 'F' };

string MidiUtil::byteToHex(char b) {

	int high = (b & 0xF0) >> 4;
	int low = (b & 0x0F);
//	FString::Printf(TEXT("%d%d"), HEX[high], HEX[low]).t;
	stringstream ss;
	ss << HEX[high] << HEX[low];
	return ss.str();
}
string MidiUtil::bytesToHex(char b[]) {
	stringstream ss;
	for (int i = 0; i < sizeof(&b); i++) {
//		FString::Printf(TEXT("%s "), byteToHex(b[i]));

		ss << byteToHex(b[i]) << " ";
	}
	return ss.str();
}
