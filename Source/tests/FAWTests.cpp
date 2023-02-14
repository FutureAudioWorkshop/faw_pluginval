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
        ut.logMessage("\nFAW Preset Change tests: " + instance.getName());
    }

};

static FAWPresetChangeTest fawPresetChangeTest;