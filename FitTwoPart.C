#include "TMath.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TRandom3.h"
#include "TH1.h"
#include "TFile.h"
#include "TRatioPlot.h"
#include "TString.h"

void FitTwoPart()
{

	const int NH=5;
	//Read in deltaphi hist
	TFile *fIn = TFile::Open("output.root","read");
	TH1D *hDeltaPhiSum = (TH1D*)fIn->Get("hDeltaPhiSum");
	hDeltaPhiSum->Print();
	
	//declare function
	TF1 *fFit = new TF1("fFit", "[0]*(1+2*TMath::Power([1],2)*TMath::Cos(1*x) + 2*TMath::Power([2],2)*TMath::Cos(2*x) + 2*TMath::Power([3],2)*TMath::Cos(3*x) + 2*TMath::Power([4],2)*TMath::Cos(4*x) + 2*TMath::Power([5],2)*TMath::Cos(5*x))", 0, 2.0*TMath::Pi());
	fFit->SetParameter(0,1E4);
	fFit->SetParameter(1,0);
	fFit->SetParameter(2,0.10);
	fFit->SetParameter(3,0.06);
	fFit->SetParameter(4,0.06);
	fFit->SetParameter(5,0.06);
	//fFit->SetParameterName("const","v1","v_2","v_3","v_4","v_5");
	TF1 *fFitvn[NH];

	
	//set initial parameters for function

	//fit
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);

	hDeltaPhiSum->SetMarkerStyle(20);
	hDeltaPhiSum->SetXTitle("#phi_{1}-#phi_{2}");
	hDeltaPhiSum->SetYTitle("dN/d#Delta#phi");
	hDeltaPhiSum->Draw("p");
	hDeltaPhiSum->Fit("fFit"); 
	fFit->SetLineColor(1);
	fFit->Draw("same");
    
    for (Int_t n=0; n<=(NH-1); n++){
    	TString formula = Form("[0]*(1 + 2*TMath::Power([1],2)*TMath::Cos(%d*x))",n+1);
		fFitvn[n]= new TF1(Form("fFitvn%02d",n+1),formula, 0, 2.0*TMath::Pi());//Jus for drawing
	}

	//get vn's from fit
	Double_t vn[NH]={-999};
	Double_t vnError[NH]={-999};
    TLegend *legendPhi = new TLegend(0.6,0.6,0.8,0.85);
	//for loop 
	for (Int_t n=1; n<=(NH-1); n++) {
		vn[n]=fFit->GetParameter(n+1);
		vnError[n]=fFit->GetParError(n+1);
		fFitvn[n]->SetParameter(1,vn[n]);// Setting individual component vn
		fFitvn[n]->SetParameter(0, fFit->GetParameter(0));//Normalization
		fFitvn[n]->SetLineColor(n+1);
		fFitvn[n]->Draw("same");
		legendPhi->AddEntry(fFitvn[n],Form("n = %d, v_n = %.3f #pm %.4f ",n+1, vn[n], vnError[n]));
	}	
	legendPhi->Draw();
	gPad->GetCanvas()->SaveAs("figs/TwoPartDecompose.pdf");
	return 0;
	TCanvas *can[NH];
	for (Int_t n=1; n<=(NH-1); n++) {
		can[n] = new TCanvas();
		hDeltaPhiSum->Draw();
		fFitvn[n]->Draw();
		legendPhi->Draw();

	}	

	
}