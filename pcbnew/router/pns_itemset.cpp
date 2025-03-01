/*
 * KiRouter - a push-and-(sometimes-)shove PCB router
 *
 * Copyright (C) 2013-2014 CERN
 * Copyright (C) 2016-2023 KiCad Developers, see AUTHORS.txt for contributors.
 * Author: Tomasz Wlostowski <tomasz.wlostowski@cern.ch>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pns_itemset.h"
#include "pns_line.h"

namespace PNS {

ITEM_SET::~ITEM_SET()
{
}


void ITEM_SET::Add( const LINE& aLine )
{
    LINE* copy = aLine.Clone();
    copy->SetOwner( this );
    m_items.emplace_back( copy );
}


void ITEM_SET::Prepend( const LINE& aLine )
{
    LINE* copy = aLine.Clone();
    copy->SetOwner( this );
    m_items.emplace( m_items.begin(), copy );
}


ITEM_SET& ITEM_SET::FilterLayers( int aStart, int aEnd, bool aInvert )
{
    std::vector<ITEM*> newItems;
    LAYER_RANGE        l;

    if( aEnd < 0 )
        l = LAYER_RANGE( aStart );
    else
        l = LAYER_RANGE( aStart, aEnd );

    for( ITEM* item : m_items )
    {
        if( item->Layers().Overlaps( l ) ^ aInvert )
            newItems.push_back( item );
    }

    m_items = std::move( newItems );

    return *this;
}


ITEM_SET& ITEM_SET::FilterKinds( int aKindMask, bool aInvert )
{
    std::vector<ITEM*> newItems;

    for( ITEM *item : m_items )
    {
        if( item->OfKind( aKindMask ) ^ aInvert )
            newItems.push_back( item );
    }

    m_items = std::move( newItems );

    return *this;
}


ITEM_SET& ITEM_SET::FilterMarker( int aMarker, bool aInvert )
{
    std::vector<ITEM*> newItems;

    for( ITEM* item : m_items )
    {
        if( item->Marker() & aMarker )
            newItems.push_back( item );
    }

    m_items = std::move( newItems );

    return *this;
}


ITEM_SET& ITEM_SET::FilterNet( NET_HANDLE aNet, bool aInvert )
{
    std::vector<ITEM*> newItems;

    for( ITEM *item : m_items )
    {
        if( ( item->Net() == aNet ) ^ aInvert )
            newItems.push_back( item );
    }

    m_items = std::move( newItems );

    return *this;
}


ITEM_SET& ITEM_SET::ExcludeItem( const ITEM* aItem )
{
    std::vector<ITEM*> newItems;

    for( ITEM* item : m_items )
    {
        if( item != aItem )
            newItems.push_back( item );
    }

    m_items = std::move( newItems );

    return *this;
}

}
