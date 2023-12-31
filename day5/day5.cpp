#include <cassert>
#include <array>
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
constexpr bool do_example = true;
constexpr size_t example_location[] = {35, 46};
constexpr auto do_part = 2;
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
				map.emplace(src, std::make_pair(dest, range));
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
					//std::cout << "Old cur diff: " << cur - e.first << " | Cur: " << cur;
					cur = e.second.first + (cur - e.first);
					//std::cout << " -> " << cur << std::endl;
					break;
				}
			}
		}
		//std::cout << "Is " << cur << " < " << location << " ? " << (cur < location) << std::endl;
		location = cur < location ? cur : location;
	}
	return location;
}

size_t part2(std::vector<std::string> input) {
	// The maps are as follows:
	// DST SRC RANGE
	// <SRC, SRC+RANGE> = <MIN, MAX>
	// <DST, DST+RANGE> = <MIN, MAX>
	// What to save.
	// SRC <- starting point
	// SRC + Range <- ending point
	// if (seed >= SRC && seed <= SRC + RANGE) { seed = DST + (seed - SRC); }
	size_t location = 0;
	auto seeds_vec = std::vector<std::pair<size_t, size_t>>();
	auto maps_vec = std::vector<std::vector<std::array<size_t, 3>>>();
	auto map = std::vector<std::array<size_t, 3>>();
	for (auto s : input) {
		auto line = std::istringstream{s};
		auto word = std::string{};
		line >> word;
		if (word.empty()) {
			maps_vec.push_back(map); // Push it in the vector of maps.
			map = std::vector<std::array<size_t, 3>>(); // New map.
			continue;
		}
		else if (word == "seeds:") {
			// Build the vector of seeds
			std::cout << word << " ";
			auto start_str = std::string{};
			auto range_str = std::string{};
			while (line >> start_str && line >> range_str) {
				auto seed_pair = std::make_pair(std::strtoull(start_str.c_str(), nullptr, 10), std::strtoull(range_str.c_str(), nullptr, 10));
				seeds_vec.push_back(seed_pair);
				std::cout << "[" << seed_pair.first << ", " << seed_pair.second << "] | ";
			}
			std::cout << std::endl;
		}
		else {
			auto dest_str = std::string{word};
			auto src_str = std::string{};
			auto range_str = std::string{};
			line >> src_str;
			if (src_str == "map:") {
				//std::cout  << dest_str << ":" << std::endl;
			}
			else {
				line >> range_str;
				auto dest = std::strtoull(dest_str.c_str(), nullptr, 10);
				auto src = std::strtoull(src_str.c_str(), nullptr, 10);
				auto range = std::strtoull(range_str.c_str(), nullptr, 10);
				// Create a row of src -> dst.
				//std::cout << "D: " << dest << "\t| S: " << src << "\t| R: " << range << std::endl;
				std::cout << "Inserting { " << src << ", " << dest << ", " << range << "};" << std::endl;
				map.push_back({src, dest, range});
			}
		}
	}
	maps_vec.push_back(map); // Push it in the vector of maps.
	std::cout << "Maps amount: " << maps_vec.size() << std::endl;
	location = seeds_vec.front().first;
	for (auto& [seed_start, seed_range] : seeds_vec) {
		auto cur = seed_start;
		auto keep = cur;
		for (size_t i = seed_start; i < seed_start + seed_range; ++i) {
			std::cout << "Checking [" << cur << ".." << seed_start + seed_range << ") in map:" << std::endl;
			for (auto& map : maps_vec) {
				for (auto& [src, dest, range] : map) {
					std::cout <<  "\t[" << src << ".." << src + range << "]" << " -> [" << dest << ".." << dest + range << "]";
					if (seed_start + seed_range < src || cur >= src + range) { std::cout << " SKIP " << std::endl; continue; } // Entire range below min map src.
					const auto offset = seed_start - src;
					std::cout << std::endl;
					if (i >= src && i < src + range) {
						std::cout << "\tSeed: " << cur;
						cur = dest + offset + (i - seed_start);
						std::cout << " -> " << cur << std::endl;
					}
				}
				std::cout << "Next Map with cur: " << cur << std::endl;
				keep = cur < keep ? cur : keep;
			}
			std::cout << "Keep: " << keep << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Is " << seed_start << " < " << location << " ? " << (seed_start < location) << std::endl;
		location = keep < location ? keep : location;
	}
	return location;
}

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
		input.push_back("");
	}
	if (print_input) {
		for (auto s : input) {
			std::cout << s << std::endl;
		}
	}

	size_t location = 0;
	if (do_part == 1) {
		location = part1(input);
	}
	else if (do_part == 2) {
		location = part2(input);
	}

	if (do_example) {
		auto example_var = example_location[do_part == 2];
		std::cout << "Location is " << location << " and should be " << example_var << std::endl;
		assert(location == example_var);
	}
	else {
		std::cout << "Location is: " << location << std::endl;
	}
	return 0;
}
