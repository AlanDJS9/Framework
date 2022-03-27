#ifndef PRINTER_H
#define PRINTER_H


class Printer {
public:
	static void Print(
		const vector<float>& time
		,const vector<float>& angacc
		, const vector<float>& angvel
		, const vector<float>& angdis
		, const vector<float>& forcex
		, const vector<float>& forcey
		, const vector<float>& accelx
		, const vector<float>& accely
		, const vector<float>& velx
		, const vector<float>& vely
		, const vector<float>& posx
		, const vector<float>& posy

	);

};

#endif