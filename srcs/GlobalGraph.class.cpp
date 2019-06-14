/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalGraph.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:15:48 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/14 13:41:36 by sflinois         ###   ########.fr       */
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
    return (*this);
}

