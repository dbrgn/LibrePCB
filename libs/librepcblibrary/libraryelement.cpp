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
#include "libraryelement.h"
#include <librepcbcommon/fileio/xmldomelement.h>

namespace library {

/*****************************************************************************************
 *  Constructors / Destructor
 ****************************************************************************************/

LibraryElement::LibraryElement(const QString& xmlFileNamePrefix,
                               const QString& xmlRootNodeName, const QUuid& uuid,
                               const Version& version, const QString& author,
                               const QString& name_en_US, const QString& description_en_US,
                               const QString& keywords_en_US) throw (Exception) :
    LibraryBaseElement(xmlFileNamePrefix, xmlRootNodeName, uuid, version, author, name_en_US, description_en_US, keywords_en_US)
{
}

LibraryElement::LibraryElement(const FilePath& elementDirectory,
                               const QString& xmlFileNamePrefix,
                               const QString& xmlRootNodeName) throw (Exception) :
    LibraryBaseElement(elementDirectory, xmlFileNamePrefix, xmlRootNodeName)
{
}

LibraryElement::~LibraryElement() noexcept
{
}

/*****************************************************************************************
 *  Protected Methods
 ****************************************************************************************/

void LibraryElement::parseDomTree(const XmlDomElement& root) throw (Exception)
{
    LibraryBaseElement::parseDomTree(root);

    // read category UUIDs
    for (XmlDomElement* node = root.getFirstChild("categories/category", true, false);
         node; node = node->getNextSibling("category"))
    {
        mCategories.append(node->getText<QUuid>());
    }
}

XmlDomElement* LibraryElement::serializeToXmlDomElement() const throw (Exception)
{
    QScopedPointer<XmlDomElement> root(LibraryBaseElement::serializeToXmlDomElement());
    XmlDomElement* categories = root->appendChild("categories");
    foreach (const QUuid& uuid, mCategories)
        categories->appendTextChild("category", uuid.toString());
    return root.take();
}

bool LibraryElement::checkAttributesValidity() const noexcept
{
    if (!LibraryBaseElement::checkAttributesValidity()) return false;
    return true;
}

/*****************************************************************************************
 *  End of File
 ****************************************************************************************/

} // namespace library
