class Bead {
public:
	
	void setX(double _x) { x = _x; }
	void setY(double _y) { y = _y; }
	void setZ(double _z) { z = _z; }
	void setDiameter(double d) { diameter = d; }
	void setMaxStepSize(double s) { max_step_size = s; }
	void setEnergy(double e) { energy = e; }
public:
	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }
	double getDiameter() { return diameter; }
	double getEnergy() { return energy; }
public:
	void move(); 
	void goBack(); 
private:
	double x,y,z;
	double x_old,y_old,z_old; 
	double diameter;
	double max_step_size; 
	double energy;
	Random random;
	
};