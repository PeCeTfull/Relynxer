#ifndef _WX_TRANSLATION_HELPER_H
#define _WX_TRANSLATION_HELPER_H

#include <wx/wx.h>
#include <wx/intl.h>

#define DEFAULT_LANGUAGE_FORMAL_NAME "English"


class wxTranslationHelper
{
    wxApp &m_App;
    wxLocale *m_Locale;
public:
    wxTranslationHelper(wxApp& app);
    ~wxTranslationHelper();

    void SetLanguage(short identifier);
    bool Load(short identifier);
    void GetInstalledLanguages(wxArrayString& names, wxArrayShort& identifiers);
    short AskUserForLanguage(wxArrayString& names, wxArrayShort& identifiers);
    const wxString languagesPath = wxPathOnly(m_App.argv[0]) + wxT("\\langs");
};

#endif // WXTRANSLATIONHELPER_H
