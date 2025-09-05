#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class GGGainAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    GGGainAudioProcessorEditor(GGGainAudioProcessor&);
    ~GGGainAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    GGGainAudioProcessor& audioProcessor;

    juce::Slider gainSlider{ "Gain" }, ageSlider{ "Age" }, feelSlider{ "Feel" }, unAgeSlider{ "Un-Age" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        gainAttach, ageAttach, feelAttach, unAgeAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GGGainAudioProcessorEditor)
};