#ifndef EXECUTION_CLASS_H
#define EXECUTION_CLASS_H

#include <iostream>
#include <algorithm>
#include "GGraphNode.hpp"
#include "GlobalGraph.class.hpp"

class Execution {

    public:

        //=================/ CONSTRUCTOR /==================//
        Execution(void);
        Execution(std::list<GGraphNode*> queriesNode);
        ~Execution(void);
        //=================/  OPERATOR   /==================//
        //=================/  VARIABLE   /==================//
        //=================/   GETTER    /==================//
        std::list<GGraphNode*>      getQueriesNode(void) const;
        //=================/   SETTER    /==================//
        //=================/  FUNCTION   /==================//
        char                        searchValue(std::pair<GGraphNode*, bool> node, std::list<GGraphNode*> check);
        void                        resolveQueries(void);

    private:

        //=================/ CONSTRUCTOR /==================//
        Execution(Execution const & src);
        //=================/  OPERATOR   /==================//
        Execution &		operator=(Execution const & src);
        //=================/  VARIABLE   /==================//
        std::list<GGraphNode*>      _queriesNode;
        //=================/   GETTER    /==================//
        //=================/   SETTER    /==================//
        //=================/  FUNCTION   /==================//

};

std::ostream &		operator<<(std::ostream & o, Execution const & i);

#endif