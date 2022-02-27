/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ColourScheme.h"
#include "MainComponent.h"

class OtoDecksApplication  : public juce::JUCEApplication
{
    public:
        OtoDecksApplication() {}

    
        /** Get the name of the juce application */
        const juce::String getApplicationName() override    { return ProjectInfo::projectName; }
    
        /** Get the version of the juce application */
        const juce::String getApplicationVersion() override     { return ProjectInfo::versionString; }
    
        /** Confirm if more than one instance of the application can be running at the same time
         * @return boolean representing if more than one instance of the application can run
        */
        bool moreThanOneInstanceAllowed() override      { return true; }

        /** Initialise the juce application
         *  @param commandLine the command line parameter list passed in when initialising the application
        */
        void initialise (const juce::String& commandLine) override  { mainWindow.reset (new MainWindow (getApplicationName())); }

        /** Shut down the juce application by deleting window */
        void shutdown() override    { mainWindow = nullptr; }

        /** Callback for when the app is being asked to quit. Call quit() to allow the app to close. */
        void systemRequestedQuit() override     { quit(); }

        /** Callback for when an additional instance of the application is requested
         * @param commandLine the command line parameter list of the currently running instance of the application
        */
        void anotherInstanceStarted (const juce::String& commandLine) override
        {
        }

    
        /** -------------------------------------------------------------------------------
         *  Implement the desktop window that contains an instance of MainComponent class.
         *  -------------------------------------------------------------------------------
        */
        class MainWindow    : public juce::DocumentWindow
        {
            public:
                MainWindow (juce::String name) : DocumentWindow (name,
                                                                 juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                                  .findColour (juce::ResizableWindow::backgroundColourId),
                                                                 DocumentWindow::allButtons)
                {
                    setUsingNativeTitleBar (true);
                    setContentOwned (new MainComponent(), true);

                   #if JUCE_IOS || JUCE_ANDROID
                    setFullScreen (true);
                   #else
                    setResizable (true, true);
                    centreWithSize (getWidth(), getHeight());
                   #endif

                    setVisible (true);
                }

                /** Callback for when user tries to close this window.
                 *  Requests app to quit.
                */
                void closeButtonPressed() override
                {
                    JUCEApplication::getInstance()->systemRequestedQuit();
                }

            
            private:
                JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
        };
        /** ------------------------------------------------------------------------------- */


    
    private:
        std::unique_ptr<MainWindow> mainWindow;
};

// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (OtoDecksApplication)
