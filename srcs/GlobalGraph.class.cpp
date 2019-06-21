/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalGraph.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:15:48 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/21 16:03:37 by sflinois         ###   ########.fr       */
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
    GGraphNode  *node = new GGraphNode();
    node->type = FACT_NODE;
    node->value = false;
    return (*this);
}

void                        GlobalGraph::init(std::list<t_tkn*> tkn)
{
    std::list<GGraphNode*>  line_nodes;
    std::list<GGraphNode*>  implied_nodes;
    line_type               l_type;
    int                     priority = 1;
    
    while((l_type = get_line_nodes(tkn, &line_nodes)) != L_QUERY)
    {
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
    }
}

line_type                   GlobalGraph::get_line_nodes(std::list<t_tkn*> tkn,
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
    
    ret = tkn.front()->l_type;
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
            tmp = new GGraphNode();
            tmp->type = type_map[(*it)->r_type];
            tmp->priority = priority;
            line_nodes->push_back(tmp);
        }
        it++;
    }
    return (ret);
}

GGraphNode*                 GlobalGraph::init_fact_line(std::list<GGraphNode*> line_nodes, int priority)
{
    std::list<GGraphNode*>::iterator it;
    GGraphNode                       *lhs;
    GGraphNode                       *rhs;

    for (it = line_nodes.begin(); it != line_nodes.end(); ++it)
    {
        if ((*it)->priority == priority && (*it)->type == AND_NODE)
        {
            
        }
    }
    return NULL; //TO RM
}

void                        GlobalGraph::init_rule_line(std::list<GGraphNode*> line_nodes)
{
    
}

GGraphNode*                 GlobalGraph::search_node(std::list<GGraphNode*> lst, char value)
{
    for (GGraphNode* g : lst)
    {
        if (g->value == value)
            return (g);
    }
    return (NULL);
}

GGraphNode*                 GlobalGraph::get_fact_node(char value)
{
    GGraphNode  *ret;
    
    for (GGraphNode* g : this->_fact_list)
    {
        if (g->value == value)
            return (g);
    }
    ret = new GGraphNode();
    ret->name = value;
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
        if (search_node(implied_nodes, lst->back()->value) == NULL)
        {
            tmp = get_fact_node(lst->back()->value);
            implied_nodes.push_back(tmp);
        }
        delete lst->back();
        lst->pop_back();
    }
}