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
#include "cmdnetsignaledit.h"
#include "../netsignal.h"
#include "../circuit.h"

namespace project {

/*****************************************************************************************
 *  Constructors / Destructor
 ****************************************************************************************/

CmdNetSignalEdit::CmdNetSignalEdit(Circuit& circuit, NetSignal& netsignal,
                                         UndoCommand* parent) throw (Exception) :
    UndoCommand(tr("Edit netsignal"), parent), mCircuit(circuit), mNetSignal(netsignal),
    mOldName(netsignal.getName()), mNewName(mOldName),
    mOldIsAutoName(netsignal.hasAutoName()), mNewIsAutoName(mOldIsAutoName)
{
}

CmdNetSignalEdit::~CmdNetSignalEdit() noexcept
{
}

/*****************************************************************************************
 *  Setters
 ****************************************************************************************/

void CmdNetSignalEdit::setName(const QString& name, bool isAutoName) noexcept
{
    Q_ASSERT((mRedoCount == 0) && (mUndoCount == 0));
    mNewName = name;
    mNewIsAutoName = isAutoName;
}

/*****************************************************************************************
 *  Inherited from UndoCommand
 ****************************************************************************************/

void CmdNetSignalEdit::redo() throw (Exception)
{
    try
    {
        mCircuit.setNetSignalName(mNetSignal, mNewName, mNewIsAutoName);
        UndoCommand::redo();
    }
    catch (Exception& e)
    {
        mCircuit.setNetSignalName(mNetSignal, mOldName, mOldIsAutoName);
        throw;
    }
}

void CmdNetSignalEdit::undo() throw (Exception)
{
    try
    {
        mCircuit.setNetSignalName(mNetSignal, mOldName, mOldIsAutoName);
        UndoCommand::undo();
    }
    catch (Exception& e)
    {
        mCircuit.setNetSignalName(mNetSignal, mNewName, mNewIsAutoName);
        throw;
    }
}

/*****************************************************************************************
 *  End of File
 ****************************************************************************************/

} // namespace project
