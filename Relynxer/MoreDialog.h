#ifndef MOREDIALOG_H
#define MOREDIALOG_H

//(*Headers(MoreDialog)
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class MoreDialog: public wxDialog
{
	public:

		MoreDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~MoreDialog();

		//(*Declarations(MoreDialog)
		wxButton* BtnAbout;
		wxButton* BtnCloseWindow;
		wxButton* BtnLanguage;
		wxButton* BtnShowHideHTTPWarning;
		//*)

	protected:

		//(*Identifiers(MoreDialog)
		static const long ID_BTNSHOWHIDEHTTPWARNING;
		static const long ID_BTNLANGUAGE;
		static const long ID_BTNABOUT;
		//*)

	private:

        void HandleBtnShowHideHTTPWarningLabel();
        void ApplySettings();
        short chosenLanguageID;
        bool hiddenHTTPWarning;

		//(*Handlers(MoreDialog)
		void OnBtnShowHideHTTPWarningClick(wxCommandEvent& event);
		void OnBtnLanguageClick(wxCommandEvent& event);
		void OnBtnAboutClick(wxCommandEvent& event);
		void OnBtnCloseWindowClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
