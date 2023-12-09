import std.stdio;
import std.file;
import std.string;
import std.uni : isWhite;
import std.conv;
import std.array;

static immutable string[] example_input = [
	"Time:      7  15   30",
	"Distance:  9  40  200",
];
static immutable string input_file_name = "input.txt";

static immutable bool do_example = false;
static immutable uint do_part = 2;
static immutable uint arr_siz = do_example ? 3 : 4;

ulong calc_dist(const ulong time_in_ms, const ulong distance_in_mm) {
	writeln("Testing with time ", time_in_ms, " and distance ", distance_in_mm);
	ulong[] successes;
	for (uint i = 1; i < time_in_ms; ++i) {
		auto race = i * (time_in_ms - i);
		/* writeln("Button pressed for ", i, " seconds."); */
		/* writeln("Final distance: ", race); */
		if (race > distance_in_mm) {
			/* writeln("Beat ", distance_in_mm, " with ", race); */
			successes ~= i;
		}
	}
	return successes.length;
}

void main() {
	writeln("Welcome to Day 6 of Advent of Code!");

	auto input = do_example ? example_input : std.file.slurp!(string)(input_file_name, "%s");
	ulong[] time_arr;
	ulong[] dist_arr;
	foreach (i, line; input) {
		writeln(line);
		auto ln = line.split(':');
		auto desc = ln[0].strip();
		writeln(desc);
		auto vars_str = ln[1].strip();
		auto vars = vars_str.split!isWhite;
		if (do_part == 1) {
			foreach (var; vars) {
				if (var.empty()) {
					continue;
				}
				auto digit = var.to!ulong;
				if (digit > 0) {
					if (i == 0) {
						time_arr ~= digit;
					}
					else {
						dist_arr ~= digit;
					}
				}
				writeln(var);
			}
		}
		if (do_part == 2) {
			if (i == 0) {
				time_arr ~= join(vars).to!ulong;
			}
			else {
				dist_arr ~= join(vars).to!ulong;
			}
		}
	}

	writeln(time_arr);
	writeln(dist_arr);

	ulong result = calc_dist(time_arr[0], dist_arr[0]);
	if (do_part == 1) {
		for (uint i = 1; i < arr_siz; ++i) {
			result *= calc_dist(time_arr[i], dist_arr[i]);
		}
	}

	writeln("Margin of error: ", result);
	if (do_example) {
		if (do_part == 1) {
			assert(288 == result);
		}
		else if (do_part == 2) {
			assert(71_503 == result);
		}
	}

	return;
}
