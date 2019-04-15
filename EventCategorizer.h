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
 *  @file EventCategorizer.h
 */

#ifndef EVENTCATEGORIZER_H
#define EVENTCATEGORIZER_H

#include <vector>
#include <utility>
#include <map>
#include <JPetUserTask/JPetUserTask.h>
#include <JPetHit/JPetHit.h>
#include <JPetEvent/JPetEvent.h>

class JPetWriter;

#ifdef __CINT__
#	define override
#endif

class EventCategorizer : public JPetUserTask{
public:
	EventCategorizer(const char * name);
	virtual ~EventCategorizer(){}
	virtual bool init() override;
	virtual bool exec() override;
	virtual bool terminate() override;


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




/*
double  AngleMix(int count, double Angle12, double Angle23, double Angle31)
	{

	static double arr[2];
	
  	if(count%6 == 0){
                
	arr[0] = Angle12;
	arr[1] = Angle23;
     
	return arr;

	  }


        else if(count%5 == 0){
      
          
	arr[0] = Angle12;
	arr[1] = Angle31;
                
           
	return arr;

	    }


        else if(count%4 == 0){ 

               
	arr[0] = Angle23;
	arr[1] = Angle31;

	return arr;

                }


        else if(count%3 == 0){


	arr[0] = Angle23;
 	arr[1] = Angle12;

	return arr;

                }


         else if(count%2 == 0){ 

              
	arr[0] = Angle31;
	arr[1] = Angle12;
	
	return arr;
                
                }


        else if(cout%1 == 0){                
          
	arr[0] = Angle31;
	arr[1] = Angle23;

	return arr;

                }





	}

*/







protected:
	void saveEvents(const std::vector<JPetEvent>& event);
	bool fSaveControlHistos = true;

	int f_event_counter = 0;
};
#endif /*  !EVENTCATEGORIZER_H */
