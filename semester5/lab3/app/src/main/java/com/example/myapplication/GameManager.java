package com.example.myapplication;


//import android.content.Intent;
//import android.widget.Toast;

import java.util.ArrayList;

public class GameManager {

    public static final int EMPTY = 0;
    public static final int PAWN = 1;
    public static final int QUEEN = 2;
    public static final int DARK = -1;
    public static final int LIGHT = 1;

    public static final int WAITING_ORIGIN_INPUT = 0;
    public static final int WAITING_END_INPUT = 1;

    public static final int SPACE_OK = 100;
    public static final int MOVE_OK = 101;
    public static final int CAPTURE_OK = 102;
    public static final int INVALID_SPACE = 200;
    public static final int MUST_CAPTURE = 201;
    public static final int EOG_NO_MOVES = 300;
    public static final int EOG_NO_CHECKERS = 301;

    public static final int CAN_MOVE = 400;
    public static final int CAN_CAPTURE = 401;
    public static final int NO_MOVES = 402;

    public static final int N_STARTING_PIECES = 12;
    public static final int BORDER = 8;

    public int[][] board;

    private int roundState;
    private int playerTurn;
    private boolean isCapturing;
    private int mainColor;
    private int enemyColor;

    private int columnOrigin, lineOrigin, columnEnd, lineEnd;
    private boolean mustCapture, movesAvailable = true;

    private int nDarkCheckers, nLightCheckers, winner;

    public GameManager(int color) {

        initializeBoard(color);
        mainColor = color;
        enemyColor = (color == DARK? LIGHT: DARK);
        nDarkCheckers = nLightCheckers = N_STARTING_PIECES;
        roundState = WAITING_ORIGIN_INPUT;
        playerTurn = LIGHT;
        isCapturing = false;
        movesAvailable = true;
    }

    private void addMove(ArrayList<ArrayList<Integer>> moves, int x1, int y1, int x2, int y2) {
        ArrayList<Integer> new_move = new ArrayList<>(4);
        new_move.add(x1);
        new_move.add(y1);
        new_move.add(x2);
        new_move.add(y2);
        moves.add(new_move);
    }

    public int Evaluate(int color) {
        int answer = 0;
        for (int i = 0; i < BORDER; ++i) {
            for (int j = 0; j < BORDER; ++j) {
                answer += board[i][j];
            }
        }
        answer *= color;
        return answer;
    }


    public static class MutableBool {
        Boolean data;
        MutableBool(boolean data) {
            this.data = data;
        }

        public Boolean getData() {
            return data;
        }

        public void setData(Boolean data) {
            this.data = data;
        }
    }

    private int makeMove(ArrayList<Integer> move, MutableBool becameQueen) {
        int lineStart = move.get(0), columnStart = move.get(1);
        int lineEnd = move.get(2), columnEnd = move.get(3);
        int answer = EMPTY;
        board[lineEnd][columnEnd] = board[lineStart][columnStart];
        if (lineEnd - lineStart == 2 || lineEnd - lineStart == -2) {
            int linePrey = lineStart;
            if (lineEnd > lineStart) linePrey++;
            else linePrey--;
            int columnPrey = columnStart;
            if (columnEnd > columnStart) columnPrey++;
            else columnPrey--;
            answer = board[linePrey][columnPrey];
            board[linePrey][columnPrey] = EMPTY;
        }
        board[lineStart][columnStart] = EMPTY;
        if (((colorOf(board[lineEnd][columnEnd]) == LIGHT && lineEnd == 0) ||
                (colorOf(board[lineEnd][columnEnd]) == DARK && lineEnd == 7)) &&
                valueOf(board[lineEnd][columnEnd]) != QUEEN && !mustCapture(colorOf(board[lineEnd][columnEnd]))) {
            board[lineEnd][columnEnd] = (int) (2 * Math.signum(board[lineEnd][columnEnd]));
            becameQueen.setData(true);
        } else {
            becameQueen.setData(false);
        }

        return answer;
    }

    private void unmakeMove(ArrayList<Integer> move, int prey, boolean wasQueen) {
        int lineStart = move.get(0), columnStart = move.get(1);
        int lineEnd = move.get(2), columnEnd = move.get(3);
        board[lineStart][columnStart] = board[lineEnd][columnEnd];
        if (wasQueen) board[lineStart][columnStart] = (int) Math.signum(board[lineStart][columnStart]);
        if (lineEnd - lineStart == 2 || lineEnd - lineStart == -2) {
            int linePrey = lineStart;
            if (lineEnd > lineStart) linePrey++;
            else linePrey--;
            int columnPrey = columnStart;
            if (columnEnd > columnStart) columnPrey++;
            else columnPrey--;
            board[linePrey][columnPrey] = prey;
        }
        board[lineEnd][columnEnd] = EMPTY;
    }

    public int searchBestMove(int depth, int color, ArrayList<Integer> best_move, boolean flag, boolean capturing) {
        int score = Integer.MIN_VALUE;
        int opColor = (color == DARK ? LIGHT : DARK);
        if (!mustCapture(color) && capturing) {
            color = opColor;
            opColor = (color == DARK ? LIGHT : DARK);
            --depth;
        }
        if (depth == 0) {
            return Evaluate(color);
        }
        ArrayList<ArrayList<Integer>> moves = getMoves(color);

        for (ArrayList<Integer> move: moves) {
            MutableBool wasQueen = new MutableBool(false);
            int prey = makeMove(move, wasQueen);
            int tmp = 0;
            if (prey != EMPTY && mustCapture(color)) {
                tmp = searchBestMove(depth, color, best_move, false, true);
            } else {
                tmp = -searchBestMove(depth - 1, opColor, best_move, false, false);
            }
            unmakeMove(move, prey,wasQueen.getData());
            if (tmp > score) {
                score = tmp;
                if (flag) {
                    for (int i = 0; i < 4; ++i) {
                        best_move.set(i, move.get(i));
                    }
                }
            }
        }
        if (score == Integer.MIN_VALUE) {
            if (flag && !moves.isEmpty()) {
                for (int i = 0; i < 4; ++i) {
                    best_move.set(i, moves.get(0).get(i));
                }
            }
        }
        return score;
    }

    private boolean mustCapture(int color) {
        for (int i = 0; i < BORDER; ++i) {
            for (int j = 0; j < BORDER; ++j) {
                if (j % 2 != i % 2) {
                    if (colorOf(board[i][j])==color) {
                        if (isHunter(i, j, color)) return true;
                    }
                }
            }
        }
        return false;
    }

    ArrayList<ArrayList<Integer>> getMoves(int color) {
        ArrayList<ArrayList<Integer>> answer = new ArrayList<>();
        boolean wow = mustCapture(color);
        for (int i = 0; i < BORDER; ++i) {
            for (int j = 0; j < BORDER; ++j) {
                if (j % 2 != i % 2) {
                    if (color == DARK) {
                        if (colorOf(board[i][j]) == DARK) {
                            if (!wow) {
                                if (isWithinBorders(i + 1, j - 1)) {
                                    if (board[i + 1][j - 1] == EMPTY)
                                        addMove(answer, i, j, i + 1, j - 1);
                                }
                                if (isWithinBorders(i + 1, j + 1)) {
                                    if (board[i + 1][j + 1] == EMPTY)
                                        addMove(answer, i, j, i + 1, j + 1);
                                }
                                if (board[i][j] == DARK * QUEEN) {
                                    if (isWithinBorders(i - 1, j - 1)) {
                                        if (board[i - 1][j - 1] == EMPTY)
                                            addMove(answer, i, j, i - 1, j - 1);
                                    }
                                    if (isWithinBorders(i - 1, j + 1)) {
                                        if (board[i - 1][j + 1] == EMPTY)
                                            addMove(answer, i, j, i - 1, j + 1);
                                    }
                                }
                            } else {
                                if (isWithinBorders(i + 2, j - 2)) {
                                    if (colorOf(board[i + 1][j - 1]) == LIGHT && board[i + 2][j - 2] == EMPTY) {
                                        addMove(answer, i, j, i + 2, j - 2);
                                    }
                                }
                                if (isWithinBorders(i + 2, j + 2)) {
                                    if (colorOf(board[i + 1][j + 1]) == LIGHT && board[i + 2][j + 2] == EMPTY) {
                                        addMove(answer, i, j, i + 2, j + 2);
                                    }
                                }
                                if (isWithinBorders(i - 2, j - 2)) {
                                    if (colorOf(board[i - 1][j - 1]) == LIGHT && board[i - 2][j - 2] == EMPTY) {
                                        addMove(answer, i, j, i - 2, j - 2);
                                    }
                                }
                                if (isWithinBorders(i - 2, j + 2)) {
                                    if (colorOf(board[i - 1][j + 1]) == LIGHT && board[i - 2][j + 2] == EMPTY) {
                                        addMove(answer, i, j, i - 2, j + 2);
                                    }
                                }
                            }
                        }
                    } else if (color == LIGHT) {
                        if (colorOf(board[i][j]) == LIGHT) {
                            if (!wow) {
                                if (isWithinBorders(i - 1, j - 1)) {
                                    if (board[i - 1][j - 1] == EMPTY)
                                        addMove(answer, i, j, i - 1, j - 1);
                                }
                                if (isWithinBorders(i - 1, j + 1)) {
                                    if (board[i - 1][j + 1] == EMPTY)
                                        addMove(answer, i, j, i - 1, j + 1);
                                }
                                if (board[i][j] == LIGHT * QUEEN) {
                                    if (isWithinBorders(i + 1, j - 1)) {
                                        if (board[i + 1][j - 1] == EMPTY)
                                            addMove(answer, i, j, i + 1, j - 1);
                                    }
                                    if (isWithinBorders(i + 1, j + 1)) {
                                        if (board[i + 1][j + 1] == EMPTY)
                                            addMove(answer, i, j, i + 1, j + 1);
                                    }
                                }
                            } else {
                                if (isWithinBorders(i + 2, j - 2)) {
                                    if (colorOf(board[i + 1][j - 1]) == DARK && board[i + 2][j - 2] == EMPTY) {
                                        addMove(answer, i, j, i + 2, j - 2);
                                    }
                                }
                                if (isWithinBorders(i + 2, j + 2)) {
                                    if (colorOf(board[i + 1][j + 1]) == DARK && board[i + 2][j + 2] == EMPTY) {
                                        addMove(answer, i, j, i + 2, j + 2);
                                    }
                                }
                                if (isWithinBorders(i - 2, j - 2)) {
                                    if (colorOf(board[i - 1][j - 1]) == DARK && board[i - 2][j - 2] == EMPTY) {
                                        addMove(answer, i, j, i - 2, j - 2);
                                    }
                                }
                                if (isWithinBorders(i - 2, j + 2)) {
                                    if (colorOf(board[i - 1][j + 1]) == DARK && board[i - 2][j + 2] == EMPTY) {
                                        addMove(answer, i, j, i - 2, j + 2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return answer;
    }

    private void initializeBoard(int color) {

        board = new int[8][8];
        int op_color = (color == LIGHT? DARK: LIGHT);

        int i, j;
        for (i = 0; i < BORDER; i++) {
            for (j = 0; j < BORDER; j++) {
                if (j % 2 != i % 2) {
                    if (i <= 2) board[i][j] = DARK * PAWN;
                    else if (i >= 5) board[i][j] = LIGHT * PAWN;
                    else board[i][j] = EMPTY;

                    BoardActivity.updateBoard(i, j, board[i][j]);
                } else
                    board[i][j] = EMPTY;
            }
        }
    }

    public int nextStepInRound(int line, int column) {

        switch (this.roundState) {
            case WAITING_ORIGIN_INPUT:
                if (!movesAvailable) {
                    winner = -1 * playerTurn;
                    return EOG_NO_MOVES;
                }

                if (selectedOriginOK(line, column) == SPACE_OK) {
                    this.roundState = WAITING_END_INPUT;
                    return SPACE_OK;
                } else return INVALID_SPACE;

            case WAITING_END_INPUT:
                switch (selectedEndOK(line, column)) {
                    case SPACE_OK:
                        this.roundState = WAITING_END_INPUT;
                        return SPACE_OK;
                    case MOVE_OK:
                        if (mustCapture)
                            return MUST_CAPTURE;
                        becameQueen(this.playerTurn);
                        moveChecker();
                        newRound();
                        return MOVE_OK;
                    case CAPTURE_OK:
                        if (becameQueen(this.playerTurn)) {
                            makeCapture();
                            newRound();
                            return CAPTURE_OK;
                        }
                        makeCapture();
                        if (zeroCheckers()) {
                            winner = (int) Math.signum(nLightCheckers - nDarkCheckers);
                            return EOG_NO_CHECKERS;
                        }
                        isCapturing = true;
                        if (isHunter(lineEnd, columnEnd, playerTurn)) {
                            lineOrigin = lineEnd;
                            columnOrigin = columnEnd;
                            this.roundState = WAITING_END_INPUT;
                        } else
                            newRound();
                        return CAPTURE_OK;
                    default:
                        return INVALID_SPACE;
                }
        }
        return 0;
    }

    private void newRound() {
        this.roundState = WAITING_ORIGIN_INPUT;
        playerTurn *= -1;
        isCapturing = false;
        switch (canMoveOrCapture(this.playerTurn)) {
            case CAN_CAPTURE:
                mustCapture = true;
                movesAvailable = true;
                break;
            case CAN_MOVE:
                mustCapture = false;
                movesAvailable = true;
                break;
            case NO_MOVES:
                mustCapture = false;
                movesAvailable = false;
                break;
        }

    }

    private int canMoveOrCapture(int color) {
        int i, j;
        boolean hasMoves = false;
        if (color == LIGHT) {
            for (i = 0; i < BORDER; i++) {
                for (j = 0; j < BORDER; j++) {
                    if (i % 2 != j % 2 && colorOf(this.board[i][j]) == this.playerTurn) {
                        if (isHunter(i, j, playerTurn)) return CAN_CAPTURE;

                        else if (!hasMoves) hasMoves = isMover(i, j);
                    }
                }
            }
        } else if (color == DARK) {
            for (i = 7; i >= 0; i--) {
                for (j = 7; j >= 0; j--) {
                    if (i % 2 != j % 2 && colorOf(this.board[i][j]) == this.playerTurn) {
                        if (isHunter(i, j, playerTurn)) return CAN_CAPTURE;
                        else if (!hasMoves) hasMoves = isMover(i, j);
                    }
                }
            }
        }
        if (hasMoves) return CAN_MOVE;
        return NO_MOVES;
    }

    private boolean isHunter(int line, int column, int color) {
        int linePrey, columnPrey, lineHunt, columnHunt;
        int i = 1, j = 1, n = 0;
        int hunter = board[line][column];
        int prey;

        while (n <= 3) {
            linePrey = line + i;
            columnPrey = column + j;
            lineHunt = line + 2 * i;
            columnHunt = column + 2 * j;

            if (isWithinBorders(lineHunt, columnHunt) && isWithinBorders(linePrey, columnPrey)) {
                prey = board[linePrey][columnPrey];
                if (colorOf(prey) == -1 * color && board[lineHunt][columnHunt] == EMPTY)
                    return true;
            }

            if (n % 2 == 0) i *= -1;
            else j *= -1;
            n++;
        }
        return false;
    }

    private boolean isMover(int line, int column) {
        int lineDestiny, columnDestiny;
        int i = 1, j = 1, n = 0;
        int spaceDestiny;
        int mover = board[line][column];

        while (n <= 3) {
            lineDestiny = line + i;
            columnDestiny = column + j;

            if (isWithinBorders(lineDestiny, columnDestiny)) {
                spaceDestiny = board[lineDestiny][columnDestiny];
                if (spaceDestiny == EMPTY && (colorOf(mover) == -1 * i || valueOf(mover) == QUEEN))
                    return true;
            }

            if (n % 2 == 0) i *= -1;
            else j *= -1;
            n++;
        }
        return false;
    }


    private int selectedOriginOK(int line, int column) {
        if (colorOf(board[line][column]) == colorOf(playerTurn)) {
            lineOrigin = line;
            columnOrigin = column;
            return SPACE_OK;
        }
        return INVALID_SPACE;
    }

    private int selectedEndOK(int lineSelected, int columnSelected) {

        int columnDelta = columnSelected - columnOrigin;
        int lineDelta = lineSelected - lineOrigin;
        int checkerMoving = board[lineOrigin][columnOrigin];

        int linePrey = (int) (lineOrigin + (lineDelta) / 2);
        int columnPrey = (int) (columnOrigin + (columnDelta) / 2);
        int prey = board[linePrey][columnPrey];

        if (colorOf(board[lineSelected][columnSelected]) == playerTurn && !isCapturing) {
            BoardActivity.updateBoard(lineOrigin, columnOrigin, board[lineOrigin][columnOrigin]);
            lineOrigin = lineSelected;
            columnOrigin = columnSelected;
            return SPACE_OK;
        }

        if (board[lineSelected][columnSelected] == EMPTY) {
            if (colorOf(checkerMoving) == LIGHT && valueOf(columnDelta) == 1 &&
                    lineDelta == -1 || (lineDelta == 1 && valueOf(checkerMoving) == QUEEN)) {

                lineEnd = lineSelected;
                columnEnd = columnSelected;
                return MOVE_OK;
            }

            else if (colorOf(checkerMoving) == DARK && valueOf(columnDelta) == 1 &&
                    lineDelta == 1 || (lineDelta == -1 && valueOf(checkerMoving) == QUEEN)) {

                lineEnd = lineSelected;
                columnEnd = columnSelected;
                return MOVE_OK;
            }

            else if (colorOf(checkerMoving) == LIGHT &&
                    (valueOf(columnDelta) == 2 || valueOf(columnDelta) == -2) &&
                    (lineDelta == -2 || lineDelta == 2) &&
                    colorOf(prey) == DARK) {

                lineEnd = lineSelected;
                columnEnd = columnSelected;
                return CAPTURE_OK;
            }

            else if (colorOf(checkerMoving) == DARK &&
                    (valueOf(columnDelta) == 2 || valueOf(columnDelta) == -2) &&
                    (lineDelta == 2 || lineDelta == -2) &&
                    colorOf(prey) == LIGHT) {

                lineEnd = lineSelected;
                columnEnd = columnSelected;
                return CAPTURE_OK;
            } else return INVALID_SPACE;
        } else return INVALID_SPACE;
    }

    private void moveChecker() {
        board[lineEnd][columnEnd] = board[lineOrigin][columnOrigin];
        board[lineOrigin][columnOrigin] = EMPTY;

        BoardActivity.updateBoard(lineOrigin, columnOrigin, board[lineOrigin][columnOrigin]);
        BoardActivity.updateBoard(lineEnd, columnEnd, board[lineEnd][columnEnd]);
    }

    private void makeCapture() {
        int deltaLine = lineEnd - lineOrigin;
        int deltaColumn = columnEnd - columnOrigin;

        int linePrey = lineOrigin + deltaLine / 2;
        int columnPrey = columnOrigin + deltaColumn / 2;

        if (colorOf(board[linePrey][columnPrey]) == LIGHT)
            nLightCheckers--;
        else
            nDarkCheckers--;

        board[lineEnd][columnEnd] = board[lineOrigin][columnOrigin];
        board[lineOrigin][columnOrigin] = EMPTY;
        board[linePrey][columnPrey] = EMPTY;

        BoardActivity.updateBoard(lineOrigin, columnOrigin, board[lineOrigin][columnOrigin]);
        BoardActivity.updateBoard(lineEnd, columnEnd, board[lineEnd][columnEnd]);
        BoardActivity.updateBoard(linePrey, columnPrey, board[linePrey][columnPrey]);
    }


    private boolean isWithinBorders(int line, int column) {
        return (line >= 0 && line < BORDER && column >= 0 && column < BORDER);
    }

    private boolean becameQueen(int color) {
        int thisCell = board[lineOrigin][columnOrigin];
        if (valueOf(thisCell) != QUEEN &&
                ((lineEnd == 7 && colorOf(thisCell) == DARK) || (colorOf(thisCell) == LIGHT && lineEnd == 0))) {
            board[lineOrigin][columnOrigin] *= 2;
            return true;
        }
        return false;
    }

    private boolean zeroCheckers() {
        return (nDarkCheckers == 0 || nLightCheckers == 0);
    }

    public int getWinner() {
        return winner;
    }

    public int getPlayerTurn() {
        return playerTurn;
    }

    private static int colorOf(int valueInBoard) {
        return (int) Math.signum(valueInBoard);
    }

    private static int valueOf(int valueInBoard) {
        return Math.abs(valueInBoard);
    }

}
