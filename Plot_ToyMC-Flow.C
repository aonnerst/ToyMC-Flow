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

    TFile *fIn = TFile::Open("output.root","read");
    const Int_t NH = 5;
    Int_t NPhiHist = 10;

    TH1D *hPhiEvent[NPhiHist];
    TH1D *hPhiPsi[NH];
    TH1D *hPhiPsiQ[NH];
    TH1D *hResolutionDist[NH];

    TH1D *hDeltaPhiSum = (TH1D*)fIn->Get("hDeltaPhiSum");

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

/*
	//hPhiPsi01 -> Sumw2();
   	hPhiPsi01 -> SetMarkerStyle(20);
   	hPhiPsi01 -> SetLineColor(kRed-7);
	hPhiPsi01 -> SetMarkerColor(kRed-7);
	hPhiPsi01 -> GetXaxis()->SetTitle("#phi - #psi_{n}");
	hPhiPsi01 -> GetYaxis()->SetTitle("dN/d#Delta#phi");

	//hPhiPsi02 -> Sumw2();
   	hPhiPsi02 -> SetMarkerStyle(20);
   	hPhiPsi02 -> SetLineColor(kGreen-6);
	hPhiPsi02 -> SetMarkerColor(kGreen-6);

	//hPhiPsi03 -> Sumw2();
   	hPhiPsi03 -> SetMarkerStyle(20);
   	hPhiPsi03 -> SetLineColor(kCyan-3);
	hPhiPsi03 -> SetMarkerColor(kCyan-3);

	//hPhiPsi04 -> Sumw2();
   	hPhiPsi04 -> SetMarkerStyle(20);
   	hPhiPsi04 -> SetLineColor(kMagenta-9);
	hPhiPsi04 -> SetMarkerColor(kMagenta-9);


	//hPhiPsiQ01 -> Sumw2();
   	hPhiPsiQ01 -> SetMarkerStyle(20);
   	hPhiPsiQ01 -> SetLineColor(kRed-7);
	hPhiPsiQ01 -> SetMarkerColor(kRed-7);
	hPhiPsiQ01 -> GetXaxis()->SetTitle("#phi - #psi_{n}");
	hPhiPsiQ01 -> GetYaxis()->SetTitle("dN/d#Delta#phi");

	//hPhiPsiQ02 -> Sumw2();
   	hPhiPsiQ02 -> SetMarkerStyle(20);
   	hPhiPsiQ02 -> SetLineColor(kGreen-6);
	hPhiPsiQ02 -> SetMarkerColor(kGreen-6);

	//hPhiPsiQ03 -> Sumw2();
   	hPhiPsiQ03 -> SetMarkerStyle(20);
   	hPhiPsiQ03 -> SetLineColor(kCyan-3);
	hPhiPsiQ03 -> SetMarkerColor(kCyan-3);

	//hPhiPsiQ04 -> Sumw2();
   	hPhiPsiQ04 -> SetMarkerStyle(20);
   	hPhiPsiQ04 -> SetLineColor(kMagenta-9);
	hPhiPsiQ04 -> SetMarkerColor(kMagenta-9);


	//hDeltaPhi01 -> Sumw2();
   	hDeltaPhi01 -> SetMarkerStyle(20);
   	hDeltaPhi01 -> SetLineColor(kRed-7);
	hDeltaPhi01 -> SetMarkerColor(kRed-7);
	hDeltaPhi01 -> GetXaxis()->SetTitle("#phi_{1} - #phi_{2}");
	hDeltaPhi01 -> GetYaxis()->SetTitle("dN/d#Delta#phi'");


	//hResolutionDist01 -> Sumw2();
   	hResolutionDist01 -> SetMarkerStyle(20);
   	hResolutionDist01 -> SetLineColor(kRed-7);
	hResolutionDist01 -> SetMarkerColor(kRed-7);
	hResolutionDist01 -> GetXaxis()->SetTitle("#psi_{n} - #psi_{EP}");
	hResolutionDist01 -> GetYaxis()->SetTitle("");

	//hResolutionDist02 -> Sumw2();
   	hResolutionDist02 -> SetMarkerStyle(20);
   	hResolutionDist02 -> SetLineColor(kGreen-6);
	hResolutionDist02 -> SetMarkerColor(kGreen-6);

	//hResolutionDist03 -> Sumw2();
   	hResolutionDist03 -> SetMarkerStyle(20);
   	hResolutionDist03 -> SetLineColor(kCyan-3);
	hResolutionDist03 -> SetMarkerColor(kCyan-3);

	//hResolutionDist04 -> Sumw2();
   	hResolutionDist04 -> SetMarkerStyle(20);
   	hResolutionDist04 -> SetLineColor(kMagenta-9);
	hResolutionDist04 -> SetMarkerColor(kMagenta-9);*/


	/*

	TLegend *legendPhiPsi = new TLegend(0.3,0.3);
	legendPhiPsi->AddEntry(hPhiPsi01, "n=1");
	legendPhiPsi->AddEntry(hPhiPsi02, "n=2");
	legendPhiPsi->AddEntry(hPhiPsi03, "n=3");
	legendPhiPsi->AddEntry(hPhiPsi04, "n=4");
	legendPhiPsi->AddEntry(hPhiPsi05, "n=5");


	TLegend *legendPhiPsiQ = new TLegend(0.3,0.3);
	legendPhiPsiQ->AddEntry(hPhiPsiQ01, "n=1");
	legendPhiPsiQ->AddEntry(hPhiPsiQ02, "n=2");
	legendPhiPsiQ->AddEntry(hPhiPsiQ03, "n=3");
	legendPhiPsiQ->AddEntry(hPhiPsiQ04, "n=4");
	legendPhiPsiQ->AddEntry(hPhiPsiQ05, "n=5");

	TLegend *legendDeltaPhi = new TLegend(0.3,0.3);
	legendDeltaPhi->AddEntry(hDeltaPhi01, "n=1");
	legendDeltaPhi->AddEntry(hDeltaPhi02, "n=2");
	legendDeltaPhi->AddEntry(hDeltaPhi03, "n=3");
	legendDeltaPhi->AddEntry(hDeltaPhi04, "n=4");
	legendDeltaPhi->AddEntry(hDeltaPhi05, "n=5");

	TLegend *legendResolution = new TLegend(0.2,0.3);
	legendResolution->AddEntry(hResolutionDist01, "n=1");
	legendResolution->AddEntry(hResolutionDist02, "n=2");
	legendResolution->AddEntry(hResolutionDist03, "n=3");
	legendResolution->AddEntry(hResolutionDist04, "n=4");
	legendResolution->AddEntry(hResolutionDist05, "n=5");
*/

  
/*
   	TCanvas *cPhiPsiDist = new TCanvas("cPhiPsiDist","cPhiPsiDist");
 	hPhiPsi01 -> Draw("same");
 	hPhiPsi02 -> Draw("same");
 	hPhiPsi03 -> Draw("same");
 	hPhiPsi04 -> Draw("same");
 	hPhiPsi05 -> Draw("same");
 	legendPhiPsi -> Draw("same");

 	TCanvas *cPhiPsiQDist = new TCanvas("cPhiPsiQDist","cPhiPsiQDist");
 	hPhiPsiQ01 -> Draw("same");
 	hPhiPsiQ02 -> Draw("same");
 	hPhiPsiQ03 -> Draw("same");
 	hPhiPsiQ04 -> Draw("same");
 	hPhiPsiQ05 -> Draw("same");
 	legendPhiPsiQ -> Draw("same");

 	TCanvas *cDeltaPhiDist = new TCanvas("cDeltaPhiDist","cDeltaPhiDist");
 	hDeltaPhi01 -> Draw("same");
 	hDeltaPhi02 -> Draw("same");
 	hDeltaPhi03 -> Draw("same");
 	hDeltaPhi04 -> Draw("same");
 	hDeltaPhi05 -> Draw("same");
 	legendDeltaPhi -> Draw("same");

 	TCanvas *cResolutionDist = new TCanvas("cResolutionDist","cResolutionDist");
 	hResolutionDist01 -> Draw("same");
 	hResolutionDist02 -> Draw("same");
 	hResolutionDist03 -> Draw("same");
 	hResolutionDist04 -> Draw("same");
 	hResolutionDist05 -> Draw("same");
 	legendResolution -> Draw("same");*/

}