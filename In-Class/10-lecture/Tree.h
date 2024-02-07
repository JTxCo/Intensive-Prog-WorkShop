#ifndef TREE_H
#define TREE_H

class Tree {
    public:
        static int tree_count;
        virtual void Seed() { number_seeds_ += 1; }

        int get_number_seeds() { return number_seeds_; }

    protected: // We make this protected, so derived classes can access it
        static int number_seeds_;
};

class Sapling : public Tree {
    public:
        //override the seed method
        void Seed() override { number_seeds_ += 2; } // Keyword override has been added
};

#endif // TREE_H
