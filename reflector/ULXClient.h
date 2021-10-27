//  Copyright © 2015 Jean-Luc Deltombe (LX3JL). All rights reserved.

// ulxd -- The universal reflector
// Copyright © 2021 Thomas A. Early N7TAE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "Client.h"

#define XLX_PROTOCOL_REVISION_0      0       // AMBE only, original connect mechanism
#define XLX_PROTOCOL_REVISION_1      1       // AMBE only, revised connect mechanism
#define XLX_PROTOCOL_REVISION_2      2       // Transcoded AMBE+AMBE2 interlink

class CUlxClient : public CClient
{
public:
	// constructors
	CUlxClient();
	CUlxClient(const CCallsign &, const CIp &, char = ' ', int = XLX_PROTOCOL_REVISION_0);
	CUlxClient(const CUlxClient &);

	// destructor
	virtual ~CUlxClient() {};

	// identity
	EProtocol GetProtocol(void) const           { return EProtocol::ulx; }
	int GetProtocolRevision(void) const         { return m_ProtRev; }
	const char *GetProtocolName(void) const     { return "XLX"; }
	int GetCodec(void) const;
	bool IsPeer(void) const                     { return true; }

	// status
	bool IsAlive(void) const;

	// reporting
	void WriteXml(std::ofstream &) {}

protected:
	// data
	int     m_ProtRev;
};
