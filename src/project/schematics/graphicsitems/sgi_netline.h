/*
 * EDA4U - Professional EDA for everyone!
 * Copyright (C) 2013 Urban Bruhin
 * http://eda4u.ubruhin.ch/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PROJECT_SGI_NETLINE_H
#define PROJECT_SGI_NETLINE_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/

#include <QtCore>
#include <QtWidgets>
#include "sgi_base.h"

/*****************************************************************************************
 *  Forward Declarations
 ****************************************************************************************/

class SchematicLayer;

namespace project {
class SI_NetLine;
}

/*****************************************************************************************
 *  Class SGI_NetLine
 ****************************************************************************************/

namespace project {

/**
 * @brief The SGI_NetLine class
 */
class SGI_NetLine final : public SGI_Base
{
    public:

        // Types

        /// to make  qgraphicsitem_cast() working
        enum {Type = Schematic::Type_NetLine};

        // Constructors / Destructor
        explicit SGI_NetLine(SI_NetLine& netline) noexcept;
        ~SGI_NetLine() noexcept;

        // Getters
        SI_NetLine& getNetLine() const {return mNetLine;}

        // General Methods
        void updateCacheAndRepaint() noexcept;

        // Inherited from QGraphicsItem
        int type() const {return Type;} ///< to make  qgraphicsitem_cast() working
        QRectF boundingRect() const {return mBoundingRect;}
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);


    private:

        // make some methods inaccessible...
        SGI_NetLine() = delete;
        SGI_NetLine(const SGI_NetLine& other) = delete;
        SGI_NetLine& operator=(const SGI_NetLine& rhs) = delete;

        // Attributes
        SI_NetLine& mNetLine;
        SchematicLayer* mLayer;

        // Cached Attributes
        QLineF mLineF;
        QRectF mBoundingRect;
};

} // namespace project

#endif // PROJECT_SGI_NETLINE_H
