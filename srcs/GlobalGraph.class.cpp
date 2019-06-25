/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalGraph.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:15:48 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/25 17:25:43 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GlobalGraph.class.hpp"

GlobalGraph::GlobalGraph()
{
    
}

GlobalGraph::GlobalGraph(GlobalGraph const &src)
{
    *this = src;
}

GlobalGraph::~GlobalGraph()
{

}

GlobalGraph&              GlobalGraph::operator=(GlobalGraph const &rhs)
{
    this->_node_list = rhs._node_list;
    this->_query_node = rhs._query_node;
    this->_fact_list = rhs._fact_list;
    return (*this);
}

void                        GlobalGraph::init(std::list<t_tkn*> tkn)
{
    std::list<GGraphNode*>          line_nodes;
    std::list<GGraphNode*>          implied_nodes;
    std::pair<GGraphNode*, bool>    tmp;
    line_type                       l_type;
    int                             priority = 1;
    
    while((l_type = get_line_nodes(&tkn, &line_nodes)) != L_QUERY)
    {
        if (l_type == L_RULE && !line_nodes.empty())
        {
            implied_nodes = implied_fact_nodes(&line_nodes);
            for (GGraphNode* n : line_nodes)
                if (n->priority > priority)
                    priority = n->priority;
            tmp = init_fact_line(line_nodes, priority);
            for (GGraphNode* n : implied_nodes)
                n->in_list.push_back(tmp);
        }
        else if (l_type == L_FACT)
            init_rule_line(line_nodes);
        remove_tkn_line(&tkn, &line_nodes);
    }
    init_query_line(line_nodes);

}

line_type                   GlobalGraph::get_line_nodes(std::list<t_tkn*> *tkn,
                            std::list<GGraphNode*>* line_nodes)
{
    std::map<rule_tkn, node_type> type_map = {
        {T_VAL, FACT_NODE},
        {T_NOT_VAL, NOTFACT_NODE},
        {T_AND, AND_NODE},
        {T_OR, OR_NODE},
        {T_XOR, XOR_NODE}
    };
    std::list<t_tkn*>::iterator it;
    GGraphNode*                 tmp;
    line_type                   ret;
    char                        priority = 1;
    
    ret = tkn->front()->l_type;
    it = tkn->begin();
    while((*it)->r_type != T_ENDL)
    {
        if ((*it)->r_type == T_BRACKET_O)
            priority++;
        if ((*it)->r_type == T_BRACKET_C)
            priority--;
        if ((*it)->r_type == T_IMPLIES)
            priority = 0;
        if (type_map.count((*it)->r_type))
        {
            if (priority != 0 || (*it)->r_type == T_VAL)
            {
                tmp = new GGraphNode();
                tmp->type = type_map[(*it)->r_type];
                tmp->name = (*it)->val;
                tmp->priority = priority;
                line_nodes->push_back(tmp);
            }
        }
        it++;
    }
    return (ret);
}

std::pair<GGraphNode*, bool>    GlobalGraph::init_fact_line(std::list<GGraphNode*> line_nodes, int priority)
{
    std::list<GGraphNode*>::iterator it;
    std::list<GGraphNode*>::iterator lhs;
    std::list<GGraphNode*>::iterator rhs;
    std::pair<GGraphNode*, bool>     ret;

    ret.first = NULL;
    ret.second = false;
    for (it = line_nodes.begin(); it != line_nodes.end(); ++it)
    {
        lhs = std::prev(it);
        rhs = std::next(it);
        if ((*it)->priority == priority && (*it)->type == AND_NODE)
            ret.first = this->handleOperator(it, lhs, rhs, line_nodes);
    }
    for (it = line_nodes.begin(); it != line_nodes.end(); ++it)
    {
        lhs = std::prev(it);
        rhs = std::next(it);
        if ((*it)->priority == priority && (*it)->type == OR_NODE)
            ret.first = this->handleOperator(it, lhs, rhs, line_nodes);
    }
    for (it = line_nodes.begin(); it != line_nodes.end(); ++it)
    {
        lhs = std::prev(it);
        rhs = std::next(it);
        if ((*it)->priority == priority && (*it)->type == XOR_NODE)
            ret.first = this->handleOperator(it, lhs, rhs, line_nodes);
    }
    if (priority > 1)
        return (this->init_fact_line(line_nodes, priority - 1));
    if (ret.first == NULL)
    {
        ret.first = get_fact_node(line_nodes.front()->name);
        ret.second = line_nodes.front()->type == NOTFACT_NODE ? true : false;
    }
    return (ret);
}

GGraphNode*                     GlobalGraph::handleOperator(std::list<GGraphNode*>::iterator it, std::list<GGraphNode*>::iterator lhs,
                                    std::list<GGraphNode*>::iterator rhs, std::list<GGraphNode*> line_nodes)
{
    std::pair<GGraphNode*, bool>     lhs_node;
    std::pair<GGraphNode*, bool>     rhs_node;

    lhs_node.second = (*lhs)->type == NOTFACT_NODE ? true : false;
    rhs_node.second = (*rhs)->type == NOTFACT_NODE ? true : false;
    if ((*lhs)->type == NOTFACT_NODE || (*lhs)->type == FACT_NODE)
    {
        lhs_node.first = get_fact_node((*lhs)->name);
        delete *lhs;
    }
    else
        lhs_node.first = (*lhs);
    (*it)->in_list.push_back(lhs_node);
    if ((*rhs)->type == NOTFACT_NODE || (*rhs)->type == FACT_NODE)
    {
        rhs_node.first = get_fact_node((*rhs)->name);
        delete *rhs;
    }
    else
        rhs_node.first = (*rhs);
    (*it)->in_list.push_back(rhs_node);
    this->_node_list.push_back((*it));
    line_nodes.erase(lhs);
    line_nodes.erase(rhs);
    return (*it);
}

void                        GlobalGraph::init_rule_line(std::list<GGraphNode*> line_nodes)
{
    for (GGraphNode* node : line_nodes)
    {
        this->get_fact_node(node->name)->value = 1;
    }
}

void                        GlobalGraph::init_query_line(std::list<GGraphNode*> line_nodes)
{
    for (GGraphNode* node : line_nodes)
    {
        this->_query_node.push_back(this->get_fact_node(node->name));
    }
}

GGraphNode*                 GlobalGraph::search_node(std::list<GGraphNode*> lst, char name)
{
    for (GGraphNode* g : lst)
    {
        if (g->name == name)
            return (g);
    }
    return (NULL);
}

GGraphNode*                 GlobalGraph::get_fact_node(char name)
{
    GGraphNode  *ret;
    
    for (GGraphNode* g : this->_fact_list)
    {
        if (g->name == name)
            return (g);
    }
    ret = new GGraphNode();
    ret->name = name;
    ret->type = FACT_NODE;
    ret->value = 0;
    this->_fact_list.push_back(ret);
    return (ret);
}

std::list<GGraphNode*>       GlobalGraph::implied_fact_nodes(std::list<GGraphNode*> *lst)
{
    std::list<GGraphNode*>  implied_nodes;
    GGraphNode              *tmp;
    while (lst->back()->priority == 0)
    {
        // std::cout << lst->back()->type ;
        // std::cout << " IMPLIED " << lst->back()->name << std::endl;
        if (lst->back()->type == FACT_NODE)
        {
            tmp = get_fact_node(lst->back()->name);
            implied_nodes.push_back(tmp);
        }
        delete lst->back();
        lst->pop_back();
    }
    return (implied_nodes);
}

void                        GlobalGraph::remove_tkn_line(std::list<t_tkn*> *tkn, std::list<GGraphNode*> *line_nodes)
{
    while (tkn->front()->r_type != T_ENDL && tkn->begin() != tkn->end())
        tkn->pop_front();
    tkn->pop_front();
    line_nodes->clear();
}

void                        GlobalGraph::display_graph()
{
    std::list<GGraphNode*>::iterator fact_it;
    std::list<GGraphNode*>::iterator it;

    std::cout << "_fact_list:" << std::endl;
    fact_it = this->_fact_list.begin();
    while (fact_it != this->_fact_list.end())
    {
        std::cout << (*fact_it)->name << std::endl;
        ++fact_it;
    }
    std::cout << "_node_list:" << std::endl;
    fact_it = this->_node_list.begin();
    while (fact_it != this->_node_list.end())
    {
        std::cout << (*fact_it)->name << std::endl;
        ++fact_it;
    }
    std::cout << "_query_node:" << std::endl;
    fact_it = this->_query_node.begin();
    while (fact_it != this->_query_node.end())
    {
        display_in_list(*fact_it, 0);
        ++fact_it;
    }
    std::cout << "end display" << std::endl;
}

void                    GlobalGraph::display_in_list(GGraphNode* node, int space)
{
    std::cout << node->name << std::endl;
    for (std::pair<GGraphNode*, bool> n : node->in_list)
    {
        for (int i = 0; i < space + 1; i++){ std::cout << "*";}
        display_in_list(n.first, space + 1);
    }
}

std::list<GGraphNode*>  &GlobalGraph::get_query_list()
{
    return (this->_query_node);
}