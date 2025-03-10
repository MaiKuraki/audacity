/**********************************************************************

 Audacity: A Digital Audio Editor

 @file imageCompilerMain.cpp

 Paul Licameli

 @brief This program runs at build time only, and generates other source files.

 @par
 The generated source file headers provide the initial data for static arrays
 of bytes.  They compile sets of images for each of the built-in themes directly
 into a library linked by Audacity.

 Platform-specific provision of image resources as separate files is avoided.
 Those files exist in the source tree in .png format, and can be easily
 maintained by version control, but are not deployed with the program.

 @par
 See lib-theme/AllThemeResources.h for the header file that guides the
 interpretation of a generated byte array as many separate images, and lists
 the names of the .png files expected to be present during this build step.
 For each name, an image file exists in each of several sub-directories.  There
 is one such directory for each of the different built-in themes.

 The list of expected names is also replicated in CMakeLists.txt to make the
 headers regenerate when the image files are updated.

 There is also a Colors.txt file for each theme, associating #rrggbb values with
 names, and AllThemeResources.h also describes the set of expected names.

 @par
 Usage: program-name absolute-path-to-folder theme-name [theme-name...]
 For each theme, under absolute-path-to-folder/theme-name/Components, expect to find
 the image and color files.
 Write a header file for each theme-name in absolute-path-to-folder.
**********************************************************************/

#include <wx/app.h>
#include <wx/image.h>
#include <list>
#include <iostream>
#include "MemoryX.h"
#include "Theme.h"

class App final : public wxAppConsole
{
    bool OnInit() override;
};

IMPLEMENT_APP_NO_MAIN(App)

int main(int argc, char* argv[])
{
    if (argc < 3) {
        using namespace std;
        cerr
            << "Usage: " << argv[0]
            << " absolute-path-to-folder theme-name [theme-name...]"
            << endl;
        return 1;
    }
    theTheme.SetFilePath(argv[1]);
    const std::vector<unsigned char> empty;
    std::list<ThemeBase::RegisteredTheme> registrations;
    for (int ii = 2; ii < argc; ++ii) {
        registrations.emplace_back(EnumValueSymbol { argv[ii], {} },
                                   PreferredSystemAppearance::Light, empty);
    }

    wxDISABLE_DEBUG_SUPPORT();

    return wxEntry(argc, argv);
}

bool App::OnInit()
{
    // Leave no persistent side-effect on preferences
    SettingScope scope;

    // So that the program can interpret PNG
    wxInitAllImageHandlers();

    theTheme.LoadThemeComponents();
    theTheme.SaveThemeAsCode();

    // Quit without any user interaction
    CallAfter([]{ wxExit(); });
    return true;
}
