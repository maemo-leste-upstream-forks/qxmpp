/*
 * Copyright (C) 2008-2022 The QXmpp developers
 *
 * Author:
 *  Melvin Keskin
 *
 * Source:
 *  https://github.com/qxmpp-project/qxmpp
 *
 * This file is a part of QXmpp library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

#include "QXmppMixInvitation.h"

#include "QXmppConstants_p.h"
#include "QXmppUtils.h"

#include <QDomElement>
#include <QSharedData>

class QXmppMixInvitationPrivate : public QSharedData
{
public:
    QString inviterJid;
    QString inviteeJid;
    QString channelJid;
    QString token;
};

///
/// Default constructor
///
QXmppMixInvitation::QXmppMixInvitation()
    : d(new QXmppMixInvitationPrivate)
{
}

///
/// Copy constructor
///
QXmppMixInvitation::QXmppMixInvitation(const QXmppMixInvitation &other) = default;

///
/// Default assignment operator.
///
QXmppMixInvitation &QXmppMixInvitation::operator=(const QXmppMixInvitation &other) = default;

///
/// Destructor
///
QXmppMixInvitation::~QXmppMixInvitation() = default;

///
/// Returns the JID of the inviter.
///
/// \return the inviter's JID
///
QString QXmppMixInvitation::inviterJid() const
{
    return d->inviterJid;
}

///
/// Sets the JID of the inviter.
///
/// \param inviterJid inviter's JID
///
void QXmppMixInvitation::setInviterJid(const QString &inviterJid)
{
    d->inviterJid = inviterJid;
}

///
/// Returns the JID of the invitee.
///
/// \return the invitee's JID
///
QString QXmppMixInvitation::inviteeJid() const
{
    return d->inviteeJid;
}

///
/// Sets the JID of the invitee.
///
/// \param inviteeJid invitee's JID
///
void QXmppMixInvitation::setInviteeJid(const QString &inviteeJid)
{
    d->inviteeJid = inviteeJid;
}

///
/// Returns the JID of the channel.
///
/// \return the channel's JID
///
QString QXmppMixInvitation::channelJid() const
{
    return d->channelJid;
}

///
/// Sets the JID of the channel.
///
/// \param channelJid channel JID
///
void QXmppMixInvitation::setChannelJid(const QString &channelJid)
{
    d->channelJid = channelJid;
}

///
/// Returns the token which is generated by the server and used by the invitee
/// for authentication.
///
/// \return the generated token used for authentication
///
QString QXmppMixInvitation::token() const
{
    return d->token;
}

///
/// Sets the token which is generated by the server and used by the invitee for
/// authentication.
///
/// \param token authentication token
///
void QXmppMixInvitation::setToken(const QString &token)
{
    d->token = token;
}

/// \cond
void QXmppMixInvitation::parse(const QDomElement &element)
{
    d->inviterJid = element.firstChildElement(QStringLiteral("inviter")).text();
    d->inviteeJid = element.firstChildElement(QStringLiteral("invitee")).text();
    d->channelJid = element.firstChildElement(QStringLiteral("channel")).text();
    d->token = element.firstChildElement(QStringLiteral("token")).text();
}

void QXmppMixInvitation::toXml(QXmlStreamWriter *writer) const
{
    writer->writeStartElement(QStringLiteral("invitation"));
    writer->writeDefaultNamespace(ns_mix_misc);

    helperToXmlAddTextElement(writer, QStringLiteral("inviter"), d->inviterJid);
    helperToXmlAddTextElement(writer, QStringLiteral("invitee"), d->inviteeJid);
    helperToXmlAddTextElement(writer, QStringLiteral("channel"), d->channelJid);
    helperToXmlAddTextElement(writer, QStringLiteral("token"), d->token);

    writer->writeEndElement();
}
/// \endcond

///
/// Determines whether the given DOM element is a MIX invitation.
///
/// \param element DOM element being checked
///
/// \return true if element is a MIX invitation, otherwise false
///
bool QXmppMixInvitation::isMixInvitation(const QDomElement &element)
{
    return element.tagName() == QStringLiteral("invitation") &&
        element.namespaceURI() == ns_mix_misc;
}
