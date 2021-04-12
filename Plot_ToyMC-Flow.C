#include "TMath.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TRandom3.h"
#include "TH1.h"
#include "TFile.h"
#include "TRatioPlot.h"
#include "TString.h"

void plotToyMC(){

	 /**********************
     ** INPUT HISTOGRAMS **
     **********************/

    TFile *fIn = TFile::Open("outputDJ.root","read");
    const Int_t NH = 5;
    Int_t NPhiHist = 10;

    TH1D *hPhiEvent[NPhiHist];
    TH1D *hPhiPsi[NH];
    TH1D *hPhiPsiQ[NH];
    TH1D *hResolutionDist[NH];

    for (Int_t n=0; n<=(NH-1); n++){
    	hPhiPsi[n]=(TH1D*)fIn->Get(Form("hPhiEvent%02d",n+1));
    	hPhiPsiQ[n]=(TH1D*)fIn->Get(Form("hPhiPsiQ%02d",n+1));
    	hResolutionDist[n]=(TH1D*)fIn->Get(Form("hResolutionDist%02d",n+1));
    }

    for (Int_t i=0; i<=(NPhiHist-1); i++){
    	hPhiEvent[i]=(TH1D*)fIn->Get(Form("hPhiEvent%02d",i+1));
    	//hPhiEvent[i] -> SetMarkerStyle(20+i);
	   	hPhiEvent[i] -> SetLineColor(i+1);
		//hPhiEvent[i] -> SetMarkerColor(i+1);
		hPhiEvent[i] -> GetXaxis()->SetTitle("#phi");
		hPhiEvent[i] -> GetYaxis()->SetTitle("dN/d#phi");
    }
   	
   	TLegend *legendPhi = new TLegend(0.3,0.3);
	

	TCanvas *cPhiDist = new TCanvas("cPhiDist","cPhiDist");
   	for(Int_t i=0; i<=(NPhiHist-1); i++){
   		hPhiEvent[i] -> Draw("SAME");
   		legendPhi->AddEntry(hPhiEvent[i],Form("Event %d",i+1));
   	}
   	legendPhi -> Draw("same");
   	/***********************
   	**** Style**************
   	************************/



}