# pluginval

pluginval is a cross-platform plugin validator and tester application. It is designed to be used by both plugin and host developers to ensure stability and compatibility between plugins and hosts.

###### Highlights:
  - Test VST/AU/VST3 plugins
  - Compatible with macOS/Windows/Linux
  - Run in GUI or headless mode
  - Validation is performed in a separate process to avoid crashing


### Installation

Either grab one of the pre-compiled binaries from the Releases page or clone the repo and build from sources.
The projects are generated by the Projucer so you may have to build that first to generate the various project files. The easiest way to do this is to run one of the build scripts in the `install` directory.
```sh
$ git clone --recurse-submodule git@github.com:Tracktion/pluginval.git
$ cd pluginval/install
$ ./mac_build
```

### Running in GUI Mode
Once the app has built for your platform it will be found in `/bin`. Simply open the app to start it in GUI mode. Once open, you'll be presented with an empty plugin list. Click "Options" to scan for plugins, making sure to add any directories required.
Alterntively, you can drag a plugin file and drop it on the list to add only that plugin.

Once the list has populated, simply select a plugin and press the "Test Selected" button to validate it. The plugin will be loaded and each of the tests run in turn. Any output from the tests will be shown on the "Console" tab.
If you find problems with a plugin, this can be useful to send to the plugin developers.

### Running in Headless Mode
As well as being a GUI app, `pluginval` can be run from the command line in a headless mode.
This is great if you want to add validation as part of your CI process and be notified immidiately if tests start failing.

###### Basic usage is as follows:
```
./pluginval --strictnessLevel 5 --validate <path_to_plugin>
```
This will run all the tests up to level 5 on the plugin at the specified path.
Output will be fed to the console.
If all the tests pass cleanly, `pluginval` will return with an exit code of `0`. If any tests fail, the exit code will be `1`.
This means you can check the exit code on your various CI and mark builds a failing if all tests don't pass.

`strictnessLevel` is optional but can be between 1 & 10 with 5 being generally recognised as the lowest level for host compatibility. Lower levels are generally quick tests, mainly checking call coverage for crashes. Higher levels contain tests which take longer to run such as parameter fuzz tests and multiple state restoration.

###### You can also list all the options with:
```
./pluginval -h
```

### Contributing
If you would like to contribute to the project please do! It's very simple to add tests, simply:
1) Subclass `PluginTest`
    ```
    struct FuzzParametersTest  : public PluginTest
    ```
2) Override `runTest` to perform any tests
    ```
    void runTest (UnitTest& ut, AudioPluginInstance& instance) override
    ```
3) Log passes or failures with the `UnitTest` parameter
    ```
    ut.expect (editor != nullptr, "Unable to create editor");
    ```
4) Register your test with a static instance of it in a cpp file:
   ```
   static FuzzParametersTest fuzzParametersTest;
   ```

If you have a case you would like tests, please simply write the test in a fork and create a pull request. The more tests the better!

### Todos
 - Create a better logo!
 - Write more Tests
 - Possibly add more command line options
 -- Run only specific tests, either named or from a certain strictness level
 
License
----

Licencing is under the `GPLv3` as we want `pluginval` to be as transparent as possible. If this conflicts with your requirements though please let us know and we can accomodate these.