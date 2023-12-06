#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

constexpr const char *example[] = {
"seeds: 79 14 55 13",
"",
"seed-to-soil map:",
"50 98 2",
"52 50 48",
"",
"soil-to-fertilizer map:",
"0 15 37",
"37 52 2",
"39 0 15",
"",
"fertilizer-to-water map:",
"49 53 8",
"0 11 42",
"42 0 7",
"57 7 4",
"",
"water-to-light map:",
"88 18 7",
"18 25 70",
"",
"light-to-temperature map:",
"45 77 23",
"81 45 19",
"68 64 13",
"",
"temperature-to-humidity map:",
"0 69 1",
"1 0 69",
"",
"humidity-to-location map:",
"60 56 37",
"56 93 4",
};

constexpr bool print_input = false;
constexpr bool do_example = false;
constexpr auto example_location = 35;
constexpr auto do_part = 1;
constexpr const char input_file_name[] = "input.txt";

size_t part1(std::vector<std::string> input) {
	// The maps are as follows:
	// DST SRC RANGE
	// <SRC, SRC+RANGE> = <MIN, MAX>
	// <DST, DST+RANGE> = <MIN, MAX>
	// What to save.
	// SRC <- starting point
	// SRC + Range <- ending point
	// if (seed >= SRC && seed <= SRC + RANGE) { seed = DST + (seed - SRC); }
	size_t location = 0;
	auto seeds_vec = std::vector<size_t>();
	auto maps_vec = std::vector<std::unordered_map<size_t, std::pair<size_t, size_t>>>();
	auto map = std::unordered_map<size_t, std::pair<size_t, size_t>>();
	for (auto s : input) {
		auto line = std::istringstream{s};
		auto word = std::string{};
		line >> word;
		if (word.empty()) {
			maps_vec.push_back(map); // Push it in the vector of maps.
			map = std::unordered_map<size_t, std::pair<size_t, size_t>>(); // New map.
			continue;
		}
		else if (word == "seeds:") {
			// Build the vector of seeds
			std::cout << word << " ";
			while (line >> word) {
				auto seed_num = std::strtoull(word.c_str(), nullptr, 10);
				seeds_vec.push_back(seed_num);
				std::cout << seed_num << " ";
			}
			std::cout << std::endl;
		}
		else {
			auto dest_str = std::string{word};
			auto src_str = std::string{};
			auto range_str = std::string{};
			line >> src_str;
			if (src_str == "map:") {
				std::cout  << dest_str << ":" << std::endl;
			}
			else {
				line >> range_str;
				auto dest = std::strtoull(dest_str.c_str(), nullptr, 10);
				auto src = std::strtoull(src_str.c_str(), nullptr, 10);
				auto range = std::strtoull(range_str.c_str(), nullptr, 10);
				// Create a row of src -> dst.
				//std::cout << "D: " << dest << "\t| S: " << src << "\t| R: " << range << std::endl;
				//std::cout << "Inserting { " << src << ", < " << dest << ", " << range << "> };" << std::endl;
				map.insert({src, std::make_pair(dest, range)});
			}
		}
	}
	maps_vec.push_back(map); // Push it in the vector of maps.
	std::cout << "Maps amount: " << maps_vec.size() << std::endl;
	location = seeds_vec.front();
	for (auto seed : seeds_vec) {
		auto cur = seed;
		for (auto map : maps_vec) {
			for (auto e : map) {
				//std::cout << "Checking if " << cur << " in range [" << e.first << ", " << e.first + e.second.second << "]" << std::endl;
				if (cur >= e.first && cur < e.first + e.second.second) {
					std::cout << "Old cur diff: " << cur - e.first << " | Cur: " << cur;
					cur = e.second.first + (cur - e.first);
					std::cout << " -> " << cur << std::endl;
					break;
				}
			}
		}
		std::cout << "Is " << cur << " < " << location << " ? " << (cur < location) << std::endl;
		location = cur < location ? cur : location;
	}
	return location;
}

int part2(std::vector<std::string> input);

int main(void) {
	std::cout << "Advent of Code Day 5!\n" << std::endl;
	// Set up input
	auto input = std::vector<std::string>();
	if (do_example) {
		for (auto s : example) {
			input.push_back(s);
		}
	}
	else {
		auto file_input = std::ifstream{input_file_name};
		if (!file_input) {
			std::cerr << "ERROR: Cannot open file " << input_file_name << "for reading\n" << std::endl;
			return -1;
		}
		auto file_line = std::string{};
		while (std::getline(file_input, file_line)) {
			input.push_back(file_line);
		}
	}
	if (print_input) {
		for (auto s : input) {
			std::cout << s << std::endl;
		}
	}

	auto location = 0;
	if (do_part == 1) {
		location = part1(input);
	}
	else if (do_part == 2) {
		location = part2(input);
	}

	if (do_example) {
		std::cout << "Location is " << location << " and should be " << example_location << std::endl;
		assert(location == example_location);
	}
	else {
		std::cout << "Location is: " << location << std::endl;
	}
	return 0;
}
