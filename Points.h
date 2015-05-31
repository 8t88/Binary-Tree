#include<iostream>
#include<fstream>
/*@brief base class to form Points

		This class takes in two double values the x and y positions and declares  
	get_position
*/
class Point2D {
public:	
	Point2D(double initial_x, double initial_y) : x(initial_x), y(initial_y) {};
	double getx(){return x;};
	double gety(){return y;};
	bool operator==(Point2D b){if(x*b.gety()==y*b.getx()) return true; return false;};
	virtual ~Point2D() { 	
	};
private:
	double x;
	double y;
	friend class PointOrderx;
};

/*@brief base class to set policy

		This class sets the () operator to compare points by their x values

*/
class PointOrderx{
public:
	bool operator()(Point2D a,Point2D b){
		return a.getx()<b.getx();
	}
};

/*@brief base class to set policy

		This class sets the () operator to compare points by their x values
*/
class PointOrdery{
public:
	bool operator()(Point2D& a,Point2D& b){
		return a.gety()<b.gety();
	}
};

/**
	This is the overloaded << operator that prints out a Point2D object

	@param out is the output stream
	@param a is the Point2D being printed
	@return the output stream that has been modified
*/
std::ostream& operator<<(std::ostream& out, Point2D a){
	out<<"("<<a.getx()<<","<<a.gety()<<")";
	return out;
}

