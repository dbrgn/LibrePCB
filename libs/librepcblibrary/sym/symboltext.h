/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 Urban Bruhin
 * http://librepcb.org/
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

#ifndef LIBRARY_SYMBOLTEXT_H
#define LIBRARY_SYMBOLTEXT_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/

#include <QtCore>
#include <librepcbcommon/fileio/if_xmlserializableobject.h>
#include <librepcbcommon/units/all_length_units.h>
#include <librepcbcommon/alignment.h>

/*****************************************************************************************
 *  Class SymbolText
 ****************************************************************************************/

namespace library {

/**
 * @brief The SymbolText class
 *
 * @note If you make changes in this class, please check if you also need to modify
 *       the class library#FootprintText as these classes are very similar.
 */
class SymbolText final : public IF_XmlSerializableObject
{
        Q_DECLARE_TR_FUNCTIONS(SymbolText)

    public:

        // Constructors / Destructor
        explicit SymbolText() noexcept;
        explicit SymbolText(const XmlDomElement& domElement) throw (Exception);
        ~SymbolText() noexcept;

        // Getters
        int getLayerId() const noexcept {return mLayerId;}
        const Point& getPosition() const noexcept {return mPosition;}
        const Angle& getRotation() const noexcept {return mRotation;}
        const Length& getHeight() const noexcept {return mHeight;}
        const Alignment& getAlign() const noexcept {return mAlign;}
        const QString& getText() const noexcept {return mText;}

        // Setters
        void setLayerId(int layerId) noexcept {mLayerId = layerId;}
        void setText(const QString& text) noexcept {mText = text;}
        void setPosition(const Point& pos) noexcept {mPosition = pos;}
        void setRotation(const Angle& rotation) noexcept {mRotation = rotation;}
        void setHeight(const Length& height) noexcept {mHeight = height;}
        void setAlign(const Alignment& align) noexcept {mAlign = align;}

        // General Methods

        /// @copydoc IF_XmlSerializableObject#serializeToXmlDomElement()
        XmlDomElement* serializeToXmlDomElement() const throw (Exception) override;


    private:

        // make some methods inaccessible...
        SymbolText(const SymbolText& other);
        SymbolText& operator=(const SymbolText& rhs);

        // Private Methods

        /// @copydoc IF_XmlSerializableObject#checkAttributesValidity()
        bool checkAttributesValidity() const noexcept override;


        // Text Attributes
        int mLayerId;
        QString mText;
        Point mPosition;
        Angle mRotation;
        Length mHeight;
        Alignment mAlign;
};

} // namespace library

#endif // LIBRARY_SYMBOLTEXT_H
