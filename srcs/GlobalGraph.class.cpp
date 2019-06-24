/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalGraph.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:15:48 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/24 16:12:45 by sflinois         ###   ########.fr       */
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
    //this->_tfact_node = rhs._tfact_node;
    //this->_query_node = rhs._query_node;
    return (*this);
}

void                        GlobalGraph::init(std::list<t_tkn*> tkn)
{
    std::list<GGraphNode*>  line_nodes;
    std::list<GGraphNode*>  implied_nodes;
    line_type               l_type;
    int                     priority = 1;
    
    while((l_type = get_line_nodes(&tkn, &line_nodes)) != L_QUERY)
    {
        std::cout << "init line" << std::endl;
        for (GGraphNode* g : line_nodes)
        {
            std::cout << g->name << ";" << static_cast<int>(g->priority) << ";" << g->type << ";" << static_cast<int>(g->value) << " | ";
        }
        std::cout << std::endl;
        if (l_type == L_FACT)
        {
            implied_nodes = implied_fact_nodes(&line_nodes);
            for (GGraphNode* n : line_nodes)
                if (n->priority > priority)
                    priority = n->priority;
            for (GGraphNode* n : implied_nodes)
                n->in_list.push_back(init_fact_line(line_nodes, priority));
        }
        else if (l_type == L_RULE)
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
        std::cout << (*it)->r_type << std::endl;
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

GGraphNode*                 GlobalGraph::init_fact_line(std::list<GGraphNode*> line_nodes, int priority)
{
    std::list<GGraphNode*>::iterator it;
    std::list<GGraphNode*>::iterator lhs;
    std::list<GGraphNode*>::iterator rhs;
    GGraphNode*                      ret;

    lhs = line_nodes.begin();
    rhs = line_nodes.begin();
    rhs++;
    for (it = line_nodes.begin(); it != line_nodes.end(); ++it)
    {
        rhs++;
        if ((*it)->priority == priority && (*it)->type == AND_NODE)
            ret = this->handleOperator(it, lhs, rhs, line_nodes);
        lhs++;
    }
    for (it = line_nodes.begin(); it != line_nodes.end(); ++it)
    {
        rhs++;
        if ((*it)->priority == priority && (*it)->type == OR_NODE)
            ret = this->handleOperator(it, lhs, rhs, line_nodes);
        lhs++;
    }
    for (it = line_nodes.begin(); it != line_nodes.end(); ++it)
    {
        rhs++;
        if ((*it)->priority == priority && (*it)->type == XOR_NODE)
            ret = this->handleOperator(it, lhs, rhs, line_nodes);
        lhs++;
    }
    if (priority > 1)
        return (this->init_fact_line(line_nodes, priority - 1));
    return (ret);
}

GGraphNode*                 GlobalGraph::handleOperator(std::list<GGraphNode*>::iterator it, std::list<GGraphNode*>::iterator lhs,
                                    std::list<GGraphNode*>::iterator rhs, std::list<GGraphNode*> line_nodes)
{
    if ((*lhs)->type == NOTFACT_NODE)
        (*it)->is_not |= 1;
    if ((*rhs)->type == NOTFACT_NODE)
        (*it)->is_not |= 2;
    if ((*lhs)->type == NOTFACT_NODE || (*lhs)->type == FACT_NODE)
    {
        (*it)->in_list.push_back(get_fact_node((*lhs)->name));
        delete *lhs;
    }
    else
        (*it)->in_list.push_back((*lhs));
    if ((*rhs)->type == NOTFACT_NODE || (*rhs)->type == FACT_NODE)
    {
        (*it)->in_list.push_back(get_fact_node((*rhs)->name));
        delete *rhs;
    }
    else
        (*it)->in_list.push_back((*rhs));
    this->_node_list.push_back((*it));
    line_nodes.erase(lhs);
    line_nodes.erase(rhs);
    return (*it);
}

void                        GlobalGraph::init_rule_line(std::list<GGraphNode*> line_nodes)
{
    for (GGraphNode* node : line_nodes)
        this->get_fact_node(node->name)->value = 1;
}

void                        GlobalGraph::init_query_line(std::list<GGraphNode*> line_nodes)
{
    for (GGraphNode* node : line_nodes)
        this->_query_node.push_back(this->get_fact_node(node->name));
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
        if (lst->back()->type == FACT_NODE &&
            search_node(implied_nodes, lst->back()->name) == NULL)
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

void                        GlobalGraph::display_graph(){
    std::list<GGraphNode*>::iterator fact_it;
    std::list<GGraphNode*>::iterator it;;

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
        std::cout << (*fact_it)->name << std::endl;
        ++fact_it;
    }
}