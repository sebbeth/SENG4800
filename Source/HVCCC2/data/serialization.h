#pragma once
#include "convertData.h"

#include <experimental/filesystem> // C++-standard header file name
#include <filesystem> // Microsoft-specific implementation header file name  
#include <string> // memset()
#include <stdexcept>

namespace fs = std::experimental::filesystem;

#include <fstream>
#include <sstream>
#include "cereal/archives/binary.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/string.hpp"
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include "util.h"



template<typename Id, typename Value>
bool serialize(const std::map<Id, std::vector<Value>>& source, const std::string& destinationPath);

template<typename... Ids, typename... Values>
bool serialize(const std::tuple<typename std::map<Ids, Values>...>& source, const std::string& destinationPath) {
    bool success = true;
	auto tmp = serialisation_detail::serialisation_functor(success, destinationPath);
    forEachInTuple(source, tmp);
	return success;
}

template<typename... Ids, typename... Values>
bool deserialize(const std::string& sourcePath, std::tuple<typename std::map<Ids, Values>...>& destination) {
    bool success = true;
	auto tmp = serialisation_detail::deserialisation_functor(success, sourcePath);
    forEachInTuple(destination, tmp);
    return success;
}

template<typename Id, typename Value>
bool deserialize(const std::string& sourcePath, std::map<typename Id, std::vector<Value>>& destination);

template<typename Id, typename Value>
bool serialize(const std::map<Id, std::vector<Value>>& source, const std::string& destinationPath) {
	for (auto each : source) {

		auto eachStates = each.second;
	
		std::string eachPath = destinationPath + '/' + each.first.nameForBinaryFile() + ".bindata";

		if (!fs::is_directory(destinationPath) || !fs::exists(destinationPath)) {
			fs::create_directory(destinationPath);
		}

		std::ofstream outlet(eachPath, std::ios::binary);
		if (outlet.is_open()) {
			try {
				cereal::BinaryOutputArchive outputArchive(outlet);
				outputArchive(eachStates);
				outlet.close();
			} catch (std::runtime_error e) {
#ifdef DEBUG
				std::cout << "serialisation error: " << e.what() << std::endl;
#endif // DEBUG
				return false;
			}
		}
		else {
			return false;
		}
	}
	return true;
}


template<typename Id, typename Value>
bool deserialize(const std::string& sourcePath, std::map<typename Id, std::vector<Value>>& destination) {
	for (const auto& each : std::experimental::filesystem::directory_iterator(sourcePath)) {
		std::string eachPathName = each.path().string();
		
		//get after last / (linux path)
		auto index = eachPathName.rfind('/') + 1;
		std::string eachName = index != std::string::npos ? eachPathName.substr(index) : eachPathName;
		
		//get after last \ (windows path)
		index = eachName.rfind('\\') + 1;
		if (index != std::string::npos) {
			eachName = eachName.substr(index);
		}

		//get before the last .
		index = eachName.rfind('.');
		if (index != std::string::npos) {
			eachName = eachName.substr(0, index);
		}

		//call stoi only if we need to
		//note: this is a bit of a hack, should probably use the type-traits pattern
        std::vector<Value> states;
		std::ifstream inlet(eachPathName, std::ios::binary);
		if (inlet.is_open()) {
			try {
				cereal::BinaryInputArchive inputArchive(inlet);
				inputArchive(states);
                destination.insert(std::make_pair(states.front().id, states));
				inlet.close();
			} catch (std::runtime_error e) {
#ifdef DEBUG
				std::cout << "serialisation error: " << e.what() << std::endl;
#endif // DEBUG
				return false;
			}
		}
		else {
			return false;
		}
	}
	return true;
}

namespace serialisation_detail {
	struct serialisation_functor {
		bool& result;
		std::string destinationPath;
		template<typename Id, typename Value>
		void operator() (const std::map<Id, std::vector<Value>>& each) {
			result = result && serialize(each, destinationPath);
		}
		serialisation_functor(bool& result, const std::string& destinationPath);
	};
    struct deserialisation_functor {
        bool& result;
        std::string sourcePath;
		template<typename Id, typename Value>
		void operator() (std::map<Id, std::vector<Value>>& each) {
            result = result && deserialize(sourcePath, each);
        }
        deserialisation_functor(bool& result, const std::string& sourcePath);
    };
}