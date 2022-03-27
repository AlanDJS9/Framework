#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include "Scene01.h"
#include "Printer.h"
using namespace std;


void Printer::Print(const vector<float>& time,
					const vector<float>& angacc
					,const vector<float>& angvel
					,const vector<float>& angdis
					,const vector<float>& forcex
					,const vector<float>& forcey
					,const vector<float>& accelx
					,const vector<float>& accely
					,const vector<float>& velx
					,const vector<float>& vely
					,const vector<float>& posx
					, const vector<float>& posy)
{
	fstream myFile;

	myFile.open("output.csv", ios::out);
	if (myFile.is_open()) {

		myFile 
			<< "Time" << "," 
			<< "Angular Acc" << "," 
			<< "Angular Vel" << ","
			<< "Angular Dis" << ","
			<< "Force X" << ","
			<< "Force Y" << ","
			<< "Accel X" << ","
			<< "Accel Y" << ","
			<< "Vel X" << ","
			<< "Vel Y" << ","
			<< "Pos X" << ","
			<< "Pos Y" << endl;

		for (int i = 0; i < time.size(); i++) {
			myFile 
				<< time.at(i) << "," 
				<< angacc.at(i) << ","
				<< angvel.at(i) << ","
				<< angdis.at(i) << ","
				<< forcex.at(i) << ","
				<< forcey.at(i) << ","
				<< accelx.at(i) << ","
				<< accely.at(i) << ","
				<< velx.at(i) << ","
				<< vely.at(i) << ","
				<< posx.at(i) << ","
				<< posy.at(i) << endl;
		}
		
		myFile.close();
	}
}

