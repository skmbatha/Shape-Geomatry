/***************************************************************
 * Name:      Sample___Frame_Based_Empty_Project_Main.h
 * Purpose:   Defines Application Frame
 * Author:    Success Katlego Mbatha (skatlego.mbatha@gmail.com)
 * Created:   2019-01-02
 * Copyright: Success Katlego Mbatha (www.katlego98523.waplux.com)
 * License:
 **************************************************************/

#ifndef SAMPLE___FRAME_BASED_EMPTY_PROJECT_MAIN_H
#define SAMPLE___FRAME_BASED_EMPTY_PROJECT_MAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "Sample___Frame_Based_Empty_Project_App.h"
#include <iostream>
#include <conio.h>
#include <math.h>
#include <wx/splitter.h>
#include <wx/toolbar.h>
#include <wx/image.h>


#include <wx/event.h>

#include <wx/spinctrl.h>
#include <wx/spinbutt.h>

#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/combobox.h>

using namespace std;

class Sample___Frame_Based_Empty_Project_Frame:public wxFrame
{
    public:
        Sample___Frame_Based_Empty_Project_Frame(wxFrame *frame, const wxString& title);///Creator function
        ~Sample___Frame_Based_Empty_Project_Frame();///killer function

        ///FUNTIONS DECLARATIONS

        //MENU FUNCTIONS
        void OpenFile(wxCommandEvent& event);
        void Save_file(wxCommandEvent& event);
        void About(wxCommandEvent& event);
        void Quit(wxCommandEvent& event);

        //TOLBAR OPTIONS

        void Print(wxCommandEvent& event);

        //MATHS FUNTIONS AND VARIABLES

        void Update_Values(wxSpinEvent& event);
        void Calculate(wxCommandEvent& event);///contain all

        double Area(int shape,double l,double w,double h,double r);
        double Parameter(int shape,double l,double w,double h,double r);
        double Surface_Area(int shape,double l,double w,double h,double r);
        double Volume(int shape,double l,double w,double h,double r);

        ///-----------------------

        ///OTHER FUNTIONS

        void Change_bitmap(int shape);
        void UpdateTitle();
        void Submit(wxCommandEvent& event);///when submit is pressed
        void ClearAll(wxCommandEvent& event);
        void UpdateShape(wxCommandEvent& event);///Updatethe current shape to the system,update the title and the visual object
        void UpdateParam(wxCommandEvent& event);
        void UpdateVisualObj(wxPaintEvent& paint);



        //OTHER VARIABLES
        wxStaticText *temp=NULL;///Public pointer fot title
        wxWindow *rightwindowPtr=NULL;
        wxImage image;   ///INITIALISE THE IMAGE OOBJECT IN MEMORY(NOT DYNAMICALLY)
        wxImage image_resized;
        wxClientDC *ClientDC=NULL;

        wxSpinCtrl *SpinPtr1=NULL;
        wxSpinCtrl *SpinPtr2=NULL;
        wxSpinCtrl *SpinPtr3=NULL;
        wxSpinCtrl *SpinPtr4=NULL;

        ///-----------------------

        ///ENUM FOR  IDs..........

        enum Event_IDs{

        OnButton1_id=67,
        OnButton2_id=68,
        OnButton3_id=69,
        OnButton4_id=70,

        OnClearAll_id,
        OnSubmit_id,
        OnShape_id,
        OnParam_id,
        OnShow_id,

        OnFile_id,
        OnAbout_id,
        OnQuit_id,
        OnOpen_id,
        OnSave_id
        };

        ///-----------------------

        ///ENUM FOR SHAPES AND VARIABLES

        enum Geometry_shapes{
            //THE SHAPES THENSELVES
            CIRCLE,
            TRIANGLE,
            RECTANGLE,
            CYLINDER,
            CONE,

            //PARAMETERS TO BE CALCULATED
            AREA,
            VOLUME,
            PARAMETER,
            SURFACE_AREA,
        };
        ///-----------------------


    private: static int CurrentShape;
             static int CurrentParam;
             static int CurrentShapeBackup;
             static int flag;

             static double length;
             static double width;
             static double radius;
             static double height;
             const double pi=3.14159265359;

             double Latest_Answer;

             DECLARE_EVENT_TABLE();///DEclare event table
};

#endif // SAMPLE___FRAME_BASED_EMPTY_PROJECT_MAIN_H
