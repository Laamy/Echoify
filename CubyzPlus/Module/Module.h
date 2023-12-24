#pragma once

#include "Setting.h"

// module class which all modules inherit from
class Module {
public:
	std::string name;
	std::string category;
	std::string description;
	std::string author;
	std::string keybind;
	std::vector<Setting*> settings_;

	bool visible = true;
	bool enabled = false;

	// constructor for module
	Module(std::string name, std::string category, std::string description, std::string author, std::string keybind, bool enabled = false) {
		this->name = name;
		this->category = category;
		this->description = description;
		this->author = author;
		this->keybind = keybind;
		SetEnabled(enabled);

		addBool("Drawn", "Draw in the arraylist", &visible);
		std::cout << "[*] Module Created " << name << std::endl;
	}

	// toggle module
	void Toggle() {
		SetEnabled(!enabled);
	}

	// toggle module from given value with events
	void SetEnabled(bool value) {
		// toggle enabled value to given value
		enabled = value;

		// using :? operator to check if value is true or false & toggle events
		value ? OnEnable() : OnDisable();
	}

	// settings borrowed from IRIS DEZ DICK IN UR MOUTH https://github.com/Laamy/Iris/blob/master/Iris/Module/Module.h
	void addSlider(const std::string name, const std::string description, float* value, float min, float max)
	{
		settings_.emplace_back(new Setting(name, description, value, min, max));
	}

	void addBool(const std::string name, const std::string description, bool* state)
	{
		settings_.emplace_back(new Setting(name, description, state));
	}

	void addEnum(const std::string name, const std::string description, std::vector<std::string> enums, int* iterator)
	{
		settings_.emplace_back(new Setting(name, description, enums, iterator));
	}

	// essential events
	virtual void OnEnable() {};
	virtual void OnDisable() {};

	// game events
	virtual void OnTick(fpsent* player) {};
	virtual void OnUpdate(ImDrawData* context) {};
	virtual void OnKey(keym* key) {};

	// rendering events
	// I should probably drop imgui events into here via a function
};