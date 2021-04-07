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



	TH1D *hPhiEvent01 = (TH1D*)fIn->Get("hPhiEvent01");
	TH1D *hPhiEvent02 = (TH1D*)fIn->Get("hPhiEvent02");
	TH1D *hPhiEvent03 = (TH1D*)fIn->Get("hPhiEvent03");
	TH1D *hPhiEvent04 = (TH1D*)fIn->Get("hPhiEvent04");
	TH1D *hPhiEvent05 = (TH1D*)fIn->Get("hPhiEvent05");
	TH1D *hPhiEvent06 = (TH1D*)fIn->Get("hPhiEvent06");
	TH1D *hPhiEvent07 = (TH1D*)fIn->Get("hPhiEvent07");
	TH1D *hPhiEvent08 = (TH1D*)fIn->Get("hPhiEvent08");
	TH1D *hPhiEvent09 = (TH1D*)fIn->Get("hPhiEvent09");
	TH1D *hPhiEvent10 = (TH1D*)fIn->Get("hPhiEvent10");

	TH1D *hPhiPsi01 = (TH1D*)fIn->Get("hPhiPsi01");
	TH1D *hPhiPsi02 = (TH1D*)fIn->Get("hPhiPsi02");
	TH1D *hPhiPsi03 = (TH1D*)fIn->Get("hPhiPsi03");
	TH1D *hPhiPsi04 = (TH1D*)fIn->Get("hPhiPsi04");
	TH1D *hPhiPsi05 = (TH1D*)fIn->Get("hPhiPsi05");

	TH1D *hPhiPsiQ01 = (TH1D*)fIn->Get("hPhiPsiQ01");
	TH1D *hPhiPsiQ02 = (TH1D*)fIn->Get("hPhiPsiQ02");
	TH1D *hPhiPsiQ03 = (TH1D*)fIn->Get("hPhiPsiQ03");
	TH1D *hPhiPsiQ04 = (TH1D*)fIn->Get("hPhiPsiQ04");
	TH1D *hPhiPsiQ05 = (TH1D*)fIn->Get("hPhiPsiQ05");

	TH1D *hDeltaPhi01 = (TH1D*)fIn->Get("hDeltaPhi01");
	TH1D *hDeltaPhi02 = (TH1D*)fIn->Get("hDeltaPhi02");
	TH1D *hDeltaPhi03 = (TH1D*)fIn->Get("hDeltaPhi03");
	TH1D *hDeltaPhi04 = (TH1D*)fIn->Get("hDeltaPhi04");
	TH1D *hDeltaPhi05 = (TH1D*)fIn->Get("hDeltaPhi05");

	TH1D *hResolutionDist01 = (TH1D*)fIn->Get("hResolutionDist01");
	TH1D *hResolutionDist02 = (TH1D*)fIn->Get("hResolutionDist02");
	TH1D *hResolutionDist03 = (TH1D*)fIn->Get("hResolutionDist03");
	TH1D *hResolutionDist04 = (TH1D*)fIn->Get("hResolutionDist04");
	TH1D *hResolutionDist05 = (TH1D*)fIn->Get("hResolutionDist05");

/*
	TF1 *fFit1 = (TF1*)fIn->Get("Fit1");
	TF1 *fFit2 = (TF1*)fIn->Get("Fit2");
	TF1 *fFit3 = (TF1*)fIn->Get("Fit3");
	TF1 *fFit4 = (TF1*)fIn->Get("Fit4");
	TF1 *fFit5 = (TF1*)fIn->Get("Fit5");*/
   	
   	/***********************
   	**** Style**************
   	************************/

   	//hPhiEvent01 -> Sumw2();
   	hPhiEvent01 -> SetMarkerStyle(20);
   	hPhiEvent01 -> SetLineColor(kRed-7);
	hPhiEvent01 -> SetMarkerColor(kRed-7);
	hPhiEvent01 -> GetXaxis()->SetTitle("#phi");
	hPhiEvent01 -> GetYaxis()->SetTitle("dN/d#phi");

	//hPhiEvent02 -> Sumw2();
   	hPhiEvent02 -> SetMarkerStyle(20);
   	hPhiEvent02 -> SetLineColor(kGreen-6);
	hPhiEvent02 -> SetMarkerColor(kGreen-6);

	//hPhiEvent03 -> Sumw2();
   	hPhiEvent03 -> SetMarkerStyle(20);
   	hPhiEvent03 -> SetLineColor(kCyan-3);
	hPhiEvent03 -> SetMarkerColor(kCyan-3);

	//hPhiEvent04 -> Sumw2();
   	hPhiEvent04 -> SetMarkerStyle(20);
   	hPhiEvent04 -> SetLineColor(kMagenta-9);
	hPhiEvent04 -> SetMarkerColor(kMagenta-9);


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
	//hDeltaPhi01 -> Fit("Fit1");

	//hDeltaPhi02 -> Sumw2();
   	hDeltaPhi02 -> SetMarkerStyle(20);
   	hDeltaPhi02 -> SetLineColor(kGreen-6);
	hDeltaPhi02 -> SetMarkerColor(kGreen-6);
	//hDeltaPhi02 -> Fit("Fit2");

	//hDeltaPhi03 -> Sumw2();
   	hDeltaPhi03 -> SetMarkerStyle(20);
   	hDeltaPhi03 -> SetLineColor(kCyan-3);
	hDeltaPhi03 -> SetMarkerColor(kCyan-3);
	//hDeltaPhi03 -> Fit("Fit3");

	//hDeltaPhi04 -> Sumw2();
   	hDeltaPhi04 -> SetMarkerStyle(20);
   	hDeltaPhi04 -> SetLineColor(kMagenta-9);
	hDeltaPhi04 -> SetMarkerColor(kMagenta-9);
	//hDeltaPhi04 -> Fit("Fit4");

	//hDeltaPhi05 -> Fit("Fit5");

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
	hResolutionDist04 -> SetMarkerColor(kMagenta-9);


	TLegend *legendPhi = new TLegend(0.3,0.3);
	legendPhi->AddEntry(hPhiEvent01,"Event 1");
	legendPhi->AddEntry(hPhiEvent02,"Event 2");
	legendPhi->AddEntry(hPhiEvent03,"Event 3");
	legendPhi->AddEntry(hPhiEvent04,"Event 4");

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


   	TCanvas *cPhiDist = new TCanvas("cPhiDist","cPhiDist");
   	hPhiEvent01 -> Draw("SAME");
   	hPhiEvent02 -> Draw("SAME");
   	hPhiEvent03 -> Draw("SAME");
   	hPhiEvent04 -> Draw("SAME");
   	/*hPhiEvent05 -> Draw();
   	hPhiEvent06 -> Draw();
   	hPhiEvent07 -> Draw();
   	hPhiEvent08 -> Draw();
   	hPhiEvent09 -> Draw();
   	hPhiEvent10 -> Draw();*/
   	legendPhi -> Draw("same");

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
 	legendResolution -> Draw("same");



}