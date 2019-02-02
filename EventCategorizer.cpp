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

EventCategorizer::EventCategorizer(const char* name): JPetUserTask(name) {}

bool EventCategorizer::init()
{

  INFO("Event categorization started.");
  INFO("Looking at two hit Events on Layer 1&2 only - creating only control histograms");

  fOutputEvents = new JPetTimeWindow("JPetEvent");

  if (fSaveControlHistos) {



    getStatistics().createHistogram( new TH1F("Hits", "Hits Distribution",
                                     10, 0.5, 10.5) );
    getStatistics().getHisto1D("Hits")->GetXaxis()->SetTitle("Hist Distribution");
    getStatistics().getHisto1D("Hits")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("TOT", "TOT",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("TOT_first", "TOT for first Hit",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_first")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_first")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("TOT_second", "TOT for second Hit",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_second")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_second")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("TOT_third", "TOT for third Hit",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_third")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_third")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("TOT_fourth", "TOT for fourth Hit",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_fourth")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_fourth")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram( new TH2F("ScinID_vs_TOT", "ScinID_vs_TOT",
                                     1100, -5.5, 105.5,
                                     192, -0.5, 192.5 ));
    getStatistics().getHisto2D("ScinID_vs_TOT")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto2D("ScinID_vs_TOT")->GetYaxis()->SetTitle("Scintillator ID");

    getStatistics().createHistogram( new TH2F("DeltaT_vs_ScinID_big", "Time difference B-A vs scintillator ID, big range",
                                     192, 0.5, 192.5,
                                     2000, -100, 100 ) );
    getStatistics().getHisto2D("DeltaT_vs_ScinID_big")->GetXaxis()->SetTitle("Scintillator ID");
    getStatistics().getHisto2D("DeltaT_vs_ScinID_big")->GetYaxis()->SetTitle("Time difference BA [ns]");


    getStatistics().createHistogram( new TH1F("ScinID", "Scintillator ID Distribution",
                                     192, -0.5, 192.5) );
    getStatistics().getHisto1D("ScinID")->GetXaxis()->SetTitle("Scintillator ID");
    getStatistics().getHisto1D("ScinID")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("ScinID_After_All_Cuts", "ScinID_After_All_Cuts",
                                     192, -0.5, 192.5) );
    getStatistics().getHisto1D("ScinID")->GetXaxis()->SetTitle("Scintillator ID");
    getStatistics().getHisto1D("ScinID")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("TimeDiff", "Time Difference Distribution",
                                     750, -10, 10) );
    getStatistics().getHisto1D("TimeDiff")->GetXaxis()->SetTitle("Time Difference BA [ns]");
    getStatistics().getHisto1D("TimeDiff")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH2F("ScinID_vs_TOT_1", "ScinID_vs_TOT_1",
                                     1100, -5.5, 105.5,
                                     192, -0.5, 192.5 ));
    getStatistics().getHisto2D("ScinID_vs_TOT_1")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto2D("ScinID_vs_TOT_1")->GetYaxis()->SetTitle("Scintillator ID");



    getStatistics().createHistogram( new TH2F("ScinID_vs_TOT_2", "ScinID_vs_TOT_2",
                                     1100, -5.5, 105.5,
                                     192, -0.5, 192.5 ));
    getStatistics().getHisto2D("ScinID_vs_TOT_2")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto2D("ScinID_vs_TOT_2")->GetYaxis()->SetTitle("Scintillator ID");



    getStatistics().createHistogram( new TH2F("ScinID_vs_TOT_3", "ScinID_vs_TOT_3",
                                     1100, -5.5, 105.5,
                                     192, -0.5, 192.5 ));
    getStatistics().getHisto2D("ScinID_vs_TOT_3")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto2D("ScinID_vs_TOT_3")->GetYaxis()->SetTitle("Scintillator ID");


    getStatistics().createHistogram( new TH2F("ScinID_vs_TOT_4", "ScinID_vs_TOT_4",
                                     1100, -5.5, 105.5,
                                     192, -0.5, 192.5 ));
    getStatistics().getHisto2D("ScinID_vs_TOT_4")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto2D("ScinID_vs_TOT_4")->GetYaxis()->SetTitle("Scintillator ID");



    getStatistics().createHistogram( new TH1F("TOT_first_Cut", "TOT_first_Cut",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_first_Cut")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_first_Cut")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("TOT_second_Cut", "TOT_second_Cut",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_second_Cut")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_second_Cut")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("TOT_third_Cut", "TOT_third_Cut",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_third_Cut")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_third_Cut")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("TOT_fourth_Cut", "TOT_fourth_Cut",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_fourth_Cut")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_fourth_Cut")->GetYaxis()->SetTitle("Counts");




    getStatistics().createHistogram(new TH2F("Angle1+0_Angle1-0_123", "Angle1+0_Angle1-0_123", 360, -0.5, 359.5, 360, -0.5, 359.5));
    getStatistics().getHisto2D("Angle1+0_Angle1-0_123")->GetXaxis()->SetTitle("Angle 1+0 [deg]");
    getStatistics().getHisto2D("Angle1+0_Angle1-0_123")->GetYaxis()->SetTitle("Angle 1-0 [deg]");


    getStatistics().createHistogram(new TH2F("Angle1+0_Angle1-0_124", "Angle1+0_Angle1-0_124", 360, -0.5, 359.5, 360, -0.5, 359.5));
    getStatistics().getHisto2D("Angle1+0_Angle1-0_124")->GetXaxis()->SetTitle("Angle 1+0 [deg]");
    getStatistics().getHisto2D("Angle1+0_Angle1-0_124")->GetYaxis()->SetTitle("Angle 1-0 [deg]");





    getStatistics().createHistogram(new TH2F("Angle1+0_Angle1-0_123_Cut", "Angle1+0_Angle1-0_123_Cut", 360, -0.5, 359.5, 360, -0.5, 359.5));
    getStatistics().getHisto2D("Angle1+0_Angle1-0_123_Cut")->GetXaxis()->SetTitle("Angle 1+0 [deg]");
    getStatistics().getHisto2D("Angle1+0_Angle1-0_123_Cut")->GetYaxis()->SetTitle("Angle 1-0 [deg]");


    getStatistics().createHistogram(new TH2F("Angle1+0_Angle1-0_124_Cut", "Angle1+0_Angle1-0_124_Cut", 360, -0.5, 359.5, 360, -0.5, 359.5));
    getStatistics().getHisto2D("Angle1+0_Angle1-0_124_Cut")->GetXaxis()->SetTitle("Angle 1+0 [deg]");
    getStatistics().getHisto2D("Angle1+0_Angle1-0_124_Cut")->GetYaxis()->SetTitle("Angle 1-0 [deg]");




    getStatistics().createHistogram( new TH1F("timeScat31", "timeScat31" , 10000, -200.5, 200.5 ));
    getStatistics().getHisto1D("timeScat31")->GetXaxis()->SetTitle("timeScat31 [ns]");
    getStatistics().getHisto1D("timeScat31")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("timeScat32", "timeScat32" , 10000, -200.5, 200.5 ));
    getStatistics().getHisto1D("timeScat32")->GetXaxis()->SetTitle("timeScat32 [ns]");
    getStatistics().getHisto1D("timeScat32")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("timeScat41", "timeScat41" , 10000, -200.5, 200.5 ));
    getStatistics().getHisto1D("timeScat41")->GetXaxis()->SetTitle("timeScat41 [ns]");
    getStatistics().getHisto1D("timeScat41")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("timeScat42", "timeScat42" , 10000, -200.5, 200.5 ));
    getStatistics().getHisto1D("timeScat42")->GetXaxis()->SetTitle("timeScat42 [ns]");
    getStatistics().getHisto1D("timeScat42")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram(new TH2F("Scatter_of_3_from_1_and_2", "Scatter_of_3_from_1_and_2", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2")->GetXaxis()->SetTitle("Scatter Time 3-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2")->GetYaxis()->SetTitle("Scatter Time 3-1 [ns]");


    getStatistics().createHistogram(new TH2F("Scatter_of_4_from_1_and_2", "Scatter_of_4_from_1_and_2", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2")->GetXaxis()->SetTitle("Scatter Time 4-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2")->GetYaxis()->SetTitle("Scatter Time 4-1 [ns]");


    getStatistics().createHistogram( new TH1F("Angle_All", "Angle_All" , 360, -0.5, 360.5 ));
    getStatistics().getHisto1D("Angle_All")->GetXaxis()->SetTitle("Angle_All [deg]");
    getStatistics().getHisto1D("Angle_All")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("Angle_All_Cut", "Angle_All_Cut" , 360, -0.5, 360.5 ));
    getStatistics().getHisto1D("Angle_All_Cut")->GetXaxis()->SetTitle("Angle_All_Cut [deg]");
    getStatistics().getHisto1D("Angle_All_Cut")->GetYaxis()->SetTitle("Counts");




    getStatistics().createHistogram(new TH2F("Scatter_of_3_from_1_and_2_AngleCut", "Scatter_of_3_from_1_and_2_AngleCut", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_AngleCut")->GetXaxis()->SetTitle("Scatter Time 3-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_AngleCut")->GetYaxis()->SetTitle("Scatter Time 3-1 [ns]");


    getStatistics().createHistogram(new TH2F("Scatter_of_4_from_1_and_2_AngleCut", "Scatter_of_4_from_1_and_2_AngleCut", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_AngleCut")->GetXaxis()->SetTitle("Scatter Time 4-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_AngleCut")->GetYaxis()->SetTitle("Scatter Time 4-1 [ns]");




    getStatistics().createHistogram(new TH2F("Scatter_of_3_from_1_and_2_For_32_and_41", "Scatter_of_3_from_1_and_2_For_32_and_41", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_For_32_and_41")->GetXaxis()->SetTitle("Scatter Time 3-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_For_32_and_41")->GetYaxis()->SetTitle("Scatter Time 3-1 [ns]");


    getStatistics().createHistogram(new TH2F("Scatter_of_4_from_1_and_2_For_32_and_41", "Scatter_of_4_from_1_and_2_For_32_and_41", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_For_32_and_41")->GetXaxis()->SetTitle("Scatter Time 4-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_For_32_and_41")->GetYaxis()->SetTitle("Scatter Time 4-1 [ns]");



    getStatistics().createHistogram(new TH2F("Scatter_of_3_from_1_and_2_For_31_and_42", "Scatter_of_3_from_1_and_2_For_31_and_42", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_For_31_and_42")->GetXaxis()->SetTitle("Scatter Time 3-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_For_31_and_42")->GetYaxis()->SetTitle("Scatter Time 3-1 [ns]");


    getStatistics().createHistogram(new TH2F("Scatter_of_4_from_1_and_2_For_31_and_42", "Scatter_of_4_from_1_and_2_For_31_and_42", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_For_31_and_42")->GetXaxis()->SetTitle("Scatter Time 4-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_For_31_and_42")->GetYaxis()->SetTitle("Scatter Time 4-1 [ns]");






    getStatistics().createHistogram( new TH1F("Phi20_23", "Phi20_23" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi20_23")->GetXaxis()->SetTitle("Phi20_23 [deg]");
    getStatistics().getHisto1D("Phi20_23")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("Phi10_14", "Phi10_14" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi10_14")->GetXaxis()->SetTitle("Phi10_14 [deg]");
    getStatistics().getHisto1D("Phi10_14")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("Phi_1", "Phi_1" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi_1")->GetXaxis()->SetTitle("Phi_1 [deg]");
    getStatistics().getHisto1D("Phi_1")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("Phi_2", "Phi_2" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi_2")->GetXaxis()->SetTitle("Phi_2 [deg]");
    getStatistics().getHisto1D("Phi_2")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram(new TH2F("Phi10_14_vs_Phi20_23", "Phi10_14_vs_Phi20_23", 770, -385.5, 385.5, 770, -385.5, 385.5));
    getStatistics().getHisto2D("Phi10_14_vs_Phi20_23")->GetXaxis()->SetTitle("Phi10_14 [deg]");
    getStatistics().getHisto2D("Phi10_14_vs_Phi20_23")->GetYaxis()->SetTitle("Phi20_23 [deg]");


    getStatistics().createHistogram(new TH2F("Phi1_vs_Phi2", "Phi1_vs_Phi2", 180, 0.0, 180.0, 180, 0.0, 180.0));
    getStatistics().getHisto2D("Phi1_vs_Phi2")->GetXaxis()->SetTitle("Phi1 [deg]");
    getStatistics().getHisto2D("Phi1_vs_Phi2")->GetYaxis()->SetTitle("Phi2 [deg]");


    getStatistics().createHistogram( new TH1F("Phi20_24", "Phi20_24" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi20_24")->GetXaxis()->SetTitle("Phi20_24 [deg]");
    getStatistics().getHisto1D("Phi20_24")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("Phi10_13", "Phi10_13" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi10_13")->GetXaxis()->SetTitle("Phi10_13 [deg]");
    getStatistics().getHisto1D("Phi10_13")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram(new TH2F("Phi10_13_vs_Phi20_24", "Phi10_13_vs_Phi20_24", 770, -385.5, 385.5, 770, -385.5, 385.5));
    getStatistics().getHisto2D("Phi10_13_vs_Phi20_24")->GetXaxis()->SetTitle("Phi10_13 [deg]");
    getStatistics().getHisto2D("Phi10_13_vs_Phi20_24")->GetYaxis()->SetTitle("Phi20_24 [deg]");




    getStatistics().createHistogram( new TH1F("theta", "theta" , 180, 0.0, 180.0 ));
    getStatistics().getHisto1D("theta")->GetXaxis()->SetTitle("theta [deg]");
    getStatistics().getHisto1D("theta")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram( new TH1F("theta1", "theta1" , 38500, -5.5, 380.5 ));
    getStatistics().getHisto1D("theta1")->GetXaxis()->SetTitle("theta1 [deg]");
    getStatistics().getHisto1D("theta1")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram( new TH1F("theta2", "theta2" , 38500, -5.5, 380.5 ));
    getStatistics().getHisto1D("theta2")->GetXaxis()->SetTitle("theta2 [deg]");
    getStatistics().getHisto1D("theta2")->GetYaxis()->SetTitle("Counts");





    getStatistics().createHistogram( new TH1F("theta_Cut", "theta_Cut" , 180, 0.0, 180.0 ));
    getStatistics().getHisto1D("theta_Cut")->GetXaxis()->SetTitle("theta_Cut [deg]");
    getStatistics().getHisto1D("theta_Cut")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram( new TH1F("theta1_Cut", "theta1_Cut" , 38500, -5.5, 380.5 ));
    getStatistics().getHisto1D("theta1_Cut")->GetXaxis()->SetTitle("theta1_Cut [deg]");
    getStatistics().getHisto1D("theta1_Cut")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram( new TH1F("theta2_Cut", "theta2_Cut" , 38500, -5.5, 380.5 ));
    getStatistics().getHisto1D("theta2_Cut")->GetXaxis()->SetTitle("theta2_Cut [deg]");
    getStatistics().getHisto1D("theta2_Cut")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH2F("Phi10_14_vs_Phi20_23_Cut", "Phi10_14_vs_Phi20_23_Cut", 770, -385.5, 385.5, 770, -385.5, 385.5));
    getStatistics().getHisto2D("Phi10_14_vs_Phi20_23_Cut")->GetXaxis()->SetTitle("Phi10_14 [deg]");
    getStatistics().getHisto2D("Phi10_14_vs_Phi20_23_Cut")->GetYaxis()->SetTitle("Phi20_23 [deg]");


    getStatistics().createHistogram(new TH2F("Phi1_vs_Phi2_Cut", "Phi1_vs_Phi2_Cut", 180, 0.0, 180.0, 180, 0.0, 180.0));
    getStatistics().getHisto2D("Phi1_vs_Phi2_Cut")->GetXaxis()->SetTitle("Phi1 [deg]");
    getStatistics().getHisto2D("Phi1_vs_Phi2_Cut")->GetYaxis()->SetTitle("Phi2 [deg]");


    getStatistics().createHistogram(new TH2F("Phi10_13_vs_Phi20_24_Cut", "Phi10_13_vs_Phi20_24_Cut", 770, -385.5, 385.5, 770, -385.5, 385.5));
    getStatistics().getHisto2D("Phi10_13_vs_Phi20_24_Cut")->GetXaxis()->SetTitle("Phi10_13 [deg]");
    getStatistics().getHisto2D("Phi10_13_vs_Phi20_24_Cut")->GetYaxis()->SetTitle("Phi20_14 [deg]");



    getStatistics().createHistogram(new TH2F("Phi1_vs_Phi2_Cut_Cut", "Phi1_vs_Phi2_Cut_Cut", 180, 0.0, 180.0, 180, 0.0, 180.0));
    getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_Cut")->GetXaxis()->SetTitle("Phi1_Cut_Cut [deg]");
    getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_Cut")->GetYaxis()->SetTitle("Phi2_Cut_Cut [deg]");




    getStatistics().createHistogram( new TH1F("Phi20_23_Cut", "Phi20_23_Cut" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi20_23_Cut")->GetXaxis()->SetTitle("Phi20_23_Cut [deg]");
    getStatistics().getHisto1D("Phi20_23_Cut")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("Phi10_14_Cut", "Phi10_14_Cut" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi10_14_Cut")->GetXaxis()->SetTitle("Phi10_14_Cut [deg]");
    getStatistics().getHisto1D("Phi10_14_Cut")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("Phi_1_Cut", "Phi_1_Cut" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi_1_Cut")->GetXaxis()->SetTitle("Phi_1_Cut [deg]");
    getStatistics().getHisto1D("Phi_1_Cut")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("Phi_2_Cut", "Phi_2_Cut" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi_2_Cut")->GetXaxis()->SetTitle("Phi_2_Cut [deg]");
    getStatistics().getHisto1D("Phi_2_Cut")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("Phi20_24_Cut", "Phi20_24_Cut" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi20_24_Cut")->GetXaxis()->SetTitle("Phi20_24_Cut [deg]");
    getStatistics().getHisto1D("Phi20_24_Cut")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("Phi10_13_Cut", "Phi10_13_Cut" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi10_13_Cut")->GetXaxis()->SetTitle("Phi10_13_Cut [deg]");
    getStatistics().getHisto1D("Phi10_13_Cut")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("theta_Cut_Cut", "theta_Cut_Cut" , 180, 0.0, 180.0 ));
    getStatistics().getHisto1D("theta_Cut_Cut")->GetXaxis()->SetTitle("theta_Cut_Cut [deg]");
    getStatistics().getHisto1D("theta_Cut_Cut")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("theta1_Cut_Cut", "theta1_Cut_Cut" , 38500, -5.5, 380.5 ));
    getStatistics().getHisto1D("theta1_Cut_Cut")->GetXaxis()->SetTitle("theta1_Cut_Cut [deg]");
    getStatistics().getHisto1D("theta1_Cut_Cut")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram( new TH1F("theta2_Cut_Cut", "theta2_Cut_Cut" , 38500, -5.5, 380.5 ));
    getStatistics().getHisto1D("theta2_Cut_Cut")->GetXaxis()->SetTitle("theta2_Cut_Cut [deg]");
    getStatistics().getHisto1D("theta2_Cut_Cut")->GetYaxis()->SetTitle("Counts");




  }



  return true;
}

//Calculate the TOT

double CalcTOT(const JPetHit& Hit)
{


  double TOT = 0.;
  double TOT_A = 0.;
  double TOT_B = 0.;

  auto lead_times_A = Hit.getSignalA().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Leading);
  auto trail_times_A = Hit.getSignalA().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Trailing);
  auto lead_times_B =  Hit.getSignalB().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Leading);
  auto trail_times_B = Hit.getSignalB().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Trailing);


  for (auto& thr_time_pair : lead_times_A) {
    int thr = thr_time_pair.first;
    if (trail_times_A.count(thr) > 0 ) {
      TOT_A = TOT_A + trail_times_A[thr] - lead_times_A[thr];
    }
  }

  for (auto& thr_time_pair : lead_times_B) {
    int thr = thr_time_pair.first;
    if ( trail_times_B.count(thr) > 0 ) {

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



Bool_t comparison(const pair < double, JPetHit > & a,
  const pair < double, JPetHit > & b) {
  return a.first < b.first;
}



bool EventCategorizer::exec()
{

  if (auto timeWindow = dynamic_cast<const JPetTimeWindow* const>(fEvent)) {
    uint n = timeWindow->getNumberOfEvents();
    for (uint i = 0; i < n; ++i) {

      const auto& event = dynamic_cast<const JPetEvent&>(timeWindow->operator[](i));

      if (event.getHits().size() == 4) {

	TVector3 Center(0.0, 0.0, 0.0);

        JPetHit Hit_1 = event.getHits().at(0);
        JPetHit Hit_2 = event.getHits().at(1);
        JPetHit Hit_3 = event.getHits().at(2);
        JPetHit Hit_4 = event.getHits().at(3);

	double TOF_1 = CalcTOF( Hit_1, Center);
        double TOF_2 = CalcTOF( Hit_2, Center);
	double TOF_3 = CalcTOF( Hit_3, Center);
	double TOF_4 = CalcTOF( Hit_4, Center);

  	vector <pair<double,JPetHit>> TOF_vec;
        TOF_vec.push_back({TOF_1, Hit_1});
	TOF_vec.push_back({TOF_2, Hit_2});
	TOF_vec.push_back({TOF_3, Hit_3});
	TOF_vec.push_back({TOF_4, Hit_4});

        std::sort(TOF_vec.begin(), TOF_vec.end(), comparison);















	auto ID_1 = Hit_1.getScintillator().getID();	
        auto ID_2 = Hit_2.getScintillator().getID();	
	auto ID_3 = Hit_3.getScintillator().getID();
	auto ID_4 = Hit_4.getScintillator().getID();

	auto TD_1 = Hit_1.getTimeDiff() / 1000.0;
	auto TD_2 = Hit_2.getTimeDiff() / 1000.0;
	auto TD_3 = Hit_3.getTimeDiff() / 1000.0;
	auto TD_4 = Hit_4.getTimeDiff() / 1000.0;

	double TOT_1 = CalcTOT( Hit_1 );
        double TOT_2 = CalcTOT( Hit_2 );
	double TOT_3 = CalcTOT( Hit_3 );
	double TOT_4 = CalcTOT( Hit_4 );


	double Angle12 = Calc3DAngle(Hit_1, Hit_2, Center);
        double Angle23 = Calc3DAngle(Hit_2, Hit_3, Center);
        double Angle34 = Calc3DAngle(Hit_3, Hit_4, Center);
	double Angle13 = Calc3DAngle(Hit_1, Hit_3, Center);
        double Angle14 = Calc3DAngle(Hit_1, Hit_4, Center);
        double Angle24 = Calc3DAngle(Hit_2, Hit_4, Center);





			}

                    }

                  } 

 else {
    return false;
  }
  return true;
}



bool EventCategorizer::terminate()
{

  INFO("More than one hit Events done. Writing conrtrol histograms.");
  return true;
}

void EventCategorizer::saveEvents(const vector<JPetEvent>& events)
{
  for (const auto& event : events) {
    fOutputEvents->add<JPetEvent>(event);
  }
}
