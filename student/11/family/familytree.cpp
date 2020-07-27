#include "familytree.hh"
#include <iostream>

using namespace std;

Familytree::Familytree():names_(), persons_(){
}
Familytree::~Familytree(){
    for( Person* person: persons_){
        delete person;
        person=nullptr;
    }
    persons_.clear();
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
        Person* a;
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
                output<<id<<" "<<person->height_<<endl;
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
        output<<"Error. "<< child <<" not found."<<endl;
        return;
    }
    for(int i=1;i<=parents.size();++i){
        if(names_.find(parents[i])==names_.end()){
            output<<"Error. "<< parents[i]<<" not found."<<endl;
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
void printChildren(const std::string& id,
                   std::ostream& output) const;

/* Description: Prints all the parents for the person.
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Output-stream for printing
 */
void printParents(const std::string& id,
                  std::ostream& output) const;

/* Description: Prints all siblings for the person.
 *  (Persons who shares a parent)
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Output-stream for printing
 */
void printSiblings(const std::string& id,
                   std::ostream& output) const;

/* Description: Prints all the cousins for the person.
 *  (Persons who share same grandparents)
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Output-stream for printing
 */
void printCousins(const std::string& id,
                  std::ostream& output) const;

/* Description: Prints the tallest person of the ID's lineage.
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Output-stream for printing
 */
void printTallestInLineage(const std::string& id,
                           std::ostream& output) const;

/* Description:
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Output-stream for printing
 */
void printShortestInLineage(const std::string& id,
                            std::ostream& output) const;


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
void printGrandChildrenN(const std::string& id, const int n,
                         std::ostream& output) const;

/* Description: Prints the amount of grandparents in given distance
 *  from the person.
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Distance from the person. (n-1 times "grandness")
 *  Param3: Output-stream for printing
 */
void printGrandParentsN(const std::string& id, const int n,
                        std::ostream& output) const;
//private>

/* The following functions are meant to make project easier.
 * You can implement them if you want and/or create your own.
 * Anyway it would be a good idea to implement more functions
 * to make things easier and to avoid "copy-paste-coding"
 */

// Return a pointer for ID.
Person* getPointer(const std::string& id) const;

// Printing errors.
void printNotFound(const std::string& id,
                   std::ostream& output) const;

// Turns a vector of persons to a set of IDs.
IdSet VectorToIdSet(const std::vector<Person*> &container) const;

// Prints the the data in a container.
void printGroup(const std::string& id, const std::string& group,
                const IdSet& container, std::ostream& output) const;



