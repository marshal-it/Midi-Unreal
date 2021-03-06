// Copyright -> Scott Bishel

#include "MidiPrivatePCH.h"
#include "TrackName.h"

TrackName::TrackName(long tick, long delta, string name)
	: TextualMetaEvent(tick, delta, MetaEvent::TRACK_NAME, name)
{
}

void TrackName::setName(string name) {
	TextualMetaEvent::setText(name);
}
string TrackName::getTrackName() {
	return TextualMetaEvent::getText();
}