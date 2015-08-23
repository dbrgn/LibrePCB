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

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/

#include <QtCore>
#include "cmdschematicnetlineremove.h"
#include "../schematic.h"
#include "../items/si_netline.h"

namespace project {

/*****************************************************************************************
 *  Constructors / Destructor
 ****************************************************************************************/

CmdSchematicNetLineRemove::CmdSchematicNetLineRemove(Schematic& schematic,
                                                     SI_NetLine& netline,
                                                     UndoCommand* parent) throw (Exception) :
    UndoCommand(tr("Remove netline"), parent),
    mSchematic(schematic), mNetLine(netline)
{
}

CmdSchematicNetLineRemove::~CmdSchematicNetLineRemove() noexcept
{
    if (isExecuted())
        delete &mNetLine;
}

/*****************************************************************************************
 *  Inherited from UndoCommand
 ****************************************************************************************/

void CmdSchematicNetLineRemove::redo() throw (Exception)
{
    mSchematic.removeNetLine(mNetLine); // throws an exception on error

    try
    {
        UndoCommand::redo(); // throws an exception on error
    }
    catch (Exception& e)
    {
        mSchematic.addNetLine(mNetLine);
        throw;
    }
}

void CmdSchematicNetLineRemove::undo() throw (Exception)
{
    mSchematic.addNetLine(mNetLine); // throws an exception on error

    try
    {
        UndoCommand::undo(); // throws an exception on error
    }
    catch (Exception& e)
    {
        mSchematic.removeNetLine(mNetLine);
        throw;
    }
}

/*****************************************************************************************
 *  End of File
 ****************************************************************************************/

} // namespace project
