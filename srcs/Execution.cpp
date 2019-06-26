#include "Execution.hpp"

//=================/ DEFAULT CONSTRUCTOR /==================//
Execution::Execution(void) {
    // std::cout << "Default Execution Constructor called" << std::endl;
    return;
}

//=================/ PARAM CONSTRUCTOR /==================//
Execution::Execution(std::list<GGraphNode*> queriesNode) : _queriesNode(queriesNode) {
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

std::list<GGraphNode*>      Execution::getQueriesNode(void) const { return this->_queriesNode; }

char                        Execution::searchValue(std::pair<GGraphNode*, bool> node, std::list<GGraphNode*> check) {
    if (node.first == nullptr)
        return -1;

    if (node.first->value != 0) {
        if (node.second) {
            return node.first->value == 1 ? -1 : 1;
        }
        return node.first->value;
    }

    if (find(check.begin(), check.end(), node.first) != check.end()) {
        node.first->value = -1;
        if (node.second) {
            return node.first->value == 1 ? -1 : 1;
        }
        return node.first->value;
    }

    if (node.first->type == AND_NODE) {
        std::list<std::pair<GGraphNode*, bool>>::iterator it = node.first->in_list.begin();
        char f = this->searchValue(*it, check);
        it++;
        char e = this->searchValue(*it, check);
        node.first->value = (f == 1 & e == 1) ? 1 : -1;
        return node.first->value;
    }

    if (node.first->type == OR_NODE) {
        std::list<std::pair<GGraphNode*, bool>>::iterator it = node.first->in_list.begin();
        char f = this->searchValue(*it, check);
        it++;
        char e = this->searchValue(*it, check);
        node.first->value = (f == 1 | e == 1) ? 1 : -1;
        return node.first->value;
    }

    if (node.first->type == XOR_NODE) {
        std::list<std::pair<GGraphNode*, bool>>::iterator it = node.first->in_list.begin();
        char f = this->searchValue(*it, check);
        it++;
        char e = this->searchValue(*it, check);
        node.first->value = ((f == 1) ^ (e == 1)) ? 1 : -1;
        return node.first->value;
    }

    if (node.first->type == FACT_NODE) {
        check.push_back(node.first);
        for (std::list<std::pair<GGraphNode*, bool>>::iterator it = node.first->in_list.begin(); it != node.first->in_list.end(); it++) {
            if (this->searchValue(*it, check) == 1) {
                node.first->value = 1;
                if (node.second) {
                    return node.first->value == 1 ? -1 : 1;
                }
                return node.first->value;
            }
        }
    }
    node.first->value = -1;
    if (node.second) {
        return node.first->value == 1 ? -1 : 1;
    }
    return node.first->value;
}

void                        Execution::resolveQueries(void) {
    // std::list<GGraphNode*> check;
    for (GGraphNode* q : this->_queriesNode) {
        std::string str;
        // check.push_back(q);
        // char ret = this->searchValue({q, false}, check);
        char ret = this->searchValue({q, false}, {});
        if (ret == -1) {
            str = "False";
        } else if (ret == 1) {
            str = "True";
        } else {
            str = "Undefine";
        }
        std::cout << q->name << " is " << str << std::endl;
    }
}