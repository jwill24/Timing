// include files
 
#include <iostream>
#include <fstream>
#include <map>
 
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/global/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

using namespace std;



class EventNumFilter : public edm::global::EDFilter<> {
 
public:

  explicit EventNumFilter(const edm::ParameterSet & iConfig);
  ~EventNumFilter() override {}

private:

  // main filter function 
  bool filter(edm::StreamID, edm::Event & iEvent, const edm::EventSetup & iSetup) const override; 
};


EventNumFilter::EventNumFilter(const edm::ParameterSet & iConfig) //:
{
  produces<bool>();
}

bool EventNumFilter::filter(edm::StreamID, edm::Event & iEvent, const edm::EventSetup & iSetup) const {

  bool pass = true;

  /*
  ifstream eventsFile("events2018.txt");
  string goodRun;
  long goodLumiEvent;
  multimap<string,long > eventMap;

  while (getline(eventsFile, goodRun)) {
    eventMap.insert( make_pair(goodRun,goodLumiEvent) );
  } 
  

  // load required values
  int run   = iEvent.id().run();
  string runS = to_string(run);
  long lumi  = iEvent.luminosityBlock();
  long event = iEvent.id().event();
  int event_len = to_string(event).length();
  long lumiEvent = lumi*pow(10,event_len)+event;


  std::pair <std::multimap<string,long>::iterator, std::multimap<string,long>::iterator> ret;
  ret = eventMap.equal_range( runS );
  for (std::multimap<string,long>::iterator it=ret.first; it!=ret.second; ++it) {
    if ( it->second == lumiEvent ) {
      pass = false;
      throw cms::Exception("BadEventNum");
    }
  }
  
  */

  throw cms::Exception("BadEventNum");

  return pass;
  
}


DEFINE_FWK_MODULE(EventNumFilter);


  
