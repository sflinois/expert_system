/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalGraph.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:15:43 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/14 14:05:27 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALGRAPH_CLASS_HPP
# define GLOBALGRAPH_CLASS_HPP

# include "expert_system.h"
# include "GGraphNode.hpp"

class GlobalGraph
{
    public:
        GlobalGraph();
        GlobalGraph(GlobalGraph const &src);
        ~GlobalGraph();

        GlobalGraph&         operator=(GlobalGraph const &rhs);

    private:
        std::list<GGraphNode*>  node_list;
};

#endif
