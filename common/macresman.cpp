/* Cabal - Legacy Game Implementations
 *
 * Cabal is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

// Based on the ScummVM (GPLv2+) file of the same name

#include "common/scummsys.h"
#include "common/debug.h"
#include "common/util.h"
#include "common/file.h"
#include "common/fs.h"
#include "common/macresman.h"
#include "common/md5.h"
#include "common/substream.h"
#include "common/textconsole.h"

#ifdef MACOSX
#include "common/config-manager.h"
#endif

namespace Common {

#define MBI_INFOHDR 128
#define MBI_ZERO1 0
#define MBI_NAMELEN 1
#define MBI_ZERO2 74
#define MBI_ZERO3 82
#define MBI_DFLEN 83
#define MBI_RFLEN 87
#define MAXNAMELEN 63

MacResManager::MacResManager() {
	memset(this, 0, sizeof(MacResManager));
	close();
}

MacResManager::~MacResManager() {
	close();
}

void MacResManager::close() {
	_resForkOffset = -1;
	_mode = kResForkNone;

	for (int i = 0; i < _resMap.numTypes; i++) {
		for (int j = 0; j < _resTypes[i].items; j++)
			if (_resLists[i][j].nameOffset != -1)
				delete[] _resLists[i][j].name;

		delete[] _resLists[i];
	}

	delete[] _resLists; _resLists = 0;
	delete[] _resTypes; _resTypes = 0;
	delete _stream; _stream = 0;
	_resMap.numTypes = 0;
}

bool MacResManager::hasDataFork() const {
	return !_baseFileName.empty();
}

bool MacResManager::hasResFork() const {
	return !_baseFileName.empty() && _mode != kResForkNone;
}

uint32 MacResManager::getResForkDataSize() const {
	if (!hasResFork())
		return 0;

	_stream->seek(_resForkOffset + 4);
	return _stream->readUint32BE();
}

String MacResManager::computeResForkMD5AsString(uint32 length) const {
	if (!hasResFork())
		return String();

	_stream->seek(_resForkOffset);
	uint32 dataOffset = _stream->readUint32BE() + _resForkOffset;
	/* uint32 mapOffset = */ _stream->readUint32BE();
	uint32 dataLength = _stream->readUint32BE();


	SeekableSubReadStream resForkStream(_stream, dataOffset, dataOffset + dataLength);
	return computeStreamMD5AsString(resForkStream, MIN<uint32>(length, _resForkSize));
}

bool MacResManager::open(const String &fileName) {
	close();

#ifdef MACOSX
	{
		// Check the actual fork on a Mac computer
		String fullPath = ConfMan.get("path") + "/" + fileName + "/..namedfork/rsrc";
		FSNode resFsNode = FSNode(fullPath);
		if (resFsNode.exists()) {
			SeekableReadStream *macResForkRawStream = resFsNode.createReadStream();

			if (macResForkRawStream && loadFromRawFork(*macResForkRawStream)) {
				_baseFileName = fileName;
				return true;
			}

			delete macResForkRawStream;
		}
	}
#endif

	File *file = new File();

	// Prefer standalone files first, starting with raw forks
	if (file->open(fileName + ".rsrc") && loadFromRawFork(*file)) {
		_baseFileName = fileName;
		return true;
	}
	file->close();

	// Then try for AppleDouble using Apple's naming
	if (file->open(constructAppleDoubleName(fileName)) && loadFromAppleDouble(*file)) {
		_baseFileName = fileName;
		return true;
	}
	file->close();

	// Check .bin for MacBinary next
	if (file->open(fileName + ".bin") && loadFromMacBinary(*file)) {
		_baseFileName = fileName;
		return true;
	}
	file->close();

	// As a last resort, see if just the data fork exists
	if (file->open(fileName)) {
		_baseFileName = fileName;

		// FIXME: Is this really needed?
		if (isMacBinary(*file)) {
			file->seek(0);
			if (loadFromMacBinary(*file))
				return true;
		}

		file->seek(0);
		_stream = file;
		return true;
	}

	delete file;

	// The file doesn't exist
	return false;
}

bool MacResManager::open(const FSNode &path, const String &fileName) {
	close();

#ifdef MACOSX
	{
		// Check the actual fork on a Mac computer
		String fullPath = path.getPath() + "/" + fileName + "/..namedfork/rsrc";
		FSNode resFsNode = FSNode(fullPath);
		if (resFsNode.exists()) {
			SeekableReadStream *macResForkRawStream = resFsNode.createReadStream();

			if (macResForkRawStream && loadFromRawFork(*macResForkRawStream)) {
				_baseFileName = fileName;
				return true;
			}

			delete macResForkRawStream;
		}
	}
#endif

	// Prefer standalone files first, starting with raw forks
	FSNode fsNode = path.getChild(fileName + ".rsrc");
	if (fsNode.exists() && !fsNode.isDirectory()) {
		SeekableReadStream *stream = fsNode.createReadStream();
		if (loadFromRawFork(*stream)) {
			_baseFileName = fileName;
			return true;
		}
		delete stream;
	}

	// Then try for AppleDouble using Apple's naming
	fsNode = path.getChild(constructAppleDoubleName(fileName));
	if (fsNode.exists() && !fsNode.isDirectory()) {
		SeekableReadStream *stream = fsNode.createReadStream();
		if (loadFromAppleDouble(*stream)) {
			_baseFileName = fileName;
			return true;
		}
		delete stream;
	}

	// Check .bin for MacBinary next
	fsNode = path.getChild(fileName + ".bin");
	if (fsNode.exists() && !fsNode.isDirectory()) {
		SeekableReadStream *stream = fsNode.createReadStream();
		if (loadFromMacBinary(*stream)) {
			_baseFileName = fileName;
			return true;
		}
		delete stream;
	}

	// As a last resort, see if just the data fork exists
	fsNode = path.getChild(fileName);
	if (fsNode.exists() && !fsNode.isDirectory()) {
		SeekableReadStream *stream = fsNode.createReadStream();
		_baseFileName = fileName;

		// FIXME: Is this really needed?
		if (isMacBinary(*stream)) {
			stream->seek(0);
			if (loadFromMacBinary(*stream))
				return true;
		}

		stream->seek(0);
		_stream = stream;
		return true;
	}

	// The file doesn't exist
	return false;
}

bool MacResManager::exists(const String &fileName) {
	// Try the file name by itself
	if (File::exists(fileName))
		return true;

	// Try the .rsrc extension
	if (File::exists(fileName + ".rsrc"))
		return true;

	// Check if we have a MacBinary file
	File tempFile;
	if (tempFile.open(fileName + ".bin") && isMacBinary(tempFile))
		return true;

	// Check if we have an AppleDouble file
	if (tempFile.open(constructAppleDoubleName(fileName))) {
		uint32 tag = tempFile.readUint32BE();
		if (!tempFile.eos() && tag == 0x00051607)
			return true;
	}

	return false;
}

bool MacResManager::loadFromAppleDouble(SeekableReadStream &stream) {
	uint32 tag = stream.readUint32BE();
	if (stream.eos() || tag != 0x00051607) // tag
		return false;

	stream.skip(20); // version + home file system

	uint16 entryCount = stream.readUint16BE();
	if (stream.eos())
		return false;

	for (uint16 i = 0; i < entryCount; i++) {
		uint32 id = stream.readUint32BE();
		uint32 offset = stream.readUint32BE();
		uint32 length = stream.readUint32BE();
		if (stream.eos())
			return false;

		if (id == 2) {
			// Found the resource fork!
			_resForkOffset = offset;
			_mode = kResForkAppleDouble;
			_resForkSize = length;
			return load(stream);
		}
	}

	return false;
}

bool MacResManager::isMacBinary(SeekableReadStream &stream) {
	byte infoHeader[MBI_INFOHDR];
	uint32 size = stream.read(infoHeader, MBI_INFOHDR);
	if (size != MBI_INFOHDR)
		return false;

	// Check that the header is correct
	if (infoHeader[MBI_ZERO1] == 0 && infoHeader[MBI_ZERO2] == 0 &&
		infoHeader[MBI_ZERO3] == 0 && infoHeader[MBI_NAMELEN] <= MAXNAMELEN) {

		// Pull out fork lengths
		uint32 dataSize = READ_BE_UINT32(infoHeader + MBI_DFLEN);
		uint32 rsrcSize = READ_BE_UINT32(infoHeader + MBI_RFLEN);

		uint32 dataSizePad = (((dataSize + 127) >> 7) << 7);
		uint32 rsrcSizePad = (((rsrcSize + 127) >> 7) << 7);

		// If the header + data size + rsrc size equal the stream size, it should
		// be MacBinary.
		if (MBI_INFOHDR + dataSizePad + rsrcSizePad == (uint32)stream.size())
			return true;
	}

	// Not detected as MacBinary
	return false;
}

bool MacResManager::loadFromMacBinary(SeekableReadStream &stream) {
	byte infoHeader[MBI_INFOHDR];
	uint32 size = stream.read(infoHeader, MBI_INFOHDR);
	if (size != MBI_INFOHDR)
		return false;

	// Maybe we have MacBinary?
	if (infoHeader[MBI_ZERO1] == 0 && infoHeader[MBI_ZERO2] == 0 &&
		infoHeader[MBI_ZERO3] == 0 && infoHeader[MBI_NAMELEN] <= MAXNAMELEN) {

		// Pull out fork lengths
		uint32 dataSize = READ_BE_UINT32(infoHeader + MBI_DFLEN);
		uint32 rsrcSize = READ_BE_UINT32(infoHeader + MBI_RFLEN);

		uint32 dataSizePad = (((dataSize + 127) >> 7) << 7);
		uint32 rsrcSizePad = (((rsrcSize + 127) >> 7) << 7);

		// Length check
		if (MBI_INFOHDR + dataSizePad + rsrcSizePad == (uint32)stream.size()) {
			_resForkOffset = MBI_INFOHDR + dataSizePad;
			_resForkSize = rsrcSize;
		}
	}

	if (_resForkOffset < 0)
		return false;

	_mode = kResForkMacBinary;
	return load(stream);
}

bool MacResManager::loadFromRawFork(SeekableReadStream &stream) {
	_mode = kResForkRaw;
	_resForkOffset = 0;
	_resForkSize = stream.size();
	return load(stream);
}

bool MacResManager::load(SeekableReadStream &stream) {
	if (_mode == kResForkNone)
		return false;

	stream.seek(_resForkOffset);

	_dataOffset = stream.readUint32BE() + _resForkOffset;
	_mapOffset = stream.readUint32BE() + _resForkOffset;
	_dataLength = stream.readUint32BE();
	_mapLength = stream.readUint32BE();

	// do sanity check
	if (stream.eos() || _dataOffset >= (uint32)stream.size() || _mapOffset >= (uint32)stream.size() ||
			_dataLength + _mapLength  > (uint32)stream.size()) {
		_resForkOffset = -1;
		_mode = kResForkNone;
		return false;
	}

	debug(7, "got header: data %d [%d] map %d [%d]",
		_dataOffset, _dataLength, _mapOffset, _mapLength);

	_stream = &stream;

	readMap();
	return true;
}

SeekableReadStream *MacResManager::getDataFork() {
	if (!_stream)
		return NULL;

	if (_mode == kResForkMacBinary) {
		_stream->seek(MBI_DFLEN);
		uint32 dataSize = _stream->readUint32BE();
		return new SeekableSubReadStream(_stream, MBI_INFOHDR, MBI_INFOHDR + dataSize);
	}

	File *file = new File();
	if (file->open(_baseFileName))
		return file;
	delete file;

	return NULL;
}

MacResIDArray MacResManager::getResIDArray(uint32 typeID) {
	int typeNum = -1;
	MacResIDArray res;

	for (int i = 0; i < _resMap.numTypes; i++)
		if (_resTypes[i].id == typeID) {
			typeNum = i;
			break;
		}

	if (typeNum == -1)
		return res;

	res.resize(_resTypes[typeNum].items);

	for (int i = 0; i < _resTypes[typeNum].items; i++)
		res[i] = _resLists[typeNum][i].id;

	return res;
}

MacResTagArray MacResManager::getResTagArray() {
	MacResTagArray tagArray;

	if (!hasResFork())
		return tagArray;

	tagArray.resize(_resMap.numTypes);

	for (uint32 i = 0; i < _resMap.numTypes; i++)
		tagArray[i] = _resTypes[i].id;

	return tagArray;
}

String MacResManager::getResName(uint32 typeID, uint16 resID) const {
	int typeNum = -1;

	for (int i = 0; i < _resMap.numTypes; i++)
		if (_resTypes[i].id == typeID) {
			typeNum = i;
			break;
		}

	if (typeNum == -1)
		return "";

	for (int i = 0; i < _resTypes[typeNum].items; i++)
		if (_resLists[typeNum][i].id == resID)
			return _resLists[typeNum][i].name;

	return "";
}

SeekableReadStream *MacResManager::getResource(uint32 typeID, uint16 resID) {
	int typeNum = -1;
	int resNum = -1;

	for (int i = 0; i < _resMap.numTypes; i++)
		if (_resTypes[i].id == typeID) {
			typeNum = i;
			break;
		}

	if (typeNum == -1)
		return NULL;

	for (int i = 0; i < _resTypes[typeNum].items; i++)
		if (_resLists[typeNum][i].id == resID) {
			resNum = i;
			break;
		}

	if (resNum == -1)
		return NULL;

	_stream->seek(_dataOffset + _resLists[typeNum][resNum].dataOffset);
	uint32 len = _stream->readUint32BE();

	// Ignore resources with 0 length
	if (!len)
		return 0;

	return _stream->readStream(len);
}

SeekableReadStream *MacResManager::getResource(const String &fileName) {
	for (uint32 i = 0; i < _resMap.numTypes; i++) {
		for (uint32 j = 0; j < _resTypes[i].items; j++) {
			if (_resLists[i][j].nameOffset != -1 && fileName.equalsIgnoreCase(_resLists[i][j].name)) {
				_stream->seek(_dataOffset + _resLists[i][j].dataOffset);
				uint32 len = _stream->readUint32BE();

				// Ignore resources with 0 length
				if (!len)
					return 0;

				return _stream->readStream(len);
			}
		}
	}

	return 0;
}

SeekableReadStream *MacResManager::getResource(uint32 typeID, const String &fileName) {
	for (uint32 i = 0; i < _resMap.numTypes; i++) {
		if (_resTypes[i].id != typeID)
			continue;

		for (uint32 j = 0; j < _resTypes[i].items; j++) {
			if (_resLists[i][j].nameOffset != -1 && fileName.equalsIgnoreCase(_resLists[i][j].name)) {
				_stream->seek(_dataOffset + _resLists[i][j].dataOffset);
				uint32 len = _stream->readUint32BE();

				// Ignore resources with 0 length
				if (!len)
					return 0;

				return _stream->readStream(len);
			}
		}
	}

	return 0;
}

void MacResManager::readMap() {
	_stream->seek(_mapOffset + 22);

	_resMap.resAttr = _stream->readUint16BE();
	_resMap.typeOffset = _stream->readUint16BE();
	_resMap.nameOffset = _stream->readUint16BE();
	_resMap.numTypes = _stream->readUint16BE();
	_resMap.numTypes++;

	_stream->seek(_mapOffset + _resMap.typeOffset + 2);
	_resTypes = new ResType[_resMap.numTypes];

	for (int i = 0; i < _resMap.numTypes; i++) {
		_resTypes[i].id = _stream->readUint32BE();
		_resTypes[i].items = _stream->readUint16BE();
		_resTypes[i].offset = _stream->readUint16BE();
		_resTypes[i].items++;

		debug(8, "resType: <%s> items: %d offset: %d (0x%x)", tag2str(_resTypes[i].id), _resTypes[i].items,  _resTypes[i].offset, _resTypes[i].offset);
	}

	_resLists = new ResPtr[_resMap.numTypes];

	for (int i = 0; i < _resMap.numTypes; i++) {
		_resLists[i] = new Resource[_resTypes[i].items];
		_stream->seek(_resTypes[i].offset + _mapOffset + _resMap.typeOffset);

		for (int j = 0; j < _resTypes[i].items; j++) {
			ResPtr resPtr = _resLists[i] + j;

			resPtr->id = _stream->readUint16BE();
			resPtr->nameOffset = _stream->readUint16BE();
			resPtr->dataOffset = _stream->readUint32BE();
			_stream->readUint32BE();
			resPtr->name = 0;

			resPtr->attr = resPtr->dataOffset >> 24;
			resPtr->dataOffset &= 0xFFFFFF;
		}

		for (int j = 0; j < _resTypes[i].items; j++) {
			if (_resLists[i][j].nameOffset != -1) {
				_stream->seek(_resLists[i][j].nameOffset + _mapOffset + _resMap.nameOffset);

				byte len = _stream->readByte();
				_resLists[i][j].name = new char[len + 1];
				_resLists[i][j].name[len] = 0;
				_stream->read(_resLists[i][j].name, len);
			}
		}
	}
}

String MacResManager::constructAppleDoubleName(const String &path) {
	// Try to find the last slash in the string
	const char *lastPathComponent = strrchr(path.c_str(), '/');

	if (lastPathComponent) {
		// Skip the actual slash so it gets copied into the right spot
		lastPathComponent++;
		return String(path.c_str(), lastPathComponent) + "._" + lastPathComponent;
	}

	// Can just insert "._" before the beginning of the string
	return "._" + path;
}

} // End of namespace Common
