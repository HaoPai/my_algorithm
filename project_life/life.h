#ifndef _LIFE_H_
#define _LIFE_H_
const int maxrow = 15, maxcol = 15;
class Life {
public:
    void initialize();
    void print();
    void update();
private:
    int grid[maxrow+2][maxcol+2];
    int neighbor_count(int row,int col);
 };
#endif
