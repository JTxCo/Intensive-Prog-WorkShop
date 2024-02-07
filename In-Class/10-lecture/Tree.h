#ifndef TREE_H
#define TREE_H

class Tree {
    public:

        void Seed() { number_seeds_ += 1; };

        int get_number_seeds() { return number_seeds_; }

    private:
        static int number_seeds_;
};

#endif // TREE_H
