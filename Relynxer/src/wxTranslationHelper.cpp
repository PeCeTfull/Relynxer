#include "../include/wxTranslationHelper.h"
#include <wx/dir.h>
#include <wx/config.h>
#include <wx/filename.h>

wxTranslationHelper::wxTranslationHelper(wxApp& app) : m_App(app), m_Locale(NULL)
{
    //ctor
}

wxTranslationHelper::~wxTranslationHelper()
{
    if(m_Locale)
        wxDELETE(m_Locale);
}

void wxTranslationHelper::SetLanguage(short identifier)
{
    if(m_Locale)
        wxDELETE(m_Locale);
    m_Locale = new wxLocale;
    m_Locale->Init(identifier);
    m_Locale->AddCatalogLookupPathPrefix(languagesPath);
    m_Locale->AddCatalog(m_App.GetAppName());
}

bool wxTranslationHelper::Load(short identifier)
{
    if(identifier == wxLANGUAGE_UNKNOWN)
        return false;
    wxArrayString names;
    wxArrayShort identifiers;
    GetInstalledLanguages(names, identifiers);
    for(size_t i = 0; i < identifiers.Count(); i++)
    {
        if(identifiers[i] == identifier)
        {
            SetLanguage(identifiers[i]);
            return true;
        }
    }
    return false;
}

void wxTranslationHelper::GetInstalledLanguages(wxArrayString& names, wxArrayShort& identifiers)
{
    names.Clear();
    identifiers.Clear();
    wxDir dir(languagesPath);
    wxString fileName;
    const wxLanguageInfo *langInfo;
    names.Add(wxGetTranslation(wxLocale::GetLanguageName(wxLANGUAGE_ENGLISH_CANADA))); // default language name
    identifiers.Add(wxLANGUAGE_ENGLISH_CANADA); // default language identifier
    for(bool cont = dir.GetFirst(&fileName, wxT("*.*"), wxDIR_DIRS); cont; cont = dir.GetNext(&fileName))
    {
        langInfo = wxLocale::FindLanguageInfo(fileName);
        if(langInfo != NULL)
        {
            if(langInfo->Language != wxLANGUAGE_ENGLISH_CANADA && wxFileExists(dir.GetName() + wxFileName::GetPathSeparator() + fileName + wxFileName::GetPathSeparator() + m_App.GetAppName() + wxT(".mo")))
            {
                names.Add(wxGetTranslation(langInfo->Description));
                identifiers.Add(langInfo->Language);
            }
        }
    }
}

short wxTranslationHelper::AskUserForLanguage(wxArrayString& names, wxArrayShort& identifiers)
{
    wxCHECK_MSG(names.Count() == identifiers.Count(), wxLANGUAGE_UNKNOWN, _("Array of language names and identifiers should have the same size."));
    int index = wxGetSingleChoiceIndex(_("Select your language."), _("Language"), names);
    if(index != -1)
    {
        SetLanguage(identifiers[index]);
        return identifiers[index];
    }
    return wxLANGUAGE_UNKNOWN;
}
