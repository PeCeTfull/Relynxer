#ifndef WAITDIALOG_H
#define WAITDIALOG_H

//(*Headers(WaitDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include <wx/timer.h>
#include "RelynxerMain.h"

class WaitDialog: public wxDialog
{
	public:

		WaitDialog(LinkParams linkParams, wxWindow* parent, wxWindowID id=wxID_ANY);
		virtual ~WaitDialog();
        void CloseWithResult(wxString result = wxT(""));
        void CloseWithErrorMessage(wxString errorMessage = wxT(""));
        RelynxerDialog *relynxerDialog;

		//(*Declarations(WaitDialog)
		wxButton* BtnAbort;
		wxStaticText* StxWaitMessage;
		//*)

	protected:

		//(*Identifiers(WaitDialog)
		static const long ID_STXWAITMESSAGE;
		//*)

	private:

        void OnCloseTimer(wxTimerEvent& event);
        wxTimer closeTimer;
	    bool isClosing = false;
	    bool canClose = false;

		//(*Handlers(WaitDialog)
		void OnBtnAbortClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
