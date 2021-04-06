#include "TMath.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TRandom3.h"
#include "TH1.h"
#include "TFile.h"
#include "TRatioPlot.h"
#include "TString.h"

std::string prd(const double x, const int decDigits, const int width);
std::string center(const string s, const int w);

void toymc()
{
	// Declare variables
	const Int_t NH = 5; // number of harmonics
	Double_t vn[]={0,0.12,0.06,0.03,0.01}; // input values for vn
	Int_t Nevt = 100;
	Int_t Nch = 10;
	Int_t NPhiHist = 10;
	Double_t phiarray[Nch];//={{0.0},{0.0}} ;
	Double_t Psi_n[NH]={0.0};
	Double_t vn_psi[NH]={0.0};
	Double_t vn_obs_EP[NH]={0.0};
	Double_t vn_phi[NH]={0.0};
	Double_t weight = 1.0;
	Double_t Qn_x[NH];//={0.0};
	Double_t Qn_y[NH];//={0.0};
	Double_t MeanArrayTwoParticle[NH]={0.0};
	Double_t MeanArrayEventPlane[NH]={0.0};
	Double_t MeanArrayEventPlaneQVec[NH]={0.0};
	Double_t MeanArrayEvtPlError[NH]={0.0};
	Double_t MeanArrayEvtPlErrorQvec[NH]={0.0};
	Double_t MeanArrayTwoPartError[NH]={0.0};
	Double_t MeanArrayResolution[NH]={0.0};
	Double_t MeanArrayResolutionError[NH]={0.0};
	Double_t vn_obs_ERROR[NH]={0.0};
	Double_t vn_TwoPart[NH]={0.0};
	Double_t vn_EvtPl[NH]={0.0};
	Double_t vn_EvtPlQvec[NH]={0.0};
	Double_t Psi_n_EP[NH]={0.0};
	Double_t Resolution[NH]={0.0};
	//TString SignArray[NH]={"+-","+-","+-","+-","+-"};


	
	TString outfile = "output.root";
	TFile *output = new TFile(outfile,"recreate");
	output->cd();
	


	TF1 *uniform[NH];
	//TF1 *fourier[NH]; 

	TH1D *hEventPlane[NH];
	TH1D *hEventPlaneEP[NH];
	TH1D *hTwoParticle[NH];
	TH1D *hPhiPsi[NH];
	TH1D *hPhiPsiQ[NH];
	TH1D *hDeltaPhi[NH];
	TH1D *hPhiEvent[NPhiHist];
	TH1D *hResolution[NH];
	TH1D *hResolutionDist[NH];

	TF1 *fourier = new TF1("Fourier", "[0]*(1+2*[1]*TMath::Cos([2]*(x-[3])) + 2*[4]*TMath::Cos([5]*(x-[6])) + 2*[7]*TMath::Cos([8]*(x-[9])) + 2*[10]*TMath::Cos([11]*(x-[12])) + 2*[13]*TMath::Cos([14]*(x-[15])))", 0, 2.0*TMath::Pi());
	fourier->SetParameter(0,Nch); // any positive constant

	TF1 *fTwoparticle = new TF1("fTwoparticle", "[0]*(1+2*TMath::Power([1],2)*TMath::Cos([2]*[3]) + 2*TMath::Power([4],2)*TMath::Cos([5]*[6]) + 2*TMath::Power([7],2)*TMath::Cos([8]*[9]) + 2*TMath::Power([10],2)*TMath::Cos([11]*[12]) + 2*TMath::Power([13],2)*TMath::Cos([14]*[15]))", 0, 2.0*TMath::Pi());
	fTwoparticle->SetParameter(0,Nch); // any positive constant

	for (Int_t n=0; n<=(NH-1); n++){

		//------Distributions------
		uniform[n]= new TF1(Form("uniform%02d",n+1),"[0]", -1.0/(n+1)*TMath::Pi(), 1.0/(n+1)*TMath::Pi());
		uniform[n]->SetParameter(0,1.);


		//-----Histograms---------
		hEventPlane[n]=new TH1D(Form("hEventPlane%02d",n+1),Form("hEventPlane%02d",n+1),200,-1.0, 1.0);
		hEventPlaneEP[n]=new TH1D(Form("hEventPlaneEP%02d",n+1),Form("hEventPlaneEP%02d",n+1),200,-1.0, 1.0);
		hTwoParticle[n]=new TH1D(Form("hTwoParticle%02d",n+1),Form("hTwoParticle%02d",n+1),200,-1.0, 1.0);
		hPhiPsi[n] = new TH1D(Form("hPhiPsi%02d",n+1),Form("hPhiPsi%02d",n+1),200,0.0, 2.0*TMath::Pi());
		hPhiPsiQ[n] = new TH1D(Form("hPhiPsiQ%02d",n+1),Form("hPhiPsiQ%02d",n+1),200,0.0, 2.0*TMath::Pi());
		hDeltaPhi[n] = new TH1D(Form("hDeltaPhi%02d",n+1),Form("hDeltaPhi%02d",n+1),200,0.0, 2.0*TMath::Pi());
		hResolution[n] = new TH1D(Form("hResolution%02d",n+1),Form("hResolution%02d",n+1),200,-100, 100);
		hResolutionDist[n] = new TH1D(Form("hResolutionDist%02d",n+1),Form("hResolutionDist%02d",n+1),200,-10, 10);
	}

	TH1D *hDeltaPhiSum = new TH1D("hDeltaPhiSum","hDeltaPhiSum",200, 0.0, 2.0*TMath::Pi());




	for (Int_t iPhiEvt=0; iPhiEvt<NPhiHist; iPhiEvt++){
		hPhiEvent[iPhiEvt] = new TH1D(Form("hPhiEvent%02d",(iPhiEvt+1)),Form("hPhiEvent%02d",(iPhiEvt+1)),200,0.0, 2.0*TMath::Pi());
	}
	

	int ieout = Nevt/10;
    if (ieout<1) ieout=1;

	//Event loop
	for (Int_t iEvent=0; iEvent<Nevt; iEvent++)
	{
		if(iEvent % ieout == 0) cout << iEvent << "\t" << int(float(iEvent)/Nevt*100) << "%" << endl ;
		
		//Get Psi for different harmonics
		for (Int_t n=0; n<=(NH-1); n++)//harmonic loop
		{
			Psi_n[n]=uniform[n]->GetRandom();
		}

		phiarray[Nch]={0.0};

		
		fourier->SetParameter(1,vn[0]);
		fourier->SetParameter(2,1);
		fourier->SetParameter(3,Psi_n[0]);
		fourier->SetParameter(4,vn[1]);
		fourier->SetParameter(5,2);
		fourier->SetParameter(6,Psi_n[1]);
		fourier->SetParameter(7,vn[2]);
		fourier->SetParameter(8,3);
		fourier->SetParameter(9,Psi_n[2]);
		fourier->SetParameter(10,vn[3]);
		fourier->SetParameter(11,4);
		fourier->SetParameter(12,Psi_n[3]);
		fourier->SetParameter(13,vn[4]);
		fourier->SetParameter(14,5);
		fourier->SetParameter(15, Psi_n[4]);
	
		for (Int_t n=0; n<=(NH-1); n++)//harmonic loop
		{
			//Track loop
			for (Int_t t=0; t<Nch; t++)
			{
				phiarray[t] = fourier->GetRandom();

				if(iEvent<NPhiHist) hPhiEvent[iEvent]->Fill(phiarray[t]);

				hPhiPsi[n]->Fill(phiarray[t]-Psi_n[n]);
				
				vn_psi[n] = TMath::Cos((n+1)*(phiarray[t]-Psi_n[n]));
				hEventPlane[n]->Fill(vn_psi[n]);
				

				// calculating eventplane with Q-vectors
				Qn_x[n] += weight*TMath::Cos((n+1)*phiarray[t]);
				Qn_y[n] += weight*TMath::Sin((n+1)*phiarray[t]);



				Psi_n_EP[n]=(1/(n+1))*TMath::ATan(Qn_y[n]/Qn_x[n]);

				vn_obs_EP[n] = TMath::Cos((n+1)*(phiarray[t]-Psi_n_EP[n]));
				hEventPlaneEP[n]->Fill(vn_obs_EP[n]);

				

				//fill histogram of Psi_n[n]-Psi_n_EP[n]

				hPhiPsiQ[n]->Fill(phiarray[t]-Psi_n_EP[n]);

				

				//cout<< Resolution[1] << endl;

				


			}

			Resolution[n] = TMath::Cos((n+1)*(Psi_n[n]-Psi_n_EP[n]));
			hResolution[n]->Fill(Resolution[n]);
			hResolutionDist[n]->Fill(Psi_n[n]-Psi_n_EP[n]);





			for (Int_t i=0; i<Nch; i++){
				for (Int_t j=0; j<Nch;j++){
					if(i==j) continue;
					hDeltaPhi[n]->Fill(phiarray[i]-phiarray[j]);
					vn_phi[n] = TMath::Cos((n+1)*(phiarray[i]-phiarray[j]));
					hTwoParticle[n]->Fill(vn_phi[n]);


					
				}
			}
		}
	}

	for (Int_t n=0; n<=(NH-1); n++)
	{
		hDeltaPhiSum->Add(hDeltaPhi[n]);
	}
	
	for (Int_t n=0; n<=(NH-1); n++)
	{
		MeanArrayTwoParticle[n]=hTwoParticle[n]->GetMean();
		MeanArrayTwoPartError[n]=hTwoParticle[n]->GetMeanError()/((n+1)*MeanArrayTwoParticle[n]);
		MeanArrayEventPlane[n]=hEventPlane[n]->GetMean();
		MeanArrayEvtPlError[n]=hEventPlane[n]->GetMeanError();
		MeanArrayEventPlaneQVec[n]=hEventPlaneEP[n]->GetMean();
		MeanArrayEvtPlErrorQvec[n]=hEventPlaneEP[n]->GetMeanError();
		MeanArrayResolution[n]=hResolution[n]->GetMean();
		MeanArrayResolutionError[n]=hResolution[n]->GetMeanError();



		vn_TwoPart[n]=TMath::Sqrt(TMath::Abs(MeanArrayTwoParticle[n]));
		vn_EvtPl[n]=MeanArrayEventPlane[n];
		vn_EvtPlQvec[n]=MeanArrayEventPlaneQVec[n]/MeanArrayResolution[n];
		vn_obs_ERROR[n]=TMath::Power(((1/MeanArrayResolution[n])*MeanArrayEvtPlErrorQvec[n]),2)+TMath::Power(((MeanArrayEventPlaneQVec[n]/TMath::Power(MeanArrayResolution[n],2))*MeanArrayResolutionError[n]),2);
	}

	fourier->Write();
	output->Write();
	output->Close();



	std::cout << center("harmonic",10)   << " | "
          << center("input",10)     << " | "
          << center("vn{Psi_n}",20) << " | "
          << center("vn_obs",20)    << " | " 
          << center("vn{n}",20)     << " | "
          << center("fit",20)       << " | "
          << center("R",10)         << "\n";

	std::cout << std::string(10*7 + 2*7, '-') << "\n";

	for(Int_t n=0; n<=(NH-1); n++) 
		{
    		std::cout << prd(n+1,0,10)             << " | "
              		<< prd(vn[n],2,8)          << " | "
              		<< prd(vn_EvtPl[n],5,9)     << " +-"<<prd(MeanArrayEvtPlError[n],5,9)    << " | "
              		<< prd(vn_EvtPlQvec[n],5,9) << " +-"<<prd(vn_obs_ERROR[n],5,9)           << " | "
              		<< prd(vn_TwoPart[n],5,9)   << " +-"<<prd(MeanArrayTwoPartError[n],5,9)  << " | "
              		<< prd(/*vn_fit[n]*/0,5,10)       << " | "
              		<< prd(Resolution[n],5,10)   << "\n";
		}

	for (Int_t n=0; n<=(NH-1); n++)//harmonic loop
		{
			cout<< "    input:                     " << vn[n] << endl;
			cout<< "calculted vn with twoparticle: "<< vn_TwoPart[n] << "+-" << MeanArrayTwoPartError[n] << endl;
			cout<< "calculated vn with eventplane: "<< vn_EvtPl[n] << "+-" << MeanArrayEvtPlError[n] << endl;
			cout<< "calculated vn with eventplane using Q-vectors : "<< vn_EvtPlQvec[n] << "+-" << vn_obs_ERROR[n] << endl;
			cout<< "vn observed : "<< MeanArrayEventPlaneQVec[n] << endl;
			cout<< "resolution : "<< MeanArrayResolution[n] << endl;
		}	

}

///////////////////////////////////////////////////////

	/* Convert double to string with specified number of places after the decimal
   and left padding. */
std::string prd(const double x, const int decDigits, const int width) {
    stringstream ss;
    ss << fixed << right;
    ss.fill(' ');        // fill space around displayed #
    ss.width(width);     // set  width around displayed #
    ss.precision(decDigits); // set # places after decimal
    ss << x;
    return ss.str();
}

/*! Center-aligns string within a field of width w. Pads with blank spaces
    to enforce alignment. */
std::string center(const string s, const int w) {
    stringstream ss, spaces;
    int padding = w - s.size();                 // count excess room to pad
    for(int i=0; i<padding/2; ++i)
        spaces << " ";
    ss << spaces.str() << s << spaces.str();    // format with padding
    if(padding>0 && padding%2!=0)               // if odd #, add 1 space
        ss << " ";
    return ss.str();
}