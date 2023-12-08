#include "board.h"

#include <iostream>
#include <iomanip>

namespace gobang {

    Board::Board() : size_(DEFAULT_SIZE) { Init(); }

    Board::Board(int size) : size_(size) { Init(); }

    void Board::Init() {
        state_ = new int[size_ * size_];
        for (int i = 0; i < size_ * size_; i++) {
            state_[i] = EMPTY;
        }
    }

    Board::~Board() {
        delete[] state_;
    }

    int Board::GetSize() const { return size_; }

    int Board::GetState(int x, int y) const {
        return state_[x * size_ + y];
    }

    bool Board::SetStateBlack(int x, int y) {
        return SetState(x, y, BLACK);
    }

    bool Board::SetStateWhite(int x, int y) {
        return SetState(x, y, WHITE);
    }

    bool Board::SetState(int x, int y, int state) {
        if (x < 0 || x >= size_ || y < 0 || y >= size_)
            return false;
        int cur_state = state_[x * size_ + y];
        if (cur_state == EMPTY) {
            state_[x * size_ + y] = state;
            return true;
        }
        return false;
    }

    void Board::Draw() const {
        std::cout << "   ";
        for (int j = 0; j < size_; j++) {
            std::cout << std::setw(3) << (j + 1);
        }
        std::cout << std::endl << std::endl;
        for (int i = 0; i < size_; i++) {
            std::cout << std::setw(3) << (i + 1);
            for (int j = 0; j < size_; j++) {
                int state = state_[i * size_ + j];
                if (state == EMPTY)
                    std::cout << "\x1B[34m" << std::setw(3) << "+" << "\033[0m";
                else if (state == BLACK)
                    std::cout << "\x1B[91m" << std::setw(3) << "@" << "\033[0m";
                else
                    std::cout << "\x1B[97m" << std::setw(3) << "o" << "\033[0m";
            }
            std::cout << std::endl << std::endl;
        }
    }

} // namespace gobang
