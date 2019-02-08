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

using namespace std;

EventCategorizer::EventCategorizer(const char * name): JPetUserTask(name) {}

bool EventCategorizer::init() {

  INFO("Event categorization started.");
  INFO("Looking at two hit Events on Layer 1&2 only - creating only control histograms");

  fOutputEvents = new JPetTimeWindow("JPetEvent");

  if (fSaveControlHistos) {

    //Control Spectra

    getStatistics().createHistogram(new TH1F("Hits_All", "Event Multiplicity",
      11, -0.5, 10.5));
    getStatistics().getHisto1D("Hits_All")->GetXaxis()->SetTitle("Event Multiplicity");
    getStatistics().getHisto1D("Hits_All")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Hits", "Event Multiplicity - 4 Hits",
      11, -0.5, 10.5));
    getStatistics().getHisto1D("Hits")->GetXaxis()->SetTitle("Event Multiplicity - 4 Hits");
    getStatistics().getHisto1D("Hits")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Z_Pos_Before", "Z_Pos_Before",
      101, -50.5, 50.5));
    getStatistics().getHisto1D("Z_Pos_Before")->GetXaxis()->SetTitle("Z Pos Before [cm]");
    getStatistics().getHisto1D("Z_Pos_Before")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TimeDiff_Resolution", "TimeDiff_Resolution",
      210, -10.5, 10.5));
    getStatistics().getHisto1D("TimeDiff_Resolution")->GetXaxis()->SetTitle("Time Difference BA [ns]");
    getStatistics().getHisto1D("TimeDiff_Resolution")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Z_Pos_After", "Z_Pos_After",
      101, -50.5, 50.5));
    getStatistics().getHisto1D("Z_Pos_After")->GetXaxis()->SetTitle("Z Pos After [cm]");
    getStatistics().getHisto1D("Z_Pos_After")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Hits_Z_Pos", "Hits_Z_Pos",
      11, -0.5, 10.5));
    getStatistics().getHisto1D("Hits_Z_Pos")->GetXaxis()->SetTitle("Hits_Z_Pos");
    getStatistics().getHisto1D("Hits_Z_Pos")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("ScinID_Replica", "ScinID_Replica",
      11, -0.5, 10.5));
    getStatistics().getHisto1D("ScinID_Replica")->GetXaxis()->SetTitle("ScinID_Replica");
    getStatistics().getHisto1D("ScinID_Replica")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("ScinID_Replica_Cut", "ScinID_Replica_Cut",
      11, -0.5, 10.5));
    getStatistics().getHisto1D("ScinID_Replica_Cut")->GetXaxis()->SetTitle("ScinID_Replica_Cut");
    getStatistics().getHisto1D("ScinID_Replica_Cut")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Hits_ScinID", "Hits_ScinID",
      11, -0.5, 10.5));
    getStatistics().getHisto1D("Hits_ScinID")->GetXaxis()->SetTitle("Hits_Z_Pos");
    getStatistics().getHisto1D("Hits_ScinID")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Delta_ij_least", "Delta_ij_least",
      40100, -200.5, 200.5));
    getStatistics().getHisto1D("Delta_ij_least")->GetXaxis()->SetTitle("Delta_ij_least [ns]");
    getStatistics().getHisto1D("Delta_ij_least")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Delta_ij_all_notleast", "Delta_ij_all_notleast",
      40100, -200.5, 200.5));
    getStatistics().getHisto1D("Delta_ij_all_notleast")->GetXaxis()->SetTitle("Delta_ij_all_notleast [ns]");
    getStatistics().getHisto1D("Delta_ij_all_notleast")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TOT_scat_check", "TOT_scat_check",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_scat_check")->GetXaxis()->SetTitle("TOT_scat_check [ns]");
    getStatistics().getHisto1D("TOT_scat_check")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Delta_ij_least_Cut_0.5ns", "Delta_ij_least_Cut_0.5ns",
      40100, -200.5, 200.5));
    getStatistics().getHisto1D("Delta_ij_least_Cut_0.5ns")->GetXaxis()->SetTitle("Delta_ij_least_Cut_0.5ns [ns]");
    getStatistics().getHisto1D("Delta_ij_least_Cut_0.5ns")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TOT_scat_check_Cut_0.5ns", "TOT_scat_check_Cut_0.5ns",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_scat_check_Cut_0.5ns")->GetXaxis()->SetTitle("TOT_scat_check_Cut_0.5ns [ns]");
    getStatistics().getHisto1D("TOT_scat_check_Cut_0.5ns")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH2F("TOT_scat_check_vs_Delta_ij_least", "TOT_scat_check_vs_Delta_ij_least",
      401, -200.5, 200.5,
      101, -0.5, 100.5));
    getStatistics().getHisto2D("TOT_scat_check_vs_Delta_ij_least")->GetXaxis()->SetTitle("Delta_ij [ns]");
    getStatistics().getHisto2D("TOT_scat_check_vs_Delta_ij_least")->GetYaxis()->SetTitle("TOT_scat_check [ns]");

    //TOT
    getStatistics().createHistogram(new TH1F("TOT", "TOT",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT")->GetYaxis()->SetTitle("Counts");

  getStatistics().createHistogram(new TH1F("TOT_AngleCheck", "TOT_AngleCheck",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_AngleCheck")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_AngleCheck")->GetYaxis()->SetTitle("Counts");

   getStatistics().createHistogram(new TH1F("TOT_AngleCheck_TOT", "TOT_AngleCheck_TOT",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_AngleCheck_TOT")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_AngleCheck_TOT")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram(new TH1F("TOT_Primary", "TOT_Primary",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_Primary")->GetXaxis()->SetTitle("TOT_Primary [ns]");
    getStatistics().getHisto1D("TOT_Primary")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TOT_pr1", "TOT_pr1",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_pr1")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_pr1")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TOT_pr2", "TOT_pr2",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_pr2")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_pr2")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TOT_pr3", "TOT_pr3",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_pr3")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_pr3")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TOT_ScatHit", "TOT_ScatHit",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_ScatHit")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_ScatHit")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH2F("ScinID_vs_TOT", "ScinID_vs_TOT",
      101, -0.5, 100.5,
      193, -0.5, 192.5));
    getStatistics().getHisto2D("ScinID_vs_TOT")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto2D("ScinID_vs_TOT")->GetYaxis()->SetTitle("Scintillator ID");

    //Time Difference

    getStatistics().createHistogram(new TH2F("DeltaT_vs_ScinID_big", "Time difference B-A vs scintillator ID, big range",
      193, -0.5, 192.5,
      210, -10.5, 10.5));
    getStatistics().getHisto2D("DeltaT_vs_ScinID_big")->GetXaxis()->SetTitle("Scintillator ID");
    getStatistics().getHisto2D("DeltaT_vs_ScinID_big")->GetYaxis()->SetTitle("Time difference BA [ns]");

    getStatistics().createHistogram(new TH1F("ScinID", "Scintillator ID Distribution",
      193, -0.5, 192.5));
    getStatistics().getHisto1D("ScinID")->GetXaxis()->SetTitle("Scintillator ID");
    getStatistics().getHisto1D("ScinID")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TimeDiff", "Time Difference Distribution",
      210, -10.5, 10.5));
    getStatistics().getHisto1D("TimeDiff")->GetXaxis()->SetTitle("Time Difference BA [ns]");
    getStatistics().getHisto1D("TimeDiff")->GetYaxis()->SetTitle("Counts");

 

    
    //Angle 3D

    getStatistics().createHistogram(new TH2F("Angle3D", "3D Azimuthal Angles (Sum and Difference of the two smallest)", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Angle3D")->GetXaxis()->SetTitle("#Theta_1 + #Theta_0");
    getStatistics().getHisto2D("Angle3D")->GetYaxis()->SetTitle("#Theta_1 - #Theta_0");

    getStatistics().createHistogram(new TH2F("Angle3D_TOT", "3D_TOT Azimuthal Angles (Sum and Difference of the two smallest)", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Angle3D_TOT")->GetXaxis()->SetTitle("#Theta_1 + #Theta_0");
    getStatistics().getHisto2D("Angle3D_TOT")->GetYaxis()->SetTitle("#Theta_1 - #Theta_0");

    getStatistics().createHistogram(new TH2F("Angle3D_Dist", "3D_Dist Azimuthal Angles (Sum and Difference of the two smallest)", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Angle3D_Dist")->GetXaxis()->SetTitle("#Theta_1 + #Theta_0");
    getStatistics().getHisto2D("Angle3D_Dist")->GetYaxis()->SetTitle("#Theta_1 - #Theta_0");

    getStatistics().createHistogram(new TH2F("Angle3D_ET", "3D_ET Azimuthal Angles (Sum and Difference of the two smallest)", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Angle3D_ET")->GetXaxis()->SetTitle("#Theta_1 + #Theta_0");
    getStatistics().getHisto2D("Angle3D_ET")->GetYaxis()->SetTitle("#Theta_1 - #Theta_0");

    //Dalitz Plot - Energy and Angle
    
    getStatistics().createHistogram(new TH2F("AngleDistribution_01", "AngleDistribution_01", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("AngleDistribution_01")->GetXaxis()->SetTitle("Angle12");
    getStatistics().getHisto2D("AngleDistribution_01")->GetYaxis()->SetTitle("Angle23");


    getStatistics().createHistogram(new TH2F("AngleDistribution_01_Check", "AngleDistribution_01_Check", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("AngleDistribution_01_Check")->GetXaxis()->SetTitle("Angle12");
    getStatistics().getHisto2D("AngleDistribution_01_Check")->GetYaxis()->SetTitle("Angle23");


    getStatistics().createHistogram(new TH2F("AngleDistribution_01_Check_TOT", "AngleDistribution_01_Check_TOT", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("AngleDistribution_01_Check_TOT")->GetXaxis()->SetTitle("Angle12");
    getStatistics().getHisto2D("AngleDistribution_01_Check_TOT")->GetYaxis()->SetTitle("Angle23");


    getStatistics().createHistogram(new TH2F("AngleDistribution_01_TOT", "AngleDistribution_01_TOT", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("AngleDistribution_01_TOT")->GetXaxis()->SetTitle("Angle12");
    getStatistics().getHisto2D("AngleDistribution_01_TOT")->GetYaxis()->SetTitle("Angle23");


    getStatistics().createHistogram(new TH2F("AngleDistribution_01_Dist", "AngleDistribution_01_Dist", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("AngleDistribution_01_Dist")->GetXaxis()->SetTitle("Angle12");
    getStatistics().getHisto2D("AngleDistribution_01_Dist")->GetYaxis()->SetTitle("Angle23");


    getStatistics().createHistogram(new TH2F("AngleDistribution_01_ET", "AngleDistribution_01_ET", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("AngleDistribution_01_ET")->GetXaxis()->SetTitle("Angle12");
    getStatistics().getHisto2D("AngleDistribution_01_ET")->GetYaxis()->SetTitle("Angle23");

   
    getStatistics().createHistogram(new TH2F("AngleDistribution_01_Angle", "AngleDistribution_01_Angle", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("AngleDistribution_01_Angle")->GetXaxis()->SetTitle("Angle12");
    getStatistics().getHisto2D("AngleDistribution_01_Angle")->GetYaxis()->SetTitle("Angle23");


    getStatistics().createHistogram(new TH2F("AngleDistribution_12", "AngleDistribution_12", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("AngleDistribution_12")->GetXaxis()->SetTitle("Angle23");
    getStatistics().getHisto2D("AngleDistribution_12")->GetYaxis()->SetTitle("Angle31");

    getStatistics().createHistogram(new TH2F("AngleDistribution_20", "AngleDistribution_20", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("AngleDistribution_20")->GetXaxis()->SetTitle("Angle31");
    getStatistics().getHisto2D("AngleDistribution_20")->GetYaxis()->SetTitle("Angle12");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_12", "Dalitz_Energy_12", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_12")->GetXaxis()->SetTitle("Energy1");
    getStatistics().getHisto2D("Dalitz_Energy_12")->GetYaxis()->SetTitle("Energy2");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_23", "Dalitz_Energy_23", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_23")->GetXaxis()->SetTitle("Energy2");
    getStatistics().getHisto2D("Dalitz_Energy_23")->GetYaxis()->SetTitle("Energy3");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_31", "Dalitz_Energy_31", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_31")->GetXaxis()->SetTitle("Energy3");
    getStatistics().getHisto2D("Dalitz_Energy_31")->GetYaxis()->SetTitle("Energy1");

    
    //Seperate Energy Calculations

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

    //Energy Summed Up

    getStatistics().createHistogram(new TH1F("Sum_Energy", "Sum_Energy",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Sum_Energy")->GetXaxis()->SetTitle("Sum_Energy [keV]");
    getStatistics().getHisto1D("Sum_Energy")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Sum_Energy_Diff", "Sum_Energy_Diff",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Sum_Energy_Diff")->GetXaxis()->SetTitle("Sum_Energy_Diff [keV]");
    getStatistics().getHisto1D("Sum_Energy_Diff")->GetYaxis()->SetTitle("Counts");
    
    //Sum of the TOT values of all 4-Hits

    getStatistics().createHistogram(new TH1F("Sum_All_TOT_90_before", "Sum_All_TOT_90_before",
      401, -0.5, 400.5));
    getStatistics().getHisto1D("Sum_All_TOT_90_before")->GetXaxis()->SetTitle("Sum_All_TOT_90_before [ns]");
    getStatistics().getHisto1D("Sum_All_TOT_90_before")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Sum_All_TOT", "Sum_All_TOT",
      401, -0.5, 400.5));
    getStatistics().getHisto1D("Sum_All_TOT")->GetXaxis()->SetTitle("Sum_All_TOT [ns]");
    getStatistics().getHisto1D("Sum_All_TOT")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Sum_All_TOT_90", "Sum_All_TOT_90",
      401, -0.5, 400.5));
    getStatistics().getHisto1D("Sum_All_TOT_90")->GetXaxis()->SetTitle("Sum_All_TOT_90 [ns]");
    getStatistics().getHisto1D("Sum_All_TOT_90")->GetYaxis()->SetTitle("Counts");

    //TOT_90 after the sum of all TOT < 90 cut

    getStatistics().createHistogram(new TH1F("TOT_90", "TOT_90",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_90")->GetXaxis()->SetTitle("TOT_90 [ns]");
    getStatistics().getHisto1D("TOT_90")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TOT_Primary_90", "TOT_Primary_90",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_Primary_90")->GetXaxis()->SetTitle("TOT_Primary_90 [ns]");
    getStatistics().getHisto1D("TOT_Primary_90")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TOT_pr1_90", "TOT_pr1_90",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_pr1_90")->GetXaxis()->SetTitle("TOT_pr1_90 [ns]");
    getStatistics().getHisto1D("TOT_pr1_90")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TOT_pr2_90", "TOT_pr2_90",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_pr2_90")->GetXaxis()->SetTitle("TOT_pr1_90 [ns]");
    getStatistics().getHisto1D("TOT_pr2_90")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TOT_pr3_90", "TOT_pr3_90",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_pr3_90")->GetXaxis()->SetTitle("TOT_pr3_90 [ns]");
    getStatistics().getHisto1D("TOT_pr3_90")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TOT_ScatHit_90", "TOT_ScatHit_90",
      101, -0.5, 100.5));
    getStatistics().getHisto1D("TOT_ScatHit_90")->GetXaxis()->SetTitle("TOT_ScatHit_90 [ns]");
    getStatistics().getHisto1D("TOT_ScatHit_90")->GetYaxis()->SetTitle("Counts");

    //Energy Spectra after TOT Cut

    getStatistics().createHistogram(new TH1F("Energy1_TOT", "Energy1_TOT",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy1_TOT")->GetXaxis()->SetTitle("Energy1_TOT [keV]");
    getStatistics().getHisto1D("Energy1_TOT")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Energy2_TOT", "Energy2_TOT",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy2_TOT")->GetXaxis()->SetTitle("Energy2_TOT [keV]");
    getStatistics().getHisto1D("Energy2_TOT")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Energy3_TOT", "Energy3_TOT",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy3_TOT")->GetXaxis()->SetTitle("Energy3_TOT [keV]");
    getStatistics().getHisto1D("Energy3_TOT")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_12_TOT", "Dalitz_Energy_12_TOT", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_12_TOT")->GetXaxis()->SetTitle("Energy1");
    getStatistics().getHisto2D("Dalitz_Energy_12_TOT")->GetYaxis()->SetTitle("Energy2");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_23_TOT", "Dalitz_Energy_23_TOT", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_23_TOT")->GetXaxis()->SetTitle("Energy2");
    getStatistics().getHisto2D("Dalitz_Energy_23_TOT")->GetYaxis()->SetTitle("Energy3");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_31_TOT", "Dalitz_Energy_31_TOT", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_31_TOT")->GetXaxis()->SetTitle("Energy3_TOT");
    getStatistics().getHisto2D("Dalitz_Energy_31_TOT")->GetYaxis()->SetTitle("Energy1_TOT");

    //Distance from the Surface
    getStatistics().createHistogram(new TH1F("DistancefromSurface", "DistancefromSurface",
      510, -0.5, 50.5));
    getStatistics().getHisto1D("DistancefromSurface")->GetXaxis()->SetTitle("DistancefromSurface [cm]");
    getStatistics().getHisto1D("DistancefromSurface")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("DistancefromSurface_less5", "DistancefromSurface_less5",
      510, -0.5, 50.5));
    getStatistics().getHisto1D("DistancefromSurface_less5")->GetXaxis()->SetTitle("DistancefromSurface_less5 [cm]");
    getStatistics().getHisto1D("DistancefromSurface_less5")->GetYaxis()->SetTitle("Counts");

    //Energy Spectra after Distance Cut

    getStatistics().createHistogram(new TH1F("Energy1_Dist", "Energy1_Dist",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy1_Dist")->GetXaxis()->SetTitle("Energy1_Dist [keV]");
    getStatistics().getHisto1D("Energy1_Dist")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Energy2_Dist", "Energy2_Dist",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy2_Dist")->GetXaxis()->SetTitle("Energy2_Dist [keV]");
    getStatistics().getHisto1D("Energy2_Dist")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Energy3_Dist", "Energy3_Dist",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy3_Dist")->GetXaxis()->SetTitle("Energy3_Dist [keV]");
    getStatistics().getHisto1D("Energy3_Dist")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_12_Dist", "Dalitz_Energy_12_Dist", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_12_Dist")->GetXaxis()->SetTitle("Energy1");
    getStatistics().getHisto2D("Dalitz_Energy_12_Dist")->GetYaxis()->SetTitle("Energy2");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_23_Dist", "Dalitz_Energy_23_Dist", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_23_Dist")->GetXaxis()->SetTitle("Energy2");
    getStatistics().getHisto2D("Dalitz_Energy_23_Dist")->GetYaxis()->SetTitle("Energy3");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_31_Dist", "Dalitz_Energy_31_Dist", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_31_Dist")->GetXaxis()->SetTitle("Energy3_Dist");
    getStatistics().getHisto2D("Dalitz_Energy_31_Dist")->GetYaxis()->SetTitle("Energy1_Dist");   

    //Emmision Time Estimation

    getStatistics().createHistogram(new TH1F("TOF_Difference_t3t1", "TOF_Difference_t3t1",
      110, -5.5, 5.5));
    getStatistics().getHisto1D("TOF_Difference_t3t1")->GetXaxis()->SetTitle("TOF_Difference_t3t1 [ns]");
    getStatistics().getHisto1D("TOF_Difference_t3t1")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TOF_Difference_avrg", "TOF_Difference_avrg",
      110, -5.5, 5.5));
    getStatistics().getHisto1D("TOF_Difference_avrg")->GetXaxis()->SetTitle("TOF_Difference_avrg [ns]");
    getStatistics().getHisto1D("TOF_Difference_avrg")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("TOF_Difference_avrg_Cut_2ns", "TOF_Difference_avrg_Cut_2ns",
      110, -5.5, 5.5));
    getStatistics().getHisto1D("TOF_Difference_avrg_Cut_2ns")->GetXaxis()->SetTitle("TOF_Difference_avrg_Cut_2ns [ns]");
    getStatistics().getHisto1D("TOF_Difference_avrg_Cut_2ns")->GetYaxis()->SetTitle("Counts");

    //Energy Spectra after Emission Time Spread Spectra Cut 

    getStatistics().createHistogram(new TH1F("Energy1_ET", "Energy1_ET",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy1_ET")->GetXaxis()->SetTitle("Energy1_ET [keV]");
    getStatistics().getHisto1D("Energy1_ET")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Energy2_ET", "Energy2_ET",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy2_ET")->GetXaxis()->SetTitle("Energy2_ET [keV]");
    getStatistics().getHisto1D("Energy2_ET")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Energy3_ET", "Energy3_ET",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy3_ET")->GetXaxis()->SetTitle("Energy3_ET [keV]");
    getStatistics().getHisto1D("Energy3_ET")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_12_ET", "Dalitz_Energy_12_ET", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_12_ET")->GetXaxis()->SetTitle("Energy1");
    getStatistics().getHisto2D("Dalitz_Energy_12_ET")->GetYaxis()->SetTitle("Energy2");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_23_ET", "Dalitz_Energy_23_ET", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_23_ET")->GetXaxis()->SetTitle("Energy2");
    getStatistics().getHisto2D("Dalitz_Energy_23_ET")->GetYaxis()->SetTitle("Energy3");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_31_ET", "Dalitz_Energy_31_ET", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_31_ET")->GetXaxis()->SetTitle("Energy3_ET");
    getStatistics().getHisto2D("Dalitz_Energy_31_ET")->GetYaxis()->SetTitle("Energy1_ET");   

    //Angle 3D Cut - At sum 190 Degree

    getStatistics().createHistogram(new TH2F("Angle3D_190", "3D Azimuthal Angles (Greater than 190deg)", 251, -0.5, 250.5, 251, -0.5, 250.5));
    getStatistics().getHisto2D("Angle3D_190")->GetXaxis()->SetTitle("#Theta_{1} + #Theta_{0}");
    getStatistics().getHisto2D("Angle3D_190")->GetYaxis()->SetTitle("#Theta_{1} - #Theta_{0}");

    //Energy Spectra after Angle Cut

    getStatistics().createHistogram(new TH1F("Energy1_Angle", "Energy1_Angle",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy1_Angle")->GetXaxis()->SetTitle("Energy1_Angle [keV]");
    getStatistics().getHisto1D("Energy1_Angle")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Energy2_Angle", "Energy2_Angle",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy2_Angle")->GetXaxis()->SetTitle("Energy2_Angle [keV]");
    getStatistics().getHisto1D("Energy2_Angle")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F("Energy3_Angle", "Energy3_Angle",
      3001, -1500.5, 1500.5));
    getStatistics().getHisto1D("Energy3_Angle")->GetXaxis()->SetTitle("Energy3_Angle [keV]");
    getStatistics().getHisto1D("Energy3_Angle")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_12_Angle", "Dalitz_Energy_12_Angle", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_12_Angle")->GetXaxis()->SetTitle("Energy1");
    getStatistics().getHisto2D("Dalitz_Energy_12_Angle")->GetYaxis()->SetTitle("Energy2");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_23_Angle", "Dalitz_Energy_23_Angle", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_23_Angle")->GetXaxis()->SetTitle("Energy2");
    getStatistics().getHisto2D("Dalitz_Energy_23_Angle")->GetYaxis()->SetTitle("Energy3");

    getStatistics().createHistogram(new TH2F("Dalitz_Energy_31_Angle", "Dalitz_Energy_31_Angle", 1041, -0.5, 1040.5, 1041, -0.5, 1040.5));
    getStatistics().getHisto2D("Dalitz_Energy_31_Angle")->GetXaxis()->SetTitle("Energy3_TOT");
    getStatistics().getHisto2D("Dalitz_Energy_31_Angle")->GetYaxis()->SetTitle("Energy1_TOT");

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



 //Expectation Value - Change in X position

/*	for(double Y_Pos = -1.0; Y_Pos <= 1.0; Y_Pos += 0.1)	
	{	

    getStatistics().createHistogram(new TH1F(Form("ExpecValue1_Y_Pos_%f",Y_Pos), Form("ExpecValue1_Y_Pos_%f", Y_Pos),
      300, -1.5, 1.5));
    getStatistics().getHisto1D(Form("ExpecValue1_Y_Pos_%f", Y_Pos))->GetXaxis()->SetTitle("ExpecValue1");
    getStatistics().getHisto1D(Form("ExpecValue1_Y_Pos_%f", Y_Pos))->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F(Form("ExpecValue2_Y_Pos_%f", Y_Pos), Form("ExpecValue2_Y_Pos_%f", Y_Pos),
      300, -1.5, 1.5));
    getStatistics().getHisto1D(Form("ExpecValue2_Y_Pos_%f", Y_Pos))->GetXaxis()->SetTitle("ExpecValue2");
    getStatistics().getHisto1D(Form("ExpecValue2_Y_Pos_%f", Y_Pos))->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F(Form("ExpecValue3_Y_Pos_%f", Y_Pos), Form("ExpecValue3_Y_Pos_%f", Y_Pos),
      300, -1.5, 1.5));
    getStatistics().getHisto1D(Form("ExpecValue3_Y_Pos_%f", Y_Pos))->GetXaxis()->SetTitle("ExpecValue3");
    getStatistics().getHisto1D(Form("ExpecValue3_Y_Pos_%f", Y_Pos))->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F(Form("ExpecValue_Y_Pos_%f", Y_Pos), Form("ExpecValue_Y_Pos_%f", Y_Pos),
      300, -1.5, 1.5));
    getStatistics().getHisto1D(Form("ExpecValue_Y_Pos_%f", Y_Pos))->GetXaxis()->SetTitle("ExpecValue");
    getStatistics().getHisto1D(Form("ExpecValue_Y_Pos_%f", Y_Pos))->GetYaxis()->SetTitle("Counts");

	}
*/
/*


 //Expectation Value - Change in Y position

	for(double Y_Pos = -1.0; Y_Pos <= 1.0; Y_Pos += 0.1)	
	{	

    getStatistics().createHistogram(new TH1F(Form("ExpecValue1_Y_Pos_%f",Y_Pos), Form("ExpecValue1_Y_Pos_%f", Y_Pos),
      300, -1.5, 1.5));
    getStatistics().getHisto1D(Form("ExpecValue1_Y_Pos_%f", Y_Pos))->GetXaxis()->SetTitle("ExpecValue1");
    getStatistics().getHisto1D(Form("ExpecValue1_Y_Pos_%f", Y_Pos))->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F(Form("ExpecValue2_Y_Pos_%f", Y_Pos), Form("ExpecValue2_Y_Pos_%f", Y_Pos),
      300, -1.5, 1.5));
    getStatistics().getHisto1D(Form("ExpecValue2_Y_Pos_%f", Y_Pos))->GetXaxis()->SetTitle("ExpecValue2");
    getStatistics().getHisto1D(Form("ExpecValue2_Y_Pos_%f", Y_Pos))->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F(Form("ExpecValue3_Y_Pos_%f", Y_Pos), Form("ExpecValue3_Y_Pos_%f", Y_Pos),
      300, -1.5, 1.5));
    getStatistics().getHisto1D(Form("ExpecValue3_Y_Pos_%f", Y_Pos))->GetXaxis()->SetTitle("ExpecValue3");
    getStatistics().getHisto1D(Form("ExpecValue3_Y_Pos_%f", Y_Pos))->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F(Form("ExpecValue_Y_Pos_%f", Y_Pos), Form("ExpecValue_Y_Pos_%f", Y_Pos),
      300, -1.5, 1.5));
    getStatistics().getHisto1D(Form("ExpecValue_Y_Pos_%f", Y_Pos))->GetXaxis()->SetTitle("ExpecValue");
    getStatistics().getHisto1D(Form("ExpecValue_Y_Pos_%f", Y_Pos))->GetYaxis()->SetTitle("Counts");

	}


//Expectation Value - Change in Z position

	for(double Z_Pos = -1.0; Z_Pos <= 1.0; Z_Pos += 0.1)	
	{	

    getStatistics().createHistogram(new TH1F(Form("ExpecValue1_Z_Pos_%f",Z_Pos), Form("ExpecValue1_Z_Pos_%f", Z_Pos),
      300, -1.5, 1.5));
    getStatistics().getHisto1D(Form("ExpecValue1_Z_Pos_%f", Z_Pos))->GetXaxis()->SetTitle("ExpecValue1");
    getStatistics().getHisto1D(Form("ExpecValue1_Z_Pos_%f", Z_Pos))->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F(Form("ExpecValue2_Z_Pos_%f", Z_Pos), Form("ExpecValue2_Z_Pos_%f", Z_Pos),
      300, -1.5, 1.5));
    getStatistics().getHisto1D(Form("ExpecValue2_Z_Pos_%f", Z_Pos))->GetXaxis()->SetTitle("ExpecValue2");
    getStatistics().getHisto1D(Form("ExpecValue2_Z_Pos_%f", Z_Pos))->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F(Form("ExpecValue3_Z_Pos_%f", Z_Pos), Form("ExpecValue3_Z_Pos_%f", Z_Pos),
      300, -1.5, 1.5));
    getStatistics().getHisto1D(Form("ExpecValue3_Z_Pos_%f", Z_Pos))->GetXaxis()->SetTitle("ExpecValue3");
    getStatistics().getHisto1D(Form("ExpecValue3_Z_Pos_%f", Z_Pos))->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH1F(Form("ExpecValue_Z_Pos_%f", Z_Pos), Form("ExpecValue_Z_Pos_%f", Z_Pos),
      300, -1.5, 1.5));
    getStatistics().getHisto1D(Form("ExpecValue_Z_Pos_%f", Z_Pos))->GetXaxis()->SetTitle("ExpecValue");
    getStatistics().getHisto1D(Form("ExpecValue_Z_Pos_%f", Z_Pos))->GetYaxis()->SetTitle("Counts");

	}


*/







  }

  return true;
}

//TOT Calculation - Function (Sum over all thresholds)

double CalcTOT(const JPetHit & Hit) {

  double TOT = 0.;
  double TOT_A = 0.;
  double TOT_B = 0.;

  auto lead_times_A = Hit.getSignalA().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Leading);
  auto trail_times_A = Hit.getSignalA().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Trailing);
  auto lead_times_B = Hit.getSignalB().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Leading);
  auto trail_times_B = Hit.getSignalB().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Trailing);

  for (auto & thr_time_pair: lead_times_A) {
    int thr = thr_time_pair.first;
    if (trail_times_A.count(thr) > 0) {
      TOT_A = TOT_A + trail_times_A[thr] - lead_times_A[thr];
    }
  }

  for (auto & thr_time_pair: lead_times_B) {
    int thr = thr_time_pair.first;
    if (trail_times_B.count(thr) > 0) {

      TOT_B = TOT_B + trail_times_B[thr] - lead_times_B[thr];
    }
  }
  TOT = (TOT_A + TOT_B) / 1000.;

  return TOT;
}

//TOF Calculation - Function (From Center (0,0,0))

double CalcTOF(const JPetHit & Hit, TVector3 Center) {

  double Dist = sqrt(pow(Hit.getPosX() - Center.X(), 2) + pow(Hit.getPosY() - Center.Y(), 2) + pow(Hit.getPosZ() - Center.Z(), 2));

  double CalTime = Dist / 29.979246; //velocity of light in cm/s, returns time in ns

  double HitTime = Hit.getTime() / 1000.0;

  double TOF = (HitTime - CalTime);

  return TOF;

}

//TOF of Scattered Hit

/*double CalcScatTOF(const JPetHit & Hit1,
  const JPetHit & Hit2) {

  double Distpr = sqrt(pow(Hit1.getPosX(), 2) + pow(Hit1.getPosY(), 2) + pow(Hit1.getPosZ(), 2));

  double Distsr = sqrt(pow((Hit2.getPosX() - Hit1.getPosX()), 2) + pow((Hit2.getPosY() - Hit1.getPosY()), 2) + pow((Hit2.getPosZ() - Hit1.getPosZ()), 2));

  double TotalDist = Distpr + Distsr;

  double ScatCalTime = TotalDist / 29.979246; //velocity of light in cm/s, returns time in ns

  return ScatCalTime;

}
*/


//3D-Angle Calculation - Function

  double Calc3DAngle(const JPetHit & Hit1,
  const JPetHit & Hit2 , TVector3 Center) {

  double scalarProd = (Hit1.getPosX() - Center.X()) * (Hit2.getPosX() - Center.X()) + (Hit1.getPosY() - Center.Y()) * (Hit2.getPosY() - Center.Y()) + (Hit1.getPosZ() - Center.Z()) * (Hit2.getPosZ() - Center.Z());

  double magProd = sqrt((pow(Hit1.getPosX() - Center.X(), 2) +
      pow(Hit1.getPosY() - Center.Y(), 2) +
      pow(Hit1.getPosZ() - Center.Z(), 2)) *
    (pow(Hit2.getPosX() - Center.X(), 2) +
      pow(Hit2.getPosY() - Center.Y(), 2) +
      pow(Hit2.getPosZ() - Center.Z(), 2)));

  double Angle = acos(scalarProd / magProd) * 180 / 3.14159;

  return Angle;
}

//Caulculate Energy1 (Most Energetic)

double CalcEnergy1(double Angle12, double Angle23, double Angle31)

{

  Angle12 = Angle12 * 3.14159 / 180;
  Angle23 = Angle23 * 3.14159 / 180;
  Angle31 = Angle31 * 3.14159 / 180;

  double masse = 510.9989461; // keV

  double Numerator = -cos(Angle31) + (cos(Angle12) * cos(Angle23));

  double Denominator = (-1 + cos(Angle12)) * (1 + cos(Angle12) - cos(Angle31) - cos(Angle23));

  double Energy1 = -2.0 * masse * (Numerator / Denominator);

  return Energy1;

}

//Caulculate Energy2 (Second Most Energetic)

double CalcEnergy2(double Angle12, double Angle23, double Angle31)

{

  Angle12 = Angle12 * 3.14159 / 180;
  Angle23 = Angle23 * 3.14159 / 180;
  Angle31 = Angle31 * 3.14159 / 180;

  double masse = 510.9989461; // keV

  double Numerator = (cos(Angle12) * cos(Angle31)) - cos(Angle23);

  double Denominator1 = (-1 + cos(Angle12));
  double Denominator2 = (1 + cos(Angle12) - cos(Angle31) - cos(Angle23));
  double Denominator = Denominator1 * Denominator2;

  double Energy2 = -2.0 * masse * (Numerator / Denominator);

  return Energy2;

}

//Caulculate Energy3 (Least Energetic)

double CalcEnergy3(double Angle12, double Angle23, double Angle31)

{

  Angle12 = Angle12 * 3.14159 / 180;
  Angle23 = Angle23 * 3.14159 / 180;
  Angle31 = Angle31 * 3.14159 / 180;

  double masse = 510.9989461; // keV

  double Numerator = (1 + cos(Angle12));

  double Denominator = (1 + cos(Angle12) - cos(Angle31) - cos(Angle23));

  double Energy3 = 2.0 * masse * (Numerator / Denominator);

  return Energy3;

}

//Calculate the distance of the Annihilation Surface to the center of the detector geometry

double CalDistofSurface(const JPetHit Hit1,
  const JPetHit Hit2,
    const JPetHit Hit3, TVector3 Center)

{

  TVector3 vec1(Hit2.getPosX() - Hit1.getPosX(), Hit2.getPosY() - Hit1.getPosY(), Hit2.getPosZ() - Hit1.getPosZ());
  TVector3 vec2(Hit3.getPosX() - Hit2.getPosX(), Hit3.getPosY() - Hit2.getPosY(), Hit3.getPosZ() - Hit2.getPosZ());
  TVector3 crossProd = vec1.Cross(vec2);

  double Dcoeef = -crossProd(0) * Hit2.getPosX() - crossProd(1) * Hit2.getPosY() - crossProd(2) * Hit2.getPosZ();

  double distancefromZero = fabs(crossProd(0) * Center.X() + crossProd(1) * Center.Y() + crossProd(2) * Center.Z() + Dcoeef) / crossProd.Mag();
  return distancefromZero;
}

//Calculation of the Expectation Value function

double CalExpecValue(const JPetHit Hit1,
  const JPetHit Hit2,
    const JPetHit Hit3, TVector3 Center)

{

  TVector3 k1(Hit1.getPosX() - Center.X() , Hit1.getPosY() - Center.Y() , Hit1.getPosZ() - Center.Z());
  TVector3 k1p(Hit2.getPosX() - Hit1.getPosX(), Hit2.getPosY() - Hit1.getPosY(), Hit2.getPosZ() - Hit1.getPosZ());
  TVector3 k2(Hit3.getPosX() - Center.X() , Hit3.getPosY() - Center.Y(), Hit3.getPosZ() - Center.Z());

  TVector3 epsilon = k1.Cross(k1p);

  double ExpecValue = ((epsilon.Dot(k2)) / ((epsilon.Mag()) * (k2.Mag())));

  return ExpecValue;

}



 

//Calculation of the Scatter Test between Primary and Secondary hits

double CalScatterTest(const JPetHit & Hit1,
  const JPetHit & Hit2)

{

  double timeDiff = ((Hit2.getTime() / 1000.0) - (Hit1.getTime() / 1000.0));
  float Dist = sqrt(pow(Hit2.getPosX() - Hit1.getPosX(), 2) +
    pow(Hit2.getPosY() - Hit1.getPosY(), 2) +
    pow(Hit2.getPosZ() - Hit1.getPosZ(), 2));
  Dist = Dist / 29.979246;
  double Scat = (timeDiff - Dist);
  return Scat;

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



      const auto & event = dynamic_cast <
        const JPetEvent & > (timeWindow->operator[](i));

      getStatistics().getHisto1D("Hits_All")->Fill(event.getHits().size());

      //This analysis requires only 4-Hits in a single event	    

      if (event.getHits().size() == 5) {

	//for(double Y_Pos = -1.0; Y_Pos <= 1.0; Y_Pos += 0.1){

		
	//Main Code:

	TVector3 Center(0.0, 0.0, 0.0);  //Center of the Geometry

	getStatistics().getHisto1D("Hits")->Fill(event.getHits().size()); 

        JPetHit firstHit = event.getHits().at(0);
        JPetHit secondHit = event.getHits().at(1);
        JPetHit thirdHit = event.getHits().at(2);
        JPetHit fourthHit = event.getHits().at(3);
	JPetHit fifthHit = event.getHits().at(4);
	
	//Z-Position of the Hits
        getStatistics().getHisto1D("Z_Pos_Before")->Fill(firstHit.getPosZ());
        getStatistics().getHisto1D("Z_Pos_Before")->Fill(secondHit.getPosZ());
        getStatistics().getHisto1D("Z_Pos_Before")->Fill(thirdHit.getPosZ());
        getStatistics().getHisto1D("Z_Pos_Before")->Fill(fourthHit.getPosZ());
        getStatistics().getHisto1D("Z_Pos_Before")->Fill(fifthHit.getPosZ());

	//Time Difference B-A of the Hits
	auto timeDifference_first = firstHit.getTimeDiff() / 1000.0;
        getStatistics().getHisto1D("TimeDiff_Resolution")->Fill(timeDifference_first);
        auto timeDifference_second = secondHit.getTimeDiff() / 1000.0;
        getStatistics().getHisto1D("TimeDiff_Resolution")->Fill(timeDifference_second);
        auto timeDifference_third = thirdHit.getTimeDiff() / 1000.0;
        getStatistics().getHisto1D("TimeDiff_Resolution")->Fill(timeDifference_third);
        auto timeDifference_fourth = fourthHit.getTimeDiff() / 1000.0;
        getStatistics().getHisto1D("TimeDiff_Resolution")->Fill(timeDifference_fourth);
	auto timeDifference_fifth = fifthHit.getTimeDiff() / 1000.0;
        getStatistics().getHisto1D("TimeDiff_Resolution")->Fill(timeDifference_fifth);


        //Z-Position is less than 23.0 cm

        if (fabs(firstHit.getPosZ()) <= 23.0 && fabs(secondHit.getPosZ()) <= 23.0 && fabs(thirdHit.getPosZ()) <= 23.0 && fabs(fourthHit.getPosZ()) <= 23.0 && fabs(fifthHit.getPosZ()) <= 23.0) {

          getStatistics().getHisto1D("Z_Pos_After")->Fill(firstHit.getPosZ());
          getStatistics().getHisto1D("Z_Pos_After")->Fill(secondHit.getPosZ());
          getStatistics().getHisto1D("Z_Pos_After")->Fill(thirdHit.getPosZ());
          getStatistics().getHisto1D("Z_Pos_After")->Fill(fourthHit.getPosZ());
          getStatistics().getHisto1D("Hits_Z_Pos")->Fill(event.getHits().size());


   	//Scintillator ID must be unique

          auto scinID_first = firstHit.getScintillator().getID();
          auto scinID_second = secondHit.getScintillator().getID();
          auto scinID_third = thirdHit.getScintillator().getID();
          auto scinID_fourth = fourthHit.getScintillator().getID();
	  auto scinID_fifth = fifthHit.getScintillator().getID();

          std::vector < double > ScinID;
          ScinID.push_back(scinID_first);
          ScinID.push_back(scinID_second);
          ScinID.push_back(scinID_third);
          ScinID.push_back(scinID_fourth);
	  ScinID.push_back(scinID_fifth);


          int k = 0;
          int limit = ScinID.size();
          for (int i = 0; i < limit; i++) {
            for (int j = 0; j < limit; j++) {
              if (i != j && ScinID[i] == ScinID[j])
                k++;
            }
          }

          int m = k / 2;

          getStatistics().getHisto1D("ScinID_Replica")->Fill(m);

          if (m == 0)
            getStatistics().getHisto1D("ScinID_Replica_Cut")->Fill(m);

          if (scinID_first != scinID_second && scinID_first != scinID_third && scinID_first != scinID_fourth && scinID_first != scinID_fifth)

          {

            if (scinID_second != scinID_third && scinID_second != scinID_fourth && scinID_second != scinID_fifth)

            {

              if (scinID_third != scinID_fourth && scinID_third != scinID_fifth)

              {

		if(scinID_fourth != scinID_fifth)
	
		{


                getStatistics().getHisto1D("Hits_ScinID")->Fill(event.getHits().size());



                double TOT_1 = CalcTOT(firstHit);
		double TOT_2 = CalcTOT(secondHit);
		double TOT_3 = CalcTOT(thirdHit);
		double TOT_4 = CalcTOT(fourthHit);
		double TOT_5 = CalcTOT(fifthHit);



       


                //Ordering Hits and segregating Primary interactions and Scattered Interaction

                vector < pair < double, pair < JPetHit, JPetHit >>> Scat_Ordering_Vec; //Create Vector of pair of pair
                for (uint i = 0; i < 4; i++) {

                  for (uint j = 0; j < 4; j++) {

                    if (i != j) {

                      //For two different hits combination 

            		
		      JPetHit Hiti = event.getHits().at(i);
                      JPetHit Hitj = event.getHits().at(j);
                
		
		      //Fill the vector with ScatTest value and the pr. hit & sr. hit
		
		      double Time_i = Hiti.getTime() / 1000.0 ;
		      double Time_j = Hitj.getTime() / 1000.0 ;
                     
			if(Time_j > Time_i)
			{


		      double Scatij = CalScatterTest(event.getHits().at(i), event.getHits().at(j));
                      Scat_Ordering_Vec.push_back({
                        Scatij,
                        {
                          Hiti,
                          Hitj
                        }
                      });

                    }

                  }

                }

  	      }

		//cout<<Scat_Ordering_Vec.size()<<endl;
                std::sort(Scat_Ordering_Vec.begin(), Scat_Ordering_Vec.end(), comparison3); //Sort based on the abs ScatTest value
                getStatistics().getHisto1D("Delta_ij_least")->Fill(Scat_Ordering_Vec.at(0).first);
                double scatTOT_check = CalcTOT(Scat_Ordering_Vec.at(0).second.second); //TOT of the least ScatTest value
                getStatistics().getHisto1D("TOT_scat_check")->Fill(scatTOT_check);

                for (uint i = 1; i < Scat_Ordering_Vec.size(); i++) {
                  getStatistics().getHisto1D("Delta_ij_all_notleast")->Fill(Scat_Ordering_Vec.at(i).first);

                }

                if (fabs(Scat_Ordering_Vec.at(0).first) <= 0.5) {

                  getStatistics().getHisto1D("Delta_ij_least_Cut_0.5ns")->Fill(Scat_Ordering_Vec.at(0).first);
                  getStatistics().getHisto1D("TOT_scat_check_Cut_0.5ns")->Fill(scatTOT_check);


                  getStatistics().getHisto2D("TOT_scat_check_vs_Delta_ij_least")->Fill(Scat_Ordering_Vec.at(0).first, scatTOT_check);

                  //Create a vector with the primary hits 
                  std::vector < JPetHit > Hits_Ordered;
                  JPetHit ScatHit = Scat_Ordering_Vec.at(0).second.second;

                  //Fill a vector with hits that don't have the same ID as the Scattered one	
                  for (int z = 0; z < 4; z++) {

                    JPetHit Hit_var = event.getHits().at(z);

                    if (Hit_var.getScintillator().getID() != Scat_Ordering_Vec.at(0).second.second.getScintillator().getID()) {

                      Hits_Ordered.push_back(Hit_var);

                    }

                  }

                  JPetHit & pr1 = Hits_Ordered.at(0);
                  JPetHit & pr2 = Hits_Ordered.at(1);
                  JPetHit & pr3 = Hits_Ordered.at(2);

                  //Scin ID of ordered Hits
                  auto scinID_pr1 = pr1.getScintillator().getID();
                  auto scinID_pr2 = pr2.getScintillator().getID();
                  auto scinID_pr3 = pr3.getScintillator().getID();
                  auto scinID_ScatHit = ScatHit.getScintillator().getID();

                  //TOT first Hit//
                  double pr1TOT = CalcTOT(pr1);
                  getStatistics().getHisto1D("TOT_pr1")->Fill(pr1TOT);
                  getStatistics().getHisto1D("TOT")->Fill(pr1TOT);
                  getStatistics().getHisto1D("TOT_Primary")->Fill(pr1TOT);

                  //Control Spectras for first Hit
                  auto timeDifference_pr1 = pr1.getTimeDiff() / 1000.0;
                  getStatistics().getHisto2D("ScinID_vs_TOT")->Fill(pr1TOT, scinID_pr1);
                  getStatistics().getHisto2D("DeltaT_vs_ScinID_big")->Fill(scinID_pr1, timeDifference_pr1);
                  getStatistics().getHisto1D("ScinID")->Fill(scinID_pr1);
                  getStatistics().getHisto1D("TimeDiff")->Fill(timeDifference_pr1);

                  //TOT second Hit//
                  double pr2TOT = CalcTOT(pr2);
                  getStatistics().getHisto1D("TOT_pr2")->Fill(pr2TOT);
                  getStatistics().getHisto1D("TOT")->Fill(pr2TOT);
                  getStatistics().getHisto1D("TOT_Primary")->Fill(pr2TOT);

                  //Control Spectras for second Hit
                  auto timeDifference_pr2 = pr2.getTimeDiff() / 1000.0;
                  getStatistics().getHisto2D("ScinID_vs_TOT")->Fill(pr2TOT, scinID_pr2);
                  getStatistics().getHisto2D("DeltaT_vs_ScinID_big")->Fill(scinID_pr2, timeDifference_pr2);
                  getStatistics().getHisto1D("ScinID")->Fill(scinID_pr2);
                  getStatistics().getHisto1D("TimeDiff")->Fill(timeDifference_pr2);

                  //TOT third Hit//
                  double pr3TOT = CalcTOT(pr3);
                  getStatistics().getHisto1D("TOT_pr3")->Fill(pr3TOT);
                  getStatistics().getHisto1D("TOT")->Fill(pr3TOT);
                  getStatistics().getHisto1D("TOT_Primary")->Fill(pr3TOT);
                  //Control Spectras for third Hit
                  auto timeDifference_pr3 = pr3.getTimeDiff() / 1000.0;
                  getStatistics().getHisto2D("ScinID_vs_TOT")->Fill(pr3TOT, scinID_pr3);
                  getStatistics().getHisto2D("DeltaT_vs_ScinID_big")->Fill(scinID_pr3, timeDifference_pr3);
                  getStatistics().getHisto1D("ScinID")->Fill(scinID_pr3);
                  getStatistics().getHisto1D("TimeDiff")->Fill(timeDifference_pr3);

                  //TOT fourth Hit//
                  double ScatHitTOT = CalcTOT(ScatHit);
                  getStatistics().getHisto1D("TOT_ScatHit")->Fill(ScatHitTOT);
                  getStatistics().getHisto1D("TOT")->Fill(ScatHitTOT);

                  //Control Spectras for fourth Hit
                  auto timeDifference_ScatHit = ScatHit.getTimeDiff() / 1000.0;
                  getStatistics().getHisto2D("ScinID_vs_TOT")->Fill(ScatHitTOT, scinID_ScatHit);
                  getStatistics().getHisto2D("DeltaT_vs_ScinID_big")->Fill(scinID_ScatHit, timeDifference_ScatHit);
                  getStatistics().getHisto1D("ScinID")->Fill(scinID_ScatHit);
                  getStatistics().getHisto1D("TimeDiff")->Fill(timeDifference_ScatHit);

                  //TOF Correction for Primary and Secondary Hits

                  double pr1TOF = CalcTOF(pr1, Center);
                  double pr2TOF = CalcTOF(pr2, Center);
                  double pr3TOF = CalcTOF(pr3, Center);
                //  double Scat_calculated = CalcScatTOF(Scat_Ordering_Vec.at(0).second.first, Scat_Ordering_Vec.at(0).second.second);

                  double Scat_t1 = (pr1TOF + pr2TOF + pr3TOF) / 3.0;

                
                    //3-Dimensional Angle Calculation between all four registered interactions
                    vector < pair < double, pair < JPetHit, JPetHit >>> Angle3D;
                    double Angle12 = Calc3DAngle(pr1, pr2, Center);
                    double Angle23 = Calc3DAngle(pr2, pr3, Center);
                    double Angle31 = Calc3DAngle(pr3, pr1, Center);
                    Angle3D.push_back({
                      Angle12,
                      {
                        pr1,
                        pr2
                      }
                    });
                    Angle3D.push_back({
                      Angle23,
                      {
                        pr2,
                        pr3
                      }
                    });
                    Angle3D.push_back({
                      Angle31,
                      {
                        pr3,
                        pr1
                      }
                    });

                    std::sort(Angle3D.begin(), Angle3D.end(), comparison3);

                    getStatistics().getHisto2D("Angle3D")->Fill(Angle3D.at(1).first + Angle3D.at(0).first, Angle3D.at(1).first - Angle3D.at(0).first);
			
		    double AngleDiff = (360 - (Angle12 + Angle23));
                    double Sum_All_TOT = pr1TOT + pr2TOT + pr3TOT + ScatHitTOT;
  		    getStatistics().getHisto1D("Sum_All_TOT_90_before")->Fill(Sum_All_TOT);



                    //Energy Calculations

                    double Energy1 = CalcEnergy1(Angle12, Angle23, AngleDiff);
                    double Energy2 = CalcEnergy2(Angle12, Angle23, AngleDiff);
                    double Energy3 = CalcEnergy3(Angle12, Angle23, AngleDiff);

                    getStatistics().getHisto2D("Dalitz_Energy_12")->Fill(Energy1, Energy2);
                    getStatistics().getHisto2D("Dalitz_Energy_23")->Fill(Energy2, Energy3);
                    getStatistics().getHisto2D("Dalitz_Energy_31")->Fill(Energy3, Energy1);

                    getStatistics().getHisto2D("AngleDistribution_01")->Fill(Angle12, Angle23);
                    getStatistics().getHisto2D("AngleDistribution_12")->Fill(Angle23, Angle31);
                    getStatistics().getHisto2D("AngleDistribution_20")->Fill(Angle31, Angle12);
		
		    if((Angle23 < (Angle12 + 10))  &&  (Angle23 > (Angle12 - 10))){

		 getStatistics().getHisto2D("AngleDistribution_01_Check")->Fill(Angle12, Angle23);
   		 getStatistics().getHisto1D("TOT_AngleCheck")->Fill(ScatHitTOT);
		 getStatistics().getHisto1D("TOT_AngleCheck")->Fill(pr3TOT);
		 getStatistics().getHisto1D("TOT_AngleCheck")->Fill(pr2TOT);
		 getStatistics().getHisto1D("TOT_AngleCheck")->Fill(pr1TOT);

		    }

		    if(pr1TOT >= 20 && pr2TOT >= 20 && pr3TOT >= 20 && ScatHitTOT >= 20)
			{

 		 getStatistics().getHisto1D("TOT_AngleCheck_TOT")->Fill(ScatHitTOT);
		 getStatistics().getHisto1D("TOT_AngleCheck_TOT")->Fill(pr3TOT);
		 getStatistics().getHisto1D("TOT_AngleCheck_TOT")->Fill(pr2TOT);
		 getStatistics().getHisto1D("TOT_AngleCheck_TOT")->Fill(pr1TOT);

		 getStatistics().getHisto2D("AngleDistribution_01_Check_TOT")->Fill(Angle12, Angle23);



			}



                    double Sum_Energy = Energy1 + Energy2 + Energy3;

                    getStatistics().getHisto1D("Energy1")->Fill(Energy1);
                    getStatistics().getHisto1D("Energy2")->Fill(Energy2);
                    getStatistics().getHisto1D("Energy3")->Fill(Energy3);
                    getStatistics().getHisto1D("Sum_Energy")->Fill(Sum_Energy);
                    double Sum_Energy_Diff = ((2 * 511.0) - Sum_Energy);

                    getStatistics().getHisto1D("Sum_Energy_Diff")->Fill(Sum_Energy_Diff);

                    //TOT sum of all the four hits


                    getStatistics().getHisto1D("Sum_All_TOT")->Fill(Sum_All_TOT);

                    if (Sum_All_TOT <= 90.0) {

                    getStatistics().getHisto2D("AngleDistribution_01_TOT")->Fill(Angle12, Angle23);

			 getStatistics().getHisto2D("Angle3D_TOT")->Fill(Angle3D.at(1).first + Angle3D.at(0).first, Angle3D.at(1).first - Angle3D.at(0).first);
                   
   getStatistics().getHisto1D("Sum_All_TOT_90")->Fill(Sum_All_TOT);

                      getStatistics().getHisto1D("TOT_pr1_90")->Fill(pr1TOT);
                      getStatistics().getHisto1D("TOT_pr2_90")->Fill(pr2TOT);
                      getStatistics().getHisto1D("TOT_pr3_90")->Fill(pr3TOT);
                      getStatistics().getHisto1D("TOT_90")->Fill(pr1TOT);
                      getStatistics().getHisto1D("TOT_90")->Fill(pr2TOT);
                      getStatistics().getHisto1D("TOT_90")->Fill(pr3TOT);
                      getStatistics().getHisto1D("TOT_90")->Fill(ScatHitTOT);
                      getStatistics().getHisto1D("TOT_Primary_90")->Fill(pr1TOT);
                      getStatistics().getHisto1D("TOT_Primary_90")->Fill(pr2TOT);
                      getStatistics().getHisto1D("TOT_Primary_90")->Fill(pr3TOT);
                      getStatistics().getHisto1D("TOT_ScatHit_90")->Fill(ScatHitTOT);

                      //Energy Spectra after the TOT sum cut

                      getStatistics().getHisto2D("Dalitz_Energy_12_TOT")->Fill(Energy1, Energy2);
                      getStatistics().getHisto2D("Dalitz_Energy_23_TOT")->Fill(Energy2, Energy3);
                      getStatistics().getHisto2D("Dalitz_Energy_31_TOT")->Fill(Energy3, Energy1);
                      getStatistics().getHisto1D("Energy1_TOT")->Fill(Energy1);
                      getStatistics().getHisto1D("Energy2_TOT")->Fill(Energy2);
                      getStatistics().getHisto1D("Energy3_TOT")->Fill(Energy3);

                      //Calculation of the constructed annihillation plane from the center of the geometry

                      double DistfromSurface = CalDistofSurface(pr1, pr2, pr3, Center);
                      getStatistics().getHisto1D("DistancefromSurface")->Fill(DistfromSurface);

                      if (DistfromSurface <= 3.0) {


                    getStatistics().getHisto2D("AngleDistribution_01_Dist")->Fill(Angle12, Angle23);
			 getStatistics().getHisto2D("Angle3D_Dist")->Fill(Angle3D.at(1).first + Angle3D.at(0).first, Angle3D.at(1).first - Angle3D.at(0).first);

                        getStatistics().getHisto1D("DistancefromSurface_less5")->Fill(DistfromSurface);

                        getStatistics().getHisto2D("Dalitz_Energy_12_Dist")->Fill(Energy1, Energy2);
                        getStatistics().getHisto2D("Dalitz_Energy_23_Dist")->Fill(Energy2, Energy3);
                        getStatistics().getHisto2D("Dalitz_Energy_31_Dist")->Fill(Energy3, Energy1);
                        getStatistics().getHisto1D("Energy1_Dist")->Fill(Energy1);
                        getStatistics().getHisto1D("Energy2_Dist")->Fill(Energy2);
                        getStatistics().getHisto1D("Energy3_Dist")->Fill(Energy3);

                        //Emission Time Average & Difference
                        std::vector < double > TOF;
                        TOF.push_back(pr1TOF);
                        TOF.push_back(pr2TOF);
                        TOF.push_back(pr3TOF);

                        std::sort(TOF.begin(), TOF.begin() + 3);
                        double t3t1 = (TOF[2] - TOF[0]);
                        getStatistics().getHisto1D("TOF_Difference_t3t1")->Fill(t3t1);
                        getStatistics().getHisto1D("TOF_Difference_avrg")->Fill(Scat_t1 - TOF[0]);
                        getStatistics().getHisto1D("TOF_Difference_avrg")->Fill(Scat_t1 - TOF[1]);
                        getStatistics().getHisto1D("TOF_Difference_avrg")->Fill(Scat_t1 - TOF[2]);

                        if (fabs(Scat_t1 - TOF[0]) <= 2.0 && fabs(Scat_t1 - TOF[1]) <= 2.0 && fabs(Scat_t1 - TOF[2]) <= 2.0) {

                    getStatistics().getHisto2D("AngleDistribution_01_ET")->Fill(Angle12, Angle23);
			 getStatistics().getHisto2D("Angle3D_ET")->Fill(Angle3D.at(1).first + Angle3D.at(0).first, Angle3D.at(1).first - Angle3D.at(0).first);


                          getStatistics().getHisto1D("TOF_Difference_avrg_Cut_2ns")->Fill(Scat_t1 - TOF[0]);
                          getStatistics().getHisto1D("TOF_Difference_avrg_Cut_2ns")->Fill(Scat_t1 - TOF[1]);
                          getStatistics().getHisto1D("TOF_Difference_avrg_Cut_2ns")->Fill(Scat_t1 - TOF[2]);

                          //Energy Spectra after the Chi Square cut

                          getStatistics().getHisto2D("Dalitz_Energy_12_ET")->Fill(Energy1, Energy2);
                          getStatistics().getHisto2D("Dalitz_Energy_23_ET")->Fill(Energy2, Energy3);
                          getStatistics().getHisto2D("Dalitz_Energy_31_ET")->Fill(Energy3, Energy1);
                          getStatistics().getHisto1D("Energy1_ET")->Fill(Energy1);
                          getStatistics().getHisto1D("Energy2_ET")->Fill(Energy2);
                          getStatistics().getHisto1D("Energy3_ET")->Fill(Energy3);

                          //3D Angle Cut 	
                          if ((Angle3D.at(1).first + Angle3D.at(0).first) >= 190.0) {

                    getStatistics().getHisto2D("AngleDistribution_01_Angle")->Fill(Angle12, Angle23);
                            getStatistics().getHisto2D("Angle3D_190")->Fill(Angle3D.at(1).first + Angle3D.at(0).first, Angle3D.at(1).first - Angle3D.at(0).first);

                            //Energy Spectra after the 3D Angle cut
                            getStatistics().getHisto2D("Dalitz_Energy_12_Angle")->Fill(Energy1, Energy2);
                            getStatistics().getHisto2D("Dalitz_Energy_23_Angle")->Fill(Energy2, Energy3);
                            getStatistics().getHisto2D("Dalitz_Energy_31_Angle")->Fill(Energy3, Energy1);
                            getStatistics().getHisto1D("Energy1_Angle")->Fill(Energy1);
                            getStatistics().getHisto1D("Energy2_Angle")->Fill(Energy2);
                            getStatistics().getHisto1D("Energy3_Angle")->Fill(Energy3);

                    //Sorting of Calculated Energies   

		    vector <pair<double,JPetHit>> Energy_Vector;
                    Energy_Vector.push_back({Energy1, pr1});
                    Energy_Vector.push_back({Energy2, pr2});
                    Energy_Vector.push_back({Energy3, pr3});
                    std::sort(Energy_Vector.begin(), Energy_Vector.end(), comparison);
			
	//Calculation of Expectation Value

	/*




                            if (Scat_Ordering_Vec.at(0).second.first.getScintillator().getID() == Energy_Vector.at(2).second.getScintillator().getID()) {

                              double ExpecValue1 = CalExpecValue(Scat_Ordering_Vec.at(0).second.first, Scat_Ordering_Vec.at(0).second.second, Energy_Vector.at(1).second, Center);

               getStatistics().getHisto1D(Form("ExpecValue1_Y_Pos_%f", Y_Pos))->Fill(ExpecValue1);
            getStatistics().getHisto1D(Form("ExpecValue_Y_Pos_%f", Y_Pos))->Fill(ExpecValue1);

                            } else if (Scat_Ordering_Vec.at(0).second.first.getScintillator().getID() == Energy_Vector.at(1).second.getScintillator().getID()) {

                              double ExpecValue2 = CalExpecValue(Scat_Ordering_Vec.at(0).second.first, Scat_Ordering_Vec.at(0).second.second, Energy_Vector.at(2).second, Center);
            
	    getStatistics().getHisto1D(Form("ExpecValue2_Y_Pos_%f", Y_Pos))->Fill(ExpecValue2);
            getStatistics().getHisto1D(Form("ExpecValue_Y_Pos_%f", Y_Pos))->Fill(ExpecValue2);
                            
			   } else if (Scat_Ordering_Vec.at(0).second.first.getScintillator().getID() == Energy_Vector.at(0).second.getScintillator().getID()) {

                              double ExpecValue3 = CalExpecValue(Scat_Ordering_Vec.at(0).second.first, Scat_Ordering_Vec.at(0).second.second,Energy_Vector.at(2).second, Center);
                             
 	getStatistics().getHisto1D(Form("ExpecValue3_Y_Pos_%f", Y_Pos))->Fill(ExpecValue3);
 	getStatistics().getHisto1D(Form("ExpecValue_Y_Pos_%f", Y_Pos))->Fill(ExpecValue3);
				


			*/



        if (Scat_Ordering_Vec.at(0).second.first.getScintillator().getID() == Energy_Vector.at(2).second.getScintillator().getID()) {

                              double ExpecValue1 = CalExpecValue(Scat_Ordering_Vec.at(0).second.first, Scat_Ordering_Vec.at(0).second.second, Energy_Vector.at(1).second, Center);

               getStatistics().getHisto1D("ExpecValue1")->Fill(ExpecValue1);
            getStatistics().getHisto1D("ExpecValue")->Fill(ExpecValue1);

                            } else if (Scat_Ordering_Vec.at(0).second.first.getScintillator().getID() == Energy_Vector.at(1).second.getScintillator().getID()) {

                              double ExpecValue2 = CalExpecValue(Scat_Ordering_Vec.at(0).second.first, Scat_Ordering_Vec.at(0).second.second, Energy_Vector.at(2).second, Center);
            
	    getStatistics().getHisto1D("ExpecValue2")->Fill(ExpecValue2);
            getStatistics().getHisto1D("ExpecValue")->Fill(ExpecValue2);
                            
			   } else if (Scat_Ordering_Vec.at(0).second.first.getScintillator().getID() == Energy_Vector.at(0).second.getScintillator().getID()) {

                              double ExpecValue3 = CalExpecValue(Scat_Ordering_Vec.at(0).second.first, Scat_Ordering_Vec.at(0).second.second,Energy_Vector.at(2).second, Center);
                             
 	getStatistics().getHisto1D("ExpecValue3")->Fill(ExpecValue3);
 	getStatistics().getHisto1D("ExpecValue")->Fill(ExpecValue3);

					



		              // }
    				
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

		

		}  //For the for loop on X - Pos

	    
          

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
