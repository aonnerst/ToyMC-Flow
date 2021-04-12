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

Int_t gMarkers[]= {20,24,21,25,22,26,23};
Int_t gColors[]={kRed+1, kOrange+2, kCyan+2, kSpring-6, kRed-7, kOrange+1,kCyan-6,kGreen+7,kRed-9,kOrange-9,kAzure+6,kGreen-9};
void fitSingle()
{
	const Int_t NH = 5;
	Double_t vIn[NH]={0.0,0.12,0.06,0.03,0.01};
	//Read in deltaphi hist
	TFile *fIn = TFile::Open("outputDJ.root","read");

	TH1D *hPhiPsi[NH];
	TF1 *fFit[NH];
	TF1 *fFitvn[NH];

	for(Int_t n=0; n<=(NH-1); n++){
		hPhiPsi[n]=(TH1D*)fIn->Get(Form("hPhiPsi%02d",n+1));//Reading in the phi-psi histogram for all harmonics from output file.
	}

	hPhiPsi[1]->Print();

	TCanvas *can = new TCanvas("canvas","canvas",1024,740);
	can->SetFillStyle(4000);

	gStyle->SetOptStat(0);

	

  	Double_t vn[NH]={-999};
	Double_t vnError[NH]={-999};
    TLegend *legend = new TLegend(0.5,0.6,0.8,0.85,"","brNDC");
    legend->SetTextSize(0.04);legend->SetBorderSize(0);legend->SetFillStyle(0);//legend settings;

	//TF1 *fFit = new TF1("fFit","[0]*(1+2*[1]*TMath::Cos(x) + 2*[2]*TMath::Cos(x) + 2*[3]*TMath::Cos(x) + 2*[4]*TMath::Cos(x) + 2*[5]*TMath::Cos(x))", 0, 2.0*TMath::Pi());//Declaring fit
	//fFit->SetParameter(0,1E4);
	for (Int_t n=0; n<NH; n++){
		TString formula = Form("[0]*(1 + 2*[1]*TMath::Cos(%d*x))");
		fFit[n] = new TF1(Form("fFit%02d",n+1), "[0]*(1 + 2*[1]*TMath::Cos(%d*x))",0, 2.0*TMath::Pi())
		fFit[n]->SetParameter(0,1E4);
		fFit[n]->SetParameter(n+1,vIn[n])
	}
	
	for (Int_t n=0; n<NH; n++){	
		hPhiPsi[n]->Fit(Form("fFit%02d",n+1));
	}
	//For editing canvas #include "include/rootcommon.h"
	Double_t lowx = 0.,highx=2*TMath::Pi();
  	Double_t ly=hPhiPsi[1]->GetMinimum()*0.99,hy=hPhiPsi[1]->GetMaximum()*1.01;
  	TH2F *hfr = new TH2F("hfr"," ", 100,lowx, highx, 10, ly, hy); // numbers: tics x, low limit x, upper limit x, tics y, low limit y, upper limit y
  	hset( *hfr, "#Delta#phi=#phi-#psi_{n}", "dN/d#Delta#phi",0.65,0.65, 0.07,0.07, 0.01,0.01, 0.04,0.05, 510,505);//settings of the upper pad: x-axis, y-axis
  	hfr->Draw();

	for (Int_t n=0; n<NH; n++){	
		hPhiPsi[n]->SetMarkerStyle(20);
		hPhiPsi[n]->SetMarkerColor(gColors[n]);
		hPhiPsi[n]->Draw("psame");
		fFit[n]->SetLineColor(gColors[n]);
		fFit[n]->Draw("same");

		vn[n]=fFit[n]->GetParameter(n+1);
		vnError[n]=fFit[n]->GetParError(n+1);
		legend->AddEntry(fFit[n],Form("n = %d, v_n = %.3f #pm %.4f ",n+1, vn[n], vnError[n]),"l");
	}

	legend->Draw();
	gPad->GetCanvas()->SaveAs("figs/SingleParticle.pdf");



	//get vn's from fit
	

	//for loop 

}