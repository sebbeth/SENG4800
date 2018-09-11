#pragma once
#include <vector>
#include <map>

#include "extraction/implementedEntities.h"
#include "extraction/implementedTraits.h"
#include "extraction/extractData.h"

#include "loadData.h"

std::map<Stacker::Id, std::vector<StackerState>> convert(const std::map<Stacker::Id, std::vector<StackerEvent>>& source);