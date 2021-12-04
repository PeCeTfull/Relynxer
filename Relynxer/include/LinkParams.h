#ifndef LINKPARAMS_H
#define LINKPARAMS_H


struct LinkParams {
    wxString url;
    wxString custom;
    bool isPrivate;
    wxString password;
    int uses;
    wxString expire;
};

#endif // LINKPARAMS_H
