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

#ifndef PROJECT_CMDSYMBOLINSTANCEADD_H
#define PROJECT_CMDSYMBOLINSTANCEADD_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/

#include <QtCore>
#include <librepcbcommon/units/all_length_units.h>
#include <librepcbcommon/undocommand.h>
#include <librepcbcommon/exceptions.h>

/*****************************************************************************************
 *  Forward Declarations
 ****************************************************************************************/

namespace project {
class Schematic;
class GenCompInstance;
class SI_Symbol;
}

/*****************************************************************************************
 *  Class CmdSymbolInstanceAdd
 ****************************************************************************************/

namespace project {

/**
 * @brief The CmdSymbolInstanceAdd class
 */
class CmdSymbolInstanceAdd final : public UndoCommand
{
    public:

        // Constructors / Destructor
        explicit CmdSymbolInstanceAdd(Schematic& schematic, GenCompInstance& genComp,
                                      const QUuid& symbolItem, const Point& position = Point(),
                                      const Angle& angle = Angle(), UndoCommand* parent = 0) throw (Exception);
        explicit CmdSymbolInstanceAdd(SI_Symbol& symbol, UndoCommand* parent = 0) throw (Exception);
        ~CmdSymbolInstanceAdd() noexcept;

        // Getters
        SI_Symbol* getSymbol() const noexcept {return mSymbol;}

        // Inherited from UndoCommand
        void redo() throw (Exception) override;
        void undo() throw (Exception) override;

    private:

        // Attributes from the constructor
        Schematic& mSchematic;

        /// @brief The created symbol
        SI_Symbol* mSymbol;
};

} // namespace project

#endif // PROJECT_CMDSYMBOLINSTANCEADD_H
