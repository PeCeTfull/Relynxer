#ifndef SENDREQUESTTHREAD_H
#define SENDREQUESTTHREAD_H

#include <wx/thread.h>
#include "../WaitDialog.h"

class SendRequestThread: public wxThread
{
    public:
        SendRequestThread(LinkParams requestedLinkParams);
        virtual ~SendRequestThread();
        void *Entry();
        WaitDialog *waitDialog;
    protected:
    private:
        LinkParams linkParams;
        wxString result = wxT("");
        wxString errorMessage = wxT("");
};

#endif // SENDREQUESTTHREAD_H
