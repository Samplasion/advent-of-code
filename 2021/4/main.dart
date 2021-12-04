import 'dart:io';

main() async {
  File input = File('input.txt');
  String content = (await input.readAsString()).trim();
  List<int> numbers = content.split('\n\n')[0].split(",").where((element) {
    return element.isNotEmpty;
  }).map((s) {
    return int.parse(s);
  }).toList();
  List<Board> p1Boards = content
      .split('\n\n')
      .skip(1)
      .map((line) => Board.fromString(line))
      .toList();
  List<Board> p2Boards = p1Boards.map((board) => board.clone()).toList();

  part1(numbers: numbers, boards: p1Boards);
  part2(numbers: numbers, boards: p2Boards);
}

void part1({
  required List<int> numbers,
  required List<Board> boards,
}) {
  bool foundWinner = false;
  Board? winningBoard = null;
  for (int pick in numbers) {
    if (foundWinner) break;
    for (Board board in boards) {
      board.add(pick);
      if (board.checkBingo()) {
        foundWinner = true;
        winningBoard = board;
        break;
      }
    }
  }

  if (foundWinner && winningBoard != null) {
    print("[Part 1] The score of the first winning board "
        "is: ${winningBoard.score}");
  }
}

void part2({
  required List<int> numbers,
  required List<Board> boards,
}) {
  int winners = 0;
  Board? lastWinningBoard;
  for (int pick in numbers) {
    if (winners == boards.length) break;
    for (Board board in boards) {
      if (board.hasWon) continue;
      board.add(pick);
      if (board.checkBingo()) {
        winners++;
        if (winners == boards.length) {
          lastWinningBoard = board;
          break;
        }
      }
    }
  }

  if (lastWinningBoard != null) {
    print("[Part 2] The score of the last winning board "
        "is: ${lastWinningBoard.score}");
  }
}

class Board {
  late final List<List<int>> board;
  final List<int> marked = [];
  bool hasWon = false;

  Board._(this.board);

  factory Board.fromString(String input) {
    var lines = input.split('\n');
    List<List<int>> board = [];
    for (var line in lines) {
      var row = line.trim().split(RegExp(r'  ?')).map((c) {
        return int.tryParse(c) ?? 0;
      }).toList();
      board.add(row);
    }
    return Board._(board);
  }

  bool add(int number) {
    if (board.any((row) => row.contains(number))) {
      marked.add(number);
      return true;
    }
    return false;
  }

  bool checkBingo() {
    // Check vertical
    for (var i = 0; i < 5; i++) {
      if (board[i].every((n) => marked.contains(n))) {
        this.hasWon = true;
        return true;
      }
    }

    // Check horizontal
    for (var i = 0; i < 5; i++) {
      var row = board.map((row) => row[i]).toList();
      if (row.every((n) => marked.contains(n))) {
        this.hasWon = true;
        return true;
      }
    }

    return false;
  }

  int get score {
    if (!checkBingo()) {
      return 0;
    }

    return marked.last *
        board.expand((row) => row).fold(0, (score, element) {
          if (marked.contains(element)) {
            return score;
          }
          return score + element;
        });
  }

  Board clone() {
    return Board._(board.map((row) => row.toList()).toList());
  }
}
