/***************************************************************
 * Name:      RelynxerApp.h
 * Purpose:   Defines Application Class
 * Author:    PeCeT_full (me@pecetfull.pl)
 * Created:   2019-11-23
 * Copyright: PeCeT_full (https://www.pecetfull.pl/)
 * Licence:   The MIT License
 **************************************************************/

#ifndef RELYNXERAPP_H
#define RELYNXERAPP_H

#include "include/wxTranslationHelper.h"
#include "ConfigFile.h"
#include <wx/app.h>

class RelynxerApp : public wxApp
{
    wxTranslationHelper *m_TranslationHelper;
    public:
        virtual bool OnInit();
        virtual int OnExit();
        void OnSetLanguage(short languageID);
        short SelectLanguage();
        bool DoesLangsFolderExist();
        short languageID = wxLANGUAGE_ENGLISH_CANADA; // parameter 1
        bool hideHTTPWarning = false; // parameter 2
};

DECLARE_APP(RelynxerApp);

#endif // RELYNXERAPP_H
