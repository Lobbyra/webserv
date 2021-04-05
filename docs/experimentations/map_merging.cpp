#include <map>
#include <iostream>

template < class T , class U>
std::ostream& operator<<(std::ostream& s, std::pair<T, U>& v) {
    s << "(" << v.first << ":" << v.second << ")";
    return (s);
}

template < class T , class U>
std::ostream& operator<<(std::ostream& s, std::map<T, U>& v) {
    if (v.empty() == true)
        return (s);
    s << "{";
    for (typename std::map<T, U>::iterator it = v.begin();
         it != --(v.end());
         it++) {
        s << (*it) << ", ";
    }
    s << (*(--(v.end()))) << "}";
    return s;
}

int         main(void) {
    std::map<int, int>  map_1;
    std::map<int, int>  map_2;

    map_1[1] = 1;
    map_1[2] = 2;
    map_1[3] = 3;

    map_2[4] = 4;
    map_2[5] = 5;
    map_2[2] = 435;
    map_2[6] = 6;

    std::cout << "map_1 = " << map_1 << std::endl;
    std::cout << "map_2 = " << map_2 << std::endl << std::endl;

    map_1.insert(map_2.begin(), map_2.end());

    std::cout << "map_1 = " << map_1 << std::endl;

    return (0);
}
