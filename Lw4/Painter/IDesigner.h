#pragma once

#include "CPictureDraft.h"

class IDesigner
{
public:
	virtual CPictureDraft CreateDraft(std::istream& strm) = 0;
	virtual ~IDesigner() = default;
};