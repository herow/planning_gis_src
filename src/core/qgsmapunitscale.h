/***************************************************************************
  qgsmapunitscale.h
  Struct for storing maximum and minimum scales for measurements in map units
  -------------------
   begin                : April 2014
   copyright            : (C) Sandro Mani
   email                : smani at sourcepole dot ch

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSMAPUNITSCALE_H
#define QGSMAPUNITSCALE_H

#include <QtCore>
#include "qgsrendercontext.h"

/**
 * \class QgsMapUnitScale
 * \brief Struct for storing maximum and minimum scales for measurements in map units
 *
 * For measurements in map units, a minimum and a maximum scale can be defined.
 * Outside this range, the measurements aren't scaled anymore proportionally to
 * the map scale.
 */

class CORE_EXPORT QgsMapUnitScale
{
  public:

    /** Constructor for QgsMapUnitScale
     * @param minScale minimum allowed scale, or 0.0 if no minimum scale set
     * @param maxScale maximum allowed scale, or 0.0 if no maximum scale set
     */
    QgsMapUnitScale( double minScale = 0.0, double maxScale = 0.0 ) : minScale( minScale ), maxScale( maxScale ) {}

    /** The minimum scale, or 0.0 if unset */
    double minScale;
    /** The maximum scale, or 0.0 if unset */
    double maxScale;

    /** Computes a map units per pixel scaling factor, respecting the minimum and maximum scales
     * set for the object.
     * @param c render context
     * @returns map units per pixel, limited between minimum and maximum scales
     */
    double computeMapUnitsPerPixel( const QgsRenderContext& c ) const
    {
      double mup = c.mapToPixel().mapUnitsPerPixel();
      double renderScale = c.rendererScale(); // Note: this value is 1 / scale
      if ( minScale != 0 )
      {
        mup = qMin( mup / ( minScale * renderScale ), mup );
      }
      if ( maxScale != 0 )
      {
        mup = qMax( mup / ( maxScale * renderScale ), mup );
      }
      return mup;
    }

    bool operator==( const QgsMapUnitScale& other ) const
    {
      return minScale == other.minScale && maxScale == other.maxScale;
    }

    bool operator!=( const QgsMapUnitScale& other ) const
    {
      return minScale != other.minScale || maxScale != other.maxScale;
    }
};


#endif // QGSMAPUNITSCALE_H


