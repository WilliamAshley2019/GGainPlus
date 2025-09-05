#include "PluginEditor.h"

GGGainAudioProcessorEditor::GGGainAudioProcessorEditor(GGGainAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(400, 220); // Increased width to accommodate the new slider

    auto makeRotary = [this](juce::Slider& s, juce::String suffix)
        {
            addAndMakeVisible(s);
            s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
            s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
            s.setTextValueSuffix(suffix);
        };

    makeRotary(gainSlider, " dB");
    makeRotary(ageSlider, " yrs");
    makeRotary(feelSlider, "");
    makeRotary(unAgeSlider, " %");

    gainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "gain", gainSlider);
    ageAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "age", ageSlider);
    feelAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "feel", feelSlider);
    unAgeAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "unAge", unAgeSlider);
}

GGGainAudioProcessorEditor::~GGGainAudioProcessorEditor() = default;

void GGGainAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::white);
    g.setFont(18.0f);
    g.drawFittedText("GGGain", getLocalBounds().removeFromTop(30), juce::Justification::centred, 1);
}

void GGGainAudioProcessorEditor::resized()
{
    auto b = getLocalBounds().reduced(10);
    b.removeFromTop(30);
    const int sliderWidth = 100;
    gainSlider.setBounds(b.removeFromLeft(sliderWidth));
    ageSlider.setBounds(b.removeFromLeft(sliderWidth));
    feelSlider.setBounds(b.removeFromLeft(sliderWidth));
    unAgeSlider.setBounds(b.removeFromLeft(sliderWidth));
}