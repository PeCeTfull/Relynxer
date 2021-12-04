/***************************************************************
 * Name:      RelynxerMain.h
 * Purpose:   Defines Application Frame
 * Author:    PeCeT_full (me@pecetfull.pl)
 * Created:   2019-11-23
 * Copyright: PeCeT_full (https://www.pecetfull.pl/)
 * Licence:   The MIT License
 **************************************************************/

#ifndef RELYNXERMAIN_H
#define RELYNXERMAIN_H

//(*Headers(RelynxerDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/datectrl.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>
#include <wx/panel.h>
#include <wx/dateevt.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include "include/LinkParams.h"

class RelynxerDialog: public wxDialog
{
    public:

        RelynxerDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~RelynxerDialog();
        wxString finalUrl = wxT("");

    private:

        void RefreshDialogView();
        void SwitchStep();
        LinkParams PrepareLinkParams();
        bool ValidateFirstStep();

        //(*Handlers(RelynxerDialog)
        void OnBtnMoreClick(wxCommandEvent& event);
        void OnBtnBackClick(wxCommandEvent& event);
        void OnBtnNextClick(wxCommandEvent& event);
        void OnBtnCancelClick(wxCommandEvent& event);
        void OnChkExpireOnClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(RelynxerDialog)
        static const long ID_IMAGE;
        static const long ID_STXHEADER;
        static const long ID_STXMAINMESSAGE;
        static const long ID_TXCURL;
        static const long ID_STXYOURLINK;
        static const long ID_TXCYOURLINK;
        static const long ID_STXPASSWORD;
        static const long ID_TXCPASSWORD;
        static const long ID_STXUSAGES;
        static const long ID_SPCUSAGES;
        static const long ID_CHKEXPIREON;
        static const long ID_DTPEXPIRATIONDATE;
        static const long ID_CHKPUBLICLINK;
        static const long ID_STXOPTIONALCUSTOMNAME;
        static const long ID_TXCOPTIONALCUSTOMNAME;
        static const long ID_SEPARATOR;
        static const long ID_BTNMORE;
        static const long ID_BACK;
        static const long ID_NEXT;
        //*)

        //(*Declarations(RelynxerDialog)
        wxTextCtrl* TxcYourLink;
        wxButton* BtnCancel;
        wxTextCtrl* TxcPassword;
        wxSpinCtrl* SpcUsages;
        wxButton* BtnBack;
        wxCheckBox* ChkPublicLink;
        wxButton* BtnMore;
        wxCheckBox* ChkExpireOn;
        wxButton* BtnNext;
        wxStaticText* StxOptionalCustomName;
        wxTextCtrl* TxcUrl;
        wxStaticText* StxPassword;
        wxStaticText* StxYourLink;
        wxTextCtrl* TxcOptionalCustomName;
        wxPanel* PnlImage;
        wxStaticText* StxHeader;
        wxStaticLine* SlnSeparator;
        wxDatePickerCtrl* DtpExpirationDate;
        wxStaticText* StxUsages;
        wxStaticText* StxMainMessage;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // RELYNXERMAIN_H
