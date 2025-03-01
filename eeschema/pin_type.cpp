/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2004-2023 KiCad Developers, see change_log.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include <bitmaps.h>
#include <cstddef>
#include <core/arraydim.h>
#include <magic_enum.hpp>
#include <lib_pin.h>
#include "pgm_base.h"


// These are true singletons so it's OK for them to be globals.

static std::vector<BITMAPS> g_typeIcons;
static wxArrayString        g_typeNames;

static std::vector<BITMAPS> g_shapeIcons;
static wxArrayString        g_shapeNames;

static std::vector<BITMAPS> g_orientationIcons;
static wxArrayString        g_orientationNames;


struct pinTypeStruct
{
    wxString name;
    BITMAPS  bitmap;
};


std::map<ELECTRICAL_PINTYPE, struct pinTypeStruct> g_pinTypes = {
    { ELECTRICAL_PINTYPE::PT_INPUT,        { _( "Input" ),          BITMAPS::pintype_input } },
    { ELECTRICAL_PINTYPE::PT_OUTPUT,       { _( "Output" ),         BITMAPS::pintype_output } },
    { ELECTRICAL_PINTYPE::PT_BIDI,         { _( "Bidirectional" ),  BITMAPS::pintype_bidi } },
    { ELECTRICAL_PINTYPE::PT_TRISTATE,     { _( "Tri-state" ),      BITMAPS::pintype_3states } },
    { ELECTRICAL_PINTYPE::PT_PASSIVE,      { _( "Passive" ),        BITMAPS::pintype_passive } },
    { ELECTRICAL_PINTYPE::PT_NIC,          { _( "Free" ),           BITMAPS::pintype_nic } },
    { ELECTRICAL_PINTYPE::PT_UNSPECIFIED,  { _( "Unspecified" ),    BITMAPS::pintype_notspecif } },
    { ELECTRICAL_PINTYPE::PT_POWER_IN,     { _( "Power input" ),    BITMAPS::pintype_powerinput } },
    { ELECTRICAL_PINTYPE::PT_POWER_OUT,    { _( "Power output" ),   BITMAPS::pintype_poweroutput } },
    { ELECTRICAL_PINTYPE::PT_OPENCOLLECTOR,{ _( "Open collector" ), BITMAPS::pintype_opencoll } },
    { ELECTRICAL_PINTYPE::PT_OPENEMITTER,  { _( "Open emitter" ),   BITMAPS::pintype_openemit } },
    { ELECTRICAL_PINTYPE::PT_NC,           { _( "Unconnected" ),    BITMAPS::pintype_noconnect } },
};


int g_pinTypesLanguage = wxLANGUAGE_UNKNOWN;


struct pinShapeStruct
{
    wxString name;
    BITMAPS  bitmap;
};


// clang-format off
const std::map<GRAPHIC_PINSHAPE, struct pinShapeStruct> pinShapes = {
    { GRAPHIC_PINSHAPE::LINE,               { _( "Line" ),               BITMAPS::pinshape_normal } },
    { GRAPHIC_PINSHAPE::INVERTED,           { _( "Inverted" ),           BITMAPS::pinshape_invert } },
    { GRAPHIC_PINSHAPE::CLOCK,              { _( "Clock" ),              BITMAPS::pinshape_clock_normal } },
    { GRAPHIC_PINSHAPE::INVERTED_CLOCK,     { _( "Inverted clock" ),     BITMAPS::pinshape_clock_invert } },
    { GRAPHIC_PINSHAPE::INPUT_LOW,          { _( "Input low" ),          BITMAPS::pinshape_active_low_input } },
    { GRAPHIC_PINSHAPE::CLOCK_LOW,          { _( "Clock low" ),          BITMAPS::pinshape_clock_active_low } },
    { GRAPHIC_PINSHAPE::OUTPUT_LOW,         { _( "Output low" ),         BITMAPS::pinshape_active_low_output } },
    { GRAPHIC_PINSHAPE::FALLING_EDGE_CLOCK, { _( "Falling edge clock" ), BITMAPS::pinshape_clock_fall } },
    { GRAPHIC_PINSHAPE::NONLOGIC,           { _( "NonLogic" ),           BITMAPS::pinshape_nonlogic } },
};
// clang-format on


// clang-format off
std::map<PIN_ORIENTATION, struct pinShapeStruct> pinOrientations = {
    { PIN_ORIENTATION::PIN_RIGHT, { _( "Right" ), BITMAPS::pinorient_right } },
    { PIN_ORIENTATION::PIN_LEFT,  { _( "Left" ),  BITMAPS::pinorient_left } },
    { PIN_ORIENTATION::PIN_UP,    { _( "Up" ),    BITMAPS::pinorient_up } },
    { PIN_ORIENTATION::PIN_DOWN,  { _( "Down" ),  BITMAPS::pinorient_down } },
};
// clang-format on


PIN_ORIENTATION PinOrientationCode( size_t index )
{
    wxASSERT( index < magic_enum::enum_count<PIN_ORIENTATION>() );
    return magic_enum::enum_value<PIN_ORIENTATION>( index );
}


int PinOrientationIndex( PIN_ORIENTATION code )
{
    auto index = magic_enum::enum_index<PIN_ORIENTATION>( code );

    if( index.has_value() )
        return index.value();

    return wxNOT_FOUND;
}


void InitTables()
{
    for( unsigned i = 0; i < ELECTRICAL_PINTYPES_TOTAL; ++i )
    {
        g_typeIcons.push_back( ElectricalPinTypeGetBitmap( static_cast<ELECTRICAL_PINTYPE>( i ) ) );
        g_typeNames.push_back( ElectricalPinTypeGetText( static_cast<ELECTRICAL_PINTYPE>( i ) ) );
    }

    for( unsigned i = 0; i < GRAPHIC_PINSHAPES_TOTAL; ++i )
    {
        g_shapeIcons.push_back( PinShapeGetBitmap( static_cast<GRAPHIC_PINSHAPE>( i ) ) );
        g_shapeNames.push_back( PinShapeGetText( static_cast<GRAPHIC_PINSHAPE>( i ) ) );
    }

    for( PIN_ORIENTATION orientation : magic_enum::enum_values<PIN_ORIENTATION>() )
    {
        g_orientationIcons.push_back( PinOrientationGetBitmap( orientation ) );
        g_orientationNames.push_back( PinOrientationName( orientation ) );
    }
}


const wxArrayString& PinTypeNames()
{
    if( g_typeNames.empty() )
        InitTables();

    return g_typeNames;
}


const std::vector<BITMAPS>& PinTypeIcons()
{
    if( g_typeIcons.empty() )
        InitTables();

    return g_typeIcons;
}


const wxArrayString& PinShapeNames()
{
    if( g_shapeNames.empty() )
        InitTables();

    return g_shapeNames;
}


const std::vector<BITMAPS>& PinShapeIcons()
{
    if( g_shapeIcons.empty() )
        InitTables();

    return g_shapeIcons;
}


const wxArrayString& PinOrientationNames()
{
    if( g_orientationNames.empty() )
        InitTables();

    return g_orientationNames;
}


const std::vector<BITMAPS>& PinOrientationIcons()
{
    if( g_orientationIcons.empty() )
        InitTables();

    return g_orientationIcons;
}


wxString ElectricalPinTypeGetText( ELECTRICAL_PINTYPE aType )
{
    if( g_pinTypesLanguage != Pgm().GetSelectedLanguageIdentifier() )
    {
        g_pinTypes[ELECTRICAL_PINTYPE::PT_INPUT].name =         _( "Input" );
        g_pinTypes[ELECTRICAL_PINTYPE::PT_OUTPUT].name =        _( "Output" );
        g_pinTypes[ELECTRICAL_PINTYPE::PT_BIDI].name =          _( "Bidirectional" );
        g_pinTypes[ELECTRICAL_PINTYPE::PT_TRISTATE].name =      _( "Tri-state" );
        g_pinTypes[ELECTRICAL_PINTYPE::PT_PASSIVE].name =       _( "Passive" );
        g_pinTypes[ELECTRICAL_PINTYPE::PT_NIC].name =           _( "Free" );
        g_pinTypes[ELECTRICAL_PINTYPE::PT_UNSPECIFIED].name =   _( "Unspecified" );
        g_pinTypes[ELECTRICAL_PINTYPE::PT_POWER_IN].name =      _( "Power input" );
        g_pinTypes[ELECTRICAL_PINTYPE::PT_POWER_OUT].name =     _( "Power output" );
        g_pinTypes[ELECTRICAL_PINTYPE::PT_OPENCOLLECTOR].name = _( "Open collector" );
        g_pinTypes[ELECTRICAL_PINTYPE::PT_OPENEMITTER].name =   _( "Open emitter" );
        g_pinTypes[ELECTRICAL_PINTYPE::PT_NC].name =            _( "Unconnected" );

        g_pinTypesLanguage = Pgm().GetSelectedLanguageIdentifier();
    }

    auto findIt = g_pinTypes.find( aType );

    wxCHECK_MSG( findIt != g_pinTypes.end(), wxT( "???" ), wxT( "Pin type not found!" ) );

    return findIt->second.name;
}


BITMAPS ElectricalPinTypeGetBitmap( ELECTRICAL_PINTYPE aType )
{
    auto findIt = g_pinTypes.find( aType );

    wxCHECK_MSG( findIt != g_pinTypes.end(), BITMAPS::INVALID_BITMAP, wxT( "Pin type not found!" ) );

    return findIt->second.bitmap;
}


wxString PinShapeGetText( GRAPHIC_PINSHAPE aShape )
{
    auto findIt = pinShapes.find( aShape );

    wxCHECK_MSG( findIt != pinShapes.end(), wxT( "?" ), wxT( "Pin type not found!" ) );

    return findIt->second.name;
}


BITMAPS PinShapeGetBitmap( GRAPHIC_PINSHAPE aShape )
{
    auto findIt = pinShapes.find( aShape );

    wxCHECK_MSG( findIt != pinShapes.end(), BITMAPS::INVALID_BITMAP, wxT( "Pin type not found!" ) );

    return findIt->second.bitmap;
}


wxString PinOrientationName( PIN_ORIENTATION aOrientation )
{
    auto findIt = pinOrientations.find( aOrientation );

    wxCHECK_MSG( findIt != pinOrientations.end(), wxT( "?" ), wxT( "Pin orientation not found!" ) );

    return findIt->second.name;
}


BITMAPS PinOrientationGetBitmap( PIN_ORIENTATION aOrientation )
{
    auto findIt = pinOrientations.find( aOrientation );

    wxCHECK_MSG( findIt != pinOrientations.end(), BITMAPS::INVALID_BITMAP,
                 wxT( "Pin orientation not found!" ) );

    return findIt->second.bitmap;
}
