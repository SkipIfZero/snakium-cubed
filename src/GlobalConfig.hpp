#pragma once
#ifndef S3_CONFIG_HPP
#define S3_CONFIG_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>

#include <iostream>
#include <string>
#include <exception> // std::terminate()
#include <cstdint> // uint16_t

#include "sfz/SDL.hpp"
#include "gamelogic/ModelConfig.hpp"

namespace s3 {

using std::uint16_t;

class GlobalConfig {
public:
	ModelConfig mModelConfig;
	uint16_t mWindowResolutionX, mWindowResolutionY;
	uint16_t mMSAA;
	bool mTransparentCube, mTransparentWhenEating;

	void load() noexcept;
	void save() noexcept;

private:
	boost::property_tree::ptree mPtree;
};

} // namespace s3

#endif