#include <vcl.h>      

#pragma hdrstop

#include "Unit1.h"

#include "Unit2.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"       

USEFORM("Unit2.cpp", Form2);

//---------------------------------------------------------------------------

  TForm1  * Form1 ;

//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent * Owner) : TForm(Owner)
{
}          

//---------------------------------------------------------------------------
                                                   
void __fastcall TForm1::BRunClick(TObject *Sender)

{  Application->CreateForm( __classid(TForm2) , &Form2 ) ;

   Form2->Show() ;
}




