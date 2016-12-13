#ifndef StPicoEventMixer_hh
#define StPicoEventMixer_hh

/* **************************************************
 *  
 * Class stores event buffer used in event mixing. Mixing
 * is done automatically once buffer reaches defined maximum.
 * Template provided used for D0 reconstruction, user should personalize 
 * mixEvent() method to cosntruct desired background.
 *
 * **************************************************
 * 
 * Initial Authors:
 *       ** Michael Lomnitz (mrlomnitz@lbl.gov)
 *          Mustafa Mustafa   (mmustafa@lbl.gov)
 *
 *  ** Code maintainer 
 *
 * **************************************************
 */

#include <vector>

#include "StarClassLibrary/StThreeVectorF.hh"
#include "StMixerCuts.h"

class TTree;
class TH2F;
class StPicoEvent;
class StPicoTrack;
class StPicoDst;
class StMixerTrack;
class StMixerEvent;
class StMixerTriplet;
class StMixerHists;

class StPicoEventMixer {
 public: 
  enum bitNumber { kPionTPCbit, kPionTOFbit, kKaonTPCbit, kKaonTOFbit, kProtonTPCbit, kProtonTOFbit};

  StPicoEventMixer(char* category);
  ~StPicoEventMixer();
  bool addPicoEvent(StPicoDst const* picoDst);
  void setEventBuffer(int buffer);
  void mixEvents();
  bool isGoodEvent(StPicoDst const * const picoDst);
  bool isGoodTrigger(StPicoEvent const * const) const;
  bool isGoodTrack(StPicoTrack const * const trk);
  bool isCloseTrack(StPicoTrack const& trk, StThreeVectorF const& pVtx);
  bool isTpcPion(StPicoTrack const * const);
  bool isTpcKaon(StPicoTrack const * const);
  bool isTpcProton(StPicoTrack const * const);
  bool isTPCHadron(StPicoTrack const * const, int pidFlag);
  bool isGoodTriplet(StMixerTriplet const& triplet);
  int getLcPtIndex(StMixerTriplet const& pair) const;
  void finish();
 private:
  bool isMixerPion(StMixerTrack const&);
  bool isMixerKaon(StMixerTrack const&);
  bool isMixerProton(StMixerTrack const&);
  
  std::vector <StMixerEvent*> mEvents; 
  StMixerHists* mHists;
  StPicoHFCuts *mHFCuts;
  unsigned short int mEventsBuffer; 
  unsigned short int filledBuffer;
  float dca1, dca2, dcaDaughters, theta_hs, decayL_hs;
  float pt_hs, mass_hs, eta_hs, phi_hs;
};

inline void StPicoEventMixer::setEventBuffer(int buffer){ mEventsBuffer = buffer;}
			    
    
#endif
