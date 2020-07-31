#include "familytree.hh"
#include <iostream>

using namespace std;

Familytree::Familytree(): persons_(), names_(){
}
Familytree::~Familytree(){
    for( Person* person: persons_){
        delete person;
        person=nullptr;
    }
    persons_.clear();
    names_.clear();
}


/* Description: Adds a new Person to the datastructure.
 * Parameters:
 *  Param1: Person's ID string
 *  Param2: Person's height
 *  Param3: Output-stream for error-printing
 * Errormessages:
 *  If person's ID is already in datastructure:
 *      "Error. Person already added."
 */
void Familytree::  addNewPerson(const std::string& id, int height,
                                std::ostream &output){

    if(names_.find(id)!=names_.end()){
        output<<"Error. Person already added."<<endl;
        return;
    }
    else{
        names_.insert(id);
        Person* a=new Person;
        a->id_=id;
        a->height_=height;
        persons_.push_back(a);
    }
}


/* Description: Prints all stored Persons' IDs and heights
 * Parameters:
 *  Param1: Output-stream for printing
 * Errormessages:
 *  None.
 */
void Familytree::printPersons(std::ostream &output) const{
    for(string id : names_){
        for (Person* person : persons_ ){
            if(person->id_==id){
                output<<id<<", "<<person->height_<<endl;
            }
        }
    }
}



/*
 * All the following functions have the same error messages:
 *  If ID wasn't found in datastructure:
 *      "Error. <ID> not found."
 *  If the printing list is empty:
 *      "Error. <ID> has no <group's name>."
 * -------------------------------------------------------------------
 */

/* Description: Adds new parent-child relation
 * Parameters:
 *  Param1: ID of the child
 *  Param2: Vector containing the parents' IDs
 *  Param3: Output-stream for error-printing
 */
void Familytree::addRelation(const std::string& child,
                 const std::vector<std::string>& parents,
                 std::ostream& output){
    if(names_.find(child)==names_.end()){
        printNotFound(child,output);
        return;
    }
    for(int i=0;i<int(parents.size());++i){
        if(parents.at(i)=="-"){
            continue;
        }
        if(names_.find(parents[i])==names_.end()){
            printNotFound(parents[i],output);
            return;
        }
        for(Person* kid: persons_){
            if(child == kid->id_){
                for(Person* one_parent: persons_){
                    if(parents[i]==one_parent->id_){
                        kid->parents_[i]=one_parent;
                        one_parent->children_.push_back(kid);
                    }
                }
            }
        }
    }

}

/* Description: Prints all children for the person.
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Output-stream for printing
 */
void Familytree::printChildren(const std::string& id,
                               std::ostream& output) const{
    if(names_.find(id)==names_.end()){
        printNotFound(id,output);
        return;
    }
    IdSet names;
    Person* id_pointer=getPointer(id);//get nullptr, if id not in container
    for (Person* person: id_pointer->children_){
        names.insert(person->id_);
    }
    printIDs(id, "children", names, output);


}

/* Description: Prints all the parents for the person.
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Output-stream for printing
 */
void Familytree::printParents(const std::string& id,
                              std::ostream& output) const{
    if(names_.find(id)==names_.end()){
        printNotFound(id,output);
        return;
    }
    IdSet names;
    Person* id_pointer=getPointer(id);
    for (Person* person: id_pointer->parents_){
        if(person!=nullptr){
            names.insert(person->id_);
        }
    }
    printIDs(id, "parents", names, output);
}


/* Description: Prints all siblings for the person.
 *  (Persons who shares a parent)
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Output-stream for printing
 */
void Familytree::printSiblings(const std::string& id,
                               std::ostream& output) const{
    if(names_.find(id)==names_.end()){
        printNotFound(id,output);
        return;
    }

    IdSet names;
    Person* id_ptr=getPointer(id);
    for(Person* parent_ptr: id_ptr->parents_){
        if(parent_ptr!=nullptr){
            for (Person* person: parent_ptr->children_){
                if( person->id_!=id){
                    names.insert(person->id_);
                }
            }
        }
    }
    printIDs(id,  "siblings",names, output);
}


/* Description: Prints all the cousins for the person.
 *  (Persons who share same grandparents)
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Output-stream for printing
 */
void Familytree::printCousins(const std::string& id,
                              std::ostream& output) const{
    if(names_.find(id)==names_.end()){
        printNotFound(id,output);
        return;
    }
    //cousins are father's or mothers's siblins's children
    IdSet names;
    Person* id_ptr=getPointer(id);
    //parents are:
    for (Person* parents: id_ptr->parents_){
        if(parents!=nullptr){

            //to have grandparents
            for(Person* grandparent_ptr: parents->parents_){
                if(grandparent_ptr!=nullptr){

                    //now (parents_sib is the variable of)parent(s) siblins
                    for (Person* parents_sib: grandparent_ptr->children_){
                        if( parents_sib->id_!=parents->id_){

                            //now to add parents_sib's children(s)
                            for (Person* cousins: parents_sib->children_){
                                names.insert(cousins->id_);
                            }
                        }
                    }
                }
            }
        }
    }
    printIDs(id,  "cousins",names, output);
}


/* Description: Prints the tallest person of the ID's lineage.
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Output-stream for printing
 */
void Familytree::printTallestInLineage(const std::string& id,
                                       std::ostream& output) const{
    if(names_.find(id)==names_.end()){
        printNotFound(id,output);
        return;
    }

    Person* greatest=nullptr;
    for(Person* x: persons_){
        if(x->id_==id){
            greatest=x;
        }
    }


    //Person* person= greatest;
    vector<Person*> set_of_persons;

    for(Person* child: greatest->children_){
        if(child->height_>greatest->height_){
            greatest=child;
        }
        set_of_persons.push_back(child);
    }


    while (set_of_persons.size()!=0){
        vector<Person*> set_of_2;
        for(Person* person: set_of_persons){
            for (Person* child: person->children_){
                if(child->height_>greatest->height_){
                    greatest=child;
                }
                set_of_2.push_back(child);
            }

        }
        set_of_persons=set_of_2;
    }
    if(greatest->id_==id){
        output<<"With the height of "<<greatest->height_<<
             ", "<<greatest->id_<<" is the tallest person in his/her lineage."<<endl;
    }
    else{
        output<<"With the height of "<<greatest->height_<<
             ", "<<greatest->id_<<" is the tallest person in "<<id<<"'s lineage."<<endl;
    }

}

/* Description:
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Output-stream for printing
 */
void Familytree::printShortestInLineage(const std::string& id,
                                        std::ostream& output) const{
    if(names_.find(id)==names_.end()){
        printNotFound(id,output);
        return;
    }


    Person* greatest=nullptr;
    for(Person* x: persons_){
        if(x->id_==id){
            greatest=x;
        }
    }


    //Person* person= greatest;
    vector<Person*> set_of_persons;

    for(Person* child: greatest->children_){
        if(child->height_<greatest->height_){
            greatest=child;
        }
        set_of_persons.push_back(child);
    }


    while (set_of_persons.size()!=0){
        vector<Person*> set_of_2;
        for(Person* person: set_of_persons){
            for (Person* child: person->children_){
                if(child->height_<greatest->height_){
                    greatest=child;
                }
                set_of_2.push_back(child);
            }

        }
        set_of_persons=set_of_2;
    }
    if(greatest->id_==id){
        output<<"With the height of "<<greatest->height_<<
             ", "<<greatest->id_<<" is the shortest person in his/her lineage."<<endl;
    }
    else{
        output<<"With the height of "<<greatest->height_<<
             ", "<<greatest->id_<<" is the shortest person in "<<id<<"'s lineage."<<endl;
    }

}


/* The following functions have additional errormessage:
 *  If Param2's value is less than 1:
 *      "Error. Level can't be less than 1."
 * ---------------------------------------------------------------
 */


/* Description: Prints the amount of grandchildren in given distance
 *  from the person.
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Distance from the person. (n-1 times "grandness")
 *  Param3: Output-stream for printing
 */
void Familytree::printGrandChildrenN(const std::string& id, const int n,
                                     std::ostream& output) const{
    if(n<1){
        cout<<"Error. Level can't be less than 1"<<endl;
        return;
    }

    int times=n;
    string mark="great-";
    string marks="";
    for(int i=0;i<n;++i){
        marks+=mark;
    }

    IdSet names;
    while (times!=0){
        names.clear();
        for(Person* child : persons_){
            for(Person* grand_chi: child->children_){
                names.insert(grand_chi->id_);
            }

        }
        --times;
    }


    if(names.size()!=0){
        output<<id<<" has "<<names.size()<<" "<<marks<<"grandchildren"<<endl;
        for(string id: names){
            output<<id<<endl;
        }
    }
    else{
        output<<id<<" has no "<<marks<<"grandchildren"<<endl;
    }



}




/* Description: Prints the amount of grandparents in given distance
 *  from the person.
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Distance from the person. (n-1 times "grandness")
 *  Param3: Output-stream for printing
 */
void Familytree::printGrandParentsN(const std::string& id, const int n,
                        std::ostream& output) const{
    if(n<1){
        cout<<"Error. Level can't be less than 1"<<endl;
        return;
    }
}






//private>

/* The following functions are meant to make project easier.
 * You can implement them if you want and/or create your own.
 * Anyway it would be a good idea to implement more functions
 * to make things easier and to avoid "copy-paste-coding"
 */

// Return a pointer for ID.
Person* Familytree::getPointer(const std::string& id) const{
    for (Person* person : persons_){
        if(person->id_==id){
            return person;
        }
    }
    return nullptr;
}
//print<ID> has <num><somthing >
void Familytree:: printIDs(const std::string& ID, const std::string& human,
                           const IdSet& names, std:: ostream& output) const{

    if(names.size()!=0){
        output<<ID<<" has "<<names.size()<<" "<<human<<":"<<endl;
        for (string name : names){
            output<<name<<endl;
        }
    }
    else{
       output<<ID<<" has no "<<human<<"."<<endl;
    }

}

// Printing errors.
void Familytree::printNotFound(const std::string& id,std::ostream& output) const{
    output<<"Error. "<<id<<" not found."<<endl;
}


// Turns a vector of persons to a set of IDs.
IdSet Familytree::VectorToIdSet(const std::vector<Person*> &container) const{
    IdSet names;
    for(Person* person : container){
        names.insert(person->id_);
    }
    return names;
}


// Prints the the data in a container.
//void printGroup(const std::string& id, const std::string& group,const IdSet& container, std::ostream& output) const;



