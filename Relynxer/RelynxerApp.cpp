/***************************************************************
 * Name:      RelynxerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    PeCeT_full (me@pecetfull.pl)
 * Created:   2019-11-23
 * Copyright: PeCeT_full (https://www.pecetfull.pl/)
 * Licence:   The MIT License
 **************************************************************/

#include "RelynxerApp.h"
#include <wx/filename.h>
#include <wx/dir.h>

//(*AppHeaders
#include "RelynxerMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(RelynxerApp);

bool RelynxerApp::OnInit()
{
    m_TranslationHelper = new wxTranslationHelper(*this);

    wxString *parameters;
    ConfigFile *newConfigFile = new ConfigFile();
    if(!wxFileName::FileExists(newConfigFile->configFileName))
        newConfigFile->NewFileContents();
    else
    {
        parameters = newConfigFile->ReadFileContents();

        const wxChar equalitySign = '=';
        size_t equalitySignPos;
        equalitySignPos = parameters[1].Find(equalitySign);
        languageID = wxAtoi(parameters[1].SubString(equalitySignPos + 1, parameters[1].Length()));
        equalitySignPos = parameters[2].Find(equalitySign);
        hideHTTPWarning = wxAtoi(parameters[2].SubString(equalitySignPos + 1, parameters[2].Length()));
    }
    wxDELETE(newConfigFile);
    if (DoesLangsFolderExist())
    {
        m_TranslationHelper->Load(languageID);
    }

    if (hideHTTPWarning == false)
    {
        wxMessageBox(_("This program uses HTTP which is not encrypted - this means that data sent through this program can be easily tracked. The encrypted HTTPS protocol is not supported in order to preserve compatibility with legacy Windows versions (especially Windows 95). If you do not wish to have your data possibly compromised by any other party, please do not enter any detail in the wizard and exit Relynxer immediately. The author does not take any responsibility in case of any piece of information retrieved from a request created by this application.\n\nYou have been warned."), _("Warning"), wxICON_EXCLAMATION);
    }

    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	RelynxerDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}

int RelynxerApp::OnExit()
{
    if(m_TranslationHelper)
    {
        wxDELETE(m_TranslationHelper);
    }

    return 0;
}

void RelynxerApp::OnSetLanguage(short languageID)
{
    m_TranslationHelper->SetLanguage(languageID);
}

short RelynxerApp::SelectLanguage()
{
    wxArrayString names;
    wxArrayShort identifiers;
    m_TranslationHelper->GetInstalledLanguages(names, identifiers);
    return m_TranslationHelper->AskUserForLanguage(names, identifiers);
}

bool RelynxerApp::DoesLangsFolderExist()
{
    return wxDir::Exists(m_TranslationHelper->languagesPath) ? true : false;
}
