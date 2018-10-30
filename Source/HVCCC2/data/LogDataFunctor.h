#pragma once
#include "extraction/implementedEntities.h"
#include "extraction/logStates.h"
#if defined(_WIN32)
#include <direct.h>  
#include <stdlib.h>  
#include <stdio.h>  
#define createDirectory(path) _mkdir(path);
#else
#include <sys/stat.h>
#define createDirectory(path) mkdir(path, 0777); // notice that 777 is different than 0777
#endif

//template<typename Entity>
//using StateMap = std::map<typename Entity::Id, std::vector<typename Entity::AssociatedState>>;
//
//template<typename... Entities>
//using StateMapTuple = std::tuple<StateMap<Entities>...>;

struct LogDataFunctor {
	std::string folderPath;

	template<typename StateMap>

	std::enable_if_t<
		std::is_same_v<
			typename StateMap::mapped_type,
			std::vector<typename StateMap::key_type::Entity::AssociatedState>
		>
	> operator()(const StateMap& data) {
		using Entity = StateMap::key_type::Entity;
		std::string entityPath = folderPath + '/' + Entity::ENTITY_NAME;
		createDirectory(entityPath.c_str());
		for (auto& eachPair : data) {
			std::ofstream eachFile(entityPath + '/' + eachPair.first.nameForBinaryFile());
			logStates(eachFile, eachPair.second);
			eachFile.flush();
			eachFile.close();
		}
	}
	LogDataFunctor(const std::string& folderPath);
};