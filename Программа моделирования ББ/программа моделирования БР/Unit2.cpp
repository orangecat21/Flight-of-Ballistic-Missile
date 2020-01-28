#include <vcl.h>
#include <stdio.h>
#include <math.h>

#pragma hdrstop

#include "Unit2.h"            
#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

#define  Rz   6371000

#define  Pi0  3.986e14

#define  Ro0  1.225

#define  Hm   7110

//---------------------------------------------------------------------------

    TForm2  * Form2 ;

  unsigned  t = 0;

    double  r  , Fi  , V  , Teta  ;

    double  a1 , a2 , a3 , a4 ;

    double  b1 , b2 , b3 , b4 ;

    double  c1 , c2 , c3 , c4 ;

    double  d1 , d2 , d3 , d4 ;

    double  f1 , W=0 , q=0 , nx = 0 , ny = 0;

    double  h = 1 ;

    double  P = 784800 ;

    double  Cx0 ;

    double  S ;

    double  CyAlfa ;

    double  Alfa  ;

    double  Teta1 ;

    double  hTek ;

    double vTime ;

      FILE  * asf ;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner) : TForm(Owner) {}

//---------------------------------------------------------------------------

double m( double tt )

{  return 1000 ;
}

//---------------------------------------------------------------------------

/*double r( double xx , double yy )

{  return sqrt( pow( xx , 2 ) + pow( yy+Rz , 2 ) ) ;
}  */

//---------------------------------------------------------------------------

double fHeight( double rr )

{  return rr - Rz ;
}

//---------------------------------------------------------------------------

double Ro( double hh )

{  return Ro0 * exp( - hh / Hm ) ;
}

//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender )

{  Cx0 = StrToFloat( Form1->LabeledEditCx0->Text ) ;

   S = StrToFloat( Form1->LabeledEditS->Text ) ;

   CyAlfa = StrToFloat( Form1->LabeledEditCyAlfa->Text ) ;

   vTime = StrToFloat( Form1->LabeledEditP->Text ) ;

   r = StrToFloat( Form1->LabeledEditr->Text ) ;

   Fi = StrToFloat( Form1->LabeledEditFi->Text ) ;

   V  = StrToFloat( Form1->LabeledEditV->Text ) ;

   Teta = StrToFloat( Form1->LabeledEditTeta->Text ) ;

   hTek = fHeight(r) ;


   /*-------------------------------------------------------------------------------------------*/

   asf = fopen( "BB.txt" , "wb" ) ;

   fprintf( asf ,
                "t" "\t" 
		"r" "\t\t"
		"Fi" "\t\t"
		"V" "\t\t"
		"Teta" "\t\t"
                "h" "\xd\xa\xd\xa") ;

  fprintf( asf ,
		"%u" "\t"
		"%f" "\t"
		"%f" "\t"
		"%f" "\t"
		"%f" "\t"
		"%.2f" "\xd\xa" ,
               t , r , Fi , V , Teta , hTek ) ;


   for ( t=1 ; t <= 5000 ; t++ )

   {
        if (hTek<90000)break;

         a1 = V * sin(Teta) ;

         b1 = (V * cos (Teta))/ r ;

         c1 = 0 - (Pi0 * sin(Teta))/(pow(r,2));

         d1 = 0 - (Pi0 * cos(Teta))/(pow( r , 2 )*V) + b1;

	 //f1 = (P+sqrt(pow(Cx0*S*q,2)+pow(CyAlfa*Alfa*S*q,2)))/m(t);


         /*-------------------------------------------------------------------------------------------*/

         a2 = (V+h/2*c1) * sin(Teta+h/2*d1) ;

         b2 = ((V+h/2*c1) * cos (Teta+h/2*d1))/ (r+h/2*a1) ;

         c2 = 0 - (Pi0 * sin(Teta+h/2*d1))/(pow(r+h/2*a1,2));

         d2 = 0 - (Pi0 * cos(Teta+h/2*d1))/(pow(r+h/2*a1,2)*(V+h/2*c1)) + b2;

         /*-------------------------------------------------------------------------------------------*/

         a3 = (V+h/2*c2) * sin(Teta+h/2*d2) ;

         b3 = ((V+h/2*c2) * cos (Teta+h/2*d2))/ (r+h/2*a2) ;

         c3 = 0 - (Pi0 * sin(Teta+h/2*d2))/(pow(r+h/2*a2,2));

         d3 = 0 - (Pi0 * cos(Teta+h/2*d2))/(pow(r+h/2*a2,2)*(V+h/2*c2)) + b3;

         /*-------------------------------------------------------------------------------------------*/

         a4 = (V+h*c3) * sin(Teta+h*d3) ;

         b4 = ((V+h*c3) * cos (Teta+h*d3))/ (r+h*a3) ;

         c4 = 0 - (Pi0 * sin(Teta+h*d3))/(pow(r+h*a3,2));

         d4 = 0 - (Pi0 * cos(Teta+h*d3))/(pow(r+h*a3,2)*(V+h*c3)) + b4;

         /*-------------------------------------------------------------------------------------------*/

         r += ( h * ( a1 + 2 * a2 + 2 * a3 + a4 ) / 6 ) ;

         Fi += ( h * ( b1 + 2 * b2 + 2 * b3 + b4 ) / 6 ) ;

         V += ( h * ( c1 + 2 * c2 + 2 * c3 + c4 ) / 6 ) ;

         Teta += ( h * ( d1 + 2 * d2 + 2 * d3 + d4 ) / 6 ) ;


     // W+=f1*h;

      hTek = fHeight(r) ;

      //Alfa = Teta1 - Teta + Fi ;

      //nx=(P-Cx0*S*q)/(m(t)*9.81);

      //ny=(P*Alfa+CyAlfa*Alfa*S*q)/(m(t)*9.81);

     // q=(Ro(hTek)*pow(V,2))/2;

      


         fprintf( asf ,
		"%u" "\t"
		"%f" "\t"
		"%f" "\t"
		"%f" "\t"
		"%f" "\t"
		"%.2f" "\xd\xa" ,
               t , r , Fi , V , Teta , hTek ) ;



      Chart1->Series[0]->AddXY( t , r , 0 , 0x000000ff ) ;

      Chart2->Series[0]->AddXY( t , Fi , 0 , 0x00007f00 ) ;

      Chart3->Series[0]->AddXY( t , V , 0 , 0x00007f00 ) ;

      Chart4->Series[0]->AddXY( t , Teta , 0 , 0x00ff0000 ) ;

      Chart5->Series[0]->AddXY( t , Alfa , 0 , 0x000000ff ) ;

      Chart6->Series[0]->AddXY( t , hTek , 0 , 0x00007f00 ) ;

      Chart8->Series[0]->AddXY( t , q , 0 , 0x00007f00 ) ;

      Chart9->Series[0]->AddXY( t , nx , 0 , 0x00007f00 ) ;

      Chart10->Series[0]->AddXY( t , ny , 0 , 0x00007f00 ) ;

      Chart11->Series[0]->AddXY( t , W , 0 , 0x00007f00 ) ;

   }

   fclose(asf) ;
   LabeledEdithTek->Text=r*sin(Fi);
   LabeledEditt->Text=t;
}

//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton1Click(TObject *Sender)

{  Chart1->Visible = true ;
   Chart2->Visible = false ;
   Chart3->Visible = false ;
   Chart4->Visible = false ;
   Chart5->Visible = false ;
   Chart6->Visible = false ;
   Chart8->Visible = false ;
   Chart9->Visible = false ;
   Chart10->Visible = false ;
   Chart11->Visible = false ;
}

//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton2Click(TObject *Sender)

{  Chart1->Visible = false ;
   Chart2->Visible = true ;
   Chart3->Visible = false ;
   Chart4->Visible = false ;
   Chart5->Visible = false ;
   Chart6->Visible = false ;
   Chart8->Visible = false ;
   Chart9->Visible = false ;
   Chart10->Visible = false ;
   Chart11->Visible = false ;
}

//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton3Click(TObject *Sender)

{  Chart1->Visible = false ;
   Chart2->Visible = false ;
   Chart3->Visible = true ;
   Chart4->Visible = false ;
   Chart5->Visible = false ;
   Chart6->Visible = false ;
   Chart8->Visible = false ;
   Chart9->Visible = false ;
   Chart10->Visible = false ;
   Chart11->Visible = false ;
}

//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton4Click(TObject *Sender)

{  Chart1->Visible = false ;
   Chart2->Visible = false ;
   Chart3->Visible = false ;
   Chart4->Visible = true ;
   Chart5->Visible = false ;
   Chart6->Visible = false ;
   Chart8->Visible = false ;
   Chart9->Visible = false ;
   Chart10->Visible = false ;
   Chart11->Visible = false ;
}

//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton5Click(TObject *Sender)

{  Chart1->Visible = false ;
   Chart2->Visible = false ;
   Chart3->Visible = false ;
   Chart4->Visible = false ;
   Chart5->Visible = true ;
   Chart6->Visible = false ;
   Chart8->Visible = false ;
   Chart9->Visible = false ;
   Chart10->Visible = false ;
   Chart11->Visible = false ;
}

//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton6Click(TObject *Sender)

{  Chart1->Visible = false ;
   Chart2->Visible = false ;
   Chart3->Visible = false ;
   Chart4->Visible = false ;
   Chart5->Visible = false ;
   Chart6->Visible = true ;
   Chart8->Visible = false ;
   Chart9->Visible = false ;
   Chart10->Visible = false ;
   Chart11->Visible = false ;
}

//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton8Click(TObject *Sender)
{

   Chart1->Visible = false ;
   Chart2->Visible = false ;
   Chart3->Visible = false ;
   Chart4->Visible = false ;
   Chart5->Visible = false ;
   Chart6->Visible = false ;
   Chart8->Visible = true ;
   Chart9->Visible = false ;
   Chart10->Visible = false ;
   Chart11->Visible = false ;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton9Click(TObject *Sender)
{

   Chart1->Visible = false ;
   Chart2->Visible = false ;
   Chart3->Visible = false ;
   Chart4->Visible = false ;
   Chart5->Visible = false ;
   Chart6->Visible = false ;
   Chart8->Visible = false ;
   Chart9->Visible = true ;
   Chart10->Visible = false ;
   Chart11->Visible = false ;

}
//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton10Click(TObject *Sender)
{

   Chart1->Visible = false ;
   Chart2->Visible = false ;
   Chart3->Visible = false ;
   Chart4->Visible = false ;
   Chart5->Visible = false ;
   Chart6->Visible = false ;
   Chart8->Visible = false ;
   Chart9->Visible = false ;
   Chart10->Visible = true ;
   Chart11->Visible = false ;

}
//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton11Click(TObject *Sender)
{
   Chart1->Visible = false ;
   Chart2->Visible = false ;
   Chart3->Visible = false ;
   Chart4->Visible = false ;
   Chart5->Visible = false ;
   Chart6->Visible = false ;
   Chart8->Visible = false ;
   Chart9->Visible = false ;
   Chart10->Visible = false ;
   Chart11->Visible = true ;
}
//---------------------------------------------------------------------------

