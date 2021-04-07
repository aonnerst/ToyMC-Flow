#include "TMath.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TRandom3.h"
#include "TH1.h"
#include "TFile.h"
#include "TRatioPlot.h"
#include "TString.h"

void fit()
{
	//Read in deltaphi hist
	TH1D *hDeltaPhiSum;
	//declare function
	TF1 *fFit = new TF1("fTFit", "[0]*(1+2*TMath::Power([1],2)*TMath::Cos([2]*[3]) + 2*TMath::Power([4],2)*TMath::Cos([5]*[6]) + 2*TMath::Power([7],2)*TMath::Cos([8]*[9]) + 2*TMath::Power([10],2)*TMath::Cos([11]*[12]) + 2*TMath::Power([13],2)*TMath::Cos([14]*[15]))", 0, 2.0*TMath::Pi());;
	//set initial parameters for function

	//fit
	hDeltaPhiSum ->Fit("fFit"); 

	//get vn's from fit
	Double_t vn[NH]

	//for loop 
	vn[i]=fFit->GetParameter(i)
}