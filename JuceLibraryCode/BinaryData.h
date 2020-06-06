/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   logoAltColor_png;
    const int            logoAltColor_pngSize = 12149;

    extern const char*   beat_wav;
    const int            beat_wavSize = 844;

    extern const char*   click_wav;
    const int            click_wavSize = 844;

    extern const char*   Muli_ttf;
    const int            Muli_ttfSize = 89244;

    extern const char*   TiMicon_png;
    const int            TiMicon_pngSize = 239362;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 5;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
