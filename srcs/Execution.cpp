#include "Execution.hpp"

//=================/ DEFAULT CONSTRUCTOR /==================//
Execution::Execution(void) {
    // std::cout << "Default Execution Constructor called" << std::endl;
    return;
}

//=================/ PARAM CONSTRUCTOR /==================//
Execution::Execution(std::list<std::pair<GGraphNode*, bool>> queriesNode) : _queriesNode(queriesNode) {
    // std::cout << "Param Execution Constructor called" << std::endl;
    return;
}

//=================/  COPY CONSTRUCTOR   /==================//
Execution::Execution(Execution const & src) {
    // std::cout << "Copy Execution Constructor called" << std::endl;
    *this = src;
    return;
}

//=================/     DESTRUCTOR      /==================//
Execution::~Execution(void) {
    // std::cout << "Destructor Execution called" << std::endl;
    return;
}

//=================/      OPERATOR =     /==================//
Execution &		Execution::operator=(Execution const & src) {
    // std::cout << "Assignation Execution operator called" << std::endl;
    if (this != &src) {
        
    }
    return *this;
}

//=================/     OPERATOR <<     /==================//
std::ostream &		operator<<(std::ostream & o, Execution const & i) {
    (void)i;
    o << " This is Execution instence";
    return o;
}

std::list<std::pair<GGraphNode*, bool>>      Execution::getQueriesNode(void) const { return this->_queriesNode; }

char                        Execution::searchValue(std::pair<GGraphNode*, bool> node) {
    if (node.first == nullptr)
        return -1;

    if (node.first->value != 0)
        return node.first->value;

    if (node.first->type == AND_NODE) {
        std::list<std::pair<GGraphNode*, bool>>::iterator it = node.first->in_list.begin();
        char f = this->searchValue(*it);
        it++;
        char e = this->searchValue(*it);
        node.first->value = (f == 1 & e == 1) ? 1 : -1;
        return node.first->value;
    }

    if (node.first->type == OR_NODE) {
        std::list<std::pair<GGraphNode*, bool>>::iterator it = node.first->in_list.begin();
        char f = this->searchValue(*it);
        it++;
        char e = this->searchValue(*it);
        node.first->value = (f == 1 | e == 1) ? 1 : -1;
        return node.first->value;
    }

    if (node.first->type == XOR_NODE) {
        std::list<std::pair<GGraphNode*, bool>>::iterator it = node.first->in_list.begin();
        char f = this->searchValue(*it);
        it++;
        char e = this->searchValue(*it);
        node.first->value = ((f == 1) ^ (e == 1)) ? 1 : -1;
        return node.first->value;
    }

    if (node.first->type == FACT_NODE) {
        for (std::list<std::pair<GGraphNode*, bool>>::iterator it = node.first->in_list.begin(); it != node.first->in_list.end(); it++) {
            if (this->searchValue(*it) == 1) {
                node.first->value = 1;
                return 1;
            }
        }
    }
    node.first->value = -1;
    return -1;
}

void                        Execution::resolveQueries(void) {
    for (std::pair<GGraphNode*, bool> q : this->_queriesNode) {
        std::string str;
        char ret = this->searchValue(q);
        if (ret == -1) {
            str = "False";
        } else if (ret == 1) {
            str = "True";
        } else {
            str = "Undefine";
        }
        std::cout << q.first->name << " is " << str << std::endl;
    }
}