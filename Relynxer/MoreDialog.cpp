#include "RelynxerApp.h"
#include "MoreDialog.h"
#include <wx/aboutdlg.h>

#define ICON_NAME "aaaa"

//(*InternalHeaders(MoreDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxBuildInfoFormat {
    short_f, long_f };

wxString wxBuildInfo(wxBuildInfoFormat format)
{
    wxString wxBuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxBuild << _T("-Windows");
#elif defined(__UNIX__)
        wxBuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxBuild << _T("-Unicode build");
#else
        wxBuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxBuild;
}

//(*IdInit(MoreDialog)
const long MoreDialog::ID_BTNSHOWHIDEHTTPWARNING = wxNewId();
const long MoreDialog::ID_BTNLANGUAGE = wxNewId();
const long MoreDialog::ID_BTNABOUT = wxNewId();
//*)

BEGIN_EVENT_TABLE(MoreDialog,wxDialog)
	//(*EventTable(MoreDialog)
	//*)
END_EVENT_TABLE()

MoreDialog::MoreDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(MoreDialog)
	wxFlexGridSizer* FgsMain;

	Create(parent, id, _("More options"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FgsMain = new wxFlexGridSizer(3, 1, 0, 0);
	FgsMain->AddGrowableCol(1);
	FgsMain->AddGrowableRow(3);
	BtnShowHideHTTPWarning = new wxButton(this, ID_BTNSHOWHIDEHTTPWARNING, _("Show/hide HTTP &warning"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTNSHOWHIDEHTTPWARNING"));
	BtnShowHideHTTPWarning->SetMinSize(wxSize(250,-1));
	FgsMain->Add(BtnShowHideHTTPWarning, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BtnLanguage = new wxButton(this, ID_BTNLANGUAGE, _("Change &language"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTNLANGUAGE"));
	BtnLanguage->SetMinSize(wxSize(250,-1));
	FgsMain->Add(BtnLanguage, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BtnAbout = new wxButton(this, ID_BTNABOUT, _("&About..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTNABOUT"));
	BtnAbout->SetMinSize(wxSize(250,-1));
	FgsMain->Add(BtnAbout, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BtnCloseWindow = new wxButton(this, wxID_OK, _("Close window"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	BtnCloseWindow->SetMinSize(wxSize(250,-1));
	FgsMain->Add(BtnCloseWindow, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FgsMain);
	FgsMain->Fit(this);
	FgsMain->SetSizeHints(this);
	Center();

	Connect(ID_BTNSHOWHIDEHTTPWARNING,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MoreDialog::OnBtnShowHideHTTPWarningClick);
	Connect(ID_BTNLANGUAGE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MoreDialog::OnBtnLanguageClick);
	Connect(ID_BTNABOUT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MoreDialog::OnBtnAboutClick);
	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MoreDialog::OnBtnCloseWindowClick);
	//*)

	chosenLanguageID = wxGetApp().languageID;
	hiddenHTTPWarning = wxGetApp().hideHTTPWarning;
	HandleBtnShowHideHTTPWarningLabel();
}

MoreDialog::~MoreDialog()
{
	//(*Destroy(MoreDialog)
	//*)
}

void MoreDialog::HandleBtnShowHideHTTPWarningLabel()
{
    if (hiddenHTTPWarning)
    {
        BtnShowHideHTTPWarning->SetLabel(_("Show HTTP &warning"));
    }
    else
    {
        BtnShowHideHTTPWarning->SetLabel(_("Hide HTTP &warning"));
    }
}

void MoreDialog::ApplySettings()
{
    wxGetApp().languageID = chosenLanguageID;
    wxGetApp().hideHTTPWarning = hiddenHTTPWarning;

    wxString *parameters = new wxString[PARAMS_AMOUNT];
    parameters[0] = wxT(FILE_HEADER);
    parameters[1] = wxT(PARAM_1) + wxString::Format(wxT("%d"), chosenLanguageID);
    parameters[2] = wxT(PARAM_2) + wxString::Format(wxT("%d"), hiddenHTTPWarning);
    ConfigFile *newConfigFile = new ConfigFile();
    newConfigFile->WriteFileContents(parameters);
    wxDELETE(newConfigFile);
}

void MoreDialog::OnBtnShowHideHTTPWarningClick(wxCommandEvent& event)
{
    hiddenHTTPWarning = !hiddenHTTPWarning;
    HandleBtnShowHideHTTPWarningLabel();
    ApplySettings();
}

void MoreDialog::OnBtnLanguageClick(wxCommandEvent& event)
{
    short selectedLanguageID = wxGetApp().SelectLanguage();
    if(selectedLanguageID != wxLANGUAGE_UNKNOWN)
    {
        if (chosenLanguageID != selectedLanguageID)
        {
            wxMessageBox(_("Another language has just been selected. To reflect all the changes, please restart the application."), _("Message"));
            chosenLanguageID = selectedLanguageID;
            ApplySettings();
        }
    }
}

void MoreDialog::OnBtnAboutClick(wxCommandEvent& event)
{
    wxString currentLanguageName = wxLocale::GetLanguageName(wxGetApp().languageID);
    if(currentLanguageName.Contains(wxT(DEFAULT_LANGUAGE_FORMAL_NAME)))
        currentLanguageName = wxT(DEFAULT_LANGUAGE_FORMAL_NAME);
    currentLanguageName = wxGetTranslation(currentLanguageName);

    wxAboutDialogInfo info;
    info.SetIcon(wxIcon(wxT(ICON_NAME)));
    info.SetName(_("Relynxer"));
    info.SetVersion(wxT("1.0.1"));
    info.SetCopyright(wxT("Copyright (C) PeCeT_full 2021-2022 <me@pecetfull.pl>"));
    info.SetDescription(_("A wizard program for the link shortening service Lynx.re. Powered by Shrinky.\n\nBuild info: ") + wxBuildInfo(long_f) + _(".\nBuild date: ") +  __TDATE__ + wxT(", ") __TTIME__ + _(".\n\nCurrent language: ") + currentLanguageName + '.');
    info.SetWebSite(_("http://www.pecetfull.pl"));
    info.SetLicence(_("This program is published under The MIT License. For more information, please refer to the Licence.txt file included with the application."));

    wxAboutBox(info);
}

void MoreDialog::OnBtnCloseWindowClick(wxCommandEvent& event)
{
    Close();
}
