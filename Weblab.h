// weblab.h
#ifndef WEBLAB_H
#define WEBLAB_H


class WebLab {
public:
	WebLab() { }
	~WebLab() { }
public:
	void setPosition(double,double,double);
	void setConnection(int,int);
	void setFileName(string name) { file_name = name; }
	void setIndex(int n) { num = n; }
	void openFile();
	void writeHeader(int);
	void writePosition(int,char,int,double,double,double);
	void writeConnection();
	void writeEnd();
	void closeFile() { fclose( stream ); }
private:
	string file_name;
	FILE* stream;
	int current, next;
	int num;
};
#endif
