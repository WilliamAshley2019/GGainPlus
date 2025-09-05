#pragma once
#include <JuceHeader.h>

class GGGainAudioProcessor : public juce::AudioProcessor
{
public:
    GGGainAudioProcessor();
    ~GGGainAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts{ *this, nullptr, "Parameters", createParameterLayout() };

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    // Store sample rate for accurate phase calculations
    double currentSampleRate = 44100.0;

    // Smoothed gain control
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> gainLin{ 1.0f };

    // Age-based psychoacoustic curve parameters
    struct LoudnessCurve
    {
        float lfBoost = 1.0f;  // Low frequency boost for presbycusis compensation
        float hfCut = 1.0f;  // High frequency cut for age-related hearing loss
    } curve;

    // Inverse (Un-Age) curve
    struct UnAgeCurve
    {
        float lfCut = 1.0f;   // 1 / lfBoost
        float hfBoost = 1.0f; // 1 / hfCut
    } unAgeCurve;

    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> unAgeAmount{ 0.0f };

    // Tactile "feel" enhancement parameters
    struct Feel
    {
        float subLevel = 0.0f;  // Sub-harmonic generation level
        float phase = 0.0f;  // Phase accumulator for 40Hz sub-harmonic
    } feel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GGGainAudioProcessor)
};