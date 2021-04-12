#include "TMath.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TRandom3.h"
#include "TH1.h"
#include "TFile.h"
#include "TRatioPlot.h"
#include "TString.h"
#include "include/rootcommon.h"

Int_t gMarkers[]= {20,24,21,25,22,26,23,27,32,28};
Int_t gColors[]={kRed+1, kOrange+2, kCyan+2, kSpring-6, kRed-7, kOrange+1,kCyan-6,kGreen+7,kRed-9,kOrange-9,kAzure+6,kGreen-9};
Int_t gStyles[]={1,2,3,4,5,6,7,8,9,10};

void PhiEventByEvent()
{
	TFile *fIn = TFile::Open("outputDJ.root","read");
    const Int_t NH = 5;
    const Int_t NPhiHist = 10;

    TH1D *hPhiEvent[NPhiHist];

    TF1 *fourier = (TF1*)fIn->Get("Fourier");
    //TF1 *uniform= new TF1("uniform","[0]", 0.0, 2.0*TMath::Pi());
    //uniform->SetParameter(0,60.);
   // TF1 *fourier = new TF1("Fourier", "[0]*(1+2*[1]*TMath::Cos(1*(x-[6])) + 2*[2]*TMath::Cos(2*(x-[7])) + 2*[3]*TMath::Cos(3*(x-[8])) + 2*[4]*TMath::Cos(4*(x-[9])) + 2*[5]*TMath::Cos(5*(x-[10])))", 0.0, 2.0*TMath::Pi());
    //fourier->Scale(60,"width");
    //fourier->Print();

    gStyle->SetOptStat(0);
    TCanvas *cPhi = new TCanvas("cPhi","cPhi");

    for (Int_t i=0; i<=(NPhiHist-1); i++){
    	hPhiEvent[i]=(TH1D*)fIn->Get(Form("hPhiEvent%02d",i+1));
    	//hResolutionDist[i]->Sumw2();
	   	//hResolutionDist[i] -> SetLineColor(i+1);
    }

    double lowx = 0.,highx=2*TMath::Pi();
  	double ly=hPhiEvent[0]->GetMinimum()*0.1,hy=hPhiEvent[0]->GetMaximum()*1.4;
  	TH2F *hfr = new TH2F("hfr"," ", 100,lowx, highx, 10, ly, hy); // numbers: tics x, low limit x, upper limit x, tics y, low limit y, upper limit y
  	hset( *hfr, "#phi", "dN/d#phi",0.45,0.45, 0.07,0.07, 0.01,0.01, 0.03,0.03, 510,505);//settings of the upper pad: x-axis, y-axis
  	hfr->Draw();

  	/*fourier->SetLineColor(kBlack);
   	fourier->SetLineStyle(10);
   	fourier->Draw("same");*/


  	TLegend *legendPhi = new TLegend(0.5,0.6,0.8,0.85,"","brNDC");
    legendPhi->SetTextSize(0.04);legendPhi->SetBorderSize(0);legendPhi->SetFillStyle(0);//legend settings;

    for(Int_t i=0; i<=(NPhiHist-5); i++){
   		hPhiEvent[i]->Draw("same");
   		hPhiEvent[i]->SetLineColor(gColors[i]);
   		hPhiEvent[i]->SetLineWidth(5);
   		//hResolutionDist[i]->SetLineStyle(gStyles[i]);
   		//hResolutionDist[i]->SetMarkerStyle(gMarkers[i]);
   		//hResolutionDist[i]->SetMarkerColor(gColors[i]);
   		legendPhi->AddEntry(hPhiEvent[i],Form("Event %d",i+1));
   	}
   	legendPhi -> Draw("same");
   	gPad->GetCanvas()->SaveAs("figs/PhiEventByEvent.pdf");

}