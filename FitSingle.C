#include "TMath.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TRandom3.h"
#include "TH1.h"
#include "TFile.h"
#include "TRatioPlot.h"
#include "TString.h"

void fitSingle()
{
	//Read in deltaphi hist
	TFile *fIn = TFile::Open("output.root","read");
	TH1D *hDeltaPhiSum = (TH1D*)fIn->Get();
	TH1D *hDeltaPhi[NH];
	//declare function
	TF1 *fFit = new TF1("fTFit", "[0]*1+2*[1]*TMath::Cos(x)", 0, 2.0*TMath::Pi());;
	//set initial parameters for function

	//Looping over NH
	//fit
	hDeltaPhiSum ->Fit("fFit"); 

	//get vn's from fit
	Double_t vn[NH]

	//for loop 
	vn[i]=fFit->GetParameter(i)
}