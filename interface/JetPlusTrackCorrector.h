#ifndef JetPlusTrackCorrector_h
#define JetPlusTrackCorrector_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "JetMETCorrections/Algorithms/interface/SingleParticleJetResponse.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/JetReco/interface/JetTracksAssociation.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

//JW: electrons
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
//JW: needed for elecID
#include "AnalysisDataFormats/Egamma/interface/ElectronID.h"
#include "DataFormats/Common/interface/ValueMap.h"

class SingleParticleJetResponse;

namespace edm {
  class Event;
  class EventSetup;
  class ParameterSet;
}

///
/// jet energy corrections from MCjet calibration
///

class JetPlusTrackCorrector : public JetCorrector
{
public:  

  typedef reco::Particle::LorentzVector LorentzVector;

  JetPlusTrackCorrector(const edm::ParameterSet& fParameters);

  virtual ~JetPlusTrackCorrector();
  
  /// apply correction using Jet information only
  virtual double  correction (const LorentzVector& fJet) const;
  /// apply correction using Jet information only
  virtual double correction (const reco::Jet& fJet) const;
  
  virtual double correction (const reco::Jet& fJet, const edm::Event& fEvent, const edm::EventSetup& fSetup) const;

  void setParameters( std::string fDataFile1, std::string fDataFile2, std::string fDataFile3);
 
  virtual reco::TrackRefVector jtC_rebuild(
                                        const reco::JetTracksAssociation::Container&, const reco::Jet& fJet, reco::TrackRefVector& Excl) const;

  virtual reco::TrackRefVector jtC_exclude(
                                        const reco::JetTracksAssociation::Container&, const reco::Jet& fJet, reco::TrackRefVector& Excl) const;

 
  /// if correction needs event information
  virtual bool eventRequired () const {return true;}
   
private:
  edm::InputTag m_JetTracksAtVertex;
  edm::InputTag m_JetTracksAtCalo;
  edm::InputTag m_muonsSrc;
  //JW:
  edm::InputTag m_recoGsfelectrons; 
  edm::InputTag m_eIDValueMap_;
  // Split/Merge
  int mSplitMerge;
  // responce algo (will be absolete)
  int theResponseAlgo;
  // add or not out of cone tracks (default: true)
  bool theAddOutOfConeTracks;
  // tracker efficiency map
  std::string theNonEfficiencyFile;
  // corrections to responce of lost tracks
  std::string theNonEfficiencyFileResp;
  // single pion responce map for found fracks
  std::string theResponseFile;
  // use tracks of high quality
  bool theUseQuality;
  // track quality
  std::string theTrackQuality;

  reco::TrackBase::TrackQuality trackQuality_;

  SingleParticleJetResponse * theSingle;

/// Tracking efficiency
  int netabin1,nptbin1;
  std::vector<double> etabin1;
  std::vector<double> ptbin1;
  std::vector<double> trkeff;

/// Leakage corrections
  int netabin2,nptbin2;
  std::vector<double> etabin2;
  std::vector<double> ptbin2;
  std::vector<double> eleakage;
  //  std::vector<double> trkeff_resp;

/// single particle responce
  int netabin3,nptbin3;
  std::vector<double> etabin3;
  std::vector<double> ptbin3;
  std::vector<double> response;

};

#endif
