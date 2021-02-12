/***************************************************************
 * Name:      Sample___Frame_Based_Empty_Project_App.cpp
 * Purpose:   Code for Application Class
 * Author:    Success Katlego Mbatha (skatlego.mbatha@gmail.com)
 * Created:   2019-01-02
 * Copyright: Success Katlego Mbatha (www.katlego98523.waplux.com)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "Sample___Frame_Based_Empty_Project_App.h"
#include "Sample___Frame_Based_Empty_Project_Main.h"


IMPLEMENT_APP(Sample___Frame_Based_Empty_Project_App);

bool Sample___Frame_Based_Empty_Project_App::OnInit()
{

    wxInitAllImageHandlers();///Initialize all imagae handker to be used with wxImage

    Sample___Frame_Based_Empty_Project_Frame* frame = new Sample___Frame_Based_Empty_Project_Frame(0L, _("Shape Geometry"));

    wxImage backup_ico;
    wxImage Img(_("etc/IcoT.jpeg"),wxBITMAP_TYPE_JPEG);
    backup_ico=Img.Scale(128,128);
    wxBitmap bitIcon(backup_ico);
    wxIcon IcoT;
    IcoT.CopyFromBitmap(bitIcon);

    frame->SetIcon(IcoT); // To Set App Icon


    frame->SetSize(730,300);///hopefully in terms of pixels
    frame->SetPosition(wxPoint(300,100));
    frame->SetMaxSize(wxSize(700,300));///fix the external frame to the exact dimensions
    frame->Show();


    return true;
}
