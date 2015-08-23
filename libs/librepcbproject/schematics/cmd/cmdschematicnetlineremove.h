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

#ifndef PROJECT_CMDSCHEMATICNETLINEREMOVE_H
#define PROJECT_CMDSCHEMATICNETLINEREMOVE_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/

#include <QtCore>
#include <librepcbcommon/undocommand.h>
#include <librepcbcommon/exceptions.h>

/*****************************************************************************************
 *  Forward Declarations
 ****************************************************************************************/

namespace project {
class Schematic;
class SI_NetLine;
}

/*****************************************************************************************
 *  Class CmdSchematicNetLineRemove
 ****************************************************************************************/

namespace project {

/**
 * @brief The CmdSchematicNetLineRemove class
 */
class CmdSchematicNetLineRemove final : public UndoCommand
{
    public:

        // Constructors / Destructor
        explicit CmdSchematicNetLineRemove(Schematic& schematic, SI_NetLine& netline,
                                            UndoCommand* parent = 0) throw (Exception);
        ~CmdSchematicNetLineRemove() noexcept;

        // Inherited from UndoCommand
        void redo() throw (Exception) override;
        void undo() throw (Exception) override;

    private:

        Schematic& mSchematic;
        SI_NetLine& mNetLine;
};

} // namespace project

#endif // PROJECT_CMDSCHEMATICNETLINEREMOVE_H
