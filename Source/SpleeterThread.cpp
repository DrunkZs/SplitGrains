/*
  ==============================================================================

	SpleeterThread.cpp
	Created: 14 Feb 2022 4:32:17pm
	Author:  Christopher Davies-Dickson 

  ==============================================================================
*/

#include "SpleeterThread.h"

SpleeterThread::SpleeterThread(SplitGrainsAudioProcessor& p, const std::string& f, spleeter::SeparationType t, juce::String& o, juce::String& m) 
	: Spleeted(p), Thread("Stem seperation Thread")
{
	file = f;
	type = t;
	output_dir = o;
	model_dir = m;
	startThread();
}

SpleeterThread::~SpleeterThread()
{
	stopThread(2000);
}

void SpleeterThread::run()
{
	while (!threadShouldExit()) {
		wait(5);
		const juce::MessageManagerLock mml(Thread::getCurrentThread());
		if (!mml.lockWasGained()) {
			return;
		}
		spleeted(file, type, output_dir, model_dir);
		signalThreadShouldExit();
	}
}
