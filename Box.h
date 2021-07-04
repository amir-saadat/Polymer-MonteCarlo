class Box {
public:
	Box() { }
	Box(double _x,double _y,double _z) { x = _x; y = _y; z = _z; }
	~Box() { }
public:
	void setBoxDimensions(double _x,double _y,double _z) { x = _x; y = _y; z = _z; }
	void populateWithPolymers(vector<Polymer* > _polymer) { polymers = _polymer; } 
	void setBoxMaxStepSize(double _max) { max_box_step_size = _max; }
public:
	int move(int);
	bool Potential_between_chains(int,int,int);
	bool CheckAngle(int,int,int);
	double distance(int, int, int, int );
	double angle(int, int, int, int);
public:
	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }

private:
	double rand();
private:
	double x,y,z;
	double x_old,y_old,z_old;
	double max_box_step_size;
	Random random;
	vector<Polymer* > polymers;
};