(* The lines will be bound as: "Game ID: Round; Round; Round;"*)
(* Each round consists of a csv list, ended by ; *)
type _game = { _id : int }

(* Constraints *)
let _red_max = 12
let _green_max = 13
let _blue_max = 14
let example_file = "example.txt"
let _input_file = "input.txt"

(* Take a round of "amount color" and split into amount + color *)
let _round_extract round =
  String.split_on_char ' ' round
  |> List.partition_map (fun x ->
         match int_of_string_opt x with Some x -> Left x | None -> Right x)
  |> fun (l, r) -> (List.hd l, String.concat "" r)

let () =
  let file_in = open_in example_file in
  let lines =
    really_input_string file_in (in_channel_length file_in)
    |> String.split_on_char '\n'
  in
  close_in file_in;
  flush stdout;
  let _a =
    List.mapi
      (fun i line ->
        print_string "Idx ";
        print_int i;
        print_endline ":";
        let game, rounds =
          String.split_on_char ':' line |> fun l ->
          (List.hd l, String.concat "" (List.tl l))
        in
        print_endline game;
        print_endline rounds;
        let inspect_rounds rounds =
          String.split_on_char ';' rounds
          |> List.iter (fun round ->
                 print_endline round;

                 String.split_on_char ',' round
                 |> List.iter (fun ball -> print_endline ball))
        in
        inspect_rounds rounds;
        print_newline ())
      lines
  in
  ()

(* The plan: Parse each line into id + each round in list *)
(* Then, validate each round. If the rounds are all valid, add id into result. *)
