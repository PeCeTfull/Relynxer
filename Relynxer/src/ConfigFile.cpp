#include "ConfigFile.h"
#include <wx/wfstream.h>
#include <wx/sstream.h>
#include <wx/intl.h>

ConfigFile::ConfigFile()
{
    //ctor
}

wxString *ConfigFile::ReadFileContents()
{
    wxString *contents = new wxString[PARAMS_AMOUNT];
    wxString content;
    wxFileInputStream file(configFileName);
    wxStringOutputStream sOutput(&content);
    sOutput.Write(file);
    sOutput.Close();

    size_t newLinePos;
    for(int i = 0; i < PARAMS_AMOUNT; i++)
    {
        newLinePos = content.Find(wxT("\r\n"));
        contents[i] = content.SubString(0, newLinePos - 1);
        content = content.SubString(newLinePos + 2, content.Length());
    }

    return contents;
}

void ConfigFile::SaveFile(wxString& params)
{
    wxStringInputStream sInput(params);
    wxFileOutputStream file(configFileName);
    file.Write(sInput);
    file.Close();
}

void ConfigFile::NewFileContents()
{
    wxString params = wxString::Format(wxT("%s\r\n%s%d\r\n%s%s"), wxT(FILE_HEADER), wxT(PARAM_1), wxLANGUAGE_ENGLISH_CANADA, wxT(PARAM_2), wxT(PARAM_2_DEFAULT_VALUE));

    SaveFile(params);
}

void ConfigFile::WriteFileContents(wxString* paramTable)
{
    wxString params = paramTable[0] + wxT("\r\n") + paramTable[1] + wxT("\r\n") + paramTable[2];

    SaveFile(params);
}

ConfigFile::~ConfigFile()
{
    //dtor
}
