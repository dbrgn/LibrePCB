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
#include "bi_footprintpad.h"
#include "bi_footprint.h"
#include <librepcblibrary/fpt/footprint.h>
#include <librepcblibrary/fpt/footprintpad.h>
#include "../board.h"
#include "../../project.h"
#include "../../circuit/circuit.h"
#include "../../settings/projectsettings.h"
#include <librepcbcommon/graphics/graphicsscene.h>
#include "../componentinstance.h"

namespace project {

/*****************************************************************************************
 *  Constructors / Destructor
 ****************************************************************************************/

BI_FootprintPad::BI_FootprintPad(BI_Footprint& footprint, const QUuid& padUuid) :
    BI_Base(), mCircuit(footprint.getComponentInstance().getBoard().getProject().getCircuit()),
    mFootprint(footprint), mFootprintPad(nullptr), /*mGenCompSignal(nullptr),
    mGenCompSignalInstance(nullptr),*/ mAddedToBoard(false),
    /*mRegisteredNetPoint(nullptr),*/ mGraphicsItem(nullptr)
{
    // read attributes
    mFootprintPad = mFootprint.getLibFootprint().getPadByUuid(padUuid);
    if (!mFootprintPad)
    {
        throw RuntimeError(__FILE__, __LINE__, padUuid.toString(),
            QString(tr("Invalid footprint pad UUID: \"%1\"")).arg(padUuid.toString()));
    }

    mGraphicsItem = new BGI_FootprintPad(*this);
    updatePosition();
}

BI_FootprintPad::~BI_FootprintPad()
{
    //Q_ASSERT(mRegisteredNetPoint == nullptr);
    delete mGraphicsItem;       mGraphicsItem = nullptr;
}

/*****************************************************************************************
 *  Getters
 ****************************************************************************************/

Project& BI_FootprintPad::getProject() const noexcept
{
    return mFootprint.getProject();
}

Board& BI_FootprintPad::getBoard() const noexcept
{
    return mFootprint.getBoard();
}

const QUuid& BI_FootprintPad::getLibPadUuid() const noexcept
{
    return mFootprintPad->getUuid();
}

/*QString BI_FootprintPad::getDisplayText(bool returnGenCompSignalNameIfEmpty,
                                     bool returnPinNameIfEmpty) const noexcept
{
    const QStringList& localeOrder = mCircuit.getProject().getSettings().getLocaleOrder(true);

    QString text;
    switch (mSymbol.getGenCompSymbVarItem().getDisplayTypeOfPin(mSymbolPin->getUuid()))
    {
        case library::GenCompSymbVarItem::PinDisplayType_t::PinName:
            text = mSymbolPin->getName(localeOrder); break;
        case library::GenCompSymbVarItem::PinDisplayType_t::GenCompSignal:
            if (mGenCompSignal) text = mGenCompSignal->getName(localeOrder); break;
        case library::GenCompSymbVarItem::PinDisplayType_t::NetSignal:
            if (mGenCompSignalInstance->getNetSignal()) text = mGenCompSignalInstance->getNetSignal()->getName(); break;
        default: break;
    }
    if (text.isEmpty() && returnGenCompSignalNameIfEmpty && mGenCompSignal)
        text = mGenCompSignal->getName(localeOrder);
    if (text.isEmpty() && returnPinNameIfEmpty)
        text = mSymbolPin->getName(localeOrder);
    return text;
}*/

/*****************************************************************************************
 *  General Methods
 ****************************************************************************************/

void BI_FootprintPad::updatePosition() noexcept
{
    mPosition = mFootprint.mapToScene(mFootprintPad->getPosition());
    mRotation = mFootprint.getRotation() + mFootprintPad->getRotation();
    mGraphicsItem->setPos(mPosition.toPxQPointF());
    mGraphicsItem->setRotation(mRotation.toDeg());
    bool m = (mGraphicsItem->transform().m11() * mGraphicsItem->transform().m22() < qreal(0));
    if (getIsMirrored() != m) mGraphicsItem->setTransform(QTransform::fromScale(qreal(-1), qreal(1)), true);
    mGraphicsItem->updateCacheAndRepaint();
    //if (mRegisteredNetPoint)
    //    mRegisteredNetPoint->setPosition(mPosition);
}

/*void BI_FootprintPad::registerNetPoint(SI_NetPoint& netpoint)
{
    Q_ASSERT(mRegisteredNetPoint == nullptr);
    mRegisteredNetPoint = &netpoint;
    updateErcMessages();
}

void BI_FootprintPad::unregisterNetPoint(SI_NetPoint& netpoint)
{
    Q_UNUSED(netpoint); // to avoid compiler warning in release mode
    Q_ASSERT(mRegisteredNetPoint == &netpoint);
    mRegisteredNetPoint = nullptr;
    updateErcMessages();
}*/

void BI_FootprintPad::addToBoard(GraphicsScene& scene) noexcept
{
    Q_ASSERT(mAddedToBoard == false);
    //Q_ASSERT(mRegisteredNetPoint == nullptr);
    //mGenCompSignalInstance->registerSymbolPin(*this);
    scene.addItem(*mGraphicsItem);
    mAddedToBoard = true;
}

void BI_FootprintPad::removeFromBoard(GraphicsScene& scene) noexcept
{
    Q_ASSERT(mAddedToBoard == true);
    //Q_ASSERT(mRegisteredNetPoint == nullptr);
    //mGenCompSignalInstance->unregisterSymbolPin(*this);
    scene.removeItem(*mGraphicsItem);
    mAddedToBoard = false;
}

/*****************************************************************************************
 *  Inherited from BI_Base
 ****************************************************************************************/

bool BI_FootprintPad::getIsMirrored() const noexcept
{
    return mFootprint.getIsMirrored();
}

QPainterPath BI_FootprintPad::getGrabAreaScenePx() const noexcept
{
    return mGraphicsItem->sceneTransform().map(mGraphicsItem->shape());
}

void BI_FootprintPad::setSelected(bool selected) noexcept
{
    BI_Base::setSelected(selected);
    mGraphicsItem->update();
}

/*****************************************************************************************
 *  End of File
 ****************************************************************************************/

} // namespace project
