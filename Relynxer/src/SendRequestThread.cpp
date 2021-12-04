#include "../include/SendRequestThread.h"
#include "../include/curl/curl.h"
#include "../include/wx/jsonreader.h"

//helper functions
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size* nmemb);
    return size* nmemb;
}

SendRequestThread::SendRequestThread(LinkParams requestedLinkParams)
{
    //ctor

    linkParams = requestedLinkParams;
}

SendRequestThread::~SendRequestThread()
{
    //dtor

    curl_global_cleanup();
    if (!result.IsEmpty())
    {
        if(waitDialog != NULL) waitDialog->CloseWithResult(result);
    }
    else
    {
        if(waitDialog != NULL) waitDialog->CloseWithErrorMessage(errorMessage);
    }
}

void *SendRequestThread::Entry()
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if(curl)
    {
        wxString apiParams = wxString::Format(wxT("url=%s"), linkParams.url.c_str());
        if (!linkParams.custom.IsEmpty())
        {
            apiParams += wxString::Format(wxT("&custom=%s"), linkParams.custom.c_str());
        }
        if (linkParams.isPrivate)
        {
            apiParams += wxT("&private=true");
        }
        if (!linkParams.password.IsEmpty())
        {
            apiParams += wxString::Format(wxT("&password=%s"), linkParams.password.c_str());
        }
        if (linkParams.uses > 0)
        {
            apiParams += wxString::Format(wxT("&uses=%d"), linkParams.uses);
        }
        if (!linkParams.expire.IsEmpty())
        {
            apiParams += wxString::Format(wxT("&expire=%s"), linkParams.expire.c_str());
        }
        apiParams += wxT("&via=relynxer");

        std::string apiURLStr = "http://lynx.re/API/write/post";
        curl_easy_setopt(curl, CURLOPT_URL, apiURLStr.c_str());
        std::string apiParamsStr = std::string(apiParams.mb_str(wxConvUTF8));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, apiParamsStr.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if(res != CURLE_OK)
        {
            if(waitDialog != NULL)
            {
                waitDialog->BtnAbort->Disable();
            }

            errorMessage = wxString::Format(_("Could not successfully establish the connection due to the following reason: %s."), wxGetTranslation(wxString::FromUTF8(curl_easy_strerror(res))));
        }
        else
        {
            wxString apiResult(readBuffer.c_str(), wxConvUTF8);

            wxJSONValue jsonRoot;
            wxJSONReader jsonReader;

            int numErrors = jsonReader.Parse(apiResult, &jsonRoot);
            if(waitDialog != NULL)
            {
                waitDialog->BtnAbort->Disable();
            }

            if(numErrors > 0)
            {
                errorMessage = _("An error has occurred while processing the request. Enter another URL or try again later.");
            }
            else if(jsonRoot[wxT("success")].AsString() == wxT("true"))
            {
                result = jsonRoot[wxT("data")][wxT("url")].AsString();
            }
            else
            {
                wxString reason = jsonRoot[wxT("error")][wxT("msg")].AsString();

                if(!reason.IsEmpty())
                    errorMessage = wxString::Format(_("An error has occurred due to the following reason: %s."), wxGetTranslation(reason));
                else
                    errorMessage = _("Unknown error.");
            }
        }
    }
}
