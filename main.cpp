#include <iostream>
#include <sstream>
#include <vector>

const int ENOARG = -1;

int AskForDimensions(void);
void AttemptSolution(std::vector<int>, int);
bool OkaySoFar(std::vector<int>);
void PrintSolution(std::vector<int>);
int ReadFromArguments(int argc, char** argv);
int RequireDimensionsArgument(int argc, char** argv);

int main(int argc, char** argv) {
    int dimensions = RequireDimensionsArgument(argc, argv);
    AttemptSolution(std::vector<int>(), dimensions);
    return 0;
}

int AskForDimensions(void) {
    int dimensions = 0;
    std::cout << "Please enter a dimension...\n";
    std::cin >> dimensions;
    return dimensions;
}

void AttemptSolution(std::vector<int> board, int dimensions) {
    if(board.size() == dimensions) {
        PrintSolution(board);
        return;
    }

    for(int position = 0; position < dimensions; position++) {
        if(std::find(board.begin(), board.end(), position) == board.end()) {
            board.push_back(position);
            if(OkaySoFar(board)) {
                AttemptSolution(board, dimensions);
            }
            board.pop_back();
        }
    }
}

bool OkaySoFar(std::vector<int> board) {
    int i = board.size() - 1;
    for(int j = 0; j < i; j++) {
        if(i - j == abs(board[i] - board[j])) {
            return false;
        }
    }
    return true;
}

void PrintSolution(std::vector<int> board) {
    std::cout << "[ ";
    for(int position : board) {
        std::cout << position << " ";
    }
    std::cout << "]\n";
}

int ReadFromArguments(int argc, char** argv) {
    if(argc == 1) {
        return ENOARG;
    }

    std::istringstream ss(argv[1]);
    int dimensions;
    if (!(ss >> dimensions)) {
        std::cerr << "Invalid number: " << argv[1] << '\n';
        return ENOARG;
    } else if (!ss.eof()) {
        std::cerr << "Trailing characters after number: " << argv[1] << '\n';
        return ENOARG;
    }
    return dimensions;
}

int RequireDimensionsArgument(int argc, char** argv) {
    int dimensions = ReadFromArguments(argc, argv);
    if(dimensions == ENOARG) {
        return AskForDimensions();
    } else {
        return dimensions;
    }
}