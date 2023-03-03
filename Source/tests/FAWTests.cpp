#include "../PluginTests.h"
#include "../TestUtilities.h"
#include <future>
#include <thread>

//==============================================================================
struct FAWPresetChangeTest   : public PluginTest
{
    FAWPresetChangeTest()
        : PluginTest ("FAW preset change", 1)
    {
    }

    void runTest (PluginTests& ut, juce::AudioPluginInstance& instance) override
    {
        ut.logMessage("\n### FAW Preset Change tests: " + instance.getName());

        // first sets a normal sample rate and buffer size
        callPrepareToPlayOnMessageThreadIfVST3 (instance, 44100.0, 512);

        // special signaling sampleRate with -1 will be caught to init tests
        // passing blockSize 1 will trigger random preset change
        for (int i = 0; i < 5; ++i)
            callPrepareToPlayOnMessageThreadIfVST3 (instance, 1.0, 1);

        // wait few seconds for the test to complete
        std::this_thread::sleep_for (std::chrono::seconds (2));

        ut.logMessage("### FAW Preset Change tests completed: " + instance.getName());
    }

};

static FAWPresetChangeTest fawPresetChangeTest;

//==============================================================================
struct FAWLoadSampleTest   : public PluginTest
{
    FAWLoadSampleTest()
        : PluginTest ("FAW load sample", 1)
    {
    }

    void runTest (PluginTests& ut, juce::AudioPluginInstance& instance) override
    {
        ut.logMessage("\n### FAW Load Sample tests: " + instance.getName());

        // first sets a normal sample rate and buffer size
        callPrepareToPlayOnMessageThreadIfVST3 (instance, 44100.0, 512);

        // special signaling sampleRate with -1 will be caught to init tests
        // passing blockSize 2 will trigger load sample

        for (int i = 0; i < 5; ++i)
            callPrepareToPlayOnMessageThreadIfVST3 (instance, 1.0, 2);

        // wait few seconds for the test to complete
        std::this_thread::sleep_for (std::chrono::seconds (2));

        ut.logMessage("### FAW Load Sample tests completed: " + instance.getName());
    }

};

static FAWLoadSampleTest fawLoadSampleTest;

struct FAWNuclearTest   : public PluginTest {
    FAWNuclearTest()
            : PluginTest("FAW NUCLEAR TEST", 1, { Requirements::Thread::messageThread, Requirements::GUI::noGUI }) {
    }

    void runTest (PluginTests& ut, juce::AudioPluginInstance& instance) override
    {
        ut.logMessage("\n### FAW NUCLEAR TEST: " + instance.getName());

        callReleaseResourcesOnMessageThreadIfVST3 (instance);

        callPrepareToPlayOnMessageThreadIfVST3 (instance, 44100.0, 512);

        auto r = ut.getRandom();

        const int numChannelsRequired = juce::jmax (instance.getTotalNumInputChannels(), instance.getTotalNumOutputChannels());
        juce::AudioBuffer<float> ab (numChannelsRequired, 512);
        juce::MidiBuffer mb;

        // Add a random note on if the plugin is a synth
        const int noteChannel = r.nextInt ({ 1, 17 });
        const int noteNumber = r.nextInt (128);


        addNoteOn (mb, noteChannel, noteNumber, juce::jmin (10, 512));

        for (int i = 0; i < 20; ++i)
        {
            // Add note off in last block if plugin is a synth
            if (i == (20 - 1))
                addNoteOff (mb, noteChannel, noteNumber, 0);

            fillNoise (ab);
            instance.processBlock (ab, mb);
            mb.clear();

            ut.expectEquals (countNaNs (ab), 0, "NaNs found in buffer");
            ut.expectEquals (countInfs (ab), 0, "Infs found in buffer");
            ut.expectEquals (countSubnormals (ab), 0, "Subnormals found in buffer");

            // if i is 3 or 12, change preset
            if (i == 3 || i == 12)
                callPrepareToPlayOnMessageThreadIfVST3 (instance, 1.0, 1);

            // if i is 7, load sample
            if (i == 7)
                callPrepareToPlayOnMessageThreadIfVST3 (instance, 1.0, 2);

            // sleep for few milliseconds
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }


        ut.logMessage("### FAW NUCLEAR TEST completed: " + instance.getName());
    }
};

static FAWNuclearTest fawNuclearTest;