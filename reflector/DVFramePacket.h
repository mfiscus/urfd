#pragma once

//  Copyright © 2015 Jean-Luc Deltombe (LX3JL). All rights reserved.
//
// urfd -- The universal reflector
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

#include "Packet.h"

////////////////////////////////////////////////////////////////////////////////////////
// defines

// typedef & structures

using SDStarFrame = struct __attribute__ ((__packed__))dstar_dvframe_tag
{
	uint8_t	AMBE[9];
	uint8_t	DVDATA[3];
};

////////////////////////////////////////////////////////////////////////////////////////
// class

class CDvFramePacket : public CPacket
{
	//friend class CCodecStream;
public:
	// constructor
	CDvFramePacket();
	// DStar frame
	CDvFramePacket(const SDStarFrame *dstarframe, uint16_t streamid, uint8_t counter);
	// DMR Frame
	CDvFramePacket(const uint8_t *ambe, const uint8_t *sync, uint16_t streamid, uint8_t counter1, uint8_t counter2);
	// YSF Frame
	CDvFramePacket(const uint8_t *ambe, uint16_t streamid, uint8_t counter1, uint8_t counter2, uint8_t counter3);
	// URF Frame
	CDvFramePacket(uint16_t streamid, uint8_t dstarcounter, const uint8_t *dstarambe, const uint8_t *dvdata, uint8_t dmrcounter1, uint8_t dmrcounter2, const uint8_t *dmrambe, const uint8_t *dmrsync, ECodecType type, const uint8_t *m17codec, const uint8_t *nonce);
	CDvFramePacket(const CM17Packet &m17);

	// virtual duplication
	std::unique_ptr<CPacket> Duplicate(void) const;

	// identity
	bool IsDvFrame(void) const           { return true; }
	bool HasTranscodableAmbe(void) const { return true; }

	// get
	const STCPacket *GetCodecPacket() const { return &m_TCPack; }
	const uint8_t *GetCodecData(ECodecType) const;
	const uint8_t *GetDvSync(void) const { return m_uiDvSync; }
	const uint8_t *GetDvData(void) const { return m_uiDvData; }
	const uint8_t *GetNonce(void)  const { return m_Nonce; }

	// set
	void SetDvData(const uint8_t *);
	void SetCodecData(ECodecType, const uint8_t *);
	void SetCodecData(const STCPacket *pack);

	// operators
	bool operator ==(const CDvFramePacket &) const;

protected:
	// data (dstar)
	uint8_t m_uiDvData[3];
	// data (dmr)
	uint8_t m_uiDvSync[7];
	// m17
	uint8_t m_Nonce[14];
	// the transcoder packet
	STCPacket m_TCPack;
};