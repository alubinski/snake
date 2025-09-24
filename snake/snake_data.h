#ifndef SNAKE_DATA_H
#define SNAKE_DATA_H

enum MoveDirection { UP, DOWN, LEFT, RIGHT };

struct SnakeData {
  int headRow;
  int headCol;
  int length;
  MoveDirection direction;
};

#endif // SNAKE_DATA_H
