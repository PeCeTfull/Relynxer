/***************************************************************
 * Name:      RelynxerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    PeCeT_full (me@pecetfull.pl)
 * Created:   2019-11-23
 * Copyright: PeCeT_full (https://www.pecetfull.pl/)
 * Licence:   The MIT License
 **************************************************************/

#include "RelynxerMain.h"
#include "MoreDialog.h"
#include "WaitDialog.h"
#include "include/wxImagePanel.h"
#include "include/LynxPhoto.h"
#include <wx/msgdlg.h>
#include <wx/mstream.h>

#define ICON_NAME "aaaa"

//(*InternalHeaders(RelynxerDialog)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(RelynxerDialog)
const long RelynxerDialog::ID_IMAGE = wxNewId();
const long RelynxerDialog::ID_STXHEADER = wxNewId();
const long RelynxerDialog::ID_STXMAINMESSAGE = wxNewId();
const long RelynxerDialog::ID_TXCURL = wxNewId();
const long RelynxerDialog::ID_STXYOURLINK = wxNewId();
const long RelynxerDialog::ID_TXCYOURLINK = wxNewId();
const long RelynxerDialog::ID_STXPASSWORD = wxNewId();
const long RelynxerDialog::ID_TXCPASSWORD = wxNewId();
const long RelynxerDialog::ID_STXUSAGES = wxNewId();
const long RelynxerDialog::ID_SPCUSAGES = wxNewId();
const long RelynxerDialog::ID_CHKEXPIREON = wxNewId();
const long RelynxerDialog::ID_DTPEXPIRATIONDATE = wxNewId();
const long RelynxerDialog::ID_CHKPUBLICLINK = wxNewId();
const long RelynxerDialog::ID_STXOPTIONALCUSTOMNAME = wxNewId();
const long RelynxerDialog::ID_TXCOPTIONALCUSTOMNAME = wxNewId();
const long RelynxerDialog::ID_SEPARATOR = wxNewId();
const long RelynxerDialog::ID_BTNMORE = wxNewId();
const long RelynxerDialog::ID_BACK = wxNewId();
const long RelynxerDialog::ID_NEXT = wxNewId();
//*)

BEGIN_EVENT_TABLE(RelynxerDialog,wxDialog)
    //(*EventTable(RelynxerDialog)
    //*)
END_EVENT_TABLE()

// common messages
wxString welcomeHeader;
wxString welcomeMessage;
wxString successHeader;
wxString successMessage;
// control pointers
wxFlexGridSizer* pntFgsDialogContents;
wxFlexGridSizer* pntFgsYourLink;
wxStaticBoxSizer* pntSbsAdditionalOptions;

RelynxerDialog::RelynxerDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(RelynxerDialog)
    wxFlexGridSizer* FgsDialogBody;
    wxFlexGridSizer* FgsOptionalCustomName;
    wxFlexGridSizer* FgsExpirationDatePublicLink;
    wxFlexGridSizer* FgsStepButtons;
    wxFlexGridSizer* FgsYourLink;
    wxFlexGridSizer* FgsDialogContents;
    wxFlexGridSizer* FgsMiscButtons;
    wxFlexGridSizer* FgsPasswordUsages;
    wxBoxSizer* BxsAdditionalOptions;
    wxFlexGridSizer* FgsDialogButtons;
    wxFlexGridSizer* FgsMain;
    wxStaticBoxSizer* SbsAdditionalOptions;

    Create(parent, wxID_ANY, _("Lynx.re Link Shortener Wizard"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    FgsMain = new wxFlexGridSizer(3, 1, 0, 0);
    FgsMain->AddGrowableCol(1);
    FgsMain->AddGrowableRow(1);
    FgsDialogBody = new wxFlexGridSizer(1, 2, 0, 0);
    FgsDialogBody->AddGrowableCol(1);
    FgsDialogBody->AddGrowableRow(0);
    PnlImage = new wxPanel(this, ID_IMAGE, wxDefaultPosition, wxSize(122,284), wxSUNKEN_BORDER|wxTAB_TRAVERSAL, _T("ID_IMAGE"));
    PnlImage->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    FgsDialogBody->Add(PnlImage, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FgsDialogContents = new wxFlexGridSizer(4, 1, 0, 0);
    StxHeader = new wxStaticText(this, ID_STXHEADER, _("<header>"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STXHEADER"));
    StxHeader->SetMinSize(wxSize(314,-1));
    wxFont StxHeaderFont(18,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("MS Serif"),wxFONTENCODING_DEFAULT);
    StxHeader->SetFont(StxHeaderFont);
    FgsDialogContents->Add(StxHeader, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StxMainMessage = new wxStaticText(this, ID_STXMAINMESSAGE, _("<main message>"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STXMAINMESSAGE"));
    StxMainMessage->SetMinSize(wxSize(314,-1));
    FgsDialogContents->Add(StxMainMessage, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TxcUrl = new wxTextCtrl(this, ID_TXCURL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXCURL"));
    FgsDialogContents->Add(TxcUrl, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FgsYourLink = new wxFlexGridSizer(1, 2, 0, 0);
    FgsYourLink->AddGrowableCol(1);
    FgsYourLink->AddGrowableRow(1);
    StxYourLink = new wxStaticText(this, ID_STXYOURLINK, _("Your link:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STXYOURLINK"));
    FgsYourLink->Add(StxYourLink, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TxcYourLink = new wxTextCtrl(this, ID_TXCYOURLINK, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TXCYOURLINK"));
    FgsYourLink->Add(TxcYourLink, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FgsDialogContents->Add(FgsYourLink, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    SbsAdditionalOptions = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Additional options"));
    BxsAdditionalOptions = new wxBoxSizer(wxVERTICAL);
    FgsPasswordUsages = new wxFlexGridSizer(1, 4, 0, 0);
    FgsPasswordUsages->AddGrowableCol(1);
    FgsPasswordUsages->AddGrowableRow(1);
    StxPassword = new wxStaticText(this, ID_STXPASSWORD, _("Password:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STXPASSWORD"));
    FgsPasswordUsages->Add(StxPassword, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TxcPassword = new wxTextCtrl(this, ID_TXCPASSWORD, wxEmptyString, wxDefaultPosition, wxSize(60,-1), 0, wxDefaultValidator, _T("ID_TXCPASSWORD"));
    TxcPassword->SetMaxLength(10);
    FgsPasswordUsages->Add(TxcPassword, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StxUsages = new wxStaticText(this, ID_STXUSAGES, _("Usages:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STXUSAGES"));
    FgsPasswordUsages->Add(StxUsages, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SpcUsages = new wxSpinCtrl(this, ID_SPCUSAGES, _T("0"), wxDefaultPosition, wxSize(76,-1), 0, 0, 100000, 0, _T("ID_SPCUSAGES"));
    SpcUsages->SetValue(_T("0"));
    FgsPasswordUsages->Add(SpcUsages, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BxsAdditionalOptions->Add(FgsPasswordUsages, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FgsExpirationDatePublicLink = new wxFlexGridSizer(1, 3, 0, 0);
    FgsExpirationDatePublicLink->AddGrowableCol(1);
    FgsExpirationDatePublicLink->AddGrowableRow(1);
    ChkExpireOn = new wxCheckBox(this, ID_CHKEXPIREON, _("Expire on:"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHKEXPIREON"));
    ChkExpireOn->SetValue(false);
    FgsExpirationDatePublicLink->Add(ChkExpireOn, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DtpExpirationDate = new wxDatePickerCtrl(this, ID_DTPEXPIRATIONDATE, wxDefaultDateTime, wxDefaultPosition, wxSize(90,-1), wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_DTPEXPIRATIONDATE"));
    DtpExpirationDate->Disable();
    FgsExpirationDatePublicLink->Add(DtpExpirationDate, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ChkPublicLink = new wxCheckBox(this, ID_CHKPUBLICLINK, _("Public link"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHKPUBLICLINK"));
    ChkPublicLink->SetValue(true);
    FgsExpirationDatePublicLink->Add(ChkPublicLink, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    BxsAdditionalOptions->Add(FgsExpirationDatePublicLink, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FgsOptionalCustomName = new wxFlexGridSizer(1, 2, 0, 0);
    FgsOptionalCustomName->AddGrowableCol(1);
    FgsOptionalCustomName->AddGrowableRow(1);
    StxOptionalCustomName = new wxStaticText(this, ID_STXOPTIONALCUSTOMNAME, _("Optional custom name:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STXOPTIONALCUSTOMNAME"));
    FgsOptionalCustomName->Add(StxOptionalCustomName, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TxcOptionalCustomName = new wxTextCtrl(this, ID_TXCOPTIONALCUSTOMNAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXCOPTIONALCUSTOMNAME"));
    TxcOptionalCustomName->SetMaxLength(60);
    FgsOptionalCustomName->Add(TxcOptionalCustomName, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BxsAdditionalOptions->Add(FgsOptionalCustomName, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    SbsAdditionalOptions->Add(BxsAdditionalOptions, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FgsDialogContents->Add(SbsAdditionalOptions, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FgsDialogBody->Add(FgsDialogContents, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FgsMain->Add(FgsDialogBody, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    SlnSeparator = new wxStaticLine(this, ID_SEPARATOR, wxDefaultPosition, wxSize(455,-1), wxLI_HORIZONTAL, _T("ID_SEPARATOR"));
    FgsMain->Add(SlnSeparator, 1, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    FgsDialogButtons = new wxFlexGridSizer(1, 2, 0, 0);
    FgsDialogButtons->AddGrowableCol(1);
    FgsDialogButtons->AddGrowableRow(1);
    FgsMiscButtons = new wxFlexGridSizer(1, 1, 0, 0);
    BtnMore = new wxButton(this, ID_BTNMORE, _("More..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTNMORE"));
    FgsMiscButtons->Add(BtnMore, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FgsDialogButtons->Add(FgsMiscButtons, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FgsStepButtons = new wxFlexGridSizer(1, 3, 0, 0);
    BtnBack = new wxButton(this, ID_BACK, _("< &Back"), wxDefaultPosition, wxSize(85,-1), 0, wxDefaultValidator, _T("ID_BACK"));
    BtnBack->Disable();
    FgsStepButtons->Add(BtnBack, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    BtnNext = new wxButton(this, ID_NEXT, _("&Next >"), wxDefaultPosition, wxSize(85,-1), 0, wxDefaultValidator, _T("ID_NEXT"));
    BtnNext->SetDefault();
    FgsStepButtons->Add(BtnNext, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    BtnCancel = new wxButton(this, wxID_OK, _("Cancel"), wxDefaultPosition, wxSize(85,-1), 0, wxDefaultValidator, _T("wxID_OK"));
    FgsStepButtons->Add(BtnCancel, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FgsDialogButtons->Add(FgsStepButtons, 1, wxALL|wxALIGN_RIGHT|wxALIGN_BOTTOM, 0);
    FgsMain->Add(FgsDialogButtons, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FgsMain);
    FgsMain->Fit(this);
    FgsMain->SetSizeHints(this);
    Center();

    Connect(ID_CHKEXPIREON,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&RelynxerDialog::OnChkExpireOnClick);
    Connect(ID_BTNMORE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RelynxerDialog::OnBtnMoreClick);
    Connect(ID_BACK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RelynxerDialog::OnBtnBackClick);
    Connect(ID_NEXT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RelynxerDialog::OnBtnNextClick);
    Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RelynxerDialog::OnBtnCancelClick);
    //*)

    SetIcon(wxIcon(wxT(ICON_NAME)));
    welcomeHeader = _("Welcome to Relynxer");
    welcomeMessage = _("This wizard will guide you through the process of shortening your\nlink.\n\nTo continue, please enter the website URL you want to generate\na shortened link of:");
    successHeader = _("Ready to share");
    successMessage = _("Your shortened link has been successfully generated! Now you\ncan share it with anyone you want to.\n\nTo shorten another link, please return to the previous step.");

    StxHeader->SetLabel(welcomeHeader);
    StxMainMessage->SetLabel(welcomeMessage);
    FgsDialogContents->Hide(FgsYourLink);
    RefreshDialogView();

    TxcUrl->SetFocus();
    wxMemoryInputStream mInput(lynxPhoto, LYNX_PHOTO_SIZE);
    wxImage wizardImage(mInput, wxBITMAP_TYPE_JPEG);
    wxPanel *drawPanel = new wxImagePanel(PnlImage, wizardImage);
    drawPanel->SetSize(118, 280);

    pntFgsDialogContents = FgsDialogContents;
    pntFgsYourLink = FgsYourLink;
    pntSbsAdditionalOptions = SbsAdditionalOptions;
}

RelynxerDialog::~RelynxerDialog()
{
    //(*Destroy(RelynxerDialog)
    //*)
}

void RelynxerDialog::RefreshDialogView()
{
    GetSizer()->Layout();
    GetSizer()->Fit(this);
    this->CentreOnScreen();
}

void RelynxerDialog::SwitchStep()
{
    this->Freeze();

    if (pntFgsDialogContents->IsShown(pntSbsAdditionalOptions))
    {
        StxHeader->SetLabel(successHeader);
        StxMainMessage->SetLabel(successMessage);
        pntFgsDialogContents->Hide(pntSbsAdditionalOptions);
        pntFgsDialogContents->Show(pntFgsYourLink);
        TxcUrl->Disable();
        TxcYourLink->SetValue(finalUrl);
        TxcYourLink->SetFocus();
        TxcYourLink->SelectAll();

        BtnBack->Enable();
        BtnNext->SetLabel(_("Finish"));

        RefreshDialogView();
    }
    else
    {
        StxHeader->SetLabel(welcomeHeader);
        StxMainMessage->SetLabel(welcomeMessage);
        pntFgsDialogContents->Hide(pntFgsYourLink);
        pntFgsDialogContents->Show(pntSbsAdditionalOptions);
        TxcUrl->Enable();
        TxcUrl->SetFocus();
        TxcUrl->SelectAll();

        BtnBack->Disable();
        BtnNext->SetLabel(_("&Next >"));

        RefreshDialogView();
    }

    this->Thaw();
}

LinkParams RelynxerDialog::PrepareLinkParams()
{
    LinkParams *linkParams = new LinkParams();

    linkParams->url = TxcUrl->GetValue().Trim();
    linkParams->url.Replace(wxT("&"), wxT("%26"));

    linkParams->custom = TxcOptionalCustomName->GetValue().Trim();
    linkParams->isPrivate = !ChkPublicLink->IsChecked();
    linkParams->password = TxcPassword->GetValue().Trim();
    linkParams->uses = SpcUsages->GetValue();
    linkParams->expire = ChkExpireOn->IsChecked() ? DtpExpirationDate->GetValue().Format(wxT("%m/%d/%Y")) : wxT("");

    return *linkParams;
}

bool RelynxerDialog::ValidateFirstStep()
{
    bool result = false;

    if (TxcUrl->GetValue().Trim().IsEmpty())
    {
        wxMessageBox(_("You need to enter the URL in order to proceed."), _("Warning"), wxICON_EXCLAMATION);
        TxcUrl->SetFocus();
    }
    else
    {
        result = true;
    }

    return result;
}

void RelynxerDialog::OnBtnMoreClick(wxCommandEvent& event)
{
    MoreDialog *moreDialog = new MoreDialog(GetParent());
    moreDialog->ShowModal();
    wxDELETE(moreDialog);
}

void RelynxerDialog::OnBtnBackClick(wxCommandEvent& event)
{
    SwitchStep();
}

void RelynxerDialog::OnBtnNextClick(wxCommandEvent& event)
{
    if (pntFgsDialogContents->IsShown(pntSbsAdditionalOptions))
    {
        if (ValidateFirstStep())
        {
            LinkParams linkParams = PrepareLinkParams();

            WaitDialog *waitDialog = new WaitDialog(linkParams, GetParent());
            waitDialog->relynxerDialog = this;
            waitDialog->ShowModal();
            wxDELETE(waitDialog);

            if (!finalUrl.IsEmpty())
            {
                SwitchStep();
                finalUrl = wxT("");
            }
        }
    }
    else
    {
        Close();
    }
}

void RelynxerDialog::OnBtnCancelClick(wxCommandEvent& event)
{
    Close();
}

void RelynxerDialog::OnChkExpireOnClick(wxCommandEvent& event)
{
    DtpExpirationDate->Enable(ChkExpireOn->IsChecked());
}
