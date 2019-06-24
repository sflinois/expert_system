/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalGraph.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:15:43 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/24 17:15:38 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALGRAPH_CLASS_HPP
# define GLOBALGRAPH_CLASS_HPP

# include "expert_system.h"
# include "GGraphNode.hpp"
# include <map>
# include <iostream>

class GlobalGraph
{
    public:
        GlobalGraph();
        GlobalGraph(GlobalGraph const &src);
        ~GlobalGraph();

        GlobalGraph&        operator=(GlobalGraph const &rhs);

        void                init(std::list<t_tkn*> tkn);
        void                display_graph();
        void                display_in_list(GGraphNode* node, int space);

    private:

        line_type               get_line_nodes(std::list<t_tkn*> *tkn, std::list<GGraphNode*>* line_nodes);
        GGraphNode*             init_fact_line(std::list<GGraphNode*> line_nodes, int priority);
        GGraphNode*             handleOperator(std::list<GGraphNode*>::iterator it,
                                    std::list<GGraphNode*>::iterator lsh,
                                    std::list<GGraphNode*>::iterator rhs,
                                    std::list<GGraphNode*> line_nodes);

        void                    init_rule_line(std::list<GGraphNode*> line_nodes);
        void                    init_query_line(std::list<GGraphNode*> line_nodes);
        GGraphNode*             search_node(std::list<GGraphNode*> lst, char value);
        GGraphNode*             get_fact_node(char name);
        std::list<GGraphNode*>  implied_fact_nodes(std::list<GGraphNode*> *lst);
        void                    remove_tkn_line(std::list<t_tkn*> *tkn, std::list<GGraphNode*> *line_nodes);


        std::list<GGraphNode*>  _node_list;
        std::list<GGraphNode*>  _fact_list;
        std::list<GGraphNode*>  _query_node;
};

#endif
