const std = @import("std");
const example_lines = [_][]const u8{
    "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53",
    "Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19",
    "Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1",
    "Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83",
    "Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36",
    "Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11",
};

const input_file = @embedFile("input.txt");

const part = 1;
const do_example = false;

fn parse_line(line: []const u8) !u64 {
    // Build a dynamic array of winning numbers
    var winning_numbers = std.ArrayList(u64).init(std.heap.page_allocator);
    defer winning_numbers.deinit();

    // Build a dynamic array of scratchcard numbers
    var playing_numbers = std.ArrayList(u64).init(std.heap.page_allocator);
    defer playing_numbers.deinit();

    // Split input into iterator by delimiter and parse
    var split_iter = std.mem.splitAny(u8, line, ":|");
    _ = split_iter.next(); // Skip the Card ID line.
    var idx: u32 = 0;
    while (split_iter.next()) |segment| {
        const trimmed_segment = std.mem.trim(u8, segment, " ");
        std.debug.print("Trimmed segment: {s}\n", .{trimmed_segment});
        var numbers = std.mem.splitAny(u8, trimmed_segment, " ");
        while (numbers.next()) |number_str| {
            const number = std.zig.parseNumberLiteral(number_str).int;
            if (number > 0) {
                if (idx == 0) {
                    try winning_numbers.append(number);
                } else if (idx == 1) {
                    // deduplicate the numbers by checking if the arraylist contains the needle temp
                    if (!std.mem.containsAtLeast(u64, playing_numbers.items, 1, &[1]u64{number})) {
                        try playing_numbers.append(number);
                    }
                }
            }
        }
        idx += 1;
    }
    std.debug.print("Winning numbers: {d}\n", .{winning_numbers.items});
    std.debug.print("Playing numbers: {d}\n", .{playing_numbers.items});
    // compare each scratchcard number to winning number
    var points: u64 = 0;
    for (playing_numbers.items) |pl| {
        for (winning_numbers.items) |wl| {
            if (pl == wl) {
                points += if (points > 0) points else 1;
                break;
            }
        }
    }
    return points;
}

fn part1(input: *std.mem.SplitIterator(u8, .any)) !u64 {
    // === IMPLEMENTATION START ===
    var result: u64 = 0;
    std.debug.print("Lines: \n", .{});
    while (input.next()) |line| {
        std.debug.print("{s}\n", .{line});
        var points = try parse_line(line);
        // Points: 0 + 2^n where n == matches.
        std.debug.print("Points: {d}\n", .{points});
        result += points;
        // === IMPLEMENTATION END ===
    }
    return result;
}

fn part2(input: *std.mem.SplitIterator(u8, .any)) !u64 {
    _ = input;
    return 0;
}

pub fn main() !void {
    // Prints to stderr (it's a shortcut based on `std.io.getStdErr()`)
    std.debug.print("Welcome to Advent of Code Day 4\n", .{});
    var input = if (do_example) std.mem.splitAny([]const u8, example_lines, "") else std.mem.splitAny(u8, input_file, "\n");
    var result: u64 = 0;
    if (part == 1) {
        result = try part1(&input);
    } else if (part == 2) {}
    if (do_example) {
        const impl_state = if (result == 13) "success" else "failure";
        std.debug.print("Implementation: {s}.\n", .{impl_state});
        std.debug.print("Expected: {} | Got: {d}\n", .{ 13, result });
    } else {
        std.debug.print("Result: {d}\n", .{result});
    }

    return;
}

test "simple test" {
    var list = std.ArrayList(i32).init(std.testing.allocator);
    defer list.deinit(); // try commenting this out and see if zig detects the memory leak!
    try list.append(42);
    try std.testing.expectEqual(@as(i32, 42), list.pop());
}
