// header file for the functions and class that is in the pe3 references file
#ifndef PE3_REFERENCES_H
#define PE3_REFERENCES_H


void modify(int *ptr);
void modify2(int &ref);
void modify3(const int &ref, int *ptr);

class MyClass{
    private:
        int x;
    public:
        MyClass(int x);
        int get_x();
        bool operator==(const MyClass &other);
        MyClass operator+(const MyClass &other);
};

#endif // PE3_REFERENCES_H