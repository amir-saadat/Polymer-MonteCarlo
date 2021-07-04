
class Polymer {
public:
//	Polymer() {}
	//Polymer(vector<Bead* > a) { pbeads = a; }
//	~Polymer() {}
public:
	void addBead(Bead* _bead) { beads.push_back(_bead); }


public:
	Bead* getBead(int );
	void bead_of_polymerMove(int );
	void bead_of_polymerBack(int );
	double distance(int,int);
	bool Potential_in_chain(int );
	
private:
	vector<Bead* > beads;
	
};