#include <bits/stdc++.h>
#include "rdb.h"
//importing libraries
using namespace std;

Relation * Union(Relation * R1, Relation * R2)
{
    // check if it has same attributes, union compatible
    if(R1->nattr != R2->nattr)
	{
		cout<<"Given Relations are not union compatible"<<endl;
		return NULL;
	}
	for(int i=0;i<R1->nattr;i++)
	{
		if(R1->attrnames[i] != R2->attrnames[i])
		{
			cout<<"Given Relations are not union compatible"<<endl;
			return NULL;
		}
	}

    Relation *R = new Relation (R1->attrnames, R1->original); //dynamic allocation of R of type relation

    // insert R1 in R
    for(auto rec : R1->recs){
        R->insert(rec);
    }

    // check if record matches in R1 and R2 and insert those who dont match
    for(auto rec2 : R2->recs){
        int flag = 0;
        for(auto rec1 : R1->recs){
            if(rec1 == rec2){
                flag = 1;
                break;
            }
        }

        if(!flag) {
            R->insert(rec2);
        }
    }

    return R;

}

// Records in R1 but not in R2
Relation * difference (Relation * R1, Relation * R2)
{
    // check if it has same attributes, union compatible
    if(R1->nattr != R2->nattr)
	{
		cout<<"Given Relations are not union compatible"<<endl;
		return NULL;
	}
	for(int i=0;i<R1->nattr;i++)
	{
		if(R1->attrnames[i] != R2->attrnames[i])
		{
			cout<<"Given Relations are not union compatible"<<endl;
			return NULL;
		}
	}

    Relation *R = new Relation (R1->attrnames, R1->original);

    // insert R1 in R
    for(auto rec : R1->recs){
        R->insert(rec);
    }

    // check if record matches in R1 and R2 and remove those who matches
    for(auto rec2 : R2->recs){
        int flag = 0;
        for(auto rec1 : R1->recs){
            if(rec1 == rec2){
                flag = 1;
                break;
            }
        }

        if(flag) {
            R->remove(rec2);
        }
    }

    return R;

}

Relation * catersianproduct(Relation * R1, Relation * R2)
{

    Relation * R = new Relation();

    // pushing attributes of R1 into R
    for(auto attr : R1->original){
        R->original.push_back(attr);
        R->attrinds.push_back(R->nattr);
        R->nattr++;
    }

    // pushing attributes of R2 into R
    for(auto attr : R2->original){
        R->original.push_back(attr);
        R->attrinds.push_back(R->nattr);
        R->nattr++;
    }

    for(auto it: R1->attrnames)
	{
		R->attrnames.push_back(it);
	}
	for(auto it: R2->attrnames)
	{
		R->attrnames.push_back(it);
	}

    // inserting records for every R1 x R2
    for(auto r1 : R1->recs){
        for(auto r2 : R2->recs){
            Record *r = new Record();
            r->attrptr = r1->attrptr;
            r->attrptr.insert(r->attrptr.end(), r2->attrptr.begin(), r2->attrptr.end());
            R->recs.push_back(r);
            R->nrecs++;
        }
    }

    return R;

}

Relation * projection(Relation * R1, list<string> projectattrs)
{
    // return relation
    Relation* R = new Relation();//Return relation
	for(int i=0;i<R1->attrnames.size();i++)
	{
		if(find(projectattrs.begin(),projectattrs.end(),R1->attrnames[i])!=projectattrs.end())
		{
			R->attrnames.push_back(R1->attrnames[i]);
			R->original.push_back(R1->original[i]);
		}
	}
	R->nattr = R->attrnames.size();

    // iterating over record list of relation and finding the attributes to be present in projection
    for(auto r : R1->recs){
        Record *temprec = new Record(); //dynamic allocation of temprec of type Record
        int i = 0;

        // checking if attribute is there
        for(auto it : r->attrptr){
            string s = R1->attrnames[i];
            int flag = 0;
            for(auto it2 : projectattrs){
                if(it2 == s){
                    flag = 1;
                    break;
                }
            }

            if(flag){
                temprec->add_Attr(it);
            }
            i++;

        }

        R->insert(temprec);
    }

    return R;
}

// Function to rename an attribute in a relation
Relation * difference (Relation * R1, string s1, string s2)
{
    for(int i = 0; i < R1->nattr; i++){
        // finding attribute to be replaced and then replace it with given new name
        if(R1->attrnames[i] == s1){
            R1->attrnames[i] = s2;
        }
    }
    return R1;
}

// DNFformula structure
// struct DNFformula {
//     list<list<tuple<string, char, Attr *>>> ops;
// };

Relation * Union (Relation * R1, DNFformula * f)
{
    vector <Relation> temp;

    for (auto it : f->ops){

        Relation temp1(R1->attrnames, R1->original);

        for (auto it2 : R1->recs){
            bool flag = true;
            int i = 0;

            for(auto it3 : it2->attrptr){
                for(auto it4 : it){
                    if(R1->attrnames[i] == get<0>(it4)){
                        if(get<1>(it4) == '<')
						{
							if(flag)
							flag = (*it3) < *(get<2>(it4));

						}
						if(get<1>(it4) == '=')
						{
							if(flag)
							flag = (*it3) == *(get<2>(it4));
						}
						if(get<1>(it4) == '>')
						{
							if(flag)
							flag = (*it3) > *(get<2>(it4));
						}
					}
                }
                i++;
            }
            if(flag){
                temp1.insert(it2);
            }

        }
        temp.push_back(temp1);
    }

    if(temp.size() == 0) return R1;
    if(temp.size() == 1){
        //temp[0].display();
        return (new Relation(temp[0]));
    }
    else
    //Taking the union of relations satisfying various different conditions
	{
		Relation * R = Union(new Relation(temp[0]),new Relation(temp[1]));
		for(int i = 2;i < temp.size();i++)
		{
			R = Union(new Relation(temp[i]), R);
		}
		return R;
	}

}

list<tuple<string,char,Attr*>> func(Relation* R1)
{
	list<tuple<string,char,Attr*>> temp;
	for(int i=0;i<R1->attrnames.size();i++)
	{
		cout<<"Do you want to add a condition on "<<R1->attrnames[i]<<"?:(y/n) ";
		string s;
		cin>>s;
		if(s == "y")
		{
			cout<<"Choose comparison to perform:\n1)<\n2)=\n3)>\n";
			char scheme[]={'<','=','>'};
			int optinput;
			cin >> optinput;
            char optioninput = scheme[optinput-1];
			cout << "Enter the value to compare with: ";
			if(R1->original[i] == "integerAttribute")
			{
				int k;
				cin >> k;
				temp.push_back(make_tuple(R1->attrnames[i],optioninput,makeinstance("integerAttribute",k)));
			}
			if(R1->original[i] == "floatAttribute")
			{
				float k;
				cin >> k;
				temp.push_back(make_tuple(R1->attrnames[i],optioninput,makeinstance("floatAttribute",0,k)));
			}
			if(R1->original[i] == "stringAttribute")
			{
				string k;
				cin >> k;
				temp.push_back(make_tuple(R1->attrnames[i],optioninput,makeinstance("stringAttribute",0,0,k)));
			}
		}

	}
	return temp;

}

