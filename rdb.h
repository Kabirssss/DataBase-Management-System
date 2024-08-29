#include <bits/stdc++.h>
using namespace std;
//importing libraries


//declaration of classes
class Attr
{
public:

    void *data;

    virtual bool operator== (const Attr &right) = 0;//declaring operators
    virtual bool operator!= (const Attr &right) = 0;
    virtual bool operator< (const Attr &right) = 0;
    virtual bool operator<= (const Attr &right) = 0;
    virtual bool operator> (const Attr &right) = 0;
    virtual bool operator>= (const Attr &right) = 0;

};

Attr* makeinstance(string, int=0, float=0, string="");

// DNFformula structure
struct DNFformula {
    list<list<tuple<string, char, Attr *>>> ops;
};

class Relation;

class Record
{
    vector <Attr *> attrptr;

public:
    Record(vector<Attr*> x)//Constructor
	{
		attrptr = x;
	}

    Record() {}

    void add_Attr(Attr *attr){
        attrptr.push_back(attr);
    }

    // == operator overloaded to check equality of two records
    bool operator== (const Record &R)
    {
        if(attrptr.size() != R.attrptr.size()){
            return false;
        }

        for(int i = 0; i < attrptr.size(); i++){
            if(*attrptr[i] != *(R.attrptr[i])){
                return false;
            }
        }

        return true;

    }

    // Relation needs access to Record
    friend class Relation;

    // Friend Functions using the private members and member function of Record class
    friend Relation * catersianproduct(Relation * R1, Relation * R2);
    friend Relation * projection(Relation * R1, list<string> projectattrs);
    friend Relation * Union (Relation * R1, DNFformula * f);
    friend Relation* naturaljoin(Relation* R1, Relation* R2, list<string>attributes);

};

//Relation classes
class Relation
{
private:
    int nattr, nrecs;            // number of attributes and records
    vector <string> attrnames;   // schema
    vector <int> attrinds;       // mapping schema to indices
    list <Record *> recs;        // list of records
    int index;                   // stores no. of attributes added
    vector <string> original;

public:
    // constructor
    Relation (vector<string> attrs, vector <string> original) : attrnames(attrs), nattr(attrs.size()), nrecs(0), index(attrs.size()), original(original){
        for(int i=0; i < nattr; i++){
            attrinds.push_back(i);
        }
    }

    // overloaded constructor
    Relation():nattr(0),nrecs(0),index(0){}

    // copy constructor
    Relation(const Relation& R)
	{
		nattr = R.nattr;
		nrecs = R.nrecs;
		attrnames = R.attrnames;
		attrinds = R.attrinds;
        original = R.original;
		for(auto rec : R.recs)//Deep copy of udt
		{
			recs.push_back(new Record(*rec));
		}
	}

    void insert(Record* rec){
        recs.push_back(rec);
        nrecs++;
    }

    void remove(Record* rec){
        recs.remove(rec);
        nrecs--;
    }

    //Function declarations
	void addattr(string);     //Function to add attribute to the relation
	void addrec();            //Function to add record to relation
	void display();           //Function to display the relation

    // friend functions
    friend Relation * Union (Relation * R1, DNFformula * f);
    friend Relation * Union(Relation * R1, Relation * R2);
    friend Relation * difference (Relation * R1, Relation * R2);
    friend Relation * catersianproduct(Relation * R1, Relation * R2);
    friend Relation * projection(Relation * R1, list<string> projectattrs);
    friend Relation * difference (Relation * R1, string s1, string s2);
    friend list<string> commonattributes(Relation* R1,Relation*R2);
    friend list<tuple<string,char,Attr*>> func(Relation* R1);
    friend Relation* naturaljoin(Relation* R1, Relation* R2, list<string>attributes);

};
