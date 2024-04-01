#ifndef MAIN_H
#define MAIN_H

#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib> //stoi
#include<cstring> //strtok
using namespace std;
typedef pair <int,float> mem_unit; //int: memory index; float: memory value;
enum Operation
{
	addi,
	subi,
	addf,
	subf,
	mulf,
	load,
	store,
	beq,
	bne
}; //opcode

/********* dst, src, tgt *************/
class item
{
public:
	float value;
	int id;
	bool imme_flag;		//0 for register, 1 for immediate
	bool ready;			//0 for not, 1 for ready
	item();
};

/********* instruction buffer ********/

struct InstBuf
{
	int free;
	char inst[];
};

/*********** arf ****************/
template<typename T>
class ARF
{
public:
	int id;				//int_arf id is 1 ~ 100
	bool ready;
	T value;
	ARF():id(0),ready(0){};
};

/********** integral ARF ***********/
class IntARF
{
public:
	ARF<int> *table;
	int pointer;
	IntARF(int);
	~IntARF(){delete[]table;}
};

/*********** float point ARF ********/
class FpARF
{
public:
	ARF<float> *table;
	int pointer;
	FpARF(int);
	~FpARF(){delete[]table;}
};

/************** RAT ****************/
class RAT
{
public:
	int alias;			//alias of register, just store the id of alias;
	float value;
	RAT():value(0.0){};
};

/************* integral RAT **********/
class IntRAT
{
public:
	RAT *table;
	int pointer;
	IntRAT(int);
	~IntRAT(){delete[]table;}
};

/*************** float point RAT ********/
class FpRAT
{
public:
	RAT *table;
	int pointer;
	FpRAT(int);
	~FpRAT(){delete[]table;}
};


/****************** ROB ******************/
class ReOrderBuf_entry
{
public:
	int id;				//reorder buffer id is 201 ~ 400, 0 for available entry.
	int dst_id;			// dstination register id.
	float value;
	int cmt_flag;		// 0 for not commit, 1 for commit;	
 
	ReOrderBuf_entry():id(0),dst_id(0),value(0.0),cmt_flag(0){}
};

class ReOrderBuf
{
public:
	ReOrderBuf_entry *table;
	int head;
	int tail;
	int n;
	int size;

	int get_size();
	bool empty();
	bool full();
	
	ReOrderBuf(int);
	~ReOrderBuf(){delete[]table;}
};
class inst
{
public:
	Operation opcode;
	item rd;
	item rs;
	item rt;
	string name;
	string sd_offset;
	int t_issue;
	int t_ex;
	int t_mem;
	int t_wb;
	int t_commit;
	bool cmt;
	inst():t_issue(0),t_ex(0),t_mem(0),t_wb(0),t_commit(0),cmt(0){}
	void reset(){
		t_issue=0;
		t_ex=0;
		t_mem=0;
		t_wb=0;
		t_commit=0;
		cmt=false;
	}
};


void Addi();
void Addf();
void Mulf();
void Store();
void Load();
void Beq();

void initial();
void issue();
void execution();
void mem();
void writeback();
void commit();

/************** RS entry ****************/
class RS_entry
{
public:
	item d_r;
	item s_r;
	item t_r;
	int time;
	int icount;
	bool empty;
	RS_entry():time(0),icount(0),empty(1){};
};
/************** RS ***************/

class RS
{
public:
	RS_entry *table;
	int head;
	int tail;
	//int size;
	int n;//capacity
	int size;
	
	int get_size();
	bool empty();
	bool full();
	RS(int );
	~RS(){delete[]table;}
};
/************** addi **************/
class ADDIER
{
public:
	RS_entry line;
	bool empty;
	int cycle;
	ADDIER();
};
/*************** addf ***************/
class ADDFER
{
public:
	RS_entry *line;
	int head;
	int tail;
	int cycle;
	int n;
	int size;

	int get_size();
	bool empty();
	bool full();
	ADDFER();
	//~ADDFER(){delete[]line;}
};
class MULFER
{
public:
	RS_entry *line;
	int head;
	int tail;
	int cycle;
	int n;
	int size;

	int get_size();
	bool empty();
	bool full();
	MULFER();
	//~ADDFER(){delete[]line;}
};
#endif
