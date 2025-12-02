#pragma once
#include "const.h"
struct SectionInfo {
	SectionInfo() {

   }
	~SectionInfo() {
		_section_datas.clear();
	} 
	SectionInfo(const SectionInfo& inf) {

	}
	SectionInfo& operator = (const SectionInfo& inf){
		if (&inf == this) {
			return *this;
		}
		this->_section_datas = inf._section_datas;
		return*this;
	}
	int a = 0;
	std::map<std::string, std::string>_section_datas;

	std::string operator[](const std::string& key) {
		if (_section_datas.find(key) == _section_datas.end()) {
			return "";
		}
		return _section_datas[key];
	}
};
class ConfigMgr
{
public:
	~ConfigMgr() {
		std::map<std::string, SectionInfo>_config_map;
	}
	SectionInfo operator[](const std::string& section) {
		if (_config_map.find(section) == _config_map.end()) {
			return SectionInfo();
		}
		return _config_map[section];
	}
	ConfigMgr();
	ConfigMgr(const ConfigMgr& src) {

	}
	ConfigMgr& operator=(const ConfigMgr& inf) {
		if (&inf == this) {
			return *this;
		}
		_config_map = inf._config_map;
		return *this;
	}
	
private:
	std::map<std::string, SectionInfo>_config_map;
};

