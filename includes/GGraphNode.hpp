/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GGraphNode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:35:28 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/14 14:03:42 by sflinois         ###   ########.fr       */
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
    AND_NODE,
    OR_NODE,
    XOR_NODE,
    IMPLY_NODE,
};

struct GGraphNode
{
    node_type               type;
    std::list<GGraphNode*>  in_list;
    std::list<GGraphNode*>  out_list;
    char                    is_not;
    bool                    value;
};

#endif