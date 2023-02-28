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