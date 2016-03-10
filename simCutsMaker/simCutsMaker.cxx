#define simCutsMaker_cxx
#include "simCutsMaker.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <cmath>
#include "TH1D.h"
#include "TFile.h"
#include "TString.h"
#include <iostream>

#include "cutsConsts.h"
using namespace tenthIter;

using namespace std;

// class simCutsMaker;

// --------------------------------------------------
void simCutsMaker::Loop(Long64_t first, Long64_t last)
{
//   In a ROOT session, you can do:
//      Root > .L simCutsMaker.C
//      Root > simCutsMaker t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   nentries = nentries < last ? nentries : last;

   for (Long64_t jentry=first-1; jentry<nentries;jentry++) 
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;

      if (jentry % 100000 == 0)
	cout << "Running on entry # " << jentry << " ______________"<< endl;

      fChain->GetEntry(jentry);
      //
      // mass cut
      if (m < 2.266 || m > 2.306)
	continue;

      calculateIndices();

      for (int ii = 0; ii < indices[0]; ++ii) // dLength
      {
	// cout << "dLength" << endl;
	for (int jj = 0; jj < indices[1]; ++jj) // daughters DCA
	{
	  // cout << "daughters DCA" << endl;
	  for (int kk = 0; kk < indices[2]; ++kk) // daghters vertex dist
	  {
	    // cout << "daughters DCA and daughters vertex dist" << endl;
	    for (int ll = 0; ll < indices[3]; ++ll) // p pT
	    {
	      for (int mm = 0; mm < indices[4]; ++mm) // K pT
	      {
		for (int nn = 0; nn < indices[5]; ++nn) // pi pT
		{
		  // cout << "pT cuts" << endl;
		  for (int oo = 0; oo < indices[6]; ++oo) // cos(theta)
		  {
		    // cout << "Event selected" << endl;
		    H[indexInArray(ii,jj,kk,ll,mm,nn,oo)]->Fill(pt);
		  }
		}
	      }
	    }
	  }
	}
      }
   } // for (Long64_t jentry=first-1; jentry<nentries;jentry++) 

   write();
}
// --------------------------------------------------

void simCutsMaker::bookHistograms()
{
  //H = new TH1D******[5];
  for (int ii = 0; ii < 5; ++ii) // dLength
  {
    //H[ii] = new TH1D*****[5];
    for (int jj = 0; jj < 5; ++jj) // dcaDaughters
    {
      //H[ii][jj] = new TH1D****[5];
      for (int kk = 0; kk < 5; ++kk) // maxVDist
      {
	//H[ii][jj][kk] = new TH1D***[5];
	for (int ll = 0; ll < 5; ++ll) // pPt
	{
	  //H[ii][jj][kk][ll] = new TH1D**[5];
	  for (int mm = 0; mm < 5; ++mm) // piPt
	  {
	    //H[ii][jj][kk][ll][mm] = new TH1D*[5];
	    for (int nn  = 0; nn < 5; ++nn) // kPt
	    {
	      for (int oo = 0; oo < 5; ++oo) // cos(theta)
	      {
		int index [7] = {ii, jj, kk, ll, mm, nn, oo};
		setCutsFromIndex(index);
		TH1D *hist;
		hist = new TH1D(Form("H%d%d%d%d%d%d%d", ii, jj, kk, ll, mm, nn, oo),
				     Form("p_{T} spectrum {dLength>%1.3fcm,dcaDaughters<%1.3fcm,maxVdist<%1.3f,pPt<%1.1fGeV,piPt<%1.1fGeV,kPt<%1.1fGeV,cos(#theta)>%1.4f}", 
					  cuts[0],cuts[1],cuts[2],cuts[3],cuts[4],cuts[5], cuts[6]),
				     20,0.,13.);
		hist -> Sumw2();
		hist -> GetXaxis() -> SetTitle("p_{T} [GeV]");
		hist -> GetYaxis() -> SetTitle("N");
		// cout << "indexInArray(" << ii << "," << jj << "," << kk << "," <<  ll<< "," <<  mm << "," << nn << ") = " << indexInArray(ii,jj,kk,ll,mm,nn) << endl;
		H[indexInArray(ii,jj,kk,ll,mm,nn,oo)] = hist;
	      } // cos(theta)
	    } // kPt
	  } // piPt
	} // pPt
      } // maxVDist
    } // dcaDaughters
  } // dLength
} // void simCutsMaker::bookHistograms()
// --------------------------------------------------

void simCutsMaker::setCutsFromIndex(int const *index)
{

  // ***********************************************
  float MdLength = DLstart + DLinc* index[0];
  float MdcaDaughters = dcaDaughtersStart - dcaDaughtersInc*index[1];
  float MmaxVdist = maxVdistStart - maxVdistInc*index[2];
  float MpPt = pPtStart + pPtInc*index[3];
  float MpiPt = piPtStart + piPtInc*index[4];
  float MkPt = KPtStart + KPtInc*index[5];
  float McosTheta = cosThetaStart + cosThetaInc*index[6];
  // ***********************************************

  unsigned int iArr = 0;
  cuts[iArr++]=MdLength;
  cuts[iArr++]=MdcaDaughters;
  cuts[iArr++]=MmaxVdist;
  cuts[iArr++]=MpPt;
  cuts[iArr++]=MpiPt;
  cuts[iArr++]=MkPt;
  cuts[iArr++]=McosTheta;
}
// --------------------------------------------------

// calculate the first rejected inndex in array
void simCutsMaker::calculateIndices()
{
  unsigned int iArr = 0;
  // dLength cut
  indices[iArr++] = int(ceil( (dLength - DLstart)/DLinc ));
  // daughters DCA cut
  // calculate maximum of daughters DCA
  float maxDcaDaughters = dcaDaugthers12 > dcaDaugthers23 ? dcaDaugthers12 : dcaDaugthers23;
  maxDcaDaughters = maxDcaDaughters > dcaDaugthers31 ? maxDcaDaughters : dcaDaugthers31;
  indices[iArr++] = int(ceil( (-maxDcaDaughters + dcaDaughtersStart )/dcaDaughtersInc ));
  // maxVDist cut
  indices[iArr++] = int(ceil( (-maxVertexDist + maxVdistStart )/maxVdistInc ));
  // daughters pT
  indices[iArr++] = int(ceil( (p2pt - pPtStart )/pPtInc )); // proton
  indices[iArr++] = int(ceil( (p3pt - piPtStart)/piPtInc )); // pion
  indices[iArr++] = int(ceil( (p1pt - KPtStart)/KPtInc )); // kaon
  // cos(theta)
  indices[iArr++] = int(ceil( (cosPntAngle - cosThetaStart)/cosThetaInc ));

  for(int i = 0; i < 7; ++i)
  {
    if (indices[i] > 5)
      indices[i] = 5;
  }
}
// --------------------------------------------------

void simCutsMaker::write()
{
  outf->cd();
  for(int ii = 0; ii < 5; ++ii)
  {
    for(int jj = 0; jj < 5; ++jj)
    {
      for(int kk = 0; kk < 5; ++kk)
      {
	for(int ll = 0; ll < 5; ++ll)
	{
	  for (int mm = 0; mm < 5; ++mm)
	  {
	    for (int nn = 0; nn < 5; ++nn)
	    {
	      for (int oo = 0; oo < 5; ++oo)
	      {
		H[indexInArray(ii,jj,kk,ll,mm,nn,oo)]->Write();
	      }
	    }
	  }
	}
      }
    }
  }
} // write()
// --------------------------------------------------

// workarround fo 7 dimensional array in root
// calculates index in 1D array
inline int simCutsMaker::indexInArray(int ii, int jj, int kk, int ll, int mm, int nn, int oo)
{
  return oo+5*nn+25*mm+125*ll+625*kk+3125*jj+15625*ii;
}

