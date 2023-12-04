static EXAMPLE_SCHEMATIC: [&str; 10] = [
    "467..114..",
    "...*......",
    "..35..633.",
    "......#...",
    "617*......",
    ".....+.58.",
    "..592.....",
    "......755.",
    "...$.*....",
    ".664.598..",
];

static EXAMPLE_SUM_PART_1: u32 = 4361;
static EXAMPLE_SUM_PART_2: u32 = 467835;

static SYMBOLS: [u8; 18] = [
    b'!', b'"', b'#', b'$', b'%', b'&', b'\'', b'(', b')', b'*', b'+', b',', b'/', b'@', b'=',
    b'-', b'?', b'!',
];

static DO_EXAMPLE: bool = false;

fn part1(schematic: &Vec<&str>, i: usize, j: usize, c: &u8, symbol: u8) -> u32 {
    let mut res: u32 = 0;
    if *c == symbol {
        println!(
            "Found {} at index {} in line {}",
            char::from(symbol),
            j,
            i + 1
        );
        println!("Lines:");
        println!("{}", schematic[i - 1]);
        println!("{}", schematic[i]);
        println!("{}", schematic[i + 1]);

        // Get index of c and check for numbers in a 3x3 matrix around it.
        let row1 = schematic[i - 1].as_bytes().windows(3).nth(j - 1).unwrap();
        let row2 = schematic[i].as_bytes().windows(3).nth(j - 1).unwrap();
        let row3 = schematic[i + 1].as_bytes().windows(3).nth(j - 1).unwrap();

        println!("{:?}", row1);
        println!("{:?}", row2);
        println!("{:?}", row3);

        let mut do_row1 = false;
        let mut do_row2 = false;
        let mut do_row3 = false;

        if row1[0].is_ascii_digit() || row1[1].is_ascii_digit() || row1[2].is_ascii_digit() {
            do_row1 = true;
        }
        if row2[0].is_ascii_digit()
        //|| row2[1].is_ascii_digit()
        || row2[2].is_ascii_digit()
        {
            do_row2 = true;
        }
        if row3[0].is_ascii_digit() || row3[1].is_ascii_digit() || row3[2].is_ascii_digit() {
            do_row3 = true;
        }
        if do_row1 {
            let (left, right) = schematic[i - 1].as_bytes().split_at(j).into();
            println!("{:?} {:?}", left, right);
            let mut sum: u32 = 0;
            if left[left.len() - 1].is_ascii_digit() {
                let mut k: u32 = 0;
                for num in left.iter().rev() {
                    if num.is_ascii_digit() {
                        sum = (u32::from(num & 0xF)) * u32::pow(10, k) + sum;
                        k += 1;
                    } else {
                        break;
                    }
                }
                println!("Left: {}", sum);
            }
            if !schematic[i - 1].as_bytes()[j].is_ascii_digit() {
                res += sum;
                sum = 0;
            }
            if right[0].is_ascii_digit() || right[1].is_ascii_digit() {
                for num in right
                    .iter()
                    .skip((!right[0].is_ascii_digit() && right[1].is_ascii_digit()).into())
                {
                    if *num == b'.' {
                        break;
                    }
                    if num.is_ascii_digit() {
                        sum = (sum * 10) + u32::from(num & 0xF);
                    }
                }
                println!("Right: {}", sum);
            }
            res += sum;
        }
        if do_row2 {
            let (left, right) = schematic[i].as_bytes().split_at(j).into();
            println!("{:?} {:?}", left, right);
            let mut sum: u32 = 0;
            if left[left.len() - 1].is_ascii_digit() {
                let mut k: u32 = 0;
                for num in left.iter().rev() {
                    if num.is_ascii_digit() {
                        sum = (u32::from(num & 0xF)) * u32::pow(10, k) + sum;
                        k += 1;
                    } else {
                        break;
                    }
                }
                println!("Left: {}", sum);
            }
            if !schematic[i].as_bytes()[j].is_ascii_digit() {
                res += sum;
                sum = 0;
            }
            if right[1].is_ascii_digit() {
                for num in right {
                    if *num == b'.' {
                        break;
                    }
                    if num.is_ascii_digit() {
                        sum = (sum * 10) + u32::from(num & 0xF);
                    }
                }
                println!("Right: {}", sum);
            }
            res += sum;
        }
        if do_row3 {
            let (left, right) = schematic[i + 1].as_bytes().split_at(j).into();
            println!("{:?} {:?}", left, right);
            let mut sum: u32 = 0;
            if left[left.len() - 1].is_ascii_digit() {
                let mut k: u32 = 0;
                for num in left.iter().rev() {
                    if num.is_ascii_digit() {
                        sum = (u32::from(num & 0xF)) * u32::pow(10, k) + sum;
                        k += 1;
                    } else {
                        break;
                    }
                }
                println!("Left: {}", sum);
            }
            if !schematic[i + 1].as_bytes()[j].is_ascii_digit() {
                res += sum;
                sum = 0;
            }
            if right[0].is_ascii_digit() || right[1].is_ascii_digit() {
                for num in right
                    .iter()
                    .skip((!right[0].is_ascii_digit() && right[1].is_ascii_digit()).into())
                {
                    if *num == b'.' {
                        break;
                    }
                    if num.is_ascii_digit() {
                        sum = (sum * 10) + u32::from(num & 0xF);
                    }
                }
                println!("Right: {}", sum);
            }
            res += sum;
        }
    }
    return res;
}

static TASK_PART: u8 = 2;

fn main() {
    println!("Hello, world!");

    let schematic_file_path = "input.txt";
    let schematic_input = std::fs::read_to_string(schematic_file_path).unwrap();
    let schematic: Vec<&str> = match DO_EXAMPLE {
        true => EXAMPLE_SCHEMATIC.to_vec(),
        false => schematic_input.split('\n').collect(),
    };

    println!("Schematic:");
    for line in schematic.as_slice() {
        println!("{line}");
    }

    let mut res: u32 = 0;
    for (i, line) in schematic.as_slice().iter().enumerate() {
        for (j, c) in line.as_bytes().iter().enumerate() {
            if TASK_PART == 1 {
                for symbol in SYMBOLS {
                    res += part1(&schematic, i, j, c, symbol);
                }
            } else if TASK_PART == 2 {
                if *c == b'*' {
                    println!("Found * at index {} in line {}", j, i + 1);
                    println!("Lines:");
                    println!("{}", schematic[i - 1]);
                    println!("{}", schematic[i]);
                    println!("{}", schematic[i + 1]);

                    // Get index of c and check for numbers in a 3x3 matrix around it.
                    let row1 = schematic[i - 1].as_bytes().windows(3).nth(j - 1).unwrap();
                    let row2 = schematic[i].as_bytes().windows(3).nth(j - 1).unwrap();
                    let row3 = schematic[i + 1].as_bytes().windows(3).nth(j - 1).unwrap();

                    println!("{:?}", row1);
                    println!("{:?}", row2);
                    println!("{:?}", row3);

                    let mut do_row1 = false;
                    let mut do_row2 = false;
                    let mut do_row3 = false;

                    if row1[0].is_ascii_digit()
                        || row1[1].is_ascii_digit()
                        || row1[2].is_ascii_digit()
                    {
                        do_row1 = true;
                    }
                    if row2[0].is_ascii_digit()
                    //|| row2[1].is_ascii_digit()
                    || row2[2].is_ascii_digit()
                    {
                        do_row2 = true;
                    }
                    if row3[0].is_ascii_digit()
                        || row3[1].is_ascii_digit()
                        || row3[2].is_ascii_digit()
                    {
                        do_row3 = true;
                    }
                    let mut sums: Vec<u32> = Vec::new();
                    if do_row1 {
                        let (left, right) = schematic[i - 1].as_bytes().split_at(j).into();
                        println!("{:?} {:?}", left, right);
                        let mut sum: u32 = 0;
                        if left[left.len() - 1].is_ascii_digit() {
                            let mut k: u32 = 0;
                            for num in left.iter().rev() {
                                if num.is_ascii_digit() {
                                    sum = (u32::from(num & 0xF)) * u32::pow(10, k) + sum;
                                    k += 1;
                                } else {
                                    break;
                                }
                            }
                            println!("Left: {}", sum);
                        }
                        if !schematic[i - 1].as_bytes()[j].is_ascii_digit() {
                            if sum > 0 {
                                sums.push(sum);
                            }
                            sum = 0;
                        }
                        if right[0].is_ascii_digit() || right[1].is_ascii_digit() {
                            for num in right.iter().skip(
                                (!right[0].is_ascii_digit() && right[1].is_ascii_digit()).into(),
                            ) {
                                if *num == b'.' {
                                    break;
                                }
                                if num.is_ascii_digit() {
                                    sum = (sum * 10) + u32::from(num & 0xF);
                                }
                            }
                            println!("Right: {}", sum);
                        }
                        if sum > 0 {
                            sums.push(sum);
                        }
                    }
                    if do_row2 {
                        let (left, right) = schematic[i].as_bytes().split_at(j).into();
                        println!("{:?} {:?}", left, right);
                        let mut sum: u32 = 0;
                        if left[left.len() - 1].is_ascii_digit() {
                            let mut k: u32 = 0;
                            for num in left.iter().rev() {
                                if num.is_ascii_digit() {
                                    sum = (u32::from(num & 0xF)) * u32::pow(10, k) + sum;
                                    k += 1;
                                } else {
                                    break;
                                }
                            }
                            println!("Left: {}", sum);
                        }
                        if !schematic[i].as_bytes()[j].is_ascii_digit() {
                            if sum > 0 {
                                sums.push(sum);
                            }
                            sum = 0;
                        }
                        if right[1].is_ascii_digit() {
                            for num in right {
                                if *num == b'.' {
                                    break;
                                }
                                if num.is_ascii_digit() {
                                    sum = (sum * 10) + u32::from(num & 0xF);
                                }
                            }
                            println!("Right: {}", sum);
                        }
                        if sum > 0 {
                            sums.push(sum);
                        }
                    }
                    if do_row3 {
                        let (left, right) = schematic[i + 1].as_bytes().split_at(j).into();
                        println!("{:?} {:?}", left, right);
                        let mut sum: u32 = 0;
                        if left[left.len() - 1].is_ascii_digit() {
                            let mut k: u32 = 0;
                            for num in left.iter().rev() {
                                if num.is_ascii_digit() {
                                    sum = (u32::from(num & 0xF)) * u32::pow(10, k) + sum;
                                    k += 1;
                                } else {
                                    break;
                                }
                            }
                            println!("Left: {}", sum);
                        }
                        if !schematic[i + 1].as_bytes()[j].is_ascii_digit() {
                            if sum > 0 {
                                sums.push(sum);
                            }
                            sum = 0;
                        }
                        if right[0].is_ascii_digit() || right[1].is_ascii_digit() {
                            for num in right.iter().skip(
                                (!right[0].is_ascii_digit() && right[1].is_ascii_digit()).into(),
                            ) {
                                if *num == b'.' {
                                    break;
                                }
                                if num.is_ascii_digit() {
                                    sum = (sum * 10) + u32::from(num & 0xF);
                                }
                            }
                            println!("Right: {}", sum);
                        }
                        if sum > 0 {
                            sums.push(sum);
                        }
                    }
                    if sums.len() > 1 {
                        println!("Multiplying: {:?} into {res}", sums);
                        res += sums.into_iter().reduce(|a, b| a * b).unwrap();
                    }
                }
            }
        }
        println!("Iteration {} - Result {}", i, res);
    }

    println!("Result: {}", res);
    if DO_EXAMPLE {
        if TASK_PART == 1 {
            assert_eq!(res, EXAMPLE_SUM_PART_1);
        } else if TASK_PART == 2 {
            assert_eq!(res, EXAMPLE_SUM_PART_2);
        }
    }

    return ();
}
