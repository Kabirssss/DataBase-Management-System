#include <bits/stdc++.h>
#include "rdb.h"
//including libraries
using namespace std;

//integerAttr is a derived class(base class being Attr)
class integerAttr: public Attr
{

public:

	//Constructor
	integerAttr(int x_){
		data = new int(x_); //dynamic allocation of data
	}
	//Overriden operators(These will return boolean values true(1) or false(0))
	bool operator== (const Attr& R)
	{
		if(*(int*)data == *(int*)R.data)
			return true;
		return false;
	}
	bool operator!= (const Attr& R)
	{
		if(*(int*)data != *(int*)R.data)
			return true;
		return false;
	}
	bool operator< (const Attr& R)
	{
		if(*(int*)data < *(int*)R.data)
			return true;
		return false;
	}
	bool operator<= (const Attr& R)
	{
		if(*(int*)data <= *(int*)R.data)
			return true;
		return false;
	}
	bool operator> (const Attr& R)
	{
		if(*(int*)data > *(int*)R.data)
			return true;
		return false;
	}
	bool operator>= (const Attr& R)
	{
		if(*(int*)data >= *(int*)R.data)
			return true;
		return false;
	}

};
//derived classes
class floatAttr: public Attr
{
    public:
	//Constructor
	floatAttr(float x_){
		data = new float(x_); //dynamic allocation of data
	}
	//Overriden operators(These will return boolean values true(1) or false(0))
	bool operator== (const Attr& R)
	{
		if(*(float*)data == *(float*)R.data)
			return true;
		return false;
	}
	bool operator!= (const Attr& R)
	{
		if(*(float*)data != *(float*)R.data)
			return true;
		return false;
	}
	bool operator< (const Attr& R)
	{
		if(*(float*)data < *(float*)R.data)
			return true;
		return false;
	}
	bool operator<= (const Attr& R)
	{
		if(*(float*)data <= *(float*)R.data)
			return true;
		return false;
	}
	bool operator> (const Attr& R)
	{
		if(*(float*)data > *(float*)R.data)
			return true;
		return false;
	}
	bool operator>= (const Attr& R)
	{
		if(*(float*)data >= *(float*)R.data)
			return true;
		return false;
	}

};

class stringAttr: public Attr
{
    public:
	//Constructor
	stringAttr(string s)
	{
		data = new string(s); //dynamic allocation of data
	}
	//Overriden operators(These will return boolean values true(1) or false(0))
	bool operator == (const Attr& R)
	{
		return *(string*)data == *(string*)R.data;
	}
	bool operator < (const Attr& R)
	{
		return *(string*)data < *(string*)R.data;
	}
	bool operator <= (const Attr& R)
	{
		return *(string*)data <= *(string*)R.data;
	}
	bool operator > (const Attr& R)
	{
		return *(string*)data > *(string*)R.data;
	}
	bool operator >= (const Attr& R)
	{
		return *(string*)data >= *(string*)R.data;
	}
	bool operator != (const Attr& R)
	{
		return *(string*)data != *(string*)R.data;
	}

};

//Function to create a new instance of user defined classes
Attr* makeinstance(string s, int a, float b, string s1)
{
	// s = attribute name, a, b, s1 store the attribute values (overloaded in header file)
	// Checking of s and returning appropriate instance
	if(s == "integerAttribute")
	{
		return new integerAttr(a);
	}
	if(s == "floatAttribute")
	{
		return new floatAttr(b);
	}
	if(s== "stringAttribute")
	{
		return new stringAttr(s1);
	}
}

//Function to add a new attribute to the relation
void Relation::addattr(string attrname)
{

	attrnames.push_back(attrname);               //Pushing attribute name and attribute index into their respective vectors using the pushback operation of vectors
	attrinds.push_back(++index);
	sort(attrnames.begin(),attrnames.end());
	nattr++;                                     //Increasing the count of attributes
	original = attrnames;
}

//Function to display the relation
void Relation::display()
{
	int k=0;

	for(auto it : recs)                                 //iterating over the records and listing them
	{
	    int i=0;
	    cout << "Rec_id: " << ++k;                      //printing the record number
	    for(int j = 0; j < nattr; j++)                  //Printing each attribute of the record
	    {
	    	cout<<", "<<attrnames[j]<<": ";
	    	if(original[j] == "integerAttribute")
	    	{
	    		cout<<*((int*)(*it).attrptr[i]->data);
	    	}
	    	if(original[j] == "floatAttribute")
	    	{
	    		cout<<*((float*)(*it).attrptr[i]->data);
	    	}
	    	if(original[j] == "stringAttribute")
	    	{
	    		cout<<*((string*)(*it).attrptr[i]->data);
	    	}
	    	i++;
	    }
	    cout<<endl;
	}
}

//Function to add a record
void Relation::addrec()
{
	vector<Attr*> temp;    //Temporary vector of attribute pointers to construct the record from
	int i=0;
	for(auto it:original)      //Looping over the attributenames list and taking input for each attribute
	{
	    if(it == "integerAttribute")
	    {
	    	cout<<"Enter the value of "<<attrnames[i]<<" of the record: ";
	    	int k;
	    	cin>>k;
	    	temp.push_back(new integerAttr(k));   //Pushing new attribute into the temporary vector
	    }
	    if(it == "floatAttribute")
	    {
	    	cout<<"Enter the value of "<<attrnames[i]<<" of the record: ";
	    	float k;
	    	cin>>k;
	    	temp.push_back(new floatAttr(k));
	    }
	    if(it == "stringAttribute")
	    {
	    	cout<<"Enter the value of "<<attrnames[i]<<" of the record: ";
	    	string s;
	    	cin>>s;
	    	temp.push_back(new stringAttr(s));
	    }
	    i++;
	}
    //Constructing a new record from temporary vector and adding it into the recs vector of the object
	recs.push_back(new Record(temp));
	nrecs++;
}
