#include <bits/stdc++.h>
#include "rdb.h"
//importing libraries
using namespace std;

//Function to generate commonattributes between 2 function to take natural join of the relations
list<string> commonattributes(Relation* R1,Relation*R2)
{
	list<string> retval;
	for(auto it:R1->attrnames)
	{
		bool flag = false;
		for(auto it2: R2->attrnames)
		{
			if(it==it2)
			{
				flag = true;
				break;
			}
		}
		if(flag)
		{
			retval.push_back(it);
		}
	}
	return retval;
}


// Natural join function
Relation* naturaljoin(Relation* R1, Relation* R2, list<string>attributes)
{
    // Making copy of relations to prevent original relations from getting altered
	Relation* rel1 = new Relation(*R1); // dynamic allocation of rel1 of type Relation
	Relation* rel2 = new Relation(*R2); //dynamic allocation of rel1 of type Relation
	int i=0;

    // Taking Cartesian product of the 2 relations
	Relation* crossproduct = catersianproduct(rel1,rel2);

	crossproduct->display();
	DNFformula f;
	for(auto it:rel1->recs)         // Creating the DNFformula for selecting the records
	{
		list<tuple<string,char,Attr*>>temp;
		int i=0;
		for(auto it2: it->attrptr)
		{
			if(find(attributes.begin(),attributes.end(),rel1->attrnames[i])!=attributes.end())//Pushing the common attributes into the tuples
			{
				temp.push_back(make_tuple(rel1->attrnames[i],'=',it2));
			}
			i++;
		}
		f.ops.push_back(temp);
	}

    //Selecting the viable records
	Relation* retval = Union(crossproduct, &f);
	retval->display();
	i = R1->attrnames.size();

    //Renaming the common attributes in relation 3
	for(auto it:rel2->attrnames)
	{
		if(find(attributes.begin(),attributes.end(),it) != attributes.end())
		{
			retval->attrnames[i] = "temp";
		}
		i++;
	}
	retval->display();
	i=0;

    //Creating projectionattributes list to take projection
	list<string> projectionattr;

	Relation* retrelation = new Relation();
	retrelation->nattr = retval->nattr;
	retrelation->nrecs = retval->nrecs;
	for(int i=0;i<retval->attrnames.size();i++)
	{
		if(retval->attrnames[i] != "temp")
		{
			retrelation->attrnames.push_back(retval->attrnames[i]);
			retrelation->original.push_back(retval->original[i]);
		}
	}

	cout<<retrelation->attrnames.size()<<endl<<retrelation->original.size();
	retrelation->nattr = retrelation->attrnames.size();
	for(auto it:retval->recs)
	{
		vector<Attr*>temprecord;
		for(int i=0;i<retval->attrnames.size();i++)
		{
			if(retval->attrnames[i] != "temp")
			{
				temprecord.push_back(it->attrptr[i]);
			}
		}
		retrelation->recs.push_back(new Record(temprecord));
	}
	return retrelation;
}

