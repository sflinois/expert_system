/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GGraphNode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:35:28 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/25 13:47:12 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GGRAPHNODE_HPP
# define GGRAPHNODE_HPP

# define LEFT_NOT 1
# define RIGHT_NOT 2

#include <list>

enum node_type{
    FACT_NODE,
    NOTFACT_NODE,
    XOR_NODE,
    OR_NODE,
    AND_NODE
};

struct GGraphNode
{
    node_type                               type;
    std::list<std::pair<GGraphNode*, bool>> in_list;
    char                                    value;
    char                                    name;
    char                                    priority;
};

#endif