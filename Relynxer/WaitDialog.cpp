#include "WaitDialog.h"
#include "include/SendRequestThread.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(WaitDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(WaitDialog)
const long WaitDialog::ID_STXWAITMESSAGE = wxNewId();
//*)

BEGIN_EVENT_TABLE(WaitDialog,wxDialog)
EVT_TIMER(4949, WaitDialog::OnCloseTimer)
	//(*EventTable(WaitDialog)
	//*)
END_EVENT_TABLE()

SendRequestThread *sendRequestThread = NULL;

WaitDialog::WaitDialog(LinkParams linkParams, wxWindow* parent, wxWindowID id) : closeTimer(this, 4949)
{
	//(*Initialize(WaitDialog)
	wxFlexGridSizer* FgsMain;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxCAPTION, _T("id"));
	FgsMain = new wxFlexGridSizer(2, 1, 0, 0);
	StxWaitMessage = new wxStaticText(this, ID_STXWAITMESSAGE, _("Please wait while a new redirecting link is being generated..."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STXWAITMESSAGE"));
	FgsMain->Add(StxWaitMessage, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	BtnAbort = new wxButton(this, wxID_OK, _("Abort"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	FgsMain->Add(BtnAbort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FgsMain);
	FgsMain->Fit(this);
	FgsMain->SetSizeHints(this);
	Center();

	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&WaitDialog::OnBtnAbortClick);
	//*)

	sendRequestThread = new SendRequestThread(linkParams);

    sendRequestThread->waitDialog = this;

    sendRequestThread->Create();
    sendRequestThread->Run();

    this->SetCursor(wxCURSOR_ARROWWAIT);

    closeTimer.Start(1000);
}

WaitDialog::~WaitDialog()
{
	//(*Destroy(WaitDialog)
	//*)

	relynxerDialog = NULL;
}

void WaitDialog::CloseWithResult(wxString result)
{
    if (!isClosing)
    {
        isClosing = true;

        if(sendRequestThread)
        {
            sendRequestThread->waitDialog = NULL;
        }

        if(relynxerDialog != NULL) relynxerDialog->finalUrl = result;
        Close();
    }
}

void WaitDialog::CloseWithErrorMessage(wxString errorMessage)
{
    if (!isClosing)
    {
        isClosing = true;

        if(sendRequestThread)
        {
            sendRequestThread->waitDialog = NULL;
        }

        if (!errorMessage.IsEmpty())
        {
            wxMessageBox(errorMessage, _("Error"), wxICON_HAND);
        }

        canClose = true;
    }
}

void WaitDialog::OnBtnAbortClick(wxCommandEvent& event)
{
    CloseWithErrorMessage();
}

void WaitDialog::OnCloseTimer(wxTimerEvent& event)
{
    if (canClose)
    {
        closeTimer.Stop();
        Close();
    }
}
