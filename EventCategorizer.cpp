/**
 *  @copyright Copyright 2017 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file EventCategorizer.cpp
 */

#include <iostream> 
#include <JPetWriter/JPetWriter.h> 
#include "EventCategorizer.h"
#include "../LargeBarrelAnalysis/EventCategorizerTools.h"


using namespace std;

EventCategorizer::EventCategorizer(const char * name): JPetUserTask(name) {}

bool EventCategorizer::init() {

  INFO("Event categorization started.");
  INFO("Looking at two hit Events on Layer 1&2 only - creating only control histograms");

  fOutputEvents = new JPetTimeWindow("JPetEvent");

  if (fSaveControlHistos) {

    //Control Spectra

    getStatistics().createHistogram(new TH1F("Hits_All", "Hit Multiplicity",
      11, -0.5, 10.5));
    getStatistics().getHisto1D("Hits_All")->GetXaxis()->SetTitle("Hit Multiplicity");
    getStatistics().getHisto1D("Hits_All")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Hits", "Hit Multiplicity - 4 Hits",
      11, -0.5, 10.5));
    getStatistics().getHisto1D("Hits")->GetXaxis()->SetTitle("Hit Multiplicity - 4 Hits");
    getStatistics().getHisto1D("Hits")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Hits_Z_Pos", "Hit Multiplicity - Z Pos 23 cm",
      11, -0.5, 10.5));
    getStatistics().getHisto1D("Hits_Z_Pos")->GetXaxis()->SetTitle("Hit Multiplicity - Z Pos 23 cm");
    getStatistics().getHisto1D("Hits_Z_Pos")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Hits_Replica", "Hit Multiplicity - ID Replica",
      11, -0.5, 10.5));
    getStatistics().getHisto1D("Hits_Replica")->GetXaxis()->SetTitle("Hit Multiplicity - ID Replica");
    getStatistics().getHisto1D("Hits_Replica")->GetYaxis()->SetTitle("Counts");

   getStatistics().createHistogram(new TH1F("Hits_New_Event", "Hit Multiplicity - New_Event",
      11, -0.5, 10.5));
    getStatistics().getHisto1D("Hits_New_Event")->GetXaxis()->SetTitle("Hit Multiplicity - New_Event");
    getStatistics().getHisto1D("Hits_New_Event")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram(new TH1F("Hits_New_Event_4", "Hit Multiplicity - New_Event - 4 or more",
      11, -0.5, 10.5));
    getStatistics().getHisto1D("Hits_New_Event_4")->GetXaxis()->SetTitle("Hit Multiplicity - New_Event - 4 or More");
    getStatistics().getHisto1D("Hits_New_Event_4")->GetYaxis()->SetTitle("Counts");




    getStatistics().createHistogram(new TH1F("Z_Pos_Before", "Z_Pos_Before",
      101, -50.5, 50.5));
    getStatistics().getHisto1D("Z_Pos_Before")->GetXaxis()->SetTitle("Z Pos Before [cm]");
    getStatistics().getHisto1D("Z_Pos_Before")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Z_Pos_After", "Z_Pos_After",
      101, -50.5, 50.5));
    getStatistics().getHisto1D("Z_Pos_After")->GetXaxis()->SetTitle("Z Pos After [cm]");
    getStatistics().getHisto1D("Z_Pos_After")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram(new TH1F("ScinID", "Scintillator ID Distribution",
      193, -0.5, 192.5));
    getStatistics().getHisto1D("ScinID")->GetXaxis()->SetTitle("Scintillator ID");
    getStatistics().getHisto1D("ScinID")->GetYaxis()->SetTitle("Counts");

 
    getStatistics().createHistogram(new TH1F("ScinID_Replica", "ScinID_Replica",
      11, -0.5, 10.5));
    getStatistics().getHisto1D("ScinID_Replica")->GetXaxis()->SetTitle("ScinID_Replica");
    getStatistics().getHisto1D("ScinID_Replica")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("ScinID_Replica_Cut", "ScinID_Replica_Cut",
      11, -0.5, 10.5));
    getStatistics().getHisto1D("ScinID_Replica_Cut")->GetXaxis()->SetTitle("ScinID_Replica_Cut");
    getStatistics().getHisto1D("ScinID_Replica_Cut")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram(new TH1F("Sum_All_TOT", "Sum_All_TOT",
      401, -0.5, 400.5));
    getStatistics().getHisto1D("Sum_All_TOT")->GetXaxis()->SetTitle("Sum_All_TOT [ns]");
    getStatistics().getHisto1D("Sum_All_TOT")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Sum_All_TOT_30", "Sum_All_TOT_30",
      401, -0.5, 400.5));
    getStatistics().getHisto1D("Sum_All_TOT_30")->GetXaxis()->SetTitle("Sum_All_TOT_30 [ns]");
    getStatistics().getHisto1D("Sum_All_TOT_30")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TOT_Check", "TOT_Check",
      401, -0.5, 400.5));
    getStatistics().getHisto1D("TOT_Check")->GetXaxis()->SetTitle("TOT_Check [ns]");
    getStatistics().getHisto1D("TOT_Check")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram(new TH1F("TOF_Difference_t3t1", "TOF_Difference_t3t1",
      2010, -100.5, 100.5));
    getStatistics().getHisto1D("TOF_Difference_t3t1")->GetXaxis()->SetTitle("TOF_Difference_t3t1 [ns]");
    getStatistics().getHisto1D("TOF_Difference_t3t1")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram(new TH1F("TOF_Difference_t3t1_2ns", "TOF_Difference_t3t1_2ns",
      2010, -100.5, 100.5));
    getStatistics().getHisto1D("TOF_Difference_t3t1_2ns")->GetXaxis()->SetTitle("TOF_Difference_t3t1_2ns [ns]");
    getStatistics().getHisto1D("TOF_Difference_t3t1_2ns")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram(new TH1F("DistancefromSurface", "DistancefromSurface",
      510, -0.5, 50.5));
    getStatistics().getHisto1D("DistancefromSurface")->GetXaxis()->SetTitle("DistancefromSurface [cm]");
    getStatistics().getHisto1D("DistancefromSurface")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("DistancefromSurface_less3", "DistancefromSurface_less3",
      510, -0.5, 50.5));
    getStatistics().getHisto1D("DistancefromSurface_less3")->GetXaxis()->SetTitle("DistancefromSurface_less3 [cm]");
    getStatistics().getHisto1D("DistancefromSurface_less3")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram(new TH2F("Angle3D", "3D Azimuthal Angles (Sum and Difference of the two smallest)", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Angle3D")->GetXaxis()->SetTitle("#Theta_1 + #Theta_0");
    getStatistics().getHisto2D("Angle3D")->GetYaxis()->SetTitle("#Theta_1 - #Theta_0");


    getStatistics().createHistogram(new TH2F("Angle3D_190", "3D Azimuthal Angles (Greater than 190deg)", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Angle3D_190")->GetXaxis()->SetTitle("#Theta_{1} + #Theta_{0}");
    getStatistics().getHisto2D("Angle3D_190")->GetYaxis()->SetTitle("#Theta_{1} - #Theta_{0}");


    getStatistics().createHistogram(new TH2F("Angle3D_210", "3D Azimuthal Angles (Greater than 190deg)", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Angle3D_210")->GetXaxis()->SetTitle("#Theta_{1} + #Theta_{0}");
    getStatistics().getHisto2D("Angle3D_210")->GetYaxis()->SetTitle("#Theta_{1} - #Theta_{0}");

   
    getStatistics().createHistogram(new TH2F("Angle3D_Slope", "3D Azimuthal Angles (Greater than 190deg)", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Angle3D_Slope")->GetXaxis()->SetTitle("#Theta_{1} + #Theta_{0}");
    getStatistics().getHisto2D("Angle3D_Slope")->GetYaxis()->SetTitle("#Theta_{1} - #Theta_{0}");


    getStatistics().createHistogram(new TH2F("Angle3D_Both", "3D Azimuthal Angles (Greater than 190deg)", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Angle3D_Both")->GetXaxis()->SetTitle("#Theta_{1} + #Theta_{0}");
    getStatistics().getHisto2D("Angle3D_Both")->GetYaxis()->SetTitle("#Theta_{1} - #Theta_{0}");



 
    getStatistics().createHistogram(new TH1F("Delta_ij_all_pr1", "Delta_ij_all_pr1",
      40100, -200.5, 200.5));
    getStatistics().getHisto1D("Delta_ij_all_pr1")->GetXaxis()->SetTitle("Delta_ij_all_pr1 [ns]");
    getStatistics().getHisto1D("Delta_ij_all_pr1")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Delta_ij_least_pr1", "Delta_ij_least_pr1",
      40100, -200.5, 200.5));
    getStatistics().getHisto1D("Delta_ij_least_pr1")->GetXaxis()->SetTitle("Delta_ij_least_pr1 [ns]");
    getStatistics().getHisto1D("Delta_ij_least_pr1")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram(new TH1F("Delta_ij_all_pr2", "Delta_ij_all_pr2",
      40100, -200.5, 200.5));
    getStatistics().getHisto1D("Delta_ij_all_pr2")->GetXaxis()->SetTitle("Delta_ij_all_pr2 [ns]");
    getStatistics().getHisto1D("Delta_ij_all_pr2")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Delta_ij_least_pr2", "Delta_ij_least_pr2",
      40100, -200.5, 200.5));
    getStatistics().getHisto1D("Delta_ij_least_pr2")->GetXaxis()->SetTitle("Delta_ij_least_pr2 [ns]");
    getStatistics().getHisto1D("Delta_ij_least_pr2")->GetYaxis()->SetTitle("Counts");




    getStatistics().createHistogram(new TH1F("Delta_ij_all_pr3", "Delta_ij_all_pr3",
      40100, -200.5, 200.5));
    getStatistics().getHisto1D("Delta_ij_all_pr3")->GetXaxis()->SetTitle("Delta_ij_all_pr3 [ns]");
    getStatistics().getHisto1D("Delta_ij_all_pr3")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Delta_ij_least_pr3", "Delta_ij_least_pr3",
      40100, -200.5, 200.5));
    getStatistics().getHisto1D("Delta_ij_least_pr3")->GetXaxis()->SetTitle("Delta_ij_least_pr3 [ns]");
    getStatistics().getHisto1D("Delta_ij_least_pr3")->GetYaxis()->SetTitle("Counts");




    getStatistics().createHistogram(new TH2F("Dalitz_Angle_12_Full", "Dalitz Angle12 vs Angle23", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_12_Full")->GetXaxis()->SetTitle("Angle12 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_12_Full")->GetYaxis()->SetTitle("Angle23 [Degree]");

   getStatistics().createHistogram(new TH2F("Dalitz_Angle_23_Full", "Dalitz Angle23 vs Angle31", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_23_Full")->GetXaxis()->SetTitle("Angle23 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_23_Full")->GetYaxis()->SetTitle("Angle31 [Degree]");

    getStatistics().createHistogram(new TH2F("Dalitz_Angle_31_Full", "Dalitz Angle12 vs Angle23", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_31_Full")->GetXaxis()->SetTitle("Angle31 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_31_Full")->GetYaxis()->SetTitle("Angle12 [Degree]");



    getStatistics().createHistogram(new TH2F("Dalitz_Angle_12_190", "Dalitz Angle12 vs Angle23", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_12_190")->GetXaxis()->SetTitle("Angle12 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_12_190")->GetYaxis()->SetTitle("Angle23 [Degree]");

   getStatistics().createHistogram(new TH2F("Dalitz_Angle_23_190", "Dalitz Angle23 vs Angle31", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_23_190")->GetXaxis()->SetTitle("Angle23 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_23_190")->GetYaxis()->SetTitle("Angle31 [Degree]");

    getStatistics().createHistogram(new TH2F("Dalitz_Angle_31_190", "Dalitz Angle12 vs Angle23", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_31_190")->GetXaxis()->SetTitle("Angle31 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_31_190")->GetYaxis()->SetTitle("Angle12 [Degree]");


    getStatistics().createHistogram(new TH2F("Dalitz_Angle_12_210", "Dalitz Angle12 vs Angle23", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_12_210")->GetXaxis()->SetTitle("Angle12 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_12_210")->GetYaxis()->SetTitle("Angle23 [Degree]");

   getStatistics().createHistogram(new TH2F("Dalitz_Angle_23_210", "Dalitz Angle23 vs Angle31", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_23_210")->GetXaxis()->SetTitle("Angle23 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_23_210")->GetYaxis()->SetTitle("Angle31 [Degree]");

    getStatistics().createHistogram(new TH2F("Dalitz_Angle_31_210", "Dalitz Angle12 vs Angle23", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_31_210")->GetXaxis()->SetTitle("Angle31 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_31_210")->GetYaxis()->SetTitle("Angle12 [Degree]");



    getStatistics().createHistogram(new TH2F("Dalitz_Angle_12_Slope", "Dalitz Angle12 vs Angle23", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_12_Slope")->GetXaxis()->SetTitle("Angle12 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_12_Slope")->GetYaxis()->SetTitle("Angle23 [Degree]");

   getStatistics().createHistogram(new TH2F("Dalitz_Angle_23_Slope", "Dalitz Angle23 vs Angle31", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_23_Slope")->GetXaxis()->SetTitle("Angle23 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_23_Slope")->GetYaxis()->SetTitle("Angle31 [Degree]");

    getStatistics().createHistogram(new TH2F("Dalitz_Angle_31_Slope", "Dalitz Angle12 vs Angle23", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_31_Slope")->GetXaxis()->SetTitle("Angle31 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_31_Slope")->GetYaxis()->SetTitle("Angle12 [Degree]");



    getStatistics().createHistogram(new TH2F("Dalitz_Angle_12", "Dalitz Angle12 vs Angle23", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_12")->GetXaxis()->SetTitle("Angle12 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_12")->GetYaxis()->SetTitle("Angle23 [Degree]");

   getStatistics().createHistogram(new TH2F("Dalitz_Angle_23", "Dalitz Angle23 vs Angle31", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_23")->GetXaxis()->SetTitle("Angle23 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_23")->GetYaxis()->SetTitle("Angle31 [Degree]");

    getStatistics().createHistogram(new TH2F("Dalitz_Angle_31", "Dalitz Angle12 vs Angle23", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Dalitz_Angle_31")->GetXaxis()->SetTitle("Angle31 [Degree]");
    getStatistics().getHisto2D("Dalitz_Angle_31")->GetYaxis()->SetTitle("Angle12 [Degree]");




    getStatistics().createHistogram(new TH1F("Energy1", "Energy1",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy1")->GetXaxis()->SetTitle("Energy1 [keV]");
    getStatistics().getHisto1D("Energy1")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Energy2", "Energy2",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy2")->GetXaxis()->SetTitle("Energy2 [keV]");
    getStatistics().getHisto1D("Energy2")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Energy3", "Energy3",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy3")->GetXaxis()->SetTitle("Energy3 [keV]");
    getStatistics().getHisto1D("Energy3")->GetYaxis()->SetTitle("Counts");




    getStatistics().createHistogram(new TH2F("Dalitz_Energy_12", "Dalitz Energy1 vs Energy2", 521, -0.5, 520.5, 521, -0.5, 520.5));
    getStatistics().getHisto2D("Dalitz_Energy_12")->GetXaxis()->SetTitle("Energy1 [keV]");
    getStatistics().getHisto2D("Dalitz_Energy_12")->GetYaxis()->SetTitle("Energy2 [keV]");

   getStatistics().createHistogram(new TH2F("Dalitz_Energy_23", "Dalitz Energy2 vs Energy3", 521, -0.5, 520.5, 521, -0.5, 520.5));
    getStatistics().getHisto2D("Dalitz_Energy_23")->GetXaxis()->SetTitle("Energy2 [keV]");
    getStatistics().getHisto2D("Dalitz_Energy_23")->GetYaxis()->SetTitle("Energy3 [keV]");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_31", "Dalitz Energy3 vs Energy1", 521, -0.5, 520.5, 521, -0.5, 520.5));
    getStatistics().getHisto2D("Dalitz_Energy_31")->GetXaxis()->SetTitle("Energy3 [keV]");
    getStatistics().getHisto2D("Dalitz_Energy_31")->GetYaxis()->SetTitle("Energy1 [keV]");




 
 //Expectation Value

    getStatistics().createHistogram(new TH1F("ExpecValue1", "ExpecValue1",
      300, -1.5, 1.5));
    getStatistics().getHisto1D("ExpecValue1")->GetXaxis()->SetTitle("ExpecValue1");
    getStatistics().getHisto1D("ExpecValue1")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("ExpecValue2", "ExpecValue2",
      300, -1.5, 1.5));
    getStatistics().getHisto1D("ExpecValue2")->GetXaxis()->SetTitle("ExpecValue2");
    getStatistics().getHisto1D("ExpecValue2")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("ExpecValue3", "ExpecValue3",
      300, -1.5, 1.5));
    getStatistics().getHisto1D("ExpecValue3")->GetXaxis()->SetTitle("ExpecValue3");
    getStatistics().getHisto1D("ExpecValue3")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("ExpecValue", "ExpecValue",
      300, -1.5, 1.5));
    getStatistics().getHisto1D("ExpecValue")->GetXaxis()->SetTitle("ExpecValue");
    getStatistics().getHisto1D("ExpecValue")->GetYaxis()->SetTitle("Counts");







  }

  return true;
}

Bool_t comparison(const pair < double, JPetHit > & a,
  const pair < double, JPetHit > & b) {
  return a.first < b.first;
}

Bool_t comparison3(const pair < double, pair < JPetHit, JPetHit >> & a,
  const pair < double, pair < JPetHit, JPetHit >> & b) {
  return abs(a.first) < abs(b.first);
}

bool EventCategorizer::exec() {

  //Begin of exec function

  if (auto timeWindow = dynamic_cast <
    const JPetTimeWindow *
      const > (fEvent)) {
    uint n = timeWindow->getNumberOfEvents();
    for (uint i = 0; i < n; ++i) {

	//Initializing the assumed center of the geometry globally

	TVector3 Center(0.0, 0.0, 0.0);  //Center of the Geometry

      const auto & event = dynamic_cast <
        const JPetEvent & > (timeWindow->operator[](i));

      getStatistics().getHisto1D("Hits_All")->Fill(event.getHits().size());

   //This analysis requires only 4-Hits in a single event	    




    //Create a general vector of hits

	vector<JPetHit> hits = event.getHits();
	std::vector<JPetHit> New_Event;

    //Create vectors for different types of hits
	
	std::vector < JPetHit > PrimaryHits;
	std::vector < JPetHit > SecondaryHits;







    //Check for the Z-pos  of all hits 
	
        std::vector < int > ZPos_vec;

     for (auto j = hits.begin(); j != hits.end(); ++j) 
	{
		auto& hitz = *j;

	double Z_Pos = hitz.getPosZ();

        getStatistics().getHisto1D("Z_Pos_Before")->Fill(Z_Pos);

	if(fabs(Z_Pos) <= 23)
		{

        getStatistics().getHisto1D("Z_Pos_After")->Fill(Z_Pos);

	 ZPos_vec.push_back( Z_Pos );	
	

		}

	}	








	
	//Only if all hits have Z-Pos less than 23 [cm] enter

	if(ZPos_vec.size() == event.getHits().size())
	{



	getStatistics().getHisto1D("Hits_Z_Pos")->Fill(event.getHits().size()); 
	













	//Check for the duplicate ID's


	std::vector < int > ID_vec;

	for (auto i = hits.begin(); i != hits.end(); ++i) 
	{
		auto& hit1 = *i;
        

	 auto ID = hit1.getScintillator().getID();
	 ID_vec.push_back( ID );
	

        getStatistics().getHisto1D("ScinID")->Fill(ID);


	}

	sort( ID_vec.begin(), ID_vec.end() );
	
	ID_vec.erase(unique(ID_vec.begin(), ID_vec.end()), ID_vec.end());

	getStatistics().getHisto1D("ScinID_Replica")->Fill(ID_vec.size());













	//No duplicate ID's only then enter 


	if(ID_vec.size() == event.getHits().size())
	{

        getStatistics().getHisto1D("ScinID_Replica_Cut")->Fill(ID_vec.size());

	getStatistics().getHisto1D("Hits_Replica")->Fill(event.getHits().size()); 










	//Check all TOT 



	for (auto i = hits.begin(); i != hits.end(); ++i) 
	{
		auto& hit1 = *i;


	double TOT_i = CalcTOT(hit1);
							
	getStatistics().getHisto1D("Sum_All_TOT")->Fill(TOT_i);



	if(TOT_i <= 30.0)

		{


	New_Event.push_back(hit1);
	getStatistics().getHisto1D("Sum_All_TOT_30")->Fill(TOT_i);


		}

	}






	
	getStatistics().getHisto1D("Hits_New_Event")->Fill(New_Event.size()); 







	if(New_Event.size() >= 4)


	{


	getStatistics().getHisto1D("Hits_New_Event_4")->Fill(New_Event.size()); 

	

	for (auto l = New_Event.begin(); l != New_Event.end(); ++l) 
	{
		

	auto& hitl = *l;

	double TOT_l = CalcTOT(hitl);
							
	getStatistics().getHisto1D("TOT_Check")->Fill(TOT_l);


	}



	//TOF correct all hits

	vector <pair< double, JPetHit >> TOF_vec;

	for (auto m = New_Event.begin(); m != New_Event.end(); ++m) 
	{
		
	auto& hitm = *m;

	double TOF_x = CalcTOF(hitm, Center);

	TOF_vec.push_back({TOF_x, hitm});						

	}



	//Order the hits based on TOF time

	std::sort(TOF_vec.begin(), TOF_vec.end(), comparison);

	
	//Segregate to possible primary and secondary 

	PrimaryHits.push_back(TOF_vec.at(0).second);
	PrimaryHits.push_back(TOF_vec.at(1).second);
	PrimaryHits.push_back(TOF_vec.at(2).second);

	for(uint h = 3; h < TOF_vec.size(); h++)	
	{	

	SecondaryHits.push_back(TOF_vec.at(h).second);	


		}


	
	




	getStatistics().getHisto1D("TOF_Difference_t3t1")->Fill(TOF_vec.at(2).first - TOF_vec.at(0).first);


	




	//Cut on the Emission Time Difference  - TOF Corrected Times
	
	if((TOF_vec.at(2).first - TOF_vec.at(0).first) <= 2.0)


	{


        getStatistics().getHisto1D("TOF_Difference_t3t1_2ns")->Fill(TOF_vec.at(2).first - TOF_vec.at(0).first);
	


	//Distance of the Annihilation plane from the center of the geometry

	double DistfromSurface = CalDistofSurface(PrimaryHits[0], PrimaryHits[1], PrimaryHits[2], Center);
		
	getStatistics().getHisto1D("DistancefromSurface")->Fill(DistfromSurface);



	if(DistfromSurface <= 3.0)		
	{
	
	getStatistics().getHisto1D("DistancefromSurface_less3")->Fill(DistfromSurface);



	//Calculate the Angle 3D 


	  vector < pair < double, pair < JPetHit, JPetHit >>> Angle3D;
                    double Angle12 = Calc3DAngle(PrimaryHits[0], PrimaryHits[1], Center);
                    double Angle23 = Calc3DAngle(PrimaryHits[1], PrimaryHits[2], Center);
                    double Angle31 = Calc3DAngle(PrimaryHits[2], PrimaryHits[0], Center);
                    Angle3D.push_back({Angle12,{PrimaryHits[0],PrimaryHits[1]}});
                    Angle3D.push_back({Angle23,{PrimaryHits[1],PrimaryHits[2]}});
                    Angle3D.push_back({Angle31,{PrimaryHits[2],PrimaryHits[0]}});

                    std::sort(Angle3D.begin(), Angle3D.end(), comparison3);

                    getStatistics().getHisto2D("Angle3D")->Fill(Angle3D.at(1).first + Angle3D.at(0).first, Angle3D.at(1).first - Angle3D.at(0).first);


	getStatistics().getHisto2D("Dalitz_Angle_12_Full")->Fill(Angle12, Angle23);

	getStatistics().getHisto2D("Dalitz_Angle_23_Full")->Fill(Angle23, Angle31);

	getStatistics().getHisto2D("Dalitz_Angle_31_Full")->Fill(Angle31, Angle12);



 	//3D Angle Cut - With a Slope
 

	double Slope = ((Angle3D.at(1).first - Angle3D.at(0).first)/((Angle3D.at(1).first + Angle3D.at(0).first) - 190));

	
	if((Angle3D.at(1).first + Angle3D.at(0).first) >= 190)

	{

	getStatistics().getHisto2D("Angle3D_190")->Fill(Angle3D.at(1).first + Angle3D.at(0).first, Angle3D.at(1).first - Angle3D.at(0).first);


	getStatistics().getHisto2D("Dalitz_Angle_12_190")->Fill(Angle12, Angle23);

	getStatistics().getHisto2D("Dalitz_Angle_23_190")->Fill(Angle23, Angle31);

	getStatistics().getHisto2D("Dalitz_Angle_31_190")->Fill(Angle31, Angle12);

	}



	if((Angle3D.at(1).first + Angle3D.at(0).first) >= 210)

	{

	getStatistics().getHisto2D("Angle3D_210")->Fill(Angle3D.at(1).first + Angle3D.at(0).first, Angle3D.at(1).first - Angle3D.at(0).first);


	getStatistics().getHisto2D("Dalitz_Angle_12_210")->Fill(Angle12, Angle23);

	getStatistics().getHisto2D("Dalitz_Angle_23_210")->Fill(Angle23, Angle31);

	getStatistics().getHisto2D("Dalitz_Angle_31_210")->Fill(Angle31, Angle12);

	}


	

                         
	if ( Slope <= 10 && Slope > 0 ) {


	getStatistics().getHisto2D("Angle3D_Slope")->Fill(Angle3D.at(1).first + Angle3D.at(0).first, Angle3D.at(1).first - Angle3D.at(0).first);
 	
	getStatistics().getHisto2D("Dalitz_Angle_12_Slope")->Fill(Angle12, Angle23);

	getStatistics().getHisto2D("Dalitz_Angle_23_Slope")->Fill(Angle23, Angle31);

	getStatistics().getHisto2D("Dalitz_Angle_31_Slope")->Fill(Angle31, Angle12);


	}




	if((Angle3D.at(1).first + Angle3D.at(0).first) >= 200 &&  (Angle3D.at(1).first - Angle3D.at(0).first) <= 100 )
	{

	//Dalitz Angle Plot


	getStatistics().getHisto2D("Angle3D_Both")->Fill(Angle3D.at(1).first + Angle3D.at(0).first, Angle3D.at(1).first - Angle3D.at(0).first);

	getStatistics().getHisto2D("Dalitz_Angle_12")->Fill(Angle12, Angle23);

	getStatistics().getHisto2D("Dalitz_Angle_23")->Fill(Angle23, Angle31);

	getStatistics().getHisto2D("Dalitz_Angle_31")->Fill(Angle31, Angle12);








	//Map the Scatter Hits Possibility
	
	std::vector < pair < double, pair < JPetHit, JPetHit >>> Scat_vec_1;
	std::vector < pair < double, pair < JPetHit, JPetHit >>> Scat_vec_2;
	std::vector < pair < double, pair < JPetHit, JPetHit >>> Scat_vec_3;

	std::vector < pair < double, pair < JPetHit, JPetHit >>> Final_Hits;


	
		//Primary Hit_1


		for (uint s = 0; s < SecondaryHits.size(); s++) 
		{
	

			if(PrimaryHits[0].getTime()<SecondaryHits[s].getTime())


 		//Perform Scatter Check only if S_t > P_t

			{
	
	

		double Scatij_pr1 = CalScatterTest(PrimaryHits[0], SecondaryHits[s]);
		
		getStatistics().getHisto1D("Delta_ij_all_pr1")->Fill(Scatij_pr1);


	
		Scat_vec_1.push_back({Scatij_pr1, {PrimaryHits[0], SecondaryHits[s]}});	
		
					
					}




			}
	
        	

		//Least Scatter Test Values of Pr1




		std::sort(Scat_vec_1.begin(), Scat_vec_1.end(), comparison3); //Sort Scatij

		getStatistics().getHisto1D("Delta_ij_least_pr1")->Fill(Scat_vec_1.at(0).first);



		Final_Hits.push_back({Scat_vec_1.at(0).first, {Scat_vec_1.at(0).second.first, Scat_vec_1.at(0).second.second}});	





		//Primary Hit_2


		for (uint s = 0; s < SecondaryHits.size(); s++) 
		{
	

			if(PrimaryHits[1].getTime()<SecondaryHits[s].getTime())


 		//Perform Scatter Check only if S_t > P_t

			{
	
	

		double Scatij_pr2 = CalScatterTest(PrimaryHits[1], SecondaryHits[s]);
		
		getStatistics().getHisto1D("Delta_ij_all_pr2")->Fill(Scatij_pr2);


	
		Scat_vec_2.push_back({Scatij_pr2, {PrimaryHits[1], SecondaryHits[s]}});	
		
				}




			}
	
        	

		//Least Scatter Test Values of Pr2




		std::sort(Scat_vec_2.begin(), Scat_vec_2.end(), comparison3); //Sort Scatij

		getStatistics().getHisto1D("Delta_ij_least_pr2")->Fill(Scat_vec_2.at(0).first);



		Final_Hits.push_back({Scat_vec_2.at(0).first, {Scat_vec_2.at(0).second.first, Scat_vec_2.at(0).second.second}});



		
		//Primary Hit_3


		for (uint s = 0; s < SecondaryHits.size(); s++) 
		{
	

			if(PrimaryHits[2].getTime()<SecondaryHits[s].getTime())


 		//Perform Scatter Check only if S_t > P_t

			{
	
	

		double Scatij_pr3 = CalScatterTest(PrimaryHits[2], SecondaryHits[s]);
		
		getStatistics().getHisto1D("Delta_ij_all_pr3")->Fill(Scatij_pr3);


	
		Scat_vec_3.push_back({Scatij_pr3, {PrimaryHits[2], SecondaryHits[s]}});	
		
				}




			}
	
        	

		//Least Scatter Test Values of Pr3




		std::sort(Scat_vec_3.begin(), Scat_vec_3.end(), comparison3); //Sort Scatij

		getStatistics().getHisto1D("Delta_ij_least_pr3")->Fill(Scat_vec_3.at(0).first);

		

		Final_Hits.push_back({Scat_vec_3.at(0).first, {Scat_vec_3.at(0).second.first, Scat_vec_3.at(0).second.second}});





		
	
		    double AngleDiff = (360 - (Angle12 + Angle23));
                
		    //Energy Calculations

                    double Energy1 = CalcEnergy1(Angle12, Angle23, AngleDiff);
                    double Energy2 = CalcEnergy2(Angle12, Angle23, AngleDiff);
                    double Energy3 = CalcEnergy3(Angle12, Angle23, AngleDiff);

       		    getStatistics().getHisto1D("Energy1")->Fill(Energy1);
                    getStatistics().getHisto1D("Energy2")->Fill(Energy2);
                    getStatistics().getHisto1D("Energy3")->Fill(Energy3);

	            getStatistics().getHisto2D("Dalitz_Energy_12")->Fill(Energy1, Energy2);
                    getStatistics().getHisto2D("Dalitz_Energy_23")->Fill(Energy2, Energy3);
                    getStatistics().getHisto2D("Dalitz_Energy_31")->Fill(Energy3, Energy1);








                    //Sorting of Calculated Energies   

		    vector <pair<double,JPetHit>> Energy_Vector;
                    Energy_Vector.push_back({Energy1, PrimaryHits[0]});
                    Energy_Vector.push_back({Energy2, PrimaryHits[1]});
                    Energy_Vector.push_back({Energy3, PrimaryHits[2]});
                    std::sort(Energy_Vector.begin(), Energy_Vector.end(), comparison);



	for(uint o = 0; o < 3; o++)
	{



       	 if (Final_Hits.at(o).second.first.getScintillator().getID() == Energy_Vector.at(2).second.getScintillator().getID()) {

                              double ExpecValue1 = CalExpecValue(Final_Hits.at(o).second.first, Final_Hits.at(o).second.second, Energy_Vector.at(1).second, Center);

            getStatistics().getHisto1D("ExpecValue1")->Fill(ExpecValue1);
            getStatistics().getHisto1D("ExpecValue")->Fill(ExpecValue1);

                            } else if (Final_Hits.at(o).second.first.getScintillator().getID() == Energy_Vector.at(1).second.getScintillator().getID()) {

                              double ExpecValue2 = CalExpecValue(Final_Hits.at(o).second.first, Final_Hits.at(o).second.second, Energy_Vector.at(2).second, Center);
            
	    getStatistics().getHisto1D("ExpecValue2")->Fill(ExpecValue2);
            getStatistics().getHisto1D("ExpecValue")->Fill(ExpecValue2);
                            
			   } else if (Final_Hits.at(o).second.first.getScintillator().getID() == Energy_Vector.at(0).second.getScintillator().getID()) {

                              double ExpecValue3 = CalExpecValue(Final_Hits.at(o).second.first, Final_Hits.at(o).second.second,Energy_Vector.at(2).second, Center);
                             
 	    getStatistics().getHisto1D("ExpecValue3")->Fill(ExpecValue3);
 	    getStatistics().getHisto1D("ExpecValue")->Fill(ExpecValue3);

	
				
							}





		}






	


											}
										

										}

									}

								}

							}
				
						}

					}

				}

			

		





else {
  return false;
}
return true;
}

bool EventCategorizer::terminate() {

  INFO("More than one hit Events done. Writing conrtrol histograms.");
  return true;
}

void EventCategorizer::saveEvents(const vector < JPetEvent > & events) {
  for (const auto & event: events) {
    fOutputEvents->add < JPetEvent > (event);
  }
}
