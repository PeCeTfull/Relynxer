#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <wx/string.h>

#define PARAMS_AMOUNT 3 // 2 + 1 for the header
#define FILE_HEADER "[Relynxer]"
#define PARAM_1 "LanguageID=" // default value is wxLANGUAGE_ENGLISH_CANADA
#define PARAM_2 "HideHTTPWarning="
#define PARAM_2_DEFAULT_VALUE "0"


class ConfigFile
{
    public:
        ConfigFile();
        wxString *ReadFileContents();
        void NewFileContents();
        void WriteFileContents(wxString* paramTable);
        virtual ~ConfigFile();
        const wxString configFileName = wxT("config.ini");
    protected:
    private:
        void SaveFile(wxString& params);
};

#endif // CONFIGFILE_H
