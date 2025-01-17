// SPDX-FileCopyrightText: 2022 Linus Jahn <lnj@kaidan.im>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "QXmppThumbnail.h"

#include "QXmppConstants_p.h"

#include <QDomElement>
#include <QMimeDatabase>
#include <QMimeType>
#include <QUrl>
#include <QXmlStreamWriter>

class QXmppThumbnailPrivate : public QSharedData
{
public:
    QString uri;
    QMimeType mediaType;
    std::optional<uint32_t> width;
    std::optional<uint32_t> height;
};

///
/// \class QXmppThumbnail
///
/// Thumbnail from \xep{0264, Jingle Content Thumbnails}.
///
/// \since QXmpp 1.5
///

/// Default constructor
QXmppThumbnail::QXmppThumbnail()
    : d(new QXmppThumbnailPrivate)
{
}
/// Default copy-constructor
QXmppThumbnail::QXmppThumbnail(const QXmppThumbnail &) = default;
/// Default move-constructor
QXmppThumbnail::QXmppThumbnail(QXmppThumbnail &&) noexcept = default;
QXmppThumbnail::~QXmppThumbnail() = default;
/// Default assignment operator
QXmppThumbnail &QXmppThumbnail::operator=(const QXmppThumbnail &) = default;
/// Default move-assignment operator
QXmppThumbnail &QXmppThumbnail::operator=(QXmppThumbnail &&) noexcept = default;

/// Returns the URI with the location for the data (usually a \xep{0231, Bits of Binary} content ID)
const QString &QXmppThumbnail::uri() const
{
    return d->uri;
}

/// Sets the URI with the location for the data (usually a \xep{0231, Bits of Binary} content ID)
void QXmppThumbnail::setUri(const QString &newUri)
{
    d->uri = newUri;
}

/// Returns the MIME type of the thumbnail data.
const QMimeType &QXmppThumbnail::mediaType() const
{
    return d->mediaType;
}

/// Sets the MIME type of the thumbnail data.
void QXmppThumbnail::setMediaType(const QMimeType &newMediaType)
{
    d->mediaType = newMediaType;
}

/// Returns the width of the thumbnail image.
std::optional<uint32_t> QXmppThumbnail::width() const
{
    return d->width;
}

/// Sets the width of the thumbnail image.
void QXmppThumbnail::setWidth(std::optional<uint32_t> newWidth)
{
    d->width = newWidth;
}

/// Returns the height of the thumbnail image.
std::optional<uint32_t> QXmppThumbnail::height() const
{
    return d->height;
}

/// Sets the height of the thumbnail image.
void QXmppThumbnail::setHeight(std::optional<uint32_t> newHeight)
{
    d->height = newHeight;
}

/// \cond
bool QXmppThumbnail::parse(const QDomElement &el)
{
    if (el.tagName() == "thumbnail" && el.namespaceURI() == ns_thumbs) {
        if (!el.hasAttribute("uri")) {
            return false;
        }

        d->uri = el.attribute("uri");
        if (el.hasAttribute("media-type")) {
            d->mediaType = QMimeDatabase().mimeTypeForName(el.attribute(QStringLiteral("media-type")));
        }

        bool success = false;
        if (auto string = el.attribute("width"); !string.isEmpty()) {
            if (auto parsedInt = string.toUInt(&success); success) {
                d->width = parsedInt;
            } else {
                return false;
            }
        }
        if (auto string = el.attribute("height"); !string.isEmpty()) {
            if (auto parsedInt = string.toUInt(&success); success) {
                d->height = parsedInt;
            } else {
                return false;
            }
        }
        return true;
    }
    return false;
}

void QXmppThumbnail::toXml(QXmlStreamWriter *writer) const
{
    writer->writeStartElement(QStringLiteral("thumbnail"));
    writer->writeDefaultNamespace(ns_thumbs);
    writer->writeAttribute(QStringLiteral("uri"), d->uri);
    if (d->mediaType.isValid()) {
        writer->writeAttribute("media-type", d->mediaType.name());
    }
    if (d->width) {
        writer->writeAttribute("width", QString::number(*d->width));
    }
    if (d->height) {
        writer->writeAttribute("height", QString::number(*d->height));
    }
    writer->writeEndElement();
}
/// \endcond
