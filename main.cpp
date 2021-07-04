#include <iostream>
#include <fstream> 
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;
#include "Random.h"
#include "Read.h" 
#include "Bead.h"
#include "Polymer.h"
#include "Box.h"
#include "Weblab.h"


int main (int argc, char* const argv[])
{
	const int total_number_of_steps = 500;
	const int number_of_beads = 100;
	const double bead_diameter = 1.0;
	const double max_step_size = 1.0;
	vector<Bead*> beads(number_of_beads);
	vector<double> line;
	Read read;
	read.setFileName("C:/Users/F & A/Documents/Wascana Workspaces/workspace/Polymer/start.txt");
	read.openFile();
	int i,j;
	for(i=0;i<number_of_beads;i++) {
		beads[i] = new Bead;
		line = read.getLine();
		beads[i]->setX(line[0]);
		beads[i]->setY(line[1]);
		beads[i]->setZ(line[2]);
		beads[i]->setDiameter(bead_diameter);
		beads[i]->setMaxStepSize(max_step_size);
	}
	read.closeFile();
	
	const int number_of_polymers = 10;
	const int number_of_beads_in_polymer = 10;
	vector<Polymer*> polymers(number_of_polymers);
	
	for(i=0;i<number_of_polymers;i++){
		polymers[i] = new Polymer;
		for(j=0;j<number_of_beads_in_polymer;j++){
			polymers[i]->addBead(beads[j+i*number_of_beads_in_polymer]);
		}
	}

	double box_x = 20.0;
	double box_y = 20.0;
	double box_z = 20.0;
	Box* box = new Box(box_x,box_y,box_z);
	box->populateWithPolymers( polymers );
	box->setBoxMaxStepSize(0.5);
	
	WebLab weblab;
	weblab.setFileName("movie.pdb");
	weblab.openFile();
	vector<char>chain(10);
	chain[0] = 'A';
	chain[1] = 'B';
	chain[2] = 'C';
	chain[3] = 'D';
	chain[4] = 'E';
	chain[5] = 'F';
	chain[6] = 'G';
	chain[7] = 'H';
	chain[8] = 'I';
	chain[9] = 'J';
	
	FILE* _stream;
	_stream = fopen("C:/Users/F & A/Documents/Wascana Workspaces/workspace/Polymer/finish.txt", "w" );
	
	Bead* temp;
	int l;
	
	for(i=0;i<total_number_of_steps;i++){
	
		box->move(number_of_beads_in_polymer);
		l=1;
		weblab.writeHeader(i);
		fprintf( _stream, "%d\n", i );
		fprintf( _stream, "%lf\t%lf\t%lf\n", box->getX(), box->getY(), box->getZ() );
		for(j=0;j<number_of_polymers;j++){
			for(int k=0;k<number_of_beads_in_polymer;k++){
				temp=polymers[j]->getBead(k);
				fprintf( _stream, "%lf\t", temp->getX() );
				fprintf( _stream, "%lf\t", temp->getY() );
				fprintf( _stream, "%lf\n", temp->getZ() );
				weblab.writePosition(l,chain[j],j,temp->getX(),temp->getY(),temp->getZ());
				l++;
			}
		}
		fprintf( _stream, "\n" );
		weblab.writeEnd();
	}
	fclose(_stream);
	weblab.closeFile();
	cout<< "finish"<<endl;
	return 0;
}
