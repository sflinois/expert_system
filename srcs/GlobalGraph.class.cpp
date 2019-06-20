/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalGraph.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:15:48 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/20 14:55:14 by sflinois         ###   ########.fr       */
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
    if (tkn.empty())
        ;
}

