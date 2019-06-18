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
        Execution(std::list<std::pair<GGraphNode*, bool>> queriesNode);
        ~Execution(void);
        //=================/  OPERATOR   /==================//
        //=================/  VARIABLE   /==================//
        //=================/   GETTER    /==================//
        std::list<std::pair<GGraphNode*, bool>>      getQueriesNode(void) const;
        //=================/   SETTER    /==================//
        //=================/  FUNCTION   /==================//
        char                        searchValue(std::pair<GGraphNode*, bool> node);
        void                        resolveQueries(void);

    private:

        //=================/ CONSTRUCTOR /==================//
        Execution(Execution const & src);
        //=================/  OPERATOR   /==================//
        Execution &		operator=(Execution const & src);
        //=================/  VARIABLE   /==================//
        std::list<std::pair<GGraphNode*, bool>>      _queriesNode;
        //=================/   GETTER    /==================//
        //=================/   SETTER    /==================//
        //=================/  FUNCTION   /==================//

};

std::ostream &		operator<<(std::ostream & o, Execution const & i);

#endif