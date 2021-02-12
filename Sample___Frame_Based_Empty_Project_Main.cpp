/***************************************************************
 * Name:      Sample___Frame_Based_Empty_Project_Main.cpp
 * Purpose:   Code for Application Frame
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

#include "Sample___Frame_Based_Empty_Project_Main.h"
#include <string.h>

///Initialise all static members with zero

int Sample___Frame_Based_Empty_Project_Frame::CurrentShape=RECTANGLE;
int Sample___Frame_Based_Empty_Project_Frame::CurrentParam=SURFACE_AREA;
int Sample___Frame_Based_Empty_Project_Frame::CurrentShapeBackup=100;
int Sample___Frame_Based_Empty_Project_Frame::flag=0;

double Sample___Frame_Based_Empty_Project_Frame:: length=0;
double Sample___Frame_Based_Empty_Project_Frame:: width=0;
double Sample___Frame_Based_Empty_Project_Frame:: radius=0;
double Sample___Frame_Based_Empty_Project_Frame::height=0;

BEGIN_EVENT_TABLE(Sample___Frame_Based_Empty_Project_Frame, wxFrame)///==========================

///LIST OF EVENTS

EVT_MENU(OnAbout_id,Sample___Frame_Based_Empty_Project_Frame::About)///about funtion
EVT_MENU(OnQuit_id,Sample___Frame_Based_Empty_Project_Frame::Quit)///quit funtion

EVT_SPINCTRL(OnButton1_id,Sample___Frame_Based_Empty_Project_Frame::Update_Values)///spin control
EVT_SPINCTRL(OnButton2_id,Sample___Frame_Based_Empty_Project_Frame::Update_Values)
EVT_SPINCTRL(OnButton3_id,Sample___Frame_Based_Empty_Project_Frame::Update_Values)
EVT_SPINCTRL(OnButton4_id,Sample___Frame_Based_Empty_Project_Frame::Update_Values)

EVT_BUTTON(OnSubmit_id,Sample___Frame_Based_Empty_Project_Frame::Submit)
EVT_BUTTON(OnClearAll_id,Sample___Frame_Based_Empty_Project_Frame::ClearAll)

EVT_COMBOBOX(OnShape_id,Sample___Frame_Based_Empty_Project_Frame::UpdateShape)///ComboBox for shape
EVT_COMBOBOX(OnParam_id,Sample___Frame_Based_Empty_Project_Frame::UpdateParam)///ComboBox for Parameter

EVT_BUTTON(OnShow_id,Sample___Frame_Based_Empty_Project_Frame::Calculate)///Calculate and display value

EVT_PAINT(Sample___Frame_Based_Empty_Project_Frame::UpdateVisualObj)

END_EVENT_TABLE()///=============================================================================
///CONSTRUCTOR


Sample___Frame_Based_Empty_Project_Frame::Sample___Frame_Based_Empty_Project_Frame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
        /// ****************************************************************
        /// *                         MENU BAR                             *
        /// ****************************************************************

        ///Menu bar instantiation
        wxMenuBar *MyMenuBar=new wxMenuBar(wxMB_DOCKABLE);///create menu bar

        ///Instantiate menus
        wxMenu *File=new wxMenu(wxT("File"));
        wxMenu *About=new wxMenu(_("About"));
        wxMenu *Quit=new wxMenu(wxT("Quit"));


        ///Append options to menus
        File->Append(OnOpen_id, _("&Open \tAlt+O"), _("Manage the current environment.")); //append to file menu
        File->Append(OnSave_id,wxT("&Save \tAlt+S"),_("Save the current project"));

        About->Append(OnAbout_id,("&About \tAlt+A"),wxT("See about the application"));//append to about

        Quit->Append(OnQuit_id,wxT("&Exit \tAlt+E"),_T("Close the application"));        //appednd to quit

        ///Append menus to the menu bar

        MyMenuBar->Append(File,wxT("File"));
        MyMenuBar->Append(About,wxT("About"));
        MyMenuBar->Append(Quit,wxT("Quit"));

        SetMenuBar(MyMenuBar);///Display  the menu bar
        ///Done with menu bar

        ///****************************************************************
        ///*                       Tool bar add                           *
        ///****************************************************************

       // wxToolBar *Mytoolbar = new wxToolBar(this,wxID_ANY,wxPoint(40,0),wxSize(700,50)/*wxTB_HORZ_TEXT*/);



        ///****************************************************************
        ///*                     Windows +(spli)                          *
        ///****************************************************************

        wxSplitterWindow *splitter=new wxSplitterWindow(this, wxID_ANY,
                             wxPoint(0, 30), wxSize(700, 450), wxSP_3D);

        wxWindow *leftwindow= new wxWindow(splitter,wxID_ANY,wxPoint(0,20),wxSize(227,225),wxRAISED_BORDER);
        wxWindow *rightwindow= new wxWindow(splitter,wxID_ANY,wxPoint(247,20),wxSize(227,225),wxRAISED_BORDER);
        rightwindowPtr=rightwindow;///save right windows poiter in the Ptr

        splitter->Initialize(leftwindow);//you need this or esle nothing will show
        splitter->Initialize(rightwindow);//same here
        splitter->SetMinimumPaneSize(20);//cannot be minimised smaller than this

        splitter->SplitVertically( leftwindow, rightwindow,280);//split the two windows


        ///status bar
        CreateStatusBar(1);
        SetStatusText(_("Welcome to your Math assistant!!!"),0);///


        ///****************************************************************
        ///*                  Non static controls                         *
        ///****************************************************************

        //ADD SPINS

        wxSpinCtrl* spinCtrl1 = new wxSpinCtrl(leftwindow,OnButton1_id,///Add a spin control
        wxT("0"), wxPoint(30,40), wxSize(80,25), wxSP_ARROW_KEYS,-1000,1000,length);

        wxSpinCtrl* spinCtrl2 = new wxSpinCtrl(leftwindow,OnButton2_id,///Add a spin control
        wxT("0"), wxPoint(130,40), wxSize(80,25), wxSP_ARROW_KEYS,-1000,1000,width);

        wxSpinCtrl* spinCtrl3 = new wxSpinCtrl(leftwindow,OnButton3_id,///Add a spin control
        wxT("0"), wxPoint(30,105), wxSize(80,25), wxSP_ARROW_KEYS,-1000,1000,height);

        wxSpinCtrl* spinCtrl4 = new wxSpinCtrl(leftwindow,OnButton4_id,///Add a spin control
        wxT("0"), wxPoint(130,105), wxSize(80,25), wxSP_ARROW_KEYS,-1000,1000,radius);

        SpinPtr1=spinCtrl1;///SAVE THE SPIN BUTTON POINTERS INSIDE THE TEMP
        SpinPtr2=spinCtrl2;
        SpinPtr3=spinCtrl3;
        SpinPtr4=spinCtrl4;
        //ADD SPIN TEXT(DISCRIPTION)

        wxStaticText* label1 = new wxStaticText(leftwindow, wxID_ANY,
        wxT("LENGTH:"),wxPoint(30,10), wxSize(80,25), wxALIGN_LEFT);

        wxStaticText* label2 = new wxStaticText(leftwindow, wxID_ANY,
        wxT("BREADTH:"),wxPoint(130,10), wxSize(80,25), wxALIGN_LEFT);

        wxStaticText* label3 = new wxStaticText(leftwindow, wxID_ANY,
        wxT("HEIGHT:"),wxPoint(30,80), wxSize(80,25), wxALIGN_LEFT);

        wxStaticText* label4 = new wxStaticText(leftwindow, wxID_ANY,
        wxT("RADIUS:"),wxPoint(130,80), wxSize(80,25), wxALIGN_LEFT);

        //ADD OTHER BUTTON CONTROLS

        wxButton* Clearall = new wxButton(leftwindow,OnClearAll_id, wxT("Clear all"),wxPoint(27,170), wxSize(80,25));
        wxButton* SubmitVal = new wxButton(leftwindow,OnSubmit_id, wxT("Submit"),wxPoint(127,170), wxSize(80,25));
       // wxButton* other = new wxButton(leftwindow,OnClearAll_id, wxT("Clear all"),wxPoint(27,170), wxSize(80,25));
       // wxButton* other2 = new wxButton(leftwindow,OnClearAll_id, wxT("Clear all"),wxPoint(27,170), wxSize(80,25));

       //TITLE

            if(CurrentParam==AREA){
                 wxStaticText* title = new wxStaticText(rightwindow, wxID_ANY,wxT("AREA"),wxPoint(2,2), wxSize(80,25), wxALIGN_LEFT);;
                 title->SetFont(wxFont(20, 74 , 90, 90, false));///will come back to this
                 temp=title;
            }
            else if(CurrentParam==VOLUME){
                 wxStaticText* title = new wxStaticText(rightwindow, wxID_ANY,wxT("VOLUME"),wxPoint(2,2), wxSize(80,25), wxALIGN_LEFT);
                 title->SetFont(wxFont(20, 74, 90, 90, false, wxT("Arial")));///will come back to this
                 temp=title;
            }
            else if(CurrentParam==SURFACE_AREA){
                 wxStaticText* title = new wxStaticText(rightwindow, wxID_ANY,wxT("SURFACE AREA"),wxPoint(2,2), wxSize(80,25), wxALIGN_LEFT);
                 title->SetFont(wxFont(15, 74, 90, 90, false, wxT("Arial")));///will come back to this
                 temp=title;
            }
            else{
                 wxStaticText* title = new wxStaticText(rightwindow, wxID_ANY,wxT("PARAMETER"),wxPoint(2,2), wxSize(80,25), wxALIGN_LEFT);
                 title->SetFont(wxFont(15, 74, 90, 90, false, wxT("Arial")));///will come back to this
                 temp=title;
            }

         //ADD LINE

            wxStaticLine* staticLine = new wxStaticLine(rightwindow, wxID_ANY,
            wxPoint(10,45), wxSize(150,-1), wxLI_HORIZONTAL);

         //LABEL FOR OPTIONS

            wxArrayString Shape_Array;///declare a string array
            Shape_Array.Add(wxT("Circle"));///add options to the string array
            Shape_Array.Add(wxT("Square"));
            Shape_Array.Add(wxT("Triangle"));
            Shape_Array.Add(wxT("Cylinder"));
            Shape_Array.Add(wxT("Cone"));

            wxComboBox* Shape = new wxComboBox(rightwindow,OnShape_id,///instantiate the drop down menu
            wxT("Choose"), wxPoint(70,70), wxSize(80,50),
            Shape_Array, wxCB_DROPDOWN);
            ///-----------------------------------------------------------------------------------------
            wxArrayString Param_Array;///declare a string array
            Param_Array.Add(wxT("Area"));///add options to the string array
            Param_Array.Add(wxT("Volume"));
            Param_Array.Add(wxT("Surface_Area"));
            Param_Array.Add(wxT("Parameter"));

            wxComboBox* Param = new wxComboBox(rightwindow,OnParam_id,///instantiate the drop down menu
            wxT("Choose"), wxPoint(70,105), wxSize(80,50),
            Param_Array, wxCB_DROPDOWN);

            //ADD LABELS To drop down menue

            wxStaticText* label5 = new wxStaticText(rightwindow, wxID_ANY,
            wxT("SHAPE:"),wxPoint(5,75), wxSize(50,25), wxALIGN_LEFT);

            wxStaticText* label6 = new wxStaticText(rightwindow, wxID_ANY,
            wxT("PARAM:"),wxPoint(5,110), wxSize(50,25), wxALIGN_LEFT);

            //ADD A  SHOW ANS BUTTON

            wxButton* Getval = new wxButton(rightwindow,OnShow_id, wxT("Display ANS"),wxPoint(5,170), wxSize(150,25));

            //ADD A VERTICALL SEPERATOR LINE

            wxStaticLine* staticLine2 = new wxStaticLine(rightwindow, wxID_ANY,
            wxPoint(170,5), wxSize(2,225), wxLI_VERTICAL);


            ///2ND WINDOWS (2nd pane)

            wxStaticText* Visual = new wxStaticText(rightwindow, wxID_ANY,wxT("VISUAL OBJECT"),wxPoint(240,2), wxSize(150,25), wxALIGN_LEFT);
            Visual->SetFont(wxFont(16, 74, 90, 90, false, wxT("Arial")));///will come back to this

            //ADD SEPERATOR LINE

            wxStaticLine* staticLine3 = new wxStaticLine(rightwindow, wxID_ANY,
            wxPoint(180,45), wxSize(290,-1), wxLI_HORIZONTAL);

}


///-------------------------------------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------------------------------------

///DESTRUCTOR
Sample___Frame_Based_Empty_Project_Frame::~Sample___Frame_Based_Empty_Project_Frame()
{
}

///MORE CLASS FUNTION MEMBERS...

        ///FUNTIONS DECLARATIONS

        //MENU FUNCTIONS

        void Sample___Frame_Based_Empty_Project_Frame::OpenFile(wxCommandEvent& event)
        {
            ///Do some file handling stuff
            ///Import the file,read the  info into local varibales and then update the GUI controllers
        }

        void Sample___Frame_Based_Empty_Project_Frame::Save_file(wxCommandEvent& event)
        {
            ///File handling as well
        }

        void Sample___Frame_Based_Empty_Project_Frame::About(wxCommandEvent& event)
        {
            wxString About;
            About.Printf(_("This is the 1st major project\nbuilt by katlego just after finishing\nChaper 4 in the wxWindows book with windows!!!"));
            wxMessageBox(About,wxT("About"));
        }


        void Sample___Frame_Based_Empty_Project_Frame::Quit(wxCommandEvent& event)
        {
            Destroy();///Close the top frame and other frames windows
        }

        //TOLBAR OPTIONS

        void Sample___Frame_Based_Empty_Project_Frame::Print(wxCommandEvent& event)
        {
            ///No implemenation for now but this should sent the informatio to the printer
        }

        //TITLE UPDATE

        void Sample___Frame_Based_Empty_Project_Frame::UpdateTitle()
        {
             if(CurrentParam==AREA){
                 temp->SetLabel(_("AREA"));
            }
            else if(CurrentParam==VOLUME){
                 temp->SetLabel(_("VOLUME"));
            }
            else if(CurrentParam==SURFACE_AREA){
                 temp->SetLabel(_("SURFACE AREA"));
            }
            else if(CurrentParam==PARAMETER)
            {
                 temp->SetLabel(_("PARAMETER"));
            }


        }

        //MATHS FUNTIONS AND VARIABLES

        void Sample___Frame_Based_Empty_Project_Frame::Update_Values(wxSpinEvent& event)
        {
            ///Get information from the control and update local  varibles

            switch(event.GetId())///update static values from the spins
            {
            case OnButton1_id:length=event.GetValue();
                break;
            case OnButton2_id:width=event.GetValue();
                break;
            case OnButton3_id:height=event.GetValue();
                break;
            case OnButton4_id:radius=event.GetValue();
                break;
            }

        }

            void Sample___Frame_Based_Empty_Project_Frame::UpdateVisualObj(wxPaintEvent& paint)
            {

               if(CurrentShape!=CurrentShapeBackup)
                {
                //wxMessageBox(_("I'm IN"))
                wxClientDC rightDC(rightwindowPtr);

                if(CurrentShape==CIRCLE){
                image.LoadFile(_("shapes/Circle.jpeg"),wxBITMAP_TYPE_JPEG);
                }else if(CurrentShape==TRIANGLE){
                image.LoadFile(_("shapes/Triangle.jpeg"),wxBITMAP_TYPE_JPEG);
                }else if(CurrentShape==CONE){
                image.LoadFile(_("shapes/Cone.jpeg"),wxBITMAP_TYPE_JPEG);
                }else if(CurrentShape==CYLINDER){
                image.LoadFile(_("shapes/Cylinder.jpg"),wxBITMAP_TYPE_JPEG);
                }else if(CurrentShape==RECTANGLE){
                image.LoadFile(_("shapes/Rectangle.jpeg"),wxBITMAP_TYPE_JPEG);
                }

                image_resized=image.Scale(250,145);///scale the image
                wxBitmap bitmap(image_resized);///Convert the resized image into a bitmap
                rightDC.DrawBitmap(bitmap,wxPoint(200,55));///Draw bitmap on the screen
                CurrentShapeBackup=CurrentShape;///Save the current shape
                }
            }

        void Sample___Frame_Based_Empty_Project_Frame::Submit(wxCommandEvent& event)
        {
            wxString l,w,h,r;///declare local
            l=wxString::Format(wxT("%lf"),length);///format to strings
            w=wxString::Format(wxT("%lf"),width);
            h=wxString::Format(wxT("%lf"),height);
            r=wxString::Format(wxT("%lf"),radius);

            wxMessageBox(_("Values are submitted\n\nLength:"+l+"\nWidth:"+w+"\nHeight:"+h+"\nRadius:"+r));
        }

        void Sample___Frame_Based_Empty_Project_Frame::Calculate(wxCommandEvent& event)///contain all
        {
            double Answer;
            wxString Param;

            //Define functionality

            switch(CurrentParam)
            {
                case AREA:Answer=Area(CurrentShape,length,width,height,radius);
                          Param="Area";
                    break;
                case PARAMETER:Answer=Parameter(CurrentShape,length,width,height,radius);
                          Param="Parameter";
                    break;
                case SURFACE_AREA:Answer=Surface_Area(CurrentShape,length,width,height,radius);
                          Param="Surface Area";
                    break;
                case VOLUME:Answer=Volume(CurrentShape,length,width,height,radius);
                          Param="Volume";
                    break;
            }

            Latest_Answer=Answer;//Copy the latest answer to the funtion

            ///JUST FOR DISPLAY

            wxString l,w,h,r,a;///declare local
            l=wxString::Format(wxT("%.2lf"),length);///format to strings
            w=wxString::Format(wxT("%.2lf"),width);
            h=wxString::Format(wxT("%.2lf"),height);
            r=wxString::Format(wxT("%.2lf"),radius);
            a=wxString::Format(wxT("%.2lf"),Answer);

            if(CurrentShape==CIRCLE){
            wxMessageBox(wxT("The "+Param+" Answer for a Circle \nwith a radius of :"+r+" = "+a));}

            if(CurrentShape==CONE){
            wxMessageBox(wxT("The "+Param+" Answer for a Cone \nwith a radius of :"+r+" and a \nheight of : "+h+" = "+a));}

            if(CurrentShape==RECTANGLE){
            wxMessageBox(wxT("The "+Param+" Answer for a Square \nwith a length: "+l+" ,\nheight : "+h+" and width : "+w+" = "+a));}

            if(CurrentShape==CYLINDER){
            wxMessageBox(wxT("The "+Param+" Answer for a Cylinder \nwith a radius of : "+r+" and a \nheight of : "+h+" = "+a));}

            if(CurrentShape==TRIANGLE){
            wxMessageBox(wxT("The "+Param+" Answer for a Triangle \nwith a length(base): "+l+" and\nheight : "+h+" = "+a));}

            Answer=0;///Nullify the value
        }


        void Sample___Frame_Based_Empty_Project_Frame::ClearAll(wxCommandEvent& event)
        {
            ///clear all imputs and buffers
            SpinPtr1->SetValue(0);
            SpinPtr2->SetValue(0);
            SpinPtr3->SetValue(0);
            SpinPtr4->SetValue(0);

            length=0;
            width=0;
            height=0;
            radius=0;
        }

        void Sample___Frame_Based_Empty_Project_Frame::UpdateShape(wxCommandEvent& event)
        {

            if(!strcmp("Circle",event.GetString()))
            {
                CurrentShape=CIRCLE;
            }
            else if(!strcmp("Triangle",event.GetString()))
            {
                CurrentShape=TRIANGLE;
            }
            else if(!strcmp("Cylinder",event.GetString()))
            {
                CurrentShape=CYLINDER;
            }
            else if(!strcmp("Cone",event.GetString()))
            {
                 CurrentShape=CONE;
            }
            else if(!strcmp("Square",event.GetString()))
            {
                 CurrentShape=RECTANGLE;
            }

            ///NOTE!!!

            wxPaintEvent *paint=new wxPaintEvent(NULL);///MANUALLY CREATE AN EENT OBJECT FOR CALLIGN THE FUNTION
            Sample___Frame_Based_Empty_Project_Frame::UpdateVisualObj(*paint);
            delete paint;///delet the dynamically created pointer

        }

        void Sample___Frame_Based_Empty_Project_Frame::UpdateParam(wxCommandEvent& event)
        {
            if(strcmp("Area",event.GetString())==false)
            {
                CurrentParam=AREA;
            }
            else if(strcmp("Volume",event.GetString())==false)
            {
                CurrentParam=VOLUME;
            }
            else if(strcmp("Surface_Area",event.GetString())==false)
            {
                CurrentParam=SURFACE_AREA;
            }
            else if(strcmp("Parameter",event.GetString())==false)
            {
                CurrentParam=PARAMETER;
            }

            ///Update funtions title
            Sample___Frame_Based_Empty_Project_Frame::UpdateTitle();///UPDATE THE TITLE

        }



        ///====================================MATH FUNTIONS=================================================

        double Sample___Frame_Based_Empty_Project_Frame::Area(int shape,double l,double w,double h,double r)
        {
            double Answer;

            switch(shape)
            {
                case CIRCLE:Answer=pi*radius*radius;
                    break;
                case CYLINDER:Answer=pi*radius*radius*height;
                    break;
                case TRIANGLE:Answer=0.5*length*height;
                    break;
                case CONE:Answer=pi*radius*(sqrt(radius+sqrt(height*height+radius*radius)));
                    break;
                case RECTANGLE:Answer=length*width;
                    break;
            }

            return Answer;
        }

        double Sample___Frame_Based_Empty_Project_Frame::Parameter(int shape,double l,double w,double h,double r)
        {
            double Answer;

            switch(shape)
            {
                case CIRCLE:Answer=2*pi*radius;
                    break;
                case CYLINDER:Answer=4+pi*radius;
                    break;
                case TRIANGLE:Answer=length+sqrt((length/2)*(length/2)+(height*height));
                    break;
                case CONE:Answer=length+sqrt((length/2)*(length/2)+(height*height));
                    break;
                case RECTANGLE:Answer=length+width+height;
                    break;
            }

            return Answer;
        }

        double Sample___Frame_Based_Empty_Project_Frame::Surface_Area(int shape,double l,double w,double h,double r)
        {
            double Answer;

            switch(shape)
            {
                case CIRCLE:Answer=pi*4*radius*radius;
                    break;
                case CYLINDER:Answer=2*pi*radius*radius+2*pi*radius*height;
                    break;
                case TRIANGLE:Answer=0.5*length*height*4+length*width;
                    break;
                case CONE:Answer=pi*radius*(sqrt(radius+sqrt(height*height+radius*radius)));
                    break;
                case RECTANGLE:Answer=2*length*width+2*length*height*2*width*height;
                    break;
            }

            return Answer;
        }

        double Sample___Frame_Based_Empty_Project_Frame::Volume(int shape,double l,double w,double h,double r)
        {
            double Answer;

            switch(shape)
            {
                case CIRCLE:Answer=pi*radius*radius;
                    break;
                case CYLINDER:Answer=pi*radius*radius*height;
                    break;
                case TRIANGLE:Answer=0.5*length*height;
                    break;
                case CONE:Answer=pi*radius*(sqrt(radius+sqrt(height*height+radius*radius)));
                    break;
                case RECTANGLE:Answer=length*width;
                    break;
            }

            return Answer;
        }

        ///-----------------------

        ///OTHER FUNTIONS

        void Sample___Frame_Based_Empty_Project_Frame::Change_bitmap(int shape)
        {
            ///Change the geomerty picture
        }

        ///-----------------------
